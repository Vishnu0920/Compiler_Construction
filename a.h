#ifndef AST_H
#define AST_H

typedef enum {
    NODE_PROGRAM,
    NODE_VARLIST,
    NODE_VARDECL,
    NODE_BLOCK,
    NODE_STMT_LIST,
    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_PRINT,
    NODE_SCAN,
    NODE_ASSIGN,
    NODE_ADD_ASSIGN,
    NODE_SUB_ASSIGN,
    NODE_MUL_ASSIGN,
    NODE_DIV_ASSIGN,
    NODE_MOD_ASSIGN,
    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV,
    NODE_MOD,
    NODE_NEG,
    NODE_EQ,
    NODE_NEQ,
    NODE_GT,
    NODE_LT,
    NODE_GEQ,
    NODE_LEQ,
    NODE_NUMBER,
    NODE_VAR_REF,
    NODE_STRING,
    NODE_CHAR,
    NODE_FORMAT_STRING
} NodeType;
const char *nodeTypeToString(NodeType type);

typedef struct ASTNode {
    NodeType type;
    
    union {
        struct{int int_val; int base;}number;
        char* str_val;
        
        struct {
            struct ASTNode* left;
            struct ASTNode* right;
        } op;
        
        struct {
            char* name;
            int var_type;
        } var_decl;
        
        struct {
            char* name;
        } var_ref;
        
        struct {
            struct ASTNode* condition;
            struct ASTNode* true_branch;
            struct ASTNode* false_branch;
        } if_stmt;
        
        struct {
            struct ASTNode* condition;
            struct ASTNode* body;
        } while_stmt;
        
        struct {
            struct ASTNode* var;
            struct ASTNode* init;
            struct ASTNode* limit;
            int op_type;
            struct ASTNode* step;
            struct ASTNode* body;
        } for_stmt;
        
        struct {
            char* var_name;
            struct ASTNode* value;
        } assign;
        
        struct {
            struct ASTNode* vars;
            struct ASTNode* stmts;
        } program;
    } data;
} ASTNode;

// AST Node Creation Functions
ASTNode* createProgramNode(ASTNode* var_decls, ASTNode* statements);
ASTNode* createDeclListNode(ASTNode* decl, ASTNode* next);
ASTNode* createVarDeclNode(char* name, int type);
ASTNode* createBlockNode(ASTNode* statements);
ASTNode* createStatementListNode(ASTNode* stmt, ASTNode* next);
ASTNode* createIfNode(ASTNode* condition, ASTNode* true_branch, ASTNode* false_branch);
ASTNode* createWhileNode(ASTNode* condition, ASTNode* body);
ASTNode* createForNode(ASTNode* var, ASTNode* init, ASTNode* limit, int op_type, ASTNode* step, ASTNode* body);
ASTNode* createAssignNode(char* var_name, ASTNode* value);
ASTNode* createOperatorAssignNode(NodeType op_type, char* var_name, ASTNode* value);
ASTNode* createOperatorNode(NodeType op_type, ASTNode* left, ASTNode* right);
ASTNode* createNumberNode(int value,int base);
ASTNode* createVarRefNode(char* name);
ASTNode* createStringNode(char* value);
ASTNode* createCharNode(char* value);
ASTNode* createPrintNode(ASTNode* arg);
ASTNode* createScanNode(char* format, ASTNode* args);
ASTNode* createFormatStringNode(char* format, ASTNode* args);
ASTNode* createOutputArgListNode(ASTNode* arg, ASTNode* next);
ASTNode* createInputArgListNode(ASTNode* arg, ASTNode* next);

// AST Utility Functions
void printAST(ASTNode* node, int indent);
void freeAST(ASTNode* node);

#endif // AST_H