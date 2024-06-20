#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include<limits.h>
#include<windows.h>
#include"lexer.h"
#include"bcc_log.h"
#define BCC_DEBUG_LEVEL BCC_DEBUG_LEVEL_ALL

typedef struct exp {
	char* value;
	struct exp* left, * right, *next;
}expnode;
typedef expnode* explist;

struct vartype {
	int Typedef;
	int Extern;
	int Static;
	int Auto;
	int Register;
	int Void;
	int Char;
	int Short;
	int Int;
	int Long;
	int Float;
	int Double;
	int Signed;
	int Unsigned;
	int Bool;
	int Complex;
	int Imaginary;
	int Const;
	int Restrict;
	int Volatile;
	int Inline;
	int Struct;
	int Enum;
	int Union;
}vartype = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };


explist bcc_parser_createxpnode(char* type, struct exp* left, struct exp* right) {
	expnode* node = (expnode*)malloc(sizeof(expnode));
	node->value = type;
	node->left = left;
	node->right = right;
	node->next = NULL;
	return node;
}
/*表达式*/
explist bcc_parser_primary_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_postfix_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_argument_expression_list(DoubleLinkList* list, explist explistnode);
explist bcc_parser_unary_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_cast_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_multiplicative_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_additive_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_shift_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_relational_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_equality_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_AND_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_exclusive_OR_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_inclusive_OR_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_logical_AND_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_logical_OR_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_conditional_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_assignment_expression(DoubleLinkList* list, explist explistnode);
explist bcc_parser_expression(DoubleLinkList* list, explist explistnode);

/*用于解决左递归的中间函数*/
explist bcc_parser_additive_expression_prime(DoubleLinkList* list, explist explistnode);
explist bcc_parser_expression_prime(DoubleLinkList* list, explist explistnode);
explist bcc_parser_logical_OR_expression_prime(DoubleLinkList* list, explist explistnode);
explist bcc_parser_logical_AND_expression_prime(DoubleLinkList* list, explist explistnode);
explist bcc_parser_inclusive_OR_expression_prime(DoubleLinkList* list, explist explistnode);
explist bcc_parser_exclusive_OR_expression_prime(DoubleLinkList* list, explist explistnode);
explist bcc_parser_AND_expression_prime(DoubleLinkList* list, explist explistnode);
explist bcc_parser_equality_expression_prime(DoubleLinkList* list, explist explistnode);
explist bcc_parser_relational_expression_prime(DoubleLinkList* list, explist explistnode);
explist bcc_parser_shift_expression_prime(DoubleLinkList* list, explist explistnode);
explist bcc_parser_multiplicative_expression_prime(DoubleLinkList* list, explist explistnode);
explist bcc_parser_argument_expression_list_prime(DoubleLinkList* list, explist explistnode);
explist bcc_parser_postfix_expression_prime(DoubleLinkList* list, explist explistnode);

/*表达式结束，以下为声明*/
void bcc_parser_declaration(DoubleLinkList* list,DoubleListNode *listnode,declist node);
void bcc_parser_declaration_specifiers(DoubleLinkList* list, DoubleListNode* listnode, declist node);
void bcc_parser_init_declarator_list(DoubleLinkList* list);
void bcc_parser_init_declarator(DoubleLinkList* list);
void bcc_parser_struct_or_union_specifier(DoubleLinkList* list);
void bcc_parser_struct_declaration_list(DoubleLinkList* list);
void bcc_parser_struct_declaration(DoubleLinkList* list);
void bcc_parser_specifier_qualifier_list(DoubleLinkList* list);
void bcc_parser_struct_declarator(DoubleLinkList* list);
void bcc_parser_enum_specifier(DoubleLinkList* list);
void bcc_parser_enumerator_list(DoubleLinkList* list);
void bcc_parser_enumerator(DoubleLinkList* list);
void bcc_parser_declarator(DoubleLinkList* list);
void bcc_parser_direct_declarator(DoubleLinkList* list);
void bcc_parser_type_qualifier_list(DoubleLinkList* list);
void bcc_parser_parameter_type_list(DoubleLinkList* list);
void bcc_parser_parameter_list(DoubleLinkList* list);
void bcc_parser_parameter_declaration(DoubleLinkList* list);
void bcc_parser_identifier_list(DoubleLinkList* list);
void bcc_parser_type_name(DoubleLinkList* list);
void bcc_parser_abstract_declarator(DoubleLinkList* list);
void bcc_parser_direct_abstract_declarator(DoubleLinkList* list);
void bcc_parser_initializer(DoubleLinkList* list);
void bcc_parser_initializer_list(DoubleLinkList* list);
void bcc_parser_designation(DoubleLinkList* list);
void bcc_parser_designator_list(DoubleLinkList* list);
void bcc_parser_designator(DoubleLinkList* list);
void bcc_parser_typename(DoubleLinkList* list, explist explistnode);
void bcc_parser_type_specifier(DoubleLinkList* list, explist explistnode);




