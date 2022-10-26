//
//
//

#include "progargs.h"


 bool comprobarArg(int num_args, const std::string& inDir, const std::string& outDir, const std::string& operation) {
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

contenido_BMP leerHeaderBMP(const std::string& filePath){
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
    return imagen_BMP;
}


const std::vector<int>& leerArrayBMP(const std::string& filePath, contenido_BMP imagen_BMP) {
    /* Continua la lectura del array BMP, leyendo los pixeles*/
    // Avanzamos a la posición donde empiezand los pixeles
    // 54 bytes desde el inicio
    std::ifstream BMP_file;
    BMP_file.open(filePath, std::ios::in | std::ios::binary);

    int anchura = imagen_BMP.anchura;
    int altura = imagen_BMP.altura;

    // Continuamos con la lectura
    int fila = (imagen_BMP.anchura*3 + 3) & (~3);
    unsigned char aux; // variable ayuda a reordenar los pixeles de BGR a RGB
    unsigned char* datos_imagen = unsigned char[fila];
    std::vector<int> RGB;
    // lectura de la imagen
    for (int i = 0; i < altura; i++) {
        fileRead >> datos_imagen;
        for (int j = 0; j < anchura * 3; j += 3) {
            // es por tres ya que son tres: rgb; se reordenan
            aux = datos_imagen[j];
            datos_imagen[j] = datos_imagen[j + 2];
            datos_imagen[j + 2] = aux;
            // r
            RGB.push_back((int)datos_imagen[j]);
            // g
            RGB.push_back((int)datos_imagen[j + 1]);
            // b
            RGB.push_back((int)datos_imagen[j + 2]);
        }
    }
    fileRead.close();
    return RGB;
}


