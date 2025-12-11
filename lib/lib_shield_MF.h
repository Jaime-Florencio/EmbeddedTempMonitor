%{
// --------------------------------------------------------
// Biblioteca de funções do shield multifunções
// --------------------------------------------------------


// Trava de múltiplas inclusões dessa biblioteca
#ifndef lib_shield_MF
#define lib_shield_MF


// [======================================================]
// [                      HEADER (.h)                     ]
// [======================================================]


#include <avr/io.h>         // define os registradores do ATMega
#include "lib_default.h"    // define delay, bitSet/Clear/Toggle/Read
#include "lib_pinMap_Mega.h" // mapeia número do pino para PORTA


#define LED1 10
#define LED2 11
#define LED3 12
#define LED4 13
#define SW1 ANALOG1
#define SW2 ANALOG2
#define SW3 ANALOG3
#define SDI   8
#define SHCLK 7
#define LTCLK 4
#define POTENCIOMETRO ANALOG0
#define BUZZER 3  // <-------- Acrescentar


#define buzzerOn()  pinClear(BUZZER)  // <------ Acrescentar
#define buzzerOff() pinSet(BUZZER)    // <------ Acrescentar

// [======================================================]
// [                 IMPLEMENTATION (.cpp)                ]
// [======================================================]


void setup_shield_MF() {
    // DDRB = 0b00111100;  // define bits 5..2 da PORTA B como saídas (onde estão conectados os LEDs)
    // DDRC = 0b00000000;  // define bits 3..1 da PORTA C como entradas (botões)
    configPinOutput(LED1);
    configPinOutput(LED2);
    configPinOutput(LED3);
    configPinOutput(LED4);
    configPinInputPullup(SW1);
    configPinInputPullup(SW2);
    configPinInputPullup(SW3);
    configPinOutput(SDI);
    configPinOutput(SHCLK);
    configPinOutput(LTCLK);
    configPinOutput(BUZZER);
}


// --------------------------------------------------------
// Leitura dos botões 0, 1 e 2 com filtragem de ruído


volatile uint8_t counterTempoMorto = 0;


// #define tempoMorto() delay(10)               // usando delay
// #define tempoMorto() counterTempoMorto=10    // usando contador autoregressivo
#define tempoMorto() fim=milliss+10             // usando delta milliss


uint8_t leituraBotao(uint8_t numBotao) {
    volatile static uint32_t fim = {0};
    volatile static uint8_t bta[] = { 0, 0, 0 };
    volatile static uint8_t bt[3];
    volatile static uint8_t numPino[] = { SW1, SW2, SW3 };
    numBotao--;
    bt[numBotao] = pinRead(numPino[numBotao]);      // Lê um dos botões 0, 1 ou 2
    // Se houver tempo morto ativo, valor é diferente de zero: não pode ler botão
    // ----- forma 1: usando contador autoregressivo counterTempoMorto
    // if( counterTempoMorto==0 ) {  // tempo morto está inativo?
    // ----- forma 2: usando delta milliss
    if( milliss >= fim ) {
        bt[numBotao] = pinRead(numPino[numBotao]);  // leitura do botão
        if( bt[numBotao] != bta[numBotao] ) {       // houve alteração? (borda)
            if( bta[numBotao]==1 ) {
                bta[numBotao]=0;
                tempoMorto();
                return 1;       // na borda de descida, retorna 1
            }
            else {
                bta[numBotao]=1;
                tempoMorto();
            }
        }
    } //<---------
    return 0;
}


// -------------------------------------------------------
// Funções do módulo de displays de 7 segmentos


// --------------------------------------------------------


uint8_t decod7seg[] = {
    0b00000011, // 0
    0b10011111, // 1
    0b00100101, // 2
    0b00001101, // 3
    0b10011001, // 4
    0b01001001, // 5
    0b01000001, // 6
    0b00011111, // 7
    0b00000001, // 8
    0b00001001, // 9
    0b00010001, // A
    0b11000001, // b
    0b01100011, // C
    0b10000101, // d
    0b01100001, // E
    0b01110001, // F
    0b11111111,  // 16 Segmentos Apagados (leds apagados)
    0b00111001 // 17
};


#define display1ligado 0b10000000
#define display2ligado 0b01000000
#define display3ligado 0b00100000
#define display4ligado 0b00010000


volatile uint8_t d7dig1=0, d7dig2=0, d7dig3=0, d7dig4=0;


void write595(uint8_t disp, uint8_t val) {
    // imagem dos segmentos
    uint8_t imagem = decod7seg[val];
    for (uint8_t i=0; i<8; i++) {
        if (imagem & 1) pinSet(SDI);
        else            pinClear(SDI);
        pinSet(SHCLK);      // pulso em SHCLK
        pinClear(SHCLK);
        imagem >>= 1;       // shift à esquerda
    }


    // imagem dos display ligado/desligado
    imagem = disp;
    for (uint8_t i=0; i<8; i++) {
        if (imagem & 1) pinSet(SDI);
        else            pinClear(SDI);
        pinSet(SHCLK);      // pulso em SHCLK
        pinClear(SHCLK);
        imagem >>= 1;       // shift à esquerda
    }


    // atualiza a saída
    pinSet(LTCLK);
    pinClear(LTCLK);
}


// -------------------------------------------------------
// task que faz varredura a cada 50 Hz (5 ms)
// vamos usar delta milliss
// lembrara que essa task precisa ser chamada de dentro da interrupção


volatile uint8_t qualDisplay = 1;

// 5 -> para 50hz e 20 -> para 200hz
void task_varredura_disp7() {
    volatile static uint32_t fim = {0};
    if( milliss >= fim ) {
        fim = milliss+5;    // fixa fim 5ms no futuro 5
        // trocaDisplay
        switch(qualDisplay) {
            case 1: // desliga display 1 e liga display 2
                    write595(display2ligado,d7dig2);
                    qualDisplay = 2;
                    break;
            case 2: // desliga display 2 e liga display 3
                    write595(display3ligado,d7dig3);
                    qualDisplay = 3;
                    break;
            case 3: // desliga display 3 e liga display 4
                    write595(display4ligado,d7dig4);
                    qualDisplay = 4;
                    break;
            default: // desliga display 4 e liga display 1
                    write595(display1ligado,d7dig1);
                    qualDisplay = 1;
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------

// -------------------------------------------------------
// -------------------------------------------------------


#endif  // lib_shield_MF
%}
