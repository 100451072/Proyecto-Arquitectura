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

class Common:
{
private:
    // Atributos
    int numArgumentos;
    // String pasados por el main
    string image;
    string inDirectory;
    string outDirectory;
    string operation;

    // Puntero al dir de entrada
    DIR* inDir;
    // Guardamos el valor del header en caso de que haya que copiarlo
    unsigned char header[54];
    // Archivo dentro del dir de entrada, ira cambiando
    struct dirent* fileRead;

public:
    // Constructor & Destructor
    Common();
    Virtual ~Common();

    // Funciones
    bool comprobarArg(int num_args, const string& argv_1, const string& argv_2, const string& argv_3);
    void abrirInDir();
    void leerInDir();
    void cerrarInDir();
    int leerHeaderBMP();
    int& leerArrayBMP();
    // Operaciones de la aplicación
    void copiarImagen();
    void histograma();
    void escalaGrises();
    void difusionGaussiana();
};

#endif //UNTITLED_PROGARGS_H