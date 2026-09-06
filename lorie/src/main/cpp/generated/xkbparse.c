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
#line 91 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"

#ifdef DEBUG
#define	YYDEBUG 1
#define	DEBUG_VAR parseDebug
unsigned int parseDebug;
#endif
#include "parseutils.h"
#include <X11/keysym.h>
#include <X11/extensions/XKBgeom.h>
#include <stdlib.h>


#line 84 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"

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

#include "xkbparse.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* END_OF_FILE  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ERROR_TOK = 3,                  /* ERROR_TOK  */
  YYSYMBOL_XKB_KEYMAP = 4,                 /* XKB_KEYMAP  */
  YYSYMBOL_XKB_KEYCODES = 5,               /* XKB_KEYCODES  */
  YYSYMBOL_XKB_TYPES = 6,                  /* XKB_TYPES  */
  YYSYMBOL_XKB_SYMBOLS = 7,                /* XKB_SYMBOLS  */
  YYSYMBOL_XKB_COMPATMAP = 8,              /* XKB_COMPATMAP  */
  YYSYMBOL_XKB_GEOMETRY = 9,               /* XKB_GEOMETRY  */
  YYSYMBOL_XKB_SEMANTICS = 10,             /* XKB_SEMANTICS  */
  YYSYMBOL_XKB_LAYOUT = 11,                /* XKB_LAYOUT  */
  YYSYMBOL_INCLUDE = 12,                   /* INCLUDE  */
  YYSYMBOL_OVERRIDE = 13,                  /* OVERRIDE  */
  YYSYMBOL_AUGMENT = 14,                   /* AUGMENT  */
  YYSYMBOL_REPLACE = 15,                   /* REPLACE  */
  YYSYMBOL_ALTERNATE = 16,                 /* ALTERNATE  */
  YYSYMBOL_VIRTUAL_MODS = 17,              /* VIRTUAL_MODS  */
  YYSYMBOL_TYPE = 18,                      /* TYPE  */
  YYSYMBOL_INTERPRET = 19,                 /* INTERPRET  */
  YYSYMBOL_ACTION_TOK = 20,                /* ACTION_TOK  */
  YYSYMBOL_KEY = 21,                       /* KEY  */
  YYSYMBOL_ALIAS = 22,                     /* ALIAS  */
  YYSYMBOL_GROUP = 23,                     /* GROUP  */
  YYSYMBOL_MODIFIER_MAP = 24,              /* MODIFIER_MAP  */
  YYSYMBOL_INDICATOR = 25,                 /* INDICATOR  */
  YYSYMBOL_SHAPE = 26,                     /* SHAPE  */
  YYSYMBOL_KEYS = 27,                      /* KEYS  */
  YYSYMBOL_ROW = 28,                       /* ROW  */
  YYSYMBOL_SECTION = 29,                   /* SECTION  */
  YYSYMBOL_OVERLAY = 30,                   /* OVERLAY  */
  YYSYMBOL_TEXT = 31,                      /* TEXT  */
  YYSYMBOL_OUTLINE = 32,                   /* OUTLINE  */
  YYSYMBOL_SOLID = 33,                     /* SOLID  */
  YYSYMBOL_LOGO = 34,                      /* LOGO  */
  YYSYMBOL_VIRTUAL = 35,                   /* VIRTUAL  */
  YYSYMBOL_EQUALS = 36,                    /* EQUALS  */
  YYSYMBOL_PLUS = 37,                      /* PLUS  */
  YYSYMBOL_MINUS = 38,                     /* MINUS  */
  YYSYMBOL_DIVIDE = 39,                    /* DIVIDE  */
  YYSYMBOL_TIMES = 40,                     /* TIMES  */
  YYSYMBOL_OBRACE = 41,                    /* OBRACE  */
  YYSYMBOL_CBRACE = 42,                    /* CBRACE  */
  YYSYMBOL_OPAREN = 43,                    /* OPAREN  */
  YYSYMBOL_CPAREN = 44,                    /* CPAREN  */
  YYSYMBOL_OBRACKET = 45,                  /* OBRACKET  */
  YYSYMBOL_CBRACKET = 46,                  /* CBRACKET  */
  YYSYMBOL_DOT = 47,                       /* DOT  */
  YYSYMBOL_COMMA = 48,                     /* COMMA  */
  YYSYMBOL_SEMI = 49,                      /* SEMI  */
  YYSYMBOL_EXCLAM = 50,                    /* EXCLAM  */
  YYSYMBOL_INVERT = 51,                    /* INVERT  */
  YYSYMBOL_STRING = 52,                    /* STRING  */
  YYSYMBOL_INTEGER = 53,                   /* INTEGER  */
  YYSYMBOL_FLOAT = 54,                     /* FLOAT  */
  YYSYMBOL_IDENT = 55,                     /* IDENT  */
  YYSYMBOL_KEYNAME = 56,                   /* KEYNAME  */
  YYSYMBOL_PARTIAL = 57,                   /* PARTIAL  */
  YYSYMBOL_DEFAULT = 58,                   /* DEFAULT  */
  YYSYMBOL_HIDDEN = 59,                    /* HIDDEN  */
  YYSYMBOL_ALPHANUMERIC_KEYS = 60,         /* ALPHANUMERIC_KEYS  */
  YYSYMBOL_MODIFIER_KEYS = 61,             /* MODIFIER_KEYS  */
  YYSYMBOL_KEYPAD_KEYS = 62,               /* KEYPAD_KEYS  */
  YYSYMBOL_FUNCTION_KEYS = 63,             /* FUNCTION_KEYS  */
  YYSYMBOL_ALTERNATE_GROUP = 64,           /* ALTERNATE_GROUP  */
  YYSYMBOL_YYACCEPT = 65,                  /* $accept  */
  YYSYMBOL_XkbFile = 66,                   /* XkbFile  */
  YYSYMBOL_XkbCompMapList = 67,            /* XkbCompMapList  */
  YYSYMBOL_XkbCompositeMap = 68,           /* XkbCompositeMap  */
  YYSYMBOL_XkbCompositeType = 69,          /* XkbCompositeType  */
  YYSYMBOL_XkbMapConfigList = 70,          /* XkbMapConfigList  */
  YYSYMBOL_XkbMapConfig = 71,              /* XkbMapConfig  */
  YYSYMBOL_XkbConfig = 72,                 /* XkbConfig  */
  YYSYMBOL_FileType = 73,                  /* FileType  */
  YYSYMBOL_OptFlags = 74,                  /* OptFlags  */
  YYSYMBOL_Flags = 75,                     /* Flags  */
  YYSYMBOL_Flag = 76,                      /* Flag  */
  YYSYMBOL_DeclList = 77,                  /* DeclList  */
  YYSYMBOL_Decl = 78,                      /* Decl  */
  YYSYMBOL_VarDecl = 79,                   /* VarDecl  */
  YYSYMBOL_KeyNameDecl = 80,               /* KeyNameDecl  */
  YYSYMBOL_KeyAliasDecl = 81,              /* KeyAliasDecl  */
  YYSYMBOL_VModDecl = 82,                  /* VModDecl  */
  YYSYMBOL_VModDefList = 83,               /* VModDefList  */
  YYSYMBOL_VModDef = 84,                   /* VModDef  */
  YYSYMBOL_InterpretDecl = 85,             /* InterpretDecl  */
  YYSYMBOL_InterpretMatch = 86,            /* InterpretMatch  */
  YYSYMBOL_VarDeclList = 87,               /* VarDeclList  */
  YYSYMBOL_KeyTypeDecl = 88,               /* KeyTypeDecl  */
  YYSYMBOL_SymbolsDecl = 89,               /* SymbolsDecl  */
  YYSYMBOL_SymbolsBody = 90,               /* SymbolsBody  */
  YYSYMBOL_SymbolsVarDecl = 91,            /* SymbolsVarDecl  */
  YYSYMBOL_ArrayInit = 92,                 /* ArrayInit  */
  YYSYMBOL_GroupCompatDecl = 93,           /* GroupCompatDecl  */
  YYSYMBOL_ModMapDecl = 94,                /* ModMapDecl  */
  YYSYMBOL_IndicatorMapDecl = 95,          /* IndicatorMapDecl  */
  YYSYMBOL_IndicatorNameDecl = 96,         /* IndicatorNameDecl  */
  YYSYMBOL_ShapeDecl = 97,                 /* ShapeDecl  */
  YYSYMBOL_SectionDecl = 98,               /* SectionDecl  */
  YYSYMBOL_SectionBody = 99,               /* SectionBody  */
  YYSYMBOL_SectionBodyItem = 100,          /* SectionBodyItem  */
  YYSYMBOL_RowBody = 101,                  /* RowBody  */
  YYSYMBOL_RowBodyItem = 102,              /* RowBodyItem  */
  YYSYMBOL_Keys = 103,                     /* Keys  */
  YYSYMBOL_Key = 104,                      /* Key  */
  YYSYMBOL_OverlayDecl = 105,              /* OverlayDecl  */
  YYSYMBOL_OverlayKeyList = 106,           /* OverlayKeyList  */
  YYSYMBOL_OverlayKey = 107,               /* OverlayKey  */
  YYSYMBOL_OutlineList = 108,              /* OutlineList  */
  YYSYMBOL_OutlineInList = 109,            /* OutlineInList  */
  YYSYMBOL_CoordList = 110,                /* CoordList  */
  YYSYMBOL_Coord = 111,                    /* Coord  */
  YYSYMBOL_DoodadDecl = 112,               /* DoodadDecl  */
  YYSYMBOL_DoodadType = 113,               /* DoodadType  */
  YYSYMBOL_FieldSpec = 114,                /* FieldSpec  */
  YYSYMBOL_Element = 115,                  /* Element  */
  YYSYMBOL_OptMergeMode = 116,             /* OptMergeMode  */
  YYSYMBOL_MergeMode = 117,                /* MergeMode  */
  YYSYMBOL_OptExprList = 118,              /* OptExprList  */
  YYSYMBOL_ExprList = 119,                 /* ExprList  */
  YYSYMBOL_Expr = 120,                     /* Expr  */
  YYSYMBOL_Term = 121,                     /* Term  */
  YYSYMBOL_StrictActionList = 122,         /* StrictActionList  */
  YYSYMBOL_ActionList = 123,               /* ActionList  */
  YYSYMBOL_Action = 124,                   /* Action  */
  YYSYMBOL_Actions = 125,                  /* Actions  */
  YYSYMBOL_Lhs = 126,                      /* Lhs  */
  YYSYMBOL_Terminal = 127,                 /* Terminal  */
  YYSYMBOL_OptKeySymList = 128,            /* OptKeySymList  */
  YYSYMBOL_StrictKeySymList = 129,         /* StrictKeySymList  */
  YYSYMBOL_KeySymList = 130,               /* KeySymList  */
  YYSYMBOL_KeySym = 131,                   /* KeySym  */
  YYSYMBOL_KeySyms = 132,                  /* KeySyms  */
  YYSYMBOL_SignedNumber = 133,             /* SignedNumber  */
  YYSYMBOL_Number = 134,                   /* Number  */
  YYSYMBOL_Float = 135,                    /* Float  */
  YYSYMBOL_Integer = 136,                  /* Integer  */
  YYSYMBOL_KeyName = 137,                  /* KeyName  */
  YYSYMBOL_Ident = 138,                    /* Ident  */
  YYSYMBOL_String = 139,                   /* String  */
  YYSYMBOL_OptMapName = 140,               /* OptMapName  */
  YYSYMBOL_MapName = 141                   /* MapName  */
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
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   864

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  195
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  353

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   257


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
       0,     4,     5,     6,     7,     8,     9,    10,    11,     2,
      12,    13,    14,    15,    16,     2,     2,     2,     2,     2,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,     2,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,     2,     2,     2,     2,
      52,    53,    54,    55,    56,     2,     2,     2,     2,     2,
      57,    58,    59,    60,    61,    62,    63,    64,     2,     2,
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
       2,     2,     2,     2,     2,     3,     1,     2
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   168,   168,   170,   172,   176,   178,   182,   188,   189,
     190,   193,   195,   199,   205,   210,   211,   212,   213,   214,
     217,   218,   221,   222,   225,   226,   227,   228,   229,   230,
     231,   232,   235,   237,   240,   245,   250,   255,   260,   265,
     270,   275,   280,   285,   290,   295,   300,   305,   310,   322,
     324,   326,   330,   341,   351,   355,   357,   361,   363,   367,
     376,   378,   382,   384,   388,   394,   400,   402,   404,   407,
     409,   411,   413,   415,   419,   421,   425,   429,   433,   437,
     439,   443,   445,   453,   457,   459,   463,   465,   467,   469,
     471,   475,   477,   481,   483,   487,   489,   493,   495,   499,
     503,   508,   512,   516,   518,   522,   524,   526,   530,   532,
     536,   546,   550,   551,   552,   553,   556,   557,   560,   562,
     564,   566,   568,   570,   572,   574,   576,   578,   580,   584,
     585,   588,   589,   590,   591,   592,   595,   596,   599,   601,
     605,   607,   609,   611,   613,   615,   619,   621,   623,   625,
     627,   629,   631,   633,   635,   640,   642,   647,   649,   651,
     653,   657,   666,   679,   686,   694,   703,   714,   721,   728,
     735,   746,   747,   751,   753,   758,   760,   762,   764,   768,
     769,   770,   782,   792,   793,   796,   797,   800,   803,   806,
     809,   810,   813,   816,   817,   820
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
  "END_OF_FILE", "error", "\"invalid token\"", "ERROR_TOK", "XKB_KEYMAP",
  "XKB_KEYCODES", "XKB_TYPES", "XKB_SYMBOLS", "XKB_COMPATMAP",
  "XKB_GEOMETRY", "XKB_SEMANTICS", "XKB_LAYOUT", "INCLUDE", "OVERRIDE",
  "AUGMENT", "REPLACE", "ALTERNATE", "VIRTUAL_MODS", "TYPE", "INTERPRET",
  "ACTION_TOK", "KEY", "ALIAS", "GROUP", "MODIFIER_MAP", "INDICATOR",
  "SHAPE", "KEYS", "ROW", "SECTION", "OVERLAY", "TEXT", "OUTLINE", "SOLID",
  "LOGO", "VIRTUAL", "EQUALS", "PLUS", "MINUS", "DIVIDE", "TIMES",
  "OBRACE", "CBRACE", "OPAREN", "CPAREN", "OBRACKET", "CBRACKET", "DOT",
  "COMMA", "SEMI", "EXCLAM", "INVERT", "STRING", "INTEGER", "FLOAT",
  "IDENT", "KEYNAME", "PARTIAL", "DEFAULT", "HIDDEN", "ALPHANUMERIC_KEYS",
  "MODIFIER_KEYS", "KEYPAD_KEYS", "FUNCTION_KEYS", "ALTERNATE_GROUP",
  "$accept", "XkbFile", "XkbCompMapList", "XkbCompositeMap",
  "XkbCompositeType", "XkbMapConfigList", "XkbMapConfig", "XkbConfig",
  "FileType", "OptFlags", "Flags", "Flag", "DeclList", "Decl", "VarDecl",
  "KeyNameDecl", "KeyAliasDecl", "VModDecl", "VModDefList", "VModDef",
  "InterpretDecl", "InterpretMatch", "VarDeclList", "KeyTypeDecl",
  "SymbolsDecl", "SymbolsBody", "SymbolsVarDecl", "ArrayInit",
  "GroupCompatDecl", "ModMapDecl", "IndicatorMapDecl", "IndicatorNameDecl",
  "ShapeDecl", "SectionDecl", "SectionBody", "SectionBodyItem", "RowBody",
  "RowBodyItem", "Keys", "Key", "OverlayDecl", "OverlayKeyList",
  "OverlayKey", "OutlineList", "OutlineInList", "CoordList", "Coord",
  "DoodadDecl", "DoodadType", "FieldSpec", "Element", "OptMergeMode",
  "MergeMode", "OptExprList", "ExprList", "Expr", "Term",
  "StrictActionList", "ActionList", "Action", "Actions", "Lhs", "Terminal",
  "OptKeySymList", "StrictKeySymList", "KeySymList", "KeySym", "KeySyms",
  "SignedNumber", "Number", "Float", "Integer", "KeyName", "Ident",
  "String", "OptMapName", "MapName", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-178)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-191)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     585,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,    31,
       6,  -178,    16,  -178,  -178,   807,   585,  -178,  -178,  -178,
      97,  -178,   382,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,   -13,   -13,  -178,   -13,  -178,    53,  -178,    65,    65,
     585,  -178,   185,    74,    11,  -178,  -178,  -178,  -178,  -178,
    -178,   351,    67,    78,    81,    -7,    89,    -1,  -178,    58,
      58,   112,    -7,     7,    89,  -178,    89,   121,  -178,  -178,
    -178,   153,    -7,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
      89,    36,  -178,   147,   157,   130,  -178,  -178,  -178,    23,
    -178,   159,  -178,   161,  -178,  -178,  -178,   162,   176,  -178,
     173,   186,   188,   195,   202,   212,   214,   216,   112,   211,
     223,   415,   806,   415,   415,  -178,    -7,  -178,   415,   709,
     709,   415,   302,    58,   415,   415,   415,   709,    -8,   538,
     233,  -178,   709,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,   415,   415,   806,   415,   415,   415,  -178,   143,
     264,  -178,  -178,   236,  -178,  -178,  -178,  -178,  -178,  -178,
     235,    49,   109,  -178,   383,  -178,   555,   583,   383,   598,
      -7,    42,  -178,  -178,   257,    62,   248,   113,   164,   383,
     131,   639,   253,     4,   168,  -178,   175,  -178,   263,    89,
     265,    89,  -178,  -178,   497,  -178,  -178,  -178,   415,   654,
    -178,  -178,  -178,   262,   183,  -178,   306,  -178,  -178,   415,
     415,   415,   415,   415,  -178,   415,   415,  -178,  -178,   260,
    -178,   268,   269,   723,   271,    51,  -178,  -178,   261,   270,
    -178,  -178,  -178,   280,   302,   374,  -178,  -178,   283,   415,
    -178,   285,   193,    91,  -178,  -178,   287,  -178,   291,   -23,
     299,   253,   456,   695,   278,   300,  -178,   181,   309,   415,
    -178,   806,  -178,   267,   303,   136,   136,  -178,  -178,   383,
     316,  -178,  -178,   203,  -178,  -178,   764,  -178,   -12,  -178,
    -178,  -178,   383,  -178,   383,  -178,  -178,  -178,     4,  -178,
    -178,  -178,  -178,   778,   383,   322,  -178,   258,  -178,    58,
    -178,  -178,  -178,   320,  -178,  -178,  -178,  -178,    -1,  -178,
    -178,    -1,  -178,  -178,   321,   206,   -20,   317,  -178,   225,
    -178,   345,  -178,  -178,  -178,  -178,   415,   226,  -178,  -178,
    -178,   347,    58,    58,   246,   355,   -20,  -178,  -178,  -178,
    -178,  -178,  -178
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      21,    24,    25,    26,    27,    28,    29,    30,    31,     0,
      21,     6,    21,    12,     4,     0,    20,    23,     1,     5,
       0,    11,     0,     8,    15,    16,    18,    17,    19,     9,
      10,   194,   194,    22,   194,   195,     0,   193,    33,     0,
      21,    33,   130,    21,   130,   131,   133,   132,   134,   135,
      32,     0,   129,     0,     0,     0,   120,   119,   118,   121,
       0,   122,   123,   124,   125,   126,   127,   128,   113,   114,
     115,     0,     0,   190,   189,   191,    34,    37,    38,    35,
      36,    39,    40,    42,    41,    43,    44,    45,    46,    47,
       0,   163,   117,     0,     0,   116,    48,     7,    13,     0,
      56,    57,   192,     0,   180,   188,   179,     0,    61,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    50,     0,    54,     0,     0,
       0,     0,    68,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,   120,   119,   121,   122,   123,   124,   125,
     127,   128,     0,     0,     0,     0,     0,     0,   187,   163,
       0,   145,   152,   150,   153,   169,   168,   170,   116,   167,
     164,     0,     0,    55,    58,    63,     0,     0,    60,   172,
       0,     0,    67,    73,     0,   116,     0,     0,     0,   139,
       0,     0,     0,     0,     0,   104,     0,   109,     0,   124,
     126,     0,    87,    89,     0,    85,    90,    88,     0,     0,
     147,   150,   146,     0,     0,   156,     0,   148,   149,   137,
       0,     0,     0,     0,   165,     0,     0,    49,    52,     0,
      62,     0,   180,     0,   179,     0,   159,   160,     0,   171,
     177,   178,    72,     0,     0,     0,    53,    76,     0,     0,
      79,     0,     0,     0,   186,   185,     0,   184,     0,     0,
       0,     0,     0,     0,     0,     0,    84,     0,     0,   137,
     162,     0,   154,     0,   136,   141,   142,   140,   143,   144,
       0,    64,    59,     0,   174,    75,     0,    74,     0,    65,
      66,    70,    69,    77,   138,    78,   105,   183,     0,    81,
     103,    82,   108,     0,   107,     0,    94,     0,    92,     0,
      83,    80,   111,     0,   155,   151,   166,   182,     0,   157,
     158,     0,   175,   176,     0,     0,     0,     0,    91,     0,
     101,     0,   161,   173,   110,   106,     0,     0,    96,    97,
      86,     0,     0,     0,     0,     0,     0,    99,   100,   102,
      98,    93,    95
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,  -178,  -178,   398,  -178,   370,     1,  -178,   391,    30,
    -178,   400,   373,  -178,   -48,  -178,  -178,  -178,  -178,   292,
    -178,  -178,   -81,  -178,  -178,  -178,   187,   192,  -178,  -178,
     394,  -178,  -178,  -178,  -178,   238,  -178,   140,  -178,   102,
    -178,  -178,   107,  -178,   198,  -177,   199,   408,  -178,   -37,
    -178,  -178,  -178,   194,  -125,   116,   298,  -178,  -178,  -175,
    -168,    52,  -178,  -178,  -178,  -178,   -55,   174,   163,   219,
    -178,   -56,   -51,   -17,   -44,   132,  -178
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     9,    10,    11,    31,    12,    13,    14,    32,    22,
      16,    17,    42,    50,   175,    77,    78,    79,    99,   100,
      80,   107,   176,    81,    82,   181,   182,   183,    83,    84,
     203,    86,    87,    88,   204,   205,   307,   308,   337,   338,
     206,   329,   330,   194,   195,   196,   197,   207,    90,   159,
      92,    51,    52,   273,   274,   189,   161,   214,   235,   215,
     162,   163,   164,   238,   283,   239,   284,   241,   256,   257,
     165,   166,   167,   168,   169,    36,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      94,   109,   108,    76,   236,   112,    -2,   114,   110,   111,
     188,   237,   103,    21,    91,   252,    -3,   104,   192,   115,
     116,   336,   117,    45,    46,    47,    48,    49,   104,   321,
      15,    18,    73,   192,    95,    75,    74,   193,   101,    35,
      20,   105,   253,   106,    21,   113,   120,    73,    73,   177,
      75,    75,   105,    54,   106,   119,   191,   254,   255,   102,
     105,   209,   140,     1,     2,     3,     4,     5,     6,     7,
       8,   126,   127,     1,     2,     3,     4,     5,     6,     7,
       8,   121,   186,   122,   243,   170,   220,   221,   222,   223,
     244,   202,    91,    91,    40,    91,   314,   285,   227,   286,
      91,    23,    91,    93,   -71,    91,    41,    29,    30,   101,
     -71,   319,    95,    95,    74,   185,    53,   213,   320,    96,
      95,   198,    95,   109,   240,    95,   325,    97,   230,   230,
      98,     1,     2,     3,     4,     5,     6,     7,     8,    91,
      91,   102,   213,   230,   254,   255,   220,   221,   222,   223,
     220,   221,   222,   223,    91,   115,   202,   264,   228,    95,
      95,   230,   247,   242,    38,   105,    39,    91,   220,   221,
     222,   223,    91,  -112,    95,   222,   223,   109,   118,   125,
     250,    93,    93,   123,   184,   -14,   219,    95,   121,    93,
     122,    93,    95,   124,    93,   128,   213,    45,    46,    47,
      48,    49,   129,   130,   211,   211,   248,    91,   211,   211,
     258,   344,   249,   131,   132,   306,   259,   260,   220,   221,
     222,   223,   133,   261,   134,   270,    91,   185,    93,    93,
     311,   271,   109,   322,   213,   296,   135,   160,   136,   171,
     172,   261,   198,    93,   174,   317,    95,   178,   335,   213,
     187,   318,   190,   137,   261,   138,    93,   139,   331,   306,
     141,    93,   109,   333,   142,   109,   213,   341,   345,   208,
      91,   216,   225,   342,   346,   339,   143,   144,    58,   145,
     226,   146,   147,   148,   149,   305,    65,   150,   350,   151,
      95,   331,   349,   245,   249,   339,   184,   246,   193,   262,
     327,   220,   221,   222,   223,   269,   263,   287,    72,   281,
     224,   315,  -127,    73,  -190,    93,    75,   282,   288,   309,
     143,   144,    58,   145,   267,   146,   147,   148,   149,   289,
      65,   150,   293,   151,   295,   298,   275,   276,   277,   278,
     299,   279,   280,   220,   221,   222,   223,   179,   301,   310,
     272,   249,   180,   220,   221,   222,   223,    73,   312,    93,
      75,   292,   316,   326,   332,   294,   340,   334,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,   304,    65,
      66,   343,    67,    68,    69,    70,    71,    24,    25,    26,
      27,    28,   143,   144,    58,   145,   347,   146,   147,   148,
     149,    72,    65,   150,   351,   151,    73,    74,    19,    75,
      43,   152,   153,    34,    44,   154,    33,   155,   173,   179,
     220,   221,   222,   223,   156,   157,   102,   105,   158,    73,
      74,   290,    75,   143,   144,    58,   145,   291,   146,   147,
     148,   149,   266,    65,   150,    85,   151,   328,   352,   348,
     210,   212,   152,   153,   217,   218,   154,   300,   155,    89,
     302,   324,   323,   313,     0,   156,   157,   102,   105,   158,
      73,    74,   297,    75,   143,   144,    58,   145,     0,   146,
     147,   148,   149,     0,    65,   150,     0,   151,     0,     0,
       0,     0,     0,   152,   153,     0,     0,   303,     0,   155,
       0,     0,     0,     0,     0,     0,   156,   157,   102,   105,
     158,    73,    74,     0,    75,   143,   144,    58,   145,     0,
     146,   147,   199,   149,     0,   200,   150,   201,    67,    68,
      69,    70,     0,     0,     0,     0,     0,     0,     0,   265,
       0,     0,     0,     0,     0,     0,     0,    72,     0,     0,
       0,     0,    73,     0,     0,    75,   143,   144,    58,   145,
       0,   146,   147,   199,   149,     0,   200,   150,   201,    67,
      68,    69,    70,   143,   144,    58,   145,     0,   146,   147,
     148,   149,     0,    65,   150,     0,   151,     0,    72,     0,
       0,     0,     0,    73,     0,     0,    75,   229,     0,     0,
       0,   143,   144,    58,   145,    72,   146,   147,   148,   149,
      73,    65,   150,    75,   151,     0,   143,   144,    58,   145,
       0,   146,   147,   148,   149,   231,    65,   232,     0,   151,
       0,     0,     0,    72,     0,     0,     0,     0,    73,   233,
       0,    75,     1,     2,     3,     4,     5,     6,     7,     8,
       0,   105,     0,   234,     0,     0,    75,   143,   144,    58,
     145,     0,   146,   147,   148,   149,     0,    65,   150,     0,
     151,     0,   143,   144,    58,   145,     0,   146,   147,   148,
     149,   251,    65,   150,     0,   151,     0,     0,     0,    72,
       0,     0,     0,     0,    73,     0,   268,    75,     0,     0,
       0,     0,     0,     0,    72,     0,     0,     0,     0,    73,
       0,     0,    75,   143,   144,    58,   145,     0,   146,   147,
     148,   149,   305,    65,   150,     0,   151,   143,   144,    58,
     145,     0,   146,   147,   148,   149,     0,    65,   150,     0,
     151,   143,   144,    58,   145,    72,   146,   147,   148,   149,
      73,    65,   232,    75,   151,     0,     0,     0,     0,    72,
       0,     0,     0,     0,    73,     0,     0,    75,     0,     0,
       0,     0,     0,     0,     0,     0,   105,     0,   234,     0,
       0,    75,   143,   144,    58,   145,     0,   146,   147,   148,
     149,     0,    65,   150,     0,   151,   143,   144,    58,   145,
       0,   146,   147,   148,   149,   154,    65,   150,     0,   151,
       0,    23,    24,    25,    26,    27,    28,    29,    30,    73,
       0,     0,    75,   193,   143,   144,    58,   145,     0,   146,
     147,   148,   149,    73,    65,   150,    75,   151,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,     0,     0,    75
};

