#include "a.h"
#include "a.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------- Symbol Table and Interpreter --------------

Symbol symtab[MAX_SYMBOLS];
int symtab_count = 0;

void insertSymbol(char* name, int type) {
    if (lookupSymbol(name)) {
        printf("Semantic Error: Variable '%s' redeclared.\n", name);
        exit(1);
    }
    symtab[symtab_count].name = strdup(name);
    symtab[symtab_count].type = type;
    symtab[symtab_count].initialized = 0;
    symtab[symtab_count].base = (type == INT) ? 10 : 0; // default base for int
    symtab_count++;
}

Symbol* lookupSymbol(char* name) {
    for (int i = 0; i < symtab_count; i++) {
        if (strcmp(symtab[i].name, name) == 0) return &symtab[i];
    }
    return NULL;
}

void updateSymbolValue(char* name, int value, int base) {
    Symbol* sym = lookupSymbol(name);
    if (!sym) {
        printf("Semantic Error: Variable '%s' not declared.\n", name);
        exit(1);
    }
    if (sym->type != INT) {
        printf("Type Error: Cannot assign integer value to char variable '%s'.\n", name);
        exit(1);
    }
    sym->value = value;
    sym->base = base;
    sym->initialized = 1;
}

void markInitialized(char* name) {
    Symbol* sym = lookupSymbol(name);
    if (sym) sym->initialized = 1;
}

// Helper: print the value as it would be written in the given base
void print_int_base(int decimal_value, int base) {
    if (base == 10) {
        printf("%d", decimal_value);
    }
    else if (base == 8) {
        printf("%o", decimal_value);
    }
    else if (base == 2) {
        if (decimal_value < 0) {
            printf("-");
            decimal_value = -decimal_value;
        }
        if (decimal_value == 0) {
            printf("0");
            return;
        }
        char binary[33] = {0};
        int index = 0;
        while (decimal_value > 0) {
            binary[index++] = '0' + (decimal_value % 2);
            decimal_value /= 2;
        }
        for (int i = index - 1; i >= 0; i--) {
            printf("%c", binary[i]);
        }
    }
}

void printSymbolTable() {
    printf("\n---- SYMBOL TABLE ----\n");
    for (int i = 0; i < symtab_count; i++) {
        printf("%s : ", symtab[i].name);
        if (symtab[i].type == INT) {
            printf("int");
            if (symtab[i].initialized) {
                printf(", value = (");
                print_int_base(symtab[i].value, symtab[i].base);
                printf(", %d)", symtab[i].base);
            }
        } else {
            printf("char");
            if (symtab[i].initialized) {
                printf(", value = '%c'", symtab[i].value);
            }
        }
        if (!symtab[i].initialized) {
            printf(", uninitialized");
        }
        printf("\n");
    }
    printf("\n");
}

// ----------- AST Creation Functions --------------------

ASTNode* createProgramNode(ASTNode* var_decls, ASTNode* statements) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PROGRAM;
    node->data.program.vars = var_decls;
    node->data.program.stmts = statements;
    return node;
}

ASTNode* createDeclListNode(ASTNode* decl, ASTNode* next) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_VARLIST;
    node->data.op.left = decl;
    node->data.op.right = next;
    return node;
}

ASTNode* createVarDeclNode(char* name, int type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_VARDECL;
    node->data.var_decl.name = strdup(name);
    node->data.var_decl.var_type = type;
    return node;
}

ASTNode* createBlockNode(ASTNode* statements) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_BLOCK;
    node->data.op.left = statements;
    node->data.op.right = NULL;
    return node;
}

ASTNode* createStatementListNode(ASTNode* stmt, ASTNode* next) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STMT_LIST;
    node->data.op.left = stmt;
    node->data.op.right = next;
    return node;
}

ASTNode* createIfNode(ASTNode* condition, ASTNode* true_branch, ASTNode* false_branch) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_IF;
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.true_branch = true_branch;
    node->data.if_stmt.false_branch = false_branch;
    return node;
}

ASTNode* createWhileNode(ASTNode* condition, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_WHILE;
    node->data.while_stmt.condition = condition;
    node->data.while_stmt.body = body;
    return node;
}

ASTNode* createForNode(ASTNode* var, ASTNode* init, ASTNode* limit, int op_type, ASTNode* step, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FOR;
    node->data.for_stmt.var = var;
    node->data.for_stmt.init = init;
    node->data.for_stmt.limit = limit;
    node->data.for_stmt.op_type = op_type;
    node->data.for_stmt.step = step;
    node->data.for_stmt.body = body;
    return node;
}