explist bcc_parser_primary_expression(DoubleLinkList* list, explist explistnode) {
	if ((*list)->type == Id || (*list)->type == Integer || (*list)->type == FloatNum||(*list)->type==String) {
		//expnode* newnode = bcc_parser_createxpnode((*list)->value, NULL, NULL);
		explistnode->value = (char*)malloc(strlen((*list)->value) + 1);
		strcpy_s(explistnode->value, strlen((*list)->value)+1, (*list)->value);
		//explistnode->value = (*list)->value;
		return explistnode;
	} 
	/*else if ((*list)->type == Integer|| (*list)->type == FloatNum) {
		expnode* newnode=bcc_parser_createxpnode((*list)->value, NULL, NULL);
		if (explistnode->left == NULL) {
			explistnode->left = newnode;
		}
		else {
			explistnode->right = newnode;
		}
	}*/
	if ((*list)->type == OpenParen) {
		*list = (*list)->next;
		bcc_parser_expression(list, explistnode);
	}
	if ((*list)->next->type == CloseParen) {
		*list = (*list)->next;
		return explistnode;
	}
}

explist bcc_parser_postfix_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_primary_expression(list, explistnode);
	//if ((*list) != NULL && (*list)->type == LeftParenthesis) {
	//	(*list) = (*list)->next;
	//	// Parse type-name
	//	// Your parsing code here
	//	// After parsing, there should be a right parenthesis
	//	if ((*list) != NULL && (*list)->type == RightParenthesis) {
	//		(*list) = (*list)->next;
	//		if ((*list) != NULL && (*list)->type == LeftBrace) {
	//			(*list) = (*list)->next;
	//			// Parse initializer-list
	//			// Your parsing code here
	//			// After parsing, there should be a right brace
	//			if ((*list) != NULL && (*list)->type == RightBrace) {
	//				(*list) = (*list)->next;
	//				if ((*list) != NULL && (*list)->type == Comma) {
	//					(*list) = (*list)->next;
	//				}
	//			}
	//		}
	//	}
	//}
}

// Function to parse argument-expression-list'
explist bcc_parser_argument_expression_list_prime(DoubleLinkList* list, explist explistnode) {
	if (*list != NULL && (*list)->next->type == Comma) {
		*list = (*list)->next; // Move to the next token

		// Create a new node for the argument
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(strlen(tok_str[(*list)->type]) + 1);
		strcpy_s(explistnode->value, strlen(tok_str[(*list)->type]) + 1, tok_str[(*list)->type]);
		explistnode->left = newnode;
		expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);
		explistnode->right = emptynode;

		*list = (*list)->next;
		// Parse the next assignment-expression
		bcc_parser_assignment_expression(list, emptynode);

		// Continue parsing the rest of argument-expression-list'
		bcc_parser_argument_expression_list_prime(list, emptynode);
	}

	return explistnode;
}

// Function to parse argument-expression-list
explist bcc_parser_argument_expression_list(DoubleLinkList* list, explist explistnode) {
	bcc_parser_assignment_expression(list, explistnode); // Parse the first assignment-expression

	// Call the helper function to parse argument-expression-list'
	bcc_parser_argument_expression_list_prime(list, explistnode);

	return explistnode;
}

