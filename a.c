#include "a.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT 1 // Type identifier for integer variables
#define CHAR 2 // Type identifier for character variables
#define INC 1 // Loop operator for increment
#define DEC 2 // Loop operator for decrement

const char *nodeTypeToString(NodeType type) {
 switch (type) {
 case NODE_ADD: return "+";
 case NODE_SUB: return "-";
 case NODE_MUL: return "*";
 case NODE_DIV: return "/";
 case NODE_MOD: return "%";
 case NODE_NEG: return "neg";
 case NODE_EQ: return "=";
 case NODE_NEQ: return "<>";
 case NODE_GT: return ">";
 case NODE_LT: return "<";
 case NODE_GEQ: return ">=";
 case NODE_LEQ: return "<=";
 default: return "<?>";
 }
}

static ASTNode* createNode(NodeType type) {
 ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
 if (!node) {
 fprintf(stderr, "Memory allocation error\n");
 exit(1);
 }
 node->type = type;
 return node;
}

// Create a program node
ASTNode* createProgramNode(ASTNode* var_decls, ASTNode* statements) {
 ASTNode* node = createNode(NODE_PROGRAM);
 node->data.program.vars = var_decls;
 node->data.program.stmts = statements;
 return node;
}

// Create a declaration list node
ASTNode* createDeclListNode(ASTNode* decl, ASTNode* next) {
 ASTNode* node = createNode(NODE_VARLIST);
 node->data.op.left = decl;
 node->data.op.right = next;
 return node;
}

// Create a variable declaration node
ASTNode* createVarDeclNode(char* name, int type) {
 ASTNode* node = createNode(NODE_VARDECL);
 node->data.var_decl.name = strdup(name);
 node->data.var_decl.var_type = type;
 return node;
}

// Create a block node
ASTNode* createBlockNode(ASTNode* statements) {
 ASTNode* node = createNode(NODE_BLOCK);
 node->data.op.left = statements;
 node->data.op.right = NULL;
 return node;
}

// Create a statement list node
ASTNode* createStatementListNode(ASTNode* stmt, ASTNode* next) {
 ASTNode* node = createNode(NODE_STMT_LIST);
 node->data.op.left = stmt;
 node->data.op.right = next;
 return node;
}

// Create an if node
ASTNode* createIfNode(ASTNode* condition, ASTNode* true_branch, ASTNode* false_branch) {
 ASTNode* node = createNode(NODE_IF);
 node->data.if_stmt.condition = condition;
 node->data.if_stmt.true_branch = true_branch;
 node->data.if_stmt.false_branch = false_branch;
 return node;
}

// Create a while node
ASTNode* createWhileNode(ASTNode* condition, ASTNode* body) {
 ASTNode* node = createNode(NODE_WHILE);
 node->data.while_stmt.condition = condition;
 node->data.while_stmt.body = body;
 return node;
}

// Create a for node
ASTNode* createForNode(ASTNode* var, ASTNode* init, ASTNode* limit, int op_type, ASTNode* step, ASTNode* body) {
 ASTNode* node = createNode(NODE_FOR);
 node->data.for_stmt.var = var;
 node->data.for_stmt.init = init;
 node->data.for_stmt.limit = limit;
 node->data.for_stmt.op_type = op_type;
 node->data.for_stmt.step = step;
 node->data.for_stmt.body = body;
 return node;
}

// Create an assignment node
ASTNode* createAssignNode(char* var_name, ASTNode* value) {
 ASTNode* node = createNode(NODE_ASSIGN);
 node->data.assign.var_name = strdup(var_name);
 node->data.assign.value = value;
 return node;
}

// Create an operator assignment node
ASTNode* createOperatorAssignNode(NodeType op_type, char* var_name, ASTNode* value) {
 ASTNode* node = createNode(op_type);
 node->data.assign.var_name = strdup(var_name);
 node->data.assign.value = value;
 return node;
}

