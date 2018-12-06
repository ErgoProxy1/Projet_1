/*************************************************
* Fichier : lcd.cpp 
* Auteur : Kevin Clapperton 
* Date : 23 novembre 2018 
* Mise à jour : - 
* Description : Fonctions pour écrire sur le LCD 
*************************************************/ 
#include "lcd.h"
#include <util/delay.h>

//Création de l'objet pour le lcd

LCM disp(&DDRC, &PORTC);

/************************************************
* Fonction : afficherNom 
* IN : void 
* OUT : void 
* Description : Afficher le nom du robot sur le LCD 
************************************************/
void afficherNom(void) 
{
    disp.write("Mecha Zero Sion"); 
}

/************************************************
* Fonction : afficherLongueurMur
* IN : - (int) g est la longueur total du mur de gauche 
    -(int) d est la longueur total du mur de droite 
* OUT : void 
* Description : Afficher la longueur des deux murs 
************************************************/
void afficherLongueurMur(unsigned int g, unsigned int d) 
{
    disp.write("GAUCHE:"); 
	disp << g; 
	disp << " cm";  
	
	disp.write("DROITE:", LCM_FW_HALF_CH, false); 
	disp << d; 
	disp << " cm"; 
}

/************************************************
* Fonction : clearLCD
* IN : void
* OUT : void 
* Description : Efface ce qui est sur l'écran LCD
************************************************/

void clearLCD(void) 
{ 
    disp.clear(); 
}

/************************************************
* Fonction : troll
* IN : toute 
* OUT : de la *****
* Description : lol
************************************************/
void troll(void) 
{
    /*Bonne lecture, lol*/disp.write("Mecha Zero Sion"); _delay_ms(3000); disp.write("Nesquick", LCM_FW_HALF_CH, false); _delay_ms(33); disp << "veep"; _delay_ms(33); disp << "veep"; _delay_ms(33); disp.clear(); 
}