ASTNode* createAssignNode(char* var_name, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->data.assign.var_name = strdup(var_name);
    node->data.assign.value = value;
    return node;
}

ASTNode* createOperatorAssignNode(NodeType op_type, char* var_name, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = op_type;
    node->data.assign.var_name = strdup(var_name);
    node->data.assign.value = value;
    return node;
}

ASTNode* createOperatorNode(NodeType op_type, ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = op_type;
    node->data.op.left = left;
    node->data.op.right = right;
    return node;
}

ASTNode* createNumberNode(int value, int base) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_NUMBER;
    node->data.number.int_val = value;
    node->data.number.base = base;
    return node;
}

ASTNode* createVarRefNode(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_VAR_REF;
    node->data.var_ref.name = strdup(name);
    return node;
}

ASTNode* createStringNode(char* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STRING;
    node->data.str_val = strdup(value);
    return node;
}

ASTNode* createCharNode(char* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_CHAR;
    node->data.str_val = strdup(value);
    return node;
}

ASTNode* createPrintNode(ASTNode* arg) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PRINT;
    node->data.print.arg = arg;
    return node;
}

ASTNode* createScanNode(char* format, ASTNode* args) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_SCAN;
    node->data.scan.format = strdup(format);
    node->data.scan.args = args;
    return node;
}

ASTNode* createFormatStringNode(char* format, ASTNode* args) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FORMAT_STRING;
    node->data.formatString.format = strdup(format);
    node->data.formatString.args = args;
    return node;
}

ASTNode* createOutputArgListNode(ASTNode* arg, ASTNode* next) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STMT_LIST;
    node->data.op.left = arg;
    node->data.op.right = next;
    return node;
}

ASTNode* createInputArgListNode(ASTNode* arg, ASTNode* next) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STMT_LIST;
    node->data.op.left = arg;
    node->data.op.right = next;
    return node;
}

// ----------- AST Utility Functions ---------------------

void printIndent(int indent) {
    for (int i = 0; i < indent; i++) printf("  ");
}

const char* nodeTypeToString(NodeType type) {
    switch (type) {
        case NODE_PROGRAM: return "PROGRAM";
        case NODE_VARLIST: return "VARLIST";
        case NODE_VARDECL: return "VARDECL";
        case NODE_BLOCK: return "BLOCK";
        case NODE_STMT_LIST: return "STMT_LIST";
        case NODE_IF: return "IF";
        case NODE_WHILE: return "WHILE";
        case NODE_FOR: return "FOR";
        case NODE_PRINT: return "PRINT";
        case NODE_SCAN: return "SCAN";
        case NODE_ASSIGN: return "ASSIGN";
        case NODE_ADD_ASSIGN: return "ADD_ASSIGN";
        case NODE_SUB_ASSIGN: return "SUB_ASSIGN";
        case NODE_MUL_ASSIGN: return "MUL_ASSIGN";
        case NODE_DIV_ASSIGN: return "DIV_ASSIGN";
        case NODE_MOD_ASSIGN: return "MOD_ASSIGN";
        case NODE_ADD: return "ADD";
        case NODE_SUB: return "SUB";
        case NODE_MUL: return "MUL";
        case NODE_DIV: return "DIV";
        case NODE_MOD: return "MOD";
        case NODE_NEG: return "NEG";
        case NODE_EQ: return "EQ";
        case NODE_NEQ: return "NEQ";
        case NODE_GT: return "GT";
        case NODE_LT: return "LT";
        case NODE_GEQ: return "GEQ";
        case NODE_LEQ: return "LEQ";
        case NODE_NUMBER: return "NUMBER";
        case NODE_VAR_REF: return "VAR_REF";
        case NODE_STRING: return "STRING";
        case NODE_CHAR: return "CHAR";
        case NODE_FORMAT_STRING: return "FORMAT_STRING";
        default: return "UNKNOWN";
    }
}

// ... printAST and freeAST unchanged ...

// ----------- Interpreter ------------------------------

// Helper: get base precedence (10 > 8 > 2)
int base_precedence(int base) {
    if (base == 10) return 3;
    if (base == 8) return 2;
    if (base == 2) return 1;
    return 0;
}

// Helper: convert decimal to base, return as int (for binary/octal output)
int to_base(int value, int base) {
    if (base == 10) return value;
    int result = 0, factor = 1;
    while (value > 0) {
        result += (value % base) * factor;
        value /= base;
        factor *= 10;
    }
    return result;
}

// Helper: convert (num, base) to decimal
int to_decimal(int value, int base) {
    int result = 0, factor = 1;
    int v = value;
    while (v > 0) {
        int digit = v % 10;
        result += digit * factor;
        factor *= base;
        v /= 10;
    }
    return result;
}

