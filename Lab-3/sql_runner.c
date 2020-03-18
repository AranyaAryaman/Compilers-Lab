#include "sql_runner.h"

#include "csv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stmt_type;
int col_num;
char tables[2][MAX_STRLEN];
char cols[MAX_COLS][MAX_STRLEN];
char equi_id[2][MAX_STRLEN];
char equi_tables[2][MAX_STRLEN];
condition_ast *ast;
int int_compare(int val3, int val4, int operation);
int str_compare(char *val1, char *val2, int operation);
int get_header_index(char **headerFields, int nh, char *str);
int match_on(char **headerFields, char **rowFields, int nh, int nr, condition_ast *root);
void free_ast(condition_ast *root);

condition_ast *new_node() {
	condition_ast *ret = (condition_ast *)malloc(sizeof(condition_ast));
	memset(ret, 0, sizeof(condition_ast));		  // zero bomb all fields in ret
	return ret;
}

int get_header_index(char **headerFields, int nh, char *str) {
	for(int i = 0; i < nh; i++)
		if(!strcmp(headerFields[i], str))
			return i;
	return -1;
}

void init_ds(void) {
	col_num = 0;
}

void run_sql(void) {
	switch(stmt_type) {
		case E_SELECT: run_select(); break;
		case E_PROJECT: run_project(); break;
		case E_CARTPROD: run_cartprod(); break;
		case E_EQUIJOIN: run_equijoin(); break;
		default: break;
	}
}

void run_project(void) {
	int query_count = 0;
	char tablename[MAX_STRLEN];
	strncpy(tablename, tables[0], MAX_STRLEN);
	strncat(tablename, ".csv", MAX_STRLEN - strlen(tablename) - 1);
	CsvParser *csvparser = CsvParser_new(tablename);
	CsvRow *row;
	CsvRow *header = CsvParser_getHeader(csvparser);

	if(header == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(csvparser));
		return;
	}
	char **headerFields = CsvParser_getFields(header);
	int *headers = (int *)malloc(sizeof(int) * CsvParser_getNumFields(header));
	int c = 0;
	int found = 0;
	for(int j = 0; j < col_num; j++) {
		found = 0;
		for(int i = 0; i < CsvParser_getNumFields(header); i++)
			if(strcmp(cols[j], headerFields[i]) == 0) {
				headers[c++] = i;
				found = 1;
			}
		if(!found) {
			printf("\033[01;31mERROR:\033[00mColumn %s not found for projection\n", cols[j]);
			free(headers);
			CsvParser_destroy(csvparser);
			return;
		}
	}
	for(int i = 0; i < c; i++)
		printf("%s\t\t", headerFields[headers[i]]);
	printf("\n");

	while((row = CsvParser_getRow(csvparser))) {
		char **rowFields = CsvParser_getFields(row);
		for(int i = 0; i < c; i++) {
			query_count++;
			printf("%s\t\t", rowFields[headers[i]]);
		}
		printf("\n");
		CsvParser_destroy_row(row);
	}
	CsvParser_destroy(csvparser);
	free(headers);
	printf("%d rows displayed\n", query_count);
}

