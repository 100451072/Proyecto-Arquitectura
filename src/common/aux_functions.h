//
//
//

#ifndef PROYECTO_ARQUITECTURA_AUX_FUNCTIONS_H
#define PROYECTO_ARQUITECTURA_AUX_FUNCTIONS_H

std::string rutaArchivoSalida(const std::string& type, const std::string& outdir, std::string infile);

void histograma(const int& RGB, const std::string& outFile);

void escalaGrises();

float transformacionLineal(int value);

float correccionGama(float cR, float cG, float cB);

#endif //PROYECTO_ARQUITECTURA_AUX_FUNCTIONS_H
