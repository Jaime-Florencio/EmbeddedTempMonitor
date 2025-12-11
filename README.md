# TemperaturaGuard – Sistema de Monitoramento por Microcontroladores (Arduino Mega 2560)

## Resumo
Projeto desenvolvido como avaliação final da disciplina de Microcontroladores utilizando o Arduino Mega 2560 com o Shield Multifunções da Eletrogate. A solução aplica máquina de estados, leitura ADC configurada por registradores, Timer0 para temporização em tempo real, filtragem de ruído nos botões, multiplexação de displays 7 segmentos com o shift register 74HC595 e operação totalmente non-blocking (sem uso de `delay`). Todo o controle é realizado por escrita direta nos registradores do ATmega2560.

## Funcionalidades
- Configuração do limite de temperatura
- Monitoramento em tempo real
- Estado de alerta com buzzer e LEDs
- Modo economia de energia
- Interface com 3 botões e 4 displays 7 segmentos
- Operação totalmente non-blocking

## Hardware utilizado
- Arduino Mega 2560
- Shield Multifunções da Eletrogate
- Potenciômetro interno
- LEDs D1–D4
- Botões S1, S2, S3
- Buzzer
- Shift Register 74HC595

## Máquina de estados
```
CONFIGURAÇÃO → MONITORAMENTO → ALERTA → MONITORAMENTO
         ↘                                 ↗
           ↘----- ECONOMIA DE ENERGIA -----↗
```

## Como compilar
1. Instale o PlatformIO.
2. Abra o projeto e utilize o arquivo `platformio.ini`:
   ```ini
   [env:megaatmega2560]
   platform = atmelavr
   board = megaatmega2560
   framework = arduino

   debug_tool = simavr
   monitor_speed = 115200
   ```
3. Build: `Ctrl + Alt + B`
4. Upload: `Ctrl + Alt + U`

## Como o projeto funciona
- Timer0 incrementa `milliss` via interrupção
- Displays multiplexados a cada 5 ms
- ADC lido a cada ciclo
- Botões filtrados por tempo morto
- LEDs indicam o estado da máquina
- Buzzer ativado apenas em ALERTA

## Capturas de tela (placeholder)
- **Fotos do hardware (Adicionar depois)**
- **GIF da execução (Adicionar depois)**

## Estrutura do projeto
```
PROJECT_ROOT/
├── lib/
│   ├── lib_default.h
│   ├── lib_pinMap_Mega.h
│   ├── lib_shield_MF.h
│   ├── lib_timer_0.h
│   └── lib_ad.h
├── src/
│   └── main.cpp
├── platformio.ini
├── .gitignore
└── README.md
```

## Licença
Distribuído sob a licença MIT. Consulte o arquivo `LICENSE` para mais informações.
