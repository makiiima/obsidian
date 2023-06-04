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

    #include <iostream>
    #include <string>
    #include "AST.hpp"
    extern int yylex(void);
    int yyerror(char* s){fprintf(stderr,"%s\n",s);return 0;}
    AST::Program* root;
    using namespace std;
    using namespace AST;

#line 82 "parser.cpp"

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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_INT_CONST = 4,                  /* INT_CONST  */
  YYSYMBOL_DOUBLE_CONST = 5,               /* DOUBLE_CONST  */
  YYSYMBOL_CHAR_CONST = 6,                 /* CHAR_CONST  */
  YYSYMBOL_STRING_CONST = 7,               /* STRING_CONST  */
  YYSYMBOL_LBRACKET = 8,                   /* LBRACKET  */
  YYSYMBOL_RBRACKET = 9,                   /* RBRACKET  */
  YYSYMBOL_LPAREN = 10,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 11,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 12,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 13,                    /* RBRACE  */
  YYSYMBOL_ADD = 14,                       /* ADD  */
  YYSYMBOL_INC = 15,                       /* INC  */
  YYSYMBOL_ADDEQ = 16,                     /* ADDEQ  */
  YYSYMBOL_SUB = 17,                       /* SUB  */
  YYSYMBOL_DEC = 18,                       /* DEC  */
  YYSYMBOL_SUBEQ = 19,                     /* SUBEQ  */
  YYSYMBOL_MUL = 20,                       /* MUL  */
  YYSYMBOL_MULEQ = 21,                     /* MULEQ  */
  YYSYMBOL_DIV = 22,                       /* DIV  */
  YYSYMBOL_DIVEQ = 23,                     /* DIVEQ  */
  YYSYMBOL_MOD = 24,                       /* MOD  */
  YYSYMBOL_MODEQ = 25,                     /* MODEQ  */
  YYSYMBOL_BITAND_ADDRESS = 26,            /* BITAND_ADDRESS  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_BITANDEQ = 28,                  /* BITANDEQ  */
  YYSYMBOL_BITOR = 29,                     /* BITOR  */
  YYSYMBOL_OR = 30,                        /* OR  */
  YYSYMBOL_BITOREQ = 31,                   /* BITOREQ  */
  YYSYMBOL_NOT = 32,                       /* NOT  */
  YYSYMBOL_XOR = 33,                       /* XOR  */
  YYSYMBOL_XOREQ = 34,                     /* XOREQ  */
  YYSYMBOL_LSHIFT = 35,                    /* LSHIFT  */
  YYSYMBOL_LSHIFTEQ = 36,                  /* LSHIFTEQ  */
  YYSYMBOL_RSHIFT = 37,                    /* RSHIFT  */
  YYSYMBOL_RSHIFTEQ = 38,                  /* RSHIFTEQ  */
  YYSYMBOL_GT = 39,                        /* GT  */
  YYSYMBOL_GEQ = 40,                       /* GEQ  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_LEQ = 42,                       /* LEQ  */
  YYSYMBOL_EQ = 43,                        /* EQ  */
  YYSYMBOL_NEQ = 44,                       /* NEQ  */
  YYSYMBOL_DOT = 45,                       /* DOT  */
  YYSYMBOL_MEMBEROF = 46,                  /* MEMBEROF  */
  YYSYMBOL_BITNOT = 47,                    /* BITNOT  */
  YYSYMBOL_SIZEOF = 48,                    /* SIZEOF  */
  YYSYMBOL_QUE = 49,                       /* QUE  */
  YYSYMBOL_COLON = 50,                     /* COLON  */
  YYSYMBOL_SEMI = 51,                      /* SEMI  */
  YYSYMBOL_ASSIGN = 52,                    /* ASSIGN  */
  YYSYMBOL_COMMA = 53,                     /* COMMA  */
  YYSYMBOL_BOOL = 54,                      /* BOOL  */
  YYSYMBOL_INT = 55,                       /* INT  */
  YYSYMBOL_LONG = 56,                      /* LONG  */
  YYSYMBOL_FLOAT = 57,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 58,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 59,                      /* CHAR  */
  YYSYMBOL_UNSIGNED = 60,                  /* UNSIGNED  */
  YYSYMBOL_STRUCT = 61,                    /* STRUCT  */
  YYSYMBOL_UNION = 62,                     /* UNION  */
  YYSYMBOL_ENUM = 63,                      /* ENUM  */
  YYSYMBOL_TRUE = 64,                      /* TRUE  */
  YYSYMBOL_FALSE = 65,                     /* FALSE  */
  YYSYMBOL_VOID = 66,                      /* VOID  */
  YYSYMBOL_CONST = 67,                     /* CONST  */
  YYSYMBOL_IF = 68,                        /* IF  */
  YYSYMBOL_ELSE = 69,                      /* ELSE  */
  YYSYMBOL_FOR = 70,                       /* FOR  */
  YYSYMBOL_WHILE = 71,                     /* WHILE  */
  YYSYMBOL_DO = 72,                        /* DO  */
  YYSYMBOL_BREAK = 73,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 74,                  /* CONTINUE  */
  YYSYMBOL_SWITCH = 75,                    /* SWITCH  */
  YYSYMBOL_CASE = 76,                      /* CASE  */
  YYSYMBOL_DEFAULT = 77,                   /* DEFAULT  */
  YYSYMBOL_RETURN = 78,                    /* RETURN  */
  YYSYMBOL_DEFINE = 79,                    /* DEFINE  */
  YYSYMBOL_BITXOREQ = 80,                  /* BITXOREQ  */
  YYSYMBOL_COL = 81,                       /* COL  */
  YYSYMBOL_BITXOR = 82,                    /* BITXOR  */
  YYSYMBOL_YYACCEPT = 83,                  /* $accept  */
  YYSYMBOL_Program = 84,                   /* Program  */
  YYSYMBOL_DecList = 85,                   /* DecList  */
  YYSYMBOL_FunImp = 86,                    /* FunImp  */
  YYSYMBOL_Block = 87,                     /* Block  */
  YYSYMBOL_ParaList = 88,                  /* ParaList  */
  YYSYMBOL_VarDec = 89,                    /* VarDec  */
  YYSYMBOL_StatList = 90,                  /* StatList  */
  YYSYMBOL_Stat = 91,                      /* Stat  */
  YYSYMBOL_Exp = 92,                       /* Exp  */
  YYSYMBOL_ExpList = 93,                   /* ExpList  */
  YYSYMBOL_Specifier = 94,                 /* Specifier  */
  YYSYMBOL_Constant = 95                   /* Constant  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   962

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  161

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   337


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    86,    86,    89,    91,    92,    95,    96,    99,   103,
     104,   108,   149,   150,   153,   154,   155,   156,   157,   158,
     159,   161,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     199,   200,   202,   203,   204,   205,   213,   214,   216,   217,
     218,   219,   222,   223,   227,   228,   229,   230,   231,   232,
     233,   234,   240,   241,   242,   243,   244,   245
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "INT_CONST", "DOUBLE_CONST", "CHAR_CONST", "STRING_CONST", "LBRACKET",
  "RBRACKET", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "ADD", "INC",
  "ADDEQ", "SUB", "DEC", "SUBEQ", "MUL", "MULEQ", "DIV", "DIVEQ", "MOD",
  "MODEQ", "BITAND_ADDRESS", "AND", "BITANDEQ", "BITOR", "OR", "BITOREQ",
  "NOT", "XOR", "XOREQ", "LSHIFT", "LSHIFTEQ", "RSHIFT", "RSHIFTEQ", "GT",
  "GEQ", "LT", "LEQ", "EQ", "NEQ", "DOT", "MEMBEROF", "BITNOT", "SIZEOF",
  "QUE", "COLON", "SEMI", "ASSIGN", "COMMA", "BOOL", "INT", "LONG",
  "FLOAT", "DOUBLE", "CHAR", "UNSIGNED", "STRUCT", "UNION", "ENUM", "TRUE",
  "FALSE", "VOID", "CONST", "IF", "ELSE", "FOR", "WHILE", "DO", "BREAK",
  "CONTINUE", "SWITCH", "CASE", "DEFAULT", "RETURN", "DEFINE", "BITXOREQ",
  "COL", "BITXOR", "$accept", "Program", "DecList", "FunImp", "Block",
  "ParaList", "VarDec", "StatList", "Stat", "Exp", "ExpList", "Specifier",
  "Constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-55)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -55,     2,   870,   -55,   -55,   -55,   -55,   -55,   -55,   -55,
     -54,   -55,   -55,   -55,     6,   -55,    22,   892,   -55,     0,
      13,     9,     4,     4,   870,   -55,   153,   -55,   -55,    11,
       7,   -55,   -55,   -55,   -55,   868,   868,   868,   868,   868,
     -55,   -55,    10,    12,    23,   -30,   868,   -55,    83,   -55,
     458,    31,   -55,   -55,   868,   218,    -5,    -5,    -5,    -5,
     868,   868,   868,     4,   506,   -55,   -55,   868,   -55,   868,
     868,   -55,   868,   868,   868,   868,   868,   868,   868,   868,
     868,   868,   868,   868,   868,   868,   868,   868,   868,   868,
     868,   868,   868,   868,   868,   868,   868,   -55,   868,   868,
     -25,   719,    16,   -55,   266,   554,   314,   -36,   -55,   169,
     719,   169,   719,    -5,   719,    -5,   719,   719,   719,   877,
     788,   719,   821,   635,   719,   719,    61,   719,    61,   719,
      88,    88,    88,    88,   920,   920,   602,   719,   155,   -55,
     868,     4,   868,     4,    27,   868,   719,     3,   671,   -55,
     868,   755,     4,   868,   362,   -55,   410,    19,     4,   -55,
     -55
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     2,     1,    64,    65,    66,    67,    68,    69,
       0,    71,     4,     3,     0,    70,     0,     0,    11,    71,
       0,     0,     0,     0,     0,    10,     0,     7,     6,     0,
      59,    74,    75,    76,    77,     0,     0,     0,     0,     0,
      72,    73,     0,     0,     0,     0,     0,    21,     0,    13,
       0,     0,    60,     9,     0,     0,    53,    55,    50,    51,
       0,     0,     0,     0,     0,     8,    12,     0,    52,     0,
       0,    54,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    14,     0,     0,
       0,    63,     0,    58,     0,     0,     0,     0,    15,    22,
      40,    23,    41,    24,    42,    25,    43,    26,    44,    27,
      28,    45,    29,    30,    46,    31,    32,    48,    33,    49,
      34,    35,    36,    37,    38,    39,     0,    57,    47,    61,
       0,     0,     0,     0,     0,     0,    62,    16,     0,    19,
       0,    56,     0,     0,     0,    17,     0,     0,     0,    20,
      18
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -55,   -55,   -55,   -55,   -23,   -55,    69,   -55,    26,   -31,
     -55,     1,   -55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    12,    27,    20,    47,    48,    49,    50,
     102,    51,    52
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      28,    15,     3,    14,    55,    56,    57,    58,    59,    16,
      68,    22,    25,    71,    53,    64,    26,    54,    21,    77,
      60,    63,    61,   101,    23,    29,    18,   139,    85,   104,
     105,   106,    17,    62,   100,   144,   109,   150,   110,   111,
     107,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,    24,   137,   138,   140,
     159,    13,   152,    18,    66,    67,    68,     0,    70,    71,
       0,    73,     0,    75,     0,    77,    30,    31,    32,    33,
      34,     0,     0,    35,    85,     0,    65,     0,    36,     0,
       0,    37,    67,    68,     0,    70,    71,     0,    73,   146,
      75,   148,    77,     0,   151,    38,     0,     0,   147,   154,
     149,    85,   156,    86,     0,    88,     0,     0,     0,   155,
      39,     0,     0,     0,     0,   160,     0,     4,     5,     6,
       7,     8,     9,    10,     0,     0,     0,    40,    41,    11,
       0,    42,     0,    43,    44,    45,    30,    31,    32,    33,
      34,    46,     0,    35,     0,     0,     0,     0,    36,    67,
      68,    37,    70,    71,     0,    73,     0,    75,     0,    77,
       0,    79,     0,     0,    68,    38,     0,    71,    85,    73,
      86,    75,    88,    77,    90,    91,    92,    93,    94,    95,
      39,     0,    85,     0,     0,     0,     0,     4,     5,     6,
       7,     8,     9,    10,     0,     0,     0,    40,    41,    11,
       0,    42,     0,    43,    44,    45,     0,     0,     0,   103,
       0,    46,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
       0,    85,     0,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,     0,     0,     0,     0,    96,     0,     0,
      98,     0,     0,     0,     0,     0,     0,   141,     0,     0,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,     0,    85,
      99,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,     0,     0,     0,     0,    96,     0,     0,    98,     0,
       0,     0,     0,     0,     0,   143,     0,     0,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,     0,    85,    99,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,     0,
       0,     0,     0,    96,     0,     0,    98,     0,     0,     0,
       0,     0,     0,   157,     0,     0,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,     0,    85,    99,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,     0,     0,     0,
       0,    96,     0,     0,    98,     0,     0,     0,     0,     0,
       0,   158,     0,     0,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,     0,    85,    99,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,     0,     0,     0,     0,    96,
       0,     0,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
       0,    85,    99,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,     0,     0,     0,     0,    96,     0,    97,
      98,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,     0,    85,
      99,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,     0,     0,     0,     0,    96,     0,   108,    98,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,     0,    85,    99,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,     0,
       0,     0,     0,    96,     0,   142,    98,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,     0,    85,    99,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,     0,     0,    67,
      68,    96,    70,    71,    98,    73,     0,    75,     0,    77,
       0,    79,    80,     0,    82,     0,     0,     0,    85,     0,
      86,     0,    88,     0,    90,    91,    92,    93,    94,    95,
       0,     0,     0,   145,    99,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,     0,    85,     0,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,     0,    99,     0,     0,
      96,     0,   153,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,     0,    85,    99,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,     0,     0,     0,     0,    96,    67,
      68,    98,    70,    71,     0,    73,     0,    75,     0,    77,
       0,    79,    80,     0,    82,    83,     0,     0,    85,     0,
      86,     0,    88,     0,    90,    91,    92,    93,    94,    95,
       0,    99,    67,    68,    96,    70,    71,     0,    73,     0,
      75,     0,    77,     0,    79,     0,     0,    82,     0,     0,
       0,    85,     0,    86,     0,    88,     0,    90,    91,    92,
      93,    94,    95,     0,     0,    67,    68,    99,    70,    71,
       0,    73,     0,    75,     0,    77,     0,    79,     0,     0,
       0,     0,     0,     0,    85,     0,    86,     0,    88,     0,
      90,    91,    92,    93,    94,    95,     0,     0,     0,     0,
      99,    30,    31,    32,    33,    34,     0,     0,    35,     0,
       0,     0,     0,    36,     0,     0,    37,     0,     0,     0,
       0,    67,    68,     0,    70,    71,     0,    73,     0,    75,
      38,    77,     0,    99,     0,     0,     0,     0,     0,     0,
      85,     0,    86,     0,    88,    39,    90,    91,    92,    93,
      94,    95,     0,     0,     4,     5,     6,     7,     8,     9,
      10,     0,    40,    41,    67,    68,    11,    70,    71,     0,
      73,     0,    75,     0,    77,     0,     4,     5,     6,     7,
       8,     9,    10,    85,     0,    86,     0,    88,    19,    90,
      91,    92,    93
};

static const yytype_int16 yycheck[] =
{
      23,    55,     0,     2,    35,    36,    37,    38,    39,     3,
      15,    11,     3,    18,     3,    46,    12,    10,    17,    24,
      10,    51,    10,    54,    11,    24,    51,    11,    33,    60,
      61,    62,    10,    10,     3,    71,    67,    10,    69,    70,
      63,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    53,    98,    99,    53,
      51,     2,    69,    51,    48,    14,    15,    -1,    17,    18,
      -1,    20,    -1,    22,    -1,    24,     3,     4,     5,     6,
       7,    -1,    -1,    10,    33,    -1,    13,    -1,    15,    -1,
      -1,    18,    14,    15,    -1,    17,    18,    -1,    20,   140,
      22,   142,    24,    -1,   145,    32,    -1,    -1,   141,   150,
     143,    33,   153,    35,    -1,    37,    -1,    -1,    -1,   152,
      47,    -1,    -1,    -1,    -1,   158,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    64,    65,    66,
      -1,    68,    -1,    70,    71,    72,     3,     4,     5,     6,
       7,    78,    -1,    10,    -1,    -1,    -1,    -1,    15,    14,
      15,    18,    17,    18,    -1,    20,    -1,    22,    -1,    24,
      -1,    26,    -1,    -1,    15,    32,    -1,    18,    33,    20,
      35,    22,    37,    24,    39,    40,    41,    42,    43,    44,
      47,    -1,    33,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    64,    65,    66,
      -1,    68,    -1,    70,    71,    72,    -1,    -1,    -1,    11,
      -1,    78,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    11,    -1,    -1,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      82,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    49,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    11,    -1,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    82,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    11,    -1,    -1,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    82,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    82,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,    82,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    49,    -1,    51,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      82,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    82,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    -1,    51,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    82,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    14,
      15,    49,    17,    18,    52,    20,    -1,    22,    -1,    24,
      -1,    26,    27,    -1,    29,    -1,    -1,    -1,    33,    -1,
      35,    -1,    37,    -1,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    81,    82,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,    -1,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    82,    -1,    -1,
      49,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    82,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    14,
      15,    52,    17,    18,    -1,    20,    -1,    22,    -1,    24,
      -1,    26,    27,    -1,    29,    30,    -1,    -1,    33,    -1,
      35,    -1,    37,    -1,    39,    40,    41,    42,    43,    44,
      -1,    82,    14,    15,    49,    17,    18,    -1,    20,    -1,
      22,    -1,    24,    -1,    26,    -1,    -1,    29,    -1,    -1,
      -1,    33,    -1,    35,    -1,    37,    -1,    39,    40,    41,
      42,    43,    44,    -1,    -1,    14,    15,    82,    17,    18,
      -1,    20,    -1,    22,    -1,    24,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    35,    -1,    37,    -1,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      82,     3,     4,     5,     6,     7,    -1,    -1,    10,    -1,
      -1,    -1,    -1,    15,    -1,    -1,    18,    -1,    -1,    -1,
      -1,    14,    15,    -1,    17,    18,    -1,    20,    -1,    22,
      32,    24,    -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    -1,    35,    -1,    37,    47,    39,    40,    41,    42,
      43,    44,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    -1,    64,    65,    14,    15,    66,    17,    18,    -1,
      20,    -1,    22,    -1,    24,    -1,    54,    55,    56,    57,
      58,    59,    60,    33,    -1,    35,    -1,    37,    66,    39,
      40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    84,    85,     0,    54,    55,    56,    57,    58,    59,
      60,    66,    86,    89,    94,    55,     3,    10,    51,    66,
      88,    94,    11,    11,    53,     3,    12,    87,    87,    94,
       3,     4,     5,     6,     7,    10,    15,    18,    32,    47,
      64,    65,    68,    70,    71,    72,    78,    89,    90,    91,
      92,    94,    95,     3,    10,    92,    92,    92,    92,    92,
      10,    10,    10,    51,    92,    13,    91,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    33,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    49,    51,    52,    82,
       3,    92,    93,    11,    92,    92,    92,    87,    51,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    11,
      53,    11,    51,    11,    71,    81,    92,    87,    92,    87,
      10,    92,    69,    51,    92,    87,    92,    11,    11,    51,
      87
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    83,    84,    85,    85,    85,    86,    86,    87,    88,
      88,    89,    90,    90,    91,    91,    91,    91,    91,    91,
      91,    91,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    93,    93,    94,    94,    94,    94,    94,    94,
      94,    94,    95,    95,    95,    95,    95,    95
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     0,     6,     6,     3,     4,
       2,     3,     2,     1,     2,     3,     5,     7,     9,     5,
       8,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     2,     2,     2,     5,     3,     3,     1,
       1,     4,     3,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1
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
  case 2: /* Program: DecList  */
