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

typedef struct contenido_BMP {
    // contenido del archivo bmp para usarlo en las lecturas NO SON TODOS SON LOS IMPORTANTES
    // Primer header
    unsigned int tamano;             // Tamño archivo (4B) (offset 2B) (ojo que hay dos headers, de info, y el siguiente de bits)
    unsigned int dir_datos_imagen;   // Start pixeles (4B) (offset 10)
    // Segundo header
    unsigned anchura;               // Anchura del bit map (2B) (offset 18B)
    unsigned altura;                // Altura del bit map (2B) (offset 20B)
    unsigned int numero_planos;     // (2B) (offset 22B) debe ser uno
    unsigned int pix_por_bit        // (2B) (offset 24)
    int compresion;
    int t_punto;
    int t_padding;

} contenido_BMP;

// Estructura que nos permite medir el tiempo
typedef struct chronometro {
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