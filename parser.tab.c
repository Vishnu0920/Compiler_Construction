/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin;
extern int yylex();
extern int yylineno;
extern char* yytext;

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error at line %d near token '%s': %s\n", yylineno, yytext, s);
}

int syntax_errors = 0;

/* Symbol table for variable tracking */
#define MAX_SYMBOLS 100
char* symbol_table[MAX_SYMBOLS];
int symbol_count = 0;

/* Add a variable to the symbol table */
void add_symbol(char* name) {
    if (symbol_count < MAX_SYMBOLS) {
        /* Check if symbol already exists */
        for (int i = 0; i < symbol_count; i++) {
            if (strcmp(symbol_table[i], name) == 0) {
                return; /* Already exists */
            }
        }
        symbol_table[symbol_count] = strdup(name);
        symbol_count++;
    }
}

/* Check if a variable exists in the symbol table */
int symbol_exists(char* name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i], name) == 0) {
            return 1; /* Found */
        }
    }
    return 0; /* Not found */
}

/* Check if a number base is valid (2, 8, or 10) */
int is_valid_base(int base) {
    return (base == 2 || base == 8 || base == 10);
}

#line 122 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BEGIN_K = 3,                    /* BEGIN_K  */
  YYSYMBOL_END_K = 4,                      /* END_K  */
  YYSYMBOL_PROGRAM = 5,                    /* PROGRAM  */
  YYSYMBOL_COLON = 6,                      /* COLON  */
  YYSYMBOL_SEMICOLON = 7,                  /* SEMICOLON  */
  YYSYMBOL_COMMA = 8,                      /* COMMA  */
  YYSYMBOL_LPAR = 9,                       /* LPAR  */
  YYSYMBOL_RPAR = 10,                      /* RPAR  */
  YYSYMBOL_LBRACK = 11,                    /* LBRACK  */
  YYSYMBOL_RBRACK = 12,                    /* RBRACK  */
  YYSYMBOL_INT = 13,                       /* INT  */
  YYSYMBOL_CHAR = 14,                      /* CHAR  */
  YYSYMBOL_PRINT = 15,                     /* PRINT  */
  YYSYMBOL_SCAN = 16,                      /* SCAN  */
  YYSYMBOL_VARDECL = 17,                   /* VARDECL  */
  YYSYMBOL_INC = 18,                       /* INC  */
  YYSYMBOL_DEC = 19,                       /* DEC  */
  YYSYMBOL_ADD_OP = 20,                    /* ADD_OP  */
  YYSYMBOL_SUB_OP = 21,                    /* SUB_OP  */
  YYSYMBOL_MUL_OP = 22,                    /* MUL_OP  */
  YYSYMBOL_DIV_OP = 23,                    /* DIV_OP  */
  YYSYMBOL_MOD_OP = 24,                    /* MOD_OP  */
  YYSYMBOL_ID = 25,                        /* ID  */
  YYSYMBOL_STRING = 26,                    /* STRING  */
  YYSYMBOL_CHARACTER = 27,                 /* CHARACTER  */
  YYSYMBOL_FORMAT_STRING = 28,             /* FORMAT_STRING  */
  YYSYMBOL_INPUT_STRING = 29,              /* INPUT_STRING  */
  YYSYMBOL_NUMBER = 30,                    /* NUMBER  */
  YYSYMBOL_IF_K = 31,                      /* IF_K  */
  YYSYMBOL_ELSE_K = 32,                    /* ELSE_K  */
  YYSYMBOL_WHILE_K = 33,                   /* WHILE_K  */
  YYSYMBOL_FOR_K = 34,                     /* FOR_K  */
  YYSYMBOL_TO_K = 35,                      /* TO_K  */
  YYSYMBOL_DO_K = 36,                      /* DO_K  */
  YYSYMBOL_EQ = 37,                        /* EQ  */
  YYSYMBOL_NEQ = 38,                       /* NEQ  */
  YYSYMBOL_GT = 39,                        /* GT  */
  YYSYMBOL_LT = 40,                        /* LT  */
  YYSYMBOL_GEQ = 41,                       /* GEQ  */
  YYSYMBOL_LEQ = 42,                       /* LEQ  */
  YYSYMBOL_ASSIGN = 43,                    /* ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 44,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 45,                /* SUB_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 46,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 47,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 48,                /* MOD_ASSIGN  */
  YYSYMBOL_UMINUS = 49,                    /* UMINUS  */
  YYSYMBOL_IF_PREC = 50,                   /* IF_PREC  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_Program = 52,                   /* Program  */
  YYSYMBOL_VarDeclSection = 53,            /* VarDeclSection  */
  YYSYMBOL_DeclList = 54,                  /* DeclList  */
  YYSYMBOL_Decl = 55,                      /* Decl  */
  YYSYMBOL_Type = 56,                      /* Type  */
  YYSYMBOL_VarNameDecl = 57,               /* VarNameDecl  */
  YYSYMBOL_VarName = 58,                   /* VarName  */
  YYSYMBOL_StatementSection = 59,          /* StatementSection  */
  YYSYMBOL_StatementList = 60,             /* StatementList  */
  YYSYMBOL_Statement = 61,                 /* Statement  */
  YYSYMBOL_OutputStmt = 62,                /* OutputStmt  */
  YYSYMBOL_PrintArg = 63,                  /* PrintArg  */
  YYSYMBOL_OutputArgList = 64,             /* OutputArgList  */
  YYSYMBOL_OutputArg = 65,                 /* OutputArg  */
  YYSYMBOL_InputStmt = 66,                 /* InputStmt  */
  YYSYMBOL_InputString = 67,               /* InputString  */
  YYSYMBOL_InputArgList = 68,              /* InputArgList  */
  YYSYMBOL_Assignment = 69,                /* Assignment  */
  YYSYMBOL_AssnArg = 70,                   /* AssnArg  */
  YYSYMBOL_NUM = 71,                       /* NUM  */
  YYSYMBOL_ConditionalStmt = 72,           /* ConditionalStmt  */
  YYSYMBOL_Block = 73,                     /* Block  */
  YYSYMBOL_LoopStmt = 74,                  /* LoopStmt  */
  YYSYMBOL_LoopOp = 75,                    /* LoopOp  */
  YYSYMBOL_Condition = 76,                 /* Condition  */
  YYSYMBOL_RelOp = 77,                     /* RelOp  */
  YYSYMBOL_ArithmeticExpression = 78,      /* ArithmeticExpression  */
  YYSYMBOL_Term = 79,                      /* Term  */
  YYSYMBOL_Factor = 80,                    /* Factor  */
  YYSYMBOL_Primary = 81                    /* Primary  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   166

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  161

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    88,    88,    93,    98,    99,   103,   108,   109,   113,
     119,   128,   135,   145,   146,   150,   151,   155,   156,   157,
     158,   159,   163,   168,   169,   170,   174,   175,   179,   180,
     181,   185,   191,   195,   196,   200,   202,   204,   206,   208,
     210,   215,   216,   217,   221,   233,   235,   240,   245,   247,
     252,   253,   257,   262,   263,   264,   265,   266,   267,   271,
     272,   273,   277,   278,   279,   280,   284,   285,   289,   290,
     291
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "BEGIN_K", "END_K",
  "PROGRAM", "COLON", "SEMICOLON", "COMMA", "LPAR", "RPAR", "LBRACK",
  "RBRACK", "INT", "CHAR", "PRINT", "SCAN", "VARDECL", "INC", "DEC",
  "ADD_OP", "SUB_OP", "MUL_OP", "DIV_OP", "MOD_OP", "ID", "STRING",
  "CHARACTER", "FORMAT_STRING", "INPUT_STRING", "NUMBER", "IF_K", "ELSE_K",
  "WHILE_K", "FOR_K", "TO_K", "DO_K", "EQ", "NEQ", "GT", "LT", "GEQ",
  "LEQ", "ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "UMINUS", "IF_PREC", "$accept", "Program",
  "VarDeclSection", "DeclList", "Decl", "Type", "VarNameDecl", "VarName",
  "StatementSection", "StatementList", "Statement", "OutputStmt",
  "PrintArg", "OutputArgList", "OutputArg", "InputStmt", "InputString",
  "InputArgList", "Assignment", "AssnArg", "NUM", "ConditionalStmt",
  "Block", "LoopStmt", "LoopOp", "Condition", "RelOp",
  "ArithmeticExpression", "Term", "Factor", "Primary", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-71)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      36,    13,    25,    48,   -71,    57,    55,    22,    82,    89,
      90,    91,    94,    95,    75,   -31,   103,   -71,    22,   -71,
     -71,   -71,   -71,   -71,   100,    61,    81,    23,    23,    23,
      68,    37,    37,    37,    37,    37,    37,   107,   -71,    88,
     110,   100,   -71,   108,   109,   111,   -71,   112,    15,    23,
     -71,   -71,    53,    69,   -71,   -71,   113,   -11,   114,    23,
     -71,   -71,   115,    74,   120,   121,   122,   123,   124,   -71,
     125,   126,   102,   -71,    50,    50,   128,    75,   129,    47,
     -71,   -71,    23,    23,    23,    23,    23,   130,   -71,   -71,
     -71,   -71,   -71,   -71,    23,   135,    31,   -71,   -71,   -71,
     -71,   -71,   -71,   116,     8,   -71,   -71,   -71,   -71,   131,
      74,   -71,   -71,   133,   132,   117,   -71,    69,    69,   -71,
     -71,   -71,    22,     1,    74,    22,    23,   136,   -71,   -71,
     134,    50,    75,   138,   139,   147,   -71,   130,   148,    65,
     -71,   146,   -71,   -71,   -71,   -71,   -71,   149,   150,   -71,
     -71,    23,   -71,   -71,   -71,    -1,   140,    22,   151,   152,
     -71
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,    14,     0,     0,
       0,    11,     0,     0,     0,     0,     0,    13,    16,    17,
      18,    19,    20,    21,     5,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15,     0,
       0,     5,    23,     0,     0,     0,    32,     0,     0,     0,
      69,    68,     0,    59,    62,    66,     0,     0,     0,     0,
      41,    42,     0,    43,     0,     0,     0,     0,     0,     2,
       9,     0,     0,     4,     0,     0,     0,     0,     0,     0,
      67,    12,     0,     0,     0,     0,     0,     0,    53,    54,
      55,    56,    57,    58,     0,     0,     0,    35,    36,    37,
      38,    39,    40,     0,     0,     3,    29,    30,    25,    26,
      28,    24,    22,    33,     0,     0,    70,    60,    61,    63,
      64,    65,     0,     0,    52,     0,     0,     0,     7,     8,
       0,     0,     0,     0,     0,     0,    45,     0,     0,     0,
      10,     0,    27,    34,    31,    44,    47,     0,     0,    50,
      51,     0,     6,    46,    48,     0,     0,     0,     0,     0,
      49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -71,   -71,   -71,   119,   -71,   -71,   -71,    -7,   -71,   -17,
     -71,   -71,   -71,   -70,   -71,   -71,   -71,     0,   -71,    46,
     -71,   -71,    17,   -71,   -71,   137,   -71,   -25,    14,   -43,
     -71
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     7,    40,    41,   130,    71,    50,    16,    17,
      18,    19,    45,   108,   109,    20,    47,   114,    21,    62,
      51,    22,   123,    23,   151,    56,    94,    63,    53,    54,
      55
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      15,    38,    52,    57,    57,   111,    80,    30,   136,    82,
      83,    15,    31,    32,    33,    34,    35,    36,     3,    82,
      83,   128,   129,    79,    48,     4,    88,    89,    90,    91,
      92,    93,    48,   137,    96,   156,    49,     9,    10,     1,
      11,   119,   120,   121,    49,    78,    48,    11,    11,   110,
     110,    82,    83,    12,     5,    13,    14,   116,    49,    48,
       6,   142,    11,    60,    61,    81,   126,    82,    83,   124,
     113,    49,     8,    82,    83,    11,   106,   107,    64,    65,
      66,    67,    68,   149,   150,    82,    83,    42,    24,    43,
      44,    84,    85,    86,    82,    83,   117,   118,    25,    26,
      11,   139,    27,    28,    29,   135,   110,    37,   138,    39,
      46,    59,    69,    70,    72,    15,    74,    75,    15,   105,
      77,    76,    97,    87,    95,   113,   155,    98,    99,   100,
     101,   102,   143,   122,   104,   112,   103,   115,   125,   131,
     158,   132,   133,   157,   141,   144,   127,   134,   140,   145,
      15,   146,   148,   152,   147,   159,   153,   154,     0,   160,
      73,     0,     0,     0,     0,     0,    58
};

static const yytype_int16 yycheck[] =
{
       7,    18,    27,    28,    29,    75,    49,    14,     7,    20,
      21,    18,    43,    44,    45,    46,    47,    48,     5,    20,
      21,    13,    14,    48,     9,     0,    37,    38,    39,    40,
      41,    42,     9,    32,    59,    36,    21,    15,    16,     3,
      25,    84,    85,    86,    21,    30,     9,    25,    25,    74,
      75,    20,    21,    31,     6,    33,    34,    10,    21,     9,
       3,   131,    25,    26,    27,    12,    35,    20,    21,    94,
      77,    21,    17,    20,    21,    25,    26,    27,    32,    33,
      34,    35,    36,    18,    19,    20,    21,    26,     6,    28,
      29,    22,    23,    24,    20,    21,    82,    83,     9,     9,
      25,   126,    11,     9,     9,   122,   131,     4,   125,     9,
      29,    43,     5,    25,     4,   122,     8,     8,   125,    17,
       8,    10,     7,    10,    10,   132,   151,     7,     7,     7,
       7,     7,   132,     3,     8,     7,    11,     8,     3,     8,
     157,     8,    10,     3,    10,     7,    30,    30,    12,    10,
     157,     4,     4,     7,   137,     4,     7,     7,    -1,     7,
      41,    -1,    -1,    -1,    -1,    -1,    29
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    52,     5,     0,     6,     3,    53,    17,    15,
      16,    25,    31,    33,    34,    58,    59,    60,    61,    62,
      66,    69,    72,    74,     6,     9,     9,    11,     9,     9,
      58,    43,    44,    45,    46,    47,    48,     4,    60,     9,
      54,    55,    26,    28,    29,    63,    29,    67,     9,    21,
      58,    71,    78,    79,    80,    81,    76,    78,    76,    43,
      26,    27,    70,    78,    70,    70,    70,    70,    70,     5,
      25,    57,     4,    54,     8,     8,    10,     8,    30,    78,
      80,    12,    20,    21,    22,    23,    24,    10,    37,    38,
      39,    40,    41,    42,    77,    10,    78,     7,     7,     7,
       7,     7,     7,    11,     8,    17,    26,    27,    64,    65,
      78,    64,     7,    58,    68,     8,    10,    79,    79,    80,
      80,    80,     3,    73,    78,     3,    35,    30,    13,    14,
      56,     8,     8,    10,    30,    60,     7,    32,    60,    78,
      12,    10,    64,    68,     7,    10,     4,    73,     4,    18,
      19,    75,     7,     7,     7,    78,    36,     3,    60,     4,
       7
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    54,    54,    55,    56,    56,    57,
      57,    58,    58,    59,    59,    60,    60,    61,    61,    61,
      61,    61,    62,    63,    63,    63,    64,    64,    65,    65,
      65,    66,    67,    68,    68,    69,    69,    69,    69,    69,
      69,    70,    70,    70,    71,    72,    72,    73,    74,    74,
      75,    75,    76,    77,    77,    77,    77,    77,    77,    78,
      78,    78,    79,    79,    79,    79,    80,    80,    81,    81,
      81
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     7,     6,     2,     0,     6,     1,     1,     1,
       4,     1,     4,     1,     0,     2,     1,     1,     1,     1,
       1,     1,     5,     1,     3,     3,     1,     3,     1,     1,
       1,     7,     1,     1,     3,     4,     4,     4,     4,     4,
       4,     1,     1,     1,     5,     6,     8,     3,     8,    13,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     1,     1,
       3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: BEGIN_K PROGRAM COLON VarDeclSection StatementSection END_K PROGRAM  */
