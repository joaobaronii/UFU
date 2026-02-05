#include "candidatos.h"

#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

typedef struct nobinaria NoBinaria;

NoBinaria *inserirBinaria(NoBinaria *raiz, Candidato candidato);

void filtrar_por_estado_ab(NoBinaria *raiz, const char *estado, int detalhes);

void filtrar_por_cidade_ab(NoBinaria *raiz, const char *cidade, const char *estado, int detalhes);

void filtrar_por_numero_ab(NoBinaria *raiz, int numero, const char *estado, const char *cidade);

#endif