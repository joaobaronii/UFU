#include "arvorealv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoAvl
{
  Candidato candidato;
  int fator;
  struct NoAvl *fesq, *fdir;
} NoAvl;

NoAvl *criarNo(Candidato candidato)
{
  NoAvl *novo = (NoAvl *)malloc(sizeof(NoAvl));
  if (novo == NULL)
  {
    printf("Erro na alocação de memória.\n");
    exit(1);
  }
  novo->candidato = candidato;
  novo->fator = 0;
  novo->fesq = NULL;
  novo->fdir = NULL;
  return novo;
}

int altura(NoAvl *no)
{
  if (no == NULL)
    return -1;
  int alturaEsq = altura(no->fesq);
  int alturaDir = altura(no->fdir);
  return (alturaEsq > alturaDir ? alturaEsq : alturaDir) + 1;
}

void atualizarFator(NoAvl *no)
{
  no->fator = altura(no->fdir) - altura(no->fesq);
}

NoAvl *rotacaoSimplesDireita(NoAvl *no)
{
  NoAvl *esq = no->fesq;
  no->fesq = esq->fdir;
  esq->fdir = no;
  atualizarFator(no);
  atualizarFator(esq);
  return esq;
}

NoAvl *rotacaoSimplesEsquerda(NoAvl *no)
{
  NoAvl *dir = no->fdir;
  no->fdir = dir->fesq;
  dir->fesq = no;
  atualizarFator(no);
  atualizarFator(dir);
  return dir;
}

NoAvl *rotacaoEsquerdaDireita(NoAvl *no)
{
  no->fesq = rotacaoSimplesEsquerda(no->fesq);
  return rotacaoSimplesDireita(no);
}

NoAvl *rotacaoDireitaEsquerda(NoAvl *no)
{
  no->fdir = rotacaoSimplesDireita(no->fdir);
  return rotacaoSimplesEsquerda(no);
}

NoAvl *balancear(NoAvl *no)
{
  atualizarFator(no);
  if (no->fator == -2)
  { // desbalanceado para a esquerda
    if (no->fesq->fator <= 0)
      no = rotacaoSimplesDireita(no);
    else
      no = rotacaoEsquerdaDireita(no);
  }
  else if (no->fator == 2)
  { // desbalanceado para a direita
    if (no->fdir->fator >= 0)
      no = rotacaoSimplesEsquerda(no);
    else
      no = rotacaoDireitaEsquerda(no);
  }
  return no;
}

NoAvl *inserirAvl(NoAvl *no, Candidato candidato)
{
  if (no == NULL)
    return criarNo(candidato);

  if (candidato.numero < no->candidato.numero)
    no->fesq = inserirAvl(no->fesq, candidato);
  else if (candidato.numero > no->candidato.numero)
    no->fdir = inserirAvl(no->fdir, candidato);

  return balancear(no);
}

void filtrar_por_estado_avl(NoAvl *raiz, const char *estado, int detalhes)
{
  if (detalhes == 0)
  {

    if (raiz == NULL)
      return;

    if (strcmp(raiz->candidato.estado, estado) == 0)
    {
      printf("Candidato: %s, Cidade: %s, Numero: %d\n",
             raiz->candidato.nome_candidato, raiz->candidato.cidade,
             raiz->candidato.numero);
    }

    filtrar_por_estado_avl(raiz->fesq, estado, detalhes);
    filtrar_por_estado_avl(raiz->fdir, estado, detalhes);
  }
  else
  {
    if (raiz == NULL)
      return;

    if (strcmp(raiz->candidato.estado, estado) == 0)
    {
      printf("Candidato: %s, Cidade: %s, Numero: %d, ",
             raiz->candidato.nome_candidato, raiz->candidato.cidade,
             raiz->candidato.numero);

      if (detalhes == 1)
      {
        printf("Genero: %s\n",
               raiz->candidato.genero);
      }
      else if (detalhes == 2)
      {
        printf("Partido: %s\n",
               raiz->candidato.partido);
      }
      else if (detalhes == 3)
      {
        printf("Cor/Raça: %s\n",
               raiz->candidato.cor);
      }
    }

    filtrar_por_estado_avl(raiz->fesq, estado, detalhes);
    filtrar_por_estado_avl(raiz->fdir, estado, detalhes);
  }
}

void filtrar_por_cidade_avl(NoAvl *raiz, const char *cidade, const char *estado, int detalhes)
{

  if (detalhes == 0)
  {
    if (raiz == NULL)
      return;

    if (strcmp(raiz->candidato.estado, estado) == 0)
    {

      if (strcmp(raiz->candidato.cidade, cidade) == 0)
      {
        printf("Candidato: %s, Numero: %d\n", raiz->candidato.nome_candidato,
               raiz->candidato.numero);
      }
    }

    filtrar_por_cidade_avl(raiz->fesq, cidade, estado, detalhes);
    filtrar_por_cidade_avl(raiz->fdir, cidade, estado, detalhes);
  }
  else
  {
    if (raiz == NULL)
      return;

    if (strcmp(raiz->candidato.estado, estado) == 0)
    {

      if (strcmp(raiz->candidato.cidade, cidade) == 0)
      {
        printf("Candidato: %s, Numero: %d\n", raiz->candidato.nome_candidato,
               raiz->candidato.numero);
      }
      if (detalhes == 1)
      {
        printf("Genero: %s\n",
               raiz->candidato.genero);
      }
      else if (detalhes == 2)
      {
        printf("Partido: %s\n",
               raiz->candidato.partido);
      }
      else if (detalhes == 3)
      {
        printf("Cor/Raça: %s\n",
               raiz->candidato.cor);
      }
    }

    filtrar_por_cidade_avl(raiz->fesq, cidade, estado, detalhes);
    filtrar_por_cidade_avl(raiz->fdir, cidade, estado, detalhes);
  }
}

void filtrar_por_numero_avl(NoAvl *raiz, int numero, const char *estado, const char *cidade)
{
  if (raiz == NULL)
    return;

  if (strcmp(raiz->candidato.estado, estado) == 0)
  {
    // Depois, filtramos pela cidade
    if (strcmp(raiz->candidato.cidade, cidade) == 0)
    {

      if (raiz->candidato.numero == numero)
      {
        printf("Candidato encontrado:\n");
        printf("Nome: %s\n", raiz->candidato.nome_candidato);
        printf("Cidade: %s\n", raiz->candidato.cidade);
        printf("Estado: %s\n", raiz->candidato.estado);
        printf("Cargo: %s\n", raiz->candidato.cargo);
        printf("Partido: %s\n", raiz->candidato.partido);
        printf("Genero: %s\n", raiz->candidato.genero);
        printf("Escolaridade: %s\n", raiz->candidato.escolaridade);
        printf("Cor: %s\n", raiz->candidato.cor);
        return;
      }
    }
  }
  filtrar_por_numero_avl(raiz->fesq, numero, estado, cidade);
  filtrar_por_numero_avl(raiz->fdir, numero, estado, cidade);
}