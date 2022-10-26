//
//
//

#include "imagesoa.h"

//Constructor & Destructor
Imagesoa::Imagesoa(int num_args, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3) {
    /* Constructor, recibe tres vectores que conformarán
     * el structurePixels*/
    // Inicialización de los atributos de common
    this->comun.numArgumentos = num_args;
    this->comun.inDirectory = arg_1;
    this->comun.outDirectory = arg_2;
    this->comun.operation = arg_3;
    this->actualFile = "";
}

void Imagesoa::executeProgram() {
    /* Función principal encargada de la ejecución del programa*/

    // Comenzamos comprobando los argumentos de entrada
    if (!comprobarArg(this->numArgumentos, this->inDirectory, this->outDirectory, this->operation))
        throw std::invalid_argument("Error: parámetros incorrectos");

    // bucle que nos permitirá operar cada imagen del dir de entrada
    for (auto const &currentFile: std::filesystem::directory_iterator{this->inDirectory}) {
        // Actualizamos el archivo actual
        this->actualFile = currentFile.path();
        // Rellenamos los pixeles llama a leerBMP()
        this->llenarPixeles();
        // Realizar operacion seleccionada
        this->realizarOperacion();
    }
    std::cout << "Ejecución finalizada con exito" << std::endl;
}

void Imagesoa::llenarPixeles() {
    /* Función encargada de llenar el array con los pixeles del
     * archivo BMP de comun*/

    int num_pixeles = 0;
    int* pixeles;
    contenido_BMP header;
    // Leemos el header y abrimos el archivo en el que nos encontramos
    header = leerHeaderBMP(this->actualFile);
    num_pixeles = header.tamano;
    // Recibe como parametro una referencia a un array
    pixeles = leerArrayBMP(header);

    for (int i=0; i<num_pixeles; i += 3) {
        // Añadimos los pixeles al array
        this->structPixels.arrayR[i] = pixeles[i];
        this->structPixels.arrayG[i + 1] = pixeles[i + 1];
        this->structPixels.arrayB[i + 2] = pixeles[i + 2];
    }
}

