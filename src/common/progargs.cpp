//
//
//

#include "progargs.h"
#include "../aos/imageaos.h"


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

contenido_BMP leerHeaderBMP(const std::string& filePath, std::vector<BYTE>& array_BMP){
    /* Funcion encargada de leer y comprobar los valores del header*/
    // Volcamos los primeros 54 bytes en header_bmp
    std::ifstream BMP_file;
    BYTE temp = '0';
    contenido_BMP imagen_BMP;

    // Comprobamos que podemos abrir el archivo
    BMP_file.open(filePath, std::ios::in | std::ios::binary);
    // Obtenemos la longitud del archivo
    BMP_file.seekg(0, std::ifstream::end);
    long length = BMP_file.tellg();
    BMP_file.seekg(0, std::ifstream::beg);

    // Bucle para llenar nuestro array
    for (int i=0; i<length; ++i) {
        BMP_file >> temp;
        array_BMP.push_back(temp);
    }

    BMP_file.close();

    // Para obtener los valores utilizamos mascaras(multiplicar por 2⁸, 2^16...))
    // Header info
    imagen_BMP.tamano = array_BMP[2] + array_BMP[3] * pow(2, 8) + array_BMP[4] * pow(2, 16) + array_BMP[5] * pow(2, 24);
    imagen_BMP.dir_datos_imagen = array_BMP[10] + array_BMP[11] * pow(2, 8) + array_BMP[12] * pow(2, 16) + array_BMP[13] * pow(2, 24);
    // Header DIB
    imagen_BMP.anchura = array_BMP[18] + array_BMP[19] * pow(2, 8) + array_BMP[20] * pow(2, 16) + array_BMP[21] * pow(2, 24);
    imagen_BMP.altura = array_BMP[22] + array_BMP[23] * pow(2, 8) + array_BMP[24] * pow(2, 16) + array_BMP[25] * pow(2, 24);
    imagen_BMP.numero_planos = array_BMP[26] + array_BMP[27] * pow(2, 8);
    imagen_BMP.t_punto = array_BMP[28] + array_BMP[29] * pow(2, 8);
    imagen_BMP.compresion = array_BMP[30] + array_BMP[31] * pow(2, 8) + array_BMP[32] * pow(2, 16) + array_BMP[33] * pow(2, 24);
    imagen_BMP.size_bitmap_data = array_BMP[34] + array_BMP[35] * pow(2, 8) + array_BMP[36] * pow(2, 16)+ array_BMP[37] * pow(2, 24);
    imagen_BMP.t_padding = (int) (imagen_BMP.anchura * 3) % 4 ;//(4 - (imagen_BMP.anchura * 3) % 4) % 4;

    if (imagen_BMP.t_punto != 24){
        throw std::invalid_argument("Error tamaño punto.");
    }
    if (imagen_BMP.compresion != 0){
        throw std::invalid_argument("Error valor de compresion");
    }
    if (imagen_BMP.numero_planos != 1){
        throw std::invalid_argument("Error numero de planos.");
    }
    return imagen_BMP;
}


const std::vector<int>& leerArrayBMP(contenido_BMP imagen_BMP, std::vector<BYTE>& archivo_BMP) {
    /* Continua la lectura del array BMP, leyendo los pixeles*/
    // Avanzamos a la posición donde empiezand los pixeles

    // Posición de inicio de los pixeles
    int inicio = (int)imagen_BMP.dir_datos_imagen;
    int altura = (int)imagen_BMP.altura;
    int anchura = (int)imagen_BMP.anchura;
    int padding = (int)imagen_BMP.t_padding;
    int end_pixeles = (int)imagen_BMP.size_bitmap_data;  // En bytes

    std::vector<int> RGB;

    // lectura de la imagen
    for (int i=0; i< altura; ++i) {
        for (int j=0; j<anchura * 3; j += 3) {
            // Importante en archivo_BMP esta en BGR
            // r                                (bytes que ya hemos leido)
            RGB.push_back((int) archivo_BMP[inicio + i * (anchura * 3 + padding) + j + 2]);
            // g
            RGB.push_back((int) archivo_BMP[inicio + i * (anchura * 3 + padding) + j + 1]);
            // b
            RGB.push_back((int) archivo_BMP[inicio + i * (anchura * 3 + padding) + j]);
        }
    }
    return RGB;
}