static const yytype_int16 yycheck[] =
{
      51,    57,    57,    51,   179,    61,     0,    63,    59,    60,
     135,   179,    56,    12,    51,   192,     0,    29,    41,    63,
      64,    41,    66,    12,    13,    14,    15,    16,    29,    41,
       0,     0,    55,    41,    51,    58,    56,    45,    55,    52,
      10,    53,    38,    55,    43,    62,    90,    55,    55,   130,
      58,    58,    53,    42,    55,    72,   137,    53,    54,    52,
      53,   142,   118,    57,    58,    59,    60,    61,    62,    63,
      64,    48,    49,    57,    58,    59,    60,    61,    62,    63,
      64,    45,   133,    47,    42,   122,    37,    38,    39,    40,
      48,   139,   129,   130,    41,   132,   271,    46,    49,    48,
     137,     4,   139,    51,    42,   142,    41,    10,    11,   126,
      48,   286,   129,   130,    56,   132,    42,   154,   286,    52,
     137,   138,   139,   179,   179,   142,   303,    49,   176,   177,
      49,    57,    58,    59,    60,    61,    62,    63,    64,   176,
     177,    52,   179,   191,    53,    54,    37,    38,    39,    40,
      37,    38,    39,    40,   191,   199,   204,   201,    49,   176,
     177,   209,    49,   180,    32,    53,    34,   204,    37,    38,
      39,    40,   209,    52,   191,    39,    40,   233,    25,    49,
      49,   129,   130,    36,   132,     0,    43,   204,    45,   137,
      47,   139,   209,    36,   142,    36,   233,    12,    13,    14,
      15,    16,    41,    41,   152,   153,    42,   244,   156,   157,
      42,   336,    48,    37,    41,   263,    48,    42,    37,    38,
      39,    40,    36,    48,    36,    42,   263,   244,   176,   177,
      49,    48,   288,   288,   271,    42,    41,   121,    36,   123,
     124,    48,   259,   191,   128,    42,   263,   131,    42,   286,
     134,    48,   136,    41,    48,    41,   204,    41,   309,   307,
      49,   209,   318,   318,    41,   321,   303,    42,    42,    36,
     307,   155,    36,    48,    48,   326,    18,    19,    20,    21,
      45,    23,    24,    25,    26,    27,    28,    29,    42,    31,
     307,   342,   343,    36,    48,   346,   244,    49,    45,    36,
      42,    37,    38,    39,    40,    43,    41,    46,    50,    49,
      46,    44,    43,    55,    43,   263,    58,    49,    48,    41,
      18,    19,    20,    21,   208,    23,    24,    25,    26,    49,
      28,    29,    49,    31,    49,    48,   220,   221,   222,   223,
      49,   225,   226,    37,    38,    39,    40,    45,    49,    49,
      44,    48,    50,    37,    38,    39,    40,    55,    49,   307,
      58,   245,    46,    41,    44,   249,    49,    46,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,   262,    28,
      29,    36,    31,    32,    33,    34,    35,     5,     6,     7,
       8,     9,    18,    19,    20,    21,    49,    23,    24,    25,
      26,    50,    28,    29,    49,    31,    55,    56,    10,    58,
      40,    37,    38,    22,    41,    41,    16,    43,   126,    45,
      37,    38,    39,    40,    50,    51,    52,    53,    54,    55,
      56,   244,    58,    18,    19,    20,    21,   245,    23,    24,
      25,    26,   204,    28,    29,    51,    31,   307,   346,   342,
     152,   153,    37,    38,   156,   157,    41,   259,    43,    51,
     261,   298,   288,   269,    -1,    50,    51,    52,    53,    54,
      55,    56,   253,    58,    18,    19,    20,    21,    -1,    23,
      24,    25,    26,    -1,    28,    29,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    37,    38,    -1,    -1,    41,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    -1,    58,    18,    19,    20,    21,    -1,
      23,    24,    25,    26,    -1,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    55,    -1,    -1,    58,    18,    19,    20,    21,
      -1,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,    34,    18,    19,    20,    21,    -1,    23,    24,
      25,    26,    -1,    28,    29,    -1,    31,    -1,    50,    -1,
      -1,    -1,    -1,    55,    -1,    -1,    58,    42,    -1,    -1,
      -1,    18,    19,    20,    21,    50,    23,    24,    25,    26,
      55,    28,    29,    58,    31,    -1,    18,    19,    20,    21,
      -1,    23,    24,    25,    26,    42,    28,    29,    -1,    31,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    55,    41,
      -1,    58,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    53,    -1,    55,    -1,    -1,    58,    18,    19,    20,
      21,    -1,    23,    24,    25,    26,    -1,    28,    29,    -1,
      31,    -1,    18,    19,    20,    21,    -1,    23,    24,    25,
      26,    42,    28,    29,    -1,    31,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    55,    -1,    42,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    55,
      -1,    -1,    58,    18,    19,    20,    21,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    31,    18,    19,    20,
      21,    -1,    23,    24,    25,    26,    -1,    28,    29,    -1,
      31,    18,    19,    20,    21,    50,    23,    24,    25,    26,
      55,    28,    29,    58,    31,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    55,    -1,
      -1,    58,    18,    19,    20,    21,    -1,    23,    24,    25,
      26,    -1,    28,    29,    -1,    31,    18,    19,    20,    21,
      -1,    23,    24,    25,    26,    41,    28,    29,    -1,    31,
      -1,     4,     5,     6,     7,     8,     9,    10,    11,    55,
      -1,    -1,    58,    45,    18,    19,    20,    21,    -1,    23,
      24,    25,    26,    55,    28,    29,    58,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    -1,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    57,    58,    59,    60,    61,    62,    63,    64,    66,
      67,    68,    70,    71,    72,    74,    75,    76,     0,    68,
      74,    71,    74,     4,     5,     6,     7,     8,     9,    10,
      11,    69,    73,    76,    73,    52,   140,   141,   140,   140,
      41,    41,    77,    70,    77,    12,    13,    14,    15,    16,
      78,   116,   117,    42,    42,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    28,    29,    31,    32,    33,
      34,    35,    50,    55,    56,    58,    79,    80,    81,    82,
      85,    88,    89,    93,    94,    95,    96,    97,    98,   112,
     113,   114,   115,   126,   137,   138,    52,    49,    49,    83,
      84,   138,    52,   139,    29,    53,    55,    86,   131,   136,
     137,   137,   136,   138,   136,   139,   139,   139,    25,   138,
     139,    45,    47,    36,    36,    49,    48,    49,    36,    41,
      41,    37,    41,    36,    36,    41,    36,    41,    41,    41,
     136,    49,    41,    18,    19,    21,    23,    24,    25,    26,
      29,    31,    37,    38,    41,    43,    50,    51,    54,   114,
     120,   121,   125,   126,   127,   135,   136,   137,   138,   139,
     114,   120,   120,    84,   120,    79,    87,    87,   120,    45,
      50,    90,    91,    92,   126,   138,   137,   120,   119,   120,
     120,    87,    41,    45,   108,   109,   110,   111,   138,    25,
      28,    30,    79,    95,    99,   100,   105,   112,    36,    87,
     121,   126,   121,   114,   122,   124,   120,   121,   121,    43,
      37,    38,    39,    40,    46,    36,    45,    49,    49,    42,
      79,    42,    29,    41,    55,   123,   124,   125,   128,   130,
     131,   132,   138,    42,    48,    36,    49,    49,    42,    48,
      49,    42,   110,    38,    53,    54,   133,   134,    42,    48,
      42,    48,    36,    41,   139,    42,   100,   120,    42,    43,
      42,    48,    44,   118,   119,   120,   120,   120,   120,   120,
     120,    49,    49,   129,   131,    46,    48,    46,    48,    49,
      91,    92,   120,    49,   120,    49,    42,   134,    48,    49,
     109,    49,   111,    41,   120,    27,    79,   101,   102,    41,
      49,    49,    49,   118,   124,    44,    46,    42,    48,   124,
     125,    41,   131,   132,   133,   110,    41,    42,   102,   106,
     107,   137,    44,   131,    46,    42,    41,   103,   104,   137,
      49,    42,    48,    36,   119,    42,    48,    49,   107,   137,
      42,    49,   104
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    66,    66,    67,    67,    68,    69,    69,
      69,    70,    70,    71,    72,    73,    73,    73,    73,    73,
      74,    74,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    76,    77,    77,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    79,
      79,    79,    80,    81,    82,    83,    83,    84,    84,    85,
      86,    86,    87,    87,    88,    89,    90,    90,    90,    91,
      91,    91,    91,    91,    92,    92,    93,    94,    95,    96,
      96,    97,    97,    98,    99,    99,   100,   100,   100,   100,
     100,   101,   101,   102,   102,   103,   103,   104,   104,   105,
     106,   106,   107,   108,   108,   109,   109,   109,   110,   110,
     111,   112,   113,   113,   113,   113,   114,   114,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   116,
     116,   117,   117,   117,   117,   117,   118,   118,   119,   119,
     120,   120,   120,   120,   120,   120,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   122,   122,   123,   123,   123,
     123,   124,   125,   126,   126,   126,   126,   127,   127,   127,
     127,   128,   128,   129,   129,   130,   130,   130,   130,   131,
     131,   131,   132,   133,   133,   134,   134,   135,   136,   137,
     138,   138,   139,   140,   140,   141
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     1,     7,     1,     1,
       1,     2,     1,     7,     4,     1,     1,     1,     1,     1,
       1,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     0,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       2,     3,     4,     5,     3,     3,     1,     1,     3,     6,
       3,     1,     2,     1,     6,     6,     3,     1,     0,     3,
       3,     1,     2,     1,     3,     3,     5,     6,     6,     5,
       6,     6,     6,     6,     2,     1,     5,     1,     1,     1,
       1,     2,     1,     5,     1,     3,     1,     1,     3,     6,
       3,     1,     3,     3,     1,     3,     5,     3,     3,     1,
       5,     6,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     1,     1,     1,     1,     1,     1,     0,     3,     1,
       3,     3,     3,     3,     3,     1,     2,     2,     2,     2,
       1,     4,     1,     1,     3,     3,     1,     3,     3,     1,
       1,     4,     3,     1,     3,     4,     6,     1,     1,     1,
       1,     1,     0,     3,     1,     3,     3,     1,     1,     1,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1
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

  if (yychar <= END_OF_FILE)
    {
      yychar = END_OF_FILE;
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
  case 2: /* XkbFile: XkbCompMapList  */
#line 169 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.file)= rtrnValue= (yyvsp[0].file); }
#line 1571 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 3: /* XkbFile: XkbMapConfigList  */
#line 171 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.file)= rtrnValue= (yyvsp[0].file);  }
#line 1577 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 4: /* XkbFile: XkbConfig  */
#line 173 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.file)= rtrnValue= (yyvsp[0].file); }
#line 1583 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 5: /* XkbCompMapList: XkbCompMapList XkbCompositeMap  */
#line 177 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.file)= (XkbFile *)AppendStmt(&(yyvsp[-1].file)->common,&(yyvsp[0].file)->common); }
#line 1589 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 6: /* XkbCompMapList: XkbCompositeMap  */
#line 179 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.file)= (yyvsp[0].file); }
#line 1595 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 7: /* XkbCompositeMap: OptFlags XkbCompositeType OptMapName OBRACE XkbMapConfigList CBRACE SEMI  */
#line 185 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.file)= CreateXKBFile((yyvsp[-5].uval),(yyvsp[-4].str),&(yyvsp[-2].file)->common,(yyvsp[-6].uval)); }
#line 1601 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 8: /* XkbCompositeType: XKB_KEYMAP  */
#line 188 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                        { (yyval.uval)= XkmKeymapFile; }
#line 1607 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 9: /* XkbCompositeType: XKB_SEMANTICS  */
#line 189 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                        { (yyval.uval)= XkmSemanticsFile; }
#line 1613 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 10: /* XkbCompositeType: XKB_LAYOUT  */
#line 190 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                        { (yyval.uval)= XkmLayoutFile; }
#line 1619 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 11: /* XkbMapConfigList: XkbMapConfigList XkbMapConfig  */
#line 194 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.file)= (XkbFile *)AppendStmt(&(yyvsp[-1].file)->common,&(yyvsp[0].file)->common); }
#line 1625 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 12: /* XkbMapConfigList: XkbMapConfig  */
#line 196 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.file)= (yyvsp[0].file); }
#line 1631 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 13: /* XkbMapConfig: OptFlags FileType OptMapName OBRACE DeclList CBRACE SEMI  */
#line 202 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.file)= CreateXKBFile((yyvsp[-5].uval),(yyvsp[-4].str),(yyvsp[-2].any),(yyvsp[-6].uval)); }
#line 1637 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 14: /* XkbConfig: OptFlags FileType OptMapName DeclList  */
#line 206 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.file)= CreateXKBFile((yyvsp[-2].uval),(yyvsp[-1].str),(yyvsp[0].any),(yyvsp[-3].uval)); }
#line 1643 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 15: /* FileType: XKB_KEYCODES  */
#line 210 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkmKeyNamesIndex; }
#line 1649 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 16: /* FileType: XKB_TYPES  */
#line 211 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkmTypesIndex; }
#line 1655 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 17: /* FileType: XKB_COMPATMAP  */
#line 212 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkmCompatMapIndex; }
#line 1661 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 18: /* FileType: XKB_SYMBOLS  */
#line 213 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkmSymbolsIndex; }
#line 1667 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 19: /* FileType: XKB_GEOMETRY  */
#line 214 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkmGeometryIndex; }
#line 1673 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 20: /* OptFlags: Flags  */
#line 217 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= (yyvsp[0].uval); }
#line 1679 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 21: /* OptFlags: %empty  */
#line 218 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= 0; }
#line 1685 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 22: /* Flags: Flags Flag  */
#line 221 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= (((yyvsp[-1].uval))|((yyvsp[0].uval))); }
#line 1691 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 23: /* Flags: Flag  */
#line 222 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= (yyvsp[0].uval); }
#line 1697 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 24: /* Flag: PARTIAL  */
#line 225 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkbLC_Partial; }
#line 1703 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 25: /* Flag: DEFAULT  */
#line 226 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkbLC_Default; }
#line 1709 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 26: /* Flag: HIDDEN  */
#line 227 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkbLC_Hidden; }
#line 1715 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 27: /* Flag: ALPHANUMERIC_KEYS  */
#line 228 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkbLC_AlphanumericKeys; }
#line 1721 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 28: /* Flag: MODIFIER_KEYS  */
#line 229 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkbLC_ModifierKeys; }
#line 1727 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 29: /* Flag: KEYPAD_KEYS  */
#line 230 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkbLC_KeypadKeys; }
#line 1733 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 30: /* Flag: FUNCTION_KEYS  */
#line 231 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkbLC_FunctionKeys; }
#line 1739 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 31: /* Flag: ALTERNATE_GROUP  */
#line 232 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkbLC_AlternateGroup; }
#line 1745 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 32: /* DeclList: DeclList Decl  */
#line 236 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.any)= AppendStmt((yyvsp[-1].any),(yyvsp[0].any)); }
#line 1751 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 33: /* DeclList: %empty  */
#line 237 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.any)= NULL; }
#line 1757 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 34: /* Decl: OptMergeMode VarDecl  */
#line 241 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].var)->merge= StmtSetMerge(&(yyvsp[0].var)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].var)->common;
			}
#line 1766 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 35: /* Decl: OptMergeMode VModDecl  */
#line 246 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].vmod)->merge= StmtSetMerge(&(yyvsp[0].vmod)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].vmod)->common;
			}
