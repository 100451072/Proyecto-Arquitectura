//
//
//

#include "imageaos.h"

// Constructor & Destructor
Imageaos::Imageaos() {
    /* Constructor, encargado de asigar a cada nodo de arrayPixeles
     * su valor de R, G, B*/

    this->arrayPixeles = NULL;
    this->lastPos = 0;

}

void Imageaos::addPixel(int R, int G, int B) {
    /* Funcion que ira añadiendo pixeles al final
     * del arrayPixeles */

    this->arrayPixeles[this->lastPos].R = R;
    this->arrayPixeles[this->lastPos].G = G;
    this->arrayPixeles[this->lastPos].B = B;

    // Sumamos uno para ir avanzando en el array
    this->lastPos++;

}