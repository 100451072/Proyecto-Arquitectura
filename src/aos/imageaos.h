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
#include <cmath>
#include <chrono>
#include "progargs.h"

using namespace std;

// Tamaño max de un array
int MAX_SIZE = 1000000;

// localizaciones del path
char origin[256];
char prox_location[256];

// Estructura que nos permite medir el tiempo
typedef struct chronometro
{
    int loadTime;
    int gaussTime;
    int histoTime;
    int monoTime;
    int copyTime;
    int storeTime;
    int total;

} chronometro;

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
    // Elementos comunes
    Common comun;

public:
    // Constructor & Destructor
    Imageaos(int num_args, const string& arg_1, const string& arg_2, const string& arg_3);

    // Funciones
    void executeProgram();
    void llenarPixeles();
    void realizarOperacion();
};


#endif //UNTITLED_IMAGEAOS_H
