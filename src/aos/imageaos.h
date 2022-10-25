//
//
//

#ifndef UNTITLED_IMAGEAOS_H
#define UNTITLED_IMAGEAOS_H


#include <iostream>
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

    // Como dice la definicion de aos, un solo array
    Pixel arrayPixeles[MAX_SIZE];

    // Cronómetro
    chronometro time;

    // Argumentos pasados por main
    int numArgumentos;
    std::string image;
    std::string inDirectory;
    std::string outDirectory;
    std::string operation;

public:
    // Constructor & Destructor
    Imageaos(int num_args, std::string arg_1, std::string arg_2, std::string arg_3);

    // Funciones
    void executeProgram();
    void llenarPixeles(std::string filePath);
    void realizarOperacion(contenido_BMP imagen_BMP);

    // Operaciones
    void copiarImagen();
    void histograma(contenido_BMP imagen_BMP);
    void escalaGrises(contenido_BMP imagen_BMP);
    void difusionGaussiana(contenido_BMP imagen_BMP);
};


#endif //UNTITLED_IMAGEAOS_H
