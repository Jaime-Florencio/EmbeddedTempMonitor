%{
//  #include <Arduino.h>

#include "lib_default.h"
// #include "lib_pinMap_Mega.h"
// #include "lib_shield_MF.h"


// --------------------------------------------------------
// Módulos dos projetos

 #include "sensorTemp.cpp"


// --------------------------------------------------------

#ifndef Arduino_h
int main(void) {
    setup();
    while(1) { loop(); }
}
#endif

%}
