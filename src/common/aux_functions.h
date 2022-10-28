//
//
//

#ifndef PROYECTO_ARQUITECTURA_AUX_FUNCTIONS_H
#define PROYECTO_ARQUITECTURA_AUX_FUNCTIONS_H

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

std::string rutaArchivoSalida(const std::string& type, const std::string& outdir, std::string infile);

void histograma_aux(const std::vector<int>& RGB, const std::string& outFile);

float transformacionLineal(int value);

float correccionGama(float cR, float cG, float cB);

#endif //PROYECTO_ARQUITECTURA_AUX_FUNCTIONS_H
