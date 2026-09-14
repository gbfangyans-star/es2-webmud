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
#line 1 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"

#ifdef	HAVE_CONFIG_H
#include <config.h>
#endif	/* HAVE_CONFIG_H */

#include "src/std.h"
#include "rc.h"
#include "scratchpad.h"
#include "src/simul_efun.h"
#include "lpc/object.h"
#include "lpc/otable.h"
#include "lpc/program/parse_trees.h"
#include "lpc/program/generate.h"

#include "lpc/include/function.h"
#include "lpc/include/runtime_config.h"

/*
 * This is the grammar definition of LPC, and its parse tree generator.
 */

/* down to one global :) 
   bits:
      SWITCH_CONTEXT     - we're inside a switch
      LOOP_CONTEXT       - we're inside a loop
      SWITCH_STRINGS     - a string case has been found
      SWITCH_NUMBERS     - a non-zero numeric case has been found
      SWITCH_RANGES      - a range has been found
      SWITCH_DEFAULT     - a default has been found
 */
int64_t context;

/*
 * bison & yacc don't prototype this in y.tab.h
 */
int yyparse(void);


#line 110 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"

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

#include "grammar.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_L_NUMBER = 3,                   /* L_NUMBER  */
  YYSYMBOL_L_REAL = 4,                     /* L_REAL  */
  YYSYMBOL_L_STRING = 5,                   /* L_STRING  */
  YYSYMBOL_L_BASIC_TYPE = 6,               /* L_BASIC_TYPE  */
  YYSYMBOL_L_TYPE_MODIFIER = 7,            /* L_TYPE_MODIFIER  */
  YYSYMBOL_L_DEFINED_NAME = 8,             /* L_DEFINED_NAME  */
  YYSYMBOL_L_IDENTIFIER = 9,               /* L_IDENTIFIER  */
  YYSYMBOL_L_EFUN = 10,                    /* L_EFUN  */
  YYSYMBOL_L_INC = 11,                     /* L_INC  */
  YYSYMBOL_L_DEC = 12,                     /* L_DEC  */
  YYSYMBOL_L_ASSIGN = 13,                  /* L_ASSIGN  */
  YYSYMBOL_L_LAND = 14,                    /* L_LAND  */
  YYSYMBOL_L_LOR = 15,                     /* L_LOR  */
  YYSYMBOL_L_LSH = 16,                     /* L_LSH  */
  YYSYMBOL_L_RSH = 17,                     /* L_RSH  */
  YYSYMBOL_L_ORDER = 18,                   /* L_ORDER  */
  YYSYMBOL_L_NOT = 19,                     /* L_NOT  */
  YYSYMBOL_L_IF = 20,                      /* L_IF  */
  YYSYMBOL_L_ELSE = 21,                    /* L_ELSE  */
  YYSYMBOL_L_SWITCH = 22,                  /* L_SWITCH  */
  YYSYMBOL_L_CASE = 23,                    /* L_CASE  */
  YYSYMBOL_L_DEFAULT = 24,                 /* L_DEFAULT  */
  YYSYMBOL_L_RANGE = 25,                   /* L_RANGE  */
  YYSYMBOL_L_DOT = 26,                     /* L_DOT  */
  YYSYMBOL_L_DOT_DOT_DOT = 27,             /* L_DOT_DOT_DOT  */
  YYSYMBOL_L_WHILE = 28,                   /* L_WHILE  */
  YYSYMBOL_L_DO = 29,                      /* L_DO  */
  YYSYMBOL_L_FOR = 30,                     /* L_FOR  */
  YYSYMBOL_L_FOREACH = 31,                 /* L_FOREACH  */
  YYSYMBOL_L_IN = 32,                      /* L_IN  */
  YYSYMBOL_L_BREAK = 33,                   /* L_BREAK  */
  YYSYMBOL_L_CONTINUE = 34,                /* L_CONTINUE  */
  YYSYMBOL_L_RETURN = 35,                  /* L_RETURN  */
  YYSYMBOL_L_ARROW = 36,                   /* L_ARROW  */
  YYSYMBOL_L_INHERIT = 37,                 /* L_INHERIT  */
  YYSYMBOL_L_COLON_COLON = 38,             /* L_COLON_COLON  */
  YYSYMBOL_L_ARRAY_OPEN = 39,              /* L_ARRAY_OPEN  */
  YYSYMBOL_L_MAPPING_OPEN = 40,            /* L_MAPPING_OPEN  */
  YYSYMBOL_L_FUNCTION_OPEN = 41,           /* L_FUNCTION_OPEN  */
  YYSYMBOL_L_NEW_FUNCTION_OPEN = 42,       /* L_NEW_FUNCTION_OPEN  */
  YYSYMBOL_L_SSCANF = 43,                  /* L_SSCANF  */
  YYSYMBOL_L_CATCH = 44,                   /* L_CATCH  */
  YYSYMBOL_L_PARSE_COMMAND = 45,           /* L_PARSE_COMMAND  */
  YYSYMBOL_L_TIME_EXPRESSION = 46,         /* L_TIME_EXPRESSION  */
  YYSYMBOL_L_CLASS = 47,                   /* L_CLASS  */
  YYSYMBOL_L_NEW = 48,                     /* L_NEW  */
  YYSYMBOL_L_PARAMETER = 49,               /* L_PARAMETER  */
  YYSYMBOL_LOWER_THAN_ELSE = 50,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_51_ = 51,                       /* '?'  */
  YYSYMBOL_52_ = 52,                       /* '|'  */
  YYSYMBOL_53_ = 53,                       /* '^'  */
  YYSYMBOL_54_ = 54,                       /* '&'  */
  YYSYMBOL_L_EQ = 55,                      /* L_EQ  */
  YYSYMBOL_L_NE = 56,                      /* L_NE  */
  YYSYMBOL_57_ = 57,                       /* '<'  */
  YYSYMBOL_58_ = 58,                       /* '+'  */
  YYSYMBOL_59_ = 59,                       /* '-'  */
  YYSYMBOL_60_ = 60,                       /* '*'  */
  YYSYMBOL_61_ = 61,                       /* '%'  */
  YYSYMBOL_62_ = 62,                       /* '/'  */
  YYSYMBOL_63_ = 63,                       /* '~'  */
  YYSYMBOL_64_ = 64,                       /* ';'  */
  YYSYMBOL_65_ = 65,                       /* '('  */
  YYSYMBOL_66_ = 66,                       /* ')'  */
  YYSYMBOL_67_ = 67,                       /* ':'  */
  YYSYMBOL_68_ = 68,                       /* ','  */
  YYSYMBOL_69_ = 69,                       /* '{'  */
  YYSYMBOL_70_ = 70,                       /* '}'  */
  YYSYMBOL_71_ = 71,                       /* '$'  */
  YYSYMBOL_72_ = 72,                       /* '['  */
  YYSYMBOL_73_ = 73,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_all = 75,                       /* all  */
  YYSYMBOL_program = 76,                   /* program  */
  YYSYMBOL_possible_semi_colon = 77,       /* possible_semi_colon  */
  YYSYMBOL_inheritance = 78,               /* inheritance  */
  YYSYMBOL_real = 79,                      /* real  */
  YYSYMBOL_number = 80,                    /* number  */
  YYSYMBOL_optional_star = 81,             /* optional_star  */
  YYSYMBOL_block_or_semi = 82,             /* block_or_semi  */
  YYSYMBOL_identifier = 83,                /* identifier  */
  YYSYMBOL_def = 84,                       /* def  */
  YYSYMBOL_85_1 = 85,                      /* $@1  */
  YYSYMBOL_86_2 = 86,                      /* @2  */
  YYSYMBOL_modifier_change = 87,           /* modifier_change  */
  YYSYMBOL_member_name = 88,               /* member_name  */
  YYSYMBOL_member_name_list = 89,          /* member_name_list  */
  YYSYMBOL_member_list = 90,               /* member_list  */
  YYSYMBOL_type_decl = 91,                 /* type_decl  */
  YYSYMBOL_92_3 = 92,                      /* @3  */
  YYSYMBOL_new_local_name = 93,            /* new_local_name  */
  YYSYMBOL_atomic_type = 94,               /* atomic_type  */
  YYSYMBOL_basic_type = 95,                /* basic_type  */
  YYSYMBOL_new_arg = 96,                   /* new_arg  */
  YYSYMBOL_argument = 97,                  /* argument  */
  YYSYMBOL_argument_list = 98,             /* argument_list  */
  YYSYMBOL_type_modifier_list = 99,        /* type_modifier_list  */
  YYSYMBOL_type = 100,                     /* type  */
  YYSYMBOL_cast = 101,                     /* cast  */
  YYSYMBOL_opt_basic_type = 102,           /* opt_basic_type  */
  YYSYMBOL_name_list = 103,                /* name_list  */
  YYSYMBOL_new_name = 104,                 /* new_name  */
  YYSYMBOL_block = 105,                    /* block  */
  YYSYMBOL_block_items = 106,              /* block_items  */
  YYSYMBOL_block_item = 107,               /* block_item  */
  YYSYMBOL_local_declaration_stmt = 108,   /* local_declaration_stmt  */
  YYSYMBOL_109_4 = 109,                    /* $@4  */
  YYSYMBOL_decl_block = 110,               /* decl_block  */
  YYSYMBOL_local_declarations = 111,       /* local_declarations  */
  YYSYMBOL_new_local_def = 112,            /* new_local_def  */
  YYSYMBOL_single_new_local_def = 113,     /* single_new_local_def  */
  YYSYMBOL_single_new_local_def_with_init = 114, /* single_new_local_def_with_init  */
  YYSYMBOL_local_name_list = 115,          /* local_name_list  */
  YYSYMBOL_statement = 116,                /* statement  */
  YYSYMBOL_while = 117,                    /* while  */
  YYSYMBOL_118_5 = 118,                    /* $@5  */
  YYSYMBOL_do = 119,                       /* do  */
  YYSYMBOL_120_6 = 120,                    /* $@6  */
  YYSYMBOL_for = 121,                      /* for  */
  YYSYMBOL_122_7 = 122,                    /* $@7  */
  YYSYMBOL_foreach_var = 123,              /* foreach_var  */
  YYSYMBOL_foreach_vars = 124,             /* foreach_vars  */
  YYSYMBOL_foreach = 125,                  /* foreach  */
  YYSYMBOL_126_8 = 126,                    /* $@8  */
  YYSYMBOL_for_expr = 127,                 /* for_expr  */
  YYSYMBOL_first_for_expr = 128,           /* first_for_expr  */
  YYSYMBOL_switch = 129,                   /* switch  */
  YYSYMBOL_130_9 = 130,                    /* $@9  */
  YYSYMBOL_switch_block = 131,             /* switch_block  */
  YYSYMBOL_case = 132,                     /* case  */
  YYSYMBOL_case_label = 133,               /* case_label  */
  YYSYMBOL_constant = 134,                 /* constant  */
  YYSYMBOL_comma_expr = 135,               /* comma_expr  */
  YYSYMBOL_expr0 = 136,                    /* expr0  */
  YYSYMBOL_return = 137,                   /* return  */
  YYSYMBOL_expr_list = 138,                /* expr_list  */
  YYSYMBOL_expr_list_node = 139,           /* expr_list_node  */
  YYSYMBOL_expr_list2 = 140,               /* expr_list2  */
  YYSYMBOL_expr_list3 = 141,               /* expr_list3  */
  YYSYMBOL_expr_list4 = 142,               /* expr_list4  */
  YYSYMBOL_assoc_pair = 143,               /* assoc_pair  */
  YYSYMBOL_lvalue = 144,                   /* lvalue  */
  YYSYMBOL_expr4 = 145,                    /* expr4  */
  YYSYMBOL_146_10 = 146,                   /* @10  */
  YYSYMBOL_147_11 = 147,                   /* @11  */
  YYSYMBOL_expr_or_block = 148,            /* expr_or_block  */
  YYSYMBOL_catch = 149,                    /* catch  */
  YYSYMBOL_150_12 = 150,                   /* @12  */
  YYSYMBOL_sscanf = 151,                   /* sscanf  */
  YYSYMBOL_parse_command = 152,            /* parse_command  */
  YYSYMBOL_time_expression = 153,          /* time_expression  */
  YYSYMBOL_154_13 = 154,                   /* @13  */
  YYSYMBOL_lvalue_list = 155,              /* lvalue_list  */
  YYSYMBOL_string = 156,                   /* string  */
  YYSYMBOL_string_con1 = 157,              /* string_con1  */
  YYSYMBOL_string_con2 = 158,              /* string_con2  */
  YYSYMBOL_class_init = 159,               /* class_init  */
  YYSYMBOL_opt_class_init = 160,           /* opt_class_init  */
  YYSYMBOL_function_call = 161,            /* function_call  */
  YYSYMBOL_efun_override = 162,            /* efun_override  */
  YYSYMBOL_function_name = 163,            /* function_name  */
  YYSYMBOL_cond = 164,                     /* cond  */
  YYSYMBOL_optional_else_part = 165        /* optional_else_part  */
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
typedef yytype_int16 yy_state_t;

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
#define YYLAST   1742

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  92
/* YYNRULES -- Number of rules.  */
#define YYNRULES  240
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  465

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


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
       2,     2,     2,     2,     2,     2,    71,    61,    54,     2,
      65,    66,    60,    58,    68,    59,     2,    62,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    67,    64,
      57,     2,     2,    51,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    72,     2,    73,    53,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    69,    52,    70,    63,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    55,    56
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   197,   197,   201,   202,   206,   207,   215,   265,   270,
     275,   276,   280,   281,   282,   286,   287,   292,   309,   291,
     359,   363,   364,   365,   369,   373,   383,   384,   388,   389,
     394,   393,   439,   440,   457,   458,   476,   480,   487,   495,
     506,   510,   511,   524,   529,   538,   539,   543,   551,   555,
     556,   560,   561,   565,   572,   611,   619,   623,   633,   638,
     643,   642,   659,   660,   661,   666,   670,   683,   689,   717,
     728,   754,   759,   769,   770,   771,   772,   773,   774,   775,
     780,   784,   806,   819,   818,   832,   831,   845,   844,   868,
     888,   893,   910,   915,   924,   923,   943,   946,   950,   955,
     964,   963,   995,  1001,  1008,  1015,  1022,  1036,  1052,  1062,
    1078,  1082,  1086,  1090,  1094,  1098,  1106,  1110,  1114,  1118,
    1122,  1126,  1130,  1134,  1138,  1142,  1146,  1150,  1154,  1161,
    1165,  1172,  1193,  1198,  1222,  1228,  1234,  1240,  1244,  1267,
    1289,  1303,  1347,  1384,  1388,  1392,  1546,  1640,  1720,  1724,
    1819,  1840,  1861,  1883,  1892,  1903,  1927,  1949,  1970,  1971,
    1972,  1973,  1974,  1975,  1979,  1985,  2006,  2009,  2013,  2020,
    2024,  2031,  2037,  2050,  2054,  2058,  2065,  2075,  2093,  2100,
    2212,  2213,  2251,  2267,  2272,  2271,  2301,  2312,  2316,  2320,
    2327,  2334,  2338,  2342,  2385,  2435,  2436,  2440,  2442,  2441,
    2501,  2534,  2623,  2641,  2645,  2652,  2656,  2664,  2663,  2677,
    2686,  2696,  2695,  2709,  2714,  2728,  2736,  2737,  2741,  2757,
    2758,  2773,  2784,  2787,  2796,  2800,  2807,  2839,  2910,  2965,
    2991,  3031,  3052,  3080,  3100,  3101,  3115,  3130,  3145,  3179,
    3183
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
  "\"end of file\"", "error", "\"invalid token\"", "L_NUMBER", "L_REAL",
  "L_STRING", "L_BASIC_TYPE", "L_TYPE_MODIFIER", "L_DEFINED_NAME",
  "L_IDENTIFIER", "L_EFUN", "L_INC", "L_DEC", "L_ASSIGN", "L_LAND",
  "L_LOR", "L_LSH", "L_RSH", "L_ORDER", "L_NOT", "L_IF", "L_ELSE",
  "L_SWITCH", "L_CASE", "L_DEFAULT", "L_RANGE", "L_DOT", "L_DOT_DOT_DOT",
  "L_WHILE", "L_DO", "L_FOR", "L_FOREACH", "L_IN", "L_BREAK", "L_CONTINUE",
  "L_RETURN", "L_ARROW", "L_INHERIT", "L_COLON_COLON", "L_ARRAY_OPEN",
  "L_MAPPING_OPEN", "L_FUNCTION_OPEN", "L_NEW_FUNCTION_OPEN", "L_SSCANF",
  "L_CATCH", "L_PARSE_COMMAND", "L_TIME_EXPRESSION", "L_CLASS", "L_NEW",
  "L_PARAMETER", "LOWER_THAN_ELSE", "'?'", "'|'", "'^'", "'&'", "L_EQ",
  "L_NE", "'<'", "'+'", "'-'", "'*'", "'%'", "'/'", "'~'", "';'", "'('",
  "')'", "':'", "','", "'{'", "'}'", "'$'", "'['", "']'", "$accept", "all",
  "program", "possible_semi_colon", "inheritance", "real", "number",
  "optional_star", "block_or_semi", "identifier", "def", "$@1", "@2",
  "modifier_change", "member_name", "member_name_list", "member_list",
  "type_decl", "@3", "new_local_name", "atomic_type", "basic_type",
  "new_arg", "argument", "argument_list", "type_modifier_list", "type",
  "cast", "opt_basic_type", "name_list", "new_name", "block",
  "block_items", "block_item", "local_declaration_stmt", "$@4",
  "decl_block", "local_declarations", "new_local_def",
  "single_new_local_def", "single_new_local_def_with_init",
  "local_name_list", "statement", "while", "$@5", "do", "$@6", "for",
  "$@7", "foreach_var", "foreach_vars", "foreach", "$@8", "for_expr",
  "first_for_expr", "switch", "$@9", "switch_block", "case", "case_label",
  "constant", "comma_expr", "expr0", "return", "expr_list",
  "expr_list_node", "expr_list2", "expr_list3", "expr_list4", "assoc_pair",
  "lvalue", "expr4", "@10", "@11", "expr_or_block", "catch", "@12",
  "sscanf", "parse_command", "time_expression", "@13", "lvalue_list",
  "string", "string_con1", "string_con2", "class_init", "opt_class_init",
  "function_call", "efun_override", "function_name", "cond",
  "optional_else_part", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-327)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-235)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -327,    32,    49,  -327,    53,  -327,     6,  -327,  -327,   121,
      54,  -327,  -327,  -327,  -327,    20,   185,  -327,  -327,  -327,
    -327,  -327,   198,    58,    -2,  -327,    20,   -13,   146,   110,
    -327,   118,  -327,    25,  -327,    54,   -11,    20,  -327,  -327,
    -327,  1650,   125,   198,  -327,  -327,  -327,  -327,   216,  -327,
    -327,   194,    12,    14,   212,   229,   229,  1650,   198,  1165,
     534,  1650,   151,   188,  -327,   192,  -327,   210,  -327,  1650,
    1650,   887,   227,  -327,  -327,   264,  1650,  1343,   124,    22,
    -327,  -327,  -327,  -327,  -327,   146,  -327,   262,   273,   183,
     282,    21,  1650,   198,   275,  1236,   153,  1305,  -327,   140,
    -327,  -327,  -327,  1276,   248,  -327,   254,  1065,   256,   283,
    -327,   193,  1343,   286,  1650,  1650,    -8,  1650,    -8,   956,
    -327,  -327,    92,   333,  1650,    54,   174,  -327,   198,  -327,
    1650,  1650,  1650,  1650,  1650,  1650,  1650,  1650,  1650,  1650,
    1650,  1650,  1650,  1650,  1650,  1650,  1650,  -327,  -327,  1650,
     198,   198,  1374,  1236,  1236,  -327,  -327,  -327,    54,  -327,
     289,     4,  -327,    40,    54,  1343,  -327,   183,   297,  -327,
    -327,  -327,   298,  1025,  1650,   316,   605,   317,  1650,  -327,
     242,   574,  1650,  -327,  -327,  -327,   856,  -327,   346,   318,
    -327,   208,   319,  -327,  1650,  -327,   507,   436,   221,   221,
     138,  1134,   314,  1547,   166,   299,   299,   138,   149,   149,
    -327,  -327,  -327,  1343,   300,   321,  1650,     5,   324,   325,
     327,  -327,  -327,   183,   198,   326,   323,   339,  -327,  -327,
    -327,  1343,  -327,  -327,  -327,  1343,   340,  1650,  1650,   225,
     747,  1650,  -327,  -327,   342,  -327,   230,  1650,  1236,  1236,
      55,   392,  -327,  -327,  -327,  -327,    19,  -327,  -327,    54,
    -327,   341,  -327,   925,  -327,   343,   344,   361,  -327,   362,
     374,   364,   378,  1443,  -327,  -327,  -327,  -327,  -327,  -327,
    -327,  -327,  -327,  -327,  -327,  -327,  -327,    -1,  -327,  -327,
     994,   231,  1236,  -327,  1343,   377,   379,   463,  -327,  1650,
    -327,    71,  -327,  -327,  -327,  -327,  -327,  -327,   229,   380,
    1650,  1650,  1650,   818,  1096,   243,  -327,  -327,  -327,    65,
      54,  -327,  1650,  -327,   198,   381,  -327,  -327,  1650,  -327,
      99,   113,  -327,   376,  -327,   235,   245,   253,   420,    54,
     443,  -327,  -327,   394,   391,  -327,  -327,  -327,   393,   428,
    -327,   327,   402,   398,   925,   409,  -327,  -327,   163,  -327,
    -327,  -327,   818,  -327,  -327,   412,   327,  1650,  1512,   243,
    1650,   465,    54,  -327,   413,  1650,  -327,   459,   414,   818,
    1650,  -327,  1343,   417,  -327,   363,  1650,  -327,  -327,  1343,
     818,  -327,  -327,  -327,   257,  1581,  -327,  1343,  -327,   126,
     421,   418,   818,   112,   419,  -327,   676,  -327,  -327,  -327,
    -327,   484,   496,   497,   112,    28,  1411,   452,  -327,   676,
     444,   676,   818,  -327,  -327,  -327,  1204,   112,  -327,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,  -327,  -327,  -327,  -327,  -327,   446,   115,
     226,   226,   186,  1479,  1556,   288,  1418,  1418,   186,   203,
     203,  -327,  -327,  -327,  -327
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,    45,     1,    45,    21,     5,    23,    22,    49,
      10,    46,     6,     3,    34,     0,     0,    24,    36,    50,
      47,    11,     0,     0,    51,   219,     0,     0,   216,    35,
      16,     0,    15,    53,    20,    10,     0,     0,     7,   220,
      30,     0,     0,     0,    52,   217,   218,    28,     0,     9,
       8,   198,   181,   182,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   207,     0,   211,     0,   183,     0,
       0,     0,     0,   163,   162,     0,     0,    54,     0,   158,
     197,   159,   160,   161,   195,   215,   180,     0,     0,    40,
      53,    45,     0,     0,     0,     0,     0,     0,   151,   179,
     152,   153,   235,   169,     0,   171,   167,     0,     0,   174,
     176,     0,   129,     0,     0,     0,     0,     0,     0,     0,
     155,   154,    34,     0,     0,    10,     0,   184,     0,   150,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   156,   157,     0,
       0,     0,     0,     0,     0,    33,    32,    39,    10,    43,
       0,    41,    31,    49,    10,   132,   236,    40,     0,   233,
     232,   170,     0,     0,     0,     0,     0,     0,     0,   200,
       0,     0,     0,    56,   205,   208,     0,   212,     0,     0,
      35,     0,     0,   196,     0,   237,   135,   134,   143,   144,
     141,     0,   136,   137,   138,   139,   140,   142,   145,   146,
     147,   148,   149,   131,     0,   186,     0,     0,     0,     0,
      37,    18,    42,     0,     0,    26,     0,     0,   227,   204,
     172,   178,   203,   177,   202,   130,     0,     0,     0,     0,
       0,     0,   222,   225,     0,    48,     0,     0,     0,     0,
       0,     0,   194,   224,   228,    38,     0,    44,    25,    10,
      29,     0,   201,   213,   206,     0,     0,     0,    85,     0,
       0,     0,     0,     0,    80,    55,    60,    62,    57,    59,
      79,    58,    75,    76,    63,    64,    77,     0,    78,    74,
       0,     0,     0,   185,   133,     0,     0,     0,   193,     0,
     191,     0,    14,    13,    19,    12,    27,   199,     0,     0,
       0,     0,     0,     0,     0,     0,    81,    82,   164,     0,
      10,    73,     0,   226,     0,     0,   230,   229,     0,   192,
       0,     0,   187,   213,   209,     0,     0,     0,     0,    10,
       0,    99,    98,     0,    97,    89,    91,    90,    92,     0,
     165,     0,    71,     0,   213,     0,   223,   231,     0,   188,
     190,   214,     0,   100,    83,     0,     0,     0,     0,     0,
       0,    67,    10,    61,     0,     0,   189,   239,     0,     0,
       0,    69,    70,     0,    93,     0,     0,    72,   210,   221,
       0,   238,    65,    84,     0,     0,    94,    68,   240,     0,
       0,     0,     0,     0,     0,    66,     0,    86,    87,    95,
     125,     0,     0,     0,     0,     0,   108,   109,   107,     0,
       0,     0,     0,   127,   126,   128,     0,     0,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   103,   101,   102,    88,   124,     0,     0,
     117,   118,   115,   110,   111,   112,   113,   114,   116,   119,
     120,   121,   122,   123,   106
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -327,  -327,  -327,  -327,  -327,  -327,  -327,    -6,  -327,    -4,
    -327,  -327,  -327,  -327,  -327,   258,  -327,  -327,  -327,  -203,
    -327,    -7,   292,   349,  -327,     2,   427,  -327,  -327,   486,
    -327,   -97,  -327,  -327,   120,  -327,  -327,  -327,  -327,   213,
    -327,   157,  -237,  -327,  -327,  -327,  -327,  -327,  -327,   161,
    -327,  -327,  -327,  -326,  -327,  -327,  -327,   -93,   132,   105,
    1293,   -56,   -33,  -327,   -79,  -166,   433,  -327,  -327,   357,
     -46,   -42,  -327,  -327,   423,  -327,  -327,  -327,  -327,  -327,
    -327,  -289,  -327,   -14,   -15,  -327,  -327,  -327,  -327,  -327,
    -327,  -327
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,    13,     5,    73,    74,   224,   304,    75,
       6,    42,   256,     7,   225,   226,    91,     8,    47,   157,
      18,   158,   159,   160,   161,     9,    10,    76,    20,    23,
      24,   277,   240,   278,   279,   320,   280,   399,   352,   347,
     341,   353,   419,   282,   379,   283,   313,   284,   422,   348,
     349,   285,   402,   342,   343,   286,   378,   420,   421,   415,
     416,   287,   112,   288,   104,   105,   106,   108,   109,   110,
      78,    79,   194,    94,   185,    80,   116,    81,    82,    83,
     118,   309,    84,    36,    85,   356,   291,    86,    87,    88,
     289,   391
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    27,    19,   281,    22,   111,    11,   230,    77,    98,
     100,    28,    31,    99,    99,   126,   168,   255,    33,   184,
     302,   184,    28,    46,   101,    25,   103,   107,     4,    43,
     251,   222,     3,  -179,  -179,  -179,   120,   121,    41,    90,
     189,   126,   383,   129,   361,    37,    14,    37,   150,    -2,
     -15,    38,   -16,   427,   102,    45,     4,   182,   151,   165,
       4,   183,   103,   321,   125,   374,    35,   178,   191,   401,
      12,   230,   223,   178,   218,   219,   338,    95,   252,  -234,
     297,   103,   181,   303,   186,    26,   103,   123,   183,   166,
     -17,   162,   170,   163,   152,   428,   217,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,    21,   410,   213,    25,   410,   192,
     103,   103,    34,   178,   195,   377,   239,    14,   298,   350,
      93,   411,    14,   178,   411,   147,   148,   149,   246,   178,
     103,   231,   393,   107,   332,   235,   214,   215,   371,   403,
     404,    39,   220,   398,   132,   133,    19,  -198,    15,   305,
     250,    32,    30,   381,   307,   409,   150,   178,    16,   295,
     296,   412,   359,   123,   412,   413,   151,   414,   413,   -15,
     449,   178,   132,   133,   134,   446,   360,    40,    17,    14,
      89,   155,   156,    29,    30,   301,   142,   143,   144,   145,
     146,   169,   429,   430,   103,   263,    32,    30,   290,   144,
     145,   146,   152,   325,   294,   103,   103,   319,   113,   114,
     258,   139,   140,   141,   142,   143,   144,   145,   146,    92,
     123,   178,    93,   276,    25,    51,   376,    52,    53,    54,
     193,   330,   178,   331,   438,   439,   440,   441,   442,    14,
      96,   345,   346,   115,   335,   336,   337,   117,   344,   103,
     177,   178,   333,   440,   441,   442,    99,    58,    59,    60,
      61,    62,   358,    64,   244,   119,   178,    67,    68,   142,
     143,   144,   145,   146,   438,   439,   440,   441,   442,   354,
     123,   264,   127,   178,    97,    41,   293,   323,   178,   324,
      72,   362,   128,   178,   429,   430,   431,   339,   339,   236,
     237,   363,   344,   178,   351,   132,   133,   134,   172,   364,
     355,   178,   173,   400,   394,   178,   443,   153,   445,   175,
     132,   133,   134,   366,   382,   155,   156,   385,   154,   344,
     167,   190,   389,   435,   436,   437,   438,   439,   440,   441,
     442,   176,   179,   397,   242,   221,   141,   142,   143,   144,
     145,   146,   339,   228,   229,   248,   351,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   130,   131,   132,
     133,   134,   232,   234,   243,   245,   249,   260,    28,   417,
     253,   254,   276,    48,   259,    49,    50,    25,    51,    28,
      52,    53,    54,    55,    56,   261,   262,   292,   310,   311,
     183,    57,    28,   417,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   312,   314,   316,   396,
      58,    59,    60,    61,    62,    63,    64,    65,    66,   315,
      67,    68,   317,   326,   308,   327,   334,   357,   365,   299,
     130,    69,   132,   133,   134,    70,   367,    71,   368,   178,
     370,   369,   373,    72,    48,   300,    49,    50,    25,    51,
     372,    52,    53,    54,    55,    56,   375,   380,   386,   388,
     390,   395,    57,   392,   408,   407,   418,   423,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   424,
     425,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      37,    67,    68,   464,   444,   257,   227,   306,   164,   405,
     328,    44,    69,   132,   133,   134,    70,   340,    71,   387,
     384,   406,   448,   233,    72,    48,   329,    49,    50,    25,
      51,   187,    52,    53,    54,    55,    56,   180,     0,     0,
       0,     0,     0,    57,     0,     0,     0,     0,     0,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
       0,     0,    58,    59,    60,    61,    62,    63,    64,    65,
      66,     0,    67,    68,     0,     0,     0,     0,   130,   131,
     132,   133,   134,    69,     0,     0,     0,    70,     0,    71,
       0,     0,     0,     0,     0,    72,    48,  -173,    49,    50,
      25,    51,     0,    52,    53,    54,    55,    56,     0,     0,
       0,     0,     0,     0,    57,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,     0,     0,
       0,     0,   238,    58,    59,    60,    61,    62,    63,    64,
      65,    66,     0,    67,    68,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    69,     0,     0,     0,    70,     0,
      71,     0,     0,     0,     0,     0,    72,    48,  -175,    49,
      50,    25,    51,     0,    52,    53,    54,    55,    56,     0,
       0,     0,     0,     0,     0,    57,   265,     0,   266,   403,
     404,     0,     0,     0,   267,   268,   269,   270,     0,   271,
     272,   273,     0,     0,    58,    59,    60,    61,    62,    63,
      64,    65,    66,     0,    67,    68,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    69,     0,     0,     0,    70,
     274,    71,     0,     0,     0,   183,  -104,    72,    48,     0,
      49,    50,    25,   122,     0,    52,    53,    54,    55,    56,
       0,     0,     0,     0,     0,     0,    57,   265,     0,   266,
       0,     0,     0,     0,     0,   267,   268,   269,   270,     0,
     271,   272,   273,     0,     0,    58,    59,    60,    61,    62,
      63,    64,    65,    66,   123,    67,    68,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    69,     0,     0,     0,
      70,   274,    71,     0,     0,     0,   183,   275,    72,    48,
       0,    49,    50,    25,    51,     0,    52,    53,    54,    55,
      56,     0,     0,     0,     0,     0,     0,    57,   265,     0,
     266,     0,     0,     0,     0,     0,   267,   268,   269,   270,
       0,   271,   272,   273,     0,     0,    58,    59,    60,    61,
      62,    63,    64,    65,    66,     0,    67,    68,     0,     0,
     130,   131,   132,   133,   134,     0,     0,    69,     0,     0,
       0,    70,   274,    71,     0,     0,     0,   183,    48,    72,
      49,    50,    25,   122,     0,    52,    53,    54,    55,    56,
       0,     0,     0,     0,     0,     0,    57,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,     0,
       0,     0,     0,     0,   241,    58,    59,    60,    61,    62,
      63,    64,    65,    66,   123,    67,    68,     0,     0,   130,
     131,   132,   133,   134,     0,     0,    69,   124,     0,     0,
      70,     0,    71,     0,     0,     0,     0,    48,    72,    49,
      50,    25,    51,     0,    52,    53,    54,    55,    56,     0,
       0,     0,     0,     0,     0,    57,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,     0,     0,
       0,     0,     0,   308,    58,    59,    60,    61,    62,    63,
      64,    65,    66,   188,    67,    68,     0,     0,   130,   131,
     132,   133,   134,     0,     0,    69,     0,     0,     0,    70,
       0,    71,  -166,     0,     0,     0,    48,    72,    49,    50,
      25,    51,     0,    52,    53,    54,    55,    56,     0,     0,
       0,     0,     0,     0,    57,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,     0,     0,
       0,     0,   322,    58,    59,    60,    61,    62,    63,    64,
      65,    66,     0,    67,    68,     0,     0,     0,     0,   130,
     131,   132,   133,   134,    69,     0,     0,     0,    70,     0,
      71,  -168,     0,     0,     0,  -168,    72,    48,     0,    49,
      50,    25,   122,     0,    52,    53,    54,    55,    56,     0,
       0,     0,     0,     0,     0,    57,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,     0,     0,
       0,     0,   174,     0,    58,    59,    60,    61,    62,    63,
      64,    65,    66,   123,    67,    68,     0,     0,   130,   131,
     132,   133,   134,     0,     0,    69,     0,     0,     0,    70,
     -96,    71,     0,     0,     0,     0,    48,    72,    49,    50,
      25,    51,     0,    52,    53,    54,    55,    56,     0,     0,
       0,     0,     0,     0,    57,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,     0,     0,     0,
       0,   247,     0,    58,    59,    60,    61,    62,    63,    64,
      65,    66,     0,    67,    68,     0,     0,     0,     0,     0,
     429,   430,   431,     0,    69,     0,     0,     0,    70,     0,
      71,     0,     0,     0,     0,  -166,    72,    48,     0,    49,
      50,    25,    51,     0,    52,    53,    54,    55,    56,     0,
       0,     0,     0,     0,     0,    57,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,     0,     0,     0,
     447,     0,     0,     0,    58,    59,    60,    61,    62,    63,
      64,    65,    66,     0,    67,    68,     0,     0,     0,     0,
     130,   131,   132,   133,   134,    69,     0,     0,     0,    70,
       0,    71,  -166,   171,     0,     0,    48,    72,    49,    50,
      25,    51,     0,    52,    53,    54,    55,    56,     0,     0,
       0,     0,     0,     0,    57,     0,     0,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,     0,
       0,     0,     0,    58,    59,    60,    61,    62,    63,    64,
      65,    66,     0,    67,    68,     0,     0,   130,   131,   132,
     133,   134,     0,     0,    69,   124,     0,     0,    70,     0,
      71,     0,     0,     0,     0,    48,    72,    49,    50,    25,
      51,     0,    52,    53,    54,    55,    56,     0,     0,     0,
       0,     0,     0,    57,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,     0,     0,     0,     0,
       0,     0,    58,    59,    60,    61,    62,    63,    64,    65,
      66,     0,    67,    68,     0,     0,     0,   429,   430,   431,
       0,   216,     0,    69,   429,   430,   431,    70,     0,    71,
       0,     0,     0,     0,    48,    72,    49,    50,    25,    51,
       0,    52,    53,    54,    55,    56,     0,     0,     0,     0,
       0,     0,    57,   432,   433,   434,   435,   436,   437,   438,
     439,   440,   441,   442,     0,   437,   438,   439,   440,   441,
     442,    58,    59,    60,    61,    62,    63,    64,    65,    66,
       0,    67,    68,     0,     0,   429,   430,   431,     0,     0,
       0,     0,    69,     0,     0,     0,    70,   318,    71,     0,
       0,     0,     0,    48,    72,    49,    50,    25,    51,     0,
      52,    53,    54,    55,    56,     0,     0,     0,     0,     0,
       0,    57,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,     0,     0,     0,     0,     0,     0,     0,     0,
      58,    59,    60,    61,    62,    63,    64,    65,    66,     0,
      67,    68,     0,   132,   133,   134,     0,     0,     0,     0,
       0,    69,   429,   430,   431,    70,   -96,    71,     0,     0,
       0,     0,    48,    72,    49,    50,    25,    51,     0,    52,
      53,    54,    55,    56,     0,     0,     0,     0,     0,     0,
      57,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     434,   435,   436,   437,   438,   439,   440,   441,   442,    58,
      59,    60,    61,    62,    63,    64,    65,    66,     0,    67,
      68,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      69,     0,     0,     0,    70,     0,    71,   -96,     0,     0,
       0,    48,    72,    49,    50,    25,    51,     0,    52,    53,
      54,    55,    56,     0,     0,     0,     0,     0,     0,    57,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    58,    59,
      60,    61,    62,    63,    64,    65,    66,     0,    67,    68,
       0,     0,     0,     0,     0,     0,     0,   426,     0,    69,
       0,     0,     0,    70,     0,    71,     0,     0,     0,     0,
       0,    72,   450,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   461,   462,   463,     0,     0,     0,     0,
       0,     0,   426
};

