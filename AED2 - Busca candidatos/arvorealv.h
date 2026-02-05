#include "candidatos.h"

#ifndef ARVOREAVL_H
#define ARVOREAVL_H

typedef struct NoAvl NoAvl;

struct NoAvl *criarNo(Candidato candidato);

int altura(struct NoAvl *no);

void atualizaFator(NoAvl *no);

NoAvl *rotacaoSimplesDireita(NoAvl *no);

NoAvl *rotacaoSimplesEsquerda(NoAvl *no);

NoAvl *rotacaoEsquerdaDireita(NoAvl *no);

NoAvl *rotacaoDireitaEsquerda(NoAvl *no);

NoAvl *balancear(NoAvl *no);

NoAvl *inserirAvl(NoAvl *no, Candidato candidato);

void filtrar_por_estado_avl(NoAvl *raiz, const char *estado, int detalhes);

void filtrar_por_cidade_avl(NoAvl *raiz, const char *cidade, const char *estado, int detalhes);

void filtrar_por_numero_avl(NoAvl *raiz, int numero, const char *estado, const char *cidade);

#endif