explist bcc_parser_unary_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_postfix_expression(list, explistnode); // postfix-expression
	if (*list != NULL && ((*list)->type == Increment || (*list)->type == Decrement)) { // ++ unary-expression or -- unary-expression
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(strlen(tok_str[(*list)->type]) + 1);
		strcpy_s(explistnode->value, strlen(tok_str[(*list)->type]) + 1, tok_str[(*list)->type]);
		explistnode->right = newnode;
		*list = (*list)->next;
		bcc_parser_unary_expression(list, newnode);
	}
	else if (*list != NULL && ((*list)->type == Address || (*list)->type == Derefer_Mul || (*list)->type == Add
		|| (*list)->type == Sub || (*list)->type == BitNOT || (*list)->type == LogicalNOT)) {
		
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(strlen(tok_str[(*list)->type]) + 1);
		strcpy_s(explistnode->value, strlen(tok_str[(*list)->type]) + 1, tok_str[(*list)->type]);
		explistnode->right = newnode;
		*list = (*list)->next;
		bcc_parser_cast_expression(list, newnode);
	}

	if (*list != NULL && (*list)->type == Sizeof) { // sizeof unary-expression or sizeof ( type-name )
		*list = (*list)->next;
		if (*list != NULL && (*list)->type == OpenParen) { // sizeof ( type-name )
			*list = (*list)->next;
			// Parse type-name
			// Your parsing code here
			// After parsing, there should be a right parenthesis
			if (*list != NULL && (*list)->type == CloseParen) {
				*list = (*list)->next;
			}
		}
		else { // sizeof unary-expression
			bcc_parser_unary_expression(list, explistnode);
		}
	}
}

explist bcc_parser_cast_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_unary_expression(list, explistnode); // unary-expression
	if (*list != NULL && (*list)->type == OpenParen) { // ( type-name ) cast-expression
		*list = (*list)->next;
		//if (bcc_parser_typename(list, explistnode)) {
			//(*list) = (*list)->next;
		if (bcc_parser_cast_expression(list, explistnode)) {
			*list = (*list)->next;
			if (*list != NULL && (*list)->type == CloseParen) {
				//操作
				return explistnode;
			}
		}
	}
	else {

	}
}

// Function to parse multiplicative-expression'
explist bcc_parser_multiplicative_expression_prime(DoubleLinkList* list, explist explistnode) {
	if (*list != NULL && ((*list)->next->type == Derefer_Mul || (*list)->next->type == Division ||
		(*list)->next->type == Mod)) {
		*list = (*list)->next; // Move to the next token

		// Create a new node for the multiplicative operation
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(strlen(tok_str[(*list)->type]) + 1);
		strcpy_s(explistnode->value, strlen(tok_str[(*list)->type]) + 1, tok_str[(*list)->type]);
		explistnode->left = newnode;
		expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);
		explistnode->right = emptynode;

		*list = (*list)->next;
		// Parse the right side of the multiplicative expression
		bcc_parser_cast_expression(list, emptynode);

		// Continue parsing the rest of multiplicative-expression'
		bcc_parser_multiplicative_expression_prime(list, emptynode);
	}

	return explistnode;
}

// Function to parse multiplicative-expression
explist bcc_parser_multiplicative_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_cast_expression(list, explistnode); // Parse the first operand

	// Call the helper function to parse multiplicative-expression'
	bcc_parser_multiplicative_expression_prime(list, explistnode);

	return explistnode;
}