static const yytype_int16 yycheck[] =
{
      15,    15,     9,   240,    10,    61,     4,   173,    41,    55,
      56,    26,    16,    55,    56,    71,    95,   220,    22,   116,
       1,   118,    37,    37,    57,     5,    59,    60,     7,    35,
      25,    27,     0,    11,    12,    13,    69,    70,    13,    43,
     119,    97,   368,    76,   333,    58,     6,    58,    26,     0,
      38,    64,    38,    25,    58,    66,     7,    65,    36,    92,
       7,    69,    95,    64,    71,   354,    68,    68,   124,   395,
      64,   237,    68,    68,   153,   154,   313,    65,    73,    65,
      25,   114,   115,    64,   117,    65,   119,    47,    69,    93,
      65,    70,    96,    91,    72,    67,   152,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,    60,     3,   149,     5,     3,   125,
     153,   154,    64,    68,   128,   362,   182,     6,    73,    64,
      38,    19,     6,    68,    19,    11,    12,    13,   194,    68,
     173,   174,   379,   176,    73,   178,   150,   151,   351,    23,
      24,     5,   158,   390,    16,    17,   163,    65,    37,   256,
     216,     8,     9,   366,   261,   402,    26,    68,    47,   248,
     249,    59,    73,    47,    59,    63,    36,    65,    63,    69,
      65,    68,    16,    17,    18,   422,    73,    69,    67,     6,
      65,     8,     9,     8,     9,   251,    58,    59,    60,    61,
      62,    48,    16,    17,   237,   238,     8,     9,   241,    60,
      61,    62,    72,   292,   247,   248,   249,   273,    67,    68,
     224,    55,    56,    57,    58,    59,    60,    61,    62,    13,
      47,    68,    38,   240,     5,     6,    73,     8,     9,    10,
      66,   297,    68,   299,    58,    59,    60,    61,    62,     6,
      38,     8,     9,    65,   310,   311,   312,    65,   314,   292,
      67,    68,   308,    60,    61,    62,   308,    38,    39,    40,
      41,    42,   328,    44,    66,    65,    68,    48,    49,    58,
      59,    60,    61,    62,    58,    59,    60,    61,    62,   322,
      47,    66,    65,    68,    65,    13,    66,    66,    68,    68,
      71,    66,    38,    68,    16,    17,    18,   314,   315,    67,
      68,    66,   368,    68,   320,    16,    17,    18,    70,    66,
     324,    68,    68,    66,   380,    68,   419,    65,   421,    73,
      16,    17,    18,   339,   367,     8,     9,   370,    65,   395,
      65,     8,   375,    55,    56,    57,    58,    59,    60,    61,
      62,    68,    66,   386,     8,    66,    57,    58,    59,    60,
      61,    62,   369,    66,    66,    65,   372,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    14,    15,    16,
      17,    18,    66,    66,    66,    66,    65,    64,   403,   403,
      66,    66,   399,     1,    68,     3,     4,     5,     6,   414,
       8,     9,    10,    11,    12,    66,    66,    65,    65,    65,
      69,    19,   427,   427,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    65,    65,    64,    66,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    65,
      48,    49,    64,    66,    68,    66,    66,    66,    28,    57,
      14,    59,    16,    17,    18,    63,    13,    65,    64,    68,
      32,    68,    64,    71,     1,    73,     3,     4,     5,     6,
      68,     8,     9,    10,    11,    12,    67,    65,    13,    66,
      21,    64,    19,    69,    66,    64,    67,     3,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,     3,
       3,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      58,    48,    49,    67,    70,   223,   167,   259,    91,   399,
      57,    35,    59,    16,    17,    18,    63,   314,    65,   372,
     369,   399,   427,   176,    71,     1,    73,     3,     4,     5,
       6,   118,     8,     9,    10,    11,    12,   114,    -1,    -1,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    48,    49,    -1,    -1,    -1,    -1,    14,    15,
      16,    17,    18,    59,    -1,    -1,    -1,    63,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    71,     1,    73,     3,     4,
       5,     6,    -1,     8,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    68,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    63,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    71,     1,    73,     3,
       4,     5,     6,    -1,     8,     9,    10,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    20,    -1,    22,    23,
      24,    -1,    -1,    -1,    28,    29,    30,    31,    -1,    33,
      34,    35,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    -1,    69,    70,    71,     1,    -1,
       3,     4,     5,     6,    -1,     8,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    -1,
      33,    34,    35,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,
      63,    64,    65,    -1,    -1,    -1,    69,    70,    71,     1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    10,    11,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
      -1,    33,    34,    35,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    48,    49,    -1,    -1,
      14,    15,    16,    17,    18,    -1,    -1,    59,    -1,    -1,
      -1,    63,    64,    65,    -1,    -1,    -1,    69,     1,    71,
       3,     4,     5,     6,    -1,     8,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    -1,    -1,    -1,    68,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    14,
      15,    16,    17,    18,    -1,    -1,    59,    60,    -1,    -1,
      63,    -1,    65,    -1,    -1,    -1,    -1,     1,    71,     3,
       4,     5,     6,    -1,     8,     9,    10,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    -1,    -1,    68,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    14,    15,
      16,    17,    18,    -1,    -1,    59,    -1,    -1,    -1,    63,
      -1,    65,    66,    -1,    -1,    -1,     1,    71,     3,     4,
       5,     6,    -1,     8,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    -1,    68,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    49,    -1,    -1,    -1,    -1,    14,
      15,    16,    17,    18,    59,    -1,    -1,    -1,    63,    -1,
      65,    66,    -1,    -1,    -1,    70,    71,     1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    10,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    -1,
      -1,    -1,    67,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    14,    15,
      16,    17,    18,    -1,    -1,    59,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    -1,    -1,     1,    71,     3,     4,
       5,     6,    -1,     8,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      -1,    67,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    49,    -1,    -1,    -1,    -1,    -1,
      16,    17,    18,    -1,    59,    -1,    -1,    -1,    63,    -1,
      65,    -1,    -1,    -1,    -1,    70,    71,     1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    10,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    -1,    -1,    -1,
      66,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    48,    49,    -1,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    59,    -1,    -1,    -1,    63,
      -1,    65,    66,    27,    -1,    -1,     1,    71,     3,     4,
       5,     6,    -1,     8,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    -1,    -1,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    -1,    48,    49,    -1,    -1,    14,    15,    16,
      17,    18,    -1,    -1,    59,    60,    -1,    -1,    63,    -1,
      65,    -1,    -1,    -1,    -1,     1,    71,     3,     4,     5,
       6,    -1,     8,     9,    10,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    19,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    48,    49,    -1,    -1,    -1,    16,    17,    18,
      -1,    57,    -1,    59,    16,    17,    18,    63,    -1,    65,
      -1,    -1,    -1,    -1,     1,    71,     3,     4,     5,     6,
      -1,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    -1,    57,    58,    59,    60,    61,
      62,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    48,    49,    -1,    -1,    16,    17,    18,    -1,    -1,
      -1,    -1,    59,    -1,    -1,    -1,    63,    64,    65,    -1,
      -1,    -1,    -1,     1,    71,     3,     4,     5,     6,    -1,
       8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      48,    49,    -1,    16,    17,    18,    -1,    -1,    -1,    -1,
      -1,    59,    16,    17,    18,    63,    64,    65,    -1,    -1,
      -1,    -1,     1,    71,     3,     4,     5,     6,    -1,     8,
       9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      19,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    -1,    -1,    -1,    63,    -1,    65,    66,    -1,    -1,
      -1,     1,    71,     3,     4,     5,     6,    -1,     8,     9,
      10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   414,    -1,    59,
      -1,    -1,    -1,    63,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    71,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,    -1,    -1,    -1,    -1,
      -1,    -1,   449
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    75,    76,     0,     7,    78,    84,    87,    91,    99,
     100,    99,    64,    77,     6,    37,    47,    67,    94,    95,
     102,    60,    81,   103,   104,     5,    65,   157,   158,     8,
       9,    83,     8,    83,    64,    68,   157,    58,    64,     5,
      69,    13,    85,    81,   103,    66,   157,    92,     1,     3,
       4,     6,     8,     9,    10,    11,    12,    19,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    48,    49,    59,
      63,    65,    71,    79,    80,    83,   101,   136,   144,   145,
     149,   151,   152,   153,   156,   158,   161,   162,   163,    65,
      83,    90,    13,    38,   147,    65,    38,    65,   144,   145,
     144,   136,    83,   136,   138,   139,   140,   136,   141,   142,
     143,   135,   136,    67,    68,    65,   150,    65,   154,    65,
     136,   136,     6,    47,    60,    95,   135,    65,    38,   136,
      14,    15,    16,    17,    18,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    11,    12,    13,
      26,    36,    72,    65,    65,     8,     9,    93,    95,    96,
      97,    98,    70,    99,   100,   136,    83,    65,   138,    48,
      83,    27,    70,    68,    67,    73,    68,    67,    68,    66,
     140,   136,    65,    69,   105,   148,   136,   148,    47,   138,
       8,   135,    81,    66,   146,    83,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,    83,    83,    57,   135,   138,   138,
      81,    66,    27,    68,    81,    88,    89,    97,    66,    66,
     139,   136,    66,   143,    66,   136,    67,    68,    68,   135,
     106,    68,     8,    66,    66,    66,   135,    67,    65,    65,
     135,    25,    73,    66,    66,    93,    86,    96,    83,    68,
      64,    66,    66,   136,    66,    20,    22,    28,    29,    30,
      31,    33,    34,    35,    64,    70,    95,   105,   107,   108,
     110,   116,   117,   119,   121,   125,   129,   135,   137,   164,
     136,   160,    65,    66,   136,   138,   138,    25,    73,    57,
      73,   135,     1,    64,    82,   105,    89,   105,    68,   155,
      65,    65,    65,   120,    65,    65,    64,    64,    64,   135,
     109,    64,    68,    66,    68,   138,    66,    66,    57,    73,
     135,   135,    73,   144,    66,   135,   135,   135,   116,    95,
     113,   114,   127,   128,   135,     8,     9,   113,   123,   124,
      64,    81,   112,   115,   136,    83,   159,    66,   135,    73,
      73,   155,    66,    66,    66,    28,    81,    13,    64,    68,
      32,    93,    68,    64,   155,    67,    73,   116,   130,   118,
      65,    93,   136,   127,   123,   136,    13,   115,    66,   136,
      21,   165,    69,   116,   135,    64,    66,   136,   116,   111,
      66,   127,   126,    23,    24,   108,   132,    64,    66,   116,
       3,    19,    59,    63,    65,   133,   134,   157,    67,   116,
     131,   132,   122,     3,     3,     3,   134,    25,    67,    16,
      17,    18,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,   131,    70,   131,   116,    66,   133,    65,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,    67
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    76,    76,    77,    77,    78,    79,    80,
      81,    81,    82,    82,    82,    83,    83,    85,    86,    84,
      84,    84,    84,    84,    87,    88,    89,    89,    90,    90,
      92,    91,    93,    93,    94,    94,    95,    96,    96,    96,
      97,    97,    97,    98,    98,    99,    99,   100,   101,   102,
     102,   103,   103,   104,   104,   105,   106,   106,   107,   107,
     109,   108,   110,   110,   110,   111,   111,   112,   112,   113,
     114,   115,   115,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   118,   117,   120,   119,   122,   121,   123,
     123,   123,   124,   124,   126,   125,   127,   127,   128,   128,
     130,   129,   131,   131,   131,   132,   132,   132,   133,   133,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   135,
     135,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   137,   137,   138,   138,   138,   139,
     139,   140,   140,   141,   141,   141,   142,   142,   143,   144,
     145,   145,   145,   145,   146,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   147,   145,
     145,   145,   145,   145,   145,   148,   148,   150,   149,   151,
     152,   154,   153,   155,   155,   156,   157,   157,   157,   158,
     158,   159,   160,   160,   161,   161,   161,   161,   161,   161,
     161,   161,   162,   162,   163,   163,   163,   163,   164,   165,
     165
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     0,     0,     1,     4,     1,     1,
       0,     1,     1,     1,     1,     1,     1,     0,     0,     9,
       3,     1,     1,     1,     2,     2,     1,     3,     0,     4,
       0,     7,     1,     1,     1,     2,     1,     2,     3,     1,
       0,     1,     2,     1,     3,     0,     2,     2,     4,     0,
       1,     1,     3,     2,     4,     3,     0,     2,     1,     1,
       0,     4,     1,     1,     1,     0,     2,     2,     4,     3,
       3,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     0,     6,     0,     8,     0,    10,     1,
       1,     1,     1,     3,     0,     8,     0,     1,     1,     1,
       0,    10,     2,     2,     0,     3,     5,     2,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     2,     2,     2,     1,
       3,     3,     3,     5,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     2,     3,     0,     1,     2,     1,
       2,     1,     3,     0,     1,     2,     1,     3,     3,     1,
       1,     1,     1,     1,     0,     5,     3,     6,     7,     8,
       7,     5,     6,     5,     4,     1,     3,     1,     0,     6,
       3,     5,     4,     4,     4,     1,     3,     0,     3,     7,
       9,     0,     3,     0,     3,     1,     1,     3,     3,     1,
       2,     3,     0,     3,     4,     4,     6,     4,     4,     6,
       6,     7,     3,     3,     1,     2,     3,     3,     6,     0,
       2
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
  case 6: /* possible_semi_colon: ';'  */
#line 208 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            yywarn("Extra ';' ignored.");
        }
