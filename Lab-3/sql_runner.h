#ifndef _SQL_RUNNER_
#define _SQL_RUNNER_
#define MAX_COLS 10
#define MAX_CONDS 5
#define MAX_STRLEN 25
typedef struct conditions {
	int operation;
	int operand_type[2];
	char col_name[2][MAX_STRLEN];
	int num[2];
} conditions;
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
	E_INT
};
extern int stmt_type;
extern char tables[2][MAX_STRLEN];
extern char cols[MAX_COLS][MAX_STRLEN];
extern int col_num;
extern conditions cond_list[MAX_CONDS];
extern int cond_num;
extern char equi_id[2][MAX_STRLEN];
void init_ds();
void run_sql();
void run_select();
void run_project();
void run_equijoin();
void run_cartprod();
#endif