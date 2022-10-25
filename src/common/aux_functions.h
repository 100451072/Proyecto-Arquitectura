//
//
//

#ifndef PROYECTO_ARQUITECTURA_AUX_FUNCTIONS_H
#define PROYECTO_ARQUITECTURA_AUX_FUNCTIONS_H

std::string rutaArchivoSalida(std::string operation, std::string type,
                              std::string outdir, std::string infile);

void histograma(const int& R, const int& G, const int& B);

void escalaGrises();

float transformacionLineal(int value);

float correccionGama(float cR, float cG, float cB);

#endif //PROYECTO_ARQUITECTURA_AUX_FUNCTIONS_H
