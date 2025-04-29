%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void yyerror(const char *s);
int yylex(void);
%}

%union {
    int    ival;
    float  fval;
    char   *sval;
}

%token PROGRAM VAR VOID MAIN END IF ELSE WHILE DO PRINT INT FLOAT
%token CTE_FLOAT CTE_INT CTE_STRING ID
%token NEQ GT LT PLUS MINUS MULT DIV ASSIGN SEMI COLON COMMA LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET

%type <ival>    CTE_INT
%type <fval>    CTE_FLOAT
%type <sval>    CTE_STRING
%type <sval>    ID

%start programa

%%

programa:
    PROGRAM ID SEMI DEC_VAR DEC_FUN MAIN BODY END
;

DEC_VAR:
    VARS
    |
;

VARS:
    VAR list_id COLON TYPE SEMI DEC_VAR
;

list_id:
    ID
    | ID COMMA list_id
;

TYPE:
    INT
    | FLOAT
;

DEC_FUN:
    FUNCS DEC_FUN
    |
;

FUNCS:
    VOID ID LPAREN param RPAREN LBRACKET DEC_VAR BODY RBRACKET SEMI
;

param:
    ID COLON TYPE extra_param
    |
;

extra_param:
    COMMA param
    |
;

BODY:
    LBRACE STMT_LIST RBRACE
;

STMT_LIST:
    STATEMENT STMT_LIST
    |
;

STATEMENT:
    assign
    | condition
    | cycle
    | f_call
    | print_stmt
;

assign:
    ID ASSIGN EXPRESION SEMI
;

condition:
    IF LPAREN EXPRESION RPAREN BODY else_stmt SEMI
;

else_stmt:
    ELSE BODY
    |
;

cycle:
    WHILE LPAREN EXPRESION RPAREN DO BODY SEMI
;

f_call:
    ID LPAREN f_call_exp RPAREN SEMI
;

f_call_exp:
    EXPRESION COMMA f_call_exp
    | EXPRESION
    |
;

print_stmt:
    PRINT LPAREN print_list RPAREN SEMI
;

print_list:
    print_elem COMMA print_list
    | print_elem
;

print_elem:
    EXPRESION
    | CTE_STRING
;

EXPRESION:
    EXP
    | EXP LT EXP
    | EXP GT EXP
    | EXP NEQ EXP
;

EXP:
    TERMINO
    | TERMINO PLUS EXP
    | TERMINO MINUS EXP
;

TERMINO:
    FACTOR
  | FACTOR MULT list_term
  | FACTOR DIV list_term
;

list_term:
    TERMINO
;

FACTOR:
    LPAREN EXPRESION RPAREN
  | PLUS FACTOR
  | MINUS FACTOR
  | ID
  | CTE_INT
  | CTE_FLOAT
;

%%

int main(void) {
    return yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "ErrorL %s\n", s);
}