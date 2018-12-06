#include <avr/io.h>
#include <util/delay.h>	
#include <avr/interrupt.h>
#include "lib.h"
#include "can.h"
#include "memoire_24.h"

void ajustementPWMSonorite(int frequenceIndex);
void  arreterSonorite();
void jouerNote(uint8_t note);
void arpegeDeC();
void dank();
