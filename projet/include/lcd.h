/*************************************************
* Fichier : lcd.h 
* Auteur : Kevin Clapperton 
* Date : 23 novembre 2018 
* Mise à jour : - 
* Description : Fonctions pour écrire sur le LCD 
*************************************************/ 
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

#ifndef LCD_H
#define LCD_H 

//Création de l'objet pour le lcd

extern LCM disp; 

void afficherNom(void); 
void afficherLongueurMur(unsigned int g, unsigned int d); 
void clearLCD(void); 
void troll(void); 

#endif
