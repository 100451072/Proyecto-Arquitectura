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
#include "common/progargs.h"
#include "common/aux_functions.h"
#include <filesystem>
#include <fstream>

// Tamaño max de un array
#define MAX_SIZE 1000000


// matriz y peso gauss
int mGauss[5][5] = {{1, 4, 7, 4, 1},
                    {4, 16, 26, 16, 4},
                    {7, 26, 41, 26, 7},
                    {4, 16, 26, 16, 4},
                    {1, 4, 7, 4, 1}};
int w = 273;

//
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
struct Pixel
{
    int Red;
    int Green;
    int Blue;
};


class Imageaos {
private:
    // Atributos
    // Como dice la definicion de aos, un solo array
    Pixel arrayPixeles[MAX_SIZE];
    // Elementos comunes
    Common comun;

public:
    // Constructor & Destructor
    Imageaos(int num_args, const std::string arg_1, const std::string arg_2, const std::string arg_3);

    // Funciones
    void executeProgram();
    void llenarPixeles();
    void realizarOperacion();
    // Operaciones
    void copiarImagen();
    void histograma();
    void escalaGrises();
    void difusionGaussiana();
};


#endif //UNTITLED_IMAGEAOS_H