void run_cartprod(void) {
	int query_count = 0;
	char tablename1[MAX_STRLEN], tablename2[MAX_STRLEN];
	strncpy(tablename1, tables[0], MAX_STRLEN);
	strncpy(tablename2, tables[1], MAX_STRLEN);
	strncat(tablename1, ".csv", MAX_STRLEN - strlen(tablename1) - 1);
	strncat(tablename2, ".csv", MAX_STRLEN - strlen(tablename2) - 1);
	CsvParser *csvparser1 = CsvParser_new(tablename1);
	CsvRow *row1;
	CsvRow *header1 = CsvParser_getHeader(csvparser1);
	CsvParser *temp_csvparser2 = CsvParser_new(tablename2);
	CsvRow *temp_header2 = CsvParser_getHeader(temp_csvparser2);
	if(header1 == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(csvparser1));
		return;
	}
	if(temp_header2 == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(temp_csvparser2));
		return;
	}
	char **headerFields1 = CsvParser_getFields(header1);
	char **headerFields2 = CsvParser_getFields(temp_header2);
	for(int i = 0; i < CsvParser_getNumFields(header1); i++)
		printf("%s.%s\t\t", tables[0], headerFields1[i]);
	for(int i = 0; i < CsvParser_getNumFields(temp_header2); i++)
		printf("%s.%s\t\t", tables[1], headerFields2[i]);
	printf("\n");
	CsvParser_destroy(temp_csvparser2);

	while((row1 = CsvParser_getRow(csvparser1))) {
		char **rowFields1 = CsvParser_getFields(row1);
		// printf("%s\t\t", rowFields[i]);
		CsvParser *csvparser2 = CsvParser_new(tablename2);
		CsvRow *row2;
		CsvRow *header2 = CsvParser_getHeader(csvparser2);

		if(header2 == NULL) {
			printf("%s\n", CsvParser_getErrorMessage(csvparser2));
			CsvParser_destroy_row(row1);
			CsvParser_destroy(csvparser1);
			return;
		}
		while((row2 = CsvParser_getRow(csvparser2))) {
			char **rowFields2 = CsvParser_getFields(row2);
			query_count++;
			for(int j = 0; j < CsvParser_getNumFields(row1); j++)
				printf("%s\t\t", rowFields1[j]);
			for(int j = 0; j < CsvParser_getNumFields(row2); j++)
				printf("%s\t\t", rowFields2[j]);
			printf("\n");
			CsvParser_destroy_row(row2);
		}
		CsvParser_destroy(csvparser2);
		CsvParser_destroy_row(row1);
	}
	CsvParser_destroy(csvparser1);
	printf("%d rows displayed\n", query_count);
}

void run_equijoin(void) {
	int query_count = 0;
	char tablename1[MAX_STRLEN], tablename2[MAX_STRLEN];
	int ok = 0;
	if(strcmp(tables[0], equi_tables[0]) == 0 && strcmp(tables[1], equi_tables[1]) == 0)
		ok = 1;
	if(strcmp(tables[1], equi_tables[0]) == 0 && strcmp(tables[0], equi_tables[1]) == 0) {
		char temp[25];

		strncpy(temp, equi_tables[0], MAX_STRLEN);
		strncpy(equi_tables[0], equi_tables[1], MAX_STRLEN);
		strncpy(equi_tables[1], temp, MAX_STRLEN);

		strncpy(temp, equi_id[0], MAX_STRLEN);
		strncpy(equi_id[0], equi_id[1], MAX_STRLEN);
		strncpy(equi_id[1], temp, MAX_STRLEN);

		ok = 1;
	}
	if(!ok) {
		printf("EquiJoin condition error\n");
		return;
	}
	strncpy(tablename1, tables[0], MAX_STRLEN);
	strncpy(tablename2, tables[1], MAX_STRLEN);
	strncat(tablename1, ".csv", MAX_STRLEN - strlen(tablename1) - 1);
	strncat(tablename2, ".csv", MAX_STRLEN - strlen(tablename2) - 1);
	CsvParser *csvparser1 = CsvParser_new(tablename1);
	CsvRow *row1;
	CsvRow *header1 = CsvParser_getHeader(csvparser1);
	CsvParser *temp_csvparser2 = CsvParser_new(tablename2);
	CsvRow *temp_header2 = CsvParser_getHeader(temp_csvparser2);
	if(header1 == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(csvparser1));
		return;
	}
	if(temp_header2 == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(temp_csvparser2));
		return;
	}
	char **headerFields1 = CsvParser_getFields(header1);
	char **headerFields2 = CsvParser_getFields(temp_header2);
	int h1 = -1;
	int h2 = -1;
	for(int i = 0; i < CsvParser_getNumFields(header1); i++)
		if(!strcmp(headerFields1[i], equi_id[0]))
			h1 = i;

	for(int i = 0; i < CsvParser_getNumFields(temp_header2); i++)
		if(!strcmp(headerFields2[i], equi_id[1]))
			h2 = i;
	if(h1 == -1 || h2 == -1) {
		printf("EQUIJOIN columns wrong in condition\n");
		return;
	}
	for(int i = 0; i < CsvParser_getNumFields(header1); i++)
		printf("%s.%s\t\t", tables[0], headerFields1[i]);
	for(int i = 0; i < CsvParser_getNumFields(temp_header2); i++)
		printf("%s.%s\t\t", tables[1], headerFields2[i]);
	printf("\n");
	CsvParser_destroy(temp_csvparser2);

	while((row1 = CsvParser_getRow(csvparser1))) {
		char **rowFields1 = CsvParser_getFields(row1);
		CsvParser *csvparser2 = CsvParser_new(tablename2);
		CsvRow *row2;
		CsvRow *header2 = CsvParser_getHeader(csvparser2);

		if(header2 == NULL) {
			printf("%s\n", CsvParser_getErrorMessage(csvparser2));
			CsvParser_destroy_row(row1);
			CsvParser_destroy(csvparser1);
			return;
		}
		while((row2 = CsvParser_getRow(csvparser2))) {
			char **rowFields2 = CsvParser_getFields(row2);
			if(!strcmp(rowFields1[h1], rowFields2[h2])) {
				query_count++;
				for(int j = 0; j < CsvParser_getNumFields(row1); j++)
					printf("%s\t\t", rowFields1[j]);
				for(int j = 0; j < CsvParser_getNumFields(row2); j++)
					printf("%s\t\t", rowFields2[j]);
				printf("\n");
			}
			CsvParser_destroy_row(row2);
		}
		CsvParser_destroy(csvparser2);
		CsvParser_destroy_row(row1);
	}
	CsvParser_destroy(csvparser1);
	printf("%d rows displayed\n", query_count);
}

