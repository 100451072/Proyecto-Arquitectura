//
//
//

#include <cmath>
#include "aux_functions.h"


double transformacionLineal(double value) {
    /* Función encargada de realizar la transformación lineal sobre
     * los valores de los pixeles normalizdos*/
    double c_value;
    if (value <= 0.04045)
        c_value = value / 12.92;
    else
        c_value = pow((value + 0.055) / 1.055, 2.4);
    return c_value;
}

double correccionGamma(double cR, double cG, double cB) {
    /* Función encargada de la realización de la corrección gamma*/
    double cL = 0.2126 * cR + 0.7152 * cG + 0.0722 * cB;
    double potencia = 1 / 2.4;
    if (cL <= 0.0031308) {
        cG = 12.92 * cL;
    } else {
        cG = (1.055 * pow(cL, potencia)) - 0.055;
    }
    return cG;
}

