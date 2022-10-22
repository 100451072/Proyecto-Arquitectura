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


class Common
{
private:
    // Atributos
    int numArgumentos;
    // String pasados por el main
    std::string image;
    std::string inDirectory;
    std::string outDirectory;
    std::string operation;

    // Puntero al dir de entrada
    std::filesystem::path inDir;
    // Guardamos el valor del header en caso de que haya que copiarlo
    unsigned char header[54];
    // Archivo dentro del dir de entrada, ira cambiando
    struct dirent* fileRead;

public:
    // Constructor & Destructor
    Common();
    virtual ~Common();

    // Funciones
    bool comprobarArg(int num_args, const std::string& argv_1, const std::string& argv_2, const std::string& argv_3);
    void abrirInDir();
    std::vector <std::string> leerInDir();
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