#line 89 "parser.y"
    { printf("Successfully parsed program structure\n"); }
#line 1570 "parser.tab.c"
    break;

  case 3: /* VarDeclSection: BEGIN_K VARDECL COLON DeclList END_K VARDECL  */
#line 94 "parser.y"
    { printf("Successfully parsed variable declaration section\n"); }
#line 1576 "parser.tab.c"
    break;

  case 6: /* Decl: LPAR VarNameDecl COMMA Type RPAR SEMICOLON  */
#line 104 "parser.y"
    { printf("Parsed variable declaration: %s\n", (yyvsp[-4].str_val)); }
#line 1582 "parser.tab.c"
    break;

  case 7: /* Type: INT  */
#line 108 "parser.y"
          { printf("Type: int\n"); }
#line 1588 "parser.tab.c"
    break;

  case 8: /* Type: CHAR  */
#line 109 "parser.y"
           { printf("Type: char\n"); }
#line 1594 "parser.tab.c"
    break;

  case 9: /* VarNameDecl: ID  */
#line 114 "parser.y"
    {
        (yyval.str_val) = (yyvsp[0].str_val);
        add_symbol((yyvsp[0].str_val));
        printf("Variable name: %s\n", (yyvsp[0].str_val));
    }
#line 1604 "parser.tab.c"
    break;

  case 10: /* VarNameDecl: ID LBRACK NUMBER RBRACK  */
