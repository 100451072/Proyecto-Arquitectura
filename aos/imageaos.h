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
    // Ultima posición no vacia
    int lastPos

public:
    // Constructor & Destructor
    Imageaos();

    // Funciones
    void addPixel(int R, int G, int B);

};


#endif //UNTITLED_IMAGEAOS_H
