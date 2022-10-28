//
// Práctica Procesamiento de Imagenes
//
// Participantes:
//      Asier Justo Turuelo 100451012
//      Pablo Vallspín Aranguren 100451072
//      Alvaro Buj Mancha 100406530


#include "soa/imagesoa.h"
#include "common/progargs.h"
#include <string>
#include <filesystem>


int main(int argc, char* argv[]){

    if (argc != 4) {
        numeroIncorrectoArgs();
        return -1;
    }

    if (!comprobarArg((argv[1]), (argv[2]),(argv[3]))) {
        return -1;
    }

    std::string inDirectory = argv[1];
    std::string outDirectory = argv[2];
    std::string operation = argv[3];

    for (auto const& currentFile : std::filesystem::directory_iterator{inDirectory}) {
        Imagesoa imagen(currentFile.path().filename(), currentFile.path(), outDirectory);
        imagen.realizarOperacion(operation);
    }

    return 0;
}
