#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "lexer.h"

extern FILE *yyin;

void imprime_token_c(Token *tok) {
    switch(tok->tipo) {
        case TOK_COMMENT:
        case TOK_SEP:
        case TOK_ID:
        case TOK_PAR:
        case TOK_NUM_INT:
        case TOK_NUM_FLOAT:
            printf("%s", tok->atributo);
            break;
        case TOK_RELOP:
            if (strcmp(tok->atributo, "=") == 0) printf("==");
            else if (strcmp(tok->atributo, "<<") == 0) printf("!=");
            else printf("%s", tok->atributo);
            break;
        case TOK_ATRIB:
            printf("="); 
            break;
        case TOK_DELIM_INI:
            printf("{"); 
            break;
        case TOK_DELIM_FIM:
            printf("}"); 
            break;
        case TOK_KW_SE:
            printf("if"); 
            break;
        case TOK_KW_SENAO:
            printf("else"); 
            break;
        case TOK_KW_ENQ:
            printf("while"); 
            break;
        case TOK_KW_FACA:
            printf("do"); 
            break;
        case TOK_EOF:
            printf("\n// Fim do Programa\n");
            break;
    }
}

int main() {
    char filename[256];
    
    printf("Digite o nome do arquivo fonte a ser analisado: ");
    scanf("%255s", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo '%s'.\n", filename);
        return 1;
    }

    yyin = file; 
    Token *tok;

    tok = yylex();
    while (tok->tipo != TOK_EOF) {
        imprime_token_c(tok);
        tok = yylex();
    }
    imprime_token_c(tok); 

    fclose(file);
    return 0;
}