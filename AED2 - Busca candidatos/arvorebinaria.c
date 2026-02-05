#include "arvorebinaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nobinaria
{
  Candidato candidato;
  struct nobinaria *esquerda;
  struct nobinaria *direita;
} NoBinaria;

NoBinaria *inserirBinaria(NoBinaria *raiz, Candidato candidato)
{
  if (raiz == NULL)
  {
    NoBinaria *novo_no = (NoBinaria *)malloc(sizeof(NoBinaria));
    novo_no->candidato = candidato;
    novo_no->esquerda = novo_no->direita = NULL;
    return novo_no;
  }

  if (strcmp(candidato.estado, raiz->candidato.estado) < 0)
  {
    raiz->esquerda = inserirBinaria(raiz->esquerda, candidato);
  }
  else
  {
    raiz->direita = inserirBinaria(raiz->direita, candidato);
  }

  return raiz;
}

void filtrar_por_estado_ab(NoBinaria *raiz, const char *estado, int detalhes)
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

    filtrar_por_estado_ab(raiz->esquerda, estado, detalhes);
    filtrar_por_estado_ab(raiz->direita, estado, detalhes);
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

    filtrar_por_estado_ab(raiz->esquerda, estado, detalhes);
    filtrar_por_estado_ab(raiz->direita, estado, detalhes);
  }
}

void filtrar_por_cidade_ab(NoBinaria *raiz, const char *cidade, const char *estado, int detalhes)
{
  if (detalhes == 0)
  {
    if (raiz == NULL)
      return;

      if (strcmp(raiz->candidato.estado, estado) == 0){

    if (strcmp(raiz->candidato.cidade, cidade) == 0)
    {
      printf("Candidato: %s, Numero: %d\n", raiz->candidato.nome_candidato,
             raiz->candidato.numero);
    }
      }
    filtrar_por_cidade_ab(raiz->esquerda, cidade, estado, detalhes);
    filtrar_por_cidade_ab(raiz->direita, cidade, estado, detalhes);
  }
  else
  {
    if (raiz == NULL)
      return;

      if (strcmp(raiz->candidato.estado, estado) == 0){

    if (strcmp(raiz->candidato.cidade, cidade) == 0)
    {
      printf("Candidato: %s, Numero: %d, ", raiz->candidato.nome_candidato,
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

    filtrar_por_cidade_ab(raiz->esquerda, cidade, estado, detalhes);
    filtrar_por_cidade_ab(raiz->direita, cidade, estado, detalhes);
  }
}

void filtrar_por_numero_ab(NoBinaria *raiz, int numero, const char *estado, const char *cidade)
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

  filtrar_por_numero_ab(raiz->esquerda, numero, estado, cidade);
  filtrar_por_numero_ab(raiz->direita, numero, estado, cidade);
}
