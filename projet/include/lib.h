#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "transmissionUART.h"


//initialisations 
void initialisationPorts(uint8_t A, uint8_t B, uint8_t C, uint8_t D);
void initialisationPWM();
void initialisationMinuterie(uint8_t duree);
void initialisationINT0(void); 

void terminerProgram();
void attendre(unsigned int multiplicateur);
void permettreBoutonInterrupt();
void permettrePinInterrupt();
void desactiverPinInterrupt();
void partirMinuterieCTC(uint16_t duree, uint16_t prescale);
void partirMinuteriePWM(uint8_t duree);
void PWMAjuste(uint8_t duree1, uint8_t duree2);
void arreterMinuterie();
void initialisationPWM();
void initialisationMinuterie();