#line 1775 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 36: /* Decl: OptMergeMode InterpretDecl  */
#line 251 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].interp)->merge= StmtSetMerge(&(yyvsp[0].interp)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].interp)->common;
			}
#line 1784 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 37: /* Decl: OptMergeMode KeyNameDecl  */
#line 256 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].keyName)->merge= StmtSetMerge(&(yyvsp[0].keyName)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].keyName)->common;
			}
#line 1793 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 38: /* Decl: OptMergeMode KeyAliasDecl  */
#line 261 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].keyAlias)->merge= StmtSetMerge(&(yyvsp[0].keyAlias)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].keyAlias)->common;
			}
#line 1802 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 39: /* Decl: OptMergeMode KeyTypeDecl  */
#line 266 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].keyType)->merge= StmtSetMerge(&(yyvsp[0].keyType)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].keyType)->common;
			}
#line 1811 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 40: /* Decl: OptMergeMode SymbolsDecl  */
#line 271 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].syms)->merge= StmtSetMerge(&(yyvsp[0].syms)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].syms)->common;
			}
#line 1820 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 41: /* Decl: OptMergeMode ModMapDecl  */
#line 276 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].modMask)->merge= StmtSetMerge(&(yyvsp[0].modMask)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].modMask)->common;
			}
#line 1829 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 42: /* Decl: OptMergeMode GroupCompatDecl  */
#line 281 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].groupCompat)->merge= StmtSetMerge(&(yyvsp[0].groupCompat)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].groupCompat)->common;
			}
