#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"
#include "../../../include/lcd.h"

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
*/
int main() {
	uint8_t inputLeft = 6;
	uint8_t inputRight = 7;
	initialisation();
	can detectionLeft;
	can detectionRight;
	for (;;) {
		uint16_t voltageLeft = detectionLeft.lecture(inputLeft);
		uint16_t voltageRight = detectionRight.lecture(inputRight);


		double distanceLeft = 200.3775040589502 - 2.2657665648980 * voltageLeft
			+ 0.0116395328796 * voltageLeft * voltageLeft - 0.0000299194195 * voltageLeft * voltageLeft * voltageLeft
			+ 0.0000000374087 * voltageLeft * voltageLeft * voltageLeft * voltageLeft - 0.0000000000181 * voltageLeft * voltageLeft * voltageLeft * voltageLeft * voltageLeft;
		double distanceRight = 200.3775040589502 - 2.2657665648980 * voltageRight
			+ 0.0116395328796 * voltageRight * voltageRight - 0.0000299194195 * voltageRight * voltageRight * voltageRight
			+ 0.0000000374087 * voltageRight * voltageRight * voltageRight * voltageRight - 0.0000000000181 * voltageRight * voltageRight * voltageRight * voltageRight * voltageRight;



		afficherLongueurMur((int)distanceLeft, (int)distanceRight);
		_delay_ms(1000);
	}
}