#line 86 "parser.y"
                                                                                {root = (yyval.program) = new Program((yyvsp[0].declist));}
#line 1433 "parser.cpp"
    break;

  case 3: /* DecList: DecList VarDec  */
#line 89 "parser.y"
                                                                                {(yyval.declist) = (yyvsp[-1].declist); (yyval.declist)->adddefine((yyvsp[0].vardec));}
#line 1439 "parser.cpp"
    break;

  case 4: /* DecList: DecList FunImp  */
#line 91 "parser.y"
                                                                                {(yyval.declist) = (yyvsp[-1].declist); (yyval.declist)->adddefine((yyvsp[0].funimp));}
#line 1445 "parser.cpp"
    break;

  case 5: /* DecList: %empty  */
#line 92 "parser.y"
                                                                                {(yyval.declist) = new Define_List();}
#line 1451 "parser.cpp"
    break;

  case 6: /* FunImp: Specifier IDENTIFIER LPAREN ParaList RPAREN Block  */
#line 95 "parser.y"
                                                                                {(yyval.funimp) = new Fun_Imp((yyvsp[-5].specifier), *(yyvsp[-4].id), (yyvsp[-2].paralist), (yyvsp[0].block));}
#line 1457 "parser.cpp"
    break;

  case 7: /* FunImp: Specifier IDENTIFIER LPAREN VOID RPAREN Block  */
