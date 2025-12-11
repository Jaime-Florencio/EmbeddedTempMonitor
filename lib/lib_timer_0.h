%{
//  ------------------------------------------------------
// Biblioteca do Timer 0
// ------------------------------------------------------


// [====================================================]
// [                    HEADER (.h)                     ]
// [====================================================]


#ifndef lib_timer_0
#define lib_timer_0


#include <avr/io.h>         // nomes dos registradores
#include <avr/interrupt.h>  // interrupções (se necessário)
#include "lib_default.h"    // bitSet,Clear etc


#define T0_OV_Flag_clear()  bitSet(TIFR0,TOV0);
#define T0_OV_INT_enable()  bitSet(TIMSK0,TOIE0);


// WGM waveform generator mode:
#define T0_WGM_mode 0 // 0=Normal , 1=PWM phase correct 0xFF, 2= CTC OCR0A, 3=Fast PWM 0xFF, 5=PWM phase correct OCR0A, 7=Fast PWM OCR0A


// [====================================================]
// [               IMPLEMENTATION (.cpp)                ]
// [====================================================]


// Datasheet sec 15.9, pages 113-118
void setup_timer_0() {
    TCCR0A = (0b00 << 6) |  // Compare match A mode: 0=normal, 1=Toggle OC0A, 2=Clear OC0A, 3=Set OC0A
             (0b00 << 4) |  // Compare match B mode
             // (0b00);        // WGM bits 1..0: waveform mode bits 1..0: 0=Normal , 1=PWM phase correct 0xFF, 2= CTC OCR0A, 3=Fast PWM 0xFF, 1=PWM phase correct OCR0A, 3=Fast PWM OCR0A
             (T0_WGM_mode&0b11); // <-- prefer this definition
    TCCR0B = (0b0 << 7) |   // Force A
             (0b0 << 6) |   // Force B
             // (0b0 << 3) |   // WGM bit 2: waveform mode bit 2: 0=Normal , 0=PWM phase correct 0xFF, 0=CTC OCR0A, 0=Fast PWM 0xFF, 1=PWM phase correct OCR0A, 1=Fast PWM OCR0A
             ((T0_WGM_mode&0b100)<<1) | // <-- prefer this definition
             (0b011);       // Prescaler: 0=no clock, 1=div 1, 2=div 8, 3=div 64, 4=div 256, 5=div 1024, 6=external borda descida, 7=external borda subida
    TIMSK0 = (0b0 << 2) |   // CMP0B interrupt enable
             (0b0 << 1) |   // CMP0A interrupt enable
             (0b01);         // Overflow interrupt enable
    TIFR0 =  (0b1 << 2) |   // clear CMP0B event flag
             (0b1 << 1) |   // clear CMP0A event flag
             (0b1);         // clear Overflow event flag
    bitClear(PRR0,PRTIM0);   // liga a energia do Timer 0
}


#endif // finaliza lib_timer_0

%}
