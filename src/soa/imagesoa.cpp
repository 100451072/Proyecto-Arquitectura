//
//
//

#include "imagesoa.h"

//Constructor & Destructor
Imagesoa::Imagesoa(int num_args, std::string arg_1, std::string arg_2, std::string arg_3) {
    /* Constructor, recibe tres vectores que conformarán
     * el structurePixels*/
    // Inicialización de los atributos de common
    this->comun.numArgumentos = num_args;
    this->comun.inDirectory = arg_1;
    this->comun.outDirectory = arg_2;
    this->comun.operation = arg_3;
}

void Imageaos::executeProgram() {
    /* Función principal encargada de la ejecución del programa*/

    // Comenzamos comprobando los argumentos de entrada
    if (!this->comun.comprobarArg())
    {
        throw"Error: parametros incorrectos";
    }
    for (this->comun.inDir : std::filesystem::directory_iterator{this->comun.inDirectory}) {
        // Actualizamos el archivo actual
        this->comun.actualFile = this.comun.inDir.path();
        // Rellenamos los pixeles llama a comun.leerBMP()
        this->llenarPixeles();
        // Realizar operacion seleccionada
        this->realizarOperacion();
    }
}

void Imagesoa::llenarPixeles() {
    /* Función encargada de llenar el array con los pixeles del
     * archivo BMP de comun*/

    int num_pixeles = 0;
    int* pixeles;
    // Leemos el header y abrimos el archivo en el que nos encontramos
    num_pixeles = this->comun.leerHeaderBMP();
    // Recibe como parametro una referencia a un array
    pixeles = this->comun.leerArrayBMP();

    for (int i=0; i<num_pixeles; i += 3) {
        // Añadimos los pixeles al array
        this->structurePixels.arrayR[i] = pixeles[i];
        this->structurePixels.arrayG[i + 1] = pixeles[i + 1];
        this->structurePixels.arrayB[i + 2] = pixeles[i + 2];
    }
    std::cout << "Ejecución finalizada con exito" << std::endl;
}

