/********************************************************
 * Fichier : transmissionUART.h
 * Auteur : Kevin Clapperton 
 * Date : 2 decembre 2018 
 * Mise à jour : - 
 * Description : Les fonctions pour comminuquer avec un ordinateur qui a serieViaUSB installer 
 *              et les fonctions pour afficher les murs sur l'ordi 
 ********************************************************/ 
#include <stdint.h>
#include <avr/io.h>

#ifndef TRANSMISSIONMUR_H
#define TRANSMISSIONMUR_H

void initialisationUART (void); 
void transmissionUART (unsigned char donnee); 

bool transmissionMur (unsigned int * murG, unsigned int * murD, unsigned int nombreMesures); 

bool trollUART(void); 

#endif 


