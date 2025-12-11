%{
// --------------------------------------------------------
// Biblioteca de funções básicas
// --------------------------------------------------------


// Trava de múltiplas inclusões dessa biblioteca
#ifndef lib_default
#define lib_default


// [======================================================]
// [                     HEADER (.h)                      ]
// [======================================================]


#include <avr/io.h>     // Define os nomes dos registradores e os tipos de dados


typedef uint8_t byte;


#define bitSet(b,n)     (b=(1<<n)|b)
#define bitClear(b,n)   (b=(~(1<<n))&b)
#define bitToggle(b,n)  (b=(1<<n)^b)
#define bitRead(b,n)    (((1<<n)&b)>>n)


// Protótipos das funções
extern "C" { void delay_1_ms(); }
void delay(uint16_t ms);


#define TRUE 1
#define FALSE 0
#define LOW 0
#define HIGH 1
#define OUTPUT 1
#define INPUT 0
#define INPUT_PULLUP 2

// [======================================================]
// [                 IMPLEMENTAÇÃO (.cpp)                 ]
// [======================================================]


// Variáveis globais


volatile uint32_t milliss = 0;


// --------------------------------------------------------


void delay(uint16_t ms) {
    while(ms != 0) {
        delay_1_ms();
        ms--;
    }
}


// - Parte do HEADER (.h)
//     - includes de outros Headers            #include <avr/io.h>
//     - defines de novas definições           #define botao PORTB,5
//     - protótipos de funções                 void delay(uint16_t ms);
//     - declaração de classes                 class objeto_t : public {...}
//     - definição de novos tipos de dados     typedefs byte uint8_t
//     (nada disso vira código)


// - Parte da implementação (cpp)
//     - instanciação das variáveis            uint8_t valor = 5;
//     - instanciação de classes (objetos)     class objeto_t inst_objeto;
//     - implementação das funções             void setup() {...}
//     (isso vira código)


#endif  // lib_default

%}
