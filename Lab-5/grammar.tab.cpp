/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 16 "grammar.ypp" /* yacc.c:337  */

#include <stdio.h>

  extern int yylex();
  extern int yyerror(char *);

#line 77 "grammar.tab.cpp" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "grammar.tab.hpp".  */
#ifndef YY_YY_GRAMMAR_TAB_HPP_INCLUDED
# define YY_YY_GRAMMAR_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 3 "grammar.ypp" /* yacc.c:352  */

#include "errors.h"
#include "location.h"
#include "lexer.h"
#include "ast.h"
#include <typeinfo>
#include "mips.h"
#include <vector>
#include <map>

  using namespace std;

#line 123 "grammar.tab.cpp" /* yacc.c:352  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ELSE = 258,
    FOR = 259,
    IF = 260,
    RETURN = 261,
    WHILE = 262,
    PTR_OP = 263,
    INC_OP = 264,
    DEC_OP = 265,
    AND_OP = 266,
    OR_OP = 267,
    LT = 268,
    GT = 269,
    LE_OP = 270,
    GE_OP = 271,
    EQ_OP = 272,
    NE_OP = 273,
    DO = 274,
    NOT = 275,
    AMP = 276,
    TILDE = 277,
    STAR = 278,
    ASSIGN = 279,
    OPEN_BRACKET = 280,
    CLOSED_BRACKET = 281,
    OPEN_CURLY = 282,
    CLOSED_CURLY = 283,
    OPEN_SQUARE = 284,
    CLOSED_SQUARE = 285,
    SEMI = 286,
    COMMA = 287,
    DOT = 288,
    PLUS = 289,
    MINUS = 290,
    DIVIDE = 291,
    MODULUS = 292,
    PIPE = 293,
    XOR = 294,
    QUES = 295,
    COLON = 296,
    ID = 297,
    BOOL = 298,
    CHAR = 299,
    INT = 300,
    FLOAT = 301,
    VOID = 302,
    NUM = 303,
    REAL = 304,
    STRING_LITERAL = 305,
    BOOLEAN = 306,
    UPLUS = 308,
    UMINUS = 309
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 23 "grammar.ypp" /* yacc.c:352  */

  char *name;
  enum Type type;
  
  Declaration *decl;
  FuncDecl *funcDecl;
  Identifier *varDecl;
  vector<IntConst *> *dimList;

  StatementBlock *stmtBlock;
  vector<Statement *> *stmtList;
  map<string, Identifier *> *varDecls;
  vector<Identifier *> *parList;
  vector<Expression *> *argList;
  
  Statement *stmt;
  ExprStatement *exprStmt;
  SelStatement *selStmt;
  IterStatement *iterStmt;

  Expression *expr;
  OpExpression *opExpr;
  Operator *op;
  Access *access;

  int intConst_t;
  bool boolConst_t;
  char *stringConst_t;
  double doubleConst_t;

  IntConst *intConst;
  BoolConst *boolConst;
  StringConst *stringConst;
  DoubleConst *doubleConst;

#line 225 "grammar.tab.cpp" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_GRAMMAR_TAB_HPP_INCLUDED  */



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
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   162

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