#line 1860 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 7: /* inheritance: type_modifier_list L_INHERIT string_con1 ';'  */
#line 216 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            object_t *ob;
            inherit_t inherit;
            int initializer;

            (yyvsp[-3].type) |= global_modifiers;

            if (var_defined)
                yyerror("Invalid inherit clause after variables declarations.");

            if (memchr((yyvsp[-1].string_span).str, '\0', (yyvsp[-1].string_span).len) != NULL) {
                yyerror("Inherited file path must not contain embedded null bytes.");
                scratch_free((yyvsp[-1].string_span).str);
                break;
            }

            ob = find_object_by_name((yyvsp[-1].string_span).str);
            if (ob == 0) {
                inherit_file = alloc_cstring((yyvsp[-1].string_span).str, "inherit");
                /* Return back to load_object() */
                YYACCEPT;
            }
            scratch_free((yyvsp[-1].string_span).str);

            inherit.prog = ob->prog;
            inherit.function_index_offset = (function_index_t)(mem_block[A_RUNTIME_FUNCTIONS].current_size / sizeof (runtime_function_u));
            inherit.variable_index_offset = (unsigned short)(mem_block[A_VAR_TEMP].current_size / sizeof (variable_t));
            inherit.type_mod = (unsigned short)(yyvsp[-3].type);

            add_to_mem_block(A_INHERITS, (char *)&inherit, sizeof inherit);
            copy_variables(ob->prog, (yyvsp[-3].type));
            copy_structures(ob->prog);
            initializer = copy_functions(ob->prog, (yyvsp[-3].type));
            if (initializer >= 0)
              {
                /* initializer is an index into the object we're
                 * inheriting's function table; this finds the
                 * appropriate entry in our table and generates
                 * a call to it
                 */
                int inherit_index = (int)(mem_block[A_INHERITS].current_size/sizeof(inherit_t) - 1);
                switch_to_block(A_INITIALIZER);
                generate_inherited_init_call(inherit_index, initializer);
                switch_to_block(A_PROGRAM);
              }
        }
#line 1911 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 8: /* real: L_REAL  */
#line 266 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        { CREATE_REAL((yyval.node), (yyvsp[0].real)); }
#line 1917 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 9: /* number: L_NUMBER  */
#line 271 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        { CREATE_NUMBER((yyval.node), (yyvsp[0].number)); }
#line 1923 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 10: /* optional_star: %empty  */
#line 275 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                        { (yyval.type) = 0; }
#line 1929 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 11: /* optional_star: '*'  */
#line 276 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                        { (yyval.type) = TYPE_MOD_ARRAY; }
#line 1935 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 12: /* block_or_semi: block  */
#line 280 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                        { (yyval.node) = (yyvsp[0].decl).node; if (!(yyval.node)) CREATE_RETURN((yyval.node), 0); }
#line 1941 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 13: /* block_or_semi: ';'  */
#line 281 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                        { (yyval.node) = 0; }
#line 1947 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 14: /* block_or_semi: error  */
#line 282 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                        { (yyval.node) = 0; }
#line 1953 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 15: /* identifier: L_DEFINED_NAME  */
#line 286 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                        { (yyval.string) = scratch_copy((yyvsp[0].ihe)->name); }
#line 1959 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 17: /* $@1: %empty  */
#line 292 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            (yyvsp[-2].type) |= global_modifiers;
            /* Handle type checking here so we know whether to typecheck
               'argument' */
            if ((yyvsp[-2].type) & ~NAME_TYPE_MOD) {
                exact_types = (yyvsp[-2].type) | (yyvsp[-1].type);
            } else {
                if (pragmas & PRAGMA_STRICT_TYPES) {
                    if (strcmp((yyvsp[0].string), "create") != 0)
                        yyerror("\"#pragma strict_types\" requires type of function");
                    else
                        exact_types = TYPE_VOID; /* default for create() */
                } else
                    exact_types = 0;
            }
        }
#line 1980 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 18: /* @2: %empty  */
#line 309 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            char *p = (yyvsp[-4].string);
            (yyvsp[-4].string) = make_shared_string((yyvsp[-4].string), NULL);
            scratch_free(p);

            /* (If we had nested functions, we would need to check
             * here if we have enough space for locals)
             *
             * Define a prototype. If it is a real function, then the
             * prototype will be replaced below.
             */

            (yyval.number) = NAME_UNDEFINED | NAME_PROTOTYPE;
            if ((yyvsp[-1].argument).flags & ARG_IS_VARARGS) {
                (yyval.number) |= NAME_TRUE_VARARGS;
                (yyvsp[-6].type) |= NAME_VARARGS;
            }
            define_new_function((yyvsp[-4].string), (yyvsp[-1].argument).num_arg, 0, (yyval.number), (yyvsp[-6].type) | (yyvsp[-5].type));
            /* This is safe since it is guaranteed to be in the
               function table, so it can't be dangling */
            free_string(to_shared_str((yyvsp[-4].string))); 
            context = 0;
        }
#line 2008 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 19: /* def: type optional_star identifier $@1 '(' argument ')' @2 block_or_semi  */
#line 333 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
                /* Either a prototype or a block */
                if ((yyvsp[0].node)) {
                    int fun;

                    (yyvsp[-1].number) &= ~(NAME_UNDEFINED | NAME_PROTOTYPE);
                    if ((yyvsp[0].node)->kind != NODE_RETURN &&
                        ((yyvsp[0].node)->kind != NODE_TWO_VALUES
                         || (yyvsp[0].node)->r.expr->kind != NODE_RETURN)) {
                        parse_node_t *replacement;
                        CREATE_STATEMENTS(replacement, (yyvsp[0].node), 0);
                        CREATE_RETURN(replacement->r.expr, 0);
                        (yyvsp[0].node) = replacement;
                    }
                    if ((yyvsp[-3].argument).flags & ARG_IS_PROTO) {
                        yyerror("Missing name for function argument");
                    }
                    fun = define_new_function((yyvsp[-6].string), (yyvsp[-3].argument).num_arg, 
                                              max_num_locals - (yyvsp[-3].argument).num_arg,
                                              (yyvsp[-1].number), (yyvsp[-8].type) | (yyvsp[-7].type));
                    if (fun != -1)
                        COMPILER_FUNC(fun)->address =
                            generate_function(COMPILER_FUNC(fun), (yyvsp[0].node), max_num_locals);
                }
                free_all_local_names();
            }
#line 2039 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 20: /* def: type name_list ';'  */
#line 360 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (!(yyvsp[-2].type)) yyerror("Missing type for global variable declaration");
            }
#line 2047 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 24: /* modifier_change: type_modifier_list ':'  */
#line 369 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                                { global_modifiers = (yyvsp[-1].type); }
#line 2053 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 25: /* member_name: optional_star identifier  */
#line 374 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            if ((current_type & ~NAME_TYPE_MOD) == TYPE_VOID)
                yyerror("Illegal to declare class member of type void.");
            add_local_name((yyvsp[0].string), current_type | (yyvsp[-1].type));
            scratch_free((yyvsp[0].string));
        }
#line 2064 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 30: /* @3: %empty  */
#line 394 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            ident_hash_elem_t *ihe;

            ihe = find_or_add_ident(
                PROG_STRING((yyval.number) = store_prog_string_len((yyvsp[-1].string), strlen((yyvsp[-1].string)))),
                FOA_GLOBAL_SCOPE);
            if (ihe->dn.class_num == -1)
                ihe->sem_value++;
            else {
                /* Possibly, this should check if the definitions are
                   consistent */
                char buf[256];
                char *end = EndOf(buf);
                char *p;
                    
                p = strput(buf, end, "Illegal to redefine class ");
                p = strput(p, end, (yyvsp[-1].string));
                yyerror(buf);
            }
            ihe->dn.class_num = (short)(mem_block[A_CLASS_DEF].current_size / sizeof(class_def_t));
        }
#line 2090 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 31: /* type_decl: type_modifier_list L_CLASS identifier '{' @3 member_list '}'  */
#line 416 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            class_def_t *sd;
            class_member_entry_t *sme;
            int i;

            sd = (class_def_t *)allocate_in_mem_block(A_CLASS_DEF, sizeof(class_def_t));
            i = sd->size = (unsigned short)current_number_of_locals;
            sd->index = (unsigned short)(mem_block[A_CLASS_MEMBER].current_size / sizeof(class_member_entry_t));
            sd->name = (unsigned short)(yyvsp[-2].number);

            sme = (class_member_entry_t *)allocate_in_mem_block(A_CLASS_MEMBER, sizeof(class_member_entry_t) * current_number_of_locals);

            while (i--) {
                sme[i].name = store_prog_string_len(locals_ptr[i]->name, strlen(locals_ptr[i]->name));
                sme[i].type = type_of_locals_ptr[i];
            }

            free_all_local_names();
            scratch_free((yyvsp[-4].string));
        }
#line 2115 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 33: /* new_local_name: L_DEFINED_NAME  */
#line 441 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            if ((yyvsp[0].ihe)->dn.local_num != -1) {
                char buff[256];
                char *end = EndOf(buff);
                char *p;
                    
                p = strput(buff, end, "Illegal to redeclare local name '");
                p = strput(p, end, (yyvsp[0].ihe)->name);
                p = strput(p, end, "'");
                yyerror(buff);
            }
            (yyval.string) = scratch_copy((yyvsp[0].ihe)->name);
        }
#line 2133 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 35: /* atomic_type: L_CLASS L_DEFINED_NAME  */
#line 459 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            if ((yyvsp[0].ihe)->dn.class_num == -1) {
                char buf[256];
                char *end = EndOf(buf);
                char *p;
                    
                p = strput(buf, end, "Undefined class '");
                p = strput(p, end, (yyvsp[0].ihe)->name);
                p = strput(p, end, "'");
                yyerror(buf);
                (yyval.type) = TYPE_ANY;
            } else 
                (yyval.type) = (yyvsp[0].ihe)->dn.class_num | TYPE_MOD_CLASS;
        }
#line 2152 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 37: /* new_arg: basic_type optional_star  */
#line 481 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            if ((yyvsp[-1].type) == TYPE_VOID)
                yyerror("Illegal to declare argument of type void.");
            (yyval.number) = ARG_IS_PROTO;
            add_local_name("", (yyvsp[-1].type) | (yyvsp[0].type));
        }
#line 2163 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 38: /* new_arg: basic_type optional_star new_local_name  */
#line 488 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            if ((yyvsp[-2].type) == TYPE_VOID)
                yyerror("Illegal to declare argument of type void.");
            add_local_name((yyvsp[0].string), (yyvsp[-2].type) | (yyvsp[-1].type));
            scratch_free((yyvsp[0].string));
            (yyval.number) = 0;
        }
#line 2175 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 39: /* new_arg: new_local_name  */
#line 496 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            if (exact_types) yyerror("Missing type for argument");
            add_local_name((yyvsp[0].string), TYPE_ANY);
            scratch_free((yyvsp[0].string));
            (yyval.number) = 0;
        }
#line 2186 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 40: /* argument: %empty  */
#line 506 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            (yyval.argument).num_arg = 0;
            (yyval.argument).flags = 0;
        }
#line 2195 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 42: /* argument: argument_list L_DOT_DOT_DOT  */
#line 512 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            int x = type_of_locals_ptr[max_num_locals-1];

            (yyval.argument) = (yyvsp[-1].argument);
            (yyval.argument).flags |= ARG_IS_VARARGS;

            if (x != TYPE_ANY && !(x & TYPE_MOD_ARRAY))
                yywarn("Variable to hold remainder of arguments should be an array.");
        }
#line 2209 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 43: /* argument_list: new_arg  */
#line 525 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            (yyval.argument).num_arg = 1;
            (yyval.argument).flags = (char)(yyvsp[0].number);
        }
