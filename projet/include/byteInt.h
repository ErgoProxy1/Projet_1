#include <avr/io.h>
#include <avr/delay.h>

using namespace std;

const uint8_t dbt = 0x01, att = 0x02, dal = 0x44, det = 0x45, sgo = 0x48,
sar = 0x09, marleft = 0x60, marright = 0x61, mav = 0x62, mre = 0x63, trd = 0x64,
trg = 0x67, dbc = 0xC0, fbc = 0xC1, fin = 0xFF;
