//
//
//

#include "imageaos.h"
#include "../common/progargs.h"

#include <utility>


// Constructor & Destructor
Imageaos::Imageaos(int num_args, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3) {
    /* Constructor, encargado de asigar a cada nodo de arrayPixeles
     * su valor de R, G, B*/

    this->numArgumentos = num_args;
    this->inDirectory = arg_1;
    this->outDirectory = arg_2;
    this->operation = arg_3;
    this->actualFile = "";
}

void Imageaos::executeProgram() {
    /* Función principal encargada de la ejecución del programa*/

    // Guardar valres importantes
    contenido_BMP imagen;
    // Guardar todo el archivo
    std::vector<BYTE> archivo_BMP;

    // Comenzamos comprobando los argumentos de entrada
    if (!comprobarArg(this->numArgumentos, this->inDirectory, this->outDirectory, this->operation))
        throw std::invalid_argument("Error: parámetros incorrectos");

    // bucle que nos permitirá operar cada imagen del dir de entrada
    for (auto const& currentFile : std::filesystem::directory_iterator{this->inDirectory}) {
        // Actualizamos el archivo actual
        this->actualFile = currentFile.path();
        // Rellenamos los pixeles llama a leerBMP()
        imagen = this->llenarPixeles(archivo_BMP);
        // Realizar operacion seleccionada
        this->realizarOperacion(imagen, archivo_BMP);
    }
    std::cout << "Ejecución finalizada con exito" << std::endl;
}

void Imageaos::llenarPixeles(std::vector<BYTE>& archivo_BMP) {
    /* Función encargada de llenar el array con los pixeles del
     * archivo BMP de comun*/

    int num_pixeles = 0;
    int* pixeles;
    contenido_BMP header;
    // Leemos el header y abrimos el archivo en el que nos encontramos
    header = leerHeaderBMP(this->actualFile, archivo_BMP);
    num_pixeles = header.tamano;
    pixeles = leerArrayBMP(header);

    for (int i=0; i<num_pixeles; i += 3) {
        this->arrayPixeles[i].Red = pixeles[i];
        this->arrayPixeles[i + 1].Green = pixeles[i + 1];
        this->arrayPixeles[i + 2].Blue = pixeles[i + 2];
    }
}

