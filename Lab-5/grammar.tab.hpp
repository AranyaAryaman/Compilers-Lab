/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
#line 3 "grammar.ypp" /* yacc.c:1921  */

#include "errors.h"
#include "location.h"
#include "lexer.h"
#include "ast.h"
#include <typeinfo>
#include "mips.h"
#include <vector>
#include <map>

  using namespace std;

#line 61 "grammar.tab.hpp" /* yacc.c:1921  */

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
#line 23 "grammar.ypp" /* yacc.c:1921  */

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

#line 163 "grammar.tab.hpp" /* yacc.c:1921  */
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