explist bcc_parser_additive_expression_prime(DoubleLinkList* list, explist explistnode) {
	if (*list != NULL && ((*list)->next->type == Add || (*list)->next->type == Sub)) { // additive-expression + multiplicative-expression or additive-expression - multiplicative-expression
		//bcc_parser_multiplicative_expression(list, explistnode); // multiplicative-expression
		*list = (*list)->next;
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(strlen(tok_str[(*list)->type]) + 1);
		strcpy_s(explistnode->value, strlen(tok_str[(*list)->type]) + 1, tok_str[(*list)->type]);
		//explistnode->value = "+";//目前先直接赋值为“+”，主要用于测试整个流程的可行性
		explistnode->left = newnode;
		expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);
		explistnode->right = emptynode;
		*list = (*list)->next;
		bcc_parser_multiplicative_expression(list, emptynode);
		bcc_parser_additive_expression_prime(list, emptynode);
		//bcc_parser_multiplicative_expression(&((*list)->next), emptynode);
	}
}

explist bcc_parser_additive_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_multiplicative_expression(list, explistnode); // multiplicative-expression
	bcc_parser_additive_expression_prime(list, explistnode);
	//if (*list != NULL && ((*list)->next->type == Add || (*list)->next->type == Sub)) { // additive-expression + multiplicative-expression or additive-expression - multiplicative-expression
	//	*list = (*list)->next;
	//	expnode* newnode = bcc_parser_createxpnode(explistnode->value, NULL, NULL);
	//	explistnode->value = "+";//目前先直接赋值为“+”，主要用于测试整个流程的可行性
	//	explistnode->left = newnode;
	//	expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);
	//	explistnode->right = emptynode;
	//	bcc_parser_multiplicative_expression(&((*list)->next), emptynode);
	//}
}

// Function to parse shift-expression'
explist bcc_parser_shift_expression_prime(DoubleLinkList* list, explist explistnode) {
	if (*list != NULL && ((*list)->next->type == LShift || (*list)->next->type == RShift)) {
		*list = (*list)->next; // Move to the next token

		// Create a new node for the shift operation
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(strlen(tok_str[(*list)->type]) + 1);
		strcpy_s(explistnode->value, strlen(tok_str[(*list)->type]) + 1, tok_str[(*list)->type]);
		explistnode->left = newnode;
		expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);
		explistnode->right = emptynode;
		*list = (*list)->next;
		// Parse the right side of the shift expression
		bcc_parser_additive_expression(list, emptynode);

		// Continue parsing the rest of shift-expression'
		bcc_parser_shift_expression_prime(list, emptynode);
	}

	return explistnode;
}

// Function to parse shift-expression
explist bcc_parser_shift_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_additive_expression(list, explistnode); // Parse the first operand

	// Call the helper function to parse shift-expression'
	bcc_parser_shift_expression_prime(list, explistnode);

	return explistnode;
}

// Function to parse relational-expression'
explist bcc_parser_relational_expression_prime(DoubleLinkList* list, explist explistnode) {
	if (*list != NULL && ((*list)->next->type == Less || (*list)->next->type == Greater ||
		(*list)->next->type == LessOrEqual || (*list)->next->type == GreaterOrEqual)) {
		*list = (*list)->next; // Move to the next token

		// Create a new node for the relational operation
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(strlen(tok_str[(*list)->type]) + 1);
		strcpy_s(explistnode->value, strlen(tok_str[(*list)->type]) + 1, tok_str[(*list)->type]);
		explistnode->left = newnode;
		expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);
		explistnode->right = emptynode;

		*list = (*list)->next;
		// Parse the right side of the relational expression
		bcc_parser_shift_expression(list, emptynode);

		// Continue parsing the rest of relational-expression'
		bcc_parser_relational_expression_prime(list, emptynode);
	}

	return explistnode;
}

// Function to parse relational-expression
explist bcc_parser_relational_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_shift_expression(list, explistnode); // Parse the first operand

	// Call the helper function to parse relational-expression'
	bcc_parser_relational_expression_prime(list, explistnode);

	return explistnode;
}

