#ifndef UNTITLED_IMAGESOA_H
#define UNTITLED_IMAGESOA_H

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
struct Pixeles
{
    std::vector<int> arrayR;
    std::vector<int> arrayG;
    std::vector<int> arrayB;
};

class Imagesoa {
private:
    // Ruta al archivo sobre el que estamos trabajando en el momento
    std::string fileName, inDir, outDir;

    // Header del archivo
    unsigned char header[HEADER_SIZE]{};

    Pixeles structPixeles;

    int width{}, height{}, padding{};

public:
    // Constructor & Destructor
    Imagesoa(const std::string& fileName, const std::string& inDir, const std::string& outDir);

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

#endif //UNTITLED_IMAGESOA_H
