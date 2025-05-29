/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     VAR = 259,
     VOID = 260,
     MAIN = 261,
     END = 262,
     IF = 263,
     ELSE = 264,
     WHILE = 265,
     DO = 266,
     PRINT = 267,
     INT = 268,
     FLOAT = 269,
     CTE_FLOAT = 270,
     CTE_INT = 271,
     CTE_STRING = 272,
     ID = 273,
     NEQ = 274,
     GT = 275,
     LT = 276,
     PLUS = 277,
     MINUS = 278,
     MULT = 279,
     DIV = 280,
     ASSIGN = 281,
     SEMI = 282,
     COLON = 283,
     COMMA = 284,
     LPAREN = 285,
     RPAREN = 286,
     LBRACE = 287,
     RBRACE = 288,
     LBRACKET = 289,
     RBRACKET = 290
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define VAR 259
#define VOID 260
#define MAIN 261
#define END 262
#define IF 263
#define ELSE 264
#define WHILE 265
#define DO 266
#define PRINT 267
#define INT 268
#define FLOAT 269
#define CTE_FLOAT 270
#define CTE_INT 271
#define CTE_STRING 272
#define ID 273
#define NEQ 274
#define GT 275
#define LT 276
#define PLUS 277
#define MINUS 278
#define MULT 279
#define DIV 280
#define ASSIGN 281
#define SEMI 282
#define COLON 283
#define COMMA 284
#define LPAREN 285
#define RPAREN 286
#define LBRACE 287
#define RBRACE 288
#define LBRACKET 289
#define RBRACKET 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 35 "parser.y"
{
    int    ival;
    float  fval;
    char   *sval;
    DataType type;
}
/* Line 1529 of yacc.c.  */
#line 126 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

