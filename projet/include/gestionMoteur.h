#include "pwmFuncs.h"
enum virage{GAUCHE,DROITE};
void ajustement(uint8_t Pin, bool& detecteR, virage& quelVirage);
void gestionMoteurTS(uint8_t Pin,bool& detecteR,virage& quelVirage, int& scanState);