void Imagesoa::realizarOperacion(contenido_BMP imagen_BMP) {
    // Función encargada de realizar la operación

    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;

    // Función encargada de realizar la operación
    if (this->operation == "gauss"){
        t_inicio = std::chrono::high_resolution_clock::now();
        this->difusionGaussiana(imagen_BMP);
        t_fin = std::chrono::high_resolution_clock::now();
        this->time.gaussTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->operation == "histo"){
        t_inicio = std::chrono::high_resolution_clock::now();
        this->histograma(imagen_BMP);
        t_fin = std::chrono::high_resolution_clock::now();
        this->time.histoTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->operation == "copy"){
        t_inicio = std::chrono::high_resolution_clock::now();
        this->copiarImagen(imagen_BMP);
        t_fin = std::chrono::high_resolution_clock::now();
        this->time.copyTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->operation == "mono"){
        t_inicio = std::chrono::high_resolution_clock::now();
        this->escalaGrises(imagen_BMP);
        t_fin = std::chrono::high_resolution_clock::now();
        this->time.monoTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Imagesoa::copiarImagen(contenido_BMP imagen_BMP) {
    /* Función encargada de copiar la imagen actual en el directorio de salida*/

    // establecemos offstream con la ruta al archivo destino
    std::ofstream archivo;
    archivo.open(rutaArchivoSalida("bmp", this->outDirectory, this->actualFile), std::ofstream::out);

    if (!archivo.is_open()) {
        throw std::invalid_argument("Error: al abrir el archivo destino");
    }

    // Escribimos el header en el archivo origen
    archivo << imagen_BMP;

    // Escribimos los pixeles, recorriendo todo el array
    for (int i=0; i<this->imagen_BMP.anchura * this->imagen_BMP.anchura; ++i) {
        // Recordar que en un archivo BMP los pixeles van en orden BGR
        archivo << this->structPixels.arrayB[i];
        archivo << this->structPixels.arrayG[i];
        archivo << this->structPixels.arrayR[i];
        // Añadir padding al final de liena en caso de que exista
    }
    // Cerramos el archivo de salida
    archivo.close();
}

void Imagesoa::histograma(contenido_BMP imagen_BMP) {
    /* Función encargada de crear el histograma y pasarselos al la
     * función de comon histrograma*/

    int R[256] = { 0 };
    int G[256] = { 0 };
    int B[256] = { 0 };

    // Inicializamos el vector RGB a cero
    std::vector<int> RGB(768);

    // Sumamos un a cada valor de 0 a 256 de los arrays en caso de aparaición
    for (int i=0; i<imagen_BMP.altura * imagen_BMP.anchura ; ++i) {
        R[this->structPixels.arrayR[i]]++;
        G[this->structPixels.arrayG[i]]++;
        B[this->structPixels.arrayB[i]]++;
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

void Imagesoa::escalaGrises(contenido_BMP imagen_BMP){ // revisar
    /* Función encargada de hacer la transformación de grises de una imagen*/

    float cR = 0;
    float cG = 0;
    float cB = 0;
    float cg = 0;
    float g = 0;

    // paso 1 normalizacion
    for (int i=0; i<imagen_BMP.anchura * imagen_BMP.altura; ++i) {
        cR = transformacionLineal(this->structPixels.arrayR[i] / 255); // transformacion lineal de los 3 colores
        cG = transformacionLineal(this->structPixels.arrayG[i] / 255);
        cB = transformacionLineal(this->structPixels.arrayB[i] / 255);
        cg = correccionGama(cR, cG, cB); // sacada ahorro lineas
        g = cg * 255; // se vuelve a escala de 256 solucion por cada 3 pixeles
        this->structPixels.arrayR[i] = static_cast<int>(g); // se guardan los pixeles en el char todos el mismo
        this->structPixels.arrayG[i] =  static_cast<int>(g); // se guardan los pixeles en el char todos el mismo
        this->structPixels.arrayB[i] =  static_cast<int>(g); // se guardan los pixeles en el char todos el mismo
    }
    // Copiamos la imagen en el directorio de salida
    this->copiarImagen();
}

// funcion gauss para soa
void Imagesoa::difusionGaussiana() {
    int altura = this->comun.imagen_BMP.anchura;
    int anchura = this->comun.imagen_BMP.anchura;
    int tmpR, tmpG, tmpB; // pixeles auxiliares
    int l = anchura * 3; // pixeles por fila
    int tamano = altura * l; // tamaño total en bytes
    int cByte, b, cGauss, fGauss;
    for (int i = 0; i < altura- 1; i+=1){ // se recorre la altura
        for (int j = 0; j < l - 1; j+=3){ // se recorre en anchura
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
                        tmpR += mGauss[fGauss][cGauss] * this->structPixels.arrayR[b];

                    if (b >= 0 && cByte <= l - 1 && b <= tamano && 0 <= cByte) // PIXEL G
                        tmpG += mGauss[fGauss][cGauss] * this->structPixels.arrayG[b];
                    b += 1;
                    cByte += 1;
                    if (b >= 0 && cByte <= l - 1 && b <= tamano && 0 <= cByte) // PIXEL B
                        tmpB+= mGauss[fGauss][cGauss] * this->structPixels.arrayB[b];
                    b += 1;
                    cByte += 1;
                }
            }
            // ver como hacer en soa (añadir en array)
            tmpR = tmpR / w; // se divide entre el peso
            tmpG = tmpG / w;
            tmpB = tmpB / w;
            this->structPixels.arrayR[i] = tmpR;
            this->structPixels.arrayG[i] = tmpG;
            this->structPixels.arrayB[i] = tmpB;
        }
    }
    this->copiarImagen();

}
