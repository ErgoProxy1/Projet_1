#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../../include/lcd.h"
#include "../include/lib.h"
#include "../include/can.h"
using namespace std;

volatile int counter = 0;
volatile int prescale = 0;
can lectureGauche;
can lectureDroite;


ISR(TIMER0_COMPA_vect)
{
    if (prescale == 0){
        //mesure
        counter++;
       prescale++;
    }
    else if (prescale == 1)
    {
        prescale++; 
    }
    else {
        prescale = 0; 
    }

    //counter++;
}

void partirInterrupt65ms()
{
 
    // mode CTC du timer 1 avec horloge divisee par 1024

    // interruption apres la duree specifiee

    TCNT0 = 0; // Compteur

    OCR0A = 255; // 31.25 ms

    TCCR0A = _BV(WGM01); // Set le premier bit du registre a un

    TCCR0B = _BV(CS02) | _BV(CS00); // Meme chose qu'en haut

    TIMSK0 = _BV(OCIE0A); // Set le bit de comparaison entre OCR0A et TCNT0 a 1
}

/*void initialisation () {
	DDRA = 0x00;
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0xff;
}*/

int main()
{
    initialisationPorts(0, 0xff, 0xff, 0);
    partirInterrupt65ms();
    _delay_ms(1000);
    afficherLongueurMur(counter, 0);
} 


