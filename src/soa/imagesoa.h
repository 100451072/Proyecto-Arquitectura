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
#include <cmath>
#include <chrono>
#include <vector>
#include <fstream>
#include "common/progargs.h"
#include "common/aux_functions.h"

using namespace std;

// Tamaño max para formar un array
#define MAX_SIZE 1000000;

// variables no se si se pueden
//

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


// estructura que almacenará tres vectores para cada valor r, g, b
struct Pixeles {
    int arrayR[MAX_SIZE];
    int arrayG[MAX_SIZE];
    int arrayB[MAX_SIZE];
};

class Imagesoa {
private:
    // atributos
    Pixeles structPixels;

    chronometro time;

    // componentes comunes
    int numArgumentos;
    std::string image;
    std::string inDirectory;
    std::string outDirectory;
    std::string operation;

    // Ruta al archivo de trabajo actual
    std::string actualFile;

public:
    // constructor & destructor
    Imagesoa(int num_args, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3);

    // Funciones
    void executeProgram();
    void llenarPixeles();
    void realizarOperacion(contenido_BMP imagen_BMP));
    // Operaciones
    void copiarImagen(contenido_BMP imagen_BMP));
    void histograma(contenido_BMP imagen_BMP));
    void escalaGrises(contenido_BMP imagen_BMP));
    void difusionGaussiana(contenido_BMP imagen_BMP));
};


#endif //UNTITLED_IMAGESOA_H