#line 1838 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 43: /* Decl: OptMergeMode IndicatorMapDecl  */
#line 286 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].ledMap)->merge= StmtSetMerge(&(yyvsp[0].ledMap)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].ledMap)->common;
			}
#line 1847 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 44: /* Decl: OptMergeMode IndicatorNameDecl  */
#line 291 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].ledName)->merge= StmtSetMerge(&(yyvsp[0].ledName)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].ledName)->common;
			}
#line 1856 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 45: /* Decl: OptMergeMode ShapeDecl  */
#line 296 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].shape)->merge= StmtSetMerge(&(yyvsp[0].shape)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].shape)->common;
			}
#line 1865 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 46: /* Decl: OptMergeMode SectionDecl  */
#line 301 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].section)->merge= StmtSetMerge(&(yyvsp[0].section)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].section)->common;
			}
#line 1874 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 47: /* Decl: OptMergeMode DoodadDecl  */
#line 306 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[0].doodad)->merge= StmtSetMerge(&(yyvsp[0].doodad)->common,(yyvsp[-1].uval));
			    (yyval.any)= &(yyvsp[0].doodad)->common;
			}
#line 1883 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 48: /* Decl: MergeMode STRING  */
#line 311 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    if ((yyvsp[-1].uval)==MergeAltForm) {
			        yyerror("cannot use 'alternate' to include other maps");
			        (yyval.any)= &IncludeCreate(scanBuf,MergeDefault)->common;
			    }
			    else {
			        (yyval.any)= &IncludeCreate(scanBuf,(yyvsp[-1].uval))->common;
			    }
			}
