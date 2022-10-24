//
//
//

#include "progargs.h"
#include <filesystem>


// Constructor & Destructor
Common::Common() {
    // Los valores de los atributos serán aplicados uno a uno
    // estructura de la imagen
    this->imagen_BMP = NULL;
    // this->fileRead = NULL;
    //this->inDir = NULL;
    //this->archivos  = NULL;
    std::cout << "Clase common creada con exito" << std::endl;
}

bool Common::comprobarArg() {
    /* Función encargada de validar los argumentos introducidos,
     * devuelve false en caso de que algun arg sea incorrecto*/
    bool arg_correctos = true;
    std::cout << "$image " <<  this->inDir << " " << this->outDirectory << " " <<  this->operation << "\n";
    // comprobamos que el numero de argumentos sea el correcto
    if (this->numArgumentos != 3) {
        std::cout << "Wrong format:" << "\n";
        std::cout << "Image in_path out_path oper" << "\n";
        std::cout << "Operation: copy, histo, mono, gauss" << "\n";
        arg_correctos = false;
    }
    // comprobamos que la accion a realizar sea la indicada
    if (this->operation != "gauss" || this->operation != "histo" || this->operation != "mono" || this->operation != "copy") {
        std::cout << "Unexpected operation: " << this->operation << "\n";
        std::cout << "Image in_path out_path oper" << "\n";
        std::cout << "Operation: copy, histo, mono, gauss" << "\n";
        arg_correctos = false
    }
    // comprobamos si existen los directorios de entrada y salida
    if (!opendir(this->inDirectory)) {
        std::cout << "Input path: " << this->inDirectory << "\n";
        std::cout << "output path: " << this->outDirectory << "\n";
        std::cout << "cannot open directory " << "[" << this->inDirectory << "]" << "\n";
        std::cout << "image in_path out_path oper" << "\n";
        std::cout << "operation: copy, histo, mono, gauss" << "\n";
        arg_correctos = false;
    }
    if (!opendir(this->outDirectory)) {
        std::cout << "input path: " << this->inDirectory << "\n";
        std::cout << "output path: " << this->outDirectory << "\n";
        std::cout << "output directory " << "[" << this->outDirectory << "]" << " does not exist" << "\n";
        std::cout << "image in_path out_path oper" << "\n";
        std::cout << "operation: copy, histo, mono, gauss" << "\n";
        arg_correctos = false;
    }

    return arg_correctos;
}

std::string Common::abrirInDir() {
    /* Función que se llama para abrir el directorio de entrada*/
    this->inDir : filesystem::directory_iterator{this->inDirectory}; // libreria filesystem
}

void Common::leerInDir(){
    /* Finción que se va a encarg#include <filesystem>ar de funcionamiento
     * principal del programa, a cargo de llamar a
     * las funciones que realizarán las operaciones
     * necesarias */

    // El bucle while deberá ser implementado en la función invocante
    // ya que después de leerse debe realizarse la operación
    ; // bmps en directorio
    // hacer bucle for
    if (this->inDir.path().extension() == ".bmp"){
        this->archivos.push_back(this->inDir.path());
    }
}

string Common::nombre_archivo(std::string& ruta){
    boost::filesystem::path ruta; // toda la ruta
    nombre = filesystem::ruta.stem(); // nombre del archivo
    return nombre;
}

void Common::cerrarInDir() {
    /* Función encargada de cerrar el dir una vez abierto el dir de entrada*/

    // Una vez acabado el bucle en la función invocante, se
    // cerrará el directorio
    closedir(this->inDir);
}
////////////////////////////////////////////////////////////////////////////////
void Common::leerHeaderBMP(){
    /* Funcion encargada de leer y comprobar los valores del header*/
    // contenido del archivo bmp para usarlo en las lecturas
    this->fileRead(this->inDirectory);
    fileRead >> this->header_bmp;
    this->imagen_BMP.tamano = header_bmp[2];
    this->imagen_BMP.anchura = header_bmp[18];
    this->imagen_BMP.altura = header_bmp[22];
    this->imagen_BMP.datos_imagen = header_bmp[10];
    this->imagen_BMP.numero_planos = header_bmp[26];
    this->imagen_BMP.compresion = header_bmp[30];
    this->imagen_BMP.t_punto = header_bmp[28];
    this->padding = ((4 - (this->imagen_BMP.anchura * 3) % 4) % 4);

    if (this->imagen_BMP.t_punto != 24){
        throw "Error tamaño punto.";
    }
    if (this->imagen_BMP.compresion != 0){
        throw "Error valor de compresion";
    }
    if (this->imagen_BMP.numero_planos != 1){
        throw "Error numero de planos.";
    }
    return this->imagen_BMP.anchura * this->imagen_BMP.altura;
}
//////////////////////////////////////////////////////////////////////////////////


int& Common::leerArrayBMP(std::string path) {
    /* Continua la lectura del array BMP, leyendo los pixeles*/

    // Continuamos con la lectura
    int fila = (this->anchura*3 + 3) & (~3);
    unsigned char aux; // variable ayuda a reordenar los pyxeles de BGR a RGB
    unsigned char* datos_imagen = unsigned char[fila];
    int* RGB;
    // lectura de la imagen
    for (int i = 0; i < this->altura; i++) {
        fread(datos_imagen, sizeof(unsigned char), fila, this->actualFile);
        for (int j = 0; j < this->anchura * 3; j += 3) {
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
    std::ofstream outfile(this->outDirectory + "/" + this->fileRead->d_name + "_copia.bmp");

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
    std::ofstream outfile(this->outDirectory + "/" + this->fileRead->d_name + ".hst");

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