#line 2218 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 44: /* argument_list: argument_list ',' new_arg  */
#line 530 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            (yyval.argument) = (yyvsp[-2].argument);
            (yyval.argument).num_arg++;
            (yyval.argument).flags |= (yyvsp[0].number);
        }
#line 2228 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 45: /* type_modifier_list: %empty  */
#line 538 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                                                { (yyval.type) = 0; }
#line 2234 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 46: /* type_modifier_list: L_TYPE_MODIFIER type_modifier_list  */
#line 539 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                                                { (yyval.type) = (yyvsp[-1].type) | (yyvsp[0].type); }
#line 2240 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 47: /* type: type_modifier_list opt_basic_type  */
#line 544 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            (yyval.type) = (yyvsp[-1].type) | (yyvsp[0].type);
            current_type = (yyval.type);
        }
#line 2249 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 48: /* cast: '(' basic_type optional_star ')'  */
#line 551 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                                                { (yyval.type) = (yyvsp[-2].type) | (yyvsp[-1].type); }
#line 2255 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 49: /* opt_basic_type: %empty  */
#line 555 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                        { (yyval.type) = TYPE_UNKNOWN; }
#line 2261 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 53: /* new_name: optional_star identifier  */
#line 566 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if ((current_type & ~NAME_TYPE_MOD) == TYPE_VOID)
                    yyerror("Illegal to declare global variable of type void.");
                define_new_variable((yyvsp[0].string), current_type | (yyvsp[-1].type) | global_modifiers);
                scratch_free((yyvsp[0].string));
            }
#line 2272 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 54: /* new_name: optional_star identifier L_ASSIGN expr0  */
#line 573 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                parse_node_t *expr;
                int type = 0;
                
                if ((yyvsp[-1].number) != F_ASSIGN)
                    yyerror("Only '=' is legal in initializers.");

                /* ignore current_type == 0, which gets a missing type error
                   later anyway */
                if (current_type) {
                    type = (current_type | (yyvsp[-3].type) | global_modifiers) & ~NAME_TYPE_MOD;
                    if ((current_type & ~NAME_TYPE_MOD) == TYPE_VOID)
                        yyerror("Illegal to declare global variable of type void.");
                    if (!compatible_types(type, (yyvsp[0].node)->type)) {
                        char buff[256];
                        char *end = EndOf(buff);
                        char *p;
                        
                        p = strput(buff, end, "Type mismatch ");
                        p = get_two_types(p, end, type, (yyvsp[0].node)->type);
                        p = strput(p, end, " when initializing ");
                        p = strput(p, end, (yyvsp[-2].string));
                        yyerror(buff);
                    }
                }
                switch_to_block(A_INITIALIZER);
                (yyvsp[0].node) = do_promotions((yyvsp[0].node), type);

                CREATE_BINARY_OP(expr, F_VOID_ASSIGN, 0, (yyvsp[0].node), 0);
                CREATE_OPCODE_1(expr->r.expr, F_GLOBAL_LVALUE, 0,
                                define_new_variable((yyvsp[-2].string), current_type | (yyvsp[-3].type) | global_modifiers));
                generate(expr);
                switch_to_block(A_PROGRAM);
                scratch_free((yyvsp[-2].string));
            }
#line 2312 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 55: /* block: '{' block_items '}'  */
#line 612 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.decl) = (yyvsp[-1].decl);
            }
#line 2320 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 56: /* block_items: %empty  */
#line 619 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            (yyval.decl).node = 0;
            (yyval.decl).num = 0;
        }
#line 2329 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 57: /* block_items: block_items block_item  */
#line 624 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            if ((yyvsp[-1].decl).node && (yyvsp[0].decl).node) {
                CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-1].decl).node, (yyvsp[0].decl).node);
            } else (yyval.decl).node = ((yyvsp[-1].decl).node ? (yyvsp[-1].decl).node : (yyvsp[0].decl).node);
            (yyval.decl).num = (yyvsp[-1].decl).num + (yyvsp[0].decl).num;
        }
#line 2340 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 58: /* block_item: statement  */
#line 634 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            (yyval.decl).node = (yyvsp[0].node);
            (yyval.decl).num = 0;
        }
#line 2349 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 60: /* $@4: %empty  */
#line 643 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            if ((yyvsp[0].type) == TYPE_VOID)
                yyerror("Illegal to declare local variable of type void.");
            /* can't do this in basic_type b/c local_name_list contains
             * expr0 which contains cast which contains basic_type
             */
            current_type = (yyvsp[0].type);
        }
#line 2362 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 61: /* local_declaration_stmt: basic_type $@4 local_name_list ';'  */
#line 652 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            (yyval.decl).node = (yyvsp[-1].decl).node;
            (yyval.decl).num = (yyvsp[-1].decl).num;
        }
#line 2371 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 65: /* local_declarations: %empty  */
#line 666 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            (yyval.decl).node = 0;
            (yyval.decl).num = 0;
        }
#line 2380 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 66: /* local_declarations: local_declarations local_declaration_stmt  */
#line 671 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            if ((yyvsp[-1].decl).node && (yyvsp[0].decl).node) {
                CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-1].decl).node, (yyvsp[0].decl).node);
            } else {
                (yyval.decl).node = ((yyvsp[-1].decl).node ? (yyvsp[-1].decl).node : (yyvsp[0].decl).node);
            }
            (yyval.decl).num = (yyvsp[-1].decl).num + (yyvsp[0].decl).num;
        }
#line 2393 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 67: /* new_local_def: optional_star new_local_name  */
#line 684 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            add_local_name((yyvsp[0].string), current_type | (yyvsp[-1].type));
            scratch_free((yyvsp[0].string));
            (yyval.node) = 0;
        }
#line 2403 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 68: /* new_local_def: optional_star new_local_name L_ASSIGN expr0  */
#line 690 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
        {
            int type = (current_type | (yyvsp[-3].type)) & ~NAME_TYPE_MOD;

            if ((yyvsp[-1].number) != F_ASSIGN)
                yyerror("Only '=' is allowed in initializers.");
            if (!compatible_types((yyvsp[0].node)->type, type)) {
                char buff[256];
                char *end = EndOf(buff);
                char *p;
                    
                p = strput(buff, end, "Type mismatch ");
                p = get_two_types(p, end, type, (yyvsp[0].node)->type);
                p = strput(p, end, " when initializing ");
                p = strput(p, end, (yyvsp[-2].string));

                yyerror(buff);
            }

            (yyvsp[0].node) = do_promotions((yyvsp[0].node), type);

            CREATE_UNARY_OP_1((yyval.node), F_VOID_ASSIGN_LOCAL, 0, (yyvsp[0].node),
                        add_local_name((yyvsp[-2].string), current_type | (yyvsp[-3].type)));
            scratch_free((yyvsp[-2].string));
        }
#line 2432 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 69: /* single_new_local_def: basic_type optional_star new_local_name  */
#line 718 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if ((yyvsp[-2].type) == TYPE_VOID)
                    yyerror("Illegal to declare local variable of type void.");

                (yyval.number) = add_local_name((yyvsp[0].string), (yyvsp[-2].type) | (yyvsp[-1].type));
                scratch_free((yyvsp[0].string));
            }
#line 2444 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 70: /* single_new_local_def_with_init: single_new_local_def L_ASSIGN expr0  */
#line 729 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                int type = type_of_locals_ptr[(yyvsp[-2].number)];

                if ((yyvsp[-1].number) != F_ASSIGN)
                    yyerror("Only '=' is allowed in initializers.");
                if (!compatible_types((yyvsp[0].node)->type, type)) {
                    char buff[256];
                    char *end = EndOf(buff);
                    char *p;
                    
                    p = strput(buff, end, "Type mismatch ");
                    p = get_two_types(p, end, type, (yyvsp[0].node)->type);
                    p = strput(p, end, " when initializing.");
                    yyerror(buff);
                }

                (yyvsp[0].node) = do_promotions((yyvsp[0].node), type);

                /* this is an expression */
                CREATE_BINARY_OP((yyval.node), F_ASSIGN, 0, (yyvsp[0].node), 0);
                CREATE_OPCODE_1((yyval.node)->r.expr, F_LOCAL_LVALUE, 0, (yyvsp[-2].number));
            }
#line 2471 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 71: /* local_name_list: new_local_def  */
#line 755 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.decl).node = (yyvsp[0].node);
                (yyval.decl).num = 1;
            }
#line 2480 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 72: /* local_name_list: new_local_def ',' local_name_list  */
#line 760 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if ((yyvsp[-2].node) && (yyvsp[0].decl).node) {
                    CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-2].node), (yyvsp[0].decl).node);
                } else (yyval.decl).node = ((yyvsp[-2].node) ? (yyvsp[-2].node) : (yyvsp[0].decl).node);
                (yyval.decl).num = 1 + (yyvsp[0].decl).num;
            }
#line 2491 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 73: /* statement: comma_expr ';'  */
#line 769 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                                { (yyval.node) = insert_pop_value((yyvsp[-1].node)); }
#line 2497 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 79: /* statement: decl_block  */
#line 776 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
           {
                (yyval.node) = (yyvsp[0].decl).node;
                pop_n_locals((yyvsp[0].decl).num);
            }
#line 2506 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 80: /* statement: ';'  */
#line 781 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = 0;
            }
#line 2514 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 81: /* statement: L_BREAK ';'  */
#line 785 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (context & SPECIAL_CONTEXT) {
                    yyerror("Cannot break out of catch { } or time_expression { }");
                    (yyval.node) = 0;
                } else
                if (context & SWITCH_CONTEXT) {
                    CREATE_CONTROL_JUMP((yyval.node), CJ_BREAK_SWITCH);
                } else
                if (context & LOOP_CONTEXT) {
                    CREATE_CONTROL_JUMP((yyval.node), CJ_BREAK);
                    if (context & LOOP_FOREACH) {
                        parse_node_t *replace;
                        CREATE_STATEMENTS(replace, 0, (yyval.node));
                        CREATE_OPCODE(replace->l.expr, F_EXIT_FOREACH, 0);
                        (yyval.node) = replace;
                    }
                } else {
                    yyerror("break statement outside loop");
                    (yyval.node) = 0;
                }
            }
#line 2540 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 82: /* statement: L_CONTINUE ';'  */
#line 807 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (context & SPECIAL_CONTEXT)
                    yyerror("Cannot continue out of catch { } or time_expression { }");
                else
                if (!(context & LOOP_CONTEXT))
                    yyerror("continue statement outside loop");
                CREATE_CONTROL_JUMP((yyval.node), CJ_CONTINUE);
            }
#line 2553 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 83: /* $@5: %empty  */
#line 819 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyvsp[-3].number) = context;
                context = LOOP_CONTEXT;
            }
#line 2562 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 84: /* while: L_WHILE '(' comma_expr ')' $@5 statement  */
#line 824 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_LOOP((yyval.node), 1, (yyvsp[0].node), 0, optimize_loop_test((yyvsp[-3].node)));
                context = (yyvsp[-5].number);
            }
#line 2571 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 85: /* $@6: %empty  */
#line 832 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyvsp[0].number) = context;
                context = LOOP_CONTEXT;
            }
#line 2580 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 86: /* do: L_DO $@6 statement L_WHILE '(' comma_expr ')' ';'  */
#line 837 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_LOOP((yyval.node), 0, (yyvsp[-5].node), 0, optimize_loop_test((yyvsp[-2].node)));
                context = (yyvsp[-7].number);
            }
#line 2589 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 87: /* $@7: %empty  */
#line 845 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyvsp[-7].number) = context;
                context = LOOP_CONTEXT;
            }
#line 2598 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 88: /* for: L_FOR '(' first_for_expr ';' for_expr ';' for_expr ')' $@7 statement  */
#line 850 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.decl).num = (yyvsp[-7].decl).num; /* number of declarations (0/1) */
                
                (yyvsp[-7].decl).node = insert_pop_value((yyvsp[-7].decl).node);
                (yyvsp[-3].node) = insert_pop_value((yyvsp[-3].node));
                if ((yyvsp[-3].node) && IS_NODE((yyvsp[-3].node), NODE_UNARY_OP, F_INC)
                    && IS_NODE((yyvsp[-3].node)->r.expr, NODE_OPCODE_1, F_LOCAL_LVALUE)) {
                    int64_t lvar = (yyvsp[-3].node)->r.expr->l.number;
                    CREATE_OPCODE_1((yyvsp[-3].node), F_LOOP_INCR, 0, lvar);
                }

                CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-7].decl).node, 0);
                CREATE_LOOP((yyval.decl).node->r.expr, 1, (yyvsp[0].node), (yyvsp[-3].node), optimize_loop_test((yyvsp[-5].node)));

                context = (yyvsp[-9].number);
              }
#line 2619 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 89: /* foreach_var: L_DEFINED_NAME  */
#line 869 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if ((yyvsp[0].ihe)->dn.local_num != -1) {
                    CREATE_OPCODE_1((yyval.decl).node, F_LOCAL_LVALUE, 0, (yyvsp[0].ihe)->dn.local_num);
                } else
                if ((yyvsp[0].ihe)->dn.global_num != -1) {
                    CREATE_OPCODE_1((yyval.decl).node, F_GLOBAL_LVALUE, 0, (yyvsp[0].ihe)->dn.global_num);
                } else {
                    char buf[256];
                    char *end = EndOf(buf);
                    char *p;

                    p = strput(buf, end, "'");
                    p = strput(p, end, (yyvsp[0].ihe)->name);
                    p = strput(p, end, "' is not a local or a global variable.");
                    yyerror(buf);
                    CREATE_OPCODE_1((yyval.decl).node, F_GLOBAL_LVALUE, 0, 0);
                }
                (yyval.decl).num = 0;
            }
#line 2643 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 90: /* foreach_var: single_new_local_def  */
#line 889 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_OPCODE_1((yyval.decl).node, F_LOCAL_LVALUE, 0, (yyvsp[0].number));
                (yyval.decl).num = 1;
            }
#line 2652 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 91: /* foreach_var: L_IDENTIFIER  */
#line 894 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                char buf[256];
                char *end = EndOf(buf);
                char *p;
                
                p = strput(buf, end, "'");
                p = strput(p, end, (yyvsp[0].string));
                p = strput(p, end, "' is not a local or a global variable.");
                yyerror(buf);
                CREATE_OPCODE_1((yyval.decl).node, F_GLOBAL_LVALUE, 0, 0);
                scratch_free((yyvsp[0].string));
                (yyval.decl).num = 0;
            }
#line 2670 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 92: /* foreach_vars: foreach_var  */
#line 911 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_FOREACH((yyval.decl).node, (yyvsp[0].decl).node, 0);
                (yyval.decl).num = (yyvsp[0].decl).num;
            }
#line 2679 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 93: /* foreach_vars: foreach_var ',' foreach_var  */
#line 916 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_FOREACH((yyval.decl).node, (yyvsp[-2].decl).node, (yyvsp[0].decl).node);
                (yyval.decl).num = (yyvsp[-2].decl).num + (yyvsp[0].decl).num;
            }
#line 2688 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 94: /* $@8: %empty  */
#line 924 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyvsp[-3].decl).node->v.expr = (yyvsp[-1].node);
                (yyvsp[-5].number) = context;
                context = LOOP_CONTEXT | LOOP_FOREACH;
            }
#line 2698 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 95: /* foreach: L_FOREACH '(' foreach_vars L_IN expr0 ')' $@8 statement  */
#line 930 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.decl).num = (yyvsp[-5].decl).num;

                CREATE_STATEMENTS((yyval.decl).node, (yyvsp[-5].decl).node, 0);
                CREATE_LOOP((yyval.decl).node->r.expr, 2, (yyvsp[0].node), 0, 0);
                CREATE_OPCODE((yyval.decl).node->r.expr->r.expr, F_NEXT_FOREACH, 0);
                
                context = (yyvsp[-7].number);
            }
#line 2712 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 96: /* for_expr: %empty  */
#line 943 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_NUMBER((yyval.node), 1);
            }
#line 2720 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 98: /* first_for_expr: for_expr  */
#line 951 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                 (yyval.decl).node = (yyvsp[0].node);
                (yyval.decl).num = 0;
            }
#line 2729 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 99: /* first_for_expr: single_new_local_def_with_init  */
#line 956 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.decl).node = (yyvsp[0].node);
                (yyval.decl).num = 1;
            }
#line 2738 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 100: /* $@9: %empty  */
#line 964 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyvsp[-3].number) = context;
                context &= LOOP_CONTEXT;
                context |= SWITCH_CONTEXT;
                (yyvsp[-2].number) = mem_block[A_CASES].current_size;
            }
#line 2749 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 101: /* switch: L_SWITCH '(' comma_expr ')' $@9 '{' local_declarations case switch_block '}'  */
#line 971 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                parse_node_t *node1, *node2;

                if ((yyvsp[-1].node)) {
                    CREATE_STATEMENTS(node1, (yyvsp[-2].node), (yyvsp[-1].node));
                } else node1 = (yyvsp[-2].node);

                if (context & SWITCH_STRINGS) {
                    NODE_NO_LINE(node2, NODE_SWITCH_STRINGS);
                } else if (context & SWITCH_RANGES) {
                    NODE_NO_LINE(node2, NODE_SWITCH_RANGES);
                } else {
                    NODE_NO_LINE(node2, NODE_SWITCH_NUMBERS);
                }
                node2->l.expr = (yyvsp[-7].node);
                node2->r.expr = node1;
                prepare_cases(node2, (size_t)(yyvsp[-8].number));
                context = (yyvsp[-9].number);
                (yyval.node) = node2;
                pop_n_locals((yyvsp[-3].decl).num);
            }
#line 2775 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 102: /* switch_block: case switch_block  */
#line 996 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
          {
               if ((yyvsp[0].node)){
                   CREATE_STATEMENTS((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));
               } else (yyval.node) = (yyvsp[-1].node);
           }
#line 2785 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 103: /* switch_block: statement switch_block  */
#line 1002 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
           {
               if ((yyvsp[0].node)){
                   CREATE_STATEMENTS((yyval.node), (yyvsp[-1].node), (yyvsp[0].node));
               } else (yyval.node) = (yyvsp[-1].node);
           }
#line 2795 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 104: /* switch_block: %empty  */
#line 1008 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
           {
               (yyval.node) = 0;
           }
#line 2803 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 105: /* case: L_CASE case_label ':'  */
#line 1016 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = (yyvsp[-1].node);
                (yyval.node)->v.expr = 0;

                add_to_mem_block(A_CASES, (char *)&((yyvsp[-1].node)), sizeof((yyvsp[-1].node)));
            }
#line 2814 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 106: /* case: L_CASE case_label L_RANGE case_label ':'  */
#line 1023 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if ( (yyvsp[-3].node)->kind != NODE_CASE_NUMBER
                    || (yyvsp[-1].node)->kind != NODE_CASE_NUMBER )
                    yyerror("String case labels not allowed as range bounds");
                if ((yyvsp[-3].node)->r.number > (yyvsp[-1].node)->r.number) break;

                context |= SWITCH_RANGES;

                (yyval.node) = (yyvsp[-3].node);
                (yyval.node)->v.expr = (yyvsp[-1].node);

                add_to_mem_block(A_CASES, (char *)&((yyvsp[-3].node)), sizeof((yyvsp[-3].node)));
            }
#line 2832 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 107: /* case: L_DEFAULT ':'  */
#line 1037 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (context & SWITCH_DEFAULT) {
                    yyerror("Duplicate default");
                    (yyval.node) = 0;
                    break;
                }
                (yyval.node) = new_node();
                (yyval.node)->kind = NODE_DEFAULT;
                (yyval.node)->v.expr = 0;
                add_to_mem_block(A_CASES, (char *)&((yyval.node)), sizeof((yyval.node)));
                context |= SWITCH_DEFAULT;
            }
#line 2849 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 108: /* case_label: constant  */
#line 1053 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if ((context & SWITCH_STRINGS) && (yyvsp[0].pointer_int))
                    yyerror("Mixed case label list not allowed");

                if ((yyvsp[0].pointer_int)) context |= SWITCH_NUMBERS;
                (yyval.node) = new_node();
                (yyval.node)->kind = NODE_CASE_NUMBER;
                (yyval.node)->r.expr = (parse_node_t *)(yyvsp[0].pointer_int);
            }
#line 2863 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 109: /* case_label: string_con1  */
#line 1063 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                int str;
                
                str = store_prog_string_len((yyvsp[0].string_span).str, (yyvsp[0].string_span).len);
                scratch_free((yyvsp[0].string_span).str);
                if (context & SWITCH_NUMBERS)
                    yyerror("Mixed case label list not allowed");
                context |= SWITCH_STRINGS;
                (yyval.node) = new_node();
                (yyval.node)->kind = NODE_CASE_STRING;
                (yyval.node)->r.number = str;
            }
#line 2880 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 110: /* constant: constant '|' constant  */
#line 1079 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) | (yyvsp[0].pointer_int);
            }
#line 2888 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 111: /* constant: constant '^' constant  */
#line 1083 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) ^ (yyvsp[0].pointer_int);
            }
#line 2896 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 112: /* constant: constant '&' constant  */
#line 1087 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) & (yyvsp[0].pointer_int);
            }