#line 120 "parser.y"
    {
        (yyval.str_val) = (yyvsp[-3].str_val);
        add_symbol((yyvsp[-3].str_val));
        printf("Array declaration: %s[%d]\n", (yyvsp[-3].str_val), (yyvsp[-1].int_val));
    }
#line 1614 "parser.tab.c"
    break;

  case 11: /* VarName: ID  */
#line 128 "parser.y"
         { 
        (yyval.str_val) = (yyvsp[0].str_val); 
        if (!symbol_exists((yyvsp[0].str_val))) {
            fprintf(stderr, "Semantic Error at line %d: Undeclared variable '%s'\n", yylineno, (yyvsp[0].str_val));
            syntax_errors++;
        }
      }
#line 1626 "parser.tab.c"
    break;

  case 12: /* VarName: ID LBRACK ArithmeticExpression RBRACK  */
#line 135 "parser.y"
                                            { 
        (yyval.str_val) = (yyvsp[-3].str_val); 
        if (!symbol_exists((yyvsp[-3].str_val))) {
            fprintf(stderr, "Semantic Error at line %d: Undeclared variable '%s'\n", yylineno, (yyvsp[-3].str_val));
            syntax_errors++;
        }
      }
#line 1638 "parser.tab.c"
    break;

  case 13: /* StatementSection: StatementList  */
