%{
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lib_default.h"    // Funções básicas (delay, bitSet, etc.)
#include "lib_pinMap_Mega.h" // Mapeamento de pinos
#include "lib_shield_MF.h"   // Shield Multifunções
#include "lib_timer_0.h"     // Timer 0 para temporização
#include "lib_ad.h"          // ADC para leitura do potenciômetro

// [======================================================]
// [                VARIÁVEIS GLOBAIS                     ]
// [======================================================]

#define CONFIGURACAO 0
#define MONITORAMENTO 1
#define ALERTA 2
#define ECONOMIA 3  // Novo estado de economia de energia


volatile uint8_t estado = CONFIGURACAO;
volatile uint8_t limite_temperatura = 25;
volatile uint8_t temperatura_atual = 0;
volatile uint32_t tempo_alerta_inicio = 0;

volatile uint8_t btnUp, btnDown, btnOk;
volatile uint8_t btnUp_last = 0, btnDown_last = 0, btnOk_last = 0;

// [======================================================]
// [                DECLARAÇÃO DE FUNÇÕES                 ]
// [======================================================]

void atualizarDisplay(uint8_t valor);
void lerBotoes();
void ativarAlerta();
void desativarAlerta();
void configurarLeds();
void piscarLedsAlerta();
void piscarDisplay();

// [======================================================]
// [                IMPLEMENTAÇÃO DAS FUNÇÕES             ]
// [======================================================]

void atualizarDisplay(uint8_t valor) {
    d7dig1 = (valor / 100) % 10;
    d7dig2 = (valor / 10) % 10;
    d7dig3 = (valor % 10);
}

void lerBotoes() {
    btnUp   = leituraBotao(2); // Alterado para S2 aumentar temperatura
    btnDown = leituraBotao(1); // Alterado para S1 diminuir temperatura
    btnOk   = leituraBotao(3);
}

void ativarAlerta() {
    buzzerOn();
}

void desativarAlerta() {
    buzzerOff();
}

void configurarLeds() {
    switch (estado) {
        case CONFIGURACAO:
            pinSet(LED4);
            pinSet(LED3);
            pinClear(LED2);
            pinClear(LED1);
            break;
        case MONITORAMENTO:
            pinSet(LED2);
            pinSet(LED1);
            pinClear(LED4);
            pinClear(LED3);
            break;
        case ALERTA:
            piscarLedsAlerta();
            break;
    }
}

void piscarLedsAlerta() {
    if ((milliss / 300) % 2 == 0) {
        pinSet(LED4);
        pinSet(LED3);
        pinSet(LED2);
        pinSet(LED1);
    } else {
        pinClear(LED4);
        pinClear(LED3);
        pinClear(LED2);
        pinClear(LED1);
    }
}

void piscarDisplay() {
    if ((milliss / 300) % 2 == 0) {
        atualizarDisplay(limite_temperatura);
    } else {
        d7dig1 = 16;
        d7dig2 = 16;
        d7dig3 = 16;
    }
}

// [======================================================]
// [                MÁQUINA DE ESTADOS                    ]
// [======================================================]

volatile uint32_t tempo_inativo = 0;  // Guarda o último tempo de interação

void maqEstados() {
    lerBotoes();
    configurarLeds();

    switch (estado) {
        case CONFIGURACAO:
        piscarDisplay();
            if (btnUp && !btnUp_last) { 
                if (limite_temperatura < 200) limite_temperatura++;
                tempo_inativo = milliss;  
            }
            if (btnDown && !btnDown_last) { 
                if (limite_temperatura > 0) limite_temperatura--;
                tempo_inativo = milliss;
            }
            if (btnOk && !btnOk_last) { 
                estado = MONITORAMENTO; 
                tempo_inativo = milliss;
            }
            btnUp_last = btnUp;
            btnDown_last = btnDown;
            btnOk_last = btnOk;
            break;

        case MONITORAMENTO:
            if (AD_endOfConversion() == 0) {
                AD_clearADIF();
                uint16_t result = ADCL | (ADCH << 8);
                temperatura_atual = (result * 200 + 512) / 1023;
                atualizarDisplay(temperatura_atual);
                AD_startOfConversion();
            }

            if (temperatura_atual > limite_temperatura) {
                estado = ALERTA;
                ativarAlerta();
                tempo_alerta_inicio = milliss;
            }

            if (btnOk && !btnOk_last) { 
                estado = CONFIGURACAO; 
                tempo_inativo = milliss;
            }
            btnOk_last = btnOk;

            // Se ninguém interagir por 10s, entra no modo ECONOMIA
            if (milliss - tempo_inativo > 10000) {
                estado = ECONOMIA;
            }
            break;

        case ALERTA:
            if (AD_endOfConversion() == 0) {
                AD_clearADIF();
                uint16_t result = ADCL | (ADCH << 8);
                temperatura_atual = (result * 200 + 512) / 1023;
                atualizarDisplay(temperatura_atual);
                d7dig4 = 17;
                AD_startOfConversion();
            }

            if ((milliss - tempo_alerta_inicio > 3000) && (temperatura_atual <= limite_temperatura)) {
                estado = MONITORAMENTO;
                desativarAlerta();
                tempo_inativo = milliss;  // Garante que o modo economia seja ativado apenas após interação
            }

            if (btnOk && !btnOk_last) {
                estado = CONFIGURACAO;
                desativarAlerta();
                tempo_inativo = milliss;
            }
            btnOk_last = btnOk;
            break;

            case ECONOMIA:
            // Garante que apenas o LED4 fique oscilando
            pinSet(LED1);
            pinSet(LED2);
            pinSet(LED3);
        
            // Apaga os displays
            d7dig1 = 16;
            d7dig2 = 16;
            d7dig3 = 16;
            d7dig4 = 16;
        
            // Pisca apenas o LED4 a cada 1000ms
            if ((milliss / 1000) % 2 == 0) {
                pinClear(LED4);  // Liga LED4
            } else {
                pinSet(LED4);    // Apaga LED4
            }
        
            // Continua a leitura do ADC no modo economia
            if (AD_endOfConversion() == 0) {
                AD_clearADIF();
                uint16_t result = ADCL | (ADCH << 8);
                temperatura_atual = (result * 200 + 512) / 1023;
                AD_startOfConversion();
            }
        
            // Se a temperatura ultrapassar o limite, vai para ALERTA
            if (temperatura_atual > limite_temperatura) {
                estado = ALERTA;
                ativarAlerta();
                d7dig4 = 17;
                tempo_alerta_inicio = milliss;
            }
        
            // Se alguém interagir, sai do modo economia e volta para CONFIGURAÇÃO
            if (btnUp || btnDown || btnOk) {
                estado = CONFIGURACAO;
                tempo_inativo = milliss;
                
                // Ajuste imediato no display ao sair do modo economia**
                d7dig1 = (limite_temperatura / 100) % 10;
                d7dig2 = (limite_temperatura / 10) % 10;
                d7dig3 = (limite_temperatura % 10);
                //d7dig4 = 17; 
            }
            break;
        
        
            default:
            // Retorna à configuração em caso de erro
            estado = CONFIGURACAO;
            temperatura_atual = 0;
            limite_temperatura = 25;
            tempo_inativo = milliss;
            desativarAlerta();
            atualizarDisplay(temperatura_atual);
            break;
    }
}


void setup() {
    cli();
    setup_shield_MF();
    setup_timer_0();
    setupConversorAD();
    atualizarDisplay(limite_temperatura);
    d7dig4 = 17;
    buzzerOff();
    sei();

}

void loop() {
    maqEstados();
}

ISR(TIMER0_OVF_vect) {
    milliss++;
    task_varredura_disp7();
}

%}