#line 96 "parser.y"
                                                                                {(yyval.funimp) = new Fun_Imp((yyvsp[-5].specifier), *(yyvsp[-4].id), (yyvsp[0].block));}
#line 1463 "parser.cpp"
    break;

  case 8: /* Block: LBRACE StatList RBRACE  */
#line 99 "parser.y"
                                                                                {(yyval.block) = new Block((yyvsp[-1].statlist));}
#line 1469 "parser.cpp"
    break;

  case 9: /* ParaList: ParaList COMMA Specifier IDENTIFIER  */
#line 103 "parser.y"
                                                                                {(yyval.paralist) = (yyvsp[-3].paralist); (yyval.paralist)->addpara((yyvsp[-1].specifier), *(yyvsp[0].id));}
#line 1475 "parser.cpp"
    break;

  case 10: /* ParaList: Specifier IDENTIFIER  */
#line 104 "parser.y"
                                                                                {(yyval.paralist) = new Para_List(); (yyval.paralist)->addpara((yyvsp[-1].specifier), *(yyvsp[0].id));}
#line 1481 "parser.cpp"
    break;

  case 11: /* VarDec: Specifier IDENTIFIER SEMI  */
#line 108 "parser.y"
                                                                                   {(yyval.vardec) = new Var_Dec((yyvsp[-2].specifier), *(yyvsp[-1].id));}