#line 2904 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 113: /* constant: constant L_EQ constant  */
#line 1091 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) == (yyvsp[0].pointer_int);
            }
#line 2912 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 114: /* constant: constant L_NE constant  */
#line 1095 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) != (yyvsp[0].pointer_int);
            }
#line 2920 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 115: /* constant: constant L_ORDER constant  */
#line 1099 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                switch((yyvsp[-1].number)){
                    case F_GE: (yyval.pointer_int) = (yyvsp[-2].pointer_int) >= (yyvsp[0].pointer_int); break;
                    case F_LE: (yyval.pointer_int) = (yyvsp[-2].pointer_int) <= (yyvsp[0].pointer_int); break;
                    case F_GT: (yyval.pointer_int) = (yyvsp[-2].pointer_int) >  (yyvsp[0].pointer_int); break;
                }
            }
#line 2932 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 116: /* constant: constant '<' constant  */
#line 1107 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) < (yyvsp[0].pointer_int);
            }
#line 2940 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 117: /* constant: constant L_LSH constant  */
#line 1111 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) << (yyvsp[0].pointer_int);
            }
#line 2948 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 118: /* constant: constant L_RSH constant  */
#line 1115 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) >> (yyvsp[0].pointer_int);
            }
#line 2956 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 119: /* constant: constant '+' constant  */
#line 1119 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) + (yyvsp[0].pointer_int);
            }
#line 2964 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 120: /* constant: constant '-' constant  */
#line 1123 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) - (yyvsp[0].pointer_int);
            }
#line 2972 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 121: /* constant: constant '*' constant  */
#line 1127 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (yyvsp[-2].pointer_int) * (yyvsp[0].pointer_int);
            }
#line 2980 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 122: /* constant: constant '%' constant  */
#line 1131 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if ((yyvsp[0].pointer_int)) (yyval.pointer_int) = (yyvsp[-2].pointer_int) % (yyvsp[0].pointer_int); else yyerror("Modulo by zero");
            }
#line 2988 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 123: /* constant: constant '/' constant  */
#line 1135 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if ((yyvsp[0].pointer_int)) (yyval.pointer_int) = (yyvsp[-2].pointer_int) / (yyvsp[0].pointer_int); else yyerror("Division by zero");
            }
#line 2996 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 124: /* constant: '(' constant ')'  */
#line 1139 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (yyvsp[-1].pointer_int);
            }
#line 3004 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 125: /* constant: L_NUMBER  */
#line 1143 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (intptr_t)(yyvsp[0].number);
            }
#line 3012 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 126: /* constant: '-' L_NUMBER  */
#line 1147 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (intptr_t)(-(yyvsp[0].number));
            }
#line 3020 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 127: /* constant: L_NOT L_NUMBER  */
#line 1151 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = !(yyvsp[0].number);
            }
#line 3028 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 128: /* constant: '~' L_NUMBER  */
#line 1155 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.pointer_int) = (intptr_t)(~(yyvsp[0].number));
            }
#line 3036 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 129: /* comma_expr: expr0  */
#line 1162 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = (yyvsp[0].node);
            }
#line 3044 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 130: /* comma_expr: comma_expr ',' expr0  */
#line 1166 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_TWO_VALUES((yyval.node), (yyvsp[0].node)->type, insert_pop_value((yyvsp[-2].node)), (yyvsp[0].node));
            }
#line 3052 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 131: /* expr0: lvalue L_ASSIGN expr0  */
#line 1173 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                parse_node_t *l = (yyvsp[-2].node), *r = (yyvsp[0].node);
                /* set this up here so we can change it below */
                
                CREATE_BINARY_OP((yyval.node), (yyvsp[-1].number), r->type, r, l);

                if (exact_types && !compatible_types(r->type, l->type) &&
                    !((yyvsp[-1].number) == F_ADD_EQ && r->type == TYPE_STRING && COMP_TYPE(l->type, TYPE_NUMBER))) {
                    char buf[256];
                    char *end = EndOf(buf);
                    char *p;
                    
                    p = strput(buf, end, "Bad assignment ");
                    p = get_two_types(p, end, l->type, r->type);
                    p = strput(p, end, ".");
                    yyerror(buf);
                }

                (yyval.node)->l.expr = do_promotions(r, l->type);
            }
#line 3077 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 132: /* expr0: error L_ASSIGN expr0  */
#line 1194 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                yyerror("Illegal LHS");
                CREATE_ERROR((yyval.node));
            }
#line 3086 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 133: /* expr0: expr0 '?' expr0 ':' expr0  */
#line 1199 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                parse_node_t *p1 = (yyvsp[-2].node), *p2 = (yyvsp[0].node);

                if (exact_types && !compatible_types2(p1->type, p2->type)) {
                    char buf[256];
                    char *end = EndOf(buf);
                    char *p;
                    
                    p = strput(buf, end, "Types in ?: do not match ");
                    p = get_two_types(p, end, p1->type, p2->type);
                    p = strput(p, end, ".");
                    yywarn(buf);
                }

                /* optimize if last expression did F_NOT */
                if (IS_NODE((yyvsp[-4].node), NODE_UNARY_OP, F_NOT)) {
                    /* !a ? b : c  --> a ? c : b */
                    CREATE_IF((yyval.node), (yyvsp[-4].node)->r.expr, p2, p1);
                } else {
                    CREATE_IF((yyval.node), (yyvsp[-4].node), p1, p2);
                }
                (yyval.node)->type = ((p1->type == p2->type) ? p1->type : TYPE_ANY);
            }
#line 3114 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 134: /* expr0: expr0 L_LOR expr0  */
#line 1223 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_LAND_LOR((yyval.node), F_LOR, (yyvsp[-2].node), (yyvsp[0].node));
                if (IS_NODE((yyvsp[-2].node), NODE_LAND_LOR, F_LOR))
                    (yyvsp[-2].node)->kind = NODE_BRANCH_LINK;
            }
#line 3124 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 135: /* expr0: expr0 L_LAND expr0  */
#line 1229 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_LAND_LOR((yyval.node), F_LAND, (yyvsp[-2].node), (yyvsp[0].node));
                if (IS_NODE((yyvsp[-2].node), NODE_LAND_LOR, F_LAND))
                    (yyvsp[-2].node)->kind = NODE_BRANCH_LINK;
            }
#line 3134 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 136: /* expr0: expr0 '|' expr0  */
#line 1235 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (is_boolean((yyvsp[-2].node)) && is_boolean((yyvsp[0].node)))
                    yywarn("bitwise operation on boolean values.");
                (yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_OR, "|");		
            }
#line 3144 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 137: /* expr0: expr0 '^' expr0  */
#line 1241 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_XOR, "^");
            }
#line 3152 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 138: /* expr0: expr0 '&' expr0  */
#line 1245 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                lpc_type_t t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;
                if (is_boolean((yyvsp[-2].node)) && is_boolean((yyvsp[0].node)))
                    yywarn("bitwise operation on boolean values.");
                if ((t1 & TYPE_MOD_ARRAY) || (t3 & TYPE_MOD_ARRAY)) {
                    if (t1 != t3) {
                        if ((t1 != TYPE_ANY) && (t3 != TYPE_ANY) &&
                            !(t1 & t3 & TYPE_MOD_ARRAY)) {
                            char buf[256];
                            char *end = EndOf(buf);
                            char *p;
                            
                            p = strput(buf, end, "Incompatible types for & ");
                            p = get_two_types(p, end, t1, t3);
                            p = strput(p, end, ".");
                            yyerror(buf);
                        }
                        t1 = TYPE_ANY | TYPE_MOD_ARRAY;
                    } 
                    CREATE_BINARY_OP((yyval.node), F_AND, t1, (yyvsp[-2].node), (yyvsp[0].node));
                } else (yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_AND, "&");
            }
#line 3179 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 139: /* expr0: expr0 L_EQ expr0  */
#line 1268 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (exact_types && !compatible_types2((yyvsp[-2].node)->type, (yyvsp[0].node)->type)){
                    char buf[256];
                    char *end = EndOf(buf);
                    char *p;
                    
                    p = strput(buf, end, "== always false because of incompatible types ");
                    p = get_two_types(p, end, (yyvsp[-2].node)->type, (yyvsp[0].node)->type);
                    p = strput(p, end, ".");
                    yyerror(buf);
                }
                /* x == 0 -> !x */
                if (IS_NODE((yyvsp[-2].node), NODE_NUMBER, 0)) {
                    CREATE_UNARY_OP((yyval.node), F_NOT, TYPE_NUMBER, (yyvsp[0].node));
                } else
                if (IS_NODE((yyvsp[0].node), NODE_NUMBER, 0)) {
                    CREATE_UNARY_OP((yyval.node), F_NOT, TYPE_NUMBER, (yyvsp[-2].node));
                } else {
                    CREATE_BINARY_OP((yyval.node), F_EQ, TYPE_NUMBER, (yyvsp[-2].node), (yyvsp[0].node));
                }
            }
#line 3205 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 140: /* expr0: expr0 L_NE expr0  */
#line 1290 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (exact_types && !compatible_types2((yyvsp[-2].node)->type, (yyvsp[0].node)->type)){
                    char buf[256];
                    char *end = EndOf(buf);
                    char *p;

                    p = strput(buf, end, "!= always true because of incompatible types ");
                    p = get_two_types(p, end, (yyvsp[-2].node)->type, (yyvsp[0].node)->type);
                    p = strput(p, end, ".");
                    yyerror(buf);
                }
                CREATE_BINARY_OP((yyval.node), F_NE, TYPE_NUMBER, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 3223 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 141: /* expr0: expr0 L_ORDER expr0  */
#line 1304 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (exact_types) {
                    int t1 = (yyvsp[-2].node)->type;
                    int t3 = (yyvsp[0].node)->type;

                    if (!COMP_TYPE(t1, TYPE_NUMBER) 
                        && !COMP_TYPE(t1, TYPE_STRING)) {
                        char buf[256];
                        char *end = EndOf(buf);
                        char *p;
                        
                        p = strput(buf, end, "Bad left argument to '");
                        p = strput(p, end, query_opcode_name((int)(yyvsp[-1].number)));
                        p = strput(p, end, "' : \"");
                        p = get_type_name(p, end, t1);
                        p = strput(p, end, "\"");
                        yyerror(buf);
                    } else if (!COMP_TYPE(t3, TYPE_NUMBER) 
                               && !COMP_TYPE(t3, TYPE_STRING)) {
                        char buf[256];
                        char *end = EndOf(buf);
                        char *p;
                        
                        p = strput(buf, end, "Bad right argument to '");
                        p = strput(p, end, query_opcode_name((int)(yyvsp[-1].number)));
                        p = strput(p, end, "' : \"");
                        p = get_type_name(p, end, t3);
                        p = strput(p, end, "\"");
                        yyerror(buf);
                    } else if (!compatible_types2(t1,t3)) {
                        char buf[256];
                        char *end = EndOf(buf);
                        char *p;
                        
                        p = strput(buf, end, "Arguments to ");
                        p = strput(p, end, query_opcode_name((int)(yyvsp[-1].number)));
                        p = strput(p, end, " do not have compatible types : ");
                        p = get_two_types(p, end, t1, t3);
                        yyerror(buf);
                    }
                }
                CREATE_BINARY_OP((yyval.node), (yyvsp[-1].number), TYPE_NUMBER, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 3271 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 142: /* expr0: expr0 '<' expr0  */
#line 1348 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (exact_types) {
                    int t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

                    if (!COMP_TYPE(t1, TYPE_NUMBER) 
                        && !COMP_TYPE(t1, TYPE_STRING)) {
                        char buf[256];
                        char *end = EndOf(buf);
                        char *p;
                        
                        p = strput(buf, end, "Bad left argument to '<' : \"");
                        p = get_type_name(p, end, t1);
                        p = strput(p, end, "\"");
                        yyerror(buf);
                    } else if (!COMP_TYPE(t3, TYPE_NUMBER)
                               && !COMP_TYPE(t3, TYPE_STRING)) {
                        char buf[200];
                        char *end = EndOf(buf);
                        char *p;
                        
                        p = strput(buf, end, "Bad right argument to '<' : \"");
                        p = get_type_name(p, end, t3);
                        p = strput(p, end, "\"");
                        yyerror(buf);
                    } else if (!compatible_types2(t1,t3)) {
                        char buf[256];
                        char *end = EndOf(buf);
                        char *p;
                        
                        p = strput(buf, end, "Arguments to < do not have compatible types : ");
                        p = get_two_types(p, end, t1, t3);
                        yyerror(buf);
                    }
                }
                CREATE_BINARY_OP((yyval.node), F_LT, TYPE_NUMBER, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 3312 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 143: /* expr0: expr0 L_LSH expr0  */
#line 1385 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_LSH, "<<");
            }
#line 3320 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 144: /* expr0: expr0 L_RSH expr0  */
#line 1389 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_RSH, ">>");
            }
#line 3328 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 145: /* expr0: expr0 '+' expr0  */
#line 1393 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                lpc_type_t result_type;

                if (exact_types) {
                    lpc_type_t t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

                    if (t1 == t3){
#ifdef CAST_CALL_OTHERS
                        if (t1 == TYPE_UNKNOWN){
                            yyerror("Bad arguments to '+' (unknown vs unknown)");
                            result_type = TYPE_ANY;
                        } else
#endif
                            result_type = t1;
                    }
                    else if (t1 == TYPE_ANY) {
                        if (t3 == TYPE_FUNCTION) {
                            yyerror("Bad right argument to '+' (function)");
                            result_type = TYPE_ANY;
                        } else result_type = t3;
                    } else if (t3 == TYPE_ANY) {
                        if (t1 == TYPE_FUNCTION) {
                            yyerror("Bad left argument to '+' (function)");
                            result_type = TYPE_ANY;
                        } else result_type = t1;
                    } else {
                        switch(t1) {
                            case TYPE_STRING:
                            {
                                if (t3 == TYPE_REAL || t3 == TYPE_NUMBER){
                                    result_type = TYPE_STRING;
                                } else goto add_error;
                                break;
                            }
                            case TYPE_NUMBER:
                            {
                                if (t3 == TYPE_REAL || t3 == TYPE_STRING)
                                    result_type = t3;
                                else goto add_error;
                                break;
                            }
                        case TYPE_REAL:
                            {
                                if (t3 == TYPE_NUMBER) result_type = TYPE_REAL;
                                else if (t3 == TYPE_STRING) result_type = TYPE_STRING;
                                else goto add_error;
                                break;
                            }
                            default:
                            {
                                if (t1 & t3 & TYPE_MOD_ARRAY) {
                                    result_type = TYPE_ANY|TYPE_MOD_ARRAY;
                                    break;
                                }
add_error:
                                {
                                    char buf[256];
                                    char *end = EndOf(buf);
                                    char *p;
                                    
                                    p = strput(buf, end, "Invalid argument types to '+' ");
                                    p = get_two_types(p, end, t1, t3);
                                    yyerror(buf);
                                    result_type = TYPE_ANY;
                                }
                            }
                        }
                    }
                } else 
                    result_type = TYPE_ANY;

                switch ((yyvsp[-2].node)->kind) {
                case NODE_NUMBER:
                    /* 0 + X */
                    if ((yyvsp[-2].node)->v.number == 0 &&
                        ((yyvsp[0].node)->type == TYPE_NUMBER || (yyvsp[0].node)->type == TYPE_REAL)) {
                        (yyval.node) = (yyvsp[0].node);
                        break;
                    }
                    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyvsp[-2].node)->v.number += (yyvsp[0].node)->v.number;
                        break;
                    }
                    if ((yyvsp[0].node)->kind == NODE_REAL) {
                        (yyval.node) = (yyvsp[0].node);
                        (yyvsp[0].node)->v.real += (yyvsp[-2].node)->v.number;
                        break;
                    }
                    /* swapping the nodes may help later constant folding */
                    if ((yyvsp[0].node)->type != TYPE_STRING && (yyvsp[0].node)->type != TYPE_ANY)
                        CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[0].node), (yyvsp[-2].node));
                    else
                        CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[-2].node), (yyvsp[0].node));
                    break;
                case NODE_REAL:
                    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyvsp[-2].node)->v.real += (yyvsp[0].node)->v.number;
                        break;
                    }
                    if ((yyvsp[0].node)->kind == NODE_REAL) {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyvsp[-2].node)->v.real += (yyvsp[0].node)->v.real;
                        break;
                    }
                    /* swapping the nodes may help later constant folding */
                    if ((yyvsp[0].node)->type != TYPE_STRING && (yyvsp[0].node)->type != TYPE_ANY)
                        CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[0].node), (yyvsp[-2].node));
                    else
                        CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[-2].node), (yyvsp[0].node));
                    break;
                case NODE_STRING:
                    if ((yyvsp[0].node)->kind == NODE_STRING) {
                        /* Combine strings */
                        int n1, n2;
                        char *s_new, *s1, *s2;
                        size_t l1, l2;

                        n1 = (int)(yyvsp[-2].node)->v.number;
                        n2 = (int)(yyvsp[0].node)->v.number;
                        s1 = PROG_STRING(n1);
                        s2 = PROG_STRING(n2);
                        l1 = SHARED_STRLEN(s1);
                        l2 = SHARED_STRLEN(s2);
                        s_new = (char *)DXALLOC(l1 + l2 + 1, TAG_COMPILER, "combine string");
                        memcpy(s_new, s1, l1);
                        memcpy(s_new + l1, s2, l2);
                        s_new[l1 + l2] = '\0';
                        /* free old strings (ordering may help shrink table) */
                        if (n1 > n2) {
                            free_prog_string(n1); free_prog_string(n2);
                        } else {
                            free_prog_string(n2); free_prog_string(n1);
                        }
                        (yyval.node) = (yyvsp[-2].node);
                        (yyval.node)->v.number = store_prog_string_len(s_new, l1 + l2);
                        FREE(s_new);
                        break;
                    }
                    CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[-2].node), (yyvsp[0].node));
                    break;
                default:
                    /* X + 0 */
                    if (IS_NODE((yyvsp[0].node), NODE_NUMBER, 0) &&
                        ((yyvsp[-2].node)->type == TYPE_NUMBER || (yyvsp[-2].node)->type == TYPE_REAL)) {
                        (yyval.node) = (yyvsp[-2].node);
                        break;
                    }
                    CREATE_BINARY_OP((yyval.node), F_ADD, result_type, (yyvsp[-2].node), (yyvsp[0].node));
                    break;
                }
            }
#line 3486 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 146: /* expr0: expr0 '-' expr0  */
#line 1547 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                lpc_type_t result_type;

                if (exact_types) {
                    lpc_type_t t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

                    if (t1 == t3){
                        switch(t1){
                            case TYPE_ANY:
                            case TYPE_NUMBER:
                            case TYPE_REAL:
                                result_type = t1;
                                break;
                            default:
                                if (!(t1 & TYPE_MOD_ARRAY)){
                                    type_error("Bad argument number 1 to '-'", t1);
                                    result_type = TYPE_ANY;
                                } else result_type = t1;
                        }
                    } else if (t1 == TYPE_ANY){
                        switch(t3){
                            case TYPE_REAL:
                            case TYPE_NUMBER:
                                result_type = t3;
                                break;
                            default:
                                if (!(t3 & TYPE_MOD_ARRAY)){
                                    type_error("Bad argument number 2 to '-'", t3);
                                    result_type = TYPE_ANY;
                                } else result_type = t3;
                        }
                    } else if (t3 == TYPE_ANY){
                        switch(t1){
                            case TYPE_REAL:
                            case TYPE_NUMBER:
                                result_type = t1;
                                break;
                            default:
                                if (!(t1 & TYPE_MOD_ARRAY)){
                                    type_error("Bad argument number 1 to '-'", t1);
                                    result_type = TYPE_ANY;
                                } else result_type = t1;
                        }
                    } else if ((t1 == TYPE_REAL && t3 == TYPE_NUMBER) ||
                               (t3 == TYPE_REAL && t1 == TYPE_NUMBER)){
                        result_type = TYPE_REAL;
                    } else if (t1 & t3 & TYPE_MOD_ARRAY){
                        result_type = TYPE_MOD_ARRAY|TYPE_ANY;
                    } else {
                        char buf[256];
                        char *end = EndOf(buf);
                        char *p;
                        
                        p = strput(buf, end, "Invalid types to '-' ");
                        p = get_two_types(p, end, t1, t3);
                        yyerror(buf);
                        result_type = TYPE_ANY;
                    }
                } else result_type = TYPE_ANY;
                
                switch ((yyvsp[-2].node)->kind) {
                case NODE_NUMBER:
                    if ((yyvsp[-2].node)->v.number == 0) {
                        CREATE_UNARY_OP((yyval.node), F_NEGATE, (yyvsp[0].node)->type, (yyvsp[0].node));
                    } else if ((yyvsp[0].node)->kind == NODE_NUMBER) {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyvsp[-2].node)->v.number -= (yyvsp[0].node)->v.number;
                    } else if ((yyvsp[0].node)->kind == NODE_REAL) {
                        (yyval.node) = (yyvsp[0].node);
                        (yyvsp[0].node)->v.real = (yyvsp[-2].node)->v.number - (yyvsp[0].node)->v.real;
                    } else {
                        CREATE_BINARY_OP((yyval.node), F_SUBTRACT, result_type, (yyvsp[-2].node), (yyvsp[0].node));
                    }
                    break;
                case NODE_REAL:
                    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyvsp[-2].node)->v.real -= (yyvsp[0].node)->v.number;
                    } else if ((yyvsp[0].node)->kind == NODE_REAL) {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyvsp[-2].node)->v.real -= (yyvsp[0].node)->v.real;
                    } else {
                        CREATE_BINARY_OP((yyval.node), F_SUBTRACT, result_type, (yyvsp[-2].node), (yyvsp[0].node));
                    }
                    break;
                default:
                    /* optimize X-0 */
                    if (IS_NODE((yyvsp[0].node), NODE_NUMBER, 0)) {
                        (yyval.node) = (yyvsp[-2].node);
                    } 
                    CREATE_BINARY_OP((yyval.node), F_SUBTRACT, result_type, (yyvsp[-2].node), (yyvsp[0].node));
                }
            }
