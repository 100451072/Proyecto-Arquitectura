//
//
//

#include "imageaos.h"

// Constructor & Destructor
Imageaos::Imageaos(int num_args, String arg_1, String arg_2, String arg_3) {
    /* Constructor, encargado de asigar a cada nodo de arrayPixeles
     * su valor de R, G, B*/

    this->lastPos = 0;

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
}

void Imageaos::addPixel(int R, int G, int B) {
    /* Funcion que ira añadiendo pixeles al final
     * del arrayPixeles */

    this->arrayPixeles[this->lastPos].R = R;
    this->arrayPixeles[this->lastPos].G = G;
    this->arrayPixeles[this->lastPos].B = B;

    // Sumamos uno para ir avanzando en el array
    this->lastPos++;

}