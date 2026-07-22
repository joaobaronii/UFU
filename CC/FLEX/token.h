#ifndef TOKEN_H
#define TOKEN_H

#define TOK_ID 1
#define TOK_RELOP 2
#define TOK_SEP 3
#define TOK_NUM_INT 4
#define TOK_NUM_FLOAT 5
#define TOK_COMMENT 6
#define TOK_PAR 7
#define TOK_EOF 8
#define TOK_ATRIB 9
#define TOK_DELIM_INI 10
#define TOK_DELIM_FIM 11
#define TOK_KW_SE 12
#define TOK_KW_SENAO 13
#define TOK_KW_ENQ 14
#define TOK_KW_FACA 15

typedef struct {
    int tipo;
    char atributo[256]; 
} Token;

extern Token *token(int tipo, char *valor);

#define YY_DECL Token *yylex(void)
YY_DECL;

#endif