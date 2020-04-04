#include "sql_runner.h"

#include "csv.h"
#include "gc.h"
#include "helpers.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stmt_type;

char *tables[2];
char *equi_id[2];
char *equi_tables[2];

ast *ast_root;
clq *clq_head;

ast *new_ast_node() {
	ast *ret = (ast *)gc_malloc(sizeof(ast));
	memset(ret, 0, sizeof(ast));		// zero bomb all fields in ret
	return ret;
}

clq *new_clq_node() {
	clq *ret = (clq *)gc_malloc(sizeof(clq));
	memset(ret, 0, sizeof(clq));
	return ret;
}

void run_sql(void) {
	switch(stmt_type) {
		case E_SELECT: run_select(); break;
		case E_PROJECT: run_project(); break;
		case E_CARTPROD: run_cartprod(); break;
		case E_EQUIJOIN: run_equijoin(); break;
		default: break;
	}
	gc_collect();
}

void run_project(void) {
	int query_count = 0;
	char *tablename = str_concat(tables[0], ".csv");
	CsvParser *csvparser = CsvParser_new(tablename);
	CsvRow *row;
	CsvRow *header = CsvParser_getHeader(csvparser);

	if(header == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(csvparser));
		return;
	}
	char **headerFields = CsvParser_getFields(header);
	int nh = CsvParser_getNumFields(header);
	int *headers_arr = (int *)gc_malloc(sizeof(int) * nh);
	memset(headers_arr, 0, sizeof(int) * nh);
	int c = 0;
	int c2 = -1;
	clq_head = rev_clq(clq_head);
	clq *temp = clq_head;
	while(temp != NULL) {
		c2++;
		int index = get_header_index(headerFields, nh, temp->str);
		if(index == -1) {
			printf("Column %s not found for projection\n", temp->str);
			CsvParser_destroy(csvparser);
			return;
		}
		if(headers_arr[index] < nh) {
			headers_arr[c] += index;
			headers_arr[index] += nh;
			c++;
		} else {
			printf("[WARN]Duplicate fields in project, skipping %s(#%d)\n", temp->str, c2);
		}
		temp = temp->next;
	}
	printf("%s", headerFields[headers_arr[0] % nh]);
	for(int i = 1; i < c; i++)
		printf(", %s", headerFields[headers_arr[i] % nh]);
	printf("\n");

	while((row = CsvParser_getRow(csvparser))) {
		char **rowFields = CsvParser_getFields(row);
		query_count++;
		printf("%s", rowFields[headers_arr[0] % nh]);
		for(int i = 1; i < c; i++) {
			printf(", %s", rowFields[headers_arr[i] % nh]);
		}
		printf("\n");
		CsvParser_destroy_row(row);
	}
	CsvParser_destroy(csvparser);
	printf("\n%d rows displayed\n", query_count);
}

void run_cartprod(void) {
	int query_count = 0;
	char *tablename1 = str_concat(tables[0], ".csv");
	char *tablename2 = str_concat(tables[1], ".csv");
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
		printf("%s.%s,", tables[0], headerFields1[i]);
	for(int i = 0; i < CsvParser_getNumFields(temp_header2); i++)
		printf("%s.%s,", tables[1], headerFields2[i]);
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
			query_count++;
			printf("%s", rowFields1[0]);
			for(int j = 1; j < CsvParser_getNumFields(row1); j++)
				printf(", %s", rowFields1[j]);
			for(int j = 0; j < CsvParser_getNumFields(row2); j++)
				printf(", %s", rowFields2[j]);
			printf("\n");
			CsvParser_destroy_row(row2);
		}
		CsvParser_destroy(csvparser2);
		CsvParser_destroy_row(row1);
	}
	CsvParser_destroy(csvparser1);
	printf("\n%d rows displayed\n", query_count);
}

void run_equijoin(void) {
	int query_count = 0;
	char *tablename1, *tablename2;
	int ok = 0;
	if(strcmp(tables[0], equi_tables[0]) == 0 && strcmp(tables[1], equi_tables[1]) == 0)
		ok = 1;
	if(strcmp(tables[1], equi_tables[0]) == 0 && strcmp(tables[0], equi_tables[1]) == 0) {
		char *temp;

		temp = equi_tables[0];
		equi_tables[0] = equi_tables[1];
		equi_tables[1] = temp;

		temp = equi_id[0];
		equi_id[0] = equi_id[1];
		equi_id[1] = temp;

		ok = 1;
	}
	if(!ok) {
		printf("EquiJoin condition error\n");
		return;
	}
	tablename1 = str_concat(tables[0], ".csv");
	tablename2 = str_concat(tables[1], ".csv");
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
		printf("%s.%s,", tables[0], headerFields1[i]);
	for(int i = 0; i < CsvParser_getNumFields(temp_header2); i++)
		printf("%s.%s,", tables[1], headerFields2[i]);
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
				printf("%s", rowFields1[0]);
				for(int j = 1; j < CsvParser_getNumFields(row1); j++)
					printf(", %s", rowFields1[j]);
				for(int j = 0; j < CsvParser_getNumFields(row2); j++)
					printf(", %s", rowFields2[j]);
				printf("\n");
			}
			CsvParser_destroy_row(row2);
		}
		CsvParser_destroy(csvparser2);
		CsvParser_destroy_row(row1);
	}
	CsvParser_destroy(csvparser1);
	printf("\n%d rows displayed\n", query_count);
}

void run_select(void) {
	int query_count = 0;
	char *tablename = str_concat(tables[0], ".csv");
	CsvParser *csvparser = CsvParser_new(tablename);
	CsvRow *row;
	CsvRow *header = CsvParser_getHeader(csvparser);

	if(header == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(csvparser));
		return;
	}
	char **headerFields = CsvParser_getFields(header);
	if(!ast_ok(headerFields, CsvParser_getNumFields(header), ast_root))
		return;
	printf("%s", headerFields[0]);
	for(int i = 1; i < CsvParser_getNumFields(header); i++)
		printf(", %s", headerFields[i]);
	printf("\n");

	while((row = CsvParser_getRow(csvparser))) {
		char **rowFields = CsvParser_getFields(row);
		int res = -1;
		res = match_on(headerFields, rowFields, CsvParser_getNumFields(header), CsvParser_getNumFields(row), ast_root);
		if(res == 1) {
			query_count++;
			printf("%s", rowFields[0]);
			for(int i = 1; i < CsvParser_getNumFields(row); i++) {
				printf(", %s", rowFields[i]);
			}
			printf("\n");
		}
		CsvParser_destroy_row(row);
	}
	CsvParser_destroy(csvparser);
	printf("\n%d rows displayed\n", query_count);
}