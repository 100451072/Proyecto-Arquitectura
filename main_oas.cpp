//
// Práctica Procesamiento de Imagenes
//
// Participantes:
//      Asier Justo Turuelo 100451012
//      Pablo Vallspín Aranguren 100451072


#include <iostream>
#include <stdio.h>
#include "common/common.h"
#include "imageaos.h"

int main(int argc, char *argv[]){

    // El primer argumento sera 0 para soa y 1 para aos
    Common aosObject(1, argc, argv[0], argv[1], argv[2]);

    return 0;
}
