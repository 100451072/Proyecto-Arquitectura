//
//
//

#include "imagesoa.h"

//Constructor & Destructor
Imagesoa::Imagesoa(int num_args, String arg_1, String arg_2, String arg_3) {
    /* Constructor, recibe tres vectores que conformarán
     * el structurePixels*/

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

void Imagesoa::llenarPixeles() {
    /* Función encargada de llenar el array con los pixeles del */



}

void Imagesoa::addPixel(int R, int G, int B) {
    /* Función que irá añadiendo pixeles al final
     * de los arrays R, G, B*/

    this->structurePixels.R[this->lastPos] = R;
    this->structurePixels.G[this->lastPos] = G;
    this->structurePixels.B[this->lastPos] = B;

    // Añadimos uno para ir avanzando en el array
    this->lastPos++;
}