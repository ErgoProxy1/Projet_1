#include "pwmFuncs.h"

void avance(uint8_t vitesse) {
	//Configurer les sortie de PinD 3 et 4 pour avancer 
	// Operation ET logique bit par bit :  0b 0000 1100
	PORTD |= 0x0c;
	partirMinuteriePWM(vitesse);
}

void reculer(uint8_t vitesse) {
	//Configurer les sortie de PinD 3 et 4 pour reculer 
	// Operation OU logique bit par bit :  0b 1111 0011
	PORTD |= 0xf3;
	partirMinuteriePWM(vitesse);
}

/*void tournerGauche90Degre() {
	//Configurer les sortie de PinD 3 et 4 pour tourner a gauche  
	// Operation ET et OU logique bit par bit :  PORTD & 0b 1111 1011 | 0b 0000 1000
	PORTD = (PORTD & 0xfb) | 0x08;
	avance(64);
	_delay_ms(850);
	arreterMoteur();
}

void tournerDroite90Degre() {
	//Configurer les sortie de PinD 3 et 4 pour reculer 
	// Operation OU logique bit par bit :  PORTD & 0b 1111 0111 | 0b 0000 0100
	PORTD = (PORTD & 0xf7) | 0x04;
	avance(64);
	_delay_ms(850);
	arreterMoteur();
}
*/

void arreterMoteur() {
	partirMinuteriePWM(255);
}

void decalageDroite()
{
	PORTD |= 0x0c;
	PWMAjuste(200,90);
	
}
void decalageGauche()
{
	PORTD |= 0x0c;
	PWMAjuste(90,200); // (roue droite, roue gauche)
	
}
void tournerDroitePivot()
{
	PORTD = (PORTD & 0xfb) | 0x08; 
	PWMAjuste(255,100);
}
void tournerGauchePivot()
{
	PORTD = (PORTD & 0xf7) | 0x04;
	PWMAjuste(100,255);
}
void virageGauche()
{
	PORTD |= 0x0c;
	PWMAjuste(255,150);
}
void virageDroite()
{
	PORTD |= 0x0c;
	PWMAjuste(150,255);
}
