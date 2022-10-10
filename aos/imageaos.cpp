//
//
//

#include "imageaos.h"

// Constructor & Destructor
Imageaos::Imageaos(int &arrayR, int &arrayG, int &arrayB) {
    /* Constructor, encargado de asigar a cada nodo de arrayPixeles
     * su valor de R, G, B*/

    // El bucle debe recorrer el tamaño de los vectores introducidos
    for (int i=0; i<sizeof(arrayR)/sizeof(int); ++i){
        this->arrayPixeles[i].R = arrayR[i];
        this->arrayPixeles[i].G = arrayG[i];
        this->arrayPixeles[i].B = arrayB[i];
    }
}