//
//
//

#include "imagesoa.h"

//Constructor & Destructor
Imagesoa::Imagesoa(int num_args, std::string arg_1, std::string arg_2, std::string arg_3) {
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
    this->comun.abrirInDir();
    this->comun.leerInDir();
    while(this->comun.fileRead != NULL){
        // Rellenamos los pixeles llama a comun.leerBMP()
        this->llenarPixeles();
        // Realizar operacion seleccionada
        this->realizarOperacion();
        // Avanzamos a la siguiente pos del dir
        this->comun.leerInDir();
    }
    this->comun.cerrarInDir();
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

    for (int i=0; i<num_pixeles; i += 3) {
        // Añadimos los pixeles al array
        this->structurePixels.arrayR[i] = pixeles[i];
        this->structurePixels.arrayG[i + 1] = pixeles[i + 1];
        this->structurePixels.arrayB[i + 2] = pixeles[i + 2];
    }
}

void realizarOperacion(char *fichero, chronometro *time) {
    // Función encargada de realizar la operación
    if (this->comun.operation == "gauss"){
        t_inicio = std::chrono::high_resolution_clock::now();
        unsigned char *img = difusionGaussiana(imagen);
        t_fin = std::chrono::high_resolution_clock::now();
        time -> gaussTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->comun.operation == "histo"){
        t_inicio = std::chrono::high_resolution_clock::now();
        unsigned char *img = histograma(imagen);
        t_fin = std::chrono::high_resolution_clock::now();
        time -> histoTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();

    }
    if (this->comun.operation == "copy"){
        t_inicio = std::chrono::high_resolution_clock::now();
        unsigned char *img = copy(imagen);
        t_fin = std::chrono::high_resolution_clock::now();
        time -> copyTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->comun.operation == "mono"){
        t_inicio = std::chrono::high_resolution_clock::now();
        unsigned char *img = mono(imagen);
        t_fin = std::chrono::high_resolution_clock::now();
        time -> monoTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
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