#line 3584 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 147: /* expr0: expr0 '*' expr0  */
#line 1641 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                lpc_type_t result_type;

                if (exact_types){
                    lpc_type_t t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

                    if (t1 == t3){
                        switch(t1){
                            case TYPE_MAPPING:
                            case TYPE_ANY:
                            case TYPE_NUMBER:
                            case TYPE_REAL:
                                result_type = t1;
                                break;
                        default:
                                type_error("Bad argument number 1 to '*'", t1);
                                result_type = TYPE_ANY;
                        }
                    } else if (t1 == TYPE_ANY || t3 == TYPE_ANY){
                        lpc_type_t t = (t1 == TYPE_ANY) ? t3 : t1;
                        switch(t){
                            case TYPE_NUMBER:
                            case TYPE_REAL:
                            case TYPE_MAPPING:
                                result_type = t;
                                break;
                            default:
                                type_error((t1 == TYPE_ANY) ?
                                           "Bad argument number 2 to '*'" :
                                           "Bad argument number 1 to '*'",
                                           t);
                                result_type = TYPE_ANY;
                        }
                    } else if ((t1 == TYPE_NUMBER && t3 == TYPE_REAL) ||
                               (t1 == TYPE_REAL && t3 == TYPE_NUMBER)){
                        result_type = TYPE_REAL;
                    } else {
                        char buf[256];
                        char *end = EndOf(buf);
                        char *p;
                        
                        p = strput(buf, end, "Invalid types to '*' ");
                        p = get_two_types(p, end, t1, t3);
                        yyerror(buf);
                        result_type = TYPE_ANY;
                    }
                } else result_type = TYPE_ANY;

                switch ((yyvsp[-2].node)->kind) {
                case NODE_NUMBER:
                    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyval.node)->v.number *= (yyvsp[0].node)->v.number;
                        break;
                    }
                    if ((yyvsp[0].node)->kind == NODE_REAL) {
                        (yyval.node) = (yyvsp[0].node);
                        (yyvsp[0].node)->v.real *= (yyvsp[-2].node)->v.number;
                        break;
                    }
                    CREATE_BINARY_OP((yyval.node), F_MULTIPLY, result_type, (yyvsp[0].node), (yyvsp[-2].node));
                    break;
                case NODE_REAL:
                    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyvsp[-2].node)->v.real *= (yyvsp[0].node)->v.number;
                        break;
                    }
                    if ((yyvsp[0].node)->kind == NODE_REAL) {
                        (yyval.node) = (yyvsp[-2].node);
                        (yyvsp[-2].node)->v.real *= (yyvsp[0].node)->v.real;
                        break;
                    }
                    CREATE_BINARY_OP((yyval.node), F_MULTIPLY, result_type, (yyvsp[0].node), (yyvsp[-2].node));
                    break;
                default:
                    CREATE_BINARY_OP((yyval.node), F_MULTIPLY, result_type, (yyvsp[-2].node), (yyvsp[0].node));
                }
            }
#line 3668 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 148: /* expr0: expr0 '%' expr0  */
#line 1721 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = binary_int_op((yyvsp[-2].node), (yyvsp[0].node), F_MOD, "%");
            }
#line 3676 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 149: /* expr0: expr0 '/' expr0  */
#line 1725 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                lpc_type_t result_type;

                if (exact_types){
                    lpc_type_t t1 = (yyvsp[-2].node)->type, t3 = (yyvsp[0].node)->type;

                    if (t1 == t3){
                        switch(t1){
                            case TYPE_NUMBER:
                            case TYPE_REAL:
                        case TYPE_ANY:
                                result_type = t1;
                                break;
                            default:
                                type_error("Bad argument 1 to '/'", t1);
                                result_type = TYPE_ANY;
                        }
                    } else if (t1 == TYPE_ANY || t3 == TYPE_ANY){
                        lpc_type_t t = (t1 == TYPE_ANY) ? t3 : t1;
                        if (t == TYPE_REAL || t == TYPE_NUMBER)
                            result_type = t; 
                        else {
                            type_error(t1 == TYPE_ANY ?
                                       "Bad argument 2 to '/'" :
                                       "Bad argument 1 to '/'", t);
                            result_type = TYPE_ANY;
                        }
                    } else if ((t1 == TYPE_NUMBER && t3 == TYPE_REAL) ||
                               (t1 == TYPE_REAL && t3 == TYPE_NUMBER)) {
                        result_type = TYPE_REAL;
                    } else {
                        char buf[256];
                        char *end = EndOf(buf);
                        char *p;
                        
                        p = strput(buf, end, "Invalid types to '/' ");
                        p = get_two_types(p, end, t1, t3);
                        yyerror(buf);
                        result_type = TYPE_ANY;
                    }
                } else result_type = TYPE_ANY;		    

                /* constant expressions */
                switch ((yyvsp[-2].node)->kind) {
                case NODE_NUMBER:
                    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
                        if ((yyvsp[0].node)->v.number == 0) {
                            yyerror("Divide by zero in constant");
                            (yyval.node) = (yyvsp[-2].node);
                            break;
                        }
                        (yyval.node) = (yyvsp[-2].node);
                        (yyvsp[-2].node)->v.number /= (yyvsp[0].node)->v.number;
                        break;
                    }
                    if ((yyvsp[0].node)->kind == NODE_REAL) {
                        if ((yyvsp[0].node)->v.real == 0.0) {
                            yyerror("Divide by zero in constant");
                            (yyval.node) = (yyvsp[-2].node);
                            break;
                        }
                        (yyval.node) = (yyvsp[0].node);
                        (yyvsp[0].node)->v.real = ((yyvsp[-2].node)->v.number / (yyvsp[0].node)->v.real);
                        break;
                    }
                    CREATE_BINARY_OP((yyval.node), F_DIVIDE, result_type, (yyvsp[-2].node), (yyvsp[0].node));
                    break;
                case NODE_REAL:
                    if ((yyvsp[0].node)->kind == NODE_NUMBER) {
                        if ((yyvsp[0].node)->v.number == 0) {
                            yyerror("Divide by zero in constant");
                            (yyval.node) = (yyvsp[-2].node);
                            break;
                        }
                        (yyval.node) = (yyvsp[-2].node);
                        (yyvsp[-2].node)->v.real /= (yyvsp[0].node)->v.number;
                        break;
                    }
                    if ((yyvsp[0].node)->kind == NODE_REAL) {
                        if ((yyvsp[0].node)->v.real == 0.0) {
                            yyerror("Divide by zero in constant");
                            (yyval.node) = (yyvsp[-2].node);
                            break;
                        }
                        (yyval.node) = (yyvsp[-2].node);
                        (yyvsp[-2].node)->v.real /= (yyvsp[0].node)->v.real;
                        break;
                    }
                    CREATE_BINARY_OP((yyval.node), F_DIVIDE, result_type, (yyvsp[-2].node), (yyvsp[0].node));
                    break;
                default:
                    CREATE_BINARY_OP((yyval.node), F_DIVIDE, result_type, (yyvsp[-2].node), (yyvsp[0].node));
                }
            }
#line 3775 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 150: /* expr0: cast expr0  */
#line 1820 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = (yyvsp[0].node);
                (yyval.node)->type = (lpc_type_t)(yyvsp[-1].type);

                if (exact_types &&
                    (yyvsp[0].node)->type != (yyvsp[-1].type) &&
                    (yyvsp[0].node)->type != TYPE_ANY && 
                    (yyvsp[0].node)->type != TYPE_UNKNOWN &&
                    (yyvsp[-1].type) != TYPE_VOID) {
                    char buf[256];
                    char *end = EndOf(buf);
                    char *p;
                    
                    p = strput(buf, end, "Cannot cast ");
                    p = get_type_name(p, end, (yyvsp[0].node)->type);
                    p = strput(p, end, "to ");
                    p = get_type_name(p, end, (yyvsp[-1].type));
                    yyerror(buf);
                }
            }
#line 3800 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 151: /* expr0: L_INC lvalue  */
#line 1841 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_UNARY_OP((yyval.node), F_PRE_INC, 0, (yyvsp[0].node));
                if (exact_types){
                    switch((yyvsp[0].node)->type){
                        case TYPE_NUMBER:
                        case TYPE_ANY:
                        case TYPE_REAL:
                        {
                            (yyval.node)->type = (yyvsp[0].node)->type;
                            break;
                        }

                        default:
                        {
                            (yyval.node)->type = TYPE_ANY;
                            type_error("Bad argument 1 to ++x", (yyvsp[0].node)->type);
                        }
                    }
                } else (yyval.node)->type = TYPE_ANY;
            }
#line 3825 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 152: /* expr0: L_DEC lvalue  */
#line 1862 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_UNARY_OP((yyval.node), F_PRE_DEC, 0, (yyvsp[0].node));
                if (exact_types){
                    switch((yyvsp[0].node)->type){
                        case TYPE_NUMBER:
                        case TYPE_ANY:
                        case TYPE_REAL:
                        {
                            (yyval.node)->type = (yyvsp[0].node)->type;
                            break;
                        }

                        default:
                        {
                            (yyval.node)->type = TYPE_ANY;
                            type_error("Bad argument 1 to --x", (yyvsp[0].node)->type);
                        }
                    }
                } else (yyval.node)->type = TYPE_ANY;

            }
#line 3851 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 153: /* expr0: L_NOT expr0  */
#line 1884 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if ((yyvsp[0].node)->kind == NODE_NUMBER) {
                    (yyval.node) = (yyvsp[0].node);
                    (yyval.node)->v.number = !((yyval.node)->v.number);
                } else {
                    CREATE_UNARY_OP((yyval.node), F_NOT, TYPE_NUMBER, (yyvsp[0].node));
                }
            }
#line 3864 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 154: /* expr0: '~' expr0  */
#line 1893 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (exact_types && !IS_TYPE((yyvsp[0].node)->type, TYPE_NUMBER))
                    type_error("Bad argument to ~", (yyvsp[0].node)->type);
                if ((yyvsp[0].node)->kind == NODE_NUMBER) {
                    (yyval.node) = (yyvsp[0].node);
                    (yyval.node)->v.number = ~(yyval.node)->v.number;
                } else {
                    CREATE_UNARY_OP((yyval.node), F_COMPL, TYPE_NUMBER, (yyvsp[0].node));
                }
            }
#line 3879 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 155: /* expr0: '-' expr0  */
#line 1904 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                lpc_type_t result_type;
                if (exact_types){
                    lpc_type_t t = (yyvsp[0].node)->type;
                    if (!COMP_TYPE(t, TYPE_NUMBER)){
                        type_error("Bad argument to unary '-'", t);
                        result_type = TYPE_ANY;
                    } else result_type = t;
                } else result_type = TYPE_ANY;

                switch ((yyvsp[0].node)->kind) {
                case NODE_NUMBER:
                    (yyval.node) = (yyvsp[0].node);
                    (yyval.node)->v.number = -(yyval.node)->v.number;
                    break;
                case NODE_REAL:
                    (yyval.node) = (yyvsp[0].node);
                    (yyval.node)->v.real = -(yyval.node)->v.real;
                    break;
                default:
                    CREATE_UNARY_OP((yyval.node), F_NEGATE, result_type, (yyvsp[0].node));
                }
            }
#line 3907 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 156: /* expr0: lvalue L_INC  */
#line 1928 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_UNARY_OP((yyval.node), F_POST_INC, 0, (yyvsp[-1].node));
                (yyval.node)->v.number = F_POST_INC;
                if (exact_types){
                    switch((yyvsp[-1].node)->type){
                        case TYPE_NUMBER:
                    case TYPE_ANY:
                        case TYPE_REAL:
                        {
                            (yyval.node)->type = (yyvsp[-1].node)->type;
                            break;
                        }

                        default:
                        {
                            (yyval.node)->type = TYPE_ANY;
                            type_error("Bad argument 1 to x++", (yyvsp[-1].node)->type);
                        }
                    }
                } else (yyval.node)->type = TYPE_ANY;
            }
#line 3933 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 157: /* expr0: lvalue L_DEC  */
#line 1950 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_UNARY_OP((yyval.node), F_POST_DEC, 0, (yyvsp[-1].node));
                if (exact_types){
                    switch((yyvsp[-1].node)->type){
                    case TYPE_NUMBER:
                    case TYPE_ANY:
                    case TYPE_REAL:
                    {
                        (yyval.node)->type = (yyvsp[-1].node)->type;
                        break;
                    }

                    default:
                    {
                        (yyval.node)->type = TYPE_ANY;
                        type_error("Bad argument 1 to x--", (yyvsp[-1].node)->type);
                    }
                    }
                } else (yyval.node)->type = TYPE_ANY;
            }
#line 3958 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 164: /* return: L_RETURN ';'  */
#line 1980 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (exact_types && !IS_TYPE(exact_types, TYPE_VOID))
                    yywarn("Non-void functions must return a value.");
                CREATE_RETURN((yyval.node), 0);
            }
#line 3968 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 165: /* return: L_RETURN comma_expr ';'  */
#line 1986 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (exact_types && !compatible_types((yyvsp[-1].node)->type, exact_types & ~NAME_TYPE_MOD)) {
                    char buf[256];
                    char *end = EndOf(buf);
                    char *p;
                    
                    p = strput(buf, end, "Type of returned value doesn't match function return type ");
                    p = get_two_types(p, end, (yyvsp[-1].node)->type, exact_types & ~NAME_TYPE_MOD);
                    yyerror(buf);
                }
                if (IS_NODE((yyvsp[-1].node), NODE_NUMBER, 0)) {
                    CREATE_RETURN((yyval.node), 0);
                } else {
                    CREATE_RETURN((yyval.node), (yyvsp[-1].node));
                }
            }
#line 3989 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 166: /* expr_list: %empty  */
#line 2006 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_EXPR_LIST((yyval.node), 0);
            }
#line 3997 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 167: /* expr_list: expr_list2  */
#line 2010 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_EXPR_LIST((yyval.node), (yyvsp[0].node));
            }
#line 4005 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 168: /* expr_list: expr_list2 ','  */
#line 2014 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_EXPR_LIST((yyval.node), (yyvsp[-1].node));
            }
#line 4013 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 169: /* expr_list_node: expr0  */
#line 2021 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_EXPR_NODE((yyval.node), (yyvsp[0].node), 0);
            }
#line 4021 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 170: /* expr_list_node: expr0 L_DOT_DOT_DOT  */
#line 2025 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_EXPR_NODE((yyval.node), (yyvsp[-1].node), 1);
            }
#line 4029 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 171: /* expr_list2: expr_list_node  */
#line 2032 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyvsp[0].node)->kind = 1;

                (yyval.node) = (yyvsp[0].node);
            }
#line 4039 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 172: /* expr_list2: expr_list2 ',' expr_list_node  */
#line 2038 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyvsp[0].node)->kind = 0;

                (yyval.node) = (yyvsp[-2].node);
                (yyval.node)->kind++;
                (yyval.node)->l.expr->r.expr = (yyvsp[0].node);
                (yyval.node)->l.expr = (yyvsp[0].node);
            }
#line 4052 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 173: /* expr_list3: %empty  */
#line 2050 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                /* this is a dummy node */
                CREATE_EXPR_LIST((yyval.node), 0);
            }
#line 4061 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 174: /* expr_list3: expr_list4  */
#line 2055 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_EXPR_LIST((yyval.node), (yyvsp[0].node));
            }
#line 4069 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 175: /* expr_list3: expr_list4 ','  */
#line 2059 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_EXPR_LIST((yyval.node), (yyvsp[-1].node));
            }
#line 4077 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 176: /* expr_list4: assoc_pair  */
#line 2066 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = new_node_no_line();
                (yyval.node)->kind = 2;
                (yyval.node)->v.expr = (yyvsp[0].node);
                (yyval.node)->r.expr = 0;
                (yyval.node)->type = 0;
                /* we keep track of the end of the chain in the left nodes */
                (yyval.node)->l.expr = (yyval.node);
            }
#line 4091 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 177: /* expr_list4: expr_list4 ',' assoc_pair  */
#line 2076 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                parse_node_t *expr;

                expr = new_node_no_line();
                expr->kind = 0;
                expr->v.expr = (yyvsp[0].node);
                expr->r.expr = 0;
                expr->type = 0;
                
                (yyvsp[-2].node)->l.expr->r.expr = expr;
                (yyvsp[-2].node)->l.expr = expr;
                (yyvsp[-2].node)->kind += 2;
                (yyval.node) = (yyvsp[-2].node);
            }
#line 4110 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 178: /* assoc_pair: expr0 ':' expr0  */
#line 2094 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_TWO_VALUES((yyval.node), 0, (yyvsp[-2].node), (yyvsp[0].node));
            }
#line 4118 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 179: /* lvalue: expr4  */
#line 2101 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
#define LV_ILLEGAL 1
#define LV_RANGE 2
#define LV_INDEX 4
                /* Restrictive lvalues, but I think they make more sense :) */
                (yyval.node) = (yyvsp[0].node);
                switch((yyval.node)->kind) {
                default:
                    yyerror("Illegal lvalue");
                    break;
                case NODE_PARAMETER:
                    (yyval.node)->kind = NODE_PARAMETER_LVALUE;
                    break;
                case NODE_TERNARY_OP:
                    (yyval.node)->v.number = (yyval.node)->r.expr->v.number;
                    /* fall through */
                case NODE_OPCODE_1:
                case NODE_UNARY_OP_1:
                case NODE_BINARY_OP:
                    if ((yyval.node)->v.number >= F_LOCAL && (yyval.node)->v.number <= F_MEMBER)
                        (yyval.node)->v.number++; /* make it an lvalue */
                    else if ((yyval.node)->v.number >= F_INDEX 
                             && (yyval.node)->v.number <= F_RE_RANGE) {
                        parse_node_t *node = (yyval.node);
                        int flag = 0;
                        do {
                            switch(node->kind) {
                            case NODE_PARAMETER:
                                node->kind = NODE_PARAMETER_LVALUE;
                                flag |= LV_ILLEGAL;
                                break;
                            case NODE_TERNARY_OP:
                                node->v.number = node->r.expr->v.number;
                                /* fall through */
                            case NODE_OPCODE_1:
                            case NODE_UNARY_OP_1:
                            case NODE_BINARY_OP:
                                if (node->v.number >= F_LOCAL 
                                    && node->v.number <= F_MEMBER) {
                                    node->v.number++;
                                    flag |= LV_ILLEGAL;
                                    break;
                                } else if (node->v.number == F_INDEX ||
                                         node->v.number == F_RINDEX) {
                                    node->v.number++;
                                    flag |= LV_INDEX;
                                    break;
                                } else if (node->v.number >= F_ADD_EQ
                                           && node->v.number <= F_ASSIGN) {
                                    if (!(flag & LV_INDEX)) {
                                        yyerror("Illegal lvalue, a possible lvalue is (x <assign> y)[a]");
                                    }
                                    if (node->r.expr->kind == NODE_BINARY_OP||
                                        node->r.expr->kind == NODE_TERNARY_OP){
                                        if (node->r.expr->v.number >= F_NN_RANGE_LVALUE && node->r.expr->v.number <= F_NR_RANGE_LVALUE)
                                            yyerror("Illegal to have (x[a..b] <assign> y) to be the beginning of an lvalue");
                                    }
                                    flag = LV_ILLEGAL;
                                    break;
                                } else if (node->v.number >= F_NN_RANGE
                                         && node->v.number <= F_RE_RANGE) {
                                    if (flag & LV_RANGE) {
                                        yyerror("Can't do range lvalue of range lvalue.");
                                        flag |= LV_ILLEGAL;
                                        break;
                                    }
                                    if (flag & LV_INDEX){
                                        yyerror("Can't do indexed lvalue of range lvalue.");
                                        flag |= LV_ILLEGAL;
                                        break;
                                    }
                                    if (node->v.number == F_NE_RANGE) {
                                        /* x[foo..] -> x[foo..<1] */
                                        parse_node_t *rchild = node->r.expr;
                                        node->kind = NODE_TERNARY_OP;
                                        CREATE_BINARY_OP(node->r.expr,
                                                         F_NR_RANGE_LVALUE,
                                                         0, 0, rchild);
                                        CREATE_NUMBER(node->r.expr->l.expr, 1);
                                    } else if (node->v.number == F_RE_RANGE) {
                                        /* x[<foo..] -> x[<foo..<1] */
                                        parse_node_t *rchild = node->r.expr;
                                        node->kind = NODE_TERNARY_OP;
                                        CREATE_BINARY_OP(node->r.expr,
                                                         F_RR_RANGE_LVALUE,
                                                         0, 0, rchild);
                                        CREATE_NUMBER(node->r.expr->l.expr, 1);
                                    } else
                                        node->r.expr->v.number++;
                                    flag |= LV_RANGE;
                                    node = node->r.expr->r.expr;
                                    continue;
                                }
                                /* fall through */
                            default:
                                yyerror("Illegal lvalue");
                                flag = LV_ILLEGAL;
                                break;
                            }   
                            if ((flag & LV_ILLEGAL) || !(node = node->r.expr)) break;
                        } while (1);
                        break;
                    } else 
                        yyerror("Illegal lvalue");
                    break;
                }
            }
