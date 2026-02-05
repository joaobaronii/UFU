#include "arvorealv.h"
#include "arvorebinaria.h"
#include "buscaBinaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 1134

int main()
{
    Candidato *candidatos = NULL;
    int quantidade = 0;
    time_t ini, fim;

    ler_arquivo_e_armazenar("candidatos.txt", &candidatos, &quantidade);

    shellSort(candidatos, quantidade);

    NoBinaria *arvoreB = NULL;
    ini = clock();
    for (int i = 0; i < quantidade; i++)
    {
        arvoreB = inserirBinaria(arvoreB, candidatos[i]);
    }
    fim = clock();
    double tempoArvoreBinaria = (double)(fim - ini) / CLOCKS_PER_SEC;

    NoAvl *arvoreA = NULL;
    ini = clock();
    for (int i = 0; i < quantidade; i++)
    {
        arvoreA = inserirAvl(arvoreA, candidatos[i]);
    }
    fim = clock();
    double tempoArvoreAVL = (double)(fim - ini) / CLOCKS_PER_SEC;

    ini = clock();
    for (int i = 0; i < quantidade; i++)
    {
        int v[quantidade];
        v[i] = candidatos[i].numero;
    }
    fim = clock();
    double tempoBuscaBinaria = (double)(fim - ini) / CLOCKS_PER_SEC;

    printf("Arquivo carregado!\n");
    printf("Tempo de carregamento da pesquisa binaria(vetor): %f segundos\n",
           tempoBuscaBinaria);
    printf("Tempo de carregamento da arvore binaria: %f segundos\n",
           tempoArvoreBinaria);
    printf("Tempo de carregamento da arvore AVL: %f segundos\n", tempoArvoreAVL);
    printf("===============================================================\n");

    int opcao, opcao1, opcao2,
        opcao3; // Variáveis para armazenar as opções do menu
    char estado[3], cidade[50];
    int numero;
    do
    {

        printf("Escolha uma opcao:\n");
        printf("1 - Busca Binaria\n");
        printf("2 - Arvore Binaria\n");
        printf("3 - Arvore AVL\n");
        printf("4 - Sair\n");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do stdin para evitar problemas com fgets

        switch (opcao)
        {
        case 1:
            printf("Digite o estado para filtrar: ");
            scanf("%s", estado);
            CAPSLOCK(estado);                     // Converte o estado para maiúsculas
            estado[strcspn(estado, "\n")] = '\0'; // Remove o caractere de nova linha
            ini = clock();
            filtrar_por_estado_bb(candidatos, quantidade, estado, 0);
            fim = clock();
            double tempoBuscaBinariaEstado = (double)(fim - ini) / CLOCKS_PER_SEC;
            printf("==========================================================="
                   "======================================\n");
            printf("tempo de busca binaria: %f segundos\n", tempoBuscaBinariaEstado);

            do
            {
                printf("==============================================================="
                       "==================================\n");
                printf("1. filtrar por cidade\n");
                printf("2. detalhes\n");
                printf("3. voltar\n");
                scanf("%d", &opcao1);
                getchar(); // Limpa o buffer do stdin para evitar problemas com fgets

                switch (opcao1)
                {
                case 1:
                    printf("Digite a Cidade\n");
                    fgets(cidade, sizeof(cidade), stdin);
                    cidade[strcspn(cidade, "\n")] = '\0'; // Remove o '\n' da string
                    CAPSLOCK(cidade);                     // Converte o nome da cidade para maiúsculas
                    ini = clock();
                    filtrar_por_cidade_bb(candidatos, quantidade, cidade, 0);
                    fim = clock();
                    double tempoBuscaBinariaCidade = (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf("==========================================================="
                           "======================================\n");
                    printf("tempo de busca binaria: %f segundos\n",
                           tempoBuscaBinariaCidade);

                    do
                    {
                        printf("==========================================================="
                               "======================================\n");
                        printf("1. filtrar por numero\n");
                        printf("2. detalhes\n");
                        printf("3. voltar\n");
                        scanf("%d", &opcao2);

                        switch (opcao2)
                        {
                        case 1:
                            printf("Digite o numero\n");
                            scanf("%d", &numero);
                            ini = clock();
                            filtrar_por_numero_bb(candidatos, quantidade, numero, estado, cidade);
                            fim = clock();
                            double tempoBuscaBinariaNumero =
                                (double)(fim - ini) / CLOCKS_PER_SEC;
                            printf(
                                "==========================================================="
                                "======================================\n");
                            printf("tempo de busca binaria: %f segundos\n",
                                   tempoBuscaBinariaNumero);
                            break;

                        case 2:
                            do
                            {
                                printf("quais detalhes?\n");
                                printf("1. Genero\n");
                                printf("2. Partido\n");
                                printf("3. Cor/raca\n");
                                printf("4. Voltar\n");
                                scanf("%d", &opcao3);

                                switch (opcao3)
                                {
                                case 1:
                                    filtrar_por_cidade_bb(candidatos, quantidade, cidade, 1);
                                    break;

                                case 2:
                                    filtrar_por_cidade_bb(candidatos, quantidade, cidade, 2);
                                    break;

                                case 3:
                                    filtrar_por_cidade_bb(candidatos, quantidade, cidade, 3);
                                    break;

                                case 4:
                                    printf("Voltando...\n");
                                    break;

                                default:
                                    printf("Opcao invalida. Tente novamente.\n");
                                    break;
                                }
                            } while (opcao3 != 4);

                            break;

                        case 3:
                            printf("Voltando...\n");
                            break;

                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                            break;
                        }

                    } while (opcao2 != 3);
                    break;
                case 2:
                    do
                    {
                        printf("quais detalhes?\n");
                        printf("1. Genero\n");
                        printf("2. Partido\n");
                        printf("3. Cor/raca\n");
                        printf("4. Voltar\n");
                        scanf("%d", &opcao3);

                        switch (opcao3)
                        {
                        case 1:
                            filtrar_por_estado_bb(candidatos, quantidade, estado, 1);
                            break;

                        case 2:
                            filtrar_por_estado_bb(candidatos, quantidade, estado, 2);
                            break;

                        case 3:
                            filtrar_por_estado_bb(candidatos, quantidade, estado, 3);
                            break;

                        case 4:
                            printf("Voltando...\n");
                            break;

                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                            break;
                        }
                    } while (opcao3 != 4);
                    break;

                case 3:
                    printf("Voltando...\n");
                    break;

                default:
                    printf("Opcao invalida. Tente novamente.\n");
                    break;
                }
            } while (opcao1 != 3);

            break;

        case 2:
            printf("Digite o estado para filtrar: ");
            scanf("%s", estado);
            CAPSLOCK(estado);                     // Converte o estado para maiúsculas
            estado[strcspn(estado, "\n")] = '\0'; // Remove o caractere de nova linha
            ini = clock();
            filtrar_por_estado_ab(arvoreB, estado, 0);
            fim = clock();
            double tempoArvoreBinariaEstado = (double)(fim - ini) / CLOCKS_PER_SEC;
            printf("==========================================================="
                   "======================================\n");
            printf("tempo de busca na arvore binaria: %f segundos\n",
                   tempoArvoreBinariaEstado);

            do
            {
                printf("==============================================================="
                       "==================================\n");
                printf("1. filtrar por cidade\n");
                printf("2. detalhes\n");
                printf("3. voltar\n");
                scanf("%d", &opcao1);
                getchar(); // Limpa o buffer do stdin para evitar problemas com fgets

                switch (opcao1)
                {
                case 1:
                    printf("Digite a Cidade\n");
                    fgets(cidade, sizeof(cidade), stdin);
                    cidade[strcspn(cidade, "\n")] = '\0'; // Remove o '\n' da string
                    CAPSLOCK(cidade);                     // Converte o nome da cidade para maiúsculas
                    ini = clock();
                    filtrar_por_cidade_ab(arvoreB, cidade, estado, 0);
                    fim = clock();
                    double tempoArvoreBinariaCidade =
                        (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf("==========================================================="
                           "======================================\n");
                    printf("tempo de busca na arvore binaria: %f segundos\n",
                           tempoArvoreBinariaCidade);

                    do
                    {
                        printf("==========================================================="
                               "======================================\n");
                        printf("1. filtrar por numero\n");
                        printf("2.detalhes\n");
                        printf("3. voltar\n");
                        scanf("%d", &opcao2);

                        switch (opcao2)
                        {
                        case 1:
                            printf("Digite o numero\n");
                            scanf("%d", &numero);
                            filtrar_por_numero_ab(arvoreB, numero, estado, cidade);
                            break;

                        case 2:

                            do
                            {
                                printf("quais detalhes?\n");
                                printf("1. Genero\n");
                                printf("2. Partido\n");
                                printf("3. Cor/raca\n");
                                printf("4. Voltar\n");
                                scanf("%d", &opcao3);

                                switch (opcao3)
                                {

                                case 1:
                                    filtrar_por_cidade_ab(arvoreB, cidade, estado, 1);
                                    break;
                                case 2:
                                    filtrar_por_cidade_ab(arvoreB, cidade, estado, 2);
                                    break;
                                case 3:
                                    filtrar_por_cidade_ab(arvoreB, cidade, estado, 3);
                                    break;
                                case 4:
                                    printf("Voltando...\n");
                                    break;
                                default:
                                    printf("Opcao invalida. Tente novamente.\n");
                                    break;
                                }

                            } while (opcao3 != 4);

                            break;

                        case 3:
                            printf("Voltando...\n");
                            break;

                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                            break;
                        }

                    } while (opcao2 != 3);
                    break;
                case 2:
                    do
                    {
                        printf("quais detalhes?\n");
                        printf("1. Genero\n");
                        printf("2. Partido\n");
                        printf("3. Cor/raca\n");
                        printf("4. Voltar\n");
                        scanf("%d", &opcao3);

                        switch (opcao3)
                        {

                        case 1:
                            filtrar_por_estado_ab(arvoreB, estado, 1);
                            break;
                        case 2:
                            filtrar_por_estado_ab(arvoreB, estado, 2);
                            break;
                        case 3:
                            filtrar_por_estado_ab(arvoreB, estado, 3);
                            break;
                        case 4:
                            printf("Voltando...\n");
                            break;
                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                            break;
                        }
                    } while (opcao3 != 4);
                    break;

                case 3:
                    printf("Voltando...\n");
                    break;

                default:
                    printf("Opcao invalida. Tente novamente.\n");
                    break;
                }
            } while (opcao1 != 3);
            break;

        case 3:
            printf("Digite o estado para filtrar: ");
            scanf("%s", estado);
            CAPSLOCK(estado);                     // Converte o estado para maiúsculas
            estado[strcspn(estado, "\n")] = '\0'; // Remove o caractere de nova linha
            ini = clock();
            filtrar_por_estado_avl(arvoreA, estado, 0);
            fim = clock();
            double tempoArvoreAVLEstado = (double)(fim - ini) / CLOCKS_PER_SEC;
            printf("==========================================================="
                   "======================================\n");
            printf("tempo de busca na arvore avl: %f segundos\n",
                   tempoArvoreAVLEstado);

            do
            {
                printf("==============================================================="
                       "==================================\n");
                printf("1. filtrar por cidade\n");
                printf("2. detalhes\n");
                printf("3. voltar\n");
                scanf("%d", &opcao1);
                getchar(); // Limpa o buffer do stdin para evitar problemas com fgets

                switch (opcao1)
                {
                case 1:
                    printf("Digite a Cidade\n");
                    fgets(cidade, sizeof(cidade), stdin);
                    cidade[strcspn(cidade, "\n")] = '\0'; // Remove o '\n' da string
                    CAPSLOCK(cidade);                     // Converte o nome da cidade para maiúsculas
                    ini = clock();
                    filtrar_por_cidade_avl(arvoreA, cidade, estado, 0);
                    fim = clock();
                    double tempoArvoreAVLCidade = (double)(fim - ini) / CLOCKS_PER_SEC;
                    printf("==========================================================="
                           "======================================\n");
                    printf("tempo de busca na arvore avl: %f segundos\n",
                           tempoArvoreAVLCidade);

                    do
                    {
                        printf("==========================================================="
                               "======================================\n");
                        printf("1. filtrar por numero\n");
                        printf("2.detalhes\n");
                        printf("3. voltar\n");
                        scanf("%d", &opcao2);

                        switch (opcao2)
                        {
                        case 1:
                            printf("Digite o numero\n");
                            scanf("%d", &numero);
                            filtrar_por_numero_avl(arvoreA, numero, estado, cidade);
                            break;

                        case 2:
                            do
                            {
                                printf("quais detalhes?\n");
                                printf("1. Genero\n");
                                printf("2. Partido\n");
                                printf("3. Cor/raca\n");
                                printf("4. Voltar\n");
                                scanf("%d", &opcao3);

                                switch (opcao3)
                                {

                                case 1:
                                    filtrar_por_cidade_avl(arvoreA, cidade, estado, 1);
                                    break;
                                case 2:
                                    filtrar_por_cidade_avl(arvoreA, cidade, estado, 2);
                                    break;
                                case 3:
                                    filtrar_por_cidade_avl(arvoreA, cidade, estado, 3);
                                    break;
                                case 4:
                                    printf("Voltando...\n");
                                    break;
                                default:
                                    printf("Opcao invalida. Tente novamente.\n");
                                    break;
                                }
                            } while (opcao3 != 4);

                            break;

                        case 3:
                            printf("Voltando...\n");
                            break;

                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                            break;
                        }

                    } while (opcao2 != 3);
                    break;
                case 2:
                    do
                    {
                        printf("quais detalhes?\n");
                        printf("1. Genero\n");
                        printf("2. Partido\n");
                        printf("3. Cor/raca\n");
                        printf("4. Voltar\n");
                        scanf("%d", &opcao3);

                        switch (opcao3)
                        {

                        case 1:
                            filtrar_por_estado_avl(arvoreA, estado, 1);
                            break;
                        case 2:
                            filtrar_por_estado_avl(arvoreA, estado, 2);
                            break;
                        case 3:
                            filtrar_por_estado_avl(arvoreA, estado, 3);
                            break;
                        case 4:
                            printf("Voltando...\n");
                            break;
                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                            break;
                        }
                    } while (opcao3 != 4);
                    break;

                case 3:
                    printf("Voltando...\n");
                    break;

                default:
                    printf("Opcao invalida. Tente novamente.\n");
                    break;
                }
            } while (opcao1 != 3);
            break;

        case 4:
            printf("Saindo do programa.\n");
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (opcao != 4);

    free(candidatos);

    return 0;
}