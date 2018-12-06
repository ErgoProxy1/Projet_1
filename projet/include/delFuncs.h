/***********************************************
 * Fichier : delFuncs.h
 * Auteur : Jafaar Kaoussarani
 * Date : 15 novembre 2018 
 * Modifier par : Kevin Clapperton
 * Mise à jour : 3 décembre 2018
 * Description : Fonctions général de la DEL 
***********************************************/

#include <avr/io.h>
#include <util/delay.h>	
#include <avr/interrupt.h>
#include "lib.h"

void allumerDEL();
void eteindreDEL();
void toggleDEL(); 
void toggleCouleur(); 
void couleurAmbre(); 