// Function to parse equality-expression'
explist bcc_parser_equality_expression_prime(DoubleLinkList* list, explist explistnode) {
	if (*list != NULL && ((*list)->next->type == Equal || (*list)->next->type == NotEqual)) {
		*list = (*list)->next; // Move to the next token

		// Create a new node for the equality operation
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(strlen(tok_str[(*list)->type]) + 1);
		strcpy_s(explistnode->value, strlen(tok_str[(*list)->type]) + 1, tok_str[(*list)->type]);
		explistnode->left = newnode;
		expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);
		explistnode->right = emptynode;
		*list = (*list)->next;
		// Parse the right side of the equality expression
		bcc_parser_relational_expression(list, emptynode);

		// Continue parsing the rest of equality-expression'
		bcc_parser_equality_expression_prime(list, emptynode);
	}

	return explistnode;
}

// Function to parse equality-expression
explist bcc_parser_equality_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_relational_expression(list, explistnode); // Parse the first operand

	// Call the helper function to parse equality-expression'
	bcc_parser_equality_expression_prime(list, explistnode);

	return explistnode;
}

// Function to parse AND-expression'
explist bcc_parser_AND_expression_prime(DoubleLinkList* list, explist explistnode) {
	if (*list != NULL && (*list)->next->type == Address) {
		*list = (*list)->next; // Move to the next token

		// Create a new node for the AND operation
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(strlen(tok_str[(*list)->type]) + 1);
		strcpy_s(explistnode->value, strlen(tok_str[(*list)->type]) + 1, tok_str[(*list)->type]);
		explistnode->left = newnode;
		expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);
		explistnode->right = emptynode;
		*list = (*list)->next;
		// Parse the right side of the AND expression
		bcc_parser_equality_expression(list, emptynode);

		// Continue parsing the rest of AND-expression'
		bcc_parser_AND_expression_prime(list, emptynode);
	}

	return explistnode;
}

// Function to parse AND-expression
explist bcc_parser_AND_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_equality_expression(list, explistnode); // Parse the first operand

	// Call the helper function to parse AND-expression'
	bcc_parser_AND_expression_prime(list, explistnode);

	return explistnode;
}

// Function to parse exclusive-OR-expression'
explist bcc_parser_exclusive_OR_expression_prime(DoubleLinkList* list, explist explistnode) {
	if (*list != NULL && (*list)->next->type == BitXOR) {
		*list = (*list)->next; // Move to the next token

		// Create a new node for the exclusive OR operation
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(strlen(tok_str[(*list)->type]) + 1);
		strcpy_s(explistnode->value, strlen(tok_str[(*list)->type]) + 1, tok_str[(*list)->type]);
		explistnode->left = newnode;
		expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);
		explistnode->right = emptynode;

		*list = (*list)->next;
		// Parse the right side of the exclusive OR expression
		bcc_parser_AND_expression(list, emptynode);

		// Continue parsing the rest of exclusive-OR-expression'
		bcc_parser_exclusive_OR_expression_prime(list, emptynode);
	}

	return explistnode;
}

// Function to parse exclusive-OR-expression
explist bcc_parser_exclusive_OR_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_AND_expression(list, explistnode); // Parse the first operand

	// Call the helper function to parse exclusive-OR-expression'
	bcc_parser_exclusive_OR_expression_prime(list, explistnode);

	return explistnode;
}

// Function to parse inclusive-OR-expression'
explist bcc_parser_inclusive_OR_expression_prime(DoubleLinkList* list, explist explistnode) {
	if (*list != NULL && (*list)->next->type == BitOR) {
		*list = (*list)->next; // Move to the next token

		// Create a new node for the inclusive OR operation
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(strlen(tok_str[(*list)->type]) + 1);
		strcpy_s(explistnode->value, strlen(tok_str[(*list)->type]) + 1, tok_str[(*list)->type]);
		explistnode->left = newnode;
		expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);
		explistnode->right = emptynode;

		*list = (*list)->next;
		// Parse the right side of the inclusive OR expression
		bcc_parser_exclusive_OR_expression(list, emptynode);

		// Continue parsing the rest of inclusive-OR-expression'
		bcc_parser_inclusive_OR_expression_prime(list, emptynode);
	}

	return explistnode;
}