#line 1487 "parser.cpp"
    break;

  case 12: /* StatList: StatList Stat  */
#line 149 "parser.y"
                                                                                {(yyval.statlist) = (yyvsp[-1].statlist); (yyval.statlist)->addstat((yyvsp[0].stat));}
#line 1493 "parser.cpp"
    break;

  case 13: /* StatList: Stat  */
#line 150 "parser.y"
                                                                                {(yyval.statlist) = new Stat_List(); (yyval.statlist)->addstat((yyvsp[0].stat));}
#line 1499 "parser.cpp"
    break;

  case 14: /* Stat: Exp SEMI  */
#line 153 "parser.y"
                                                                                {(yyval.stat) = (yyvsp[-1].exp);}
#line 1505 "parser.cpp"
    break;

  case 15: /* Stat: RETURN Exp SEMI  */
#line 154 "parser.y"
                                                                                {(yyval.stat) = new Stat_Return((yyvsp[-1].exp));}
#line 1511 "parser.cpp"
    break;

  case 16: /* Stat: IF LPAREN Exp RPAREN Block  */
#line 155 "parser.y"
                                                                                {(yyval.stat) = new Stat_If((yyvsp[-2].exp), (yyvsp[0].block));}
#line 1517 "parser.cpp"
    break;

  case 17: /* Stat: IF LPAREN Exp RPAREN Block ELSE Block  */
