//
// Práctica Procesamiento de Imagenes
//
// Participantes:
//      Asier Justo Turuelo 100451012
//      Pablo Vallspín Aranguren 100451072
//      Alvaro Buj Mancha 100406530


#include "soa/imagesoa.h"

int main(int argc, char* argv[]){

    Imagesoa soaObject(argc, argv[0], argv[1], argv[2]);
    soaObject.executeProgram();

    return 0;
}