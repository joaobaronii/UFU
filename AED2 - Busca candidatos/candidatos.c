#include "candidatos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Candidato *cria_candidato(char *estado, char *cidade, char *nome_candidato,
                          char *nome_urna, char *cargo, char *partido,
                          char *genero, char *escolaridade, char *cor,
                          int numero) {
  Candidato *novo_candidato = (Candidato *)malloc(sizeof(Candidato));

  if (novo_candidato != NULL) {
    strncpy(novo_candidato->estado, estado, 3);
    strncpy(novo_candidato->cidade, cidade, 50);
    novo_candidato->numero = numero;
    strncpy(novo_candidato->cargo, cargo, 9);
    strncpy(novo_candidato->nome_candidato, nome_candidato, 50);
    strncpy(novo_candidato->nome_urna, nome_urna, 50);
    strncpy(novo_candidato->partido, partido, 11);
    strncpy(novo_candidato->genero, genero, 11);
    strncpy(novo_candidato->escolaridade, escolaridade, 50);
    strncpy(novo_candidato->cor, cor, 11);
  }

  return novo_candidato;
}

void ler_arquivo_e_armazenar(const char *nome_arquivo, Candidato **candidatos,
                             int *quantidade)
{
  FILE *arquivo = fopen(nome_arquivo, "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    exit(1);
  }

  char linha[256];
  int capacidade = 1000;
  *quantidade = 0;

  *candidatos = (Candidato *)malloc(capacidade * sizeof(Candidato));
  if (*candidatos == NULL) {
    printf("Erro ao alocar memoria.\n");
    exit(1);
  }

  while (fgets(linha, sizeof(linha), arquivo)) {

    if (*quantidade >= capacidade) {
      capacidade *= 2;
      *candidatos = (Candidato *)realloc(*candidatos, capacidade * sizeof(Candidato));
      if (*candidatos == NULL) {
        printf("Erro ao realocar memoria.\n");
        exit(1);
      }
    }

    char *estado = strtok(linha, "\t");
    char *cidade = strtok(NULL, "\t");
    int numero = atoi(strtok(NULL, "\t"));
    char *cargo = strtok(NULL, "\t");
    char *nome_candidato = strtok(NULL, "\t");
    char *nome_urna = strtok(NULL, "\t");
    char *partido = strtok(NULL, "\t");
    char *genero = strtok(NULL, "\t");
    char *escolaridade = strtok(NULL, "\t");
    char *cor = strtok(NULL, "\n");

    Candidato *novo_candidato =
        cria_candidato(estado, cidade, nome_candidato, nome_urna, cargo,
                       partido, genero, escolaridade, cor, numero);
    (*candidatos)[*quantidade] = *novo_candidato;
    free(novo_candidato);

    (*quantidade)++;
  }

  fclose(arquivo);
}

void CAPSLOCK(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}


void shellSort(Candidato *vetor, int n) {
  int i, j;
  int h = 1;
  Candidato aux;

  while (h < n/3) {
    h = 3*h + 1;
  }

  while (h >= 1) {
    for (i = h; i < n; i++) {
      aux = vetor[i];
      j = i;

      while (j >= h && strcmp(vetor[j - h].estado, aux.estado) > 0) {
        vetor[j] = vetor[j - h];
        j -= h;
      }

      vetor[j] = aux;
    }
    h /= 3;
  }
}
void shellSort_cidade(Candidato *vetor, int n) {
  int i, j, h = 1;
  Candidato aux;

  do {
    h = h * 3 + 1;
  } while (h < n);

  do {
    h /= 3;
    for (i = h; i < n; i++) {
      aux = vetor[i];
      j = i;

      while (j >= h && strcmp(vetor[j - h].cidade, aux.cidade) > 0) {
        vetor[j] = vetor[j - h];
        j -= h;
      }

      vetor[j] = aux;
    }
  } while (h != 1);
}

void shellSort_numero(Candidato *vetor, int n) {
  int i, j, h = 1;
  Candidato aux;

  do {
    h = h * 3 + 1;
  } while (h < n);

  do {
    h /= 3;
    for (i = h; i < n; i++) {
      aux = vetor[i];
      j = i;

      while (j >= h && vetor[j - h].numero > aux.numero) {
        vetor[j] = vetor[j - h];
        j -= h;
      }

      vetor[j] = aux;
    }
  } while (h != 1);
}