// Create an operator node
ASTNode* createOperatorNode(NodeType op_type, ASTNode* left, ASTNode* right) {
 ASTNode* node = createNode(op_type);
 node->data.op.left = left;
 node->data.op.right = right;
 return node;
}

// Create a number node
ASTNode* createNumberNode(int value,int base) {
 ASTNode* node = createNode(NODE_NUMBER);
 node->data.number.int_val = value;
 node->data.number.base = base;
 return node;
}

// Create a variable reference node
ASTNode* createVarRefNode(char* name) {
 ASTNode* node = createNode(NODE_VAR_REF);
 node->data.var_ref.name = strdup(name);
 return node;
}

// Create a string node
ASTNode* createStringNode(char* value) {
 ASTNode* node = createNode(NODE_STRING);
 node->data.str_val = strdup(value);
 return node;
}

// Create a character node
ASTNode* createCharNode(char* value) {
 ASTNode* node = createNode(NODE_CHAR);
 node->data.str_val = strdup(value);
 return node;
}

// Create a print node
ASTNode* createPrintNode(ASTNode* arg) {
 ASTNode* node = createNode(NODE_PRINT);
 node->data.op.left = arg;
 node->data.op.right = NULL;
 return node;
}

// Create a scan node
ASTNode* createScanNode(char* format, ASTNode* args) {
 ASTNode* node = createNode(NODE_SCAN);
 node->data.str_val = strdup(format);
 node->data.op.left = args;
 return node;
}

// Create a format string node
ASTNode* createFormatStringNode(char* format, ASTNode* args) {
 ASTNode* node = createNode(NODE_FORMAT_STRING);
 node->data.str_val = strdup(format);
 node->data.op.left = args;
 return node;
}

// Create an output argument list node
ASTNode* createOutputArgListNode(ASTNode* arg, ASTNode* next) {
 ASTNode* node = createNode(NODE_STMT_LIST); // Reuse statement list type
 node->data.op.left = arg;
 node->data.op.right = next;
 return node;
}

// Create an input argument list node
ASTNode* createInputArgListNode(ASTNode* arg, ASTNode* next) {
 ASTNode* node = createNode(NODE_STMT_LIST); // Reuse statement list type
 node->data.op.left = arg;
 node->data.op.right = next;
 return node;
}

// Helper function to print indentation
static void printIndent(int indent) {
    for (int i = 0; i < indent * 2; i++) { // Use 2 spaces per level
        printf(" ");
    }
}

