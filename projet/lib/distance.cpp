#include "../include/distance.h"
#include <math.h>

// Formule pour convertir le signal en cm
unsigned int DistanceEnCm(uint16_t distance) {
	double temp = 200.3775040589502 - 2.2657665648980 * distance
		+ 0.0116395328796 * distance * distance - 0.0000299194195 * distance * distance * distance
		+ 0.0000000374087 * distance * distance * distance * distance 
		- 0.0000000000181 * distance * distance * distance * distance * distance;
	return (unsigned int)(temp + 0.5);
}

//Utilisation de pythagore pour calculer la longeur du mur
unsigned int calculerLongueur(unsigned int* tableau, double distanceTrajet, unsigned int size){
	double temp = 0;
	for (unsigned int i = 1; i <= size; i+=3){ // i = 1 pour eviter de sortir du array space
		temp += sqrt(((tableau[i]-tableau[i-1])*(tableau[i]-tableau[i-1])) + ((distanceTrajet/size)*(distanceTrajet/size))); //Pythagore
	}
	return (unsigned int)(temp + 0.5);
}