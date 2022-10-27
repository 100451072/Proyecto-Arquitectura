//
//
//

#ifndef UNTITLED_IMAGEAOS_H
#define UNTITLED_IMAGEAOS_H


#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <utility>
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
    Pixel arrayPixeles[MAX_SIZE]{};

    // Cronómetro
    chronometro time{};

    // Argumentos pasados por main
    int numArgumentos;
    std::string image;
    std::string inDirectory;
    std::string outDirectory;
    std::string operation;

    // Ruta al archivo sobre el que estamos trabajando en el momneto
    std::string actualFile;

public:
    // Constructor & Destructor
    Imageaos(int num_args, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3);

    // Funciones
    void executeProgram();
    contenido_BMP llenarPixeles(std::vector<BYTE>& archivo_BMP);
    void realizarOperacion(contenido_BMP imagen_BMP, std::vector<BYTE>& arhcivo_BMP);

    // Operaciones
    void copiarImagen(contenido_BMP imagen_BMP, const std::vector<BYTE>& archivo_BMP);
    void histograma(contenido_BMP imagen_BMP);
    void escalaGrises(contenido_BMP imagen_BMP, std::vector<BYTE>& arraY_BMP));
    void difusionGaussiana(contenido_BMP imagen_BMP, std::vector<BYTE>& arraY_BMP);
};

#endif //UNTITLED_IMAGEAOS_H