#line 4230 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 181: /* expr4: L_DEFINED_NAME  */
#line 2214 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
              int i;
              if ((i = (yyvsp[0].ihe)->dn.local_num) != -1) {
                  CREATE_OPCODE_1((yyval.node), F_LOCAL, type_of_locals_ptr[i],i & 0xff);
                  if (current_function_context)
                      current_function_context->num_locals++;
              } else
                  if ((i = (yyvsp[0].ihe)->dn.global_num) != -1) {
                      if (current_function_context)
                          current_function_context->bindable = FP_NOT_BINDABLE;
                          CREATE_OPCODE_1((yyval.node), F_GLOBAL,
                                      VAR_TEMP(i)->type & ~NAME_TYPE_MOD, i);
                      if (VAR_TEMP(i)->type & NAME_HIDDEN) {
                          char buf[256];
                          char *end = EndOf(buf);
                          char *p;

                          p = strput(buf, end, "Illegal to use private variable '");
                          p = strput(p, end, (yyvsp[0].ihe)->name);
                          p = strput(p, end, "'");
                          yyerror(buf);
                      }
                  } else {
                      char buf[256];
                      char *end = EndOf(buf);
                      char *p;
                      
                      p = strput(buf, end, "Undefined variable '");
                      p = strput(p, end, (yyvsp[0].ihe)->name);
                      p = strput(p, end, "'");
                      if ((size_t)current_number_of_locals < num_local_variables_allowed) {
                          add_local_name((yyvsp[0].ihe)->name, TYPE_ANY);
                      }
                      CREATE_OPCODE_1((yyval.node), F_LOCAL, TYPE_ANY, 0);
                      yyerror(buf);
                  }
            }
#line 4272 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 182: /* expr4: L_IDENTIFIER  */
#line 2252 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                char buf[256];
                char *end = EndOf(buf);
                char *p;
                
                p = strput(buf, end, "Undefined variable '");
                p = strput(p, end, (yyvsp[0].string));
                p = strput(p, end, "'");
                if ((size_t)current_number_of_locals < num_local_variables_allowed) {
                    add_local_name((yyvsp[0].string), TYPE_ANY);
                }
                CREATE_OPCODE_1((yyval.node), F_LOCAL, TYPE_ANY, 0);
                yyerror(buf);
                scratch_free((yyvsp[0].string));
            }
#line 4292 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 183: /* expr4: L_PARAMETER  */
#line 2268 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_PARAMETER((yyval.node), TYPE_ANY, (yyvsp[0].number));
            }
#line 4300 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 184: /* @10: %empty  */
#line 2272 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.contextp) = current_function_context;
                /* already flagged as an error */
                if (current_function_context)
                    current_function_context = current_function_context->parent;
            }
#line 4311 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 185: /* expr4: '$' '(' @10 comma_expr ')'  */
#line 2279 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                parse_node_t *node;

                current_function_context = (yyvsp[-2].contextp);

                if (!current_function_context || current_function_context->num_parameters == -2) {
                    /* This was illegal, and error'ed when the '$' token
                     * was returned.
                     */
                    CREATE_ERROR((yyval.node));
                } else {
                    CREATE_OPCODE_1((yyval.node), F_LOCAL, (yyvsp[-1].node)->type,
                                    current_function_context->values_list->kind++);

                    node = new_node_no_line();
                    node->type = 0;
                    current_function_context->values_list->l.expr->r.expr = node;
                    current_function_context->values_list->l.expr = node;
                    node->r.expr = 0;
                    node->v.expr = (yyvsp[-1].node);
                }
            }
#line 4338 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 186: /* expr4: expr4 L_ARROW identifier  */
#line 2302 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (!IS_CLASS((yyvsp[-2].node)->type)) {
                    yyerror("Left argument of -> is not a class");
                    CREATE_ERROR((yyval.node));
                } else {
                    CREATE_UNARY_OP_1((yyval.node), F_MEMBER, 0, (yyvsp[-2].node), 0);
                    (yyval.node)->l.number = lookup_class_member(CLASS_IDX((yyvsp[-2].node)->type), (yyvsp[0].string), &((yyval.node)->type));
                }
                scratch_free((yyvsp[0].string));
            }
#line 4353 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 187: /* expr4: expr4 '[' comma_expr L_RANGE comma_expr ']'  */
#line 2313 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = make_range_node(F_NN_RANGE, (yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node));
            }
#line 4361 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 188: /* expr4: expr4 '[' '<' comma_expr L_RANGE comma_expr ']'  */
#line 2317 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = make_range_node(F_RN_RANGE, (yyvsp[-6].node), (yyvsp[-3].node), (yyvsp[-1].node));
            }
#line 4369 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 189: /* expr4: expr4 '[' '<' comma_expr L_RANGE '<' comma_expr ']'  */
#line 2321 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if ((yyvsp[-1].node)->kind == NODE_NUMBER && (yyvsp[-1].node)->v.number <= 1)
                    (yyval.node) = make_range_node(F_RE_RANGE, (yyvsp[-7].node), (yyvsp[-4].node), 0);
                else
                    (yyval.node) = make_range_node(F_RR_RANGE, (yyvsp[-7].node), (yyvsp[-4].node), (yyvsp[-1].node));
            }
#line 4380 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 190: /* expr4: expr4 '[' comma_expr L_RANGE '<' comma_expr ']'  */
#line 2328 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if ((yyvsp[-1].node)->kind == NODE_NUMBER && (yyvsp[-1].node)->v.number <= 1)
                    (yyval.node) = make_range_node(F_NE_RANGE, (yyvsp[-6].node), (yyvsp[-4].node), 0);
                else
                    (yyval.node) = make_range_node(F_NR_RANGE, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node));
            }
#line 4391 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 191: /* expr4: expr4 '[' comma_expr L_RANGE ']'  */
#line 2335 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = make_range_node(F_NE_RANGE, (yyvsp[-4].node), (yyvsp[-2].node), 0);
            }
#line 4399 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 192: /* expr4: expr4 '[' '<' comma_expr L_RANGE ']'  */
#line 2339 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = make_range_node(F_RE_RANGE, (yyvsp[-5].node), (yyvsp[-2].node), 0);
            }
#line 4407 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 193: /* expr4: expr4 '[' '<' comma_expr ']'  */
#line 2343 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if (IS_NODE((yyvsp[-4].node), NODE_CALL, F_AGGREGATE) && (yyvsp[-1].node)->kind == NODE_NUMBER) {
                    int64_t i = (yyvsp[-1].node)->v.number;
                    if (i < 1 || i > (yyvsp[-4].node)->l.number)
                        yyerror("Illegal index to array constant.");
                    else {
                        parse_node_t *node = (yyvsp[-4].node)->r.expr;
                        i = (yyvsp[-4].node)->l.number - i;
                        while (i--)
                            node = node->r.expr;
                        (yyval.node) = node->v.expr;
                        break;
                    }
                }
                CREATE_BINARY_OP((yyval.node), F_RINDEX, 0, (yyvsp[-1].node), (yyvsp[-4].node));
                if (exact_types) {
                    switch((yyvsp[-4].node)->type) {
                    case TYPE_MAPPING:
                        yyerror("Illegal index for mapping.");
                        /* fall through */
                    case TYPE_ANY:
                        (yyval.node)->type = TYPE_ANY;
                        break;
                    case TYPE_STRING:
                    case TYPE_BUFFER:
                        (yyval.node)->type = TYPE_NUMBER;
                        if (!IS_TYPE((yyvsp[-1].node)->type,TYPE_NUMBER))
                            type_error("Bad type of index", (yyvsp[-1].node)->type);
                        break;
                        
                    default:
                        if ((yyvsp[-4].node)->type & TYPE_MOD_ARRAY) {
                            (yyval.node)->type = (yyvsp[-4].node)->type & ~TYPE_MOD_ARRAY;
                            if (!IS_TYPE((yyvsp[-1].node)->type,TYPE_NUMBER))
                                type_error("Bad type of index", (yyvsp[-1].node)->type);
                        } else {
                            type_error("Value indexed has a bad type ", (yyvsp[-4].node)->type);
                            (yyval.node)->type = TYPE_ANY;
                        }
                    }
                } else (yyval.node)->type = TYPE_ANY;
            }
#line 4454 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 194: /* expr4: expr4 '[' comma_expr ']'  */
#line 2386 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                /* Something stupid like ({ 1, 2, 3 })[1]; we take the
                 * time to optimize this because people who don't understand
                 * the preprocessor often write things like:
                 *
                 * #define MY_ARRAY ({ "foo", "bar", "bazz" })
                 * ...
                 * ... MY_ARRAY[1] ...
                 *
                 * which of course expands to the above.
                 */
                if (IS_NODE((yyvsp[-3].node), NODE_CALL, F_AGGREGATE) && (yyvsp[-1].node)->kind == NODE_NUMBER) {
                    int64_t i = (yyvsp[-1].node)->v.number;
                    if (i < 0 || i >= (yyvsp[-3].node)->l.number)
                        yyerror("Illegal index to array constant.");
                    else {
                        parse_node_t *node = (yyvsp[-3].node)->r.expr;
                        while (i--)
                            node = node->r.expr;
                        (yyval.node) = node->v.expr;
                        break;
                    }
                }
                CREATE_BINARY_OP((yyval.node), F_INDEX, 0, (yyvsp[-1].node), (yyvsp[-3].node));
                if (exact_types) {
                    switch((yyvsp[-3].node)->type) {
                    case TYPE_MAPPING:
                    case TYPE_ANY:
                        (yyval.node)->type = TYPE_ANY;
                        break;
                    case TYPE_STRING:
                    case TYPE_BUFFER:
                        (yyval.node)->type = TYPE_NUMBER;
                        if (!IS_TYPE((yyvsp[-1].node)->type,TYPE_NUMBER))
                            type_error("Bad type of index", (yyvsp[-1].node)->type);
                        break;
                        
                    default:
                        if ((yyvsp[-3].node)->type & TYPE_MOD_ARRAY) {
                            (yyval.node)->type = (yyvsp[-3].node)->type & ~TYPE_MOD_ARRAY;
                            if (!IS_TYPE((yyvsp[-1].node)->type,TYPE_NUMBER))
                                type_error("Bad type of index", (yyvsp[-1].node)->type);
                        } else {
                            type_error("Value indexed has a bad type ", (yyvsp[-3].node)->type);
                            (yyval.node)->type = TYPE_ANY;
                        }
                    }
                } else (yyval.node)->type = TYPE_ANY;
            }
#line 4508 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 196: /* expr4: '(' comma_expr ')'  */
#line 2437 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = (yyvsp[-1].node);
            }
#line 4516 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 198: /* @11: %empty  */
#line 2442 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if ((yyvsp[0].type) != TYPE_FUNCTION) yyerror("Reserved type name unexpected.");
                (yyval.func_block).num_local = (char)current_number_of_locals;
                (yyval.func_block).max_num_locals = (char)max_num_locals;
                (yyval.func_block).context = (short)context;
                (yyval.func_block).save_current_type = (short)current_type;
                (yyval.func_block).save_exact_types = (short)exact_types;
                if (type_of_locals_ptr + max_num_locals + num_local_variables_allowed >= &type_of_locals[type_of_locals_size])
                    reallocate_locals();
                deactivate_current_locals();
                locals_ptr += current_number_of_locals;
                type_of_locals_ptr += max_num_locals;
                runtime_locals_ptr += current_number_of_locals;
                max_num_locals = current_number_of_locals = 0;
                push_function_context();
                current_function_context->num_parameters = -1;
                exact_types = TYPE_ANY;
                context = 0;
            }
#line 4540 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 199: /* expr4: L_BASIC_TYPE @11 '(' argument ')' block  */
#line 2462 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                if ((yyvsp[-2].argument).flags & ARG_IS_PROTO) {
                    yyerror("Missing name for function argument");
                }
                if ((yyvsp[-2].argument).flags & ARG_IS_VARARGS) {
                    yyerror("Anonymous varargs functions aren't implemented");
                }
                if (!(yyvsp[0].decl).node) {
                    CREATE_RETURN((yyval.node), 0);
                } else if ((yyvsp[0].decl).node->kind != NODE_RETURN &&
                           ((yyvsp[0].decl).node->kind != NODE_TWO_VALUES || (yyvsp[0].decl).node->r.expr->kind != NODE_RETURN)) {
                    parse_node_t *replacement;
                    CREATE_STATEMENTS(replacement, (yyvsp[0].decl).node, 0);
                    CREATE_RETURN(replacement->r.expr, 0);
                    (yyvsp[0].decl).node = replacement;
                }
                
                (yyval.node) = new_node();
                (yyval.node)->kind = NODE_ANON_FUNC;
                (yyval.node)->type = TYPE_FUNCTION;
                (yyval.node)->l.number = (max_num_locals - (yyvsp[-2].argument).num_arg);
                (yyval.node)->r.expr = (yyvsp[0].decl).node;
                (yyval.node)->v.number = (yyvsp[-2].argument).num_arg;
                if (current_function_context->bindable)
                    (yyval.node)->v.number |= 0x10000;
                free_all_local_names();
                
                current_number_of_locals = (yyvsp[-4].func_block).num_local;
                max_num_locals = (yyvsp[-4].func_block).max_num_locals;
                context = (yyvsp[-4].func_block).context;
                current_type = (yyvsp[-4].func_block).save_current_type;
                exact_types = (yyvsp[-4].func_block).save_exact_types;
                pop_function_context();
                
                locals_ptr -= current_number_of_locals;
                type_of_locals_ptr -= max_num_locals;
                runtime_locals_ptr -= current_number_of_locals;
                reactivate_current_locals();
            }
#line 4584 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 200: /* expr4: L_NEW_FUNCTION_OPEN ':' ')'  */
#line 2502 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = new_node();
                (yyval.node)->kind = NODE_FUNCTION_CONSTRUCTOR;
                (yyval.node)->type = TYPE_FUNCTION;
                (yyval.node)->r.expr = 0;
                switch ((yyvsp[-2].number) & 0xff) {
                case FP_L_VAR:
                    yyerror("Illegal to use local variable in a functional.");
                    CREATE_NUMBER((yyval.node)->l.expr, 0);
                    (yyval.node)->l.expr->r.expr = 0;
                    (yyval.node)->l.expr->l.expr = 0;
                    (yyval.node)->v.number = FP_FUNCTIONAL;
                    break;
                case FP_G_VAR:
                    CREATE_OPCODE_1((yyval.node)->l.expr, F_GLOBAL, 0, (yyvsp[-2].number) >> 8);
                    (yyval.node)->v.number = FP_FUNCTIONAL | FP_NOT_BINDABLE;
                    if (VAR_TEMP((yyval.node)->l.expr->l.number)->type & NAME_HIDDEN) {
                      char buf[256];
                      char *end = EndOf(buf);
                      char *p;
                      
                      p = strput(buf, end, "Illegal to use private variable '");
                      p = strput(p, end, VAR_TEMP((yyval.node)->l.expr->l.number)->name);
                      p = strput(p, end, "'");
                      yyerror(buf);
                    }
                    break;
                default:
                    (yyval.node)->v.number = (yyvsp[-2].number);
                    break;
                }
            }
#line 4621 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 201: /* expr4: L_NEW_FUNCTION_OPEN ',' expr_list2 ':' ')'  */
#line 2535 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = new_node();
                (yyval.node)->kind = NODE_FUNCTION_CONSTRUCTOR;
                (yyval.node)->type = TYPE_FUNCTION;
                (yyval.node)->v.number = (yyvsp[-4].number);
                (yyval.node)->r.expr = (yyvsp[-2].node);
                
                switch ((yyvsp[-4].number) & 0xff) {
                case FP_EFUN: {
                    int *argp;
                    int f = (int)((yyvsp[-4].number) >>8);
                    int num = (yyvsp[-2].node)->kind;
                    int max_arg = predefs[f].max_args;
                    
                    if (num > max_arg && max_arg != -1) {
                        parse_node_t *pn = (yyvsp[-2].node);
                        
                        while (pn) {
                            if (pn->type & 1) break;
                            pn = pn->r.expr;
                        }
                        
                        if (!pn) {
                            char bff[256];
                            char *end = EndOf(bff);
                            char *p;
                            
                            p = strput(bff, end, "Too many arguments to ");
                            p = strput(p, end, predefs[f].word);
                            yyerror(bff);
                        }
                    } else if (max_arg != -1 && exact_types) {
                        /*
                         * Now check all types of arguments to efuns.
                         */
                        int i, argn, tmp;
                        parse_node_t *enode = (yyvsp[-2].node);
                        argp = &efun_arg_types[predefs[f].arg_index];
                        
                        for (argn = 0; argn < num; argn++) {
                            if (enode->type & 1) break;
                            
                            tmp = enode->v.expr->type;
                            for (i=0; !compatible_types(tmp, argp[i])
                                 && argp[i] != 0; i++)
                                ;
                            if (argp[i] == 0) {
                                char buf[256];
                                char *end = EndOf(buf);
                                char *p;

                                p = strput(buf, end, "Bad argument ");
                                p = strput_int(p, end, argn+1);
                                p = strput(p, end, " to efun ");
                                p = strput(p, end, predefs[f].word);
                                p = strput(p, end, "()");
                                yyerror(buf);
                            } else {
                                /* this little section necessary b/c in the
                                   case float | int we dont want to do
                                   promoting. */
                                if (tmp == TYPE_NUMBER && argp[i] == TYPE_REAL) {
                                    for (i++; argp[i] && argp[i] != TYPE_NUMBER; i++)
                                        ;
                                    if (!argp[i])
                                        enode->v.expr = promote_to_float(enode->v.expr);
                                }
                                if (tmp == TYPE_REAL && argp[i] == TYPE_NUMBER) {
                                    for (i++; argp[i] && argp[i] != TYPE_REAL; i++)
                                        ;
                                    if (!argp[i])
                                        enode->v.expr = promote_to_int(enode->v.expr);
                                }
                            }
                            while (argp[i] != 0)
                                i++;
                            argp += i + 1;
                            enode = enode->r.expr;
                        }
                    }
                    break;
                }
                case FP_L_VAR:
                case FP_G_VAR:
                    yyerror("Can't give parameters to functional.");
                    break;
                }
            }
#line 4714 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 202: /* expr4: L_FUNCTION_OPEN comma_expr ':' ')'  */
#line 2624 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
             {
                 if (current_function_context->num_locals)
                     yyerror("Illegal to use local variable in functional.");
                 if (current_function_context->values_list->r.expr)
                     current_function_context->values_list->r.expr->kind = current_function_context->values_list->kind;
                 
                 (yyval.node) = new_node();
                 (yyval.node)->kind = NODE_FUNCTION_CONSTRUCTOR;
                 (yyval.node)->type = TYPE_FUNCTION;
                 (yyval.node)->l.expr = (yyvsp[-2].node);
                 if ((yyvsp[-2].node)->kind == NODE_STRING)
                     yywarn("Function pointer returning string constant is NOT a function call");
                 (yyval.node)->r.expr = current_function_context->values_list->r.expr;
                 (yyval.node)->v.number = FP_FUNCTIONAL + current_function_context->bindable
                     + (current_function_context->num_parameters << 8);
                 pop_function_context();
             }
#line 4736 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 203: /* expr4: L_MAPPING_OPEN expr_list3 ']' ')'  */
#line 2642 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_CALL((yyval.node), F_AGGREGATE_ASSOC, TYPE_MAPPING, (yyvsp[-2].node));
            }
#line 4744 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 204: /* expr4: L_ARRAY_OPEN expr_list '}' ')'  */
#line 2646 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_CALL((yyval.node), F_AGGREGATE, TYPE_ANY | TYPE_MOD_ARRAY, (yyvsp[-2].node));
            }
#line 4752 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 205: /* expr_or_block: block  */
#line 2653 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = (yyvsp[0].decl).node;
            }
#line 4760 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 206: /* expr_or_block: '(' comma_expr ')'  */
#line 2657 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = insert_pop_value((yyvsp[-1].node));
            }
#line 4768 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 207: /* @12: %empty  */
#line 2664 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.number) = context;
                context = SPECIAL_CONTEXT;
            }
#line 4777 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 208: /* catch: L_CATCH @12 expr_or_block  */
#line 2669 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_CATCH((yyval.node), (yyvsp[0].node));
                context = (yyvsp[-1].number);
            }