#line 1897 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 49: /* VarDecl: Lhs EQUALS Expr SEMI  */
#line 323 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.var)= VarCreate((yyvsp[-3].expr),(yyvsp[-1].expr)); }
#line 1903 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 50: /* VarDecl: Ident SEMI  */
#line 325 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.var)= BoolVarCreate((yyvsp[-1].sval),1); }
#line 1909 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 51: /* VarDecl: EXCLAM Ident SEMI  */
#line 327 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.var)= BoolVarCreate((yyvsp[-1].sval),0); }
#line 1915 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 52: /* KeyNameDecl: KeyName EQUALS Expr SEMI  */
#line 331 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    KeycodeDef *def;

			    def= KeycodeCreate((yyvsp[-3].str),(yyvsp[-1].expr));
			    if ((yyvsp[-3].str))
			        free((yyvsp[-3].str));
			    (yyval.keyName)= def;
			}
#line 1928 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 53: /* KeyAliasDecl: ALIAS KeyName EQUALS KeyName SEMI  */
#line 342 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    KeyAliasDef	*def;
			    def= KeyAliasCreate((yyvsp[-3].str),(yyvsp[-1].str));
			    if ((yyvsp[-3].str))	free((yyvsp[-3].str));
			    if ((yyvsp[-1].str))	free((yyvsp[-1].str));
			    (yyval.keyAlias)= def;
			}
