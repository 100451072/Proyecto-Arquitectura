//
//
//

#ifndef UNTITLED_IMAGESOA_H
#define UNTITLED_IMAGESOA_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include "progargs.h"

using namespace std;

// Tamaño max para formar un array
int MAX_SIZE = 1000000;

// Estructura que almacenará tres vectores para cada valor R, G, B
struct Nodes {
    int arrayR[MAX_SIZE];
    int arrayG[MAX_SIZE];
    int arrayB[MAX_SIZE];
};

class Imagesoa {
private:
    // Atributos
    Nodes structurePixels;
    // Ultima posición no vacia
    int lastPos;
    // Componentes comunes
    Common comun;

public:
    // Constructor & Destructor
    Imagesoa(int num_args, String arg_1, String arg_2, String arg_3);

    // Funciones
    void executeProgram();
    void llenarPixeles();
    void realizarOperacion();
    void addPixel(int R, int G, int B);
};


#endif //UNTITLED_IMAGESOA_H