void realizarOperacion() {
    // Función encargada de realizar la operación
    if (this->comun.operation == "gauss"){
        t_inicio = std::chrono::high_resolution_clock::now();
        unsigned char *img = difusionGaussiana(inputPixeles, achura, altura);
        t_fin = std::chrono::high_resolution_clock::now();
        time -> gaussTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->comun.operation == "histo"){
        t_inicio = std::chrono::high_resolution_clock::now();
        unsigned char *img = histograma(imagen);
        t_fin = std::chrono::high_resolution_clock::now();
        time -> histoTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->comun.operation == "copy"){
        t_inicio = std::chrono::high_resolution_clock::now();
        unsigned char *img = copiarImagen(imagen);
        t_fin = std::chrono::high_resolution_clock::now();
        time -> copyTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->comun.operation == "mono"){
        t_inicio = std::chrono::high_resolution_clock::now();
        unsigned char *img = this->escalaGrises(imagen);
        t_fin = std::chrono::high_resolution_clock::now();
        time -> monoTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void copiarImagen() {
    /* Función encargada de copiar la imagen actual en el directorio de salida*/

    // establecemos offstream con la ruta al archivo destino
    std::ofstream archivo.open(rutaArchivoSalida("bmp", this->comun.outDirectory, this->comun.actualFile), std::ofstream::out);

    if (!archivo.is_open()) {
        throw"Error: al abrir el archivo destino";
    }

    // Escribimos el header en el archivo origen
    archivo << this->comun.header_BMP;

    // Escribimos los pixeles, recorriendo todo el array
    for (int i=0; i<this->comun.imagen_BMP.anchura * this->comun.imagen_BMP.anchura; ++i) {
        // Recordar que en un archivo BMP los pixeles van en orden BGR
        archivo << this->arrayPixeles.arrayB[i];
        archivo << this->arrayPixeles.arrayG[i];
        archivo << this->arrayPixeles.arrayR[i];
        // Añadir padding al final de liena en caso de que exista
    }
    // Cerramos el archivo de salida
    archivo.close();
}

void histograma() {
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
    for (int i=0; i<this->comun.imagen_BMP.altura * this->comun.imagen_BMP.anchura ; ++i) {
        R[this->structPixeles.arrayR[i]]++;
        G[this->structPixeles.arrayG[i]]++;
        B[this->structPixeles.arrayB[i]]++;
    }

    // Con los valores anteriores llenamos el vector RGB
    for (int i=0; i<256; ++i) {
        RGB[i] = R[i];
        RGB[256 + i] = G[i];
        RGB[512 + i] = B[i];
    }

    // Llamamos a la pare comun del histograma
    histograma(RGB, rutaArchivoSalida("hst", this->comun.outDirectory, this->comun.actualFile));
}

void escalaGrises(BMP data, std::string ruta_salida){ // revisar
    /* Función encargada de hacer la transformación de grises de una imagen*/

    float cR = 0;
    float cG = 0;
    float cB = 0;

    // paso 1 normalizacion
    for (int i=0; i<this->comun.imagen_BMP.anchura * this->comun.imagen_BMP.altura; ++i) {
        cR = transformacionLineal(this->structPixeles.arrayRed[i] / 255); // transformacion lineal de los 3 colores
        cG = transformacionLineal(this->structPixeles.arrayGreen[i] / 255);
        cB = transformacionLineal(this->structPixeles.arrayBlue[i] / 255);
        cG = correccionGamma(cR, cG, cB); // sacada ahorro lineas
        cG *= 255; // se vuelve a escala de 256 solucion por cada 3 pixeles
        this->structPixeles.arrayRed[i] = cG; // se guardan los pixeles en el char todos el mismo
        this->structPixeles.arrayGreen[i] = cG; // se guardan los pixeles en el char todos el mismo
        this->structPixeles.arrayBlue[i] = cG; // se guardan los pixeles en el char todos el mismo
    }
    this->copiarImagen();
}






























































// lo qe supongo q cambiaria es al abrir la imagen o al pasar los pixeles
void difusionGaussiana(BMP data, std::string ruta_salida) {
    int anchura = data.anchuraInicial;
    int altura = data.altura_inicial;
    int inputPixels = data.infoImagen;
    Pixel pixel;
    int avgR, avgG, avgB;
    int l = anchura * 3;
    int tamano = altura * l;
    int cByte, b, cGauss, fGauss;
    std::string pixelesDevolver;
    for (int i = 0; i < alturaInicial - 1; i+=1){
        for (int j = 0; i < l - 1; j+=3){
            int tmpR = 0;
            int tmpG = 0;
            int tmpB = 0;
            for (int s = -2; s <= 2; s++){
                for (int t = -2; t <= 2; t++){
                    fGauss = s + 2;
                    cByte = j + t * 3;
                    cGauss = t + 2;
                    b = (i + s)*l + cByte;
                    if (b >= 0 && cByte <= l - 1 && b <= tamano && 0 <= cByte) // PIXEL R
                        tmpR += matriz[fGauss][cGauss] * inputPixels[b];

                    if (b >= 0 && cByte <= l - 1 && b <= tamano && 0 <= cByte) // PIXEL G
                        tmpG += matriz[fGauss][cGauss] * inputPixels[b];
                    b += 1;
                    cByte += 1;
                    if (b >= 0 && cByte <= l - 1 && b <= tamano && 0 <= cByte) // PIXEL B
                        tmpB+= matriz[fGauss][cGauss] * inputPixels[b];
                    b += 1;
                    cByte += 1;
                }
            }
            // ver como hacer en soa (añadir en array)
            avgR = avgR / w; // se divide entre el peso
            avgG = avgG / w;
            avgB = avgB / w;
            pixel.arrayR[i] = avgR; // dudas de como
            pixel.arrayB[i+1] = avgG;
            pixel.arrayG[i+2] = avgB;
            pixelesDevolver[(i*l) + j] = avgR; // se guardan los pixeles en el char
            pixelesDevolver[(i*l) + j + 1] = avgG;
            pixelesDevolver[(i*j) + j + 2] = avgB;
        }
    }
    ruta_salida.write(pixelesDevolver); // hacer funcion escribir
    return pixelesDevolver; // se devuelven los pixeles modificados
}