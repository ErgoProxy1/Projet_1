#include "gestionMoteur.h"
#include "pwmFuncs.h"


void ajustement(uint8_t Pin, bool& detecteR, virage& quelVirage)
{
	switch(Pin & 0x1f){
		case 0x01 :
		case 0x02:
		case 0x03 :                                                                    
		case 0x06 : decalageDroite(); break;
		case 0x18:
		case 0x08:
		case 0x10 :
		case 0x0C : decalageGauche(); break;
		case 0x1f :
		case 0x04 : avance(140); break;
		case 0x1e :
		case 0x1c : quelVirage = DROITE; avance(140); break;
		case 0x0f :
		case 0x07 : quelVirage = GAUCHE; avance(140); break;
		case 0x00 : arreterMoteur();detecteR = true; break;
		default : avance(90); break;
		}
}

void gestionMoteurTS(uint8_t Pin, bool& detecteR, virage& quelVirage, int& scanState)
{
    permettrePinInterrupt();
	switch(quelVirage){
		case DROITE : if(scanState == 0) {ajustement(Pin & 0x1f, detecteR, quelVirage); while(detecteR) { tournerDroitePivot(); }}
					  else if(scanState == 2) {ajustement(Pin & 0x1f, detecteR, quelVirage);
										  avance(140);
		                                  _delay_ms(850);
		                                  arreterMoteur();
										  _delay_ms(850);
                                          while(detecteR) {virageDroite();}
										  arreterMoteur();
										  scanState++;}
										  break;
		case GAUCHE : if(scanState == 0) {ajustement(Pin & 0x1f, detecteR, quelVirage);
										avance(140);
										_delay_ms(850);
										arreterMoteur();
										_delay_ms(850);
        								while(detecteR) {virageGauche();}
										arreterMoteur();
										scanState++;
										}
					else if(scanState == 1) {ajustement(Pin & 0x1f, detecteR, quelVirage);
										while(detecteR){ tournerGauchePivot();} scanState++;}
					break;
					

	}
	desactiverPinInterrupt();
} 
