/********************************************************
 * Fichier : transmissionUART.h
 * Auteur : Kevin Clapperton 
 * Date : 2 decembre 2018 
 * Mise à jour : - 
 * Description : Les fonctions pour comminuquer avec un ordinateur qui a serieViaUSB installer 
 *              et les fonctions pour afficher les murs sur l'ordi 
 ********************************************************/ 
#include "transmissionUART.h"
#include "delFuncs.h"
#include <stdint.h>


/***********************************************
 * Fonction : initialisationUART 
 * IN : void 
 * OUT : void 
 * Description : Initialise les registre
 *               nécéssaire pour communiquer 
 *               avec un ordinateur 
***********************************************/

void initialisationUART(void)
{

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premier registres pour vous éviter des complications

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la reception et la transmission par le UART0

    UCSR0A |= 0;

    UCSR0B |= _BV(TXEN0) | _BV(RXEN0);

    // Format des trames: 8 bits, 1 stop bits, none parity

    UCSR0C |= 0x05;
}

/***********************************************
 * Fonction : transmissionUART 
 * IN : (unsigned char) donnee
 * OUT : void 
 * Description : Envoie un caractère par UART 
***********************************************/

void transmissionUART (unsigned char donnee ) 
{

    /*Wait for empty transmit buffer*/
    while( !( UCSR0A & (1<<UDRE0)) );

    /* Put data into buffer, sends the data*/
    UDR0 = donnee;

}

/***********************************************
 * Fonction : transmissionMur 
 * IN : (int *) murG 
 *      (int *) murD
 * OUT : void 
 * Description : Afficher les mur à l'aide d'un 
 *               tableau de int de taille 96 
 *               La fonction clignote une led aussi. 
***********************************************/
bool transmissionMur (unsigned int * murG, unsigned int * murD, unsigned int nombreMesures)
{
    unsigned int nombreEspaceG = 0; 
    unsigned int nombreACG = 0; 
    unsigned int nombreEspaceD = 0; 
    unsigned int nombreACD = 0; 

    double jump = 0; 
    double index = nombreMesures;  

    //Savoir de combien il doit sauter pour prendre seulement 96 valeur 
    jump = ((double)nombreMesures)/96.0; 

    for( int i = 0; i < 96; i++) 
    {
        nombreEspaceG = murG[(unsigned int)index]; 

        if(nombreEspaceG > 95) nombreEspaceG = 95; 

        nombreACG = 95 - nombreEspaceG; 
        for(unsigned int j = 0; j < nombreACG && j < 95; j++) transmissionUART ('@');
        for(unsigned int j = 0; j < nombreEspaceG && j < 95; j++) transmissionUART(' '); 

        transmissionUART('|'); 

        toggleDEL(); 

        transmissionUART('|'); 

        nombreEspaceD = murD[(unsigned int)index]; 
        
        if(nombreEspaceD > 95) nombreEspaceD = 95; 
        
        nombreACD = 95 - nombreEspaceD; 
        for(unsigned int j = 0; j < nombreEspaceD && j < 95; j++) transmissionUART(' '); 
        for(unsigned int j = 0; j < nombreACD && j < 95; j++) transmissionUART('@'); 

        toggleDEL();  
        index -= jump; 
        if(index < 0) index = 0; 
    }
    return true;
}

/*******************************************************************
 * Fonction : trollUART 
 * IN : void 
 * OUT : void 
 * Description : Montre un exemple de mur avec les tableaux fait 
 *               manuellement. 
 *               La fonction clignote une led aussi. 
*******************************************************************/

bool trollUART(void) 
{
    int murG[96] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, /*mur droit de 16*/
    23, 25, 28, 30, 33, 35, 38, 40, 38, 35, 33, 30, 28, 25, 23, 20,  //pic ext de 16
    20, 20, 20, 20, 20, 20, 20, 20, // mur droit de 8 
    18, 15, 13, 10, 8, 5, 3, 0, 3, 5, 8, 10, 13, 15, 18, 20, //pic int de 16
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20};  //mur droit de 40
    int murD[96] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3}; // 4 pic
    
    unsigned int nombreEspaceG = 0; 
    unsigned int nombreACG = 0; 
    unsigned int nombreEspaceD = 0; 
    unsigned int nombreACD = 0; 

    for( int i = 0; i < 96; i++) 
    {
        nombreEspaceG = 2 * murG[i]; 
        nombreACG = 95 - nombreEspaceG; 
        for(unsigned int j = 0; j < nombreACG; j++) transmissionUART ('@');
        for(unsigned int j = 0; j < nombreEspaceG; j++) transmissionUART(' '); 

        transmissionUART('|'); 

        toggleDEL(); 

        transmissionUART('|'); 

        nombreEspaceD = 2 * murD[i]; 
        nombreACD = 95 - nombreEspaceD; 
        for(unsigned int j = 0; j < nombreEspaceD; j++) transmissionUART(' '); 
        for(unsigned int j = 0; j < nombreACD; j++) transmissionUART('@'); 

        toggleDEL();  
    } 
    return true; 
}

