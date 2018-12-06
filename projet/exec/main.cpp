#include <stdlib.h>
#include <avr/io.h>
#include "lib.h"
#include "can.h"
#include "memoire_24.h"
#include "pwmFuncs.h"
#include "delFuncs.h"
#include "sonorite.h"
#include "lcd.h"
#include "distance.h"
#include "gestionMoteur.h"
#include <math.h>
#include "transmissionUART.h"
#include <avr/interrupt.h>

int scanState = 0;
enum etats{INIT,SCAN,TURN_SEQUENCE, AFFICHAGE, TRANSMISSION};
etats etat = INIT;
bool isScan = false;
bool detecteR = false;
virage vir;

//IR Variables
unsigned int scanLeft[250];
unsigned int scanRight[250];
//unsigned int storageLeft[100];
//unsigned int storageRight[100];
volatile uint8_t inputLeft = 6;
volatile uint8_t inputRight = 7;
volatile uint16_t voltageLeft = 0; 
volatile uint16_t voltageRight = 0;
volatile unsigned int distanceGauche = 0;
volatile unsigned int distanceDroite = 0;
can leftIR;
can rightIR;
volatile int prescale = 0;
volatile unsigned int nombreMesures = 0;
unsigned int murGauche = 0;
unsigned int murDroite = 0;
bool hasScannedOne = false;
bool hasScannedTwo = false;
volatile int position = 0;
//unsigned int dernierePosition1;
//unsigned int dernierePosition2 = 0;
volatile bool doitAfficher = false;
volatile int correctif = 7; 

void clearTableau(unsigned int* tableau){
	for(int i = 0; i < 200; i++){
		tableau[i] = 0;
	}
}

using namespace std;
int main()
{   
	clearTableau(scanLeft);
	clearTableau(scanRight);
    initialisationPorts(0x00,0xff,0xff,0x00);
    initialisationPWM();
	initialisationMinuterie();
    while(1)
    {
		switch(etat) 
		{	
			//Cas initiale
			case INIT:
				afficherNom();
				_delay_ms(3000);
				clearLCD();
				initialisationPorts(0x00,0xff,0xff,0xff);
				etat = SCAN;
				break;
			
			//Cas ou le robot avance et scan les murs
			case SCAN :
			
				if(hasScannedTwo == true)
				{
					correctif = 7; 
				}
				else if(hasScannedOne == true)
				{
					correctif = -7; 
				}
				else 
				{
					correctif = 7; 
				}
				detecteR = false; // Allumer LED, commencer scanner
				if((PINA & 0x1f) == 0x1f && scanState == 0) { isScan = true;PORTB = 0x02;}
				ajustement(PINA & 0x1f, detecteR, vir);
				if(detecteR) { etat = TURN_SEQUENCE; isScan = false;}
				if((PINA & 0x1f) == 0x1f && scanState == 3) { isScan = false; PORTB = 0x00; arreterMoteur(); etat = AFFICHAGE;}
				if(scanState == 1 || scanState == 3 ) { isScan = true;}	
				break;
			
			//Cas ou le robot fait les virages et calcul la longeur des murs
			case TURN_SEQUENCE :
				isScan = false;
				gestionMoteurTS(PINA & 0x1f, detecteR, vir,scanState);
				
				etat = SCAN;
				//isScan = false;

				if(scanState == 0 && hasScannedOne == false){
					isScan = false;
					PORTB = 0x01;
					hasScannedOne = true;
				}

				else if(scanState == 2 && hasScannedTwo == false){
					isScan = false;
					PORTB = 0x02;
					hasScannedTwo = true;
				}

				break;
			//Cas ou le robot affiche les informations finales sur LCD et joue la musique
			case AFFICHAGE : 
				isScan = false;
				murGauche = calculerLongueur(scanLeft, 130, nombreMesures);
				murDroite = calculerLongueur(scanRight, 130, nombreMesures);
				
				afficherLongueurMur(murGauche, murDroite);
				etat = TRANSMISSION; 
				break;
			case TRANSMISSION : 
				
				initialisationUART(); 
				initialisationPorts(0x00, 0xff, 0xff, 0x00);
				PORTD = 0x00; 
				initialisationINT0(); 
 

				while (1) 
				{
					if(doitAfficher)
					{
						transmissionMur(scanLeft, scanRight, nombreMesures); 
						dank(); 
						doitAfficher = false; 
					}
				}

				break; 
		}
				
	}
}

//Interuption pour enregistrer les mesures du capteur Sharp
ISR(TIMER0_COMPA_vect)
{
	if (isScan == true)
	{
		if (prescale == 0)
		{
			voltageLeft = leftIR.lecture(6);
			voltageRight = rightIR.lecture(7);
			distanceGauche = DistanceEnCm(voltageLeft) + correctif;
			distanceDroite = DistanceEnCm(voltageRight) - correctif;
			scanLeft[position] = distanceGauche;
			scanRight[position] = distanceDroite;
			clearLCD(); 
			afficherLongueurMur(distanceGauche, distanceDroite);
			prescale++;
			position ++;
			nombreMesures++;
			disp << " " << nombreMesures; 
		}
		else if (prescale == 1)
			prescale++;
		else if (prescale == 2) 
			prescale++; 
		else
			prescale = 0;
		
	}
}

ISR(PCINT0_vect)
{
	detecteR = false;
}

ISR(INT0_vect) 
{
    _delay_ms(10); 
    if((PIND & 0x04) == 0x04) 
    {
        if (etat == TRANSMISSION)
		{
			doitAfficher = true;
		} 
    }
}