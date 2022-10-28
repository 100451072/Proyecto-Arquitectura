//
//
//

#include "imagesoa.h"

//Constructor & Destructor
Imagesoa::Imagesoa(int num_args, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3) {
    /* Constructor, recibe tres vectores que conformarán
     * el structurePixels*/
    // Inicialización de los atributos de common
    this->numArgumentos = num_args;
    this->inDirectory = arg_1;
    this->outDirectory = arg_2;
    this->operation = arg_3;
    this->actualFile = "";
}

void Imagesoa::executeProgram() {
    /* Función principal encargada de la ejecución del programa*/

    // Almacen de valores importantes
    contenido_BMP imagen;
    // Almacen de todo el archivo para poder copiar
    std::vector<BYTE> array_BMP;

    // Comenzamos comprobando los argumentos de entrada
    if (!comprobarArg(this->numArgumentos, this->inDirectory, this->outDirectory, this->operation))
        throw std::invalid_argument("Error: parámetros incorrectos");

    // bucle que nos permitirá operar cada imagen del dir de entrada
    for (auto const &currentFile: std::filesystem::directory_iterator{this->inDirectory}) {
        // Actualizamos el archivo actual
        this->actualFile = currentFile.path();
        // Rellenamos los pixeles llama a leerBMP()
        imagen = this->llenarPixeles(array_BMP);
        // Realizar operacion seleccionada
        this->realizarOperacion(imagen, array_BMP);
    }
    std::cout << "Ejecución finalizada con exito" << std::endl;
}

contenido_BMP Imagesoa::llenarPixeles(std::vector<BYTE>& array_BMP) {
    /* Función encargada de llenar el array con los pixeles del
     * archivo BMP de comun*/

    int* pixeles;
    contenido_BMP header;
    // Leemos el header y abrimos el archivo en el que nos encontramos
    header = leerHeaderBMP(this->actualFile, array_BMP);
    int num_pixeles = (int)header.anchura * (int)header.altura;
    // Recibe como parametro una referencia a un array
    pixeles = leerArrayBMP(header);

    // El vector pixeles es tres veces más largo que structPixeles, por eso
    // lo recorremos asi
    for (int i=0; i<num_pixeles * 3; i += 3) {
        // Añadimos los pixeles al array
        this->structPixels.arrayR[i/3] = pixeles[i];
        this->structPixels.arrayG[i/3] = pixeles[i + 1];
        this->structPixels.arrayB[i/3] = pixeles[i + 2];
    }

    return header;
}