// Function to parse inclusive-OR-expression
explist bcc_parser_inclusive_OR_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_exclusive_OR_expression(list, explistnode); // Parse the first operand

	// Call the helper function to parse inclusive-OR-expression'
	bcc_parser_inclusive_OR_expression_prime(list, explistnode);

	return explistnode;
}

// Function to parse logical-AND-expression'
explist bcc_parser_logical_AND_expression_prime(DoubleLinkList* list, explist explistnode) {
	if (*list != NULL && (*list)->next->type == LogicalAND) {
		*list = (*list)->next; // Move to the next token

		// Create a new node for the logical AND operation
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(strlen(tok_str[(*list)->type]) + 1);
		strcpy_s(explistnode->value, strlen(tok_str[(*list)->type]) + 1, tok_str[(*list)->type]);
		explistnode->left = newnode;
		expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);
		explistnode->right = emptynode;

		*list = (*list)->next;
		// Parse the right side of the logical AND expression
		bcc_parser_inclusive_OR_expression(list, emptynode);

		// Continue parsing the rest of logical-AND-expression'
		bcc_parser_logical_AND_expression_prime(list, emptynode);
	}

	return explistnode;
}

// Function to parse logical-AND-expression
explist bcc_parser_logical_AND_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_inclusive_OR_expression(list, explistnode); // Parse the first operand

	// Call the helper function to parse logical-AND-expression'
	bcc_parser_logical_AND_expression_prime(list, explistnode);

	return explistnode;
}

// Function to parse logical-OR-expression'
explist bcc_parser_logical_OR_expression_prime(DoubleLinkList* list, explist explistnode) {
	if (*list != NULL && (*list)->next->type == LogicalOR) {
		*list = (*list)->next; // Move to the next token

		// Create a new node for the logical OR operation
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(strlen(tok_str[(*list)->type]) + 1);
		strcpy_s(explistnode->value, strlen(tok_str[(*list)->type]) + 1, tok_str[(*list)->type]);
		explistnode->left = newnode;
		expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);
		explistnode->right = emptynode;

		*list = (*list)->next;
		// Parse the right side of the logical OR expression
		bcc_parser_logical_AND_expression(list, emptynode);

		// Continue parsing the rest of logical-OR-expression'
		bcc_parser_logical_OR_expression_prime(list, emptynode);
	}

	return explistnode;
}

// Function to parse logical-OR-expression
explist bcc_parser_logical_OR_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_logical_AND_expression(list, explistnode); // Parse the first operand

	// Call the helper function to parse logical-OR-expression'
	bcc_parser_logical_OR_expression_prime(list, explistnode);

	return explistnode;
}

explist bcc_parser_conditional_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_logical_OR_expression(list, explistnode);//logical-OR-expression
	if (*list != NULL && (*list)->next->type == Condition) {
		*list = (*list)->next;
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);//复制一个node
		explistnode->value = (char*)malloc(sizeof(tok_str[(*list)->type]) + 1);//旧节点重新赋值
		strcpy_s(explistnode->value, sizeof(tok_str[(*list)->type]), tok_str[(*list)->type]);
		explistnode->left = newnode;
		expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);//创建一个新的空节点
		explistnode->right = emptynode;
		*list = (*list)->next;
		bcc_parser_expression(list, emptynode);
		explistnode = explistnode->right;
		if (*list != NULL && (*list)->next->type == Colon) {
			*list = (*list)->next;
			newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);//复制一个node
			explistnode->value = (char*)malloc(sizeof(tok_str[(*list)->type]) + 1);//旧节点重新赋值
			strcpy_s(explistnode->value, sizeof(tok_str[(*list)->type]), tok_str[(*list)->type]);
			explistnode->left = newnode;
			emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);//创建一个新的空节点
			explistnode->right = emptynode;
			*list = (*list)->next;
			bcc_parser_conditional_expression(list, emptynode);
		}
	}
	else {
		return explistnode;
	}
}

