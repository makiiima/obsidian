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

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
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
    IDENTIFIER = 258,              /* IDENTIFIER  */
    INT_CONST = 259,               /* INT_CONST  */
    DOUBLE_CONST = 260,            /* DOUBLE_CONST  */
    CHAR_CONST = 261,              /* CHAR_CONST  */
    STRING_CONST = 262,            /* STRING_CONST  */
    LBRACKET = 263,                /* LBRACKET  */
    RBRACKET = 264,                /* RBRACKET  */
    LPAREN = 265,                  /* LPAREN  */
    RPAREN = 266,                  /* RPAREN  */
    LBRACE = 267,                  /* LBRACE  */
    RBRACE = 268,                  /* RBRACE  */
    ADD = 269,                     /* ADD  */
    INC = 270,                     /* INC  */
    ADDEQ = 271,                   /* ADDEQ  */
    SUB = 272,                     /* SUB  */
    DEC = 273,                     /* DEC  */
    SUBEQ = 274,                   /* SUBEQ  */
    MUL = 275,                     /* MUL  */
    MULEQ = 276,                   /* MULEQ  */
    DIV = 277,                     /* DIV  */
    DIVEQ = 278,                   /* DIVEQ  */
    MOD = 279,                     /* MOD  */
    MODEQ = 280,                   /* MODEQ  */
    BITAND_ADDRESS = 281,          /* BITAND_ADDRESS  */
    AND = 282,                     /* AND  */
    BITANDEQ = 283,                /* BITANDEQ  */
    BITOR = 284,                   /* BITOR  */
    OR = 285,                      /* OR  */
    BITOREQ = 286,                 /* BITOREQ  */
    NOT = 287,                     /* NOT  */
    XOR = 288,                     /* XOR  */
    XOREQ = 289,                   /* XOREQ  */
    LSHIFT = 290,                  /* LSHIFT  */
    LSHIFTEQ = 291,                /* LSHIFTEQ  */
    RSHIFT = 292,                  /* RSHIFT  */
    RSHIFTEQ = 293,                /* RSHIFTEQ  */
    GT = 294,                      /* GT  */
    GEQ = 295,                     /* GEQ  */
    LT = 296,                      /* LT  */
    LEQ = 297,                     /* LEQ  */
    EQ = 298,                      /* EQ  */
    NEQ = 299,                     /* NEQ  */
    DOT = 300,                     /* DOT  */
    MEMBEROF = 301,                /* MEMBEROF  */
    BITNOT = 302,                  /* BITNOT  */
    SIZEOF = 303,                  /* SIZEOF  */
    QUE = 304,                     /* QUE  */
    COLON = 305,                   /* COLON  */
    SEMI = 306,                    /* SEMI  */
    ASSIGN = 307,                  /* ASSIGN  */
    COMMA = 308,                   /* COMMA  */
    BOOL = 309,                    /* BOOL  */
    INT = 310,                     /* INT  */
    LONG = 311,                    /* LONG  */
    FLOAT = 312,                   /* FLOAT  */
    DOUBLE = 313,                  /* DOUBLE  */
    CHAR = 314,                    /* CHAR  */
    UNSIGNED = 315,                /* UNSIGNED  */
    STRUCT = 316,                  /* STRUCT  */
    UNION = 317,                   /* UNION  */
    ENUM = 318,                    /* ENUM  */
    TRUE = 319,                    /* TRUE  */
    FALSE = 320,                   /* FALSE  */
    VOID = 321,                    /* VOID  */
    CONST = 322,                   /* CONST  */
    IF = 323,                      /* IF  */
    ELSE = 324,                    /* ELSE  */
    FOR = 325,                     /* FOR  */
    WHILE = 326,                   /* WHILE  */
    DO = 327,                      /* DO  */
    BREAK = 328,                   /* BREAK  */
    CONTINUE = 329,                /* CONTINUE  */
    SWITCH = 330,                  /* SWITCH  */
    CASE = 331,                    /* CASE  */
    DEFAULT = 332,                 /* DEFAULT  */
    RETURN = 333,                  /* RETURN  */
    DEFINE = 334,                  /* DEFINE  */
    BITXOREQ = 335,                /* BITXOREQ  */
    COL = 336,                     /* COL  */
    BITXOR = 337                   /* BITXOR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "parser.y"

    std::string* id;
    int intval;
    double doubleval;
    char charval;
    std::string* stringval;
    AST::Program *program;
    AST::Define_List *declist;
    AST::Fun_Imp *funimp;
    AST::Block *block;
    AST::Para_List *paralist;
    AST::Var_Dec *vardec;
//    Var_List *varlist;
//    Var_Init *varinit;
    AST::Stat_List *statlist;
    AST::Stat *stat;
    AST::Exp *exp;
    AST::Exp_List *explist;
    AST::Specifier *specifier;
    AST::Constant *constant;

#line 168 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
