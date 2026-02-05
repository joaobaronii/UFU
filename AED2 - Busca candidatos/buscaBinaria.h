#include "candidatos.h"

//int buscaBinaria(int v[], int n, int chave);

void filtrar_por_estado_bb(Candidato v[], int n, char *estado, int detalhes);
void filtrar_por_cidade_bb(Candidato v[], int n, char *cidade, int detalhes);
void filtrar_por_numero_bb(Candidato v[], int n, int numero, char *estado, char *cidade);