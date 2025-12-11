%{
--------------------------------------------------------
// Biblioteca ConversorAD
// --------------------------------------------------------


#include <avr/io.h>         // define os registradores do ATMega
#include "lib_default.h"    // delay, bitClear,Set,Toggle,Read
#include "lib_pinMap_Mega.h" // pinConfig, picSet/Clear

#define AD_startOfConversion() bitSet(ADCSRA,6)
#define AD_endOfConversion() bitRead(ADCSRA,6)
#define AD_clearADIF() bitSet(ADCSRA,4)

void setupConversorAD() {
    ADMUX = (0b1 << 6) |    // Voltage reference: 0=ARef ,1=Vcc interno, 3=1.1V interno
            (0b0 << 5) |    // Alinhamento: 0=direita, 1=esquerda
            (0b00000);      // Canal AD: 0,1,2,3,4,5 (Uno), 6,7,8,9,10,11,12,13,14,15 (Mega)
    ADCSRA = (0b1 << 7) |   // 0=AD desabilitado, 1=habilitado
             (0b0 << 5) |   // ADATE, Auto trigger: 0=no, 1=yes (continuous trigger)
             (0b0 << 3) |   // 0=AD interrupt disable, 1=enabled
             (0b101);       // Prescaler: 0=div 2, 1=div 2, 2=div 4, 3=div 8, 4=div 16, 5=div 32, 6=div 64, 7=div 128
    ADCSRB = (0b101);       // If ADATE=1, trigger mode: 0=Free running, 1=analog comparator........
    DIDR0 = (0b00000001);   // Disable digital buffer I/O on PORT C (write 1 to disble)
    configPinInput(ANALOG0);
    bitClear(PRR0,PRADC);   // liga a energia do módulo do conversor AD
}
%}
