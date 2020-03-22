#ifndef _SQL_RUNNER_
#define _SQL_RUNNER_

#include "sql_runner.h"

typedef struct ast {
	int operation;		  // or and not >= <= > < = <> != (both relational and logical)

	// use this for intermediate nodes
	// (those with relational (and or not) operators)
	struct ast *child[2];		 // more conditions

	// and this for leaf nodes
	// (those with logical (>= <= > < = <> !=) operators)
	int operand_type[2];		// int str var
	char *str[2];				// salary name
	double num[2];					// 10 20
} ast;

typedef struct clq {
	char *str;
	struct clq *next;
} clq;

//**** WARNING: Preprocessor Fuckery Ahead ****

// E_ENUM takes a macro and applies it to all values
#define E_ENUM(E_FUNC) \
	E_FUNC(E_DUMMY)    \
	E_FUNC(E_SELECT)   \
	E_FUNC(E_CARTPROD) \
	E_FUNC(E_EQUIJOIN) \
	E_FUNC(E_PROJECT)  \
	E_FUNC(E_LT)       \
	E_FUNC(E_LTEQ)     \
	E_FUNC(E_GT)       \
	E_FUNC(E_GTEQ)     \
	E_FUNC(E_EQ)       \
	E_FUNC(E_NEQ)      \
	E_FUNC(E_STR)      \
	E_FUNC(E_NUM)      \
	E_FUNC(E_VAR)      \
	E_FUNC(E_AND)      \
	E_FUNC(E_OR)       \
	E_FUNC(E_NOT)      \
	E_FUNC(E_MACRO_COUNT)

// a macro which converts `value` to `value,`
#define E_MAKE_ENUM(ENUM) ENUM,
// a macro which converts `value` to `"value",`
#define E_MAKE_STRING(ENUM) #ENUM,

enum { E_ENUM(E_MAKE_ENUM) };
static const char *E_TO_STR[] = {E_ENUM(E_MAKE_STRING)};

//******** *** ********

extern int stmt_type;
extern char *tables[2];
extern char *equi_id[2];
extern char *equi_tables[2];
extern ast *ast_root;
extern clq *clq_head;

void run_sql();
void run_select();
void run_project();
void run_equijoin();
void run_cartprod();
ast *new_ast_node();
clq *new_clq_node();
#endif