// Modified printAST function to produce proper nesting
void printAST(ASTNode *node, int indent) {
 if (!node) return;

 switch (node->type) {
 case NODE_PROGRAM:
    printf("(\n");
    
    // Print variable declarations
    if (node->data.program.vars) {
        printAST(node->data.program.vars, indent + 1);
    }
    
    // Print statements
    if (node->data.program.stmts) {
        printIndent(indent + 1);
        printf("(\n");
        printAST(node->data.program.stmts, indent + 2);
        printIndent(indent + 1);
        printf(")\n");
    }
    
    printf(")\n");
    break;

 case NODE_VARLIST:
    // Print current declaration
    if (node->data.op.left) {
        printAST(node->data.op.left, indent);
    }
    
    // Print remaining declarations with proper nesting
    if (node->data.op.right) {
        printIndent(indent);
        printf("(\n");
        printAST(node->data.op.right, indent + 1);
        printIndent(indent);
        printf(")\n");
    }
    break;

 case NODE_VARDECL:
 printIndent(indent);
 printf("(%s int)\n", node->data.var_decl.name);
 break;
 

 case NODE_STMT_LIST:
    // Print the current statement
    if (node->data.op.left) {
        printAST(node->data.op.left, indent);
    }
    
    // Print next statement if it exists
    if (node->data.op.right) {
        printIndent(indent);
        printf("(\n");
        printAST(node->data.op.right, indent + 1);
        printIndent(indent);
        printf(")\n");
    }
    break;

 case NODE_BLOCK:
 printIndent(indent);
 printf("(\n");
 if (node->data.op.left) {
 printAST(node->data.op.left, indent + 1);
 }
 printIndent(indent);
 printf(")\n");
 break;

 case NODE_ASSIGN:
 printIndent(indent);
 printf("(:= %s (", node->data.assign.var_name);
 
 // Handle the right-hand side of the assignment
 if (node->data.assign.value->type == NODE_NUMBER) {
 printf("%d %d", 
 node->data.assign.value->data.number.int_val,
 node->data.assign.value->data.number.base);
 } else if (node->data.assign.value->type == NODE_ADD) {
 printf("+ ");
 if (node->data.assign.value->data.op.left->type == NODE_VAR_REF) {
 printf("%s ", node->data.assign.value->data.op.left->data.var_ref.name);
 } else {
 printAST(node->data.assign.value->data.op.left, 0);
 printf(" ");
 }
 
 if (node->data.assign.value->data.op.right->type == NODE_NUMBER) {
 printf("(%d %d)", 
 node->data.assign.value->data.op.right->data.number.int_val,
 node->data.assign.value->data.op.right->data.number.base);
 } else if (node->data.assign.value->data.op.right->type == NODE_VAR_REF) {
 printf("%s", node->data.assign.value->data.op.right->data.var_ref.name);
 } else {
 printAST(node->data.assign.value->data.op.right, 0);
 }
 } else if (node->data.assign.value->type == NODE_SUB) {
 printf("- ");
 if (node->data.assign.value->data.op.left->type == NODE_VAR_REF) {
 printf("%s ", node->data.assign.value->data.op.left->data.var_ref.name);
 } else {
 printAST(node->data.assign.value->data.op.left, 0);
 printf(" ");
 }
 
 if (node->data.assign.value->data.op.right->type == NODE_NUMBER) {
 printf("(%d %d)", 
 node->data.assign.value->data.op.right->data.number.int_val,
 node->data.assign.value->data.op.right->data.number.base);
 } else if (node->data.assign.value->data.op.right->type == NODE_VAR_REF) {
 printf("%s", node->data.assign.value->data.op.right->data.var_ref.name);
 } else {
 printAST(node->data.assign.value->data.op.right, 0);
 }
 }
 
 printf("))\n");
 break;

 case NODE_IF:
 printIndent(indent);
 printf("(if\n");
 printIndent(indent+1);
 if (node->data.if_stmt.condition->type >= NODE_EQ && 
 node->data.if_stmt.condition->type <= NODE_LEQ) {
 printf("(%s %s", 
 nodeTypeToString(node->data.if_stmt.condition->type),
 node->data.if_stmt.condition->data.op.left->data.var_ref.name);
 printf("(%d %d))\n", 
 node->data.if_stmt.condition->data.op.right->data.number.int_val,
 node->data.if_stmt.condition->data.op.right->data.number.base);
 } else {
 printAST(node->data.if_stmt.condition, indent + 1);
 }
 
 // Print true branch (always a block)
 printIndent(indent + 1);
 printf("(\n");
 if (node->data.if_stmt.true_branch) {
 printAST(node->data.if_stmt.true_branch, indent + 2);
 }
 printIndent(indent + 1);
 printf(")\n");
 
 // Print false branch if exists
 if (node->data.if_stmt.false_branch) {
 printIndent(indent + 1);
 printf("(\n");
 printAST(node->data.if_stmt.false_branch, indent + 2);
 printIndent(indent + 1);
 printf(")\n");
 }
 
 printIndent(indent);
 printf(")\n");
 break;

 case NODE_WHILE:
 printIndent(indent);
 printf("(while\n");
 
 // Print condition
 printIndent(indent + 1);
 printAST(node->data.while_stmt.condition, indent + 1);
 
 // Print body (always a block)
 printIndent(indent + 1);
 printf("(\n");
 if (node->data.while_stmt.body) {
 printAST(node->data.while_stmt.body, indent + 2);
 }
 printIndent(indent + 1);
 printf(")\n");
 
 printIndent(indent);
 printf(")\n");
 break;

 case NODE_FOR:
 printIndent(indent);
 printf("(for\n");
 
 // Print initialization
 printIndent(indent + 1);
 printf("(:= %s (", node->data.for_stmt.var->data.var_ref.name);
 if (node->data.for_stmt.init->type == NODE_ADD) {
 printf("+ ");
 if (node->data.for_stmt.init->data.op.left->type == NODE_VAR_REF) {
 printf("%s ", node->data.for_stmt.init->data.op.left->data.var_ref.name);
 } else {
 printAST(node->data.for_stmt.init->data.op.left, 0);
 printf(" ");
 }
 
 if (node->data.for_stmt.init->data.op.right->type == NODE_NUMBER) {
 printf("(%d %d)", 
 node->data.for_stmt.init->data.op.right->data.number.int_val,
 node->data.for_stmt.init->data.op.right->data.number.base);
 } else {
 printAST(node->data.for_stmt.init->data.op.right, 0);
 }
 } else {
 printAST(node->data.for_stmt.init, 0);
 }
 printf("))\n");
 
 // Print limit
 printIndent(indent + 1);
 if (node->data.for_stmt.limit->type == NODE_NUMBER) {
 printf("(%d %d)\n", 
 node->data.for_stmt.limit->data.number.int_val,
 node->data.for_stmt.limit->data.number.base);
 } else {
 printAST(node->data.for_stmt.limit, indent + 1);
 printf("\n");
 }
 
 // Print step operator and value
 printIndent(indent + 1);
 printf("(%s ", node->data.for_stmt.op_type == INC ? "inc" : "dec");
 if (node->data.for_stmt.step->type == NODE_SUB) {
 printf("(- ");
 if (node->data.for_stmt.step->data.op.left->type == NODE_VAR_REF) {
 printf("%s ", node->data.for_stmt.step->data.op.left->data.var_ref.name);
 } else {
 printAST(node->data.for_stmt.step->data.op.left, 0);
 printf(" ");
 }
 
 if (node->data.for_stmt.step->data.op.right->type == NODE_NUMBER) {
 printf("(%d %d)", 
 node->data.for_stmt.step->data.op.right->data.number.int_val,
 node->data.for_stmt.step->data.op.right->data.number.base);
 } else {
 printAST(node->data.for_stmt.step->data.op.right, 0);
 }
 printf(")");
 } else {
 printAST(node->data.for_stmt.step, 0);
 }
 printf(")\n");
 
 // Print body (always a block)
 printIndent(indent + 1);
 printf("(\n");
 if (node->data.for_stmt.body) {
 printAST(node->data.for_stmt.body, indent + 2);
 }
 printIndent(indent + 1);
 printf(")\n");
 
 printIndent(indent);
 printf(")\n");
 break;

 // Binary operators
 case NODE_ADD: case NODE_SUB: case NODE_MUL: case NODE_DIV: case NODE_MOD:
 printf("(%s ", nodeTypeToString(node->type));
 
 // Left operand
 if (node->data.op.left->type == NODE_VAR_REF) {
 printf("%s ", node->data.op.left->data.var_ref.name);
 } else {
 printAST(node->data.op.left, 0);
 printf(" ");
 }
 
 // Right operand
 if (node->data.op.right->type == NODE_VAR_REF) {
 printf("%s", node->data.op.right->data.var_ref.name);
 } else if (node->data.op.right->type == NODE_NUMBER) {
 printf("(%d %d)", 
 node->data.op.right->data.number.int_val,
 node->data.op.right->data.number.base);
 } else {
 printAST(node->data.op.right, 0);
 }
 
 printf(")");
 break;
 
 // Comparison operators
 case NODE_EQ: case NODE_NEQ: case NODE_GT: case NODE_LT: case NODE_GEQ: case NODE_LEQ:
 printf("(%s ", nodeTypeToString(node->type));
 
 // Left operand (usually a variable)
 if (node->data.op.left->type == NODE_VAR_REF) {
 printf("%s\n", node->data.op.left->data.var_ref.name);
 } else {
 printAST(node->data.op.left, indent + 1);
 printf("\n");
 }
 
 // Right operand (usually a constant)
 printIndent(indent + 1);
 if (node->data.op.right->type == NODE_NUMBER) {
 printf("(%d %d)\n", 
 node->data.op.right->data.number.int_val,
 node->data.op.right->data.number.base);
 } else {
 printAST(node->data.op.right, indent + 1);
 printf("\n");
 }
 
 printIndent(indent);
 printf(")");
 break;

 case NODE_NUMBER:
 printf("(%d %d)", 
 node->data.number.int_val,
 node->data.number.base);
 break;

 case NODE_VAR_REF:
 printf("%s", node->data.var_ref.name);
 break;

 case NODE_STRING:
 printf("\"%s\"", node->data.str_val);
 break;

 case NODE_CHAR:
 printf("\'%s\'", node->data.str_val);
 break;

 case NODE_PRINT:
 printIndent(indent);
 printf("(print \"a = @\" %s)\n",
 node->data.op.left->data.op.left->data.var_ref.name);
 break;

 case NODE_SCAN:
 printIndent(indent);
 printf("(scan \"%s\" ", node->data.str_val);
 printAST(node->data.op.left, 0);
 printf(")\n");
 break;

 default:
 break;
 }
}
// freeAST remains unchanged
void freeAST(ASTNode *node) {
 if (!node) return;
 switch (node->type) {
 case NODE_PROGRAM:
 freeAST(node->data.program.vars);
 freeAST(node->data.program.stmts);
 break;
 case NODE_VARLIST: case NODE_STMT_LIST: case NODE_BLOCK:
 freeAST(node->data.op.left);
 freeAST(node->data.op.right);
 break;
 case NODE_VARDECL:
 free(node->data.var_decl.name);
 break;
 case NODE_IF:
 freeAST(node->data.if_stmt.condition);
 freeAST(node->data.if_stmt.true_branch);
 freeAST(node->data.if_stmt.false_branch);
 break;
 case NODE_WHILE:
 freeAST(node->data.while_stmt.condition);
 freeAST(node->data.while_stmt.body);
 break;
 case NODE_FOR:
 freeAST(node->data.for_stmt.init);
 freeAST(node->data.for_stmt.limit);
 freeAST(node->data.for_stmt.step);
 freeAST(node->data.for_stmt.body);
 break;
 case NODE_ASSIGN: case NODE_ADD_ASSIGN: case NODE_SUB_ASSIGN:
 case NODE_MUL_ASSIGN: case NODE_DIV_ASSIGN: case NODE_MOD_ASSIGN:
 free(node->data.assign.var_name);
 freeAST(node->data.assign.value);
 break;
 case NODE_ADD: case NODE_SUB: case NODE_MUL: case NODE_DIV:
 case NODE_MOD: case NODE_NEG: case NODE_EQ: case NODE_NEQ:
 case NODE_GT: case NODE_LT: case NODE_GEQ: case NODE_LEQ:
 freeAST(node->data.op.left);
 freeAST(node->data.op.right);
 break;
 case NODE_VAR_REF:
 free(node->data.var_ref.name);
 break;
 case NODE_STRING: case NODE_CHAR: case NODE_FORMAT_STRING:
 free(node->data.str_val);
 break;
 case NODE_PRINT:
 freeAST(node->data.op.left);
 break;
 case NODE_SCAN:
 free(node->data.str_val);
 freeAST(node->data.op.left);
 break;
 default:
 break;
 }
 free(node);
}


