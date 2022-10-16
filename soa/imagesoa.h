//
//
//

#ifndef UNTITLED_IMAGESOA_H
#define UNTITLED_IMAGESOA_H

/*
 * SOA-Structure of arrays:  Se representará una imagen mediante
 *      tres vectores independientes de valores entre 0 y 255
 */

// Tamaño max para formar un array
int MAX_SIZE = 1000000;

// Estructura que almacenará tres vectores para cada valor R, G, B
struct Nodes {
    int arrayR[MAX_SIZE];
    int arrayG[MAX_SIZE];
    int arrayB[MAX_SIZE];
};

class Imagesoa {
private:
    // Atributos
    Nodes structurePixels;
    // Ultima posición no vacia
    int lastPos;

public:
    // Constructor & Destructor
    Imagesoa();

    // Funciones
    void addPixel(int R, int G, int B);
};


#endif //UNTITLED_IMAGESOA_H
