//
//
//

#ifndef UNTITLED_PROGARGS_H
#define UNTITLED_PROGARGS_H

/*
 *  Descripcion de esta parte en la memoria:
 *  La aplicacion leera todos los archivos del directorio de
 *  entrada, aplicará la transformaciones correspondientes y
 *  escribirán los archivos correspondientes con el mismo nombre
 *  en el dir de salida
 *
 *  Comprobar que el numero de parametros es tres
 *
 *  Si el tercer argumento no toma el valor adecuado (copy,
 *  histo, mono, gauss), se presentará un mensaje de error y se terminará
 *
 *  Si el dir de entrada no existe o no puede abrirse, se presentará un mensaje
 *  de error y se terminará
 *
 *  Si el directorio de salida no existe, se presentará un mansaje de error y
 *  se termina
 *
 *  En cualquier otro caso, se procesarán todos los archivos del dir de entrada y se
 *  dejarán los resultados en el dir de salida. Para cada archivo
 */

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


// Funciones
bool comprobarArg(int num_args, std::string& argv_1, std::string& argv_2, std::string& argv_3);
contenido_BMP leerHeaderBMP(std::string filePath);
int* leerArrayBMP(contenido_BMP);
// Operaciones de la aplicación
difusionGaussiana(unsigned char *inputPixels, int anchuraInicial, int alturaInicial);


#endif //UNTITLED_PROGARGS_H