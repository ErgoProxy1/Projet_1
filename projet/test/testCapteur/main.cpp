#include "lib.h"
#include "../../include/gestionMoteur.h"


int scanState = 0;
enum etats{INIT,SCAN,TURN_SEQUENCE, AFFICHAGE};
etats etat = INIT;
bool isScan = false;
bool detecteR = false;
virage vir;



using namespace std;
int main()
{   
    initialisationPorts(0x00,0xff,0xff,0xff);
    initialisationPWM();
    while(1)
    {
		switch(etat) 
		{
			case INIT : //affiche nom
						//delay ms 3 secondes
						etat = SCAN;
						break;
			case SCAN :
			PORTB = 0x01;
				detecteR = false; // Allumer LED, commencer scanner
				if((PINA & 0x1f) == 0x1f && scanState == 0) { isScan = true; PORTB = 0x01;}
				ajustement(PINA & 0x1f, detecteR, vir);
				if(detecteR) { etat = TURN_SEQUENCE; isScan = false;}
				if((PINA & 0x1f) == 0x1f && scanState == 3) { isScan = false; PORTB = 0x00; arreterMoteur(); etat = AFFICHAGE;}
				break;
				if(scanState == 1 || scanState == 3 ) { isScan = true;}	
			case TURN_SEQUENCE :
			PORTB = 0x02;
			
				permettrePinInterrupt();
				gestionMoteurTS(PINA & 0x1f, detecteR, vir,scanState);
				desactiverPinInterrupt();
				etat = SCAN;
				isScan = false;
				break;
			case AFFICHAGE : break;
		}
				
	}
}

ISR(PCINT0_vect)
{
	detecteR = false;
}






