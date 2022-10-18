//
//
//

#include "imagesoa.h"

//Constructor & Destructor
Imagesoa::Imagesoa(int num_args, String arg_1, String arg_2, String arg_3) {
    /* Constructor, recibe tres vectores que conformarán
     * el structurePixels*/
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

void Imagesoa::llenarPixeles() {
    /* Función encargada de llenar el array con los pixeles del
     * archivo BMP de comun*/

    int num_pixeles = 0;
    int* pixeles;
    // Leemos el header y abrimos el archivo en el que nos encontramos
    num_pixeles = this->comun.leerHeaderBMP();
    // Recibe como parametro una referencia a un array
    pixeles = this->comun.leerArrayBMP();

    for (int i=0; i<mun_pixeles; i += 3) {
        // Añadimos los pixeles al array
        this->structurePixels.arrayR[i] = pixeles[i];
        this->structurePixels.arrayG[i + 1] = pixeles[i + 1];
        this->structurePixels.arrayB[i + 2] = pixeles[i + 2];
    }
}

void realizarOperacion() {
    // Función encargada de realizar la operación
    if (this->comun.operation == "copy")
}