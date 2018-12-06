#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lib.h"
#include "can.h"
#include "memoire_24.h"
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

//Initialise les ports en entree ou en sortie
void initialisationPorts(uint8_t A, uint8_t B, uint8_t C, uint8_t D)
{
    sei();
    DDRA = A;
    DDRB = B;
    DDRC = C;
    DDRD = D;
}

void terminerProgram()
{
    DDRA = 0x00;
    DDRB = 0x00;
    DDRC = 0x00;
    DDRD = 0x00;
    cli();
}

void attendre(unsigned int multiplicateur)
{
    for (unsigned int i = 0; i < multiplicateur; i++)
    {
        _delay_ms(25);
    }
}
//Permettre l'interruption du bouton
void permettreBoutonInterrupt()
{
    sei();
    EICRA |= _BV(ISC00) | _BV(ISC01);
    EIMSK |= (1 << INT0);
}
void desactiverPinInterrupt()
{
    PCICR = PCICR xor PCICR;
}

void permettrePinInterrupt()
{
    sei();
    PCICR |= _BV(PCIE0);
    PCMSK0 |= _BV(PCINT1) | _BV(PCINT3); 
}

//Part la minuterie en mode PWM
void partirMinuteriePWM(uint8_t duree)
{

    OCR1A = duree;

    OCR1B = duree;
}
void PWMAjuste(uint8_t duree1, uint8_t duree2)
{
    OCR1A = duree1;

    OCR1B = duree2;
}

//Initalise le signal sur les roues
void initialisationPWM()
{
    TCNT1 = 0;

    TCCR1A = _BV(COM1A0) | _BV(COM1A1) | _BV(WGM10) | _BV(COM1B0) | _BV(COM1B1);

    TCCR1B = _BV(CS11);
}

//Initialise le timer selon l'entree donnee
void initialisationMinuterie(uint8_t duree)
{
    TCNT0 = 0;

    OCR0A = duree;

    TCCR0A = _BV(WGM01);

    TCCR0B = _BV(CS02) | _BV(CS00); //Prescale 1024

    TIMSK0 = _BV(OCIE0A);
}

void initialisationMinuterie(){
    TCNT0 = 0;
    OCR0A = 255;
    TCCR0A = _BV(WGM01);
    TCCR0B = _BV(CS00) | _BV(CS02);
    TIMSK0 = _BV(OCIE0A);
}

//Arrete la comparaison de la minuterie
void arreterMinuterie(){
    TIMSK0 = TIMSK0 xor TIMSK0; //mise a zero
}

/*********************************************
 * Fonction : initialisationINT0 
 * IN : void 
 * OUT : void 
 * Description : initialise l'interruption INT0 
*********************************************/

void initialisationINT0(void) 
{
// cli est une routine qui bloque toutes les interruptions.
    cli ();

// cette procédure ajuste le registre EIMSK
// de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0);
// il faut sensibiliser les interruptions externes aux
// changements de niveau du bouton-poussoir
// en ajustant le registre EICRA
    EICRA |= 3;
// sei permet de recevoir à nouveau des interruptions.
    sei ();
}
	