// Helper: get the higher base (10 > 8 > 2)
int higher_base(int base1, int base2) {
    if (base1 == 10 || base2 == 10) return 10;
    if (base1 == 8 || base2 == 8) return 8;
    return 2;
}

// Evaluate arithmetic expressions with base and type checking
IntResult evaluate(ASTNode* node) {
    IntResult res = {0, 10};
    if (!node) return res;
    switch (node->type) {
        case NODE_NUMBER:
            res.value = node->data.number.int_val;
            res.base = node->data.number.base;
            return res;
        case NODE_VAR_REF: {
            Symbol* sym = lookupSymbol(node->data.var_ref.name);
            if (!sym) {
                printf("Semantic Error: Variable '%s' not declared.\n", node->data.var_ref.name);
                exit(1);
            }
            if (!sym->initialized) {
                printf("Semantic Error: Variable '%s' used before initialization.\n", node->data.var_ref.name);
                exit(1);
            }
            if (sym->type != INT) {
                printf("Type Error: Variable '%s' is not of type int.\n", node->data.var_ref.name);
                exit(1);
            }
            res.value = sym->value;
            res.base = sym->base;
            return res;
        }
        case NODE_ADD:
        case NODE_SUB:
        case NODE_MUL:
        case NODE_DIV:
        case NODE_MOD: {
            IntResult left = evaluate(node->data.op.left);
            IntResult right = evaluate(node->data.op.right);

            // Convert operands to decimal for calculation
            int left_decimal = to_decimal(left.value, left.base);
            int right_decimal = to_decimal(right.value, right.base);

            int result_base = higher_base(left.base, right.base);
            int result_decimal;

            switch (node->type) {
                case NODE_ADD: result_decimal = left_decimal + right_decimal; break;
                case NODE_SUB: result_decimal = left_decimal - right_decimal; break;
                case NODE_MUL: result_decimal = left_decimal * right_decimal; break;
                case NODE_DIV: result_decimal = left_decimal / right_decimal; break;
                case NODE_MOD: result_decimal = left_decimal % right_decimal; break;
                default: result_decimal = 0; break;
            }

            // Convert result back to the correct base for storage/display
            res.value = result_decimal;
            res.base = result_base;
            return res;
        }
        case NODE_EQ:
        case NODE_NEQ:
        case NODE_GT:
        case NODE_LT:
        case NODE_GEQ:
        case NODE_LEQ: {
            IntResult left = evaluate(node->data.op.left);
            IntResult right = evaluate(node->data.op.right);
            int lval = to_decimal(left.value, left.base);
            int rval = to_decimal(right.value, right.base);
            switch (node->type) {
                case NODE_EQ:  res.value = (lval == rval); break;
                case NODE_NEQ: res.value = (lval != rval); break;
                case NODE_GT:  res.value = (lval > rval); break;
                case NODE_LT:  res.value = (lval < rval); break;
                case NODE_GEQ: res.value = (lval >= rval); break;
                case NODE_LEQ: res.value = (lval <= rval); break;
                default: res.value = 0; break;
            }
            res.base = 10;
            return res;
        }
        case NODE_NEG: {
            IntResult val = evaluate(node->data.op.left);
            int dec = to_decimal(val.value, val.base);
            val.value = -dec;
            val.base = 10;
            return val;
        }
        default:
            printf("Evaluation error at unknown node type %d (%s)\n", node->type, nodeTypeToString(node->type));
            exit(1);
    }
}

// Helper to get the next argument and advance the pointer
static ASTNode* get_next_arg(ASTNode** arg_ptr) {
    if (!*arg_ptr) return NULL;
    ASTNode* current = *arg_ptr;
    if (current->type == NODE_STMT_LIST) {
        ASTNode* left = current->data.op.left;
        *arg_ptr = current->data.op.right;
        return left;
    } else {
        *arg_ptr = NULL;
        return current;
    }
}

// Helper: print (num, base) for int values
static void print_any_arg(ASTNode* arg) {
    if (!arg) return;
    switch (arg->type) {
        case NODE_VAR_REF: {
            Symbol* sym = lookupSymbol(arg->data.var_ref.name);
            if (!sym || !sym->initialized) {
                printf("Error: Variable not initialized\n");
                exit(1);
            }
            if (sym->type == INT) {
                printf("(");
                print_int_base(sym->value, sym->base);
                printf(", %d)", sym->base);
            } else {
                printf("'%c'", sym->value);
            }
            break;
        }
        case NODE_STRING:
            printf("%s", arg->data.str_val);
            break;
        case NODE_NUMBER:
            printf("(");
            print_int_base(arg->data.number.int_val, arg->data.number.base);
            printf(", %d)", arg->data.number.base);
            break;
        default:
            printf("[unknown type]");
            break;
    }
}

