%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
%}

%token NUMBER EOL

%%

input:
    expr EOL { printf("Resultado: %d\n", $1); }
;

expr:
    NUMBER '+' NUMBER { $$ = $1 + $3; }
;

%%