#define YYUNDEFTOK  2
#define YYMAXUTOK   309

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   109,   109,   170,   171,   175,   176,   180,   181,   185,
     186,   190,   205,   209,   210,   214,   215,   216,   220,   221,
     222,   223,   224,   228,   229,   233,   234,   235,   236,   237,
     238,   242,   243,   244,   245,   246,   247,   254,   255,   259,
     262,   269,   270,   271,   275,   276,   280,   281,   282,   283,
     284,   288,   289,   290,   291,   295,   296,   297,   301,   302,
     303,   307,   308,   309,   313,   314,   318,   319,   323,   324,
     328,   329,   333,   334,   338,   339
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ELSE", "FOR", "IF", "RETURN", "WHILE",
  "PTR_OP", "INC_OP", "DEC_OP", "AND_OP", "OR_OP", "LT", "GT", "LE_OP",
  "GE_OP", "EQ_OP", "NE_OP", "DO", "NOT", "AMP", "TILDE", "STAR", "ASSIGN",
  "OPEN_BRACKET", "CLOSED_BRACKET", "OPEN_CURLY", "CLOSED_CURLY",
  "OPEN_SQUARE", "CLOSED_SQUARE", "SEMI", "COMMA", "DOT", "PLUS", "MINUS",
  "DIVIDE", "MODULUS", "PIPE", "XOR", "QUES", "COLON", "ID", "BOOL",
  "CHAR", "INT", "FLOAT", "VOID", "NUM", "REAL", "STRING_LITERAL",
  "BOOLEAN", "\"UIF\"", "UPLUS", "UMINUS", "$accept", "program",
  "declaration_list", "declaration", "variable_declaration",
  "bracket_list", "function_declaration", "statement_block",
  "variable_declarations", "parameter_list", "type_specifier",
  "statement_list", "statement", "primary_expression", "id_arr",
  "argument_bracket_list", "argument_expression_list", "unary_expression",
  "unary_operator", "multiplicative_expression", "additive_expression",
  "relational_expression", "equality_expression", "logical_and_expression",
  "conditional_expression", "assignment_expression", "iteration_statement",
  "selection_statement", "expression_statement", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309
};
# endif

#define YYPACT_NINF -65

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-65)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -65,     2,   112,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -33,   -21,   112,   -30,   -65,    16,   -19,   -10,
      -1,    -4,   -65,    11,   112,   -65,   -65,    18,   -65,   -65,
      26,   -65,   112,   -65,   -65,    40,    15,    56,    63,    79,
      61,    83,   -65,   -65,   -65,    80,   -65,   -65,   -65,   -65,
     -13,   -65,   -65,   -65,   -65,   -65,   -65,    89,   -65,    80,
     -22,    17,    47,    55,   105,   108,    93,   -65,   -65,   -65,
      92,    80,   -65,    94,    80,   106,    80,    80,   102,    80,
     -65,   -65,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,   -65,    92,   107,   -65,   109,   -65,   -15,
     -65,   113,    80,   -65,   -65,   -65,   -65,   -22,   -22,    17,
      17,    47,    47,    55,   105,    80,    49,    49,   -65,    80,
     -65,   130,   110,   134,   -65,   -65,   -65,    49,    49,   -65,
     -65
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    22,    19,    20,    21,    18,     3,
       5,     6,     0,     0,    17,     0,     7,     0,     0,     0,
       0,     0,     8,     0,     0,    16,    10,     0,    14,    11,
       0,     9,    24,    15,    13,     0,     0,     0,     0,     0,
       0,     0,    50,    49,    48,     0,    12,    74,    46,    47,
      37,    32,    33,    34,    28,    23,    44,    31,    51,     0,
      55,    58,    61,    64,    66,    68,     0,    27,    26,    25,
       0,     0,    29,     0,     0,     0,    43,     0,    38,     0,
      31,    45,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    75,     0,     0,    30,     0,    35,     0,
      42,     0,     0,    69,    52,    53,    54,    56,    57,    59,
      60,    62,    63,    65,    67,     0,     0,     0,    36,     0,
      40,     0,     0,    73,    70,    41,    39,     0,     0,    71,
      72
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -65,   -65,   -65,   -65,   129,   -65,   -65,   115,   -65,   -65,
       9,   -65,   -50,   -65,    62,   -65,   -65,   -56,   -65,     8,
      19,    29,    48,    70,   -65,   -40,   -65,   -65,   -64
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     9,    10,    17,    11,    54,    32,    18,
      12,    36,    55,    56,    57,    78,    99,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      73,    82,     3,    81,    14,    75,    94,    23,    15,    13,
      16,   118,    76,    24,    83,    84,    77,   119,    20,    38,
      39,    40,    41,    19,    42,    43,   104,   105,   106,    26,
     115,    95,    25,    30,    97,    44,   100,   101,    28,   103,
      45,    35,    28,    46,    27,    21,    47,    22,    31,    48,
      49,    85,    86,    38,    39,    40,    41,    50,    42,    43,
      87,    88,   121,    51,    52,    53,   123,   124,    33,    44,
      42,    43,    89,    90,    45,   122,    28,   129,   130,   125,
      47,    44,    37,    48,    49,    15,    45,    16,    70,    42,
      43,    50,    72,   107,   108,    48,    49,    51,    52,    53,
      44,    42,    43,    50,    71,    45,   109,   110,    74,    51,
      52,    53,    44,    79,    48,    49,    91,    45,   111,   112,
      92,    80,    50,    47,    93,    96,    48,    49,    51,    52,
      53,   102,    98,   116,    50,   117,   127,   128,    29,   113,
      51,    52,    53,   120,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,     4,     5,     6,     7,     8,
     126,    34,   114
};

