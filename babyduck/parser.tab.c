/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

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
int mainStartQuad = 0; // Posición donde empieza el main

// Control de verbosidad
int verbose_mode = 1; // 1 = verbose (default), 0 = quiet


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 35 "parser.y"
{
    int    ival;
    float  fval;
    char   *sval;
    DataType type;
}
/* Line 193 of yacc.c.  */
#line 207 "parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 220 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   103

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  137

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     5,     6,    18,    20,    21,    24,
      25,    32,    33,    38,    40,    42,    43,    45,    47,    50,
      51,    52,    53,    66,    67,    73,    74,    77,    78,    82,
      85,    86,    88,    90,    92,    94,    96,    97,   103,   104,
     105,   106,   117,   118,   122,   123,   124,   125,   126,   137,
     138,   139,   147,   148,   153,   155,   156,   162,   166,   168,
     170,   172,   174,   178,   182,   186,   188,   192,   196,   198,
     202,   206,   208,   212,   215,   218,   220,   222
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    -1,    -1,    -1,    38,     3,    18,    39,
      27,    41,    49,     6,    40,    56,     7,    -1,    42,    -1,
      -1,     4,    43,    -1,    -1,    45,    28,    48,    44,    27,
      47,    -1,    -1,    18,    46,    29,    45,    -1,    18,    -1,
      43,    -1,    -1,    13,    -1,    14,    -1,    50,    49,    -1,
      -1,    -1,    -1,     5,    18,    51,    30,    53,    31,    34,
      41,    56,    35,    52,    27,    -1,    -1,    18,    28,    48,
      54,    55,    -1,    -1,    29,    53,    -1,    -1,    32,    57,
      33,    -1,    58,    57,    -1,    -1,    59,    -1,    61,    -1,
      67,    -1,    71,    -1,    76,    -1,    -1,    18,    26,    60,
      79,    27,    -1,    -1,    -1,    -1,     8,    30,    62,    79,
      63,    31,    56,    64,    65,    27,    -1,    -1,     9,    66,
      56,    -1,    -1,    -1,    -1,    -1,    10,    68,    30,    79,
      69,    31,    11,    56,    70,    27,    -1,    -1,    -1,    18,
      72,    30,    74,    31,    73,    27,    -1,    -1,    79,    75,
      29,    74,    -1,    79,    -1,    -1,    12,    30,    77,    31,
      27,    -1,    78,    29,    77,    -1,    78,    -1,    79,    -1,
      17,    -1,    80,    -1,    80,    21,    80,    -1,    80,    20,
      80,    -1,    80,    19,    80,    -1,    81,    -1,    81,    22,
      80,    -1,    81,    23,    80,    -1,    83,    -1,    83,    24,
      82,    -1,    83,    25,    82,    -1,    81,    -1,    30,    79,
      31,    -1,    22,    83,    -1,    23,    83,    -1,    18,    -1,
      16,    -1,    15,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    61,    61,    71,    77,    61,   105,   106,   110,   115,
     114,   123,   122,   151,   182,   183,   187,   191,   198,   199,
     204,   227,   203,   239,   238,   259,   263,   264,   268,   272,
     273,   277,   278,   279,   280,   281,   286,   285,   304,   308,
     317,   303,   329,   328,   339,   344,   349,   358,   343,   367,
     385,   366,   394,   393,   400,   406,   410,   414,   415,   419,
     424,   432,   436,   441,   446,   454,   458,   463,   471,   475,
     480,   488,   492,   496,   500,   504,   517,   522
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "VAR", "VOID", "MAIN", "END",
  "IF", "ELSE", "WHILE", "DO", "PRINT", "INT", "FLOAT", "CTE_FLOAT",
  "CTE_INT", "CTE_STRING", "ID", "NEQ", "GT", "LT", "PLUS", "MINUS",
  "MULT", "DIV", "ASSIGN", "SEMI", "COLON", "COMMA", "LPAREN", "RPAREN",
  "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "$accept", "programa", "@1",
  "@2", "@3", "DEC_VAR", "VARS", "list_var", "@4", "list_id", "@5",
  "extra_vars", "TYPE", "DEC_FUN", "FUNCS", "@6", "@7", "param", "@8",
  "extra_param", "BODY", "STMT_LIST", "STATEMENT", "assign", "@9",
  "condition", "@10", "@11", "@12", "else_stmt", "@13", "cycle", "@14",
  "@15", "@16", "f_call", "@17", "@18", "f_call_exp", "@19", "print_stmt",
  "print_list", "print_elem", "EXPRESION", "EXP", "TERMINO", "list_term",
  "FACTOR", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    38,    39,    40,    37,    41,    41,    42,    44,
      43,    46,    45,    45,    47,    47,    48,    48,    49,    49,
      51,    52,    50,    54,    53,    53,    55,    55,    56,    57,
      57,    58,    58,    58,    58,    58,    60,    59,    62,    63,
      64,    61,    66,    65,    65,    68,    69,    70,    67,    72,
      73,    71,    75,    74,    74,    74,    76,    77,    77,    78,
      78,    79,    79,    79,    79,    80,    80,    80,    81,    81,
      81,    82,    83,    83,    83,    83,    83,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,    11,     1,     0,     2,     0,
       6,     0,     4,     1,     1,     0,     1,     1,     2,     0,
       0,     0,    12,     0,     5,     0,     2,     0,     3,     2,
       0,     1,     1,     1,     1,     1,     0,     5,     0,     0,
       0,    10,     0,     3,     0,     0,     0,     0,    10,     0,
       0,     7,     0,     4,     1,     0,     5,     3,     1,     1,
       1,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     2,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     3,     0,     7,     0,    19,
       6,    11,     8,     0,     0,     0,    19,     0,     0,    20,
       4,    18,     0,    16,    17,     9,     0,     0,    12,     0,
      25,    30,     0,    15,     0,     0,     0,    45,     0,    49,
       0,    30,    31,    32,    33,    34,    35,     5,    14,    10,
       0,     0,    38,     0,     0,    36,     0,    28,    29,    23,
       7,     0,     0,    77,    76,    60,    75,     0,     0,     0,
       0,    58,    59,    61,    65,    68,     0,    55,    27,     0,
      39,    46,    73,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,    25,    24,     0,
       0,     0,    72,    56,    57,    64,    63,    62,    66,    67,
      71,    69,    70,    37,    50,     0,    26,    21,     0,     0,
       0,    55,     0,    40,     0,    51,    53,    22,    44,    47,
      42,     0,     0,     0,    41,    48,    43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,    27,     9,    10,    12,    29,    13,
      17,    49,    25,    15,    16,    26,   122,    35,    78,    98,
      32,    40,    41,    42,    76,    43,    61,   100,   128,   131,
     133,    44,    53,   101,   132,    45,    56,   120,    95,   115,
      46,    70,    71,    72,    73,    74,   111,    75
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -78
static const yytype_int8 yypact[] =
{
     -78,     7,     6,   -78,    -1,   -78,    -3,    26,    22,    41,
     -78,    23,   -78,    24,    32,    47,    41,    25,    15,   -78,
     -78,   -78,    22,   -78,   -78,   -78,    27,    29,   -78,    28,
      40,    13,    52,    22,    34,    33,    35,   -78,    36,    37,
      38,    13,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
      15,    39,   -78,    42,   -12,   -78,    44,   -78,   -78,   -78,
      26,     4,     4,   -78,   -78,   -78,   -78,     4,     4,     4,
      45,    46,   -78,    -7,    10,    18,     4,     4,    48,    29,
     -78,   -78,   -78,   -78,    49,    43,   -12,     4,     4,     4,
       4,     4,     4,     4,    51,    50,    53,    40,   -78,    54,
      55,    56,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,    59,   -78,   -78,    29,    57,
      58,     4,    63,   -78,    29,   -78,   -78,   -78,    60,   -78,
     -78,    64,    65,    29,   -78,   -78,   -78
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -78,   -78,   -78,   -78,   -78,    19,   -78,    61,   -78,    71,
     -78,   -78,    17,    66,   -78,   -78,   -78,   -14,   -78,   -78,
     -77,    62,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -26,   -78,
     -78,    11,   -78,   -61,   -52,   -48,     3,   -19
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -55
static const yytype_int16 yytable[] =
{
      80,    81,    99,    63,    64,    65,    66,     3,    84,     4,
      67,    68,    87,    88,    89,    94,    96,     5,    69,    63,
      64,    36,    66,    37,     7,    38,    67,    68,    23,    24,
       8,    39,    90,    91,    69,   105,   106,   107,   108,   109,
      11,   123,    92,    93,   110,   110,    14,   129,    82,    83,
      19,   -13,    18,    20,    22,    33,   136,    30,    34,    47,
      96,    31,    50,    55,    51,    52,    54,    59,   124,   130,
     103,    57,    62,    60,    77,    86,    85,    97,   113,    79,
     102,   114,    21,   116,   -54,   125,   118,   119,   121,   117,
     127,   134,   135,    28,    48,   126,   112,   104,     0,     0,
       0,     0,     0,    58
};

static const yytype_int16 yycheck[] =
{
      61,    62,    79,    15,    16,    17,    18,     0,    69,     3,
      22,    23,    19,    20,    21,    76,    77,    18,    30,    15,
      16,     8,    18,    10,    27,    12,    22,    23,    13,    14,
       4,    18,    22,    23,    30,    87,    88,    89,    90,    91,
      18,   118,    24,    25,    92,    93,     5,   124,    67,    68,
      18,    28,    28,     6,    29,    27,   133,    30,    18,     7,
     121,    32,    28,    26,    31,    30,    30,    50,    11,     9,
      27,    33,    30,    34,    30,    29,    31,    29,    27,    60,
      31,    31,    16,    97,    31,    27,    31,    31,    29,    35,
      27,    27,    27,    22,    33,   121,    93,    86,    -1,    -1,
      -1,    -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    38,     0,     3,    18,    39,    27,     4,    41,
      42,    18,    43,    45,     5,    49,    50,    46,    28,    18,
       6,    49,    29,    13,    14,    48,    51,    40,    45,    44,
      30,    32,    56,    27,    18,    53,     8,    10,    12,    18,
      57,    58,    59,    61,    67,    71,    76,     7,    43,    47,
      28,    31,    30,    68,    30,    26,    72,    33,    57,    48,
      34,    62,    30,    15,    16,    17,    18,    22,    23,    30,
      77,    78,    79,    80,    81,    83,    60,    30,    54,    41,
      79,    79,    83,    83,    79,    31,    29,    19,    20,    21,
      22,    23,    24,    25,    79,    74,    79,    29,    55,    56,
      63,    69,    31,    27,    77,    80,    80,    80,    80,    80,
      81,    82,    82,    27,    31,    75,    53,    35,    31,    31,
      73,    29,    52,    56,    11,    27,    74,    27,    64,    56,
       9,    65,    70,    66,    27,    27,    56
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 61 "parser.y"
    {
        // Init semantic structures
        initSemanticCube();
        initFunctionDirectory(&funcDir);
        strcpy(currentFunction, "global");

        // init quad struct
        initQuadrupleGenerator(&quadGenerator);
    ;}
    break;

  case 3:
#line 71 "parser.y"
    {
        if (verbose_mode) {
            printf("Compiling program %s\n", (yyvsp[(3) - (3)].sval));
        }
    ;}
    break;

  case 4:
#line 77 "parser.y"
    {
        strcpy(currentFunction, "main");
        // Guardar posición donde empieza el main
        mainStartQuad = quadGenerator.quadQueue.count;
    ;}
    break;

  case 5:
#line 83 "parser.y"
    {
        // Agregar cuádruplo EOF al final del programa
        addQuadruple(&quadGenerator.quadQueue, OP_EOF, -1, -1, -1);
        
        if (verbose_mode) {
            printf("Compilation completed successfully\n");
            printGeneratedQuadruples(&quadGenerator);
            printf("\n=== INICIANDO VM ===\n");
        }
        
        // Ejecutar la máquina virtual
        VirtualMachine vm;
        initVirtualMachine(&vm, &quadGenerator.quadQueue, &quadGenerator.constTable);
        
        // Empezar ejecución en el main en lugar del cuádruplo 0
        vm.instructionPointer = mainStartQuad;
        
        executeProgram(&vm);
    ;}
    break;

  case 9:
#line 115 "parser.y"
    {
        currentType = (yyvsp[(3) - (3)].type);
    ;}
    break;

  case 11:
#line 123 "parser.y"
    {
        // punto neuralgico - add var to cur context
        int address;
        int res;
        // assign virtual mem based on type and scope
        if (strcmp(currentFunction, "global") == 0) {
            address = getNextAddress(&quadGenerator.memCounters, currentType, 1);
            res = addVar(&funcDir.globalVars, (yyvsp[(1) - (1)].sval), currentType, address);
        } else {
            address = getNextAddress(&quadGenerator.memCounters, currentType, 0);
            Function *func = findFunction(&funcDir, currentFunction);
            if (func != NULL) {
                res = addVar(&func->localVars, (yyvsp[(1) - (1)].sval), currentType, address);    
            } else {
                res = 0;
                yyerror("Function not found");
            }
        }

        if (res == 0) {
            char error[100];
            sprintf(error, "Semantic error: Variable '%s' already declared", (yyvsp[(1) - (1)].sval));
            yyerror(error);
        } else if (res == -1) {
            yyerror("Semantic error: Variable limit exceeded");
        }
    ;}
    break;

  case 13:
#line 152 "parser.y"
    {
        // Punto neuralgico - add var to cur context
        int address;
        int res;
        // assign virtual mem based on type and scope
        if (strcmp(currentFunction, "global") == 0) {
            address = getNextAddress(&quadGenerator.memCounters, currentType, 1);
            res = addVar(&funcDir.globalVars, (yyvsp[(1) - (1)].sval), currentType, address);
        } else {
            address = getNextAddress(&quadGenerator.memCounters, currentType, 0);
            Function *func = findFunction(&funcDir, currentFunction);
            if (func != NULL) {
                res = addVar(&func->localVars, (yyvsp[(1) - (1)].sval), currentType, address);
            } else {
                res = 0;
                yyerror("Function not found");
            }
        }
        
        if (res == 0) {
            char error[100];
            sprintf(error, "Semantic error: Variable '%s' already declared", (yyvsp[(1) - (1)].sval));
            yyerror(error);
        } else if (res == -1) {
            yyerror("Semantic error: Variable limit exceeded");
        }
    ;}
    break;

  case 16:
#line 188 "parser.y"
    {
        (yyval.type) = TYPE_INT;
    ;}
    break;

  case 17:
#line 192 "parser.y"
    {
        (yyval.type) = TYPE_FLOAT;
    ;}
    break;

  case 20:
#line 204 "parser.y"
    {
        // punto neuralgico - add func to funcDir
        int res = addFunction(&funcDir, (yyvsp[(2) - (2)].sval));

        if (res == 0) {
            char error[100];
            sprintf(error, "Semantic error: Function '%s' already declared", (yyvsp[(2) - (2)].sval));
            yyerror(error);
        } else if (res == -1) {
            yyerror("Semantic error: Functions limit exceeded");
        }

        // change context to new function
        strcpy(currentFunction, (yyvsp[(2) - (2)].sval));

        // store starting quadruple for function
        Function *func = findFunction(&funcDir, (yyvsp[(2) - (2)].sval));
        if (func != NULL) {
            func->startQuad = quadGenerator.quadQueue.count;
        }

    ;}
    break;

  case 21:
#line 227 "parser.y"
    {
        // add ENDPROC quad
        addQuadruple(&quadGenerator.quadQueue, OP_ENDPROC, -1, -1, -1);

        // go back to global context
        strcpy(currentFunction, "global");
    ;}
    break;

  case 23:
#line 239 "parser.y"
    {
        // punto neuralgico - add param to function
        Function *func = findFunction(&funcDir, currentFunction);
        if (func != NULL) {
            // assign virtual mem address for param
            int address = getNextAddress(&quadGenerator.memCounters, (yyvsp[(3) - (3)].type), 0); // 0 pq es local
            int res = addParameter(func, (yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].type), address);

            if (res == 0) {
                char error[100];
                sprintf(error, "Semantic error: Parameter '%s' already declared", (yyvsp[(1) - (3)].sval));
                yyerror(error);
            } else if (res == -1) {
                yyerror("Semantic error: Parameter limit exceeded");
            }
        } else {
            yyerror("Semantic error: Function not found to add param");
        }
    ;}
    break;

  case 36:
#line 286 "parser.y"
    {
        // check if var exists
        Variable *var = findVariable(&funcDir, currentFunction, (yyvsp[(1) - (2)].sval));
        if (var == NULL) {
            char error[100];
            sprintf(error, "Semantic error: Variable '%s' not declared", (yyvsp[(1) - (2)].sval));
            yyerror(error);
        }
    ;}
    break;

  case 37:
#line 296 "parser.y"
    {
        // generate assign quad
        generateAssignment(&quadGenerator, (yyvsp[(1) - (5)].sval), &funcDir, currentFunction);
    ;}
    break;

  case 38:
#line 304 "parser.y"
    {
        // process the expression before evaluating it
    ;}
    break;

  case 39:
#line 308 "parser.y"
    {
        if ((yyvsp[(4) - (4)].type) != TYPE_BOOL) {
            yyerror("Semantic error: if condition must be boolean expression");
        }
        
        // GOTOF quadruple after evaluating condition
        startIfStatement(&quadGenerator);
    ;}
    break;

  case 40:
#line 317 "parser.y"
    {
        // For an IF with no ELSE, we need to fill the jump location
        // to the end of the IF statement
        if (yychar != ELSE) {
            endIfStatement(&quadGenerator);
        }
    ;}
    break;

  case 42:
#line 329 "parser.y"
    {
        // Process the start of ELSE - generate jump to end of if-else
        // and fill the GOTOF jump location
        processElseStatement(&quadGenerator);
    ;}
    break;

  case 43:
#line 335 "parser.y"
    {
        // Fill the GOTO jump location at the end of if-else
        endIfStatement(&quadGenerator);
    ;}
    break;

  case 45:
#line 344 "parser.y"
    {
        // Mark the start of the while loop
        startWhileLoop(&quadGenerator);
    ;}
    break;

  case 46:
#line 349 "parser.y"
    {
        if ((yyvsp[(4) - (4)].type) != TYPE_BOOL) {
            yyerror("Semantic error: while condition must be boolean expression");
        }
        
        // Process condition and generate GOTOF quadruple
        processWhileCondition(&quadGenerator);
    ;}
    break;

  case 47:
#line 358 "parser.y"
    {
        // Generate GOTO to beginning of while loop and fill the GOTOF jump
        endWhileLoop(&quadGenerator);
    ;}
    break;

  case 49:
#line 367 "parser.y"
    {
        // check that function is declared
        Function *func = findFunction(&funcDir, (yyvsp[(1) - (1)].sval));
        if (func == NULL) {
            char error[100];
            sprintf(error, "Semantic error: Function '%s' not declared", (yyvsp[(1) - (1)].sval));
            yyerror(error);
        } else {
            // punto neuralgico - start function call (generate ERA)
            startFunctionCall(&quadGenerator, (yyvsp[(1) - (1)].sval), &funcDir);
        }
        
        // store function name for parameter processing
        strcpy(currentFunctionCall, (yyvsp[(1) - (1)].sval));
        currentParamIndex = 0;
    ;}
    break;

  case 50:
#line 385 "parser.y"
    {
        // punto neuralgico - end function call (generate GOSUB)
        endFunctionCall(&quadGenerator, currentFunctionCall, &funcDir);
    ;}
    break;

  case 52:
#line 394 "parser.y"
    {
        // punto neuralgico - process function parameter
        processFunctionParameter(&quadGenerator, currentParamIndex);
        currentParamIndex++;
    ;}
    break;

  case 54:
#line 401 "parser.y"
    {
        // punto neuralgico - process function parameter
        processFunctionParameter(&quadGenerator, currentParamIndex);
        currentParamIndex++;
    ;}
    break;

  case 59:
#line 420 "parser.y"
    {
        // generate print quad
        generatePrint(&quadGenerator);
    ;}
    break;

  case 60:
#line 425 "parser.y"
    {
        processStringConstant(&quadGenerator, (yyvsp[(1) - (1)].sval));
        generatePrint(&quadGenerator);
    ;}
    break;

  case 61:
#line 433 "parser.y"
    {
        (yyval.type) = (yyvsp[(1) - (1)].type);
    ;}
    break;

  case 62:
#line 437 "parser.y"
    {
        processRelationalOperator(&quadGenerator, OP_LT);
        (yyval.type) = TYPE_BOOL;
    ;}
    break;

  case 63:
#line 442 "parser.y"
    {
        processRelationalOperator(&quadGenerator, OP_GT);
        (yyval.type) = TYPE_BOOL;
    ;}
    break;

  case 64:
#line 447 "parser.y"
    {
        processRelationalOperator(&quadGenerator, OP_NEQ);
        (yyval.type) = TYPE_BOOL;
    ;}
    break;

  case 65:
#line 455 "parser.y"
    {
        (yyval.type) = (yyvsp[(1) - (1)].type);
    ;}
    break;

  case 66:
#line 459 "parser.y"
    {
        processOperator(&quadGenerator, OP_PLUS);
        (yyval.type) = peekType(&quadGenerator.types);
    ;}
    break;

  case 67:
#line 464 "parser.y"
    {
        processOperator(&quadGenerator, OP_MINUS);
        (yyval.type) = peekType(&quadGenerator.types);
    ;}
    break;

  case 68:
#line 472 "parser.y"
    {
        (yyval.type) = (yyvsp[(1) - (1)].type);
    ;}
    break;

  case 69:
#line 476 "parser.y"
    {
        processOperator(&quadGenerator, OP_MULT);
        (yyval.type) = peekType(&quadGenerator.types);
    ;}
    break;

  case 70:
#line 481 "parser.y"
    {
        processOperator(&quadGenerator, OP_DIV);
        (yyval.type) = peekType(&quadGenerator.types);
  ;}
    break;

  case 72:
#line 493 "parser.y"
    {
        (yyval.type) = (yyvsp[(2) - (3)].type);
    ;}
    break;

  case 73:
#line 497 "parser.y"
    {
    (yyval.type) = (yyvsp[(2) - (2)].type);
  ;}
    break;

  case 74:
#line 501 "parser.y"
    {
    (yyval.type) = (yyvsp[(2) - (2)].type);
  ;}
    break;

  case 75:
#line 505 "parser.y"
    {
    Variable *var = findVariable(&funcDir, currentFunction, (yyvsp[(1) - (1)].sval));
    if (var == NULL) {
        char error[100];
        sprintf(error, "Semantic error: Variable '%s' not declared", (yyvsp[(1) - (1)].sval));
        yyerror(error);
        (yyval.type) = TYPE_ERROR;
    } else {
        processOperand(&quadGenerator, (yyvsp[(1) - (1)].sval), &funcDir, currentFunction);
        (yyval.type) = var->type;
    }
  ;}
    break;

  case 76:
#line 518 "parser.y"
    {
    processIntConstant(&quadGenerator, (yyvsp[(1) - (1)].ival));
    (yyval.type) = TYPE_INT;
  ;}
    break;

  case 77:
#line 523 "parser.y"
    {
    processFloatConstant(&quadGenerator, (yyvsp[(1) - (1)].fval));
    (yyval.type) = TYPE_FLOAT;
  ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2018 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 529 "parser.y"


int main(int argc, char *argv[]) {
    // Procesar argumentos de línea de comandos
    if (argc > 1 && (strcmp(argv[1], "-q") == 0 || strcmp(argv[1], "--quiet") == 0)) {
        verbose_mode = 0;
        if (verbose_mode) printf("Modo silencioso activado\n");
    } else if (argc > 1 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--verbose") == 0)) {
        verbose_mode = 1;
        if (verbose_mode) printf("Modo verbose activado\n");
    }
    
    return yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "Error %s\n", s);
}
