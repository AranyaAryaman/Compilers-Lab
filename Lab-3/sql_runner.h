#ifndef _SQL_RUNNER_
#define _SQL_RUNNER_

#include "sql_runner.h"

#define MAX_COLS 10
#define MAX_STRLEN 25
typedef struct condition_ast {
	int operation;		  // or and not >= <= > < = <> != (both relational and logical)

	// use this for intermediate nodes
	// (those with relational (and or not) operators)
	struct condition_ast *child[2];		   // more conditions

	// and this for leaf nodes
	// (those with logical (>= <= > < = <> !=) operators)
	int operand_type[2];			// int str var
	char str[2][MAX_STRLEN];		// salary name
	int num[2];						// 10 20
} condition_ast;

enum {
	E_DUMMY = 0,

	E_SELECT,
	E_CARTPROD,
	E_EQUIJOIN,
	E_PROJECT,

	E_LT,
	E_LTEQ,
	E_GT,
	E_GTEQ,
	E_EQ,
	E_NEQ,

	E_STR,
	E_INT,
	E_VAR,

	E_AND,
	E_OR,
	E_NOT
};
extern int stmt_type;
extern int col_num;
extern char tables[2][MAX_STRLEN];
extern char cols[MAX_COLS][MAX_STRLEN];
extern char equi_id[2][MAX_STRLEN];
extern char equi_tables[2][MAX_STRLEN];
extern condition_ast *ast;
condition_ast *new_node();
// void free_ast(condition_ast *root);
void init_ds();
void run_sql();
void run_select();
void run_project();
void run_equijoin();
void run_cartprod();
condition_ast *new_node();
#endif