//
//
//

#ifndef UNTITLED_PROGARGS_H
#define UNTITLED_PROGARGS_H


#include "progargs.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>

typedef struct contenido_BMP{
    // contenido del archivo bmp para usarlo en las lecturas NO SON TODOS SON LOS IMPORTANTES
    int tamano;
    int t_padding;
    int anchura;
    int altura;
    int datos_imagen;
    int numero_planos;
    int compresion;
    int t_punto;

} contenido_BMP;

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

// Funciones
bool comprobarArg(int num_args, std::string& argv_1, std::string& argv_2, std::string& argv_3);

contenido_BMP leerHeaderBMP(const std::string& filePath);

std::vector& leerArrayBMP(contenido_BMP);

#endif //UNTITLED_PROGARGS_H