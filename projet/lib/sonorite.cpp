#include "../include/sonorite.h"
#include "delFuncs.h"
// OCR0A = ((8000000) / (2*256*frequence)) - 1

const uint8_t frequence[37] = { 141, 135, 126, 119, 112, 105, 99, 94, 89, 84, 79, 74, 70, 66, 62, 59, 55, 52, 49, 46, 44, 41, 39

,37, 35, 33, 31, 29, 27, 26, 24, 23, 21, 20, 19, 18, 17 }; //C4 a index 60 (59 dans le tableau), C5 a  index 72 (29 dans le tableau)

// Active la sonorite et set la frequence du son
void ajustementPWMSonorite(int frequenceIndex) {

	OCR0A = frequence[frequenceIndex - 45];

	TCCR0A = _BV(COM0A0) | _BV(WGM01);

	TCCR0B = _BV(CS02) | _BV(WGM02);
}

void arreterSonorite() {
	TCCR0B = _BV(WGM02);
}

void jouerNote(uint8_t note) {
	if (note == 0) {
		arreterSonorite();
	}
	else {
		ajustementPWMSonorite(note);
	}
}

// C4 - E4 - G4 - C5 - G4 - E4 - C4
void arpegeDeC() {
	uint8_t chanson[] = { 60, 64, 67, 72, 67, 64, 60 };
	unsigned int tailleChanson = 7;
	for (unsigned int i = 0; i < tailleChanson; i++) {
		jouerNote(chanson[i]);
		_delay_ms(2000); //80 bpm (60000 / bpm)
	}
}

void dank(){ // 630 is 90 bpm
	uint8_t chanson[] = {63, 70, 70, 68, 70, 68, 66, 68, 68, 66, 63, 66};
 
	jouerNote(chanson[0]);
	for(int i = 0; i < 15; i++) { couleurAmbre(); }
	jouerNote(0);
	for(int i = 0; i < 15; i++) { couleurAmbre(); }
	jouerNote(chanson[1]);
	for(int i = 0; i < 15; i++) { couleurAmbre(); }
	jouerNote(0);
	for(int i = 0; i < 15; i++) { couleurAmbre(); }

	jouerNote(chanson[2]);
	for(int i = 0; i < 15; i++) { couleurAmbre(); }
	jouerNote(chanson[3]);
	for(int i = 0; i < 15; i++) { couleurAmbre(); } 
	jouerNote(chanson[4]);
	for(int i = 0; i < 15; i++) { couleurAmbre(); }
	jouerNote(0);
	for(int i = 0; i < 15; i++) { couleurAmbre(); }

	jouerNote(chanson[5]);
	for(int i = 0; i < 15; i++) { couleurAmbre(); } 
	jouerNote(chanson[6]);
	for(int i = 0; i < 15; i++) { couleurAmbre(); } 
	jouerNote(chanson[7]);
	for(int i = 0; i < 15; i++) { couleurAmbre(); }
	jouerNote(0);
	for(int i = 0; i < 15; i++) { couleurAmbre(); }

	jouerNote(chanson[8]);
	for(int i = 0; i < 15; i++) { couleurAmbre(); } 
	jouerNote(chanson[9]);
	for(int i = 0; i < 15; i++) { couleurAmbre(); } 
	jouerNote(chanson[10]);
	for(int i = 0; i < 15; i++) { couleurAmbre(); } 
	jouerNote(chanson[11]);
	for(int i = 0; i < 15; i++) { couleurAmbre(); } 
	jouerNote(0); 
	eteindreDEL(); 
}
