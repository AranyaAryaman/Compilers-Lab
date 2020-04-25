#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	Value val1, val2;
	val1.ival = 0;
	val2.ival = 1;
	AST_Node *const_node1 = new_ast_const_node(INT_TYPE, val1);
	AST_Node *const_node2 = new_ast_const_node(INT_TYPE, val2);
	AST_Node *bool_node = new_ast_bool_node(OR, const_node1, const_node2);
	AST_Node *simple_node = new_ast_simple_node(0);
	AST_Node *if_node = new_ast_if_node(bool_node, simple_node, NULL, 0, NULL);
	ast_traversal(if_node);
	return;
}