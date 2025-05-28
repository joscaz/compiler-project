%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "semantic_cube.h"
#include "semantic_structures.h"
#include "virtual_memory.h"
#include "quadruple_generator.h"
#include "virtual_machine.h"

void yyerror(const char *s);
int yylex(void);

// global vars for semantic analysis
FunctionDirectory funcDir;
char currentFunction[MAX_FUNC_NAME];
DataType currentType;

// to generate quadruples
QuadrupleGenerator quadGenerator;

// for exp type checking
DataType exprType;

// for function calls
char currentFunctionCall[MAX_FUNC_NAME];
int currentParamIndex;
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

        // init quad struct
        initQuadrupleGenerator(&quadGenerator);
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
        printf("Compilation completed successfully\n");
        printGeneratedQuadruples(&quadGenerator);
        
        // Ejecutar la máquina virtual
        printf("\n=== INICIANDO VM ===\n");
        VirtualMachine vm;
        initVirtualMachine(&vm, &quadGenerator.quadQueue, &quadGenerator.constTable);
        executeProgram(&vm);
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
        int address;
        int res;
        // assign virtual mem based on type and scope
        if (strcmp(currentFunction, "global") == 0) {
            address = getNextAddress(&quadGenerator.memCounters, currentType, 1);
            res = addVar(&funcDir.globalVars, $1, currentType, address);
        } else {
            address = getNextAddress(&quadGenerator.memCounters, currentType, 0);
            Function *func = findFunction(&funcDir, currentFunction);
            if (func != NULL) {
                res = addVar(&func->localVars, $1, currentType, address);    
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
        int address;
        int res;
        // assign virtual mem based on type and scope
        if (strcmp(currentFunction, "global") == 0) {
            address = getNextAddress(&quadGenerator.memCounters, currentType, 1);
            res = addVar(&funcDir.globalVars, $1, currentType, address);
        } else {
            address = getNextAddress(&quadGenerator.memCounters, currentType, 0);
            Function *func = findFunction(&funcDir, currentFunction);
            if (func != NULL) {
                res = addVar(&func->localVars, $1, currentType, address);
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

        // store starting quadruple for function
        Function *func = findFunction(&funcDir, $2);
        if (func != NULL) {
            func->startQuad = quadGenerator.quadQueue.count;
        }

    }
    LPAREN param RPAREN LBRACKET DEC_VAR BODY RBRACKET
    {
        // add ENDPROC quad
        addQuadruple(&quadGenerator.quadQueue, OP_ENDPROC, -1, -1, -1);

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
            // assign virtual mem address for param
            int address = getNextAddress(&quadGenerator.memCounters, $3, 0); // 0 pq es local
            int res = addParameter(func, $1, $3, address);

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
    ID ASSIGN
    {
        // check if var exists
        Variable *var = findVariable(&funcDir, currentFunction, $1);
        if (var == NULL) {
            char error[100];
            sprintf(error, "Semantic error: Variable '%s' not declared", $1);
            yyerror(error);
        }
    }
    EXPRESION SEMI
    {
        // generate assign quad
        generateAssignment(&quadGenerator, $1, &funcDir, currentFunction);
    }
;

condition:
    IF LPAREN 
    {
        // process the expression before evaluating it
    }
    EXPRESION
    {
        if ($4 != TYPE_BOOL) {
            yyerror("Semantic error: if condition must be boolean expression");
        }
        
        // GOTOF quadruple after evaluating condition
        startIfStatement(&quadGenerator);
    }
    RPAREN BODY 
    {
        // For an IF with no ELSE, we need to fill the jump location
        // to the end of the IF statement
        if (yychar != ELSE) {
            endIfStatement(&quadGenerator);
        }
    }
    else_stmt SEMI
;

else_stmt:
    ELSE 
    {
        // Process the start of ELSE - generate jump to end of if-else
        // and fill the GOTOF jump location
        processElseStatement(&quadGenerator);
    }
    BODY
    {
        // Fill the GOTO jump location at the end of if-else
        endIfStatement(&quadGenerator);
    }
    |
;

cycle:
    WHILE 
    {
        // Mark the start of the while loop
        startWhileLoop(&quadGenerator);
    }
    LPAREN EXPRESION
    {
        if ($4 != TYPE_BOOL) {
            yyerror("Semantic error: while condition must be boolean expression");
        }
        
        // Process condition and generate GOTOF quadruple
        processWhileCondition(&quadGenerator);
    }
    RPAREN DO BODY 
    {
        // Generate GOTO to beginning of while loop and fill the GOTOF jump
        endWhileLoop(&quadGenerator);
    }
    SEMI
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
        } else {
            // punto neuralgico - start function call (generate ERA)
            startFunctionCall(&quadGenerator, $1, &funcDir);
        }
        
        // store function name for parameter processing
        strcpy(currentFunctionCall, $1);
        currentParamIndex = 0;
    }

    LPAREN f_call_exp RPAREN 
    {
        // punto neuralgico - end function call (generate GOSUB)
        endFunctionCall(&quadGenerator, currentFunctionCall, &funcDir);
    }
    SEMI
;

f_call_exp:
    EXPRESION 
    {
        // punto neuralgico - process function parameter
        processFunctionParameter(&quadGenerator, currentParamIndex);
        currentParamIndex++;
    }
    COMMA f_call_exp
    | EXPRESION
    {
        // punto neuralgico - process function parameter
        processFunctionParameter(&quadGenerator, currentParamIndex);
        currentParamIndex++;
    }
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
    {
        // generate print quad
        generatePrint(&quadGenerator);
    }
    | CTE_STRING
    {
        processStringConstant(&quadGenerator, $1);
        generatePrint(&quadGenerator);
    }
;

EXPRESION:
    EXP
    {
        $$ = $1;
    }
    | EXP LT EXP
    {
        processRelationalOperator(&quadGenerator, OP_LT);
        $$ = TYPE_BOOL;
    }
    | EXP GT EXP
    {
        processRelationalOperator(&quadGenerator, OP_GT);
        $$ = TYPE_BOOL;
    }
    | EXP NEQ EXP
    {
        processRelationalOperator(&quadGenerator, OP_NEQ);
        $$ = TYPE_BOOL;
    }
;

EXP:
    TERMINO
    {
        $$ = $1;
    }
    | TERMINO PLUS EXP
    {
        processOperator(&quadGenerator, OP_PLUS);
        $$ = peekType(&quadGenerator.types);
    }
    | TERMINO MINUS EXP
    {
        processOperator(&quadGenerator, OP_MINUS);
        $$ = peekType(&quadGenerator.types);
    }
;

TERMINO:
    FACTOR
    {
        $$ = $1;
    }
  | FACTOR MULT list_term
    {
        processOperator(&quadGenerator, OP_MULT);
        $$ = peekType(&quadGenerator.types);
    }
  | FACTOR DIV list_term
  {
        processOperator(&quadGenerator, OP_DIV);
        $$ = peekType(&quadGenerator.types);
  }
;

list_term:
    TERMINO
;

FACTOR:
    LPAREN EXPRESION RPAREN
    {
        $$ = $2;
    }
  | PLUS FACTOR
  {
    $$ = $2;
  }
  | MINUS FACTOR
  {
    $$ = $2;
  }
  | ID
  {
    Variable *var = findVariable(&funcDir, currentFunction, $1);
    if (var == NULL) {
        char error[100];
        sprintf(error, "Semantic error: Variable '%s' not declared", $1);
        yyerror(error);
        $$ = TYPE_ERROR;
    } else {
        processOperand(&quadGenerator, $1, &funcDir, currentFunction);
        $$ = var->type;
    }
  }
  | CTE_INT
  {
    processIntConstant(&quadGenerator, $1);
    $$ = TYPE_INT;
  }
  | CTE_FLOAT
  {
    processFloatConstant(&quadGenerator, $1);
    $$ = TYPE_FLOAT;
  }
;

%%

int main(void) {
    return yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "Error %s\n", s);
}