int match_on(char **headerFields, char **rowFields, int nh, int nr, condition_ast *root) {
	if(root->operation == E_AND)
		return (match_on(headerFields, rowFields, nh, nr, root->child[0]) &&
				match_on(headerFields, rowFields, nh, nr, root->child[1])) ?
				   1 :
				   0;
	if(root->operation == E_OR)
		return (match_on(headerFields, rowFields, nh, nr, root->child[0]) ||
				match_on(headerFields, rowFields, nh, nr, root->child[1])) ?
				   1 :
				   0;
	if(root->operation == E_NOT)
		return match_on(headerFields, rowFields, nh, nr, root->child[0]) ? 0 : 1;

	if(root->operand_type[0] == E_STR && root->operand_type[1] == E_INT) {
		printf("[WARN]String to int comparision, returning false\n");
		return 0;
	}
	if(root->operand_type[0] == E_INT && root->operand_type[1] == E_STR) {
		printf("[WARN]String to int comparision, returning false\n");
		return 0;
	}
	if(root->operation != E_LT && root->operation != E_LTEQ && root->operation != E_GT && root->operation != E_GTEQ &&
	   root->operation != E_EQ && root->operation != E_NEQ)
		printf("Unknown operator %s\n", E_TO_STR[root->operation]);
	char *val1, *val2;
	int val3, val4;
	int is_int_comparision = 0;
	if(root->operand_type[0] == E_INT || root->operand_type[1] == E_INT)
		is_int_comparision = 1;
	// WARNING: var to  var comparisions are str by default
	if(root->operand_type[0] == E_STR) {
		val1 = root->str[0];
	} else if(root->operand_type[0] == E_INT) {
		val3 = root->num[0];
	} else {
		int index = get_header_index(headerFields, nh, root->str[0]);
		if(index == -1) {
			printf("[WARN]No column by name %s, returning false\n", root->str[0]);
			return 0;
		}
		if(is_int_comparision)
			val3 = atoi(rowFields[index]);
		else
			val1 = rowFields[index];
	}

	if(root->operand_type[1] == E_STR) {
		val2 = root->str[1];
	} else if(root->operand_type[1] == E_INT) {
		val4 = root->num[1];
	} else {
		int index = get_header_index(headerFields, nh, root->str[1]);
		if(index == -1) {
			printf("[WARN]No column by name %s, returning false\n", root->str[1]);
			return 0;
		}
		if(is_int_comparision)
			val4 = atoi(rowFields[index]);
		else
			val2 = rowFields[index];
	}
	if(is_int_comparision)
		return int_compare(val3, val4, root->operation);
	return str_compare(val1, val2, root->operation);
}