#line 1940 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 54: /* VModDecl: VIRTUAL_MODS VModDefList SEMI  */
#line 352 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.vmod)= (yyvsp[-1].vmod); }
#line 1946 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 55: /* VModDefList: VModDefList COMMA VModDef  */
#line 356 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.vmod)= (VModDef *)AppendStmt(&(yyvsp[-2].vmod)->common,&(yyvsp[0].vmod)->common); }
#line 1952 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 56: /* VModDefList: VModDef  */
#line 358 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.vmod)= (yyvsp[0].vmod); }
#line 1958 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 57: /* VModDef: Ident  */
#line 362 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.vmod)= VModCreate((yyvsp[0].sval),NULL); }
#line 1964 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 58: /* VModDef: Ident EQUALS Expr  */
#line 364 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.vmod)= VModCreate((yyvsp[-2].sval),(yyvsp[0].expr)); }
#line 1970 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 59: /* InterpretDecl: INTERPRET InterpretMatch OBRACE VarDeclList CBRACE SEMI  */
#line 370 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyvsp[-4].interp)->def= (yyvsp[-2].var);
			    (yyval.interp)= (yyvsp[-4].interp);
			}
#line 1979 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 60: /* InterpretMatch: KeySym PLUS Expr  */
#line 377 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.interp)= InterpCreate((yyvsp[-2].str), (yyvsp[0].expr)); }
#line 1985 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 61: /* InterpretMatch: KeySym  */
#line 379 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.interp)= InterpCreate((yyvsp[0].str), NULL); }
#line 1991 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 62: /* VarDeclList: VarDeclList VarDecl  */
#line 383 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.var)= (VarDef *)AppendStmt(&(yyvsp[-1].var)->common,&(yyvsp[0].var)->common); }
#line 1997 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 63: /* VarDeclList: VarDecl  */
#line 385 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.var)= (yyvsp[0].var); }
#line 2003 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 64: /* KeyTypeDecl: TYPE String OBRACE VarDeclList CBRACE SEMI  */
#line 391 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.keyType)= KeyTypeCreate((yyvsp[-4].sval),(yyvsp[-2].var)); }
#line 2009 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 65: /* SymbolsDecl: KEY KeyName OBRACE SymbolsBody CBRACE SEMI  */
#line 397 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.syms)= SymbolsCreate((yyvsp[-4].str),(ExprDef *)(yyvsp[-2].var)); }
#line 2015 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 66: /* SymbolsBody: SymbolsBody COMMA SymbolsVarDecl  */
#line 401 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.var)= (VarDef *)AppendStmt(&(yyvsp[-2].var)->common,&(yyvsp[0].var)->common); }
#line 2021 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 67: /* SymbolsBody: SymbolsVarDecl  */
#line 403 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.var)= (yyvsp[0].var); }
#line 2027 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 68: /* SymbolsBody: %empty  */
#line 404 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.var)= NULL; }
#line 2033 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 69: /* SymbolsVarDecl: Lhs EQUALS Expr  */
#line 408 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.var)= VarCreate((yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 2039 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 70: /* SymbolsVarDecl: Lhs EQUALS ArrayInit  */
#line 410 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.var)= VarCreate((yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 2045 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 71: /* SymbolsVarDecl: Ident  */
#line 412 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.var)= BoolVarCreate((yyvsp[0].sval),1); }
#line 2051 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 72: /* SymbolsVarDecl: EXCLAM Ident  */
#line 414 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.var)= BoolVarCreate((yyvsp[0].sval),0); }
#line 2057 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 73: /* SymbolsVarDecl: ArrayInit  */
#line 416 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.var)= VarCreate(NULL,(yyvsp[0].expr)); }
#line 2063 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 74: /* ArrayInit: OBRACKET OptKeySymList CBRACKET  */
#line 420 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (yyvsp[-1].expr); }
#line 2069 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 75: /* ArrayInit: OBRACKET ActionList CBRACKET  */
#line 422 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= ExprCreateUnary(ExprActionList,TypeAction,(yyvsp[-1].expr)); }
#line 2075 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 76: /* GroupCompatDecl: GROUP Integer EQUALS Expr SEMI  */
#line 426 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.groupCompat)= GroupCompatCreate((yyvsp[-3].ival),(yyvsp[-1].expr)); }
#line 2081 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 77: /* ModMapDecl: MODIFIER_MAP Ident OBRACE ExprList CBRACE SEMI  */
#line 430 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.modMask)= ModMapCreate((yyvsp[-4].sval),(yyvsp[-2].expr)); }
#line 2087 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 78: /* IndicatorMapDecl: INDICATOR String OBRACE VarDeclList CBRACE SEMI  */
#line 434 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.ledMap)= IndicatorMapCreate((yyvsp[-4].sval),(yyvsp[-2].var)); }
#line 2093 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 79: /* IndicatorNameDecl: INDICATOR Integer EQUALS Expr SEMI  */
#line 438 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.ledName)= IndicatorNameCreate((yyvsp[-3].ival),(yyvsp[-1].expr),False); }
#line 2099 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 80: /* IndicatorNameDecl: VIRTUAL INDICATOR Integer EQUALS Expr SEMI  */
#line 440 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.ledName)= IndicatorNameCreate((yyvsp[-3].ival),(yyvsp[-1].expr),True); }
#line 2105 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 81: /* ShapeDecl: SHAPE String OBRACE OutlineList CBRACE SEMI  */
#line 444 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.shape)= ShapeDeclCreate((yyvsp[-4].sval),(OutlineDef *)&(yyvsp[-2].outline)->common); }
#line 2111 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 82: /* ShapeDecl: SHAPE String OBRACE CoordList CBRACE SEMI  */
#line 446 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    OutlineDef *outlines;
			    outlines= OutlineCreate(None,(yyvsp[-2].expr));
			    (yyval.shape)= ShapeDeclCreate((yyvsp[-4].sval),outlines);
			}
