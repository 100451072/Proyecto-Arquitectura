//
//
//

#include "imagesoa.h"

//Constructor & Destructor
Imagesoa::Imagesoa() {
    /* Constructor, recibe tres vectores que conformarán
     * el structurePixels*/

    this->structurePixels = NULL;
    this->lastPos = 0;

}

void Imagesoa::addPixel(int R, int G, int B) {
    /* Función que irá añadiendo pixeles al final
     * de los arrays R, G, B*/

    this->structurePixels.R[this->lastPos] = R;
    this->structurePixels.G[this->lastPos] = G;
    this->structurePixels.B[this->lastPos] = B;

    // Añadimos uno para ir avanzando en el array
    this->lastPos++;
}