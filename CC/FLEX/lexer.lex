%option noyywrap
%option nodefault
%option outfile="lexer.c" header-file="lexer.h"

%{
#include "token.h"
#include <string.h>
#include <stdlib.h>

Token tok;

Token *token(int tipo, char *valor) {
    tok.tipo = tipo;
    if (valor != NULL) {
        strncpy(tok.atributo, valor, 255);
        tok.atributo[255] = '\0';
    } else {
        strcpy(tok.atributo, "none");
    }
    return &tok;
}
%}

DIGITO [0-9]
LETRA  [a-zA-Z]
ID     {LETRA}({LETRA}|{DIGITO})*
NUM_INT {DIGITO}+

NUM_FLOAT {DIGITO}+"."{DIGITO}+([eE][+-]?{DIGITO}+)?

ESPACO [ \t\n]+

COMENTARIO "/*"([^*]|\*+[^*/])*\*+"/"

%%

{ESPACO}      { return token(TOK_SEP, yytext); }
{COMENTARIO}  { return token(TOK_COMMENT, yytext); }

"se"          { return token(TOK_KW_SE, NULL); }
"senao"       { return token(TOK_KW_SENAO, NULL); }
"enquanto"    { return token(TOK_KW_ENQ, NULL); }
"faca"        { return token(TOK_KW_FACA, NULL); }

"ini"         { return token(TOK_DELIM_INI, NULL); }
"fim"         { return token(TOK_DELIM_FIM, NULL); }

":="           { return token(TOK_ATRIB, NULL); }

"<"|"<="|">"|">="|"=" { return token(TOK_RELOP, yytext); }

"("|")"       { return token(TOK_PAR, yytext); }

{NUM_INT}     { return token(TOK_NUM_INT, yytext); }
{NUM_FLOAT}   { return token(TOK_NUM_FLOAT, yytext); }
{ID}          { return token(TOK_ID, yytext); }

<<EOF>>       { return token(TOK_EOF, NULL); }
.             { }

%%