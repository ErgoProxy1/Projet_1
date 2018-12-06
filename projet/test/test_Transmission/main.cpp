#include <avr/io.h>
#include "lib.h"
#include "transmissionUART.h"
#include "sonorite.h" 
#include "delFuncs.h"
#include <avr/interrupt.h>

using namespace std;

volatile bool doitAfficher = false;

ISR(INT0_vect) 
{
    _delay_ms(10); 
    if((PIND & 0x04) == 0x04) 
    {
        doitAfficher = true; 
    }
}

int main()
{
    initialisationUART(); 
    initialisationPorts(0x00, 0xff, 0x00, 0x00); 

    //Tableau de test 

    unsigned int murG[96] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, //mur droit de 16
    23, 25, 28, 30, 33, 35, 38, 40, 38, 35, 33, 30, 28, 25, 23, 20,  //pic ext de 16
    20, 20, 20, 20, 20, 20, 20, 20, // mur droit de 8 
    18, 15, 13, 10, 8, 5, 3, 0, 3, 5, 8, 10, 13, 15, 18, 20, //pic int de 16
    20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20};  //mur droit de 40
    unsigned int murD[96] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3}; // 4 pic 

    initialisationINT0(); 

    while (1) 
    {
        if(doitAfficher)
        {
            transmissionMur(murG, murD); 
            dank(); 
            doitAfficher = false; 
        }
    }

    return 0; 
}