#line 4786 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 209: /* sscanf: L_SSCANF '(' expr0 ',' expr0 lvalue_list ')'  */
#line 2678 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                lpc_type_t p = (lpc_type_t)(yyvsp[-1].node)->v.number;
                CREATE_LVALUE_EFUN((yyval.node), TYPE_NUMBER, (yyvsp[-1].node));
                CREATE_BINARY_OP_1((yyval.node)->l.expr, F_SSCANF, 0, (yyvsp[-4].node), (yyvsp[-2].node), p);
            }
#line 4796 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 210: /* parse_command: L_PARSE_COMMAND '(' expr0 ',' expr0 ',' expr0 lvalue_list ')'  */
#line 2687 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                lpc_type_t p = (lpc_type_t)(yyvsp[-1].node)->v.number;
                CREATE_LVALUE_EFUN((yyval.node), TYPE_NUMBER, (yyvsp[-1].node));
                CREATE_TERNARY_OP_1((yyval.node)->l.expr, F_PARSE_COMMAND, 0, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), p);
            }
#line 4806 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 211: /* @13: %empty  */
#line 2696 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.number) = context;
                context = SPECIAL_CONTEXT;
            }
#line 4815 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 212: /* time_expression: L_TIME_EXPRESSION @13 expr_or_block  */
#line 2701 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_TIME_EXPRESSION((yyval.node), (yyvsp[0].node));
                context = (yyvsp[-1].number);
            }
#line 4824 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 213: /* lvalue_list: %empty  */
#line 2709 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = new_node_no_line();
                (yyval.node)->r.expr = 0;
                (yyval.node)->v.number = 0;
            }
#line 4834 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 214: /* lvalue_list: ',' lvalue lvalue_list  */
#line 2715 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                parse_node_t *insert;
                
                (yyval.node) = (yyvsp[0].node);
                insert = new_node_no_line();
                insert->r.expr = (yyvsp[0].node)->r.expr;
                insert->l.expr = (yyvsp[-1].node);
                (yyvsp[0].node)->r.expr = insert;
                (yyval.node)->v.number++;
            }
#line 4849 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 215: /* string: string_con2  */
#line 2729 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                CREATE_STRING_LEN((yyval.node), (yyvsp[0].string_span).str, (yyvsp[0].string_span).len);
                scratch_free((yyvsp[0].string_span).str);
            }
#line 4858 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 217: /* string_con1: '(' string_con1 ')'  */
#line 2738 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.string_span) = (yyvsp[-1].string_span);
            }
#line 4866 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 218: /* string_con1: string_con1 '+' string_con1  */
#line 2742 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                size_t total_len;

                total_len = (size_t)(yyvsp[-2].string_span).len + (size_t)(yyvsp[0].string_span).len;
                (yyval.string_span).str = scratch_alloc(total_len + 1);
                memcpy((yyval.string_span).str, (yyvsp[-2].string_span).str, (yyvsp[-2].string_span).len);
                memcpy((yyval.string_span).str + (yyvsp[-2].string_span).len, (yyvsp[0].string_span).str, (yyvsp[0].string_span).len);
                (yyval.string_span).str[total_len] = '\0';
                (yyval.string_span).len = (unsigned int)total_len;
                scratch_free((yyvsp[-2].string_span).str);
                scratch_free((yyvsp[0].string_span).str);
            }
#line 4883 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 220: /* string_con2: string_con2 L_STRING  */
#line 2759 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                size_t total_len;

                total_len = (size_t)(yyvsp[-1].string_span).len + (size_t)(yyvsp[0].string_span).len;
                (yyval.string_span).str = scratch_alloc(total_len + 1);
                memcpy((yyval.string_span).str, (yyvsp[-1].string_span).str, (yyvsp[-1].string_span).len);
                memcpy((yyval.string_span).str + (yyvsp[-1].string_span).len, (yyvsp[0].string_span).str, (yyvsp[0].string_span).len);
                (yyval.string_span).str[total_len] = '\0';
                (yyval.string_span).len = (unsigned int)total_len;
                scratch_free((yyvsp[-1].string_span).str);
                scratch_free((yyvsp[0].string_span).str);
            }
#line 4900 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 221: /* class_init: identifier ':' expr0  */
#line 2774 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
    {
        (yyval.node) = new_node();
        (yyval.node)->l.expr = (parse_node_t *)(yyvsp[-2].string);
        (yyval.node)->v.expr = (yyvsp[0].node);
        (yyval.node)->r.expr = 0;
    }
#line 4911 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 222: /* opt_class_init: %empty  */
#line 2784 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
    {
        (yyval.node) = 0;
    }
#line 4919 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 223: /* opt_class_init: opt_class_init ',' class_init  */
#line 2788 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
    {
        (yyval.node) = (yyvsp[0].node);
        (yyval.node)->r.expr = (yyvsp[-2].node);
    }
#line 4928 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 224: /* function_call: efun_override '(' expr_list ')'  */
#line 2797 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
              (yyval.node) = validate_efun_call((int)(yyvsp[-3].number),(yyvsp[-1].node));
            }
#line 4936 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 225: /* function_call: L_NEW '(' expr_list ')'  */
#line 2801 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                ident_hash_elem_t *ihe;

                ihe = lookup_ident("clone_object");
                (yyval.node) = validate_efun_call(ihe->dn.efun_num, (yyvsp[-1].node));
            }
#line 4947 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 226: /* function_call: L_NEW '(' L_CLASS L_DEFINED_NAME opt_class_init ')'  */
#line 2808 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                parse_node_t *node;
                
                if ((yyvsp[-2].ihe)->dn.class_num == -1) {
                    char buf[256];
                    char *end = EndOf(buf);
                    char *p;
                    
                    p = strput(buf, end, "Undefined class '");
                    p = strput(p, end, (yyvsp[-2].ihe)->name);
                    p = strput(p, end, "'");
                    yyerror(buf);
                    CREATE_ERROR((yyval.node));
                    node = (yyvsp[-1].node);
                    while (node) {
                        scratch_free((char *)node->l.expr);
                        node = node->r.expr;
                    }
                } else {
                    lpc_type_t type = (yyvsp[-2].ihe)->dn.class_num | TYPE_MOD_CLASS;
                    
                    if ((node = (yyvsp[-1].node))) {
                        CREATE_TWO_VALUES((yyval.node), type, 0, 0);
                        (yyval.node)->l.expr = reorder_class_values((yyvsp[-2].ihe)->dn.class_num, node);
                        CREATE_OPCODE_1((yyval.node)->r.expr, F_NEW_CLASS, type, (yyvsp[-2].ihe)->dn.class_num);
                        
                    } else {
                        CREATE_OPCODE_1((yyval.node), F_NEW_EMPTY_CLASS, type, (yyvsp[-2].ihe)->dn.class_num);
                    }
                }
            }
#line 4983 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 227: /* function_call: L_DEFINED_NAME '(' expr_list ')'  */
#line 2840 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
              int f;

              (yyval.node) = (yyvsp[-1].node);
              if ((f = (yyvsp[-3].ihe)->dn.function_num) != -1) {
                  if (FUNCTION_FLAGS(f) & NAME_HIDDEN) {
                      char buf[256];
                      char *end = EndOf(buf);
                      char *p;
                      
                      p = strput(buf, end, "Illegal to call private function '");
                      p = strput(p, end, (yyvsp[-3].ihe)->name);
                      p = strput(p, end, "'");
                      yyerror(buf);
                  }
                  if (current_function_context)
                      current_function_context->bindable = FP_NOT_BINDABLE;

                  (yyval.node)->kind = NODE_CALL_1;
                  (yyval.node)->v.number = F_CALL_FUNCTION_BY_ADDRESS;
                  (yyval.node)->l.number = f;
                  (yyval.node)->type = validate_function_call(f, (yyvsp[-1].node)->r.expr);
              } else
              if ((f=(yyvsp[-3].ihe)->dn.simul_num) != -1) {
                  (yyval.node)->kind = NODE_CALL_1;
                  (yyval.node)->v.number = F_SIMUL_EFUN;
                  (yyval.node)->l.number = f;
                  (yyval.node)->type = (SIMUL(f)->type) & ~NAME_TYPE_MOD;
              } else 
              if ((f=(yyvsp[-3].ihe)->dn.efun_num) != -1) {
                  (yyval.node) = validate_efun_call(f, (yyvsp[-1].node));
              } else {
                /* This here is a really nasty case that only occurs with
                 * exact_types off.  The user has done something gross like:
                 *
                 * func() { int f; f(); } // if f was prototyped we wouldn't
                 * f() { }                // need this case
                 *
                 * Don't complain, just grok it.
                 */
                int cf, index;

                if (current_function_context)
                    current_function_context->bindable = FP_NOT_BINDABLE;
                
                cf = define_new_function((yyvsp[-3].ihe)->name, 0, 0, NAME_UNDEFINED | NAME_PROTOTYPE, 0);
                index = COMPILER_FUNC(cf)->runtime_index;
                (yyval.node)->kind = NODE_CALL_1;
                (yyval.node)->v.number = F_CALL_FUNCTION_BY_ADDRESS;
                (yyval.node)->l.number = index; /* runtime index */
                (yyval.node)->type = TYPE_ANY; /* just a guess */
                if (exact_types) {
                    char buf[256];
                    char *end = EndOf(buf);
                    char *p;
                    char *n = (yyvsp[-3].ihe)->name;
                    if (*n == ':') n++;
                    /* prevent some errors; by making it look like an
                     * inherited function we prevent redeclaration errors
                     * if it shows up later
                     */
                    FUNCTION_FLAGS(index) &= ~NAME_UNDEFINED;
                    FUNCTION_FLAGS(index) |= NAME_INHERITED;
                    COMPILER_FUNC(cf)->type |= NAME_VARARGS;
                    p = strput(buf, end, "Undefined function ");
                    p = strput(p, end, n);
                    yyerror(buf);
                }
              }
            }
#line 5058 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 228: /* function_call: function_name '(' expr_list ')'  */
#line 2911 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
              char *name = (yyvsp[-3].string);

              (yyval.node) = (yyvsp[-1].node);
              
              if (*name == ':'){
                  arrange_call_inherited(name + 1, (yyval.node));
              } else {
                  int f;
                  ident_hash_elem_t *ihe;
                  
                  if (current_function_context)
                      current_function_context->bindable = FP_NOT_BINDABLE;

                  f = (ihe = lookup_ident(name)) ? ihe->dn.function_num : -1;
                  (yyval.node)->kind = NODE_CALL_1;
                  (yyval.node)->v.number = F_CALL_FUNCTION_BY_ADDRESS;
                  if (f!=-1) {
                      /* The only way this can happen is if function_name
                       * below made the function name.  The lexer would
                       * return L_DEFINED_NAME instead.
                       */
                      (yyval.node)->type = validate_function_call(f, (yyvsp[-1].node)->r.expr);
                  } else {
                      f = define_new_function(name, 0, 0, 
                                              NAME_UNDEFINED | NAME_PROTOTYPE, 0);
                      f = COMPILER_FUNC(f)->runtime_index;
                  }
                  (yyval.node)->l.number = f;
                  /*
                   * Check if this function has been defined.
                   * But, don't complain yet about functions defined
                   * by inheritance.
                   */
                  if (exact_types && (FUNCTION_FLAGS(f) & NAME_UNDEFINED)) {
                      char buf[256];
                      char *end = EndOf(buf);
                      char *p;
                      char *n = (yyvsp[-3].string);
                      if (*n == ':') n++;
                      /* prevent some errors */
                      FUNCTION_FLAGS(f) &= ~NAME_UNDEFINED;
                      FUNCTION_FLAGS(f) |= (NAME_INHERITED | NAME_VARARGS);
                      p = strput(buf, end, "Undefined function ");
                      p = strput(p, end, n);
                      yyerror(buf);
                  }
                  if (!(FUNCTION_FLAGS(f) & NAME_UNDEFINED))
                      (yyval.node)->type = FUNCTION_DEF(f)->type;
                  else
                      (yyval.node)->type = TYPE_ANY;  /* Just a guess */
              }
              scratch_free(name);
          }
#line 5117 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 229: /* function_call: expr4 L_ARROW identifier '(' expr_list ')'  */
#line 2966 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                parse_node_t *expr, *expr2;
                (yyval.node) = (yyvsp[-1].node);
                (yyval.node)->kind = NODE_EFUN;
                (yyval.node)->l.number = (yyval.node)->v.number + 2;
                (yyval.node)->v.number = F_CALL_OTHER;
#ifdef CAST_CALL_OTHERS
                (yyval.node)->type = TYPE_UNKNOWN;
#else
                (yyval.node)->type = TYPE_ANY;
#endif		  
                expr = new_node_no_line();
                expr->type = 0;
                expr->v.expr = (yyvsp[-5].node);

                expr2 = new_node_no_line();
                expr2->type = 0;
                CREATE_STRING(expr2->v.expr, (yyvsp[-3].string));
                scratch_free((yyvsp[-3].string));

                /* insert the two nodes */
                expr2->r.expr = (yyval.node)->r.expr;
                expr->r.expr = expr2;
                (yyval.node)->r.expr = expr;
            }
#line 5147 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 230: /* function_call: expr4 L_DOT identifier '(' expr_list ')'  */
#line 2992 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                ident_hash_elem_t *ihe;
                parse_node_t *expr;
                int f;

                (yyval.node) = (yyvsp[-1].node);
                ihe = lookup_ident((yyvsp[-3].string));
                f = ihe ? ihe->dn.efun_num : -1;

                if (f == -1) {
                    char buf[256];
                    char *end = EndOf(buf);
                    char *p;

                    p = strput(buf, end, "Unknown efun in dot-call: ");
                    p = strput(p, end, (yyvsp[-3].string));
                    yyerror(buf);
                    CREATE_ERROR((yyval.node));
                } else if (!(ihe->token & IHE_ALLOW_DOT_CALL)) {
                    char buf[256];
                    char *end = EndOf(buf);
                    char *p;

                    p = strput(buf, end, "Efun does not permit dot-call syntax: ");
                    p = strput(p, end, (yyvsp[-3].string));
                    yyerror(buf);
                    CREATE_ERROR((yyval.node));
                } else {
                    CREATE_EXPR_NODE(expr, (yyvsp[-5].node), 0);
                    expr->kind = 0;
                    expr->r.expr = (yyval.node)->r.expr;
                    (yyval.node)->r.expr = expr;
                    if ((yyval.node)->l.expr == (yyval.node))
                        (yyval.node)->l.expr = expr;
                    (yyval.node)->v.number++;
                    (yyval.node) = validate_efun_call(f, (yyval.node));
                }
                scratch_free((yyvsp[-3].string));
            }
#line 5191 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 231: /* function_call: '(' '*' comma_expr ')' '(' expr_list ')'  */
#line 3032 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                parse_node_t *expr;

                (yyval.node) = (yyvsp[-1].node);
                (yyval.node)->kind = NODE_EFUN;
                (yyval.node)->l.number = (yyval.node)->v.number + 1;
                (yyval.node)->v.number = F_EVALUATE;
#ifdef CAST_CALL_OTHERS
                (yyval.node)->type = TYPE_UNKNOWN;
#else
                (yyval.node)->type = TYPE_ANY;
#endif
                expr = new_node_no_line();
                expr->type = 0;
                expr->v.expr = (yyvsp[-4].node);
                expr->r.expr = (yyval.node)->r.expr;
                (yyval.node)->r.expr = expr;
            }
#line 5214 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 232: /* efun_override: L_EFUN L_COLON_COLON identifier  */
#line 3052 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                                               {
        svalue_t *res;
    int approved;
        ident_hash_elem_t *ihe;

        (yyval.number) = (ihe = lookup_ident((yyvsp[0].string))) ? ihe->dn.efun_num : -1;
        if ((yyval.number) == -1) {
            char buf[256];
            char *end = EndOf(buf);
            char *p;
            
            p = strput(buf, end, "Unknown efun: ");
            p = strput(p, end, (yyvsp[0].string));
            yyerror(buf);
        } else {
            push_malloced_string(the_file_name(current_file));
            share_and_push_string((yyvsp[0].string));
            push_malloced_string(add_slash(main_file_name()));
            res = APPLY_SLOT_SAFE_MASTER_CALL(APPLY_VALID_OVERRIDE, 3);
            approved = MASTER_APPROVED(res);
            APPLY_SLOT_FINISH_CALL();
            if (!approved) {
                yyerror("Invalid simulated efunction override");
                (yyval.number) = -1;
            }
        }
        scratch_free((yyvsp[0].string));
      }
#line 5247 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 233: /* efun_override: L_EFUN L_COLON_COLON L_NEW  */
#line 3080 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
                                 {
        ident_hash_elem_t *ihe;
        svalue_t *res;
        int approved;
        
        ihe = lookup_ident("clone_object");
        push_malloced_string(the_file_name(current_file));
        push_constant_string("clone_object");
        push_malloced_string(add_slash(main_file_name()));
        res = APPLY_SLOT_SAFE_MASTER_CALL(APPLY_VALID_OVERRIDE, 3);
        approved = MASTER_APPROVED(res);
        APPLY_SLOT_FINISH_CALL();
        if (!approved) {
            yyerror("Invalid simulated efunction override");
            (yyval.number) = -1;
        } else (yyval.number) = ihe->dn.efun_num;
      }
#line 5269 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 235: /* function_name: L_COLON_COLON identifier  */
#line 3102 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                size_t l = strlen((yyvsp[0].string)) + 1;
                char *p;
                /* here we be a bit cute.  we put a : on the front so we
                 * don't have to strchr for it.  Here we do:
                 * "name" -> ":::name"
                 */
                (yyval.string) = scratch_realloc((yyvsp[0].string), l + 3);
                p = (yyval.string) + l;
                while (p--,l--)
                    *(p+3) = *p;
                memcpy((yyval.string), ":::", 3);
            }
#line 5287 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 236: /* function_name: L_BASIC_TYPE L_COLON_COLON identifier  */
#line 3116 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                size_t z, l = strlen((yyvsp[0].string)) + 1;
                char *p;
                /* <type> and "name" -> ":type::name" */
                z = strlen(compiler_type_names[(yyvsp[-2].type)]) + 3; /* length of :type:: */
                (yyval.string) = scratch_realloc((yyvsp[0].string), l + z);
                p = (yyval.string) + l;
                while (p--,l--)
                    *(p+z) = *p;
                (yyval.string)[0] = ':';
                strncpy((yyval.string) + 1, compiler_type_names[(yyvsp[-2].type)], z - 3);
                (yyval.string)[z-2] = ':';
                (yyval.string)[z-1] = ':';
            }
#line 5306 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 237: /* function_name: identifier L_COLON_COLON identifier  */
#line 3131 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                size_t l = strlen((yyvsp[-2].string));
                /* "ob" and "name" -> ":ob::name" */
                (yyval.string) = scratch_alloc(l + strlen((yyvsp[0].string)) + 4);
                *((yyval.string)) = ':';
                strcpy((yyval.string) + 1, (yyvsp[-2].string));
                strcpy((yyval.string) + l + 1, "::");
                strcpy((yyval.string) + l + 3, (yyvsp[0].string));
                scratch_free((yyvsp[-2].string));
                scratch_free((yyvsp[0].string));
            }
#line 5322 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 238: /* cond: L_IF '(' comma_expr ')' statement optional_else_part  */
#line 3146 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                /* x != 0 -> x */
                if (IS_NODE((yyvsp[-3].node), NODE_BINARY_OP, F_NE)) {
                    if (IS_NODE((yyvsp[-3].node)->r.expr, NODE_NUMBER, 0))
                        (yyvsp[-3].node) = (yyvsp[-3].node)->l.expr;
                    else if (IS_NODE((yyvsp[-3].node)->l.expr, NODE_NUMBER, 0))
                             (yyvsp[-3].node) = (yyvsp[-3].node)->r.expr;
                }

                /* TODO: should optimize if (0), if (1) here.  
                 * Also generalize this.
                 */

                if ((yyvsp[-1].node) == 0) {
                    if ((yyvsp[0].node) == 0) {
                        /* if (x) ; -> x; */
                        (yyval.node) = insert_pop_value((yyvsp[-3].node));
                        break;
                    } else {
                        /* if (x) {} else y; -> if (!x) y; */
                        parse_node_t *repl;
                        
                        CREATE_UNARY_OP(repl, F_NOT, TYPE_NUMBER, (yyvsp[-3].node));
                        (yyvsp[-3].node) = repl;
                        (yyvsp[-1].node) = (yyvsp[0].node);
                        (yyvsp[0].node) = 0;
                    }
                }
                CREATE_IF((yyval.node), (yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node));
            }
#line 5357 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 239: /* optional_else_part: %empty  */
#line 3180 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = 0;
            }
#line 5365 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;

  case 240: /* optional_else_part: L_ELSE statement  */
#line 3184 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"
            {
                (yyval.node) = (yyvsp[0].node);
            }
#line 5373 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"
    break;


#line 5377 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/build-vs2022/lib/lpc/grammar.c"

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

#line 3188 "C:/ES2/ES2_WebMUD_SourceOnly_v2.9/source/upstream/neolith/lib/lpc/grammar.y"




