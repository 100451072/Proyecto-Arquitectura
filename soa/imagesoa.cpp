//
//
//

#include "imagesoa.h"

//Constructor & Destructor
Imagesoa::Imagesoa(int& arrayR, int& arrayG, int& arrayB) {
    /* Constructor, recibe tres vectores que conformarán
     * el structurePixels*/

    this->structurePixels.arrayR = arrayR;
    this->structurePixels.arrayG = arrayG;
    this->structurePixels.arrayB = arrayB;
}