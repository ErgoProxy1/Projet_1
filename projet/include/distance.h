#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include "can.h"

using namespace std;

unsigned int DistanceEnCm(uint16_t distance);
unsigned int calculerLongueur(unsigned int* tableau, double distanceTrajet, unsigned int size);