#line 145 "parser.y"
                    { printf("Successfully parsed statement section\n"); }
#line 1644 "parser.tab.c"
    break;

  case 22: /* OutputStmt: PRINT LPAR PrintArg RPAR SEMICOLON  */
#line 164 "parser.y"
    { printf("Parsed print statement\n"); }
#line 1650 "parser.tab.c"
    break;

  case 23: /* PrintArg: STRING  */
#line 168 "parser.y"
             { printf("Print string literal\n"); }
#line 1656 "parser.tab.c"
    break;

  case 24: /* PrintArg: INPUT_STRING COMMA OutputArgList  */
#line 169 "parser.y"
                                       { printf("Print input format string with arguments\n"); }
#line 1662 "parser.tab.c"
    break;

  case 25: /* PrintArg: FORMAT_STRING COMMA OutputArgList  */
#line 170 "parser.y"
                                        { printf("Print format string with arguments\n"); }
#line 1668 "parser.tab.c"
    break;

  case 31: /* InputStmt: SCAN LPAR InputString COMMA InputArgList RPAR SEMICOLON  */
#line 186 "parser.y"
    { printf("Parsed scan statement\n"); }
#line 1674 "parser.tab.c"
    break;

  case 33: /* InputArgList: VarName  */
#line 195 "parser.y"
              { printf("Input to variable: %s\n", (yyvsp[0].str_val)); }