void run_select(void) {
	int query_count = 0;
	char tablename[MAX_STRLEN];
	strncpy(tablename, tables[0], MAX_STRLEN);
	strncat(tablename, ".csv", MAX_STRLEN - strlen(tablename) - 1);
	CsvParser *csvparser = CsvParser_new(tablename);
	CsvRow *row;
	CsvRow *header = CsvParser_getHeader(csvparser);

	if(header == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(csvparser));
		return;
	}
	char **headerFields = CsvParser_getFields(header);
	for(int i = 0; i < CsvParser_getNumFields(header); i++)
		printf("%s\t\t", headerFields[i]);
	printf("\n");

	while((row = CsvParser_getRow(csvparser))) {
		char **rowFields = CsvParser_getFields(row);
		int res = -1;
		res = match_on(headerFields, rowFields, CsvParser_getNumFields(header), CsvParser_getNumFields(row), ast);
		if(res == 1) {
			query_count++;
			for(int i = 0; i < CsvParser_getNumFields(row); i++) {
				printf("%s\t\t", rowFields[i]);
			}
			printf("\n");
		}
		CsvParser_destroy_row(row);
	}
	CsvParser_destroy(csvparser);
	free_ast(ast);
	printf("%d rows displayed\n", query_count);
}

void free_ast(condition_ast *root) {
	if(root->operation == E_OR || root->operation == E_AND || root->operation == E_NOT) {
		if(root->operation != E_NOT)
			free_ast(root->child[1]);
		free_ast(root->child[0]);
	}
	free(root);
}
// for(int cond_index = 0; cond_index < cond_num; cond_index++) {
// 	int t = -1;
// 	char *val1;
// 	char *val2;
// 	int val3;
// 	int val4;
// 	if(root->operand_type[0] == E_STR && root->operand_type[0] == E_INT) {
// 		printf("String to int comparision\n");
// 		return;
// 	}
// 	if(root->operand_type[0] == E_INT && root->operand_type[0] == E_STR) {
// 		printf("String to int comparision\n");
// 		return;
// 	}
// 	int is_int_comparision = 0;
// 	if(root->operand_type[0] == E_INT || root->operand_type[1] == E_INT)
// 		is_int_comparision = 1;
// 	// WARNING: var to  var comparisions are str by default

// 	if(root->operand_type[0] == E_STR) {
// 		val1 = root->str[0];
// 	} else if(root->operand_type[0] == E_INT) {
// 		val3 = root->num[0];
// 	} else {
// 		int index = get_header_index(headerFields, nh, root->str[0]);
// 		if(index == -1) {
// 			printf("No column by name %s\n", root->str[0]);
// 			return;
// 		}
// 		if(is_int_comparision)
// 			val3 = atoi(rowFields[index]);
// 		else
// 			val1 = rowFields[index];
// 	}

// 	if(root->operand_type[1] == E_STR) {
// 		val2 = root->str[1];
// 	} else if(root->operand_type[1] == E_INT) {
// 		val4 = root->num[1];
// 	} else {
// 		int index = get_header_index(headerFields, nh, root->str[1]);
// 		if(index == -1) {
// 			printf("No column by name %s\n", root->str[1]);
// 			return;
// 		}
// 		if(is_int_comparision)
// 			val4 = atoi(rowFields[index]);
// 		else
// 			val2 = rowFields[index];
// 	}
int int_compare(int val3, int val4, int operation) {
	if(operation == E_LT)
		return (val3 < val4) ? 1 : 0;
	else if(operation == E_LTEQ)
		return (val3 <= val4) ? 1 : 0;
	else if(operation == E_GT)
		return (val3 > val4) ? 1 : 0;
	else if(operation == E_GTEQ)
		return (val3 >= val4) ? 1 : 0;
	else if(operation == E_EQ)
		return (val3 == val4) ? 1 : 0;
	else if(operation == E_NEQ)
		return (val3 != val4) ? 1 : 0;
}
int str_compare(char *val1, char *val2, int operation) {
	if(operation == E_LT)
		return (strncmp(val1, val2, MAX_STRLEN) < 0) ? 1 : 0;
	else if(operation == E_LTEQ)
		return (strncmp(val1, val2, MAX_STRLEN) <= 0) ? 1 : 0;
	else if(operation == E_GT)
		return (strncmp(val1, val2, MAX_STRLEN) > 0) ? 1 : 0;
	else if(operation == E_GTEQ)
		return (strncmp(val1, val2, MAX_STRLEN) >= 0) ? 1 : 0;
	else if(operation == E_EQ)
		return (strncmp(val1, val2, MAX_STRLEN) == 0) ? 1 : 0;
	else if(operation == E_NEQ)
		return (strncmp(val1, val2, MAX_STRLEN) != 0) ? 1 : 0;
}

// 	if(root->cond_join == E_OR)
// 		res = res || t;
// 	else if(root->cond_join == E_AND)
// 		res = res && t;
// 	else {
// 		res = t;
// 	}
// }
