#include <avr/io.h>
#include <util/delay.h>	
#include <avr/interrupt.h>
#include "lib.h"
#include "can.h"
#include "memoire_24.h"

void avance(uint8_t vitesse);
void reculer(uint8_t vitesse);
void tournerGauche90Degre();
void tournerDroite90Degre();
void arreterMoteur();
void decalageGauche();
void decalageDroite();
void tournerDroitePivot();
void tournerGauchePivot();
void virageGauche();
void virageDroite();