#line 1680 "parser.tab.c"
    break;

  case 34: /* InputArgList: VarName COMMA InputArgList  */
#line 196 "parser.y"
                                 { printf("Input to variable: %s\n", (yyvsp[-2].str_val)); }
#line 1686 "parser.tab.c"
    break;

  case 35: /* Assignment: VarName ASSIGN AssnArg SEMICOLON  */
#line 201 "parser.y"
    { printf("Parsed assignment with :=\n"); }
#line 1692 "parser.tab.c"
    break;

  case 36: /* Assignment: VarName ADD_ASSIGN AssnArg SEMICOLON  */
#line 203 "parser.y"
    { printf("Parsed assignment with +=\n"); }
#line 1698 "parser.tab.c"
    break;

  case 37: /* Assignment: VarName SUB_ASSIGN AssnArg SEMICOLON  */
#line 205 "parser.y"
    { printf("Parsed assignment with -=\n"); }
#line 1704 "parser.tab.c"
    break;

  case 38: /* Assignment: VarName MUL_ASSIGN AssnArg SEMICOLON  */
#line 207 "parser.y"
    { printf("Parsed assignment with *=\n"); }
#line 1710 "parser.tab.c"
    break;

  case 39: /* Assignment: VarName DIV_ASSIGN AssnArg SEMICOLON  */
