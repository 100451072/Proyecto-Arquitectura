//
//
//

#include "imageaos.h"

#include <utility>

// Constructor & Destructor
Imageaos::Imageaos(int num_args, const std::string arg_1, const std::string arg_2, const std::string arg_3) {
    /* Constructor, encargado de asigar a cada nodo de arrayPixeles
     * su valor de R, G, B*/
    this->numArgumentos = num_args;
    this->inDirectory = arg_1;
    this->outDirectory = arg_2;
    this->operation = arg_3;

}

void Imageaos::executeProgram() {
    /* Función principal encargada de la ejecución del programa*/

    // Comenzamos comprobando los argumentos de entrada
    if (!Common::comprobarArg(this->numArgumentos, this->inDirectory, this->outDirectory, this->operation))
        throw std::invalid_argument("Error: parámetros incorrectos");

    // bucle que nos permitirá operar cada imagen del dir de entrada
    for (auto const& currentFile : std::filesystem::directory_iterator{this->inDirectory}) {
        // Actualizamos el archivo actual
        // Rellenamos los pixeles llama a leerBMP()
        this->llenarPixeles(currentFile.path());
        // Realizar operacion seleccionada
        this->realizarOperacion();
    }
    std::cout << "Ejecución finalizada con exito" << std::endl;
}

void Imageaos::llenarPixeles(const std::string filePath) {
    /* Función encargada de llenar el array con los pixeles del
     * archivo BMP de comun*/

    int num_pixeles = 0;
    int* pixeles;
    contenido_BMP header;
    // Leemos el header y abrimos el archivo en el que nos encontramos
    header = leerHeaderBMP(filePath);
    num_pixeles = header.tamano;
    pixeles = leerArrayBMP(header);

    for (int i=0; i<num_pixeles; i += 3) {
        this->arrayPixeles[i].Red = pixeles[i];
        this->arrayPixeles[i + 1].Green = pixeles[i + 1];
        this->arrayPixeles[i + 2].Blue = pixeles[i + 2];
    }
}

void Imageaos::realizarOperacion() {

    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;

    // Función encargada de realizar la operación
    if (this->operation == "gauss"){
        t_inicio = std::chrono::high_resolution_clock::now();
        this->difusionGaussiana();
        t_fin = std::chrono::high_resolution_clock::now();
        this->time.gaussTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->operation == "histo"){
        t_inicio = std::chrono::high_resolution_clock::now();
        this->histograma();
        t_fin = std::chrono::high_resolution_clock::now();
        this->time.histoTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->operation == "copy"){
        t_inicio = std::chrono::high_resolution_clock::now();
        this->copiarImagen();
        t_fin = std::chrono::high_resolution_clock::now();
        this->time.copyTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->operation == "mono"){
        t_inicio = std::chrono::high_resolution_clock::now();
        this->escalaGrises();
        t_fin = std::chrono::high_resolution_clock::now();
        this->time.monoTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////

void Imageaos::copiarImagen() {
    /* Función encargada de copiar la imagen actual en el directorio de salida*/

    // establecemos offstream con la ruta al archivo destino
    std::ofstream archivo;
    archivo.open(rutaArchivoSalida("bmp", this->outDirectory, this->actualFile), std::ofstream::out);

    if (!archivo.is_open()) {
        throw std::invalid_argument("Error: al abrir el archivo destino");
    }

    // Escribimos el header en el archivo origen
    archivo << this->header_BMP;

    // Escribimos los pixeles, recorriendo todo el array
    for (int i=0; i<this->imagen_BMP.anchura * this->imagen_BMP.anchura; ++i) {
        // Recordar que en un archivo BMP los pixeles van en orden BGR
        archivo << this->arrayPixeles[i].Blue;
        archivo << this->arrayPixeles[i].Green;
        archivo << this->arrayPixeles[i].Red;
        // Añadir padding al final de liena en caso de que exista
    }
    // Cerramos el archivo de salida
    archivo.close();
}

void Imageaos::histograma() {
    /* Función encargada de crear el histograma y pasarselos al la
     * función de comon histrograma*/

    int R[256] = { 0 };
    int G[256] = { 0 };
    int B[256] = { 0 };

    // Inicializamos el vector RGB a cero
    std::vector<int> RGB;
    for (int i=0; i<768; ++i) {
        RGB.push_back(0);
    }

    // Sumamos un a cada valor de 0 a 256 de los arrays en caso de aparaición
    for (int i=0; i<this->imagen_BMP.altura * this->imagen_BMP.anchura ; ++i) {
        R[this->arrayPixeles[i].Red]++;
        G[this->arrayPixeles[i].Green]++;
        B[this->arrayPixeles[i].Blue]++;
    }

    // Con los valores anteriores llenamos el vector RGB
    for (int i=0; i<256; ++i) {
        RGB[i] = R[i];
        RGB[256 + i] = G[i];
        RGB[512 + i] = B[i];
    }

    // Llamamos a la pare comun del histograma
    histograma(RGB, rutaArchivoSalida("hst", this->outDirectory, this->actualFile));
}



void Imageaos::escalaGrises(){ // revisar
    /* Función encargada de hacer la transformación de grises de una imagen*/

    float cR = 0;
    float cG = 0;
    float cB = 0;
    float cg = 0;
    float g = 0;

    // paso 1 normalizacion
    for (int i=0; i<this->imagen_BMP.anchura * this->imagen_BMP.altura; ++i) {
            cR = transformacionLineal(this->arrayPixeles[i].Red / 255); // transformacion lineal de los 3 colores
            cG = transformacionLineal(this->arrayPixeles[i].Green / 255);
            cB = transformacionLineal(this->arrayPixeles[i].Blue / 255);
            cg = correccionGama(cR, cG, cB); // sacada ahorro lineas
            g = cg * 255; // se vuelve a escala de 256 solucion por cada 3 pixeles
            this->arrayPixeles[i].Red = g; // se guardan los pixeles en el char todos el mismo
            this->arrayPixeles[i].Green = g; // se guardan los pixeles en el char todos el mismo
            this->arrayPixeles[i].Blue = g; // se guardan los pixeles en el char todos el mismo
    }
    // Copiamos la imagen en el directorio de salida
    this->copiarImagen();
}

//gauss aos
void Imageaos::difusionGaussiana() {
    int altura = this->imagen_BMP.anchura;
    int anchura = this->imagen_BMP.anchura;
    int tmpR, tmpG, tmpB; // variables auxiliares
    int l = anchura * 3; // pixeles por fila
    int tamano = altura * l; // tamaño total en bytes
    int cByte, b, cGauss, fGauss; // columna byte, byte, columna gauss, fila gauss
    for (int i = 0; i < altura - 1; i += 1){
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
            tmpR = tmpR / w; // se divide entre el peso
            tmpG = tmpG / w;
            tmpB = tmpB / w;
            this->arrayPixeles[i].Red = tmpR; // se guardan los pixeles en el array de pixeles
            this->arrayPixeles[i].Green = tmpG;
            this->arrayPixeles[i].Blue = tmpB;
        }
    }
    this->copiarImagen();
}
