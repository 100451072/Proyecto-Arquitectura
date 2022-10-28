//
//
//
#include <iostream>
#include <chrono>
#include "imageaos.h"
#include "common/aux_functions.h"




Imageaos::Imageaos(std::string fileName, std::string inDir, std::string outDir) {
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
            Pixel pixel;
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

void Imageaos::realizarOperacion(std::string operation) {
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
    // Sumamos un a cada valor de 0 a 256 de los arrays en caso de aparición
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
    histo << RGB << std::endl;
    histo.close();
    t_fin = std::chrono::high_resolution_clock::now();
    std::cout << "  Histo time: " << std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count() << std::endl;
}

void Imageaos::escalaGrises() {
    /* Función encargada de pasar la imagen a escala de grises */
    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;
    t_inicio = std::chrono::high_resolution_clock::now();
    float cR, cG, cB, cg, g;
    // Normalizacion
    for (int i=0; i<this->width * this->height; ++i) {
        cR = transformacionLineal(this->arrayPixeles[i].Red / 255); // transformacion lineal de los 3 colores
        cG = transformacionLineal(this->arrayPixeles[i].Green / 255);
        cB = transformacionLineal(this->arrayPixeles[i].Blue / 255);
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

void Imageaos::difusionGaussiana() {
    /* Función encargada de generar el efecto de difusión
     * gaussiana */
    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;
    t_inicio = std::chrono::high_resolution_clock::now();

    int tmpR, tmpG, tmpB; // variables auxiliares
    int l = this->width * 3; // pixeles por fila
    int tamano = this->height * l; // tamaño total en bytes
    int cByte, b, cGauss, fGauss; // columna byte, byte, columna gauss, fila gauss
    for (int i = 0; i < this->height - 1; i += 1){
        for (int j = 0; j < l - 1; j += 3){
            tmpR = 0;
            tmpG = 0;
            tmpB = 0;
            for (int s = -2; s <= 2; s++){
                for (int t = -2; t <= 2; t++){
                    fGauss = s + 2;
                    cByte = j + t * 3;
                    cGauss = t + 2;
                    b = (i + s)*l + cByte;
                    if (b >= 0 && cByte <= l - 1 && b <= tamano && 0 <= cByte) // PIXEL R
                        tmpR += mGauss[fGauss][cGauss] * this->arrayPixeles[b].Red;

                    if (b >= 0 && cByte <= l - 1 && b <= tamano && 0 <= cByte) // PIXEL G
                        tmpG += mGauss[fGauss][cGauss] * this->arrayPixeles[b].Green;
                    b += 1;
                    cByte += 1;
                    if (b >= 0 && cByte <= l - 1 && b <= tamano && 0 <= cByte) // PIXEL B
                        tmpB += mGauss[fGauss][cGauss] * this->arrayPixeles[b].Blue;
                    b += 1;
                    cByte += 1;
                }
            }
            tmpR = tmpR / WEIGHT; // se divide entre el peso
            tmpG = tmpG / WEIGHT;
            tmpB = tmpB / WEIGHT;
            this->arrayPixeles[i].Red = tmpR; // se guardan los pixeles en el array de pixeles
            this->arrayPixeles[i].Green = tmpG;
            this->arrayPixeles[i].Blue = tmpB;
        }
    }
    t_fin = std::chrono::high_resolution_clock::now();
    std::cout << "  Gauss time: " << std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count() << std::endl;
    this->guardar();
}