#line 209 "parser.y"
    { printf("Parsed assignment with /=\n"); }
#line 1716 "parser.tab.c"
    break;

  case 40: /* Assignment: VarName MOD_ASSIGN AssnArg SEMICOLON  */
#line 211 "parser.y"
    { printf("Parsed assignment with %%=\n"); }
#line 1722 "parser.tab.c"
    break;

  case 44: /* NUM: LPAR NUMBER COMMA NUMBER RPAR  */
#line 222 "parser.y"
    { 
        if (!is_valid_base((yyvsp[-1].int_val))) {
            fprintf(stderr, "Semantic Error at line %d: Invalid number base %d. Only bases 2, 8, and 10 are allowed.\n", yylineno, (yyvsp[-1].int_val));
            syntax_errors++;
        }
        (yyval.int_val) = (yyvsp[-3].int_val); 
        printf("Number: %d in base %d\n", (yyvsp[-3].int_val), (yyvsp[-1].int_val)); 
    }
#line 1735 "parser.tab.c"
    break;

  case 45: /* ConditionalStmt: IF_K LPAR Condition RPAR Block SEMICOLON  */
#line 234 "parser.y"
    { printf("Parsed if statement\n"); }
#line 1741 "parser.tab.c"
    break;

  case 46: /* ConditionalStmt: IF_K LPAR Condition RPAR Block ELSE_K Block SEMICOLON  */
#line 236 "parser.y"
    { printf("Parsed if-else statement\n"); }
#line 1747 "parser.tab.c"
    break;

  case 47: /* Block: BEGIN_K StatementList END_K  */
#line 241 "parser.y"
    { printf("Parsed block of statements\n"); }
#line 1753 "parser.tab.c"
    break;

  case 48: /* LoopStmt: WHILE_K LPAR Condition RPAR BEGIN_K StatementList END_K SEMICOLON  */
#line 246 "parser.y"
    { printf("Parsed while loop\n"); }
#line 1759 "parser.tab.c"
    break;

  case 49: /* LoopStmt: FOR_K VarName ASSIGN ArithmeticExpression TO_K ArithmeticExpression LoopOp ArithmeticExpression DO_K BEGIN_K StatementList END_K SEMICOLON  */
#line 248 "parser.y"
    { printf("Parsed for loop\n"); }
#line 1765 "parser.tab.c"
    break;

  case 50: /* LoopOp: INC  */
#line 252 "parser.y"
          { printf("Loop operator: inc\n"); }
#line 1771 "parser.tab.c"
    break;

  case 51: /* LoopOp: DEC  */
#line 253 "parser.y"
          { printf("Loop operator: dec\n"); }
#line 1777 "parser.tab.c"
    break;

  case 52: /* Condition: ArithmeticExpression RelOp ArithmeticExpression  */
#line 258 "parser.y"
    { printf("Parsed condition\n"); }
#line 1783 "parser.tab.c"
    break;

  case 53: /* RelOp: EQ  */
#line 262 "parser.y"
          { printf("Relational operator: =\n"); }
#line 1789 "parser.tab.c"
    break;

  case 54: /* RelOp: NEQ  */
