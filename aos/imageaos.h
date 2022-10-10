//
//
//

#ifndef UNTITLED_IMAGEAOS_H
#define UNTITLED_IMAGEAOS_H


/*
 * AOS-Array of structures: Se representará una imagen con un único
 *      vector de valores de tipo pixel. Un pixel representa una
 *      estructura con tres valores entre 0 y 255.
 */

// Tamaño max de un array
int MAX_SIZE = 1000000;

// Structura que almacenara tres enteros por pixel (R, G, B)
struct Nodo
{
    int Red;
    int Green;
    int Blue;
};

class Imageaos {
private:
    // Atributos
    // Como dice la definicion de aos, un solo array
    Nodo arrayPixeles[MAX_SIZE];

    // Funciones de inicialización

public:
    // Constructor & Destructor
    Imageaos(int& arrayR, int& arrayG, int& arrayB);

    // Getters & Setters

    // Funciones

};


#endif //UNTITLED_IMAGEAOS_H
