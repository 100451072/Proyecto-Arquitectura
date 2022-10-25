//
//
//

#include "progargs.h"
#include <filesystem>



static bool comprobarArg(int num_args, const std::string& inDir, const std::string& outDir, const std::string& operation) {
    /* Función encargada de validar los argumentos introducidos,
     * devuelve false en caso de que algun arg sea incorrecto*/
    std::cout << "$image " <<  inDir << " " << outDir << " " <<  operation << "\n";
    // comprobamos que el numero de argumentos sea el correcto
    if (num_args != 3) {
        std::cout << "Wrong format:" << "\n";
        std::cout << "Image in_path out_path oper" << "\n";
        std::cout << "Operation: copy, histo, mono, gauss" << "\n";
        return false;
    }
    // comprobamos que la accion a realizar sea la indicada
    if (operation != "gauss" || operation != "histo" || operation != "mono" || operation != "copy") {
        std::cout << "Unexpected opeoperationration: " << operation << "\n";
        std::cout << "Image in_path out_path oper" << "\n";
        std::cout << "Operation: copy, histo, mono, gauss" << "\n";
        return false;
    }
    // comprobamos si existen los directorios de entrada y salida
    std::ifstream inputFile(inDir);
    if (inputFile.bad()) {
        std::cout << "Input path: " << inDir << "\n";
        std::cout << "output path: " << outDir << "\n";
        std::cout << "cannot open directory " << "[" << inDir << "]" << "\n";
        std::cout << "image in_path out_path oper" << "\n";
        std::cout << "operation: copy, histo, mono, gauss" << "\n";
        return false;
    }
    std::ifstream outputFile(inDir);
    if (outputFile.bad()) {
        std::cout << "input path: " << inDir << "\n";
        std::cout << "output path: " << outDir << "\n";
        std::cout << "output directory " << "[" << outDir << "]" << " does not exist" << "\n";
        std::cout << "image in_path out_path oper" << "\n";
        std::cout << "operation: copy, histo, mono, gauss" << "\n";
        return false;
    }

    return true;
}

static int leerHeaderBMP(std::string filePath){
    /* Funcion encargada de leer y comprobar los valores del header*/
    // Volcamos los primeros 54 bytes en header_bmp
    std::ifstream BMP_file;
    const int BMP_header_size = 54;
    unsigned char BMP_info[BMP_header_size];
    contenido_BMP imagen_BMP;

    BMP_file.open(filePath, std::ios::in | std::ios::binary);

    BMP_file.read(reinterpret_cast<char*> (BMP_info), BMP_header_size);
    imagen_BMP.tamano = BMP_info[2];
    imagen_BMP.anchura = BMP_info[18];
    imagen_BMP.altura = BMP_info[22];
    imagen_BMP.datos_imagen = BMP_info[10];
    imagen_BMP.numero_planos = BMP_info[26];
    imagen_BMP.compresion = BMP_info[30];
    imagen_BMP.t_punto = BMP_info[28];
    imagen_BMP.t_padding = (4 - (imagen_BMP.anchura * 3) % 4) % 4;

    if (imagen_BMP.t_punto != 24){
        throw "Error tamaño punto.";
    }
    if (imagen_BMP.compresion != 0){
        throw "Error valor de compresion";
    }
    if (imagen_BMP.numero_planos != 1){
        throw "Error numero de planos.";
    }
    return imagen_BMP.anchura * imagen_BMP.altura;
}

int& Common::leerArrayBMP() {
    /* Continua la lectura del array BMP, leyendo los pixeles*/
    // Avanzamos a la posición donde empiezand los pixeles
    // 54 bytes desde el inicio
    fileRead.seekg(imagen_BMP.datos_imagen, ios::beg);

    // Continuamos con la lectura
    int fila = (imagen_BMP.anchura*3 + 3) & (~3);
    unsigned char aux; // variable ayuda a reordenar los pyxeles de BGR a RGB
    unsigned char* datos_imagen = unsigned char[fila];
    int* RGB;
    // lectura de la imagen
    for (int i = 0; i < altura; i++) {
        fileRead >> datos_imagen;
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
    fileRead.close();
    return *RGB;
}

void Common::difusionGaussiana(unsigned char *inputPixels, int anchuraInicial, int alturaInicial) {
    int matriz[5][5] = {{1,4,7,4,1},
                     {4,16,26,16,4},
                     {7,26,41,26,7},
                     {4,16,26,16,4},
                     {1,4,7,4,1}};
    int w = 273;
    int avgR = 0, avgG = 0, avgB = 0;
    int l = anchuraInicial * 3;
    int tamano = alturaInicial * l;
    int cByte, b, cGauss, fGauss;
    unsigned char *pixelesDevolver;
    for (int i = 0; i < alturaInicial - 1; i+=1){
        for (int j = 0; j < l - 1; j+=3){
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
