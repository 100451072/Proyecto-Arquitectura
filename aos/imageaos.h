//
//
//

#ifndef UNTITLED_IMAGEAOS_H
#define UNTITLED_IMAGEAOS_H


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include "progargs.h"

using namespace std;

// Tamaño max de un array
int MAX_SIZE = 1000000;

// Structura que almacenara tres enteros por pixel (R, G, B)
struct Nodo
{
    int Red;
    int Green;
    int Blue;
};

class Imageaos {
private:
    // Atributos
    // Como dice la definicion de aos, un solo array
    Nodo arrayPixeles[MAX_SIZE];
    // Ultima posición no vacia
    int lastPos;
    // Elementos comunes
    Common comun;

public:
    // Constructor & Destructor
    Imageaos(int num_args, String arg_1, String arg_2, String arg_3);

    // Funciones
    void executeProgram();
    void llenarPixeles();
    void realizarOperacion();
    void addPixel(int R, int G, int B);

};


#endif //UNTITLED_IMAGEAOS_H