static const yytype_uint8 yycheck[] =
{
      40,    23,     0,    59,    25,    45,    70,    26,    29,    42,
      31,    26,    25,    32,    36,    37,    29,    32,    48,     4,
       5,     6,     7,    14,     9,    10,    82,    83,    84,    30,
      94,    71,    42,    24,    74,    20,    76,    77,    27,    79,
      25,    32,    27,    28,    48,    29,    31,    31,    30,    34,
      35,    34,    35,     4,     5,     6,     7,    42,     9,    10,
      13,    14,   102,    48,    49,    50,   116,   117,    42,    20,
       9,    10,    17,    18,    25,   115,    27,   127,   128,   119,
      31,    20,    42,    34,    35,    29,    25,    31,    25,     9,
      10,    42,    31,    85,    86,    34,    35,    48,    49,    50,
      20,     9,    10,    42,    25,    25,    87,    88,    25,    48,
      49,    50,    20,    24,    34,    35,    11,    25,    89,    90,
      12,    59,    42,    31,    31,    31,    34,    35,    48,    49,
      50,    29,    26,    26,    42,    26,    26,     3,    23,    91,
      48,    49,    50,    30,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    43,    44,    45,    46,    47,
      30,    32,    92
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    56,    57,     0,    43,    44,    45,    46,    47,    58,
      59,    61,    65,    42,    25,    29,    31,    60,    64,    65,
      48,    29,    31,    26,    32,    42,    30,    48,    27,    62,
      65,    30,    63,    42,    59,    65,    66,    42,     4,     5,
       6,     7,     9,    10,    20,    25,    28,    31,    34,    35,
      42,    48,    49,    50,    62,    67,    68,    69,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      25,    25,    31,    80,    25,    80,    25,    29,    70,    24,
      69,    72,    23,    36,    37,    34,    35,    13,    14,    17,
      18,    11,    12,    31,    83,    80,    31,    80,    26,    71,
      80,    80,    29,    80,    72,    72,    72,    74,    74,    75,
      75,    76,    76,    77,    78,    83,    26,    26,    26,    32,
      30,    80,    80,    67,    67,    80,    30,    26,     3,    67,
      67
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    58,    59,    59,    60,
      60,    61,    62,    63,    63,    64,    64,    64,    65,    65,
      65,    65,    65,    66,    66,    67,    67,    67,    67,    67,
      67,    68,    68,    68,    68,    68,    68,    69,    69,    70,
      70,    71,    71,    71,    72,    72,    73,    73,    73,    73,
      73,    74,    74,    74,    74,    75,    75,    75,    76,    76,
      76,    77,    77,    77,    78,    78,    79,    79,    80,    80,
      81,    81,    82,    82,    83,    83
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     3,     4,     4,
       3,     6,     4,     2,     0,     4,     2,     0,     1,     1,
       1,     1,     1,     2,     0,     1,     1,     1,     1,     2,
       3,     1,     1,     1,     1,     3,     4,     1,     2,     4,
       3,     3,     1,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       5,     7,     7,     5,     1,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 109 "grammar.ypp" /* yacc.c:1652  */
    {
  setParent(global_sym_table, NULL);
  Identifier *identifier;
  FuncDecl *function;
  
  for (map<string, Declaration *>::iterator i = global_sym_table->begin();
       i != global_sym_table->end(); ++i)
  {
    if(typeid(*(i->second)) == typeid(FuncDecl)){
      function = dynamic_cast<FuncDecl *>(i->second);
      function->stmt_block->CheckStatement();
    }
  }
  
  if(numErrors == 0){
    printf(".data\n");
    for (map<string, Declaration *>::iterator i = global_sym_table->begin(); i != global_sym_table->end(); ++i)
	  {
      if(typeid(*(i->second)) == typeid(Identifier)){
        identifier = dynamic_cast<Identifier *>(i->second);
        identifier->is_global = true;
        identifier->label = "v_" + identifier->name;
        int pdt = 1;
        if(identifier->is_array){
          for(int j = 0; j<identifier->dim_list->size(); j++){
            pdt *= (*identifier->dim_list)[j]->val;
            if(pdt == 0){
              OutputError((*identifier->dim_list)[j]->loc,
                          "Array size can't be zero");
              return -1;
            }
          }
        }
        printf("%s: .word ", identifier->label.c_str());
        for(int j = 0; j<pdt-1; j++){
          printf("0, ");
        }
        printf("0 \n");
      }      
 	  }
    EmitPreamble();
    bool found_main = false;
    for (map<string, Declaration *>::iterator i = global_sym_table->begin(); i != global_sym_table->end(); ++i)
	  {
      if(typeid(*(i->second)) == typeid(FuncDecl)){
        i->second->Emit();
        if(i->second->name == "main"){
          found_main = true;
          printf("li $a0 0\n");
          printf("li $v0 17\n");
          printf("syscall\n");
        }
      }      
 	  }
    if(!found_main)
      NoMainFound();
  }
 }
#line 1593 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 3:
#line 170 "grammar.ypp" /* yacc.c:1652  */
    {CheckAndInsertIntoSymTable(global_sym_table, (yyvsp[0].decl));}
#line 1599 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 4:
#line 171 "grammar.ypp" /* yacc.c:1652  */
    {global_sym_table = new map<string, Declaration *>;}
#line 1605 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 5:
#line 175 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.decl) = (yyvsp[0].varDecl);}
#line 1611 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 6:
#line 176 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.decl) = (yyvsp[0].funcDecl);}
#line 1617 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 7:
#line 180 "grammar.ypp" /* yacc.c:1652  */
    {((yyval.varDecl) = new Identifier((yylsp[-1]), (yyvsp[-2].type), (yyvsp[-1].name)));}
#line 1623 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 8:
#line 181 "grammar.ypp" /* yacc.c:1652  */
    {((yyval.varDecl) = new Identifier((yylsp[-2]), (yyvsp[-3].type), (yyvsp[-2].name), (yyvsp[-1].dimList)));}
#line 1629 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 9:
#line 185 "grammar.ypp" /* yacc.c:1652  */
    {((yyval.dimList) = (yyvsp[-3].dimList))->push_back(new IntConst((yylsp[-1]), (yyvsp[-1].intConst_t)));}
#line 1635 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 10:
#line 186 "grammar.ypp" /* yacc.c:1652  */
    {((yyval.dimList) = new vector<IntConst *>)->push_back(new IntConst((yylsp[-1]), (yyvsp[-1].intConst_t)));}
#line 1641 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 11:
#line 190 "grammar.ypp" /* yacc.c:1652  */
    {
  // Check whether var decl conflict with parameter decl
  for(int i = 0; i<(yyvsp[-2].parList)->size(); i++){
    if((yyvsp[0].stmtBlock)->symbol_table->find((*(yyvsp[-2].parList))[i]->name) != (yyvsp[0].stmtBlock)->symbol_table->end()){
      DeclConflict((*(yyvsp[0].stmtBlock)->symbol_table)[(*(yyvsp[-2].parList))[i]->name], (*(yyvsp[-2].parList))[i]);
      //free((*$6->symbol_table)[(*$4)[i]->name]);
      (yyvsp[0].stmtBlock)->symbol_table->erase((*(yyvsp[-2].parList))[i]->name);
    }
  }
  (yyval.funcDecl) = new FuncDecl((yylsp[-4]), (yylsp[-5]), (yyvsp[-5].type), (yyvsp[-4].name), (yyvsp[-2].parList), (yyvsp[0].stmtBlock));
  (yyval.funcDecl)->CalcOffsets();
}
#line 1658 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 12:
#line 205 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.stmtBlock) = new StatementBlock((yyvsp[-2].varDecls), (yyvsp[-1].stmtList));}
#line 1664 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 13:
#line 209 "grammar.ypp" /* yacc.c:1652  */
    {CheckAndInsertIntoSymTable((yyval.varDecls) = (yyvsp[-1].varDecls), (yyvsp[0].varDecl));}
#line 1670 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 14:
#line 210 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.varDecls) = new map<string, Identifier *>;}
#line 1676 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 15:
#line 214 "grammar.ypp" /* yacc.c:1652  */
    {CheckAndInsertIntoSymTable(((yyval.parList) = (yyvsp[-3].parList)), (new Identifier((yylsp[0]), (yyvsp[-1].type), (yyvsp[0].name))));}
#line 1682 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 16:
#line 215 "grammar.ypp" /* yacc.c:1652  */
    {((yyval.parList) = new vector<Identifier *>); (yyval.parList)->push_back(new Identifier((yylsp[0]), (yyvsp[-1].type), (yyvsp[0].name)));}
#line 1688 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 17:
#line 216 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.parList) = new vector<Identifier *>;}
#line 1694 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 23:
#line 228 "grammar.ypp" /* yacc.c:1652  */
    {((yyval.stmtList) = (yyvsp[-1].stmtList))->push_back((yyvsp[0].stmt));}
#line 1700 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 24:
#line 229 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.stmtList) = new vector<Statement *>;}
#line 1706 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 25:
#line 233 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.stmt) = (yyvsp[0].exprStmt);}
#line 1712 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 26:
#line 234 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.stmt) = (yyvsp[0].selStmt);}
#line 1718 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 27:
#line 235 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.stmt) = (yyvsp[0].iterStmt);}
#line 1724 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 28:
#line 236 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.stmt) = (yyvsp[0].stmtBlock);}
#line 1730 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 29:
#line 237 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.stmt) = new ReturnStatement((yylsp[-1]), NULL);}
#line 1736 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 30:
#line 238 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.stmt) = new ReturnStatement((yylsp[-2]), (yyvsp[-1].expr));}
#line 1742 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 31:
#line 242 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = (yyvsp[0].access);}
#line 1748 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 32:
#line 243 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.expr) = new IntConst((yylsp[0]), (yyvsp[0].intConst_t)); }
#line 1754 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 33:
#line 244 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.expr) = new DoubleConst((yylsp[0]), (yyvsp[0].doubleConst_t)); }
#line 1760 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 34:
#line 245 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.expr) = new StringConst((yylsp[0]), (yyvsp[0].stringConst_t)); }
#line 1766 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 35:
#line 246 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 1772 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 36:
#line 247 "grammar.ypp" /* yacc.c:1652  */
    {
  (yyval.expr) = new Call((yylsp[-3]), *(new string((yyvsp[-3].name))), (yyvsp[-1].argList));
 }
#line 1780 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 37:
#line 254 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.access) = new Access((yylsp[0]), *(new string((yyvsp[0].name)))); }
#line 1786 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 38:
#line 255 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.access) = new Access ((yylsp[-1]), *(new string((yyvsp[-1].name))), (yyvsp[0].argList));}
#line 1792 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 39:
#line 259 "grammar.ypp" /* yacc.c:1652  */
    {
  ((yyval.argList) = (yyvsp[-3].argList))->push_back((yyvsp[-1].expr));
 }
#line 1800 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 40:
#line 262 "grammar.ypp" /* yacc.c:1652  */
    {
  (yyval.argList) = new vector<Expression *>;
  (yyval.argList)->push_back((yyvsp[-1].expr));
 }
#line 1809 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 41:
#line 269 "grammar.ypp" /* yacc.c:1652  */
    {((yyval.argList) = (yyvsp[-2].argList))->push_back((yyvsp[0].expr));}
#line 1815 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 42:
#line 270 "grammar.ypp" /* yacc.c:1652  */
    {((yyval.argList) = new vector<Expression *>)->push_back((yyvsp[0].expr));}
#line 1821 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 43:
#line 271 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.argList) = new vector<Expression *>;}
#line 1827 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 44:
#line 275 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1833 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 45:
#line 276 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.expr) = new OpExpression((yyvsp[-1].op), (yyvsp[0].expr)); }
#line 1839 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 46:
#line 280 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.op) = new Operator((yylsp[0]), PLUS); }
#line 1845 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 47:
#line 281 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.op) = new Operator((yylsp[0]), MINUS); }
#line 1851 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 48:
#line 282 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.op) = new Operator((yylsp[0]), NOT); }
#line 1857 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 49:
#line 283 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.op) = new Operator((yylsp[0]), DEC_OP);}
#line 1863 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 50:
#line 284 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.op) = new Operator((yylsp[0]), INC_OP);}
#line 1869 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 51:
#line 288 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 1875 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 52:
#line 289 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = new OpExpression(new Operator((yylsp[-1]), STAR), (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1881 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 53:
#line 290 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = new OpExpression(new Operator((yylsp[-1]), DIVIDE), (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1887 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 54:
#line 291 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = new OpExpression(new Operator((yylsp[-1]), MODULUS), (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1893 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 55:
#line 295 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 1899 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 56:
#line 296 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = new OpExpression(new Operator((yylsp[-1]), PLUS), (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1905 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 57:
#line 297 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = new OpExpression(new Operator((yylsp[-1]), MINUS), (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1911 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 58:
#line 301 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 1917 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 59:
#line 302 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = new OpExpression(new Operator((yylsp[-1]), LT), (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1923 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 60:
#line 303 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = new OpExpression(new Operator((yylsp[-1]), GT), (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1929 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 61:
#line 307 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 1935 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 62:
#line 308 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = new OpExpression(new Operator((yylsp[-1]), EQ_OP), (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1941 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 63:
#line 309 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = new OpExpression(new Operator((yylsp[-1]), NE_OP), (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1947 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 64:
#line 313 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 1953 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 65:
#line 314 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.expr) = new OpExpression(new Operator((yylsp[-1]), AND_OP), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1959 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 66:
#line 318 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = (yyvsp[0].expr);}
#line 1965 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 67:
#line 319 "grammar.ypp" /* yacc.c:1652  */
    {(yyval.expr) = new OpExpression(new Operator((yylsp[-1]), OR_OP), (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1971 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 68:
#line 323 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1977 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 69:
#line 324 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.expr) = new OpExpression(new Operator((yylsp[-1]), ASSIGN), (yyvsp[-2].access), (yyvsp[0].expr)); }
#line 1983 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 70:
#line 328 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.iterStmt) = new IterStatement((yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 1989 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 71:
#line 329 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.iterStmt) = new IterStatement((yyvsp[-4].exprStmt), (yyvsp[-3].exprStmt), (yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 1995 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 72:
#line 333 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.selStmt) = new SelStatement((yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 2001 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 73:
#line 334 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.selStmt) = new SelStatement((yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 2007 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 74:
#line 338 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.exprStmt) = new ExprStatement(NULL); }
#line 2013 "grammar.tab.cpp" /* yacc.c:1652  */
    break;

  case 75:
#line 339 "grammar.ypp" /* yacc.c:1652  */
    { (yyval.exprStmt) = new ExprStatement((yyvsp[-1].expr));}
#line 2019 "grammar.tab.cpp" /* yacc.c:1652  */
    break;


#line 2023 "grammar.tab.cpp" /* yacc.c:1652  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 342 "grammar.ypp" /* yacc.c:1918  */

#include <stdio.h>

extern char yytext[];

int yyerror(char *s){
  fflush(stdout);
  printf("%s\n", s);
}

int main(){
  InitScanner();
  InitCodeGenerator();
  //yydebug = 1;
  return yyparse();
}


