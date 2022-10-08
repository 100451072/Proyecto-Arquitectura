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