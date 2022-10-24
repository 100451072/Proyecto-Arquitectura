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

void Common::leerHeaderBMP(){
    /* Funcion encargada de leer y comprobar los valores del header*/
    // Volcamos los primeros 54 bytes en header_bmp
    this->fileRead(this->actualFile);
    fileRead >> this->header_bmp;

    this->imagen_BMP.tamano = this->header_bmp[2];
    this->imagen_BMP.anchura = this->header_bmp[18];
    this->imagen_BMP.altura = this->header_bmp[22];
    this->imagen_BMP.datos_imagen = this->header_bmp[10];
    this->imagen_BMP.numero_planos = this->header_bmp[26];
    this->imagen_BMP.compresion = this->header_bmp[30];
    this->imagen_BMP.t_punto = this->header_bmp[28];
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

int& Common::leerArrayBMP() {
    /* Continua la lectura del array BMP, leyendo los pixeles*/
    // Avanzamos a la posición donde empiezand los pixeles
    // 54 bytes desde el inicio
    this->fileRead.seekg(54, ios::beg);

    // Continuamos con la lectura
    int fila = (this->imagen_BMP.anchura*3 + 3) & (~3);
    unsigned char aux; // variable ayuda a reordenar los pyxeles de BGR a RGB
    unsigned char* datos_imagen = unsigned char[fila];
    int* RGB;
    // lectura de la imagen
    for (int i = 0; i < this->altura; i++) {
        this->fileRead >> datos_imagen;
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
    this->fileRead.close();
    return &RGB;
}

std::string Common::rutaArchivoSalida(std::string operation, std::string type) {
    /* Función encargada de devolver un string con la ruta del
     * archivo de salida, utilizada en el copy por ejemplo.
     * Los valores que puede tomar operaion son:
     *      copy_
     *      histo_
     *      grises_
     *      gauss_
     * El valor de type define el tipo de archivo.
     *      .txt
     *      .bmp
     *      .hst
     * OJO que this->actualFile debe estar inicializado con el valor
     * de archivo actual */

    std::string filePath;
    char slash = "/"

    filePath = this->outDirectory + "/" + operation;
    // Obtenemos el nombre del archivo de entrada
    for (int i=sizeof(this->actualFile); i>0; --i) {
        // recorrer this->actualFile desde atrás hasta encontrar /
        if (this->actualFile.at(i) == slash)
            // una vez obtenido el nombre del archivo terminamos y añadimos a filePath
            filePath = filePath + this->actualFile.substr(i+1, sizeof(this->actualFIle)-3) + type;
    }
    return filePath;
}

/////////////////////////////////////////////////////////////////////////////////////

void Common::histograma(const int& R, const int& G, const int& B) {
    /* Función encargada de crear y escribir el histograma
     * sobre el archivo .hst*/

    // Abrimos el archivo de salida con ruta adecuada
    std::ofstream archivo(this->rutaArchivoSalida("histo_", ".hst"));

    // Llenamos el archivo de salida
    for (int i=0; i<256; ++i) {
        archivo << R[i] << endl;
    }
    for (int i=0; i<256; ++i) {
        archivo << G[i] << endl;
    }
    for (int i=0; i<256; ++i) {
        archivo << B[i] << endl;
    }
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
