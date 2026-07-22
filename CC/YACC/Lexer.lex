%option noyywrap
%option outfile="Lexer.c" header-file="Lexer.h"

%{
#define YYSTYPE double
#include "y.tab.h"
#include <stdlib.h>
extern YYSTYPE yylval; 
%}

DIGITO [0-9]

%%
[ \t]                    { /* ignora tabulacao e espaco */ }
{DIGITO}+([.]{DIGITO}+)? { yylval = atof(yytext); return NUM; }
\n                       { return yytext[0]; }
.                        { return yytext[0]; }
%%