//
//
//

#include "progargs.h"
#include <filesystem>

void numeroIncorrectoArgs() {
    std::cout << "Wrong format:" << "\n";
    std::cout << "  Image in_path out_path oper" << "\n";
    std::cout << "      Operation: copy, histo, mono, gauss" << "\n";
}

bool comprobarArg(const std::string& inDir, const std::string& outDir, const std::string& operation) {
    /* Función encargada de validar los argumentos introducidos,
     * devuelve false en caso de que algun arg sea incorrecto*/
    std::cout << "$image " <<  inDir << " " << outDir << " " <<  operation << "\n";
    // comprobamos que el numero de argumentos sea el correcto
    // comprobamos que la accion a realizar sea la indicada
    if (operation != "gauss" && operation != "histo" && operation != "mono" && operation != "copy") {
        std::cout << "Unexpected operation: " << operation << "\n";
        std::cout << "  Image in_path out_path oper" << "\n";
        std::cout << "      Operation: copy, histo, mono, gauss" << "\n";
        return false;
    }
    // comprobamos si existen los directorios de entrada y salida

    if (!std::filesystem::is_directory(inDir)) {
        std::cout << "Input path: " << inDir << "\n";
        std::cout << "output path: " << outDir << "\n";
        std::cout << "cannot open directory " << "[" << inDir << "]" << "\n";
        std::cout << "  image in_path out_path oper" << "\n";
        std::cout << "      operation: copy, histo, mono, gauss" << "\n";
        return false;
    }

    if (!std::filesystem::is_directory(outDir)) {
        std::cout << "input path: " << inDir << "\n";
        std::cout << "output path: " << outDir << "\n";
        std::cout << "output directory " << "[" << outDir << "]" << " does not exist" << "\n";
        std::cout << "  image in_path out_path oper" << "\n";
        std::cout << "      operation: copy, histo, mono, gauss" << "\n";
        return false;
    }

    return true;
}