void execute(ASTNode* node) {
    if (!node) return;
    switch (node->type) {
        case NODE_PROGRAM:
            execute(node->data.program.vars);
            execute(node->data.program.stmts);
            break;
        case NODE_VARLIST:
            execute(node->data.op.left);
            execute(node->data.op.right);
            break;
        case NODE_VARDECL:
            insertSymbol(node->data.var_decl.name, node->data.var_decl.var_type);
            break;
        case NODE_STMT_LIST:
            execute(node->data.op.left);
            execute(node->data.op.right);
            break;
        case NODE_ASSIGN: {
            Symbol* sym = lookupSymbol(node->data.assign.var_name);
            if (!sym) {
                printf("Semantic Error: Variable '%s' not declared.\n", node->data.assign.var_name);
                exit(1);
            }
            if (sym->type == INT) {
                IntResult val = evaluate(node->data.assign.value);
                updateSymbolValue(node->data.assign.var_name, val.value, val.base);
            } else if (sym->type == CHAR) {
                if (node->data.assign.value->type != NODE_CHAR) {
                    printf("Type Error: Cannot assign non-char to char variable '%s'.\n", node->data.assign.var_name);
                    exit(1);
                }
                sym->value = node->data.assign.value->data.str_val[1];
                sym->initialized = 1;
            }
            break;
        }
        case NODE_ADD_ASSIGN: {
            Symbol* sym = lookupSymbol(node->data.assign.var_name);
            if (!sym) {
                printf("Semantic Error: Variable '%s' not declared.\n", node->data.assign.var_name);
                exit(1);
            }
            IntResult val = evaluate(node->data.assign.value);
            sym->value += val.value;
            sym->initialized = 1;
            break;
        }
        case NODE_SUB_ASSIGN: {
            Symbol* sym = lookupSymbol(node->data.assign.var_name);
            if (!sym) {
                printf("Semantic Error: Variable '%s' not declared.\n", node->data.assign.var_name);
                exit(1);
            }
            IntResult val = evaluate(node->data.assign.value);
            sym->value -= val.value;
            sym->initialized = 1;
            break;
        }
        case NODE_MUL_ASSIGN: {
            Symbol* sym = lookupSymbol(node->data.assign.var_name);
            if (!sym) {
                printf("Semantic Error: Variable '%s' not declared.\n", node->data.assign.var_name);
                exit(1);
            }
            IntResult val = evaluate(node->data.assign.value);
            sym->value *= val.value;
            sym->initialized = 1;
            break;
        }
        case NODE_DIV_ASSIGN: {
            Symbol* sym = lookupSymbol(node->data.assign.var_name);
            if (!sym) {
                printf("Semantic Error: Variable '%s' not declared.\n", node->data.assign.var_name);
                exit(1);
            }
            IntResult val = evaluate(node->data.assign.value);
            sym->value /= val.value;
            sym->initialized = 1;
            break;
        }
        case NODE_MOD_ASSIGN: {
            Symbol* sym = lookupSymbol(node->data.assign.var_name);
            if (!sym) {
                printf("Semantic Error: Variable '%s' not declared.\n", node->data.assign.var_name);
                exit(1);
            }
            IntResult val = evaluate(node->data.assign.value);
            sym->value %= val.value;
            sym->initialized = 1;
            break;
        }
        case NODE_IF: {
            IntResult cond = evaluate(node->data.if_stmt.condition);
            if (cond.value)
                execute(node->data.if_stmt.true_branch);
            else if (node->data.if_stmt.false_branch)
                execute(node->data.if_stmt.false_branch);
            break;
        }
        case NODE_WHILE: {
            IntResult cond = evaluate(node->data.while_stmt.condition);
            while (cond.value) {
                execute(node->data.while_stmt.body);
                cond = evaluate(node->data.while_stmt.condition);
            }
            break;
        }
        case NODE_FOR: {
            // Get the loop variable symbol
            Symbol* sym = lookupSymbol(node->data.for_stmt.var->data.var_ref.name);
            if (!sym) {
                printf("Semantic Error: Variable '%s' not declared.\n", 
                       node->data.for_stmt.var->data.var_ref.name);
                exit(1);
            }
        
            // Evaluate initial, limit, and step values (convert to decimal)
            IntResult init = evaluate(node->data.for_stmt.init);
            IntResult limit = evaluate(node->data.for_stmt.limit);
            IntResult step = evaluate(node->data.for_stmt.step);
        
            int init_val = to_decimal(init.value, init.base);
            int limit_val = to_decimal(limit.value, limit.base);
            int step_val = to_decimal(step.value, step.base);
        
            // Validate step is positive
            if (step_val <= 0) {
                printf("Semantic Error: Step value must be positive in for loop.\n");
                exit(1);
            }
        
            // Initialize loop variable
            sym->value = init_val;
            sym->base = 10;  // Use decimal internally for calculations
            sym->initialized = 1;
        
            // Determine direction based on op_type (273 is TO, 274 is DOWNTO)
            int ascending = (node->data.for_stmt.op_type == 273); // TO operation
        
            // Execute the loop
            while (1) {
                // Check if we should continue
                int should_continue;
                if (ascending) {
                    should_continue = (sym->value <= limit_val);
                } else {
                    should_continue = (sym->value >= limit_val);
                }
        
                if (!should_continue) break;
        
                // Execute the loop body
                execute(node->data.for_stmt.body);
        
                // Update loop variable
                if (ascending) {
                    sym->value += step_val;
                } else {
                    sym->value -= step_val;
                }
            }
            break;
        }
        case NODE_PRINT: {
            ASTNode* arg = node->data.print.arg;
            if (!arg) break;
            if (arg->type == NODE_STRING) {
                printf("%s\n", arg->data.str_val);
            } else if (arg->type == NODE_FORMAT_STRING) {
                const char* fmt = arg->data.formatString.format;
                ASTNode* args = arg->data.formatString.args;
                const char* p = fmt;
                while (*p) {
                    if (*p == '@') {
                        ASTNode* this_arg = get_next_arg(&args);
                        if (this_arg) {
                            print_any_arg(this_arg);
                        } else {
                            printf("@");
                        }
                        p++;
                    } else {
                        putchar(*p++);
                    }
                }
                printf("\n");
            } else {
                print_any_arg(arg);
                printf("\n");
            }
            break;
        }
        case NODE_SCAN: {
            // Count number of variables to scan
            int var_count = 0;
            ASTNode* tmp = node->data.scan.args;
            while (tmp) {
                var_count++;
                if (tmp->type == NODE_STMT_LIST)
                    tmp = tmp->data.op.right;
                else
                    break;
            }

            // Read a single line of input
            char input_line[256];
            if (fgets(input_line, sizeof(input_line), stdin) == NULL) {
                printf("Input Error\n");
                exit(1);
            }

            // Tokenize input by spaces
            char* token = strtok(input_line, " \t\r\n");
            ASTNode* args = node->data.scan.args;
            for (int i = 0; i < var_count && token != NULL; i++) {
                ASTNode* varNode = args;
                if (args->type == NODE_STMT_LIST) {
                    varNode = args->data.op.left;
                    args = args->data.op.right;
                } else {
                    args = NULL;
                }
                if (varNode->type == NODE_VAR_REF) {
                    Symbol* sym = lookupSymbol(varNode->data.var_ref.name);
                    if (!sym) {
                        printf("Semantic Error: Variable '%s' not declared.\n", varNode->data.var_ref.name);
                        exit(1);
                    }
                    if (sym->type == INT) {
                        int val, base = 10;
                        char* comma = strchr(token, ',');
                        if (comma) {
                            *comma = '\0';
                            val = atoi(token);
                            base = atoi(comma + 1);
                        } else {
                            val = atoi(token);
                            base = 10;
                        }
                        // Validate base
                        if (base != 2 && base != 8 && base != 10) {
                            printf("Semantic Error: Invalid base %d for input.\n", base);
                            exit(1);
                        }
                        // Validate digits for base
                        int tmpv = val < 0 ? -val : val;
                        int valid = 1;
                        if (tmpv == 0) valid = 1;
                        while (tmpv > 0) {
                            int digit = tmpv % 10;
                            if (digit >= base) valid = 0;
                            tmpv /= 10;
                        }
                        if (!valid) {
                            printf("Semantic Error: Number %d contains invalid digits for base %d.\n", val, base);
                            exit(1);
                        }
                        sym->value = val;
                        sym->base = base;
                        sym->initialized = 1;
                    } else if (sym->type == CHAR) {
                        sym->value = token[0];
                        sym->initialized = 1;
                    }
                }
                token = strtok(NULL, " \t\r\n");
            }
            break;
        }
        case NODE_BLOCK:
            execute(node->data.op.left);
            break;
        default:
            break;
    }
}

void freeAST(ASTNode* node) {
}