#line 263 "parser.y"
          { printf("Relational operator: <>\n"); }
#line 1795 "parser.tab.c"
    break;

  case 55: /* RelOp: GT  */
#line 264 "parser.y"
          { printf("Relational operator: >\n"); }
#line 1801 "parser.tab.c"
    break;

  case 56: /* RelOp: LT  */
#line 265 "parser.y"
          { printf("Relational operator: <\n"); }
#line 1807 "parser.tab.c"
    break;

  case 57: /* RelOp: GEQ  */
#line 266 "parser.y"
          { printf("Relational operator: >=\n"); }
#line 1813 "parser.tab.c"
    break;

  case 58: /* RelOp: LEQ  */
#line 267 "parser.y"
          { printf("Relational operator: <=\n"); }
#line 1819 "parser.tab.c"
    break;

  case 59: /* ArithmeticExpression: Term  */
#line 271 "parser.y"
                                              { (yyval.int_val) = (yyvsp[0].int_val); }
#line 1825 "parser.tab.c"
    break;

  case 60: /* ArithmeticExpression: ArithmeticExpression ADD_OP Term  */
#line 272 "parser.y"
                                              { (yyval.int_val) = (yyvsp[-2].int_val) + (yyvsp[0].int_val); printf("Addition\n"); }
#line 1831 "parser.tab.c"
    break;

  case 61: /* ArithmeticExpression: ArithmeticExpression SUB_OP Term  */
#line 273 "parser.y"
                                              { (yyval.int_val) = (yyvsp[-2].int_val) - (yyvsp[0].int_val); printf("Subtraction\n"); }
#line 1837 "parser.tab.c"
    break;

  case 62: /* Term: Factor  */
#line 277 "parser.y"
                                       { (yyval.int_val) = (yyvsp[0].int_val); }
#line 1843 "parser.tab.c"
    break;

  case 63: /* Term: Term MUL_OP Factor  */
#line 278 "parser.y"
                                       { (yyval.int_val) = (yyvsp[-2].int_val) * (yyvsp[0].int_val); printf("Multiplication\n"); }
#line 1849 "parser.tab.c"
    break;

  case 64: /* Term: Term DIV_OP Factor  */
#line 279 "parser.y"
                                       { (yyval.int_val) = (yyvsp[-2].int_val) / (yyvsp[0].int_val); printf("Division\n"); }
#line 1855 "parser.tab.c"
    break;

  case 65: /* Term: Term MOD_OP Factor  */
#line 280 "parser.y"
                                       { (yyval.int_val) = (yyvsp[-2].int_val) % (yyvsp[0].int_val); printf("Modulo\n"); }
#line 1861 "parser.tab.c"
    break;

  case 66: /* Factor: Primary  */
#line 284 "parser.y"
                                       { (yyval.int_val) = (yyvsp[0].int_val); }
#line 1867 "parser.tab.c"
    break;

  case 67: /* Factor: SUB_OP Factor  */
#line 285 "parser.y"
                                       { (yyval.int_val) = -(yyvsp[0].int_val); printf("Unary minus\n"); }
#line 1873 "parser.tab.c"
    break;

  case 68: /* Primary: NUM  */
#line 289 "parser.y"
                                       { (yyval.int_val) = (yyvsp[0].int_val); }
#line 1879 "parser.tab.c"
    break;

  case 69: /* Primary: VarName  */
#line 290 "parser.y"
                                       { (yyval.int_val) = 0; /* Placeholder */ }
#line 1885 "parser.tab.c"
    break;

  case 70: /* Primary: LPAR ArithmeticExpression RPAR  */
#line 291 "parser.y"
                                       { (yyval.int_val) = (yyvsp[-1].int_val); printf("Parenthesized expression\n"); }
#line 1891 "parser.tab.c"
    break;


#line 1895 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 294 "parser.y"


int main() {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        perror("Failed to open input.txt");
        return 1;
    }

    printf("Parsing input...\n");
    int result = yyparse();

    if (result == 0 && syntax_errors == 0) {
        printf("Parsing complete: Input is syntactically correct.\n");
        return 0;
    } else {
        printf("Parsing failed with %d errors.\n", syntax_errors);
        return 1;
    }
}
