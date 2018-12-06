/******************************************************
 * Fichier : main.cpp
 * Auteur : Kevin Clapperton 
 * Date : 28 novembre 2018
 * Mise à jour : --
 * Description : Test qui mesure la longueur de mur virtuel 
 ******************************************************/

#include "distance.h"
#include "lcd.h"
#include <util/delay.h>

using namespace std; 

uint8_t murG[150] = {1, 2, 3, 4, 4, 4, 4, 3, 2, 1}; 
uint8_t murD[150] = {4, 3, 2, 1, 1, 1, 1, 2, 3, 4}; 

int main() 
{ 
    unsigned int nombreElement = 10; 

    int mesureGauche = calculerLongeur(murG, 10, nombreElement); 

    int mesureDroite = calculerLongeur(murD, 10, nombreElement); 

    afficherLongueurMur(mesureGauche , mesureDroite);  
}