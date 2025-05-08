%{
#include "datatype.h"
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
int yylex(void);
%}

%%

"program"    return PROGRAM;
"var"        return VAR;
"void"       return VOID;
"main"       return MAIN;
"end"        return END;
"if"         return IF;
"else"       return ELSE;
"while"      return WHILE;
"do"         return DO;
"print"      return PRINT;
"int"        return INT;
"float"      return FLOAT;

[0-9]+\.[0-9]+              { yylval.fval = atof(yytext); return CTE_FLOAT; }
[0-9]+                      { yylval.ival = atoi(yytext); return CTE_INT; }
\"([ -~]|\\["\\ntbr])*\"    { yylval.sval = strdup(yytext); return CTE_STRING; }

[a-zA-Z_][a-zA-Z0-9_]*    { yylval.sval = strdup(yytext); return ID; }

"!="    return NEQ;
">"     return GT;
"<"     return LT;
"+"     return PLUS;
"-"     return MINUS;
"*"     return MULT;
"/"     return DIV;
"="     return ASSIGN;
";"     return SEMI;
":"     return COLON;
","     return COMMA;
"("     return LPAREN;
")"     return RPAREN;
"{"     return LBRACE;
"}"     return RBRACE;
"["     return LBRACKET;
"]"     return RBRACKET;


[ \t\n]+  ; /* ignorar espacios, tabs y saltos de línea */
"//".*    ; /* ignorar comentarios de línea */

%%

int yywrap(void) { return 1; }