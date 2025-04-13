/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    BEGIN_K = 258,                 /* BEGIN_K  */
    END_K = 259,                   /* END_K  */
    PROGRAM = 260,                 /* PROGRAM  */
    COLON = 261,                   /* COLON  */
    SEMICOLON = 262,               /* SEMICOLON  */
    COMMA = 263,                   /* COMMA  */
    LPAR = 264,                    /* LPAR  */
    RPAR = 265,                    /* RPAR  */
    LBRACK = 266,                  /* LBRACK  */
    RBRACK = 267,                  /* RBRACK  */
    INT = 268,                     /* INT  */
    CHAR = 269,                    /* CHAR  */
    PRINT = 270,                   /* PRINT  */
    SCAN = 271,                    /* SCAN  */
    VARDECL = 272,                 /* VARDECL  */
    INC = 273,                     /* INC  */
    DEC = 274,                     /* DEC  */
    ADD_OP = 275,                  /* ADD_OP  */
    SUB_OP = 276,                  /* SUB_OP  */
    MUL_OP = 277,                  /* MUL_OP  */
    DIV_OP = 278,                  /* DIV_OP  */
    MOD_OP = 279,                  /* MOD_OP  */
    ID = 280,                      /* ID  */
    STRING = 281,                  /* STRING  */
    CHARACTER = 282,               /* CHARACTER  */
    FORMAT_STRING = 283,           /* FORMAT_STRING  */
    INPUT_STRING = 284,            /* INPUT_STRING  */
    NUMBER = 285,                  /* NUMBER  */
    IF_K = 286,                    /* IF_K  */
    ELSE_K = 287,                  /* ELSE_K  */
    WHILE_K = 288,                 /* WHILE_K  */
    FOR_K = 289,                   /* FOR_K  */
    TO_K = 290,                    /* TO_K  */
    DO_K = 291,                    /* DO_K  */
    EQ = 292,                      /* EQ  */
    NEQ = 293,                     /* NEQ  */
    GT = 294,                      /* GT  */
    LT = 295,                      /* LT  */
    GEQ = 296,                     /* GEQ  */
    LEQ = 297,                     /* LEQ  */
    ASSIGN = 298,                  /* ASSIGN  */
    ADD_ASSIGN = 299,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 300,              /* SUB_ASSIGN  */
    MUL_ASSIGN = 301,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 302,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 303,              /* MOD_ASSIGN  */
    UMINUS = 304,                  /* UMINUS  */
    IF_PREC = 305                  /* IF_PREC  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "parser.y"

    int int_val;
    char* str_val;

#line 119 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
