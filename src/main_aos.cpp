//
// Práctica Procesamiento de Imagenes
//
// Participantes:
//      Asier Justo Turuelo 100451012
//      Pablo Vallspín Aranguren 100451072


#include <iostream>
#include <stdio.h>
#include "aos/imageaos.h"

int main(int argc, char* argv[]){


    Imageaos aosObject(argc, argv[0], argv[1], argv[2]);
    aosObject.executeProgram();

    return 0;
}
