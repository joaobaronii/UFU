#include <stdio.h>
#include "lexico.h"
#include "sintatico.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "uso: %s <arquivo-fonte>\n", argv[0]);
        return 1;
    }

    lex_inicializa(argv[1]);
    NoArvore *raiz = analisar();

    int erros = sint_total_erros();
    if (erros == 0) {
        imprime_arvore(raiz);
        printf("\nAnalise sintatica concluida sem erros.\n");
    } else {
        fprintf(stderr, "\nAnalise sintatica concluida com %d erro(s).\n", erros);
    }

    libera_arvore(raiz);
    lex_finaliza();
    return erros ? 1 : 0;
}