void Imagesoa::realizarOperacion(contenido_BMP imagen_BMP, std::vector<BYTE>& array_BMP) {
    // Función encargada de realizar la operación

    std::chrono::high_resolution_clock::time_point t_inicio, t_fin;

    // Función encargada de realizar la operación
    if (this->operation == "gauss"){
        t_inicio = std::chrono::high_resolution_clock::now();
        this->difusionGaussiana(imagen_BMP, array_BMP);
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
        this->copiarImagen(imagen_BMP, array_BMP);
        t_fin = std::chrono::high_resolution_clock::now();
        this->time.copyTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
    if (this->operation == "mono"){
        t_inicio = std::chrono::high_resolution_clock::now();
        this->escalaGrises(imagen_BMP, array_BMP);
        t_fin = std::chrono::high_resolution_clock::now();
        this->time.monoTime = std::chrono::duration_cast<std::chrono::microseconds>(t_fin - t_inicio).count();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Imagesoa::copiarImagen(contenido_BMP imagen_BMP, std::vector<BYTE>& array_BMP) {
    /* Función encargada de copiar la imagen actual en el directorio de salida,
     * de forma que se puede utilizar para escribir la imagen despues de realizar
     * cualquier operacion previamente*/

    int anchura = (int)imagen_BMP.anchura;
    int altura = (int)imagen_BMP.altura;
    int inicio = (int)imagen_BMP.dir_datos_imagen;
    int padding = (int)imagen_BMP.t_padding;
    // establecemos offstream con la ruta al archivo destino
    std::ofstream archivo;

    // Actualizamos el array_BMP con los nuevos valores de pixel
    for (int i=0; i<altura; ++i) {
        for (int j=0; j<anchura * 3; ++j) {
            // Importante: en BMP se guardan en orden BGR
            array_BMP[inicio + i * (anchura * 3 + padding) + j + 2] = (BYTE)this->structPixels.arrayR[i*anchura + j/3];
            array_BMP[inicio + i * (anchura * 3 + padding) + j + 1] = (BYTE)this->structPixels.arrayG[i*anchura + j/3];
            array_BMP[inicio + i * (anchura * 3 + padding)  + j] = (BYTE)this->structPixels.arrayB[i*anchura + j/3];
        }
    }
    // Abrimos el archivo de salida
    archivo.open(rutaArchivoSalida("bmp", this->outDirectory, this->actualFile), std::ofstream::out);

    // Comprobamos si se abre
    if (!archivo.is_open()) {
        throw std::invalid_argument("Error: al abrir el archivo destino");
    }

    // Añadimos el array_BMP al archivo de salida
    for (int i=0; i<imagen_BMP.tamano; ++i) {
        archivo.write(reinterpret_cast<const char *>(array_BMP[i]), sizeof(BYTE));
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

    std::string outFile = rutaArchivoSalida("hst", this->outDirectory, this->actualFile);

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
    histograma_aux(RGB, outFile);
}

void Imagesoa::escalaGrises(contenido_BMP imagen_BMP, std::vector<BYTE>& array_BMP) { // revisar
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
    this->copiarImagen(imagen_BMP, array_BMP);
}

void Imagesoa::difusionGaussiana(contenido_BMP imagen_BMP, std::vector<BYTE>& array_BMP) {
    /* Función encargada de realizar la difusion gaussiana sobre
    la imagen de entrada*/

    int anchura = (int)imagen_BMP.anchura;
    int altura = (int)imagen_BMP.altura;
    int total = anchura*altura;

    // Copia del resultado de la transformacion para no afectar a los siguientes valroes
    int temp1[MAX_SIZE] = {0};
    int temp2[MAX_SIZE] = {0};
    int temp3[MAX_SIZE] = {0};

    // Recorremos el array de pixeles por completo
    for (int i=0; i<total; ++i) {
        //Filas
        for (int k=-2; k<2; ++k) {
            // Columnas
            for (int l=-2; l<2; ++l) {
                // Nos desplazamos en el array de pixeles obteniendo las pos requeridas
                // Para que los pixeles de fuera sumen cero, comprobamos cuando los valores se salen de la matriz
                if ((0 <= i % anchura + l < anchura) && (0 <= i / anchura + k < altura)) {
                    // Multiplicar por el valor anchura nos permite desplazarnos entre las filas
                    temp1[i] += mGauss[k + 3][l + 3] * this->structPixels.arrayR[i + (anchura * k + l)];
                    temp2[i] += mGauss[k + 3][l + 3] * this->structPixels.arrayG[i + (anchura * k + l)];
                    temp3[i] += mGauss[k + 3][l + 3] * this->structPixels.arrayB[i + (anchura * k + l)];
                }
            }
        }
        // Dividimos entre w
        temp1[i] /= 273;
        temp2[i] /= 273;
        temp3[i] /= 273;
    }
    // Asignamos al array global sus respectivos valores, no se puede hacer arriba
    // ya que alterariamos los siguientes valores
    for (int i=0; i<total; ++i) {
        this->structPixels.arrayR[i] = temp1[i];
        this->structPixels.arrayG[i] = temp2[i];
        this->structPixels.arrayB[i] = temp3[i];
    }
    // Finalmente creamos el archivo de salida
    this->copiarImagen(imagen_BMP, array_BMP);
}