#line 2121 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 83: /* SectionDecl: SECTION String OBRACE SectionBody CBRACE SEMI  */
#line 454 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.section)= SectionDeclCreate((yyvsp[-4].sval),(yyvsp[-2].row)); }
#line 2127 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 84: /* SectionBody: SectionBody SectionBodyItem  */
#line 458 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.row)=(RowDef *)AppendStmt(&(yyvsp[-1].row)->common,&(yyvsp[0].row)->common);}
#line 2133 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 85: /* SectionBody: SectionBodyItem  */
#line 460 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.row)= (yyvsp[0].row); }
#line 2139 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 86: /* SectionBodyItem: ROW OBRACE RowBody CBRACE SEMI  */
#line 464 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.row)= RowDeclCreate((yyvsp[-2].key)); }
#line 2145 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 87: /* SectionBodyItem: VarDecl  */
#line 466 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.row)= (RowDef *)(yyvsp[0].var); }
#line 2151 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 88: /* SectionBodyItem: DoodadDecl  */
#line 468 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.row)= (RowDef *)(yyvsp[0].doodad); }
#line 2157 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 89: /* SectionBodyItem: IndicatorMapDecl  */
#line 470 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.row)= (RowDef *)(yyvsp[0].ledMap); }
#line 2163 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 90: /* SectionBodyItem: OverlayDecl  */
#line 472 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.row)= (RowDef *)(yyvsp[0].overlay); }
#line 2169 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 91: /* RowBody: RowBody RowBodyItem  */
#line 476 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.key)=(KeyDef *)AppendStmt(&(yyvsp[-1].key)->common,&(yyvsp[0].key)->common);}
#line 2175 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 92: /* RowBody: RowBodyItem  */
#line 478 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.key)= (yyvsp[0].key); }
#line 2181 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 93: /* RowBodyItem: KEYS OBRACE Keys CBRACE SEMI  */
#line 482 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.key)= (yyvsp[-2].key); }
#line 2187 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 94: /* RowBodyItem: VarDecl  */
#line 484 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.key)= (KeyDef *)(yyvsp[0].var); }
#line 2193 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 95: /* Keys: Keys COMMA Key  */
#line 488 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.key)=(KeyDef *)AppendStmt(&(yyvsp[-2].key)->common,&(yyvsp[0].key)->common);}
#line 2199 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 96: /* Keys: Key  */
#line 490 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.key)= (yyvsp[0].key); }
#line 2205 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 97: /* Key: KeyName  */
#line 494 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.key)= KeyDeclCreate((yyvsp[0].str),NULL); }
#line 2211 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 98: /* Key: OBRACE ExprList CBRACE  */
#line 496 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.key)= KeyDeclCreate(NULL,(yyvsp[-1].expr)); }
#line 2217 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 99: /* OverlayDecl: OVERLAY String OBRACE OverlayKeyList CBRACE SEMI  */
#line 500 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.overlay)= OverlayDeclCreate((yyvsp[-4].sval),(yyvsp[-2].olKey)); }
#line 2223 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 100: /* OverlayKeyList: OverlayKeyList COMMA OverlayKey  */
#line 504 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    (yyval.olKey)= (OverlayKeyDef *)
			        AppendStmt(&(yyvsp[-2].olKey)->common,&(yyvsp[0].olKey)->common);
			}
#line 2232 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 101: /* OverlayKeyList: OverlayKey  */
#line 509 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.olKey)= (yyvsp[0].olKey); }
#line 2238 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 102: /* OverlayKey: KeyName EQUALS KeyName  */
#line 513 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.olKey)= OverlayKeyCreate((yyvsp[-2].str),(yyvsp[0].str)); }
#line 2244 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 103: /* OutlineList: OutlineList COMMA OutlineInList  */
#line 517 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.outline)=(OutlineDef *)AppendStmt(&(yyvsp[-2].outline)->common,&(yyvsp[0].outline)->common);}
#line 2250 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 104: /* OutlineList: OutlineInList  */
#line 519 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.outline)= (yyvsp[0].outline); }
#line 2256 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 105: /* OutlineInList: OBRACE CoordList CBRACE  */
#line 523 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.outline)= OutlineCreate(None,(yyvsp[-1].expr)); }
#line 2262 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 106: /* OutlineInList: Ident EQUALS OBRACE CoordList CBRACE  */
#line 525 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.outline)= OutlineCreate((yyvsp[-4].sval),(yyvsp[-1].expr)); }
#line 2268 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 107: /* OutlineInList: Ident EQUALS Expr  */
#line 527 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.outline)= OutlineCreate((yyvsp[-2].sval),(yyvsp[0].expr)); }
#line 2274 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 108: /* CoordList: CoordList COMMA Coord  */
#line 531 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (ExprDef *)AppendStmt(&(yyvsp[-2].expr)->common,&(yyvsp[0].expr)->common); }
#line 2280 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 109: /* CoordList: Coord  */
#line 533 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (yyvsp[0].expr); }
#line 2286 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 110: /* Coord: OBRACKET SignedNumber COMMA SignedNumber CBRACKET  */
#line 537 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    ExprDef *expr;
			    expr= ExprCreate(ExprCoord,TypeUnknown);
			    expr->value.coord.x= (yyvsp[-3].ival);
			    expr->value.coord.y= (yyvsp[-1].ival);
			    (yyval.expr)= expr;
			}
#line 2298 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 111: /* DoodadDecl: DoodadType String OBRACE VarDeclList CBRACE SEMI  */
#line 547 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.doodad)= DoodadCreate((yyvsp[-5].uval),(yyvsp[-4].sval),(yyvsp[-2].var)); }
#line 2304 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 112: /* DoodadType: TEXT  */
#line 550 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkbTextDoodad; }
#line 2310 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 113: /* DoodadType: OUTLINE  */
#line 551 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkbOutlineDoodad; }
#line 2316 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 114: /* DoodadType: SOLID  */
#line 552 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkbSolidDoodad; }
#line 2322 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 115: /* DoodadType: LOGO  */
#line 553 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= XkbLogoDoodad; }
#line 2328 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 116: /* FieldSpec: Ident  */
#line 556 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.sval)= (yyvsp[0].sval); }
#line 2334 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 117: /* FieldSpec: Element  */
#line 557 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.sval)= (yyvsp[0].sval); }
#line 2340 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 118: /* Element: ACTION_TOK  */
#line 561 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.sval)= XkbInternAtom(NULL,"action",False); }
#line 2346 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 119: /* Element: INTERPRET  */
#line 563 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.sval)= XkbInternAtom(NULL,"interpret",False); }
#line 2352 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 120: /* Element: TYPE  */
#line 565 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.sval)= XkbInternAtom(NULL,"type",False); }
#line 2358 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 121: /* Element: KEY  */
#line 567 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.sval)= XkbInternAtom(NULL,"key",False); }
#line 2364 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 122: /* Element: GROUP  */
#line 569 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.sval)= XkbInternAtom(NULL,"group",False); }
#line 2370 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 123: /* Element: MODIFIER_MAP  */
#line 571 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {(yyval.sval)=XkbInternAtom(NULL,"modifier_map",False);}
#line 2376 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 124: /* Element: INDICATOR  */
#line 573 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.sval)= XkbInternAtom(NULL,"indicator",False); }
#line 2382 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 125: /* Element: SHAPE  */
#line 575 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.sval)= XkbInternAtom(NULL,"shape",False); }
#line 2388 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 126: /* Element: ROW  */
#line 577 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.sval)= XkbInternAtom(NULL,"row",False); }
#line 2394 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 127: /* Element: SECTION  */
#line 579 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.sval)= XkbInternAtom(NULL,"section",False); }
#line 2400 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 128: /* Element: TEXT  */
#line 581 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.sval)= XkbInternAtom(NULL,"text",False); }
#line 2406 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 129: /* OptMergeMode: MergeMode  */
#line 584 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= (yyvsp[0].uval); }
#line 2412 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 130: /* OptMergeMode: %empty  */
#line 585 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= MergeDefault; }
#line 2418 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 131: /* MergeMode: INCLUDE  */
#line 588 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= MergeDefault; }
#line 2424 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 132: /* MergeMode: AUGMENT  */
#line 589 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= MergeAugment; }
#line 2430 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 133: /* MergeMode: OVERRIDE  */
#line 590 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= MergeOverride; }
#line 2436 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 134: /* MergeMode: REPLACE  */
#line 591 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= MergeReplace; }
#line 2442 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 135: /* MergeMode: ALTERNATE  */
#line 592 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.uval)= MergeAltForm; }
#line 2448 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 136: /* OptExprList: ExprList  */
#line 595 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.expr)= (yyvsp[0].expr); }
#line 2454 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 137: /* OptExprList: %empty  */
#line 596 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                { (yyval.expr)= NULL; }
#line 2460 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 138: /* ExprList: ExprList COMMA Expr  */
#line 600 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (ExprDef *)AppendStmt(&(yyvsp[-2].expr)->common,&(yyvsp[0].expr)->common); }
#line 2466 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 139: /* ExprList: Expr  */
#line 602 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (yyvsp[0].expr); }
#line 2472 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 140: /* Expr: Expr DIVIDE Expr  */
#line 606 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= ExprCreateBinary(OpDivide,(yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 2478 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 141: /* Expr: Expr PLUS Expr  */
#line 608 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= ExprCreateBinary(OpAdd,(yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 2484 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 142: /* Expr: Expr MINUS Expr  */
#line 610 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= ExprCreateBinary(OpSubtract,(yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 2490 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 143: /* Expr: Expr TIMES Expr  */
#line 612 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= ExprCreateBinary(OpMultiply,(yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 2496 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 144: /* Expr: Lhs EQUALS Expr  */
#line 614 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= ExprCreateBinary(OpAssign,(yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 2502 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 145: /* Expr: Term  */
#line 616 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (yyvsp[0].expr); }
#line 2508 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 146: /* Term: MINUS Term  */
#line 620 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= ExprCreateUnary(OpNegate,(yyvsp[0].expr)->type,(yyvsp[0].expr)); }
#line 2514 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 147: /* Term: PLUS Term  */
#line 622 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= ExprCreateUnary(OpUnaryPlus,(yyvsp[0].expr)->type,(yyvsp[0].expr)); }
#line 2520 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 148: /* Term: EXCLAM Term  */
#line 624 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= ExprCreateUnary(OpNot,TypeBoolean,(yyvsp[0].expr)); }
#line 2526 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 149: /* Term: INVERT Term  */
#line 626 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= ExprCreateUnary(OpInvert,(yyvsp[0].expr)->type,(yyvsp[0].expr)); }
#line 2532 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 150: /* Term: Lhs  */
#line 628 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (yyvsp[0].expr); }
#line 2538 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 151: /* Term: FieldSpec OPAREN OptExprList CPAREN  */
#line 630 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= ActionCreate((yyvsp[-3].sval),(yyvsp[-1].expr)); }
#line 2544 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 152: /* Term: Actions  */
#line 632 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (yyvsp[0].expr); }
#line 2550 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 153: /* Term: Terminal  */
#line 634 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (yyvsp[0].expr); }
#line 2556 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 154: /* Term: OPAREN Expr CPAREN  */
#line 636 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (yyvsp[-1].expr); }
#line 2562 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 155: /* StrictActionList: StrictActionList COMMA Action  */
#line 641 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (ExprDef *)AppendStmt(&(yyvsp[-2].expr)->common,&(yyvsp[0].expr)->common); }
#line 2568 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 156: /* StrictActionList: Action  */
#line 643 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (yyvsp[0].expr); }
#line 2574 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 157: /* ActionList: ActionList COMMA Action  */
#line 648 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (ExprDef *)AppendStmt(&(yyvsp[-2].expr)->common,&(yyvsp[0].expr)->common); }
#line 2580 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 158: /* ActionList: ActionList COMMA Actions  */
#line 650 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (ExprDef *)AppendStmt(&(yyvsp[-2].expr)->common,&(yyvsp[0].expr)->common); }
#line 2586 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 159: /* ActionList: Action  */
#line 652 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (yyvsp[0].expr); }
#line 2592 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 160: /* ActionList: Actions  */
#line 654 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= (yyvsp[0].expr); }
#line 2598 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 161: /* Action: FieldSpec OPAREN OptExprList CPAREN  */
#line 658 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= ActionCreate((yyvsp[-3].sval),(yyvsp[-1].expr)); }
#line 2604 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 162: /* Actions: OBRACE StrictActionList CBRACE  */
#line 667 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    yyerror("Multiple actions per level is not "
			            "supported; list replaced by NoAction()");
			    // TODO: properly free actions list
			    free((yyvsp[-1].expr));
			    (yyval.expr)= ActionCreate(
			        XkbInternAtom(NULL, "NoAction", False),
			        NULL
			    );
			}
