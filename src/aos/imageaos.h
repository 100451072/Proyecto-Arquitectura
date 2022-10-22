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
#include <filesystem>

using namespace std;

// Tamaño max de un array
int MAX_SIZE = 1000000;

// localizaciones del path
char origin[256];
char prox_location[256];

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

typedef struct BMP
{
    char B = 'B';            // Array de chars "BM"
    char M = 'M';            // Array de chars "BM"
    int sFile;               // Tamaño del fichero
    int reservado = 0;       //Espacio reservado
    int offsetImagen = 54;   //Inicio del contenido de los pixeles de la imagen
    int sCabecera = 40;      // Tamaño de la cabecera
    int anchuraInicial;             // Anchura de la imagen
    int alturaInicial;              // Altura de la imagen
    short nPlanos = 1;       // Numero de planos de la imagen
    short bitPorPixel = 24;  //Bits por pixeles de la imange
    int compresion = 0;      // Compresion de la imagen
    int sImagen;             // Tamaño total solo de la imagen (altura*anchura*3)
    int rX = 2835;           // Resolucion horizontal
    int rY = 2835;           // Resolucion vertical
    int sColor = 0;          // Tamaño de la tabla de color
    int colorImportante = 0; // Colores Importantes
    std::string infoImagen;   // Datos de la imange BMP
} BMP;


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
    Nodo arrayPixeles[MAX_SIZE];
    // Elementos comunes
    Common comun;

public:
    // Constructor & Destructor
    Imageaos(int num_args, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3);

    // Funciones
    void executeProgram();
    void llenarPixeles();
    void realizarOperacion();
    void difusionGaussiana()
};


#endif //UNTITLED_IMAGEAOS_H
