#include "a.h"
#include "a.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_PRINT;
    node->data.print.arg = arg;
    return node;
}

// Function to create a scan node
ASTNode* createScanNode(char* format, ASTNode* args) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_SCAN;
    node->data.scan.format = strdup(format);
    node->data.scan.args = args;
    return node;
}

// Create a format string node
ASTNode* createFormatStringNode(char* format, ASTNode* args) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_FORMAT_STRING;
    node->data.formatString.format = strdup(format);
    node->data.formatString.args = args;
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
 for (int i = 0; i < indent; i++) {
 printf(" ");
 }
}

// Modified printAST function to produce proper nesting
void printAST(ASTNode *node, int indent) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM:
            printIndent(indent);
            printf("(\n");

            // Print variable declarations (each on its own line)
            ASTNode *var = node->data.program.vars;
            while (var) {
                if (var->type == NODE_VARLIST) {
                    printAST(var->data.op.left, indent + 2);
                    var = var->data.op.right;
                } else {
                    printAST(var, indent + 2);
                    var = NULL;
                }
            }

            // Print statements as a grouped subtree
            printIndent(indent + 2);
            printf("(\n");
            if (node->data.program.stmts) {
                printAST(node->data.program.stmts, indent + 4);
            }
            printIndent(indent + 2);
            printf(")\n");

            printIndent(indent);
            printf(")\n");
            break;

        case NODE_VARLIST:
            printAST(node->data.op.left, indent);
            if (node->data.op.right) {
                printAST(node->data.op.right, indent);
            }
            break;

        case NODE_VARDECL:
            printIndent(indent);
            // Only print if type is INT or CHAR (token values from parser)
            if (node->data.var_decl.var_type == INT)
                printf("(%s int)\n", node->data.var_decl.name);
            else if (node->data.var_decl.var_type == CHAR)
                printf("(%s char)\n", node->data.var_decl.name);
            // Do not print anything if not int or char
            break;

        case NODE_STMT_LIST:
            printAST(node->data.op.left, indent);
            if (node->data.op.right) {
                printAST(node->data.op.right, indent);
            }
            break;

        case NODE_BLOCK:
            printIndent(indent);
            printf("(\n");
            printAST(node->data.op.left, indent + 2);
            printIndent(indent);
            printf(")\n");
            break;

        case NODE_ASSIGN:
            printIndent(indent);
            printf("(:= %s ", node->data.assign.var_name);
            printAST(node->data.assign.value, 0);
            printf(")\n");
            break;

        case NODE_IF:
            printIndent(indent);
            printf("(if\n");

            // Print condition at one level deeper
            printIndent(indent + 2);
            printAST(node->data.if_stmt.condition, 0);
            printf("\n");

            // True branch
            printIndent(indent + 2);
            printf("(\n");
            printAST(node->data.if_stmt.true_branch, indent + 4);
            printIndent(indent + 2);
            printf(")\n");

            // False branch if exists
            if (node->data.if_stmt.false_branch) {
                printIndent(indent + 2);
                printf("(\n");
                printAST(node->data.if_stmt.false_branch, indent + 4);
                printIndent(indent + 2);
                printf(")\n");
            }

            printIndent(indent);
            printf(")\n");
            break;

        case NODE_WHILE:
            printIndent(indent);
            printf("(while\n");
            printIndent(indent + 2);
            printAST(node->data.while_stmt.condition, 0);
            printf("\n");
            
            printIndent(indent + 2);
            printf("(\n");
            printAST(node->data.while_stmt.body, indent + 4);
            printIndent(indent + 2);
            printf(")\n");
            
            printIndent(indent);
            printf(")\n");
            break;

            case NODE_FOR:
            printIndent(indent);
            printf("(for\n");
            
            // Print initialization
            printIndent(indent + 2);
            printf("(:= %s ", node->data.for_stmt.var->data.var_ref.name);
            printAST(node->data.for_stmt.init, 0);
            printf(")\n");
            
            // Print limit
            printIndent(indent + 2);
            printAST(node->data.for_stmt.limit, 0);
            printf("\n");
            
            // Print step 
            printIndent(indent + 2);
            printf("(dec ");
            printAST(node->data.for_stmt.step, 0);
            printf(")\n");
            
            // Print body
            printIndent(indent + 2);
            printf("(\n");
            printAST(node->data.for_stmt.body, indent + 4);
            printIndent(indent + 2);
            printf(")\n");
            
            printIndent(indent);
            printf(")\n");
            break;

        case NODE_ADD:
            printf("(+ ");
            printAST(node->data.op.left, 0);
            printf(" ");
            printAST(node->data.op.right, 0);
            printf(")");
            break;

        case NODE_SUB:
            printf("(- ");
            printAST(node->data.op.left, 0);
            printf(" ");
            printAST(node->data.op.right, 0);
            printf(")");
            break;
        
            case NODE_MUL:
            printf("(* ");
            printAST(node->data.op.left, 0);
            printf(" ");
            printAST(node->data.op.right, 0);
            printf(")");
            break;
        
        case NODE_DIV:
            printf("(/ ");
            printAST(node->data.op.left, 0);
            printf(" ");
            printAST(node->data.op.right, 0);
            printf(")");
            break;
        
        case NODE_MOD:
            printf("(%% ");  // Need to escape % with another %
            printAST(node->data.op.left, 0);
            printf(" ");
            printAST(node->data.op.right, 0);
            printf(")");
            break;
        
        case NODE_NEG:
            printf("(- ");  // Unary minus
            printAST(node->data.op.left, 0);  // or node->data.operand if that's how it's structured
            printf(")");
            break;
        
        case NODE_EQ:
            printf("(= ");
            printAST(node->data.op.left, 0);
            printf(" ");
            printAST(node->data.op.right, 0);
            printf(")");
            break;
        
        case NODE_NEQ:
            printf("(<> ");
            printAST(node->data.op.left, 0);
            printf(" ");
            printAST(node->data.op.right, 0);
            printf(")");
            break;
        
        case NODE_GT:
            printf("(> ");
            printAST(node->data.op.left, 0);
            printf(" ");
            printAST(node->data.op.right, 0);
            printf(")");
            break;
        
        case NODE_LT:
            printf("(< ");
            printAST(node->data.op.left, 0);
            printf(" ");
            printAST(node->data.op.right, 0);
            printf(")");
            break;
        
        case NODE_GEQ:
            printf("(>= ");
            printAST(node->data.op.left, 0);
            printf(" ");
            printAST(node->data.op.right, 0);
            printf(")");
            break;
        
        case NODE_LEQ:
            printf("(<= ");
            printAST(node->data.op.left, 0);
            printf(" ");
            printAST(node->data.op.right, 0);
            printf(")");
            break;

        case NODE_NUMBER:
            printf("(%d %d)", node->data.number.int_val, node->data.number.base);
            break;

        case NODE_VAR_REF:
            printf("%s", node->data.var_ref.name);
            break;

            case NODE_PRINT:
            printIndent(indent);
            printf("(print ");
            printAST(node->data.print.arg, 0);
            printf(")\n");
            break;
            
        case NODE_FORMAT_STRING:
            printf("\"%s\" ", node->data.formatString.format);
            printAST(node->data.formatString.args, 0);
            break;

        case NODE_SCAN:
            printIndent(indent);
            printf("(scan \"%s\"", node->data.scan.format ? node->data.scan.format : "");
            if (node->data.scan.args) {
                printf(" ");
                printAST(node->data.scan.args, 0);
            }
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
 case NODE_STRING: case NODE_CHAR:
 free(node->data.str_val);
 break;
 case NODE_PRINT:
            freeAST(node->data.print.arg);
            break;      
case NODE_FORMAT_STRING:
free(node->data.formatString.format);
freeAST(node->data.formatString.args);
break;
            
case NODE_SCAN:
free(node->data.scan.format);
freeAST(node->data.scan.args);
break;
 default:
 break;
 }
 free(node);
}