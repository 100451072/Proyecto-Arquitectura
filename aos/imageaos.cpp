//
//
//

#include "imageaos.h"
// localizaciones del path
char origin[256];
char prox_location[256];
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
    this->comun.abrirInDir();
    // leemos el dir de entrada por primera vez para que el bucle pueda empezar
    // en caso de que exista algun archivo
    this->comun.leerInDir();
    while(this->comun.fileRead != NULL){
        // Rellenamos los pixeles llama a comun.leerBMP()
        this->llenarPixeles();
        // Realizar operacion seleccionada
        this->realizarOperacion();
        // Avanzamos a la siguiente pos del dir
        this->comun.leerInDir();
    }
    // Por ultimo cerramos el dir de entrada
    this->cerrarInDir();
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

void realizarOperacion(char *fichero, tiempo *time) {
    // Función encargada de realizar la operación
    if (this->comun.operation == "gauss"){
        t_inicio = chrono::high_resolution_clock::now();
        unsigned char *img = difusionGaussiana(imagen);
        t_fin = chrono::high_resolution_clock::now();
        time -> tiempoGauss = chrono::duration_cast<chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->comun.operation == "histo"){
        t_inicio = chrono::high_resolution_clock::now();
        unsigned char *img = histograma(imagen);
        t_fin = chrono::high_resolution_clock::now();
        time -> tiempoGauss = chrono::duration_cast<chrono::microseconds>(t_fin - t_inicio).count();

    }
    if (this->comun.operation == "copy"){
        t_inicio = chrono::high_resolution_clock::now();
        unsigned char *img = copy(imagen);
        t_fin = chrono::high_resolution_clock::now();
        time -> tiempoGauss = chrono::duration_cast<chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->comun.operation == "mono"){
        t_inicio = chrono::high_resolution_clock::now();
        unsigned char *img = mono(imagen);
        t_fin = chrono::high_resolution_clock::now();
        time -> tiempoGauss = chrono::duration_cast<chrono::microseconds>(t_fin - t_inicio).count();
    }

}

// lo qe supongo q cambiaria es al abrir la imagen o al pasar los pixeles
void difusionGaussiana(unsigned char *inputPixels, int anchuraInicial, int alturaInicial,) {
        int matriz[5][5] = {1,4,7,4,1,
                            4,16,26,16,4,
                            7,26,41,26,7,
                            4,16,26,16,4,
                            1,4,7,4,1};
        int w = 273;
        int avgR = 0, avgG = 0, avgB = 0;
        int l = anchuraInicial * 3;
        int tamano = alturaInicial * l;
        int cByte, b, cGauss, fGauss;
        unsigned char *pixelesDevolver
        for (int i = 0; i < alturaInicial - 1; i+=1){
            for (int j = 0; i < l - 1; j+=3){
                for (int s = -2; s <= 2; s++){
                    for (int t = -2; t <= 2; t++){
                        fGauss = s + 2;
                        cByte = j + t * 3;
                        cGauss = t + 2;
                        b = (i + s)*l + cByte;
                        if (b >= 0 && cByte <= l - 1 && b <= tamano && 0 <= cByte) // PIXEL R
                            avgR += matriz[fGauss][cGauss] * inputPixels[b];

                        if (b >= 0 && cByte <= l - 1 && b <= tamano && 0 <= cByte) // PIXEL G
                            avgG += matriz[fGauss][cGauss] * inputPixels[b];
                        b += 1;
                        cByte += 1;
                        if (b >= 0 && cByte <= l - 1 && b <= tamano && 0 <= cByte) // PIXEL B
                            avgB+= matriz[fGauss][cGauss] * inputPixels[b];
                        b += 1;
                        cByte += 1;
                    }
                }
                avgR = avgR / w; // se divide entre el peso
                avgG = avgG / w;
                avgB = avgB / w;
                pixelesDevolver[(i*l) + j] = avgR; // se guardan los pixeles en el char
                pixelesDevolver[(i*l) + j + 1] = avgG;
                pixelesDevolver[(i*j) + j + 2] = avgB;
            }
        }
        return pixelesDevolver; // se devuelven los pixeles modificados
}
