%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "semantic_cube.h"
#include "semantic_structures.h"

void yyerror(const char *s);
int yylex(void);

// global vars for semantic analysis
FunctionDirectory funcDir;
char currentFunction[MAX_FUNC_NAME];
DataType currentType;

DataType exprType;
%}

%union {
    int    ival;
    float  fval;
    char   *sval;
    DataType type;
}

%token PROGRAM VAR VOID MAIN END IF ELSE WHILE DO PRINT INT FLOAT
%token CTE_FLOAT CTE_INT CTE_STRING ID
%token NEQ GT LT PLUS MINUS MULT DIV ASSIGN SEMI COLON COMMA LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET

%type <ival>    CTE_INT
%type <fval>    CTE_FLOAT
%type <sval>    CTE_STRING
%type <sval>    ID
%type <type>    TYPE
%type <type>    EXPRESION
%type <type>    EXP
%type <type>    TERMINO
%type <type>    FACTOR

%start programa

%%

programa:
    {
        // Init semantic structures
        initSemanticCube();
        initFunctionDirectory(&funcDir);
        strcpy(currentFunction, "global");
    }
    PROGRAM ID 
    {
        printf("Compiling program %s\n", $3);
    }
    SEMI DEC_VAR DEC_FUN MAIN 
    {
        strcpy(currentFunction, "main");
    }
    BODY END
    {
        printf("Semantic analysis completed\n");
    }
;

DEC_VAR:
    VARS
    |
;

VARS:
    VAR list_var
;

list_var:
    list_id COLON TYPE
    {
        currentType = $3;
    } 
    SEMI extra_vars
;

list_id:
    ID
    {
        // punto neuralgico - add var to cur context
        int res;
        if (strcmp(currentFunction, "global") == 0) {
            res = addVar(&funcDir.globalVars, $1, currentType);
        } else {
            Function *func = findFunction(&funcDir, currentFunction);
            if (func != NULL) {
                res = addVar(&func->localVars, $1, currentType);    
            } else {
                res = 0;
                yyerror("Function not found");
            }
        }

        if (res == 0) {
            char error[100];
            sprintf(error, "Semantic error: Variable '%s' already declared", $1);
            yyerror(error);
        } else if (res == -1) {
            yyerror("Semantic error: Variable limit exceeded");
        }
    } 
    COMMA list_id
    | ID
    {
        // Punto neuralgico - add var to cur context
        int res;
        if (strcmp(currentFunction, "global") == 0) {
            res = addVar(&funcDir.globalVars, $1, currentType);
        } else {
            Function *func = findFunction(&funcDir, currentFunction);
            if (func != NULL) {
                res = addVar(&func->localVars, $1, currentType);
            } else {
                res = 0;
                yyerror("Function not found");
            }
        }
        
        if (res == 0) {
            char error[100];
            sprintf(error, "Semantic error: Variable '%s' already declared", $1);
            yyerror(error);
        } else if (res == -1) {
            yyerror("Semantic error: Variable limit exceeded");
        }
    }
;

extra_vars:
    list_var
    |
;

TYPE:
    INT
    {
        $$ = TYPE_INT;
    }
    | FLOAT
    {
        $$ = TYPE_FLOAT;
    }
;

DEC_FUN:
    FUNCS DEC_FUN
    |
;

FUNCS:
    VOID ID 
    {
        // punto neuralgico - add func to funcDir
        int res = addFunction(&funcDir, $2);

        if (res == 0) {
            char error[100];
            sprintf(error, "Semantic error: Function '%s' already declared", $2);
            yyerror(error);
        } else if (res == -1) {
            yyerror("Semantic error: Functions limit exceeded");
        }

        // change context to new function
        strcpy(currentFunction, $2);

    }
    LPAREN param RPAREN LBRACKET DEC_VAR BODY RBRACKET
    {
        // go back to global context
        strcpy(currentFunction, "global");
    }
    SEMI
;

param:
    ID COLON TYPE
    {
        // punto neuralgico - add param to function
        Function *func = findFunction(&funcDir, currentFunction);
        if (func != NULL) {
            int res = addParameter(func, $1, $3);

            if (res == 0) {
                char error[100];
                sprintf(error, "Semantic error: Parameter '%s' already declared", $1);
                yyerror(error);
            } else if (res == -1) {
                yyerror("Semantic error: Parameter limit exceeded");
            }
        } else {
            yyerror("Semantic error: Function not found to add param");
        }
    } 
    extra_param
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
    IF LPAREN EXPRESION
    {
        if ($3 != TYPE_BOOL) {
            yyerror("Semantic error: if condition must be boolean expression"); // TODO CHECK LATER again
        }
    }
    RPAREN BODY else_stmt SEMI
;

else_stmt:
    ELSE BODY
    |
;

cycle:
    WHILE LPAREN EXPRESION
    {
        if ($3 != TYPE_BOOL) {
            yyerror("Semantic error: while condition must be boolean expression"); // TODO: CHECK LATER again
        }
    }
    RPAREN DO BODY SEMI
;

f_call:
    ID 
    {
        // check that function is declared
        Function *func = findFunction(&funcDir, $1);
        if (func == NULL) {
            char error[100];
            sprintf(error, "Semantic error: Function '%s' not declared", $1);
            yyerror(error);
        }
    }

    LPAREN f_call_exp RPAREN SEMI
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
    fprintf(stderr, "Error %s\n", s);
}