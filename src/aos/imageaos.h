#ifndef UNTITLED_IMAGEAOS_H
#define UNTITLED_IMAGEAOS_H

#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include "../common/progargs.h"
#include "../common/aux_functions.h"
#include <filesystem>
#include <fstream>


// Tamaño del header
#define HEADER_SIZE 54

#define WEIGHT 273


// Estructura que almacenara tres enteros por pixel (R, G, B)
struct Pixel
{
    int Red;
    int Green;
    int Blue;
};

class Imageaos {
private:
    // Ruta al archivo sobre el que estamos trabajando en el momento
    std::string fileName, inDir, outDir;

    // Header del archivo
    unsigned char header[HEADER_SIZE]{};

    // Como dice la definición de aos, un solo array
    std::vector<Pixel> arrayPixeles;

    int width{}, height{}, padding{};

public:
    // Constructor & Destructor
    Imageaos(const std::string& fileName, const std::string& inDir, const std::string& outDir);

    // Funciones

    void realizarOperacion(const std::string& operation);
    void guardar();
    bool checkHeader();


    // Operaciones
    void copiarImagen();
    void histograma();
    void escalaGrises();
    void difusionGaussiana();
};

#endif //UNTITLED_IMAGEAOS_H
