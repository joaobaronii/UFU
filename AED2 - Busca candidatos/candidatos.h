#ifndef CANDIDATOS_H
#define CANDIDATOS_H

typedef struct candidato {

  char estado[3];
  char cidade[50];
  int numero;
  char cargo[9];
  char nome_candidato[50];
  char nome_urna[50];
  char partido[11];
  char genero[11];
  char escolaridade[50];
  char cor[11];

} Candidato;

Candidato *cria_candidato(char *estado, char *cidade, char *nome_candidato,
                          char *nome_urna, char *cargo, char *partido,
                          char *genero, char *escolaridade, char *cor,
                          int numero);

void ler_arquivo_e_armazenar(const char *nome_arquivo, Candidato **candidatos,
                             int *quantidade);

void CAPSLOCK(char *str);

void shellSort(Candidato *vetor, int n);
void shellSort_cidade(Candidato *vetor, int n);
void shellSort_numero(Candidato *vetor, int n);

#endif