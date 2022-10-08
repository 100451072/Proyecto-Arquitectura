//
// Práctica Procesamiento de Imagenes
//
// Participantes:
// Asier Justo Turuelo 100451012
// Pablo Vallspín Aranguren 100451072

//////////////////////////////////////////////////////////////
//// lo he añadido por si acaso a progargs.cpp
// TRATAMIENTO DE EXCEPCIONES
#include <iostream>
#include <stdio.h>

int main(int argc, char *argv[]){
    using namespace std;
    // comprobamos que el numero de argumentos sea el correcto
    if (argc < 3){
        cout << "Wrong format:" << "\n";
        cout << "Image in_path out_path oper" << "\n";
        cout << "Operation: copy, histo, mono, gauss" << "\n";
        return 0;
        }
    // comprobamos que la accion a realizar sea la indicada
    if (argv[3] !== "gauss" and argv[3] !== "histo" and argv[3] !== "mono" and argv[3] != ="copy"){
        cout << "Unexpected operation: " << argv[3] << "\n";
        cout << "Image in_path out_path oper" << "\n";
        cout << "Operation: copy, histo, mono, gauss" << "\n";
        return 0;
        }
    // comprobamos si existen los directorios de entrada
    if (!opendir(argv[1])){
        cout << "Input path: " << argv[1] << "\n";
        cout << "Output path: " << argv[2] << "\n";
        cout << "Cannot open directory " << "[" << argv[1] << "]" << "\n";
        cout << "Image in_path out_path oper" << "\n";
        cout << "Operation: copy, histo, mono, gauss" << "\n";
        return 0;
    }
    if (!opendir(argv[2])){
        cout << "Input path: " << argv[1] << "\n";
        cout << "Output path: " << argv[2] << "\n";
        cout << "Output directory " << "[" << argv[2] << "]" << " does not exist" << "\n";
        cout << "Image in_path out_path oper" << "\n";
        cout << "Operation: copy, histo, mono, gauss" << "\n";
        return 0;
    }
    // si estatodo correcto se continua y se hacen las operaciones







    return 0;
}