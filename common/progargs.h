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

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include "imagesoa.h"
#include "imageoas.h"
#include <cmath>
using namespace std;

class Common:
{
private:
    // Atributos
    // Clases encargadas de almacenar los datos dependiendo del caso
    Imagesoa imagesoa;
    Imageoas imageoas;

    String inDirectory;
    String outDirectory;
    String operation;

    unsigned char header[54];
    struct dirent* diread;

    int type;

public:
    // Constructor & Destructor
    Common(int type, int num_args, String argv_1, String argv_2, String argv_3);
    Virtual ~Common();

    // Funciones
    bool comprobarArg(int num_args, String argv_1, String argv_2, String argv_3);
    char leerBMP(char* puntero);
    void devolver_imagenes(char *dir);
    // Operaciones de la aplicación
    void copiarImagen();
    void histograma();
    void escalaGrises();
    void difusionGaussiana();
};

#endif //UNTITLED_PROGARGS_H
