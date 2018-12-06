#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include "can.h"

using namespace std;

//https://acroname.com/articles/linearizing-sharp-ranger-data

void initialisation ( void ) {
	DDRA = 0x00;
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xff;
}
// 322 -> 1 cm
// A6 -- left   A7 -- right

/*
20cm:  272

40cm:  145

60cm:  116

80cm:  104

R = (6787/(voltage - 3) - 4);

OCR1A = 3125
*/

double DistanceEnCm(uint16_t distance) {
	return 200.3775040589502 - 2.2657665648980 * distance
		+ 0.0116395328796 * distance * distance - 0.0000299194195 * distance * distance * distance
		+ 0.0000000374087 * distance * distance * distance * distance 
		- 0.0000000000181 * distance * distance * distance * distance * distance;
}

double calculerLongeur(double vect[], double distanceTrajet, unsigned int size){
	double temp = 0.0;
	for (unsigned int i = 1; i < size; i++){ // i = 1 pour eviter de sortir du array space
		temp += sqrt(pow((vect[i]-vect[i-1]),2) + pow((distanceTrajet/size),2)); //Pythagore
	}
	return temp;
} 

int main() {
	uint8_t inputLeft = 6;
	uint8_t inputRight = 7;
	uint16_t voltageLeft = 0;
	uint16_t voltageRight = 0;
	double distanceGauche = 0.0;
	double distanceDroite = 0.0;
	initialisation();
	can detectionLeft;
	can detectionRight;
	double distance = 20;
	
	for (;;) {
		 voltageLeft = detectionLeft.lecture(inputLeft);
		 voltageRight = detectionRight.lecture(inputRight);
		 distanceGauche = DistanceEnCm(voltageLeft);
		 distanceDroite = DistanceEnCm(voltageRight);
		_delay_ms(100);
		if (distanceDroite >= 10 && distanceDroite <= 11){
			PORTC = 0x01;
		}
		afficherLongueurMur((int)murGauche, (int)murDroite);
	}
}