#line 156 "parser.y"
                                                                                {(yyval.stat) = new Stat_IfElse((yyvsp[-4].exp), (yyvsp[-2].block), (yyvsp[0].block));}
#line 1523 "parser.cpp"
    break;

  case 18: /* Stat: FOR LPAREN Exp SEMI Exp SEMI Exp RPAREN Block  */
#line 157 "parser.y"
                                                                                {(yyval.stat) = new Stat_For((yyvsp[-6].exp), (yyvsp[-4].exp), (yyvsp[-2].exp), (yyvsp[0].block));}
#line 1529 "parser.cpp"
    break;

  case 19: /* Stat: WHILE LPAREN Exp RPAREN Block  */
#line 158 "parser.y"
                                                                                {(yyval.stat) = new Stat_While((yyvsp[-2].exp), (yyvsp[0].block));}
#line 1535 "parser.cpp"
    break;

  case 20: /* Stat: DO SEMI Block WHILE LPAREN Exp RPAREN SEMI  */
#line 159 "parser.y"
                                                                                {(yyval.stat) = new Stat_DoWhile((yyvsp[-2].exp), (yyvsp[-5].block));}
#line 1541 "parser.cpp"
    break;

  case 21: /* Stat: VarDec  */
#line 161 "parser.y"
                                                                                {(yyval.stat) = (yyvsp[0].vardec);}
