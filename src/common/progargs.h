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

    // Ruta de dir de entrada, necesario para apertura
    auto const& inDir;
    // Guarda la ruta al archivo altual
    std::string actualFile;
    // Archivo dentro del dir de entrada, ira cambiando
    std::ifstream fileRead;

    // Datos del BMP
    // Estructura con los elemnentos importantes del header
    contenido_BMP imagen_BMP;
    // En caso de que el archivo bmp tenga padding
    unsigned char padding[3] = {0,1,2}; // padding al escribir
    // contenido o header del bmp
    unsigned char header_bmp[54];// header de el bmp

public:
    // Constructor & Destructor
    Common();
    virtual ~Common();

    // Funciones
    bool comprobarArg(int num_args, const std::string& argv_1, const std::string& argv_2, const std::string& argv_3);
    int leerHeaderBMP();
    int& leerArrayBMP();
    std::string rutaArchivoSalida(std::string operation, std::string type);
    // Operaciones de la aplicación
    void histograma(const int& R, const int& G, const int& B);
    void escalaGrises();
    void difusionGaussiana();
};

#endif //UNTITLED_PROGARGS_H