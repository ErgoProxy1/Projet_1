/***********************************************
 * Fichier : delFuncs.cpp 
 * Auteur : Jafaar Kaoussarani
 * Date : 15 novembre 2018 
 * Modifier par : Kevin Clapperton
 * Mise à jour : 3 décembre 2018
 * Description : Fonctions général de la DEL 
***********************************************/

#include "delFuncs.h"
#include <util/delay.h>	

/*******************************************
 * Fonction : allumerDEF 
 * IN : void 
 * OUT : void 
 * Description : Allumer led (sans couleur spécifié) 
*******************************************/

void allumerDEL() {
	PORTB |= 0x01;
	PORTB &= 0xfd;
}

/*******************************************
 * Fonction : eteindreDEL
 * IN : void 
 * OUT : void 
 * Description : éteint la led 
*******************************************/

void eteindreDEL() {
	PORTB &= 0xfc;
}

/*******************************************
 * Fonction : toggleDEL
 * IN : void 
 * OUT : void 
 * Description : change l'état de la led peu 
 * 				importe la couleur initial 
 * 				(sans couleur spécifié) 
*******************************************/

void toggleDEL() {
	if ((PORTB & 0x03) == 0x00)
	{
		allumerDEL(); 
	}
	else
	{
		eteindreDEL(); 
	}
}

/*******************************************
 * Fonction : toggleCouleur
 * IN : void 
 * OUT : void 
 * Description : change la couleur de la led peu 
 * 				importe l'état initial 
*******************************************/

void toggleCouleur() {
	if ((PORTB & 0x01) == 0x01)
	{
		PORTB |= 0x02;
		PORTB &= 0xfe;
	}
	else
	{
		PORTB |= 0x01;
		PORTB &= 0xfd;
	}
}

/*******************************************
 * Fonction : couleurAmbre
 * IN : void 
 * OUT : void 
 * Description : ATTENTION! Il faut appeler la
 * 				fonction plusieur fois pour avoir 
 * 				la couleur ambré clair. 
*******************************************/

void couleurAmbre() 
{
	    _delay_ms(15); 
		PORTB |= 0x01;
		PORTB &= 0xfd; 
        _delay_ms(5); 
		PORTB |= 0x02;
		PORTB &= 0xfe; 
}