#line 1547 "parser.cpp"
    break;

  case 22: /* Exp: Exp ADD Exp  */
#line 169 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("ADD", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1553 "parser.cpp"
    break;

  case 23: /* Exp: Exp SUB Exp  */
#line 170 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("SUB", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1559 "parser.cpp"
    break;

  case 24: /* Exp: Exp MUL Exp  */
#line 171 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("MUL", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1565 "parser.cpp"
    break;

  case 25: /* Exp: Exp DIV Exp  */
#line 172 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("DIV", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1571 "parser.cpp"
    break;

  case 26: /* Exp: Exp MOD Exp  */
#line 173 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("MOD", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1577 "parser.cpp"
    break;

  case 27: /* Exp: Exp BITAND_ADDRESS Exp  */
#line 174 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("BITAND_ADDRESS", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1583 "parser.cpp"
    break;

  case 28: /* Exp: Exp AND Exp  */
#line 175 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("AND", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1589 "parser.cpp"
    break;

  case 29: /* Exp: Exp BITOR Exp  */
#line 176 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("BITOR", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1595 "parser.cpp"
    break;

  case 30: /* Exp: Exp OR Exp  */
#line 177 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("OR", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1601 "parser.cpp"
    break;

  case 31: /* Exp: Exp XOR Exp  */
#line 178 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("XOR", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1607 "parser.cpp"
    break;

  case 32: /* Exp: Exp LSHIFT Exp  */
#line 179 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("LSHIFT", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1613 "parser.cpp"
    break;

  case 33: /* Exp: Exp RSHIFT Exp  */