explist bcc_parser_assignment_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_conditional_expression(list, explistnode);//conditional-expression
	if (*list != NULL && ((*list)->next->type == Assignment || (*list)->next->type == MulAss || 
		(*list)->next->type == DivAss ||(*list)->next->type == ModAss || (*list)->next->type == AddAss ||
		(*list)->next->type == SubAss || (*list)->next->type == LShAss ||(*list)->next->type == RShAss ||
		(*list)->next->type == BitANDAss || (*list)->next->type == BitXORAss ||
		(*list)->next->type == BitORAss)) {//上一步操作必然会执行到unary-expression，所以这一步直接去执行assignment-operator
		*list = (*list)->next;
		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);
		explistnode->value = (char*)malloc(sizeof(char) * 10);
		strcpy_s(explistnode->value, sizeof(tok_str[(*list)->type]), tok_str[(*list)->type]);
		//explistnode->value = tok_str[(*list)->type];//目前先直接赋值为“=”，主要用于测试整个流程的可行性
		explistnode->left = newnode;
		expnode* emptynode= bcc_parser_createxpnode(NULL, NULL, NULL);
		explistnode->right = emptynode;
		*list = (*list)->next;
		bcc_parser_assignment_expression(list, emptynode);
		//bcc_parser_assignment_expression(list, explistnode);
	}
	else {
		return explistnode;
	}
}

explist bcc_parser_expression_prime(DoubleLinkList* list, explist explistnode) {
	if (*list != NULL && ((*list)->next->type == Comma)) {
		*list = (*list)->next;

		expnode* newnode = bcc_parser_createxpnode(explistnode->value, explistnode->left, explistnode->right);//复制一个node
		explistnode->value = (char*)malloc(sizeof(tok_str[(*list)->type]) + 1);//旧节点重新赋值
		strcpy_s(explistnode->value, sizeof(tok_str[(*list)->type]), tok_str[(*list)->type]);
		explistnode->left = newnode;
		expnode* emptynode = bcc_parser_createxpnode(NULL, NULL, NULL);//创建一个新的空节点
		explistnode->right = emptynode;
		*list = (*list)->next;

		bcc_parser_assignment_expression(list, emptynode);
		//bcc_parser_additive_expression_prime(list, emptynode);
	}
	return explistnode;
}

explist bcc_parser_expression(DoubleLinkList* list, explist explistnode) {
	bcc_parser_assignment_expression(list, explistnode);
	bcc_parser_expression_prime(list, explistnode);//消除左递归的中间函数

	return explistnode;
}

void bcc_parser_typename(DoubleLinkList* list, explist explistnode) {
	//bcc_parser_specifier_qualifier_list(list, explistnode);
	//abstra_declarator;
}

void bcc_parser_declaration(DoubleLinkList* list, DoubleListNode* listnode, declist node) {
	bcc_parser_declaration_specifiers(list, list, node);

}
void bcc_parser_declaration_specifiers(DoubleLinkList* list, DoubleListNode* listnode, declist node){
	if (listnode->type == Typedef) {
		node->type=
	}
}
void bcc_parser_init_declarator_list(DoubleLinkList* list){
}
void bcc_parser_init_declarator(DoubleLinkList* list){
}
void bcc_parser_struct_or_union_specifier(DoubleLinkList* list){
}
void bcc_parser_struct_declaration_list(DoubleLinkList* list){
}
void bcc_parser_struct_declaration(DoubleLinkList* list){
}
void bcc_parser_specifier_qualifier_list(DoubleLinkList* list){
}
void bcc_parser_struct_declarator(DoubleLinkList* list){
}
void bcc_parser_enum_specifier(DoubleLinkList* list){
}
void bcc_parser_enumerator_list(DoubleLinkList* list){
}
void bcc_parser_enumerator(DoubleLinkList* list){
}
void bcc_parser_declarator(DoubleLinkList* list){
}
void bcc_parser_direct_declarator(DoubleLinkList* list){
}
void bcc_parser_type_qualifier_list(DoubleLinkList* list){
}
void bcc_parser_parameter_type_list(DoubleLinkList* list){
}
void bcc_parser_parameter_list(DoubleLinkList* list){
}
void bcc_parser_parameter_declaration(DoubleLinkList* list){
}
void bcc_parser_identifier_list(DoubleLinkList* list){
}
void bcc_parser_type_name(DoubleLinkList* list){
}
void bcc_parser_abstract_declarator(DoubleLinkList* list){
}
void bcc_parser_direct_abstract_declarator(DoubleLinkList* list){
}
void bcc_parser_initializer(DoubleLinkList* list){
}
void bcc_parser_initializer_list(DoubleLinkList* list){
}
void bcc_parser_designation(DoubleLinkList* list){
}
void bcc_parser_designator_list(DoubleLinkList* list){
}
void bcc_parser_designator(DoubleLinkList* list){
}
void bcc_parser_type_specifier(DoubleLinkList* list, explist explistnode){
}
void inorderTraversal(expnode* root,int i,char site) {
	i++;
	if (root == NULL) {
		return;
	}
	char c = 'l';
	// 递归遍历左子树
	inorderTraversal(root->left,i,c);

	// 访问根节点
	bcc_log_info("parser", "第%d层，位置是%c,值是%s\n", i,site,root->value);
	c = 'r';
	// 递归遍历右子树
	inorderTraversal(root->right,i,c);
}

