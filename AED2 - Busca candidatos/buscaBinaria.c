#include "buscaBinaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void filtrar_por_estado_bb(Candidato v[], int n, char *estado, int detalhes) {
  if (detalhes == 0) {
    if (v == NULL || estado == NULL)
      return;

    int inf = 0, sup = n - 1, meio;

    while (inf <= sup) {
      meio = (inf + sup) / 2;

      int cmp = strcmp(v[meio].estado, estado);
      if (cmp == 0) {
        // Encontrar o primeiro candidato com o estado desejado
        while (meio > 0 && strcmp(v[meio - 1].estado, estado) == 0) {
          meio--;
        }

        // Exibir todos os candidatos com o estado desejado
        while (meio < n && strcmp(v[meio].estado, estado) == 0) {
          printf("Candidato %s, Cidade: %s, Numero: %d\n",
                 v[meio].nome_candidato, v[meio].cidade, v[meio].numero);
          meio++;
        }
        return;
      } else if (cmp > 0) {
        sup = meio - 1;
      } else {
        inf = meio + 1;
      }
    }
  } else {
    if (v == NULL || estado == NULL)
      return;

    int inf = 0, sup = n - 1, meio;

    while (inf <= sup) {
      meio = (inf + sup) / 2;

      int cmp = strcmp(v[meio].estado, estado);
      if (cmp == 0) {
        // Encontrar o primeiro candidato com o estado desejado
        while (meio > 0 && strcmp(v[meio - 1].estado, estado) == 0) {
          meio--;
        }

        // Exibir todos os candidatos com o estado desejado
        while (meio < n && strcmp(v[meio].estado, estado) == 0) {
          printf("Candidato %s, Cidade: %s, Numero: %d, ",
                 v[meio].nome_candidato, v[meio].cidade, v[meio].numero);

          if (detalhes == 1) {
            printf("Genero: %s\n", v[meio].genero);
          } else if (detalhes == 2) {
            printf("Partido: %s\n", v[meio].partido);
          } else if (detalhes == 3) {
            printf("Cor/Raca: %s\n", v[meio].cor);
          }

          meio++;
        }
        return;
      } else if (cmp > 0) {
        sup = meio - 1;
      } else {
        inf = meio + 1;
      }
    }
  }
}

void filtrar_por_cidade_bb(Candidato v[], int n, char *cidade, int detalhes) {
  if (detalhes == 0) {
    if (v == NULL || cidade == NULL)
      return;

    int inf = 0, sup = n - 1, meio;

    shellSort_cidade(v, n);

    while (inf <= sup) {
      meio = (inf + sup) / 2;

      int cmp = strcmp(v[meio].cidade, cidade);
      if (cmp == 0) {
        // Encontrar o primeiro candidato com o estado desejado
        while (meio > 0 && strcmp(v[meio - 1].cidade, cidade) == 0) {
          meio--;
        }

        // Exibir todos os candidatos com a cidade desejada
        while (meio < n && strcmp(v[meio].cidade, cidade) == 0) {
          printf("Candidato %s, Numero: %d\n", v[meio].nome_candidato,
                 v[meio].numero);
          meio++;
        }
        return;
      } else if (cmp > 0) {
        sup = meio - 1;
      } else {
        inf = meio + 1;
      }
    }
  } else {
    if (v == NULL || cidade == NULL)
      return;

    int inf = 0, sup = n - 1, meio;

    shellSort_cidade(v, n);

    while (inf <= sup) {
      meio = (inf + sup) / 2;

      int cmp = strcmp(v[meio].cidade, cidade);
      if (cmp == 0) {
        // Encontrar o primeiro candidato com o estado desejado
        while (meio > 0 && strcmp(v[meio - 1].cidade, cidade) == 0) {
          meio--;
        }

        // Exibir todos os candidatos com a cidade desejada
        while (meio < n && strcmp(v[meio].cidade, cidade) == 0) {
          printf("Candidato %s, Numero: %d\n", v[meio].nome_candidato,
                 v[meio].numero);

          if (detalhes == 1) {
            printf("Genero: %s\n", v[meio].genero);
          } else if (detalhes == 2) {
            printf("Partido: %s\n", v[meio].partido);
          } else if (detalhes == 3) {
            printf("Cor/Raca: %s\n", v[meio].cor);
          }

          meio++;
        }
        return;
      } else if (cmp > 0) {
        sup = meio - 1;
      } else {
        inf = meio + 1;
      }
    }
  }
}

void filtrar_por_numero_bb(Candidato v[], int n, int numero, char *estado,
                           char *cidade) {
  if (v == NULL)
    return;

  int inf = 0, sup = n - 1, meio;
  shellSort_numero(v, n);

  while (inf <= sup) {
    meio = (inf + sup) / 2;
    int cmp = strcmp(v[meio].estado, estado);
    if (cmp == 0) {
      cmp = strcmp(v[meio].cidade, cidade);
      if (cmp == 0) {
        if (v[meio].numero == numero) {
          // Encontrado, exibe o candidato e interrompe a busca
          printf("Candidato encontrado!\n");
          printf("Nome: %s\n", v[meio].nome_candidato);
          printf("Cidade: %s\n", v[meio].cidade);
          printf("Estado: %s\n", v[meio].estado);
          printf("Cargo: %s\n", v[meio].cargo);
          printf("Partido: %s\n", v[meio].partido);
          printf("Genero: %s\n", v[meio].genero);
          printf("Escolaridade: %s\n", v[meio].escolaridade);
          printf("Cor: %s\n", v[meio].cor);
          return; // Adicione esta linha para sair da função após encontrar o
                  // candidato
            } 
        }
    }else if (cmp < 0 || (cmp == 0 && strcmp(v[meio].cidade, cidade) < 0) ||
    (cmp == 0 && strcmp(v[meio].cidade, cidade) == 0 &&
     v[meio].numero < numero)) {
          sup = meio - 1;
        } else {
          inf = meio + 1;
        }
      }
    }

    /*int busca_binaria_candidato(Candidato arr[], int tamanho,
                                const char *estado, const char *cidade,
                                const char *numCandidato) {
      int inicio = 0;
      int fim = tamanho - 1;

      while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        int cmp = strcmp(arr[meio].estado, estado);
        if (cmp == 0) {
          cmp = strcmp(arr[meio].cidade, cidade);
          if (cmp == 0) {
            cmp = strcmp(arr[meio].numCandidato, numCandidato);
            if (cmp == 0) {
              return meio; // Candidato encontrado
            }
          }
        }

        if (cmp < 0 || (cmp == 0 && strcmp(arr[meio].cidade, cidade) < 0) ||
            (cmp == 0 && strcmp(arr[meio].cidade, cidade) == 0 &&
             strcmp(arr[meio].numCandidato, numCandidato) < 0)) {
          inicio = meio + 1;
        } else {
          fim = meio - 1;
        }
      }

      return -1; // Candidato não encontrado
    }*/