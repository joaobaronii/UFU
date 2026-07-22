%{
#include <stdio.h>
#include "Lexer.h"
#define YYSTYPE double
void yyerror (char *);
%}

%token NUM
%left '+' '-'
%left '*' '/'
%right NEGAR

%%
lines : lines expr '\n' { printf("= %.2f\n", $2); }
      | lines '\n'      { return 0; }
      | error '\n'      { yyerror("Erro na ultima linha"); yyerrok; }
      | /* vazio para aceitar a primeira linha */
      ;

expr  : expr '+' expr   { $$ = $1 + $3; printf("+ "); }
      | expr '-' expr   { $$ = $1 - $3; printf("- "); }
      | expr '*' expr   { $$ = $1 * $3; printf("* "); }
      | expr '/' expr   { $$ = $1 / $3; printf("/ "); }
      | '(' expr ')'    { $$ = $2; }
      | '-' expr %prec NEGAR { $$ = -$2; printf("(-) "); }
      | NUM             { $$ = $1; printf("%g ", $1); }
      ;
%%

void yyerror(char * s) { fprintf (stderr, "%s\n", s); }

int main(void) {
    printf("\n Digite a expressao desejada:\n");
    return yyparse();
}