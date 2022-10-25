//
//
//

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
    char slash = "/"

    filePath = outdir + "/";
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
    std::ofstream archivo.open(outFile, std::ofstream::out);

    if (!archivo.is_open()) {
        throw"Error: al abrir el archivo de destino";
    }

    // Llenamos el archivo de salida con los histogramas
    for (int i=0; i<768; ++i) {
        archivo << RGB[i] << endl;
    }

    archivo.close();
}

void escalaGrises() {
    /* Función de apoyo para realizar el histograma*/
    
}