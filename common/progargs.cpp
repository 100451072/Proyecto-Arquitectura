//
//
//

#include "progargs.h"

// Funciones de inicializacion
bool Common::comprobarArg(int num_args, std::string argv_1, std::string argv_2, std::string argv_3) {
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

// Constructor & Destructor
Common::Common(int num_args, std::string argv_1, std::string argv_2, std::string argv_3) {
    // En caso de que los argumentos sean correctos continuamos construyendo
    if (this->comprobarArg(num_args, argv_1, argv_2, argv_3))
    {

    }

}

void Common::devolver_imagenes(char *directory){
    DIR *direntrada;
    struct dirent *diread;
    // al abrir ya se habra comprobado en la funcion comprobarArg
    direntrada = opendir(directory);
    while ((diread = readdir(direntrada)) != NULL) {
        this->leerBMP(diread); // es un puntero hay qye cambiar leerBMP
    }
    closedir(direntrada);
}

Common::unsigned char* leerBMP(char* filename){
    // se abre el archivo bmp
    FILE* file = fopen(filename, "rb");
    // si no existe se lanza excepcion
    if (file == NULL){
        throw "Invalid argument";
    }
    // variable de la informacion del formato BMP (54 bytes)
    unsigned char information[54];
    // se leen del archivo de entrada
    fread(information, sizeof(unsigned char), 54, file);
    // comprobamos los valores de compresion = 0, numero de planos = 1, t de punto = 24
    if ((*(int*)&information[30]) != 0){
        throw "Invalid compression value";
    }
    if ((*(int*)&information[26]) != 1){
        throw "Invalid number of level";
    }
    if ((*(int*)&information[24]) != 24){ // esto alomejor es cada punto de toda la imagen y no se si tendria q ir en el bucle
        throw "Invalid point value";
    }
    // obtenemos la altura y la anchura del header (estan los bytes en la tabla del pdf)
    int anchura = *(int*)&information[18];
    int altura = *(int*)&information[22];
    // comprobamos los valores
    cout << endl;
    cout << "Nombre: " << filename << endl;
    cout << "Anchura: " << anchura << endl;
    cout << "Altura: " << altura << endl;
    // continuamos con la lectura
    int fila = (anchura*3 + 3) & (~3);
    unsigned char aux; // variable ayuda a reordenar los pyxeles de BGR a RGB
    unsigned char* datos_imagen = unsigned char[fila];
    // lectura de la imagen
    for (int i = 0; i < altura; i++){
        fread(datos_imagen, sizeof(unsigned char), fila, file);
        for (int j = 0; j < anchura*3; j+=3){
            // es por tres ya que son tres: RGB; se reordenan
            aux = datos_imagen[j];
            datos_imagen[j] = datos_imagen[j+2];
            datos_imagen[j+2] = aux;
            // se mprime el pyxel
            cout << "Pyxel R: " <<  (int)datos_imagen[j] << " Pyxel G: " <<  (int)datos_imagen[j+1] << " Pyxel B: " <<  (int)datos_imagen[j+2] << endl;
        }
    }
    fclose(file);
    return datos_imagen;
};






























