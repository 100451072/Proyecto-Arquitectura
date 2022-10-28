//
//
//
#include <iostream>
#include <chrono>
#include "imageaos.h"




Imageaos::Imageaos(const std::string& fileName, const std::string& inDir, const std::string& outDir) {
    /* Función encargada de llenar el array con los píxeles del
     * archivo BMP de comun*/
    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;
    this->fileName = fileName;
    this->inDir = inDir;
    this->outDir = outDir;
    t_inicio = std::chrono::high_resolution_clock::now();
    std::ifstream imageFile;
    imageFile.open(this->inDir, std::ios::in | std::ios::binary);
    imageFile.read(reinterpret_cast<char*>(this->header), 54);
    if (!this->checkHeader())
        throw std::invalid_argument("HEADER INCORRECTO");
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            unsigned char pixelBuffer[3];
            Pixel pixel{};
            imageFile.read(reinterpret_cast<char*>(pixelBuffer), 3);
            pixel.Blue = static_cast<int>(pixelBuffer[0]);
            pixel.Green = static_cast<int>(pixelBuffer[1]);
            pixel.Red = static_cast<int>(pixelBuffer[2]);
            this->arrayPixeles.push_back(pixel);
        }
        imageFile.ignore(this->padding);
    }
    imageFile.close();
    std::cout << "File: \"" << this->fileName << "\"" << std::endl;
    t_fin = std::chrono::high_resolution_clock::now();
    std::cout << "  Load time: " << std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count() << std::endl;

}

bool Imageaos::checkHeader() {
    // Comprobamos si empieza por BM
    if(this->header[0] != 'B' || this->header[1] != 'M')
        return false;
    // Comprobamos si el número de planos es igual a 1
    if((this->header[26] + (this->header[27] << 8)) != 1)
        return false;
    // Comprobamos si el tamaño de punto es de 24 bits
    if((this->header[28] + (this->header[29] << 8)) != 24)
        return false;
    // Comprobamos si el valor de compresión es igual a 0
    if((this->header[30] + (this->header[31] << 8) + (this->header[32] << 16) + (this->header[33] << 24)) != 0)
        return false;
    // Guardamos los valores una vez nos hemos asegurado de que el formato es correcto
    this->width = this->header[18] + (this->header[19] << 8) + (this->header[20] << 16) + (this->header[21] << 24);
    this->height = this->header[22] + (this->header[23] << 8) + (this->header[24] << 16) + (this->header[25] << 24);
    this->padding = (4 - 3*width % 4)%4;
    return true;
}

void Imageaos::realizarOperacion(const std::string& operation) {
    /* Función encargada de escoger la operación */
    if (operation == "gauss"){
        this->difusionGaussiana();
    }
    if (operation == "histo"){
        this->histograma();
    }
    if (operation == "copy"){
        this->copiarImagen();
    }
    if (operation == "mono"){
        this->escalaGrises();
    }
}

void Imageaos::guardar() {
    /* Función encargada de guardar la imagen resultante
     * y cronometrar el proceso */
    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;
    t_inicio = std::chrono::high_resolution_clock::now();
    std::ofstream outFile;
    outFile.open(this->outDir+"/"+this->fileName, std::ios::out | std::ios::binary);
    outFile.write(reinterpret_cast<char*>(this->header), HEADER_SIZE);
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            unsigned char pixelBuffer[3];
            pixelBuffer[0] = this->arrayPixeles[i*width + j].Blue;
            pixelBuffer[1] = this->arrayPixeles[i*width + j].Green;
            pixelBuffer[2] = this->arrayPixeles[i*width + j].Red;
            outFile.write(reinterpret_cast<char*>(pixelBuffer), 3);
        }
        for(int k = 0; k < padding; k++) {
            unsigned char paddingByte[1];
            paddingByte[0] = 0;
            outFile.write(reinterpret_cast<char *>(paddingByte), 1);
        }
    }
    outFile.close();
    t_fin = std::chrono::high_resolution_clock::now();
    std::cout << "  Store time: " << std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count() << std::endl;

}

void Imageaos::copiarImagen() {
    /* Función encargada de copiar la imagen en el directorio de salida */
    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;
    t_inicio = std::chrono::high_resolution_clock::now();
    t_fin = std::chrono::high_resolution_clock::now();
    std::cout << "  Copy time: " << std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count() << std::endl;
    this->guardar();
}