void Imageaos::realizarOperacion(contenido_BMP imagen_BMP, std::vector<BYTE>& array_BMP) {

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

//////////////////////////////////////////////////////////////////////////////////////////////

void Imageaos::copiarImagen(contenido_BMP imagen_BMP, const std::vector<BYTE>& array_BMP) {
    /* Función encargada de copiar la imagen actual en el directorio de salida,
     * de forma que se puede utilizar para escribir la imagen despues de realizar
     * cualquier operacion previamente*/

    // Iterador para ir llenando cada posición del archivo
    int i = 0;

    // establecemos offstream con la ruta al archivo destino
    std::ofstream archivo;
    archivo.open(rutaArchivoSalida("bmp", this->outDirectory, this->actualFile), std::ofstream::out);

    if (!archivo.is_open()) {
        throw std::invalid_argument("Error: al abrir el archivo destino");
    }

    // Escribimos el header en el archivo origen solo hasta la dirección de inicio de pixeles
    for (i; i<imagen_BMP.dir_datos_imagen; ++i) {
        archivo.write(reinterpret_cast<const char *>(array_BMP[i]), sizeof(BYTE));
    }

    // Escribimos los pixeles, recorriendo todo el array
    for (i; i<imagen_BMP.anchura * imagen_BMP.anchura; ++i) {
        // Recordar que en un archivo BMP los pixeles van en orden BGR
        archivo << this->arrayPixeles[i].Blue;
        archivo << this->arrayPixeles[i].Green;
        archivo << this->arrayPixeles[i].Red;
        if (fin_linea) {
            // Añadir padding al final de liena en caso de que exista
            archivo << imagen_BMP.t_padding;
        }
    }

    // Añadimos la parte de después del array de pixeles en caso de que exista
    for (i; i<imagen_BMP.tamano; ++i) {
        archivo.write(reinterpret_cast<const char *>(array_BMP[i]), sizeof(BYTE));
    }

    // Cerramos el archivo de salida
    archivo.close();
}

void Imageaos::histograma(contenido_BMP imagen_BMP) {
    /* Función encargada de crear el histograma y pasarselos al la
     * función de comon histrograma*/

    int R[256] = { 0 };
    int G[256] = { 0 };
    int B[256] = { 0 };

    // Inicializamos el vector RGB a cero
    std::vector<int> RGB(768);

    // Sumamos un a cada valor de 0 a 256 de los arrays en caso de aparaición
    for (int i=0; i<imagen_BMP.altura * imagen_BMP.anchura ; ++i) {
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

void Imageaos::escalaGrises(contenido_BMP imagen_BMP, std::vector<BYTE>& arraY_BMP){ // revisar
    /* Función encargada de hacer la transformación de grises de una imagen*/

    float cR = 0;
    float cG = 0;
    float cB = 0;
    float cg = 0;
    float g = 0;

    // paso 1 normalizacion
    for (int i=0; i<imagen_BMP.anchura * imagen_BMP.altura; ++i) {
            cR = transformacionLineal(this->arrayPixeles[i].Red / 255); // transformacion lineal de los 3 colores
            cG = transformacionLineal(this->arrayPixeles[i].Green / 255);
            cB = transformacionLineal(this->arrayPixeles[i].Blue / 255);
            cg = correccionGama(cR, cG, cB); // sacada ahorro lineas
            g = cg * 255; // se vuelve a escala de 256 solucion por cada 3 pixeles
            this->arrayPixeles[i].Red =  static_cast<int>(g); // se guardan los pixeles en el char todos el mismo
            this->arrayPixeles[i].Green = static_cast<int>(g); // se guardan los pixeles en el char todos el mismo
            this->arrayPixeles[i].Blue = static_cast<int>(g); // se guardan los pixeles en el char todos el mismo
    }
    // Copiamos la imagen en el directorio de salida
    this->copiarImagen(imagen_BMP, arraY_BMP);
}

//gauss aos
void Imageaos::difusionGaussiana(contenido_BMP imagen_BMP, std::vector<BYTE>& arraY_BMP) {
    /* Función encargada de realizar la difusion gaussiana sobre
    la imagen de entrada*/

    int anchura = imagen_BMP.anchura;
    int altura = imagen_BMP.altura;
    int total = anchura*altura;

    int temp1[imagen_BMP.anchura*imagen_BMP.altura] = {0};
    int temp2[imagen_BMP.anchura*imagen_BMP.altura] = {0};
    int temp3[imagen_BMP.anchura*imagen_BMP.altura] = {0};

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
                    temp1[i] += mGauss[k + 3][k + 3] * this->arrayPixeles[i + (anchura * k + l)].Red;
                    temp2[i] += mGauss[k + 3][k + 3] * this->arrayPixeles[i + (anchura * k + l)].Green;
                    temp3[i] += mGauss[k + 3][k + 3] * this->arrayPixeles[i + (anchura * k + l)].Blue;
                }
            }
        }
        // Dividimos entre w
        temp1[i] /= 273;
        temp2[i] /= 273;
        temp3[i] /= 273;
    }
    // Asignamos al array global sus respectivos valores, no se puede hacer en el bucle de arriba
    // ya que alterariamos el calculo de los siguientes valores
    for (int i=0; i<total; ++i) {
        this->arrayPixeles[i].Red = temp1[i];
        this->arrayPixeles[i].Green = temp2[i];
        this->arrayPixeles[i].Blue = temp3[i];
    }
    // Finalmente creamos el archivo de salida
    this->copiarImagen(imagen_BMP, arraY_BMP);
}
