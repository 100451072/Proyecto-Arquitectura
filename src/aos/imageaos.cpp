//
//
//

#include "imageaos.h"

// Constructor & Destructor
Imageaos::Imageaos(int num_args, std::string arg_1, std::string arg_2, std::string arg_3) {
    /* Constructor, encargado de asigar a cada nodo de arrayPixeles
     * su valor de R, G, B*/

    // Inicialización de los atributos de common
    this->comun.numArgumentos = num_args;
    this->comun.inDirectory = arg_1;
    this->comun.outDirectory = arg_2;
    this->comun.operation = arg_3;
}

void leerImagenBMP(std::string ruta){
    ifstream archivo; // para la lectura
    ruta_archivo = ruta;
    archivo.open(ruta, ios::binary|ios::in); // se abre el archivo
    if (!archivo){
        throw "Error abriendo imagen BMP";
    }
    archivo.read(reinterpret_cast<char*>(contenido_bmp), sizeof(contenido_bmp)); // se lee el header (contenido del bmp)
    // a continuacion obtenemos los valores de este contenido del bmp
    common::leerHeaderBMP();
    // usamos seekg para que la imagen no se desplace




}


void Imageaos::executeProgram() {
    /* Función principal encargada de la ejecución del programa*/

    // Comenzamos comprobando los argumentos de entrada
    if (!this->comun.comprobarArg())
    {
        throw"Error: parametros incorrectos";
    }
    // Bucle para ejecutar las ooperaciones sobre todas las fotos del dir
    // Obtenemos la primera pos del dir
    this->comun.abrirInDir();
    // leemos el dir de entrada por primera vez para que el bucle pueda empezar
    // en caso de que exista algun archivo
    this->comun.leerInDir();
    for (std::t_size i=0; i<this->comun.archivos.size(); ++i){
        // Leemos el archivo en fileRead
        this->comun.fileRead(this->comun.archivos(i));
        // Rellenamos los pixeles llama a comun.leerBMP()
        this->llenarPixeles();
        // Realizar operacion seleccionada
        this->realizarOperacion();
        // Avanzamos a la siguiente pos del dir
    }
    // Por ultimo cerramos el dir de entrada
    this->comun.cerrarInDir();
}

void llenarPixeles() {
    /* Función encargada de llenar el array con los pixeles del
     * archivo BMP de comun*/

    int num_pixeles = 0;
    int* pixeles;

    // Leemos el header y abrimos el archivo en el que nos encontramos
    num_pixeles = this->comun.leerHeaderBMP();
    pixeles = this->comun.leerArrayBMP();

    for (int i=0; i<num_pixeles; i += 3) {
        this->arrayPixeles[i].Red = pixeles[i];
        this->arrayPixeles[i + 1].Green = pixeles[i + 1];
        this->arrayPixeles[i + 2].Blue = pixeles[i + 2];
    }
    return pixeles;
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

void copiarImagen(std::string ruta, std::string archivo_escritura){
    // escrbir en la imagen sera distinto entre aos y soa
    boost::filesystem::path ruta; // toda la ruta
    nombre = filesystem::ruta.stem(); // nombre del archivo
    // establecemos offstream
    std::ofstream archivo;
    try{archivo.open(carpeta + "/" + nombre)}{ // obtenido de libreria filesystem error
    }
    catch(filesystem::filesystem_error){
        throw "Error abriendo";
    }
    // continuar para que escriba en tipo soa (no se si lo hemos hecho ya)
}

void histogram(std::string arhivo_salida) {
        // histograma
        int histo[768] = {0};
        for (Pixel pixel in pixels){
            histo[pixel.Red] ++;
            histo[pixel.Green + 256] ++;
            histo[pixel.Blue + 512] ++;
        }
        ofstream archivo;
        archivo.open( archivo_salida + "/" + nombre_archivo + ".hs", ios::trunc);
        for (int i = 0; i<768; i++){
            arhivo << histo[i] << endl;
        }
        archivo.close();
    }



// no es definitivo
void escribirPixel(int r, int g, int b, std::string pixeles){
    pixeles[indice].Red = static_cast<u_int8_t>(r);
    pixeles[indice].Green = static_cast<u_int8_t>(g);
    pixeles[indice].Blue = static_cast<u_int8_t>(b);
}



float transformacionLineal(float color){
    // funcion de transformacion lineal
    int cN;
    if (color <= 0.04045) {
        cN = color / 12.92;
    } else {
        cN = pow((color + 0.055) / 1.055, 2.4);
    return cN;
}

float correccionGamma(float cR, float cG, float cB){
    // funcion de correccion gamma
    int cl = 0.2126 * cR + 0.7152 * cG + 0.0722 * cB;
    if (cl <= 0.0031308) {
        int cg = 12.92 * cl;
    } else {
        int cg = (1.055 * pow(cl, 1 / 2.4)) - 0.055;
    }
    return cg;
}


void escalaGrises(BMP data, std::string ruta_salida){ // revisar
    Pixel pixel; // pixeles del aos .Color
    std::string pixelesDevolver = data.infoImagen; // char a devolver
    int l = anchuraInicial * 3;
    // paso 1 normalizacion
    for (int i = 0; i < alturaInicial - 1; i+=1) {
        for (int j = 0; i < l - 1; j += 3) {
            avgR = avgR / 255; // escala 0 a 1
            avgG = avgG / 255; // escala 0 a 1
            avgB = avgB / 255; // escala 0 a 1
            cR = transformacionLineal(avgR); // transformacion lineal de los 3 colores
            cB = transformacionLineal(avgB);
            cG = transformacionLineal(agbG);
            cg = correccionGamma(cR, cG, cB); // sacada ahorro lineas
            int g = cg * 255; // se vuelve a escala de 256 solucion por cada 3 pixeles
            pixelesDevolver[(i*l) + j] = g; // se guardan los pixeles en el char todos el mismo
            pixelesDevolver[(i*l) + j + 1] = g;
            pixelesDevolver[(i*j) + j + 2] = g;
        }
    }
    ruta_salida.write(pixelesDevolver); // se escriben en el archivo out
    return pixelesDevolver;
}

// lo qe supongo q cambiaria es al abrir la imagen o al pasar los pixeles
void difusionGaussiana(BMP data, std::string ruta_salida) {
        int anchura = data.anchuraInicial;
        int altura = data.altura_inicial;
        int inputPixels = data.infoImagen;
        Pixel pixel;
        int l = anchura * 3;
        int tamano = altura * l;
        int cByte, b, cGauss, fGauss;
        std::string pixelesDevolver;
        for (int i = 0; i < altura - 1; i+=1){
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
                            tmpB += matriz[fGauss][cGauss] * inputPixels[b];
                        b += 1;
                        cByte += 1;
                    }
                }
                pixel.Red = tmpR / w; // se divide entre el peso
                pixel.Green = tmpG / w;
                pixel.Blue = tmpB / w;
                pixelesDevolver[(i*l) + j] = pixel.Red; // se guardan los pixeles en el char
                pixelesDevolver[(i*l) + j + 1] = pixel.Green;
                pixelesDevolver[(i*j) + j + 2] = pixel.Blue;
            }
        }
        ruta_salida.write(pixelesDevolver);
        return pixelesDevolver; // se devuelven los pixeles modificados y habria que escribirlos en el archivo de entrada
}
