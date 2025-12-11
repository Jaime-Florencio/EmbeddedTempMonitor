%{
// --------------------------------------------------------
// Biblioteca de mapeamento de pinos para PORTAS
// Versão para Arduino MEGA
// --------------------------------------------------------


// [======================================================]
// [                     HEADER (.h)                      ]
// [======================================================]


#ifndef lib_pinMap_Mega
#define lib_pinMap_Mega


// Includes -----------------------------------------------


#include <avr/io.h>
#include "lib_default.h"


// Functions prototypes


void configPinInput(uint8_t pin);
void configPinInputPullup(uint8_t pin);
void configPinOutput(uint8_t pin);
void pinSet(uint8_t pin);
void pinClear(uint8_t pin);
void pinToggle(uint8_t pin);
uint8_t pinRead(uint8_t pin);


// defines, a more simplified form of pin functions


#define spin(x) pinSet(x)
#define cpin(x) pinClear(x)
#define tpin(x) pinToggle(x)
#define rpin(x) pinRead(x)


// mapping the pin number to its respective port


// [======================================================]
// [                 IMPLEMENTATION (.c)                  ]
// [======================================================]


// --------------------------------------------------------
// Global variables


// PORTA=0 B=1 C=2 D=3 E=4 F=5 G=6 K=7 L=8
enum pinPortMap_def { PortA, PortB, PortC, PortD, PortE, PortF, PortG, PortH, PortJ, PortK, PortL, NO_PORT };


const pinPortMap_def pinPortMap[] = {
    PortE, // 0 - PE0
    PortE, // 1 - PE1
    PortE, // 2 - PE4
    PortE, // 3 - PE5
    PortG, // 4 - PG5
    PortE, // 5 - PE3
    PortH, // 6 - PH3
    PortH, // 7 - PH4


    PortH, // 8 - PH5
    PortH, // 9 - PH6
    PortB, // 10 - PB4
    PortB, // 11 - PB5
    PortB, // 12 - PB6
    PortB, // 13 - PB7


    PortJ, // 14 - PJ1
    PortJ, // 15 - PJ0
    PortH, // 16 - PH1
    PortH, // 17 - PH0
    PortD, // 18 - PD3
    PortD, // 19 - PD2
    PortD, // 20 - PD1
    PortD, // 21 - PD0


    PortA, // 22 - PA0
    PortA, // 23 - PA1
    PortA, // 24 - PA2
    PortA, // 25 - PA3
    PortA, // 26 - PA4
    PortA, // 27 - PA5
    PortA, // 28 - PA6
    PortA, // 29 - PA7
    PortC, // 30 - PC7
    PortC, // 31 - PC6
    PortC, // 32 - PC5
    PortC, // 33 - PC4
    PortC, // 34 - PC3
    PortC, // 35 - PC2
    PortC, // 36 - PC1
    PortC, // 37 - PC0
    PortD, // 38 - PD7
    PortG, // 39 - PG2
    PortG, // 40 - PG1
    PortG, // 41 - PG0
    PortL, // 42 - PL7
    PortL, // 43 - PL6
    PortL, // 44 - PL5
    PortL, // 45 - PL4
    PortL, // 46 - PL3
    PortL, // 47 - PL2
    PortL, // 48 - PL1
    PortL, // 49 - PL0
    PortB, // 50 - PB3
    PortB, // 51 - PB2
    PortB, // 52 - PB1
    PortB, // 53 - PB0


    PortF, // ANALOG0,54 - PF0
    PortF, // ANALOG1,55 - PF1
    PortF, // ANALOG2,56 - PF2
    PortF, // ANALOG3,57 - PF3
    PortF, // ANALOG4,58 - PF4
    PortF, // ANALOG5,59 - PF5
    PortF, // ANALOG6,60 - PF6
    PortF, // ANALOG7,61 - PF7


    PortK, //  ANALOG8,62 - PK0
    PortK, //  ANALOG9,63 - PK1
    PortK, // ANALOG10,64 - PK2
    PortK, // ANALOG11,65 - PK3
    PortK, // ANALOG12,66 - PK4
    PortK, // ANALOG13,67 - PK5
    PortK, // ANALOG14,68 - PK6
    PortK, // ANALOG15,69 - PK7


    NO_PORT // 70 - Fake port name, for unconnected pins
};


// --------------------------------------------------------


#define ANALOG0 54
#define ANALOG1 55
#define ANALOG2 56
#define ANALOG3 57
#define ANALOG4 58
#define ANALOG5 59
#define ANALOG6 60
#define ANALOG7 61
#define ANALOG8 62
#define ANALOG9 63
#define ANALOG10 64
#define ANALOG11 65
#define ANALOG12 66
#define ANALOG13 67
#define ANALOG14 68
#define ANALOG15 69
#define NOTCONNECTED 70


// --------------------------------------------------------


const uint8_t pinBitMap[] = {
    0, // 0 - PE0
    1, // 1 - PE1
    4, // 2 - PE4
    5, // 3 - PE5
    5, // 4 - PG5
    3, // 5 - PE3
    3, // 6 - PH3
    4, // 7 - PH4


    5, // 8 - PH5
    6, // 9 - PH6
    4, // 10 - PB4
    5, // 11 - PB5
    6, // 12 - PB6
    7, // 13 - PB7


    1, // 14 - PJ1
    0, // 15 - PJ0
    1, // 16 - PH1
    0, // 17 - PH0
    3, // 18 - PD3
    2, // 19 - PD2
    1, // 20 - PD1
    0, // 21 - PD0


    0, // 22 - PA0
    1, // 23 - PA1
    2, // 24 - PA2
    3, // 25 - PA3
    4, // 26 - PA4
    5, // 27 - PA5
    6, // 28 - PA6
    7, // 29 - PA7
    7, // 30 - PC7
    6, // 31 - PC6
    5, // 32 - PC5
    4, // 33 - PC4
    3, // 34 - PC3
    2, // 35 - PC2
    1, // 36 - PC1
    0, // 37 - PC0
    7, // 38 - PD7
    2, // 39 - PG2
    1, // 40 - PG1
    0, // 41 - PG0
    7, // 42 - PL7
    6, // 43 - PL6
    5, // 44 - PL5
    4, // 45 - PL4
    3, // 46 - PL3
    2, // 47 - PL2
    1, // 48 - PL1
    0, // 49 - PL0
    3, // 50 - PB3
    2, // 51 - PB2
    1, // 52 - PB1
    0, // 53 - PB0


    0, // A0,54 - PF0
    1, // A1,55 - PF1
    2, // A2,56 - PF2
    3, // A3,57 - PF3
    4, // A4,58 - PF4
    5, // A5,59 - PF5
    6, // A6,60 - PF6
    7, // A7,61 - PF7


    0, //  A8,62 - PK0
    1, //  A9,63 - PK1
    2, // A10,64 - PK2
    3, // A11,65 - PK3
    4, // A12,66 - PK4
    5, // A13,67 - PK5
    6, // A14,68 - PK6
    7, // A15,69 - PK7


    0  // 70 - Fake pin number, for unconnected pins
};


// --------------------------------------------------------
// Functions


void configPinInput(uint8_t pin) {
    pinPortMap_def PP = pinPortMap[pin];
    uint8_t bt = pinBitMap[pin];
    switch(PP) {
        case PortA: bitClear(DDRA,bt); bitClear(PORTA,bt); break;
        case PortB: bitClear(DDRB,bt); bitClear(PORTB,bt); break;
        case PortC: bitClear(DDRC,bt); bitClear(PORTC,bt); break;
        case PortD: bitClear(DDRD,bt); bitClear(PORTD,bt); break;
        case PortE: bitClear(DDRE,bt); bitClear(PORTE,bt); break;
        case PortF: bitClear(DDRF,bt); bitClear(PORTF,bt); break;
        case PortG: bitClear(DDRG,bt); bitClear(PORTG,bt); break;
        case PortH: bitClear(DDRH,bt); bitClear(PORTH,bt); break;
        case PortJ: bitClear(DDRJ,bt); bitClear(PORTJ,bt); break;
        case PortK: bitClear(DDRK,bt); bitClear(PORTK,bt); break;
        default:    bitClear(DDRL,bt); bitClear(PORTL,bt); break;
    }
}


// --------------------------------------------------------


void configPinInputPullup(uint8_t pin) {
    pinPortMap_def PP = pinPortMap[pin];
    uint8_t bt = pinBitMap[pin];
    switch(PP) {
        case PortA: bitClear(DDRA,bt); bitSet(PORTA,bt); break;
        case PortB: bitClear(DDRB,bt); bitSet(PORTB,bt); break;
        case PortC: bitClear(DDRC,bt); bitSet(PORTC,bt); break;
        case PortD: bitClear(DDRD,bt); bitSet(PORTD,bt); break;
        case PortE: bitClear(DDRE,bt); bitSet(PORTE,bt); break;
        case PortF: bitClear(DDRF,bt); bitSet(PORTF,bt); break;
        case PortG: bitClear(DDRG,bt); bitSet(PORTG,bt); break;
        case PortH: bitClear(DDRH,bt); bitSet(PORTH,bt); break;
        case PortJ: bitClear(DDRJ,bt); bitSet(PORTJ,bt); break;
        case PortK: bitClear(DDRK,bt); bitSet(PORTK,bt); break;
        default:    bitClear(DDRL,bt); bitSet(PORTL,bt); break;
    }
}


// --------------------------------------------------------


void configPinOutput(uint8_t pin) {
    pinPortMap_def PP = pinPortMap[pin];
    uint8_t bt = pinBitMap[pin];
    switch(PP) {
        case PortA: bitSet(DDRA,bt); break;
        case PortB: bitSet(DDRB,bt); break;
        case PortC: bitSet(DDRC,bt); break;
        case PortD: bitSet(DDRD,bt); break;
        case PortE: bitSet(DDRE,bt); break;
        case PortF: bitSet(DDRF,bt); break;
        case PortG: bitSet(DDRG,bt); break;
        case PortH: bitSet(DDRH,bt); break;
        case PortJ: bitSet(DDRJ,bt); break;
        case PortK: bitSet(DDRK,bt); break;
        default:    bitSet(DDRL,bt); break;
    }
}


// --------------------------------------------------------


void pinSet(uint8_t pin) {
    pinPortMap_def PP = pinPortMap[pin];
    uint8_t bt = pinBitMap[pin];
    switch(PP) {
        case PortA: bitSet(PORTA,bt); break;
        case PortB: bitSet(PORTB,bt); break;
        case PortC: bitSet(PORTC,bt); break;
        case PortD: bitSet(PORTD,bt); break;
        case PortE: bitSet(PORTE,bt); break;
        case PortF: bitSet(PORTF,bt); break;
        case PortG: bitSet(PORTG,bt); break;
        case PortH: bitSet(PORTH,bt); break;
        case PortJ: bitSet(PORTJ,bt); break;
        case PortK: bitSet(PORTK,bt); break;
        default:    bitSet(PORTL,bt); break;
    }
}


// --------------------------------------------------------


void pinClear(uint8_t pin) {
    pinPortMap_def PP = pinPortMap[pin];
    uint8_t bt = pinBitMap[pin];
    switch(PP) {
        case PortA: bitClear(PORTA,bt); break;
        case PortB: bitClear(PORTB,bt); break;
        case PortC: bitClear(PORTC,bt); break;
        case PortD: bitClear(PORTD,bt); break;
        case PortE: bitClear(PORTE,bt); break;
        case PortF: bitClear(PORTF,bt); break;
        case PortG: bitClear(PORTG,bt); break;
        case PortH: bitClear(PORTH,bt); break;
        case PortJ: bitClear(PORTJ,bt); break;
        case PortK: bitClear(PORTK,bt); break;
        default:    bitClear(PORTL,bt); break;
    }
}


// --------------------------------------------------------


void pinToggle(uint8_t pin) {
    pinPortMap_def PP = pinPortMap[pin];
    uint8_t bt = pinBitMap[pin];
    switch(PP) {
        case PortA: bitToggle(PORTA,bt); break;
        case PortB: bitToggle(PORTB,bt); break;
        case PortC: bitToggle(PORTC,bt); break;
        case PortD: bitToggle(PORTD,bt); break;
        case PortE: bitToggle(PORTE,bt); break;
        case PortF: bitToggle(PORTF,bt); break;
        case PortG: bitToggle(PORTG,bt); break;
        case PortH: bitToggle(PORTH,bt); break;
        case PortJ: bitToggle(PORTJ,bt); break;
        case PortK: bitToggle(PORTK,bt); break;
        default:    bitToggle(PORTL,bt); break;
    }
}


// --------------------------------------------------------


uint8_t pinRead(uint8_t pin) {
    pinPortMap_def PP = pinPortMap[pin];
    uint8_t bt = pinBitMap[pin];
    switch(PP) {
        case PortA: return bitRead(PINA,bt); break;
        case PortB: return bitRead(PINB,bt); break;
        case PortC: return bitRead(PINC,bt); break;
        case PortD: return bitRead(PIND,bt); break;
        case PortE: return bitRead(PINE,bt); break;
        case PortF: return bitRead(PINF,bt); break;
        case PortG: return bitRead(PING,bt); break;
        case PortH: return bitRead(PINH,bt); break;
        case PortJ: return bitRead(PINJ,bt); break;
        case PortK: return bitRead(PINK,bt); break;
        default:    return bitRead(PINL,bt); break;
    }
}


// --------------------------------------------------------


#ifndef Arduino_h
void pinMode(uint8_t pin, uint8_t mode) {
    switch(mode){
        case INPUT: configPinInput(pin); break;
        case INPUT_PULLUP: configPinInputPullup(pin); break;
        case OUTPUT: configPinOutput(pin);
    }
}


void digitalWrite(uint8_t pin,uint8_t digital){
    switch(digital){
        case LOW: pinClear(pin); break;
        case HIGH: pinSet(pin);
    }
}
#endif // Arduino_h


// --------------------------------------------------------


#endif // end of lib_pinMap_Mega

%}
