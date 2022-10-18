//
//
//

#include "imageaos.h"

// Constructor & Destructor
Imageaos::Imageaos(int num_args, String arg_1, String arg_2, String arg_3) {
    /* Constructor, encargado de asigar a cada nodo de arrayPixeles
     * su valor de R, G, B*/

    // Inicialización de los atributos de common
    this->comun.numArgumentos = num_args;
    this->comun.inDirectory = arg_1;
    this->comun.outDirectory = arg_2;
    this->comun.operation = arg_3;

}

void Imagesoa::executeProgram() {
    /* Función principal encargada de la ejecución del programa*/

    // Comenzamos comprobando los argumentos de entrada
    if (!this->comun.comprobarArg())
    {
        throw"Error: parametros incorrectos";
    }
    // Bucle para ejecutar las ooperaciones sobre todas las fotos del dir
    // Obtenemos la primera pos del dir
    this->comun.leerDir();
    while(this->comun.diread != NULL){
        // Rellenamos los pixeles llama a comun.leerBMP()
        this->llenarPixeles();
        // Realizar operacion seleccionada
        this->realizarOperacion();
        // Avanzamos a la siguiente pos del dir
        this->comun.leerDir();
    }
}

void llenarPixeles() {
    /* Función encargada de llenar el array con los pixeles del
     * archivo BMP de comun*/

    int num_pixeles = 0;
    int* pixeles;

    // Leemos el header y abrimos el archivo en el que nos encontramos
    num_pixeles = this->comun.leerHeaderBMP();
    pixeles = this->comun.leerArrayBMP();

    for (int i=0; i<mun_pixeles; i += 3) {
        this->arrayPixeles[i].Red = pixeles[i];
        this->arrayPixeles[i + 1].Green = pixeles[i + 1];
        this->arrayPixeles[i + 2].Blue = pixeles[i + 2];
    }
}

void realizarOperacion() {

}