#line 2619 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 163: /* Lhs: FieldSpec  */
#line 680 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    ExprDef *expr;
			    expr= ExprCreate(ExprIdent,TypeUnknown);
			    expr->value.str= (yyvsp[0].sval);
			    (yyval.expr)= expr;
			}
#line 2630 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 164: /* Lhs: FieldSpec DOT FieldSpec  */
#line 687 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    ExprDef *expr;
			    expr= ExprCreate(ExprFieldRef,TypeUnknown);
			    expr->value.field.element= (yyvsp[-2].sval);
			    expr->value.field.field= (yyvsp[0].sval);
			    (yyval.expr)= expr;
			}
#line 2642 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 165: /* Lhs: FieldSpec OBRACKET Expr CBRACKET  */
#line 695 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    ExprDef *expr;
			    expr= ExprCreate(ExprArrayRef,TypeUnknown);
			    expr->value.array.element= None;
			    expr->value.array.field= (yyvsp[-3].sval);
			    expr->value.array.entry= (yyvsp[-1].expr);
			    (yyval.expr)= expr;
			}
#line 2655 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 166: /* Lhs: FieldSpec DOT FieldSpec OBRACKET Expr CBRACKET  */
#line 704 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    ExprDef *expr;
			    expr= ExprCreate(ExprArrayRef,TypeUnknown);
			    expr->value.array.element= (yyvsp[-5].sval);
			    expr->value.array.field= (yyvsp[-3].sval);
			    expr->value.array.entry= (yyvsp[-1].expr);
			    (yyval.expr)= expr;
			}
#line 2668 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 167: /* Terminal: String  */
#line 715 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    ExprDef *expr;
			    expr= ExprCreate(ExprValue,TypeString);
			    expr->value.str= (yyvsp[0].sval);
			    (yyval.expr)= expr;
			}
#line 2679 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 168: /* Terminal: Integer  */
#line 722 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    ExprDef *expr;
			    expr= ExprCreate(ExprValue,TypeInt);
			    expr->value.ival= (yyvsp[0].ival);
			    (yyval.expr)= expr;
			}
#line 2690 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 169: /* Terminal: Float  */
#line 729 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    ExprDef *expr;
			    expr= ExprCreate(ExprValue,TypeFloat);
			    expr->value.ival= (yyvsp[0].ival);
			    (yyval.expr)= expr;
			}
#line 2701 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 170: /* Terminal: KeyName  */
#line 736 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    ExprDef *expr;
			    expr= ExprCreate(ExprValue,TypeKeyName);
			    memset(expr->value.keyName,0,5);
			    strncpy(expr->value.keyName,(yyvsp[0].str),4);
			    free((yyvsp[0].str));
			    (yyval.expr)= expr;
			}
#line 2714 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 171: /* OptKeySymList: KeySymList  */
#line 746 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                        { (yyval.expr)= (yyvsp[0].expr); }
#line 2720 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 172: /* OptKeySymList: %empty  */
#line 747 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                                        { (yyval.expr)= NULL; }
#line 2726 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 173: /* StrictKeySymList: StrictKeySymList COMMA KeySym  */
#line 752 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= AppendKeysymList((yyvsp[-2].expr),(yyvsp[0].str)); }
#line 2732 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 174: /* StrictKeySymList: KeySym  */
#line 754 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= CreateKeysymList((yyvsp[0].str)); }
#line 2738 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 175: /* KeySymList: KeySymList COMMA KeySym  */
#line 759 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= AppendKeysymList((yyvsp[-2].expr),(yyvsp[0].str)); }
#line 2744 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 176: /* KeySymList: KeySymList COMMA KeySyms  */
#line 761 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= AppendKeysymList((yyvsp[-2].expr),(yyvsp[0].str)); }
#line 2750 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 177: /* KeySymList: KeySym  */
#line 763 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= CreateKeysymList((yyvsp[0].str)); }
#line 2756 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 178: /* KeySymList: KeySyms  */
#line 765 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        { (yyval.expr)= CreateKeysymList((yyvsp[0].str)); }
#line 2762 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 179: /* KeySym: IDENT  */
#line 768 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                        { (yyval.str)= strdup(scanBuf); }
#line 2768 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 180: /* KeySym: SECTION  */
#line 769 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                        { (yyval.str)= strdup("section"); }
#line 2774 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 181: /* KeySym: Integer  */
#line 771 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    if ((yyvsp[0].ival)<10)	{ (yyval.str)= malloc(2); (yyval.str)[0]= '0' + (yyvsp[0].ival); (yyval.str)[1]= '\0'; }
			    else	{ (yyval.str)= malloc(19); snprintf((yyval.str), 19, "0x%x", (yyvsp[0].ival)); }
			}
#line 2783 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 182: /* KeySyms: OBRACE StrictKeySymList CBRACE  */
#line 783 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                        {
			    yyerror("Multiple keysyms per level is not "
			            "supported; list replaced by NoSymbol");
			    free((yyvsp[-1].expr)->value.list.syms);
			    free((yyvsp[-1].expr));
			    (yyval.str)= strdup("NoSymbol");
			}
#line 2795 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 183: /* SignedNumber: MINUS Number  */
#line 792 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                        { (yyval.ival)= -(yyvsp[0].ival); }
#line 2801 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 184: /* SignedNumber: Number  */
#line 793 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                        { (yyval.ival)= (yyvsp[0].ival); }
#line 2807 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 185: /* Number: FLOAT  */
#line 796 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                        { (yyval.ival)= scanInt; }
#line 2813 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 186: /* Number: INTEGER  */
#line 797 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                        { (yyval.ival)= scanInt*XkbGeomPtsPerMM; }
#line 2819 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 187: /* Float: FLOAT  */
#line 800 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                        { (yyval.ival)= scanInt; }
#line 2825 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 188: /* Integer: INTEGER  */
#line 803 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                        { (yyval.ival)= scanInt; }
#line 2831 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 189: /* KeyName: KEYNAME  */
#line 806 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                        { (yyval.str)= strdup(scanBuf); }
#line 2837 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 190: /* Ident: IDENT  */
#line 809 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                { (yyval.sval)= XkbInternAtom(NULL,scanBuf,False); }
#line 2843 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 191: /* Ident: DEFAULT  */
#line 810 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                { (yyval.sval)= XkbInternAtom(NULL,"default",False); }
#line 2849 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 192: /* String: STRING  */
#line 813 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                { (yyval.sval)= XkbInternAtom(NULL,scanBuf,False); }
#line 2855 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 193: /* OptMapName: MapName  */
#line 816 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                { (yyval.str)= (yyvsp[0].str); }
#line 2861 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 194: /* OptMapName: %empty  */
#line 817 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                { (yyval.str)= NULL; }
#line 2867 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;

  case 195: /* MapName: STRING  */
#line 820 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"
                                { (yyval.str)= strdup(scanBuf); }
#line 2873 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"
    break;


#line 2877 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/generated/xkbparse.c"

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

      if (yychar <= END_OF_FILE)
        {
          /* Return failure if at end of input.  */
          if (yychar == END_OF_FILE)
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

#line 822 "/home/ubuntu/termux-pro-native/termux-pro-app-x11-stage/lorie/src/main/cpp/xkbcomp/xkbparse.y"

void
yyerror(const char *s)
{
    if (warningLevel>0) {
	(void)fprintf(stderr,"%s: line %d of %s\n",s,lineNum,
					(scanFile?scanFile:"(unknown)"));
	if ((warningLevel>3))
	    (void)fprintf(stderr,"last scanned symbol is: %s\n",scanBuf);
    }
    return;
}


int
yywrap(void)
{
   return 1;
}