void Imageaos::histograma() {
    /* Función encargada de crear el histograma y pasárselos a la
     * función de common histograma */
    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;
    t_inicio = std::chrono::high_resolution_clock::now();
    int R[256] = { 0 };
    int G[256] = { 0 };
    int B[256] = { 0 };
    // Inicializamos el vector RGB a cero
    char RGB[768];
    // Sumamos un a cada valor de 0 a 255 de los arrays en caso de aparición
    for (int i=0; i<this->height * this->width ; ++i) {
        R[this->arrayPixeles[i].Red]++;
        G[this->arrayPixeles[i].Green]++;
        B[this->arrayPixeles[i].Blue]++;
    }
    // Con los valores anteriores llenamos el vector RGB
    for (int i=0; i<256; ++i) {
        RGB[i] = static_cast<char>(R[i]);
        RGB[256 + i] = static_cast<char>(G[i]);
        RGB[512 + i] = static_cast<char>(B[i]);
    }
    std::ofstream histo(this->outDir+"/"+this->fileName+".hst");
    for (char i : RGB) {
        histo << i << std::endl;
    }
    histo.close();
    t_fin = std::chrono::high_resolution_clock::now();
    std::cout << "  Histo time: " << std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count() << std::endl;
}

void Imageaos::escalaGrises() {
    /* Función encargada de pasar la imagen a escala de grises */
    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;
    t_inicio = std::chrono::high_resolution_clock::now();
    double cR, cG, cB, cg, g;
    // Normalizacion
    for (int i=0; i<this->width * this->height; ++i) {
        cR = transformacionLineal(static_cast<double>(this->arrayPixeles[i].Red) / double(255)); // transformacion lineal de los 3 colores
        cG = transformacionLineal(static_cast<double>(this->arrayPixeles[i].Green) / double(255));
        cB = transformacionLineal(static_cast<double>(this->arrayPixeles[i].Blue) / double(255));
        cg = correccionGamma(cR, cG, cB); // sacada ahorro lineas
        g = cg * 255; // se vuelve a escala de 256 solucion por cada 3 pixeles
        this->arrayPixeles[i].Red =  static_cast<int>(g); // se guardan los pixeles en el char todos el mismo
        this->arrayPixeles[i].Green = static_cast<int>(g); // se guardan los pixeles en el char todos el mismo
        this->arrayPixeles[i].Blue = static_cast<int>(g); // se guardan los pixeles en el char todos el mismo
    }
    t_fin = std::chrono::high_resolution_clock::now();
    std::cout << "  Mono time: " << std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count() << std::endl;
    this->guardar();
}

int mGauss[5][5] = {{1, 4, 7, 4, 1},
                    {4, 16, 26, 16, 4},
                    {7, 26, 41, 26, 7},
                    {4, 16, 26, 16, 4},
                    {1, 4, 7, 4, 1}};


//gauss aos
void Imageaos::difusionGaussiana() {
    /* Función encargada de realizar la difusion gaussiana sobre
    la imagen de entrada*/
    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;
    t_inicio = std::chrono::high_resolution_clock::now();
    int anchura = this->width;
    int altura = this->height;
    int total = anchura*altura;
    // Copia del resultado de la transformacion para no afectar a los siguientes valroes
    std::vector<int> temp1;
    std::vector<int> temp2;
    std::vector<int> temp3;
    // Recorremos el array de pixeles por completo
    for (int i=0; i<total; ++i) {
        temp1.push_back(0);
        temp2.push_back(0);
        temp3.push_back(0);
        //Filas
        for (int k=-2; k<2; ++k) {
            // Columnas
            for (int l=-2; l<2; ++l) {
                // Nos desplazamos en el array de pixeles obteniendo las pos requeridas
                // Para que los pixeles de fuera sumen cero, comprobamos cuando los valores se salen de la matriz
                if (((0 <= i % anchura + l) && (i % anchura + l < anchura)) && ((0 <= i / anchura + k) && (i / anchura + k< altura))) {
                    // Multiplicar por el valor anchura nos permite desplazarnos entre las filas
                    temp1[i] += mGauss[k + 3][l + 3] * this->arrayPixeles[i + (anchura * k + l)].Red;
                    temp2[i] += mGauss[k + 3][l + 3] * this->arrayPixeles[i + (anchura * k + l)].Green;
                    temp3[i] += mGauss[k + 3][l + 3] * this->arrayPixeles[i + (anchura * k + l)].Blue;}}}
        // Dividimos entre w
        temp1[i] /= WEIGHT;
        temp2[i] /= WEIGHT;
        temp3[i] /= WEIGHT;}
    insertarEnArray(total, temp1, temp2, temp3);
    t_fin = std::chrono::high_resolution_clock::now();
    std::cout << "  Gauss time: " << std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count() << std::endl;
    this->guardar();
}

void Imageaos::insertarEnArray(int total, const std::vector<int> &temp1, const std::vector<int> &temp2,
                               const std::vector<int> &temp3) {// Asignamos al array global sus respectivos valores, no se puede hacer en el bucle de arriba
// ya que alterariamos el calculo de los siguientes valores
    for (int i=0; i<total; ++i) {
        arrayPixeles[i].Red = temp1[i];
        arrayPixeles[i].Green = temp2[i];
        arrayPixeles[i].Blue = temp3[i];
    }
}

