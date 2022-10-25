//
//
//

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include "aux_functions.h"


std::string rutaArchivoSalida(std::string type,
                              std::string outdir,
                              std::string infile) {
    /* Función encargada de devolver un string con la ruta del
     * archivo de salida, utilizada en el copy por ejemplo.
     * El valor de type define el tipo de archivo.
     *      txt
     *      bmp
     *      hst*/

    std::string filePath;
    char slash = '/';

    filePath = outdir + slash;
    // Obtenemos el nombre del archivo de entrada
    for (int i=sizeof(infile); i>0; --i) {
        // recorrer this->actualFile desde atrás hasta encontrar /
        if (infile.at(i) == slash)
            // una vez obtenido el nombre del archivo terminamos y añadimos a filePath
            filePath = filePath + infile.substr(i+1, sizeof(infile)-3) + type;
    }
    return filePath;
}

void histograma(const std::vector<int>& RGB,
                std::string outFile) {
    /* Función encargada de crear y escribir el histograma
     * sobre el archivo .hst*/

    // Abrimos el archivo de salida con ruta adecuada
    std::ofstream archivo(outFile, std::ofstream::out);

    if (!archivo.is_open()) {
        throw"Error: al abrir el archivo de destino";
    }

    // Llenamos el archivo de salida con los histogramas
    for (int i=0; i<768; ++i) {
        archivo << RGB[i] << std::endl;
    }

    archivo.close();
}

void escalaGrises() {
    /* Función de apoyo para realizar el histograma*/

}

float transformacionLineal(int value) {
    /* Función encargada de realizar la transformación lineal sobre
     * los valores de los pixeles normalizdos*/

    float c_value;

    if (value <= 0.04045)
        c_value = value / 12.92;
    else
        c_value = pow((value + 0.055) / 1.055, 2.4);

    return c_value;
}

float correccionGamma(float cR, float cG, float cB) {
    /* Funcion encargada de la reaalización de la correccion gamma*/

    int cL = 0.2126 * cR + 0.7152 * cG + 0.0722 * cB;

    if (cL <= 0.0031308) {
        cG = 12.92 * cL;
    } else {
        cG = (1.055 * pow(cL, 1 / 2.4)) - 0.055;
    }

    return cG;
}