#line 180 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("RSHIFT", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1619 "parser.cpp"
    break;

  case 34: /* Exp: Exp GT Exp  */
#line 181 "parser.y"
                                                                                                                        {(yyval.exp) = new Exp_Bin("GT", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1625 "parser.cpp"
    break;

  case 35: /* Exp: Exp GEQ Exp  */
#line 182 "parser.y"
                                                                                                                        {(yyval.exp) = new Exp_Bin("GEQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1631 "parser.cpp"
    break;

  case 36: /* Exp: Exp LT Exp  */
#line 183 "parser.y"
                                                                                                                        {(yyval.exp) = new Exp_Bin("LT", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1637 "parser.cpp"
    break;

  case 37: /* Exp: Exp LEQ Exp  */
#line 184 "parser.y"
                                                                                                                        {(yyval.exp) = new Exp_Bin("LEQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1643 "parser.cpp"
    break;

  case 38: /* Exp: Exp EQ Exp  */
#line 185 "parser.y"
                                                                                                                        {(yyval.exp) = new Exp_Bin("EQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1649 "parser.cpp"
    break;

  case 39: /* Exp: Exp NEQ Exp  */
#line 186 "parser.y"
                                                                                                                        {(yyval.exp) = new Exp_Bin("NEQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1655 "parser.cpp"
    break;

  case 40: /* Exp: Exp ADDEQ Exp  */
#line 188 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("ADDEQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1661 "parser.cpp"
    break;

  case 41: /* Exp: Exp SUBEQ Exp  */
#line 189 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("SUBEQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1667 "parser.cpp"
    break;

  case 42: /* Exp: Exp MULEQ Exp  */
#line 190 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("MULEQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1673 "parser.cpp"
    break;

  case 43: /* Exp: Exp DIVEQ Exp  */
#line 191 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("DIVEQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1679 "parser.cpp"
    break;

  case 44: /* Exp: Exp MODEQ Exp  */
#line 192 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("MODEQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1685 "parser.cpp"
    break;

  case 45: /* Exp: Exp BITANDEQ Exp  */
#line 193 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("BITANDEQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1691 "parser.cpp"
    break;

  case 46: /* Exp: Exp BITOREQ Exp  */
#line 194 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("BITOREQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1697 "parser.cpp"
    break;

  case 47: /* Exp: Exp BITXOR Exp  */
#line 195 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("BITXOREQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1703 "parser.cpp"
    break;

  case 48: /* Exp: Exp LSHIFTEQ Exp  */
#line 196 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("LSHIFTEQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1709 "parser.cpp"
    break;

  case 49: /* Exp: Exp RSHIFTEQ Exp  */
#line 197 "parser.y"
                                                                                {(yyval.exp) = new Exp_Bin("RSHIFTEQ", (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1715 "parser.cpp"
    break;

  case 50: /* Exp: NOT Exp  */
#line 199 "parser.y"
                                                                                {(yyval.exp) = new Exp_Uni("NOT", (yyvsp[0].exp));}
#line 1721 "parser.cpp"
    break;

  case 51: /* Exp: BITNOT Exp  */
#line 200 "parser.y"
                                                                                {(yyval.exp) = new Exp_Uni("BITNOT", (yyvsp[0].exp));}
#line 1727 "parser.cpp"
    break;

  case 52: /* Exp: Exp INC  */
#line 202 "parser.y"
                                                                                {(yyval.exp) = new Exp_Uni("POSTFIX_INC", (yyvsp[-1].exp));}
#line 1733 "parser.cpp"
    break;

  case 53: /* Exp: INC Exp  */
#line 203 "parser.y"
                                                                                {(yyval.exp) = new Exp_Uni("PREFIX_INC", (yyvsp[0].exp));}
#line 1739 "parser.cpp"
    break;

  case 54: /* Exp: Exp DEC  */
#line 204 "parser.y"
                                                                                {(yyval.exp) = new Exp_Uni("POSTFIX_DEC", (yyvsp[-1].exp));}
#line 1745 "parser.cpp"
    break;

  case 55: /* Exp: DEC Exp  */
#line 205 "parser.y"
                                                                                {(yyval.exp) = new Exp_Uni("PREFIX_DEC", (yyvsp[0].exp));}
#line 1751 "parser.cpp"
    break;

  case 56: /* Exp: Exp QUE Exp COL Exp  */
#line 213 "parser.y"
                                                                                {(yyval.exp) = new Exp_Con((yyvsp[-4].exp), (yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1757 "parser.cpp"
    break;

  case 57: /* Exp: Exp ASSIGN Exp  */
#line 214 "parser.y"
                                                                                {(yyval.exp) = new Exp_Assign((yyvsp[-2].exp), (yyvsp[0].exp));}
#line 1763 "parser.cpp"
    break;

  case 58: /* Exp: LPAREN Exp RPAREN  */
#line 216 "parser.y"
                                                                                {(yyval.exp) = (yyvsp[-1].exp);}
#line 1769 "parser.cpp"
    break;

  case 59: /* Exp: IDENTIFIER  */
#line 217 "parser.y"
                                                                                {(yyval.exp) = new Exp_ID(*(yyvsp[0].id));}
#line 1775 "parser.cpp"
    break;

  case 60: /* Exp: Constant  */
#line 218 "parser.y"
                                                                                {(yyval.exp) = (yyvsp[0].constant);}
#line 1781 "parser.cpp"
    break;

  case 61: /* Exp: IDENTIFIER LPAREN ExpList RPAREN  */
#line 219 "parser.y"
                                                                                {(yyval.exp) = new Exp_Func(*(yyvsp[-3].id), (yyvsp[-1].explist));}
#line 1787 "parser.cpp"
    break;

  case 62: /* ExpList: ExpList COMMA Exp  */
#line 222 "parser.y"
                                                                                {(yyval.explist) = (yyvsp[-2].explist); (yyval.explist)->addexp((yyvsp[0].exp));}
#line 1793 "parser.cpp"
    break;

  case 63: /* ExpList: Exp  */
#line 223 "parser.y"
                                                                                {(yyval.explist) = new Exp_List(); (yyval.explist)->addexp((yyvsp[0].exp));}
#line 1799 "parser.cpp"
    break;

  case 64: /* Specifier: BOOL  */
#line 227 "parser.y"
                                                                                {(yyval.specifier) = new Specifier("BOOL");}
#line 1805 "parser.cpp"
    break;

  case 65: /* Specifier: INT  */
#line 228 "parser.y"
                                                                                {(yyval.specifier) = new Specifier("INT");}
#line 1811 "parser.cpp"
    break;

  case 66: /* Specifier: LONG  */
#line 229 "parser.y"
                                                                                {(yyval.specifier) = new Specifier("LONG");}
#line 1817 "parser.cpp"
    break;

  case 67: /* Specifier: FLOAT  */
#line 230 "parser.y"
                                                                                {(yyval.specifier) = new Specifier("FLOAT");}
#line 1823 "parser.cpp"
    break;

  case 68: /* Specifier: DOUBLE  */
#line 231 "parser.y"
                                                                                {(yyval.specifier) = new Specifier("DOUBLE");}
#line 1829 "parser.cpp"
    break;

  case 69: /* Specifier: CHAR  */
#line 232 "parser.y"
                                                                                {(yyval.specifier) = new Specifier("CHAR");}
#line 1835 "parser.cpp"
    break;

  case 70: /* Specifier: UNSIGNED INT  */
#line 233 "parser.y"
                                                                                {(yyval.specifier) = new Specifier("UNSIGNED INT");}
#line 1841 "parser.cpp"
    break;

  case 71: /* Specifier: VOID  */
#line 234 "parser.y"
                                                                                {(yyval.specifier) = new Specifier("VOID");}
#line 1847 "parser.cpp"
    break;

  case 72: /* Constant: TRUE  */
#line 240 "parser.y"
                                                                                {(yyval.constant) = new Constant_Bool(true);}
#line 1853 "parser.cpp"
    break;

  case 73: /* Constant: FALSE  */
#line 241 "parser.y"
                                                                                {(yyval.constant) = new Constant_Bool(false);}
#line 1859 "parser.cpp"
    break;

  case 74: /* Constant: INT_CONST  */
#line 242 "parser.y"
                                                                                {(yyval.constant) = new Constant_Int((yyvsp[0].intval));}
#line 1865 "parser.cpp"
    break;

  case 75: /* Constant: DOUBLE_CONST  */
#line 243 "parser.y"
                                                                                {(yyval.constant) = new Constant_Double((yyvsp[0].doubleval));}
#line 1871 "parser.cpp"
    break;

  case 76: /* Constant: CHAR_CONST  */
#line 244 "parser.y"
                                                                                {(yyval.constant) = new Constant_Char((yyvsp[0].charval));}
#line 1877 "parser.cpp"
    break;

  case 77: /* Constant: STRING_CONST  */
#line 245 "parser.y"
                                                                                {(yyval.constant) = new Constant_String(*(yyvsp[0].stringval));}
#line 1883 "parser.cpp"
    break;


#line 1887 "parser.cpp"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 248 "parser.y"

