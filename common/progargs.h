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

using namespace std;

class Common:
{
private:
    // Atributos

    // Funciones de inicializacion
    void comprobarArg(int num_args, std::String argv_1, std::String argv_2, std::String argv_3);

public:
    // Constructor & Destructor
    Common(int num_args, std::String argv_1, std::String argv_2, std::String argv_3);
    Virtual ~Common();

    // Getters & Setters

    // Funciones

};

#endif //UNTITLED_PROGARGS_H
