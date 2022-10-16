//
//
//

#include "progargs.h"

// Constructor & Destructor
Common::Common(int type, int num_args, String argv_1, String argv_2, String argv_3) {
    // En caso de que los argumentos sean correctos continuamos construyendo
    if (this->comprobarArg(num_args, argv_1, argv_2, argv_3))
    {
        // Damos valor a los argumentos de la clase
        this->inDirectory = argv_1;
        this->outDirectory = argv_2;
        this->operation = argv_3;
        // Chekear que esto no de error (puede ser nullptr)
        this->diread = NULL;
        // Esta variable define si utilizaremos el soa (0) o el aos (1)
        this->type = type;
        this->header = "";

       // Continuamos con la ejecución del programa
       this->realizarOperacion();
    }

}

bool Common::comprobarArg(int num_args, String argv_1, String argv_2, String argv_3) {
    /* Función encargada de validar los argumentos introducidos,
     * devuelve false en caso de que algun arg sea incorrecto*/

    bool arg_correctos = true;

    // comprobamos que el numero de argumentos sea el correcto
    if (num_args != 3) {
        cout << "Wrong format:" << "\n";
        cout << "Image in_path out_path oper" << "\n";
        cout << "Operation: copy, histo, mono, gauss" << "\n";
        arg_correctos = false;
    }
    // comprobamos que la accion a realizar sea la indicada
    if (argv_3 != "gauss" || argv_3 != "histo" || argv_3 != "mono" || argv_3 != "copy") {
        cout << "Unexpected operation: " << argv_3 << "\n";
        cout << "Image in_path out_path oper" << "\n";
        cout << "Operation: copy, histo, mono, gauss" << "\n";
        arg_correctos = false
    }
    // comprobamos si existen los directorios de entrada y salida
    if (!opendir(argv_1)) {
        cout << "Input path: " << argv_1 << "\n";
        cout << "Output path: " << argv_2 << "\n";
        cout << "Cannot open directory " << "[" << argv_1 << "]" << "\n";
        cout << "Image in_path out_path oper" << "\n";
        cout << "Operation: copy, histo, mono, gauss" << "\n";
        arg_correctos = false;
    }
    if (!opendir(argv_2)) {
        cout << "Input path: " << argv_1 << "\n";
        cout << "Output path: " << argv_2 << "\n";
        cout << "Output directory " << "[" << argv_2 << "]" << " does not exist" << "\n";
        cout << "Image in_path out_path oper" << "\n";
        cout << "Operation: copy, histo, mono, gauss" << "\n";
        arg_correctos = false;
    }

    return arg_correctos;
}

void Common::realizarOperacion(){
    /* Finción que se va a encargar de funcionamiento
     * principal del programa, a cargo de llamar a
     * las funciones que realizarán las operaciones
     * necesarias */

    DIR* direntrada;
    struct dirent* diread;

    // Comoprobamos que el directorio de entrada se abre correctamente
    if ((direntrada = opendir(this->inDirectory)) == NULL) {
        throw"Error: abriendo el directorio de entrada";
    }

    // Bucle while que ejecutará las operaciones sobre
    // cada fotografía del directorio de entrada
    while ((diread = readdir(direntrada)) != NULL) {
        // Para no pasar punteros entre funciones
        // utilizamos el atrib this->diread
        this->diread = diread;
        this->leerBMP();
        if (this->operation == "copy") {
            this->copiarImagen();
        }
        if (this->operation == "histo") {

        }
        if (this->operation == "mono") {

        }
        if (this->operation == "gauss") {

        }
    }
    closedir(direntrada);
}

void Common::leerBMP(){
    // se abre el archivo bmp
    // COMPROBAR SI this->diread.name CONTINE LA RUTA ABSOLUTA AL ARCHIVO
    FILE* file = fopen(this->diread->d_name, "rb");
    // si no existe se lanza excepcion
    if (file == NULL){
        throw "Error: no se pudo encontrar el archivo imagen dentro del directorio";
    }

    // se leen del archivo de entrada
    fread(this->header, sizeof(unsigned char), 54, file);
    // comprobamos los valores de compresion = 0, numero de planos = 1, t de punto = 24
    if ((*(int*)&this->header[30]) != 0){
        throw "Valor de compresión invalido";
    }
    if ((*(int*)&this->header[26]) != 1){
        throw "Número de nivel invalido";
    }
    if ((*(int*)&this->header[24]) != 24){ // esto alomejor es cada punto de toda la imagen y no se si tendria q ir en el bucle
        throw "Punto de nivel invalido";
    }
    // Obtenemos la altura y la anchura del header (estan los bytes en la tabla del pdf)
    int anchura = *(int*)&this->header[18];
    int altura = *(int*)&this->header[22];
    // Comprobamos los valores
    cout << endl;
    cout << "Nombre: " << this->diread.name << endl;
    cout << "Anchura: " << anchura << endl;
    cout << "Altura: " << altura << endl;

    // Continuamos con la lectura
    int fila = (anchura*3 + 3) & (~3);
    unsigned char aux; // variable ayuda a reordenar los pyxeles de BGR a RGB
    unsigned char* datos_imagen = unsigned char[fila];
    int R;
    int G;
    int B;
    // Lectura de la imagen
    for (int i = 0; i < altura; i++) {
        fread(datos_imagen, sizeof(unsigned char), fila, file);
        for (int j = 0; j < anchura * 3; j += 3) {
            // es por tres ya que son tres: RGB; se reordenan
            aux = datos_imagen[j];
            datos_imagen[j] = datos_imagen[j + 2];
            datos_imagen[j + 2] = aux;
            // R
            R = (int)datos_imagen[j];
            // G
            G = (int)datos_imagen[j + 1];
            // B
            B = (int)datos_imagen[j + 2];
            // Formamos las estructuras de datos con sus correspondientes pixeles
            // En caso de que sea la ejecución del tipo soa (type = 0)
            if (this->type == 0) {
                this->imageSoa.addPixel(&R, &G, &B);
            }
            // En caso de que sea la ejecución del tipo aos (type = 1)
            else {
                this->imageAos.addPixel(&R, &G, &B);
            }
        }
    }
    fclose(file);
};

// Operaciones de la aplicación

void Common::copiarImagen() {
    /* Función que implementa la copia
     * de imagenes, para ello crea un nuevo archivo*/

    // NO SE SI CONCATENAR CHAR ASI FUNCIONARA
    ofstream outfile(this->outDirectory + "/" + this->diread->d_name + "_copia.bmp");

    // Añadimos el header
    outfile << this->header;

    // Hacer un bucle para meter todos los pixeles uno por uno
    // OJO: ordenarlos como antes estaban ordenados BGR
    for (int i=0; i<){

    }
    outfile.close();
}

void Common::histograma() {
    /* Función encargada de crear el histograma,
     * para lo que deberá crear un archivo .hst*/

    // Histograma R, G, B
    int R[256], G[256], B[256];

    // Creamos el nuevo archivo en el dir de salida
    ofstream outfile(this->outDirectory + "/" + this->diread->d_name + ".hst");

    // Calculo de los histogramas

    // Añadimos la información de los histogramas al archivo .hst
    for (int i=0; i<256*3; ++i) {
        outfile << ;
    }

    outfile.close();
}

void Common::escalaGrises() {

}

void Common::difusionGaussiana() {

}