int main() {
	char sour[20000];
	memset(sour, 0, 20000);//初始化数组，方便存储源代码
	FILE* fp;
	errno_t err = fopen_s(&fp, "parser_exp_text.txt", "r");
	//fp = fopen("text_01.txt", "r");//打开文件
	if (err != 0 || fp == NULL) {
		printf("文件打开失败\n");
		fclose(fp);
		return 0;
	}
	else {
		printf("文件打开成功\n");
	}
	fseek(fp, 0, SEEK_END);
	int file_len = ftell(fp);
	printf("文件字符数为 %d\n", file_len);
	fseek(fp, 0, SEEK_SET);               //重新将指针指向文件首部
	fread(sour, sizeof(char), file_len, fp);//开始读取整个文件
	printf("%s\n", sour);//用于调试
	fclose(fp);//关闭文件
	free(fp);
	int len = strlen(sour);
	DoubleLinkList list = NodeInit();
	DoubleLinkList DLL_head = list;
	int i = 0;
	long int count_line = 1;
	while (i < len) {
		if (isletter(sour[i]) || sour[i] == '_'){//本次接收字母，可能是关键字或标识符
			opstr(sour, &i, len, &list,count_line);
		}
		else if (isdigits(sour[i])){//本次接收为数字
			opnum(sour, &i, len, &list, count_line);
		}
		else if (isqmark(sour[i])) {//本次接收了引号
			opqmark(sour, &i, len, &list,&count_line);
		}
		else if (sour[i] == '/'){//处理注释
			opcomment(sour, &i, len, &list, &count_line);
		}
		else if (sour[i] == ' '){//本次空格
			i++;
		}
		else if (sour[i] == '\n'){//回车，行数增加
			count_line++;
			i++;
		}
		else{//处理符号
			op_operator(sour, &i, file_len, &list,count_line);
		}
	}
	/*截至于此，词法分析部分结束，开始进行语法分析*/
	list = DLL_head->next;
	decl* decinode = (decl*)malloc(sizeof(decl));

	//expnode* explist= bcc_parser_createxpnode(NULL, NULL, NULL);
	//expnode* exphead = bcc_parser_createxpnode(NULL, NULL, NULL);
	//exphead = explist;
	//while (list->next != NULL) {
	//	bcc_parser_expression(&list, explist);
	//	i = 0;
	//	inorderTraversal(explist,i,'m');
	//	expnode* newnode = bcc_parser_createxpnode(NULL, NULL, NULL);
	//	printf("下一个节点\n");
	//	explist->next = newnode;
	//	explist = explist->next;
	//	list = list->next;
	//	if (list->type == Semicolon) {
	//		list = list->next;
	//	}
	//}
	//int long long a = 0;
	/*expnode* newnode=bcc_parser_createxpnode(NULL, NULL, NULL);
	bcc_parser_expression(&list, newnode);*/
	return 0;
}