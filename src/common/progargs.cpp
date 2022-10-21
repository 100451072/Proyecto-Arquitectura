//
//
//

#include "progargs.h"

// Constructor & Destructor
Common::Common() {
    // Los valores de los atributos serán aplicados uno a uno
    this->actualFile = NULL;
    cout << "Clase common creada con exito" << endl;
}

bool Common::comprobarArg() {
    /* Función encargada de validar los argumentos introducidos,
     * devuelve false en caso de que algun arg sea incorrecto*/

    bool arg_correctos = true;

    // comprobamos que el numero de argumentos sea el correcto
    if (this->numArgumentos != 3) {
        cout << "Wrong format:" << "\n";
        cout << "Image in_path out_path oper" << "\n";
        cout << "Operation: copy, histo, mono, gauss" << "\n";
        arg_correctos = false;
    }
    // comprobamos que la accion a realizar sea la indicada
    if (this->operation != "gauss" || this->operation != "histo" || this->operation != "mono" || this->operation != "copy") {
        cout << "Unexpected operation: " << this->operation << "\n";
        cout << "Image in_path out_path oper" << "\n";
        cout << "Operation: copy, histo, mono, gauss" << "\n";
        arg_correctos = false
    }
    // comprobamos si existen los directorios de entrada y salida
    if (!opendir(this->inDirectory)) {
        cout << "Input path: " << this->inDirectory << "\n";
        cout << "output path: " << this->outDirectory << "\n";
        cout << "cannot open directory " << "[" << this->inDirectory << "]" << "\n";
        cout << "image in_path out_path oper" << "\n";
        cout << "operation: copy, histo, mono, gauss" << "\n";
        arg_correctos = false;
    }
    if (!opendir(this->outDirectory)) {
        cout << "input path: " << this->inDirectory << "\n";
        cout << "output path: " << this->outDirectory << "\n";
        cout << "output directory " << "[" << this->outDirectory << "]" << " does not exist" << "\n";
        cout << "image in_path out_path oper" << "\n";
        cout << "operation: copy, histo, mono, gauss" << "\n";
        arg_correctos = false;
    }

    return arg_correctos;
}

void Common::abrirInDir() {
    /* Función que se llama para abrir el directorio de entrada*/

    // Comoprobamos que el directorio de entrada se abre correctamente
    if ((this->inDir = opendir(this->inDirectory)) == NULL) {
        throw"Error: abriendo el directorio de entrada";
    }
}

void Common::leerInDir(){
    /* Finción que se va a encargar de funcionamiento
     * principal del programa, a cargo de llamar a
     * las funciones que realizarán las operaciones
     * necesarias */

    // El bucle while deberá ser implementado en la función invocante
    // ya que después de leerse debe realizarse la operación
    this->fileRead = readdir(direntrada);
}

void Common::cerrarInDir() {
    /* Función encargada de cerrar el dir una vez abierto el dir de entrada*/

    // Una vez acabado el bucle en la función invocante, se
    // cerrará el directorio
    closedir(this->inDir);
}

int Common::leerHeaderBMP(){
    /* Funciń encargada de leer y comprobar los valores del header*/

    // COMPROBAR SI this->fileRead.name CONTINE LA RUTA ABSOLUTA AL ARCHIVO
    this->actualFile = fopen(this->fileRead.d_name, "rb");
    // si no existe se lanza excepcion
    if (this->actualFile == NULL){
        throw "Error: no se pudo encontrar el archivo imagen dentro del directorio";
    }

    // se leen del archivo de entrada
    fread(this->header, sizeof(unsigned char), 54, this->actualFile);
    // comprobamos los valores de compresion = 0, numero de planos = 1, t de punto = 24
    if ((*(int*)&this->header[30]) != 0){
        throw "Valor de compresión invalido";
    }
    if ((*(int*)&this->header[26]) != 1){
        throw "Número de nivel invalido";
    }
    if ((*(int*)&this->header[24]) != 24){ // esto alomejor es cada punto de toda la imagen y no se si tendria q ir en el bucle
        throw "Punto de nivel invalido";
    }
    // Obtenemos la altura y la anchura del header (estan los bytes en la tabla del pdf)
    int anchura = *(int*)&this->header[18];
    int altura = *(int*)&this->header[22];

    // Devolvemos la altura por la anchura, para que la función invocante
    // sepa cuantos pixeles tiene la imagen
    return anchura * altura;
}

int& Common::leerArrayBMP() {
    /* Continua la lectura del array BMP */

    int anchura = *(int*)&this->header[18];
    int altura = *(int*)&this->header[22];
    // Continuamos con la lectura
    int fila = (anchura*3 + 3) & (~3);
    unsigned char aux; // variable ayuda a reordenar los pyxeles de BGR a RGB
    unsigned char* datos_imagen = unsigned char[fila];
    int* RGB;
    // lectura de la imagen
    for (int i = 0; i < altura; i++) {
        fread(datos_imagen, sizeof(unsigned char), fila, this->actualFile);
        for (int j = 0; j < anchura * 3; j += 3) {
            // es por tres ya que son tres: rgb; se reordenan
            aux = datos_imagen[j];
            datos_imagen[j] = datos_imagen[j + 2];
            datos_imagen[j + 2] = aux;
            // r
            RGB[j] = (int)datos_imagen[j];
            // g
            RGB[j + 1] = (int)datos_imagen[j + 1];
            // b
            RGB[j + 2] = (int)datos_imagen[j + 2];
        }
    }
    fclose(this->actaulfile);
    return &RGB;
}

// operaciones de la aplicación///////////////////////////7

void Common::copiarImagen() {
    /* función que implementa la copia
     * de imagenes, para ello crea un nuevo archivo*/

    // no se si concatenar char asi funcionara
    ofstream outfile(this->outdirectory + "/" + this->fileRead->d_name + "_copia.bmp");

    // añadimos el header
    outfile << this->header;

    // hacer un bucle para meter todos los pixeles uno por uno
    // ojo: ordenarlos como antes estaban ordenados bgr
    for (int i=0; i<){

    }
    outfile.close();
}

void Common::histograma() {
    /* función encargada de crear el histograma,
     * para lo que deberá crear un archivo .hst*/

    // histograma r, g, b
    int r[256], g[256], b[256];

    // creamos el nuevo archivo en el dir de salida
    ofstream outfile(this->outdirectory + "/" + this->fileRead->d_name + ".hst");

    // calculo de los histogramas

    // añadimos la información de los histogramas al archivo .hst
    for (int i=0; i<256*3; ++i) {
        outfile << ;
    }
    outfile.close();
}

void Common::escalagrises() {

}


void Common::difusionGaussiana(unsigned char *inputPixels, int anchuraInicial, int alturaInicial,) {
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
