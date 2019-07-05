/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         AXSTYPE
#define YYLTYPE         AXLTYPE
/* Substitute the variable and function names.  */
#define yyparse         axparse
#define yylex           axlex
#define yyerror         axerror
#define yydebug         axdebug
#define yynerrs         axnerrs

#define yylval          axlval
#define yychar          axchar
#define yylloc          axlloc

/* Copy the first part of user declarations.  */


    #include <stdio.h>
    #include <iostream>

    #include <openvdb/Platform.h> // for OPENVDB_NO_TYPE_CONVERSION_WARNING_BEGIN
    #include <openvdb_ax/ast/AST.h>
    #include <openvdb_ax/ast/Tokens.h>

    /// @note  Bypasses bison conversion warnings in yyparse
    OPENVDB_NO_TYPE_CONVERSION_WARNING_BEGIN

    extern int axlex();

    using namespace openvdb::ax::ast;

    void yyerror(Tree** tree, const char* s);



# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "axparser.h".  */
#ifndef YY_AX_OPENVDB_AX_GRAMMAR_AXPARSER_H_INCLUDED
# define YY_AX_OPENVDB_AX_GRAMMAR_AXPARSER_H_INCLUDED
/* Debug traces.  */
#ifndef AXDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define AXDEBUG 1
#  else
#   define AXDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define AXDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined AXDEBUG */
#if AXDEBUG
extern int axdebug;
#endif

/* Token type.  */
#ifndef AXTOKENTYPE
# define AXTOKENTYPE
  enum axtokentype
  {
    TRUE = 258,
    FALSE = 259,
    SEMICOLON = 260,
    AT = 261,
    DOLLAR = 262,
    IF = 263,
    ELSE = 264,
    RETURN = 265,
    LCURLY = 266,
    RCURLY = 267,
    LSQUARE = 268,
    RSQUARE = 269,
    STRING = 270,
    DOUBLE = 271,
    FLOAT = 272,
    LONG = 273,
    INT = 274,
    SHORT = 275,
    BOOL = 276,
    VOID = 277,
    VEC2I = 278,
    VEC2F = 279,
    VEC2D = 280,
    VEC3I = 281,
    VEC3F = 282,
    VEC3D = 283,
    VEC4I = 284,
    VEC4F = 285,
    VEC4D = 286,
    F_AT = 287,
    I_AT = 288,
    V_AT = 289,
    S_AT = 290,
    MAT3F = 291,
    MAT3D = 292,
    MAT4F = 293,
    MAT4D = 294,
    M3F_AT = 295,
    M4F_AT = 296,
    F_DOLLAR = 297,
    I_DOLLAR = 298,
    V_DOLLAR = 299,
    S_DOLLAR = 300,
    DOT_X = 301,
    DOT_Y = 302,
    DOT_Z = 303,
    L_SHORT = 304,
    L_INT = 305,
    L_LONG = 306,
    L_FLOAT = 307,
    L_DOUBLE = 308,
    L_STRING = 309,
    IDENTIFIER = 310,
    COMMA = 311,
    EQUALS = 312,
    PLUSEQUALS = 313,
    MINUSEQUALS = 314,
    MULTIPLYEQUALS = 315,
    DIVIDEEQUALS = 316,
    MODULOEQUALS = 317,
    BITANDEQUALS = 318,
    BITXOREQUALS = 319,
    BITOREQUALS = 320,
    OR = 321,
    AND = 322,
    BITOR = 323,
    BITXOR = 324,
    BITAND = 325,
    EQUALSEQUALS = 326,
    NOTEQUALS = 327,
    MORETHAN = 328,
    LESSTHAN = 329,
    MORETHANOREQUAL = 330,
    LESSTHANOREQUAL = 331,
    PLUS = 332,
    MINUS = 333,
    MULTIPLY = 334,
    DIVIDE = 335,
    MODULO = 336,
    NOT = 337,
    BITNOT = 338,
    PLUSPLUS = 339,
    MINUSMINUS = 340,
    LPARENS = 341,
    RPARENS = 342,
    LOWER_THAN_ELSE = 343
  };
#endif

/* Value type.  */
#if ! defined AXSTYPE && ! defined AXSTYPE_IS_DECLARED

union AXSTYPE
{


    const char* string;
    uint64_t index;

    openvdb::ax::ast::Tree* tree;
    openvdb::ax::ast::ValueBase* value;
    openvdb::ax::ast::Block* block;
    openvdb::ax::ast::Statement* statement;
    openvdb::ax::ast::Expression* expression;
    openvdb::ax::ast::ExpressionList* expressionlist;
    openvdb::ax::ast::Variable* variable;
    openvdb::ax::ast::ExternalVariable* external;
    openvdb::ax::ast::Attribute* attribute;
    openvdb::ax::ast::DeclareLocal* declare_local;
    openvdb::ax::ast::Local* local;


};

typedef union AXSTYPE AXSTYPE;
# define AXSTYPE_IS_TRIVIAL 1
# define AXSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined AXLTYPE && ! defined AXLTYPE_IS_DECLARED
typedef struct AXLTYPE AXLTYPE;
struct AXLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define AXLTYPE_IS_DECLARED 1
# define AXLTYPE_IS_TRIVIAL 1
#endif


extern AXSTYPE axlval;
extern AXLTYPE axlloc;
int axparse (openvdb::ax::ast::Tree** tree);

#endif /* !YY_AX_OPENVDB_AX_GRAMMAR_AXPARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined AXLTYPE_IS_TRIVIAL && AXLTYPE_IS_TRIVIAL \
             && defined AXSTYPE_IS_TRIVIAL && AXSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  105
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   761

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  198

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   343

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88
};

#if AXDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   167,   167,   168,   172,   173,   174,   178,   179,   185,
     186,   187,   188,   189,   197,   198,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   218,   219,   220,   225,
     226,   233,   234,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   273,   274,
     275,   276,   280,   281,   285,   286,   291,   292,   293,   294,
     295,   296,   297,   302,   308,   309,   314,   315,   316,   317,
     318,   319,   320,   321,   326,   327,   328,   329,   330,   331,
     336,   343,   350,   351,   352,   353,   354,   355,   356,   357,
     361,   362,   363,   364,   369,   370,   371,   372,   377,   378,
     379,   380,   381,   382,   387,   388,   389,   390,   391,   392,
     393,   394,   395
};
#endif

#if AXDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TRUE", "FALSE", "SEMICOLON", "AT",
  "DOLLAR", "IF", "ELSE", "RETURN", "LCURLY", "RCURLY", "LSQUARE",
  "RSQUARE", "STRING", "DOUBLE", "FLOAT", "LONG", "INT", "SHORT", "BOOL",
  "VOID", "VEC2I", "VEC2F", "VEC2D", "VEC3I", "VEC3F", "VEC3D", "VEC4I",
  "VEC4F", "VEC4D", "F_AT", "I_AT", "V_AT", "S_AT", "MAT3F", "MAT3D",
  "MAT4F", "MAT4D", "M3F_AT", "M4F_AT", "F_DOLLAR", "I_DOLLAR", "V_DOLLAR",
  "S_DOLLAR", "DOT_X", "DOT_Y", "DOT_Z", "L_SHORT", "L_INT", "L_LONG",
  "L_FLOAT", "L_DOUBLE", "L_STRING", "IDENTIFIER", "COMMA", "EQUALS",
  "PLUSEQUALS", "MINUSEQUALS", "MULTIPLYEQUALS", "DIVIDEEQUALS",
  "MODULOEQUALS", "BITANDEQUALS", "BITXOREQUALS", "BITOREQUALS", "OR",
  "AND", "BITOR", "BITXOR", "BITAND", "EQUALSEQUALS", "NOTEQUALS",
  "MORETHAN", "LESSTHAN", "MORETHANOREQUAL", "LESSTHANOREQUAL", "PLUS",
  "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "NOT", "BITNOT", "PLUSPLUS",
  "MINUSMINUS", "LPARENS", "RPARENS", "LOWER_THAN_ELSE", "$accept",
  "statements", "block", "body", "statement", "conditional_statement",
  "expression", "function_call_expression", "arguments", "declaration",
  "assign_expression", "binary_expression", "unary_expression",
  "pre_crement", "post_crement", "variable_reference", "array", "variable",
  "attribute", "external", "declare_local", "local", "literal", "type",
  "matrix_type", "scalar_type", "vector_type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343
};
# endif

#define YYPACT_NINF -109

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-109)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     435,  -109,  -109,  -109,   -12,    -2,   -42,    50,   603,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,    30,    62,    72,    73,  -109,
    -109,  -109,  -109,    76,    77,    79,    80,    81,    83,  -109,
    -109,  -109,  -109,  -109,  -109,    53,   603,   603,   603,   603,
     676,   676,   603,    84,   435,  -109,  -109,    78,  -109,   137,
    -109,  -109,  -109,  -109,  -109,   111,  -109,   -11,  -109,  -109,
     103,  -109,  -109,    18,  -109,    75,  -109,  -109,  -109,   603,
    -109,   509,    -4,    -1,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,   182,   -32,   -32,  -109,  -109,  -109,
    -109,   156,  -109,  -109,   259,  -109,  -109,  -109,   603,   603,
     603,   603,   603,   603,   603,   603,   603,   603,   603,   603,
     603,   603,   603,   603,  -109,   603,   603,   603,   603,   603,
     603,   603,   603,   603,  -109,  -109,   603,  -109,  -109,  -109,
     603,   108,   109,  -109,   603,   343,  -109,   603,  -109,   -49,
    -109,   -58,   591,    19,   648,   661,   -47,   -47,    -3,    -3,
      -3,    -3,   -32,   -32,  -109,  -109,  -109,   509,   509,   509,
     509,   509,   509,   509,   509,   509,   -10,   509,  -109,  -109,
     427,   519,   509,  -109,  -109,   603,  -109,   267,   157,  -109,
     176,  -109,   351,    78,   519,  -109,  -109,  -109
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    98,    99,    13,     0,     0,     0,     0,     0,   103,
     113,   112,   111,   110,   109,   108,   114,   115,   116,   117,
     118,   119,   120,   121,   122,     0,     0,     0,     0,   104,
     105,   106,   107,     0,     0,     0,     0,     0,     0,    92,
      93,    94,    95,    96,    97,    91,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     8,    11,     0,    19,     0,
      18,    16,    17,    67,    22,    24,    23,    66,    74,    21,
      32,    75,    20,     0,   102,   100,   101,    83,    89,     0,
      12,    29,     0,     0,    78,    77,    79,    80,    81,    82,
      86,    85,    87,    88,     0,    58,    59,    61,    60,    91,
      62,     0,   100,    63,     0,     1,     7,     9,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,    65,     0,    68,    69,    70,
       0,     0,     0,    90,     0,     0,    73,     0,    27,     0,
      25,    51,    50,    48,    49,    47,    52,    53,    54,    55,
      56,    57,    42,    43,    44,    45,    46,    33,    34,    35,
      36,    37,    38,    39,    40,    41,     0,    31,    76,    84,
       0,     0,    30,    26,    71,     0,    28,     0,    14,     6,
       0,     5,     0,    29,     0,    72,     4,    15
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -109,  -109,  -108,   -22,   -51,  -109,    -7,  -109,    85,  -109,
    -109,  -109,  -109,  -109,  -109,    29,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,     0,  -109,    31,  -109
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    53,   188,    54,    55,    56,    57,    58,    82,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    83,    74,    75,    76
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      73,    81,   136,   106,   184,   141,   142,   147,   146,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   141,   142,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   137,   138,   139,   183,    95,
      96,    97,    98,    77,    79,   104,   185,   121,   122,   123,
     101,   101,   147,    78,    73,    80,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   145,   143,   119,   120,   121,   122,   123,   100,
     103,   102,   102,   107,   105,    84,   197,    81,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,    85,   167,   168,
     169,   170,   171,   172,   173,   174,   175,    86,    87,   176,
     189,    88,    89,   177,    90,    91,    92,   180,    93,    94,
     182,   106,   124,   189,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     140,   144,   141,   178,   179,   192,   194,     0,   125,   126,
     127,   128,   129,   130,   131,   132,   133,     0,   190,   149,
     193,    73,     0,     0,     0,     1,     2,    73,     4,     5,
     195,     0,    73,     8,    73,   134,   135,     9,    10,    11,
      12,    13,    14,    15,     0,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,     0,     0,
       0,    39,    40,    41,    42,    43,    44,    45,     0,     0,
       0,     0,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,     0,    46,
      47,     0,     0,     0,    48,    49,    50,    51,    52,   148,
       1,     2,     3,     4,     5,     6,     0,     7,     8,   191,
       0,     0,     9,    10,    11,    12,    13,    14,    15,     0,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,     0,     0,     0,    39,    40,    41,    42,
      43,    44,    45,     0,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,     0,     0,     0,    46,    47,   150,     0,     0,    48,
      49,    50,    51,    52,     1,     2,     3,     4,     5,     6,
       0,     7,     8,   196,     0,     0,     9,    10,    11,    12,
      13,    14,    15,     0,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,     0,     0,     0,
      39,    40,    41,    42,    43,    44,    45,     0,     0,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,     0,     0,     0,    46,    47,
     181,     0,     0,    48,    49,    50,    51,    52,     1,     2,
       3,     4,     5,     6,     0,     7,     8,     0,     0,     0,
       9,    10,    11,    12,    13,    14,    15,     0,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,     0,     0,     0,    39,    40,    41,    42,    43,    44,
      45,     0,     0,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,     0,
       0,     0,    46,    47,   186,     0,     0,    48,    49,    50,
      51,    52,     1,     2,     3,     4,     5,     6,     0,     7,
     187,     0,     0,     0,     9,    10,    11,    12,    13,    14,
      15,     0,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,     0,     0,     0,    39,    40,
      41,    42,    43,    44,    45,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,     0,     0,     0,     0,     0,    46,    47,     0,     0,
       0,    48,    49,    50,    51,    52,     1,     2,     0,     4,
       5,     0,     0,     0,     8,     0,     0,     0,     9,    10,
      11,    12,    13,    14,    15,     0,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,     0,
       0,     0,    39,    40,    41,    42,    43,    44,    45,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,     0,     0,     0,     0,     0,     0,     0,
      46,    47,     4,     0,     0,    48,    49,    50,    51,    52,
       0,     9,    10,    11,    12,    13,    14,    15,     0,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
       0,    99,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    51
};

static const yytype_int16 yycheck[] =
{
       0,     8,    13,    54,    14,     6,     7,    56,    12,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,     6,     7,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    46,    47,    48,    87,    46,
      47,    48,    49,    55,    86,    52,    56,    79,    80,    81,
      50,    51,    56,    55,    54,     5,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    79,    55,    77,    78,    79,    80,    81,    50,
      51,    50,    51,     5,     0,    55,   194,    94,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,    55,   125,   126,
     127,   128,   129,   130,   131,   132,   133,    55,    55,   136,
     181,    55,    55,   140,    55,    55,    55,   144,    55,    86,
     147,   192,     5,   194,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      57,    86,     6,    55,    55,   187,     9,    -1,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    -1,   185,    94,
     187,   181,    -1,    -1,    -1,     3,     4,   187,     6,     7,
      14,    -1,   192,    11,   194,    84,    85,    15,    16,    17,
      18,    19,    20,    21,    -1,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    -1,    77,
      78,    -1,    -1,    -1,    82,    83,    84,    85,    86,    87,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      -1,    -1,    15,    16,    17,    18,    19,    20,    21,    -1,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    -1,    -1,    -1,    77,    78,    87,    -1,    -1,    82,
      83,    84,    85,    86,     3,     4,     5,     6,     7,     8,
      -1,    10,    11,    12,    -1,    -1,    15,    16,    17,    18,
      19,    20,    21,    -1,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    -1,    -1,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    -1,    -1,    -1,    77,    78,
      87,    -1,    -1,    82,    83,    84,    85,    86,     3,     4,
       5,     6,     7,     8,    -1,    10,    11,    -1,    -1,    -1,
      15,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      -1,    -1,    77,    78,    87,    -1,    -1,    82,    83,    84,
      85,    86,     3,     4,     5,     6,     7,     8,    -1,    10,
      11,    -1,    -1,    -1,    15,    16,    17,    18,    19,    20,
      21,    -1,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    -1,    -1,    -1,    -1,    -1,    77,    78,    -1,    -1,
      -1,    82,    83,    84,    85,    86,     3,     4,    -1,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,
      17,    18,    19,    20,    21,    -1,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    78,     6,    -1,    -1,    82,    83,    84,    85,    86,
      -1,    15,    16,    17,    18,    19,    20,    21,    -1,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    55,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    10,    11,    15,
      16,    17,    18,    19,    20,    21,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    49,
      50,    51,    52,    53,    54,    55,    77,    78,    82,    83,
      84,    85,    86,    90,    92,    93,    94,    95,    96,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,    55,    55,    86,
       5,    95,    97,   112,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    86,    95,    95,    95,    95,    55,
     104,   112,   114,   104,    95,     0,    93,     5,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,     5,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    84,    85,    13,    46,    47,    48,
      57,     6,     7,    55,    86,    95,    12,    56,    87,    97,
      87,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    55,    55,
      95,    87,    95,    87,    14,    56,    87,    11,    91,    93,
      95,    12,    92,    95,     9,    14,    12,    91
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    89,    90,    90,    91,    91,    91,    92,    92,    93,
      93,    93,    93,    93,    94,    94,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    96,    96,    96,    97,
      97,    98,    98,    99,    99,    99,    99,    99,    99,    99,
      99,    99,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   101,   101,
     101,   101,   102,   102,   103,   103,   104,   104,   104,   104,
     104,   104,   104,   105,   106,   106,   107,   107,   107,   107,
     107,   107,   107,   107,   108,   108,   108,   108,   108,   108,
     109,   110,   111,   111,   111,   111,   111,   111,   111,   111,
     112,   112,   112,   112,   113,   113,   113,   113,   114,   114,
     114,   114,   114,   114,   115,   115,   115,   115,   115,   115,
     115,   115,   115
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     3,     2,     1,     2,     1,     2,
       2,     1,     2,     1,     5,     7,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     4,     3,     4,     1,
       3,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     1,     2,     2,
       2,     4,     6,     3,     1,     1,     3,     2,     2,     2,
       2,     2,     2,     2,     3,     2,     2,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (tree, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if AXDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined AXLTYPE_IS_TRIVIAL && AXLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, tree); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, openvdb::ax::ast::Tree** tree)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (tree);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, openvdb::ax::ast::Tree** tree)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, tree);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, openvdb::ax::ast::Tree** tree)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , tree);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, tree); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !AXDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !AXDEBUG */


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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, openvdb::ax::ast::Tree** tree)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (tree);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined AXLTYPE_IS_TRIVIAL && AXLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (openvdb::ax::ast::Tree** tree)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

    { *tree = new Tree(); (yyval.tree) = *tree; }

    break;

  case 3:

    { *tree = new Tree((yyvsp[0].block)); (yyval.tree) = *tree; }

    break;

  case 4:

    { (yyval.block) = (yyvsp[-1].block); }

    break;

  case 5:

    { (yyval.block) = new Block(); }

    break;

  case 6:

    { (yyval.block) = new Block(); (yyval.block)->addStatement((yyvsp[0].statement)); }

    break;

  case 7:

    { (yyvsp[-1].block)->addStatement((yyvsp[0].statement)); (yyval.block) = (yyvsp[-1].block); }

    break;

  case 8:

    { (yyval.block) = new Block(); (yyval.block)->addStatement((yyvsp[0].statement)); }

    break;

  case 9:

    { (yyval.statement) = (yyvsp[-1].expression); }

    break;

  case 10:

    { (yyval.statement) = (yyvsp[-1].statement); }

    break;

  case 11:

    { (yyval.statement) = (yyvsp[0].statement); }

    break;

  case 12:

    { (yyval.statement) = new Return; }

    break;

  case 13:

    { (yyval.statement) = nullptr; }

    break;

  case 14:

    { (yyval.statement) = new ConditionalStatement((yyvsp[-2].expression), ((yyvsp[0].block) ? (yyvsp[0].block) : new Block())); }

    break;

  case 15:

    { (yyval.statement) = new ConditionalStatement((yyvsp[-4].expression), ((yyvsp[-2].block) ? (yyvsp[-2].block) : new Block()), ((yyvsp[0].block) ? (yyvsp[0].block) : new Block())); }

    break;

  case 16:

    { (yyval.expression) = (yyvsp[0].expression); }

    break;

  case 17:

    { (yyval.expression) = (yyvsp[0].expression); }

    break;

  case 18:

    { (yyval.expression) = (yyvsp[0].expression); }

    break;

  case 19:

    { (yyval.expression) = (yyvsp[0].expression); }

    break;

  case 20:

    { (yyval.expression) = (yyvsp[0].value); }

    break;

  case 21:

    { (yyval.expression) = (yyvsp[0].external); }

    break;

  case 22:

    { (yyval.expression) = (yyvsp[0].expression); }

    break;

  case 23:

    { (yyval.expression) = (yyvsp[0].expression); }

    break;

  case 24:

    { (yyval.expression) = (yyvsp[0].expression); }

    break;

  case 25:

    { (yyval.expression) = (yyvsp[-1].expression); }

    break;

  case 26:

    { (yyval.expression) = new FunctionCall((yyvsp[-3].string), (yyvsp[-1].expressionlist)); free(const_cast<char*>((yyvsp[-3].string))); }

    break;

  case 27:

    { (yyval.expression) = new FunctionCall((yyvsp[-2].string)); free(const_cast<char*>((yyvsp[-2].string))); }

    break;

  case 28:

    { (yyval.expression) = new Cast((yyvsp[-1].expression), static_cast<tokens::CoreType>((yyvsp[-3].index))); }

    break;

  case 29:

    { (yyval.expressionlist) = new ExpressionList(); (yyval.expressionlist)->addExpression((yyvsp[0].expression)); }

    break;

  case 30:

    { (yyvsp[-2].expressionlist)->addExpression((yyvsp[0].expression)); (yyval.expressionlist) = (yyvsp[-2].expressionlist); }

    break;

  case 31:

    { (yyval.statement) = new AssignExpression((yyvsp[-2].declare_local), (yyvsp[0].expression), false); }

    break;

  case 32:

    { (yyval.statement) = (yyvsp[0].declare_local); }

    break;

  case 33:

    { (yyval.expression) = new AssignExpression((yyvsp[-2].expression), (yyvsp[0].expression), false); }

    break;

  case 34:

    { (yyval.expression) = new AssignExpression((yyvsp[-2].expression), new BinaryOperator(tokens::PLUS, (yyvsp[-2].expression)->copy(), (yyvsp[0].expression)), true); }

    break;

  case 35:

    { (yyval.expression) = new AssignExpression((yyvsp[-2].expression), new BinaryOperator(tokens::MINUS, (yyvsp[-2].expression)->copy(), (yyvsp[0].expression)), true); }

    break;

  case 36:

    { (yyval.expression) = new AssignExpression((yyvsp[-2].expression), new BinaryOperator(tokens::MULTIPLY, (yyvsp[-2].expression)->copy(), (yyvsp[0].expression)), true); }

    break;

  case 37:

    { (yyval.expression) = new AssignExpression((yyvsp[-2].expression), new BinaryOperator(tokens::DIVIDE, (yyvsp[-2].expression)->copy(), (yyvsp[0].expression)), true); }

    break;

  case 38:

    { (yyval.expression) = new AssignExpression((yyvsp[-2].expression), new BinaryOperator(tokens::MODULO, (yyvsp[-2].expression)->copy(), (yyvsp[0].expression)), true); }

    break;

  case 39:

    { (yyval.expression) = new AssignExpression((yyvsp[-2].expression), new BinaryOperator(tokens::BITAND, (yyvsp[-2].expression)->copy(), (yyvsp[0].expression)), true); }

    break;

  case 40:

    { (yyval.expression) = new AssignExpression((yyvsp[-2].expression), new BinaryOperator(tokens::BITXOR, (yyvsp[-2].expression)->copy(), (yyvsp[0].expression)), true); }

    break;

  case 41:

    { (yyval.expression) = new AssignExpression((yyvsp[-2].expression), new BinaryOperator(tokens::BITOR, (yyvsp[-2].expression)->copy(), (yyvsp[0].expression)), true); }

    break;

  case 42:

    { (yyval.expression) = new BinaryOperator(tokens::PLUS, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 43:

    { (yyval.expression) = new BinaryOperator(tokens::MINUS, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 44:

    { (yyval.expression) = new BinaryOperator(tokens::MULTIPLY, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 45:

    { (yyval.expression) = new BinaryOperator(tokens::DIVIDE, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 46:

    { (yyval.expression) = new BinaryOperator(tokens::MODULO, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 47:

    { (yyval.expression) = new BinaryOperator(tokens::BITAND, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 48:

    { (yyval.expression) = new BinaryOperator(tokens::BITOR, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 49:

    { (yyval.expression) = new BinaryOperator(tokens::BITXOR, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 50:

    { (yyval.expression) = new BinaryOperator(tokens::AND, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 51:

    { (yyval.expression) = new BinaryOperator(tokens::OR, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 52:

    { (yyval.expression) = new BinaryOperator(tokens::EQUALSEQUALS, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 53:

    { (yyval.expression) = new BinaryOperator(tokens::NOTEQUALS, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 54:

    { (yyval.expression) = new BinaryOperator(tokens::MORETHAN, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 55:

    { (yyval.expression) = new BinaryOperator(tokens::LESSTHAN, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 56:

    { (yyval.expression) = new BinaryOperator(tokens::MORETHANOREQUAL, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 57:

    { (yyval.expression) = new BinaryOperator(tokens::LESSTHANOREQUAL, (yyvsp[-2].expression), (yyvsp[0].expression)); }

    break;

  case 58:

    { (yyval.expression) = new UnaryOperator(tokens::PLUS, (yyvsp[0].expression)); }

    break;

  case 59:

    { (yyval.expression) = new UnaryOperator(tokens::MINUS, (yyvsp[0].expression)); }

    break;

  case 60:

    { (yyval.expression) = new UnaryOperator(tokens::BITNOT, (yyvsp[0].expression)); }

    break;

  case 61:

    { (yyval.expression) = new UnaryOperator(tokens::NOT, (yyvsp[0].expression)); }

    break;

  case 62:

    { (yyval.expression) = new Crement((yyvsp[0].expression), Crement::Increment, /*post*/false); }

    break;

  case 63:

    { (yyval.expression) = new Crement((yyvsp[0].expression), Crement::Decrement, /*post*/false); }

    break;

  case 64:

    { (yyval.expression) = new Crement((yyvsp[-1].expression), Crement::Increment, /*post*/true); }

    break;

  case 65:

    { (yyval.expression) = new Crement((yyvsp[-1].expression), Crement::Decrement, /*post*/true); }

    break;

  case 66:

    { (yyval.expression) = (yyvsp[0].variable); }

    break;

  case 67:

    { (yyval.expression) = (yyvsp[0].expression);}

    break;

  case 68:

    { (yyval.expression) = new ArrayUnpack((yyvsp[-1].variable), new Value<int32_t>(0)); }

    break;

  case 69:

    { (yyval.expression) = new ArrayUnpack((yyvsp[-1].variable), new Value<int32_t>(1)); }

    break;

  case 70:

    { (yyval.expression) = new ArrayUnpack((yyvsp[-1].variable), new Value<int32_t>(2)); }

    break;

  case 71:

    { (yyval.expression) = new ArrayUnpack((yyvsp[-3].variable), (yyvsp[-1].expression)); }

    break;

  case 72:

    { (yyval.expression) = new ArrayUnpack((yyvsp[-5].variable), (yyvsp[-3].expression), (yyvsp[-1].expression)); }

    break;

  case 73:

    { (yyval.expression) = new ArrayPack((yyvsp[-1].expressionlist)); }

    break;

  case 74:

    { (yyval.variable) = (yyvsp[0].attribute); }

    break;

  case 75:

    { (yyval.variable) = (yyvsp[0].local); }

    break;

  case 76:

    { (yyval.attribute) = new Attribute((yyvsp[0].string), static_cast<tokens::CoreType>((yyvsp[-2].index))); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 77:

    { (yyval.attribute) = new Attribute((yyvsp[0].string), tokens::INT); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 78:

    { (yyval.attribute) = new Attribute((yyvsp[0].string), tokens::FLOAT); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 79:

    { (yyval.attribute) = new Attribute((yyvsp[0].string), tokens::VEC3F); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 80:

    { (yyval.attribute) = new Attribute((yyvsp[0].string), tokens::STRING); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 81:

    { (yyval.attribute) = new Attribute((yyvsp[0].string), tokens::MAT3F); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 82:

    { (yyval.attribute) = new Attribute((yyvsp[0].string), tokens::MAT4F); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 83:

    { (yyval.attribute) = new Attribute((yyvsp[0].string), tokens::FLOAT, true); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 84:

    { (yyval.external) = new ExternalVariable((yyvsp[0].string), static_cast<tokens::CoreType>((yyvsp[-2].index))); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 85:

    { (yyval.external) = new ExternalVariable((yyvsp[0].string), tokens::INT); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 86:

    { (yyval.external) = new ExternalVariable((yyvsp[0].string), tokens::FLOAT); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 87:

    { (yyval.external) = new ExternalVariable((yyvsp[0].string), tokens::VEC3F); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 88:

    { (yyval.external) = new ExternalVariable((yyvsp[0].string), tokens::STRING); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 89:

    { (yyval.external) = new ExternalVariable((yyvsp[0].string), tokens::FLOAT); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 90:

    { (yyval.declare_local) = new DeclareLocal((yyvsp[0].string), static_cast<tokens::CoreType>((yyvsp[-1].index))); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 91:

    { (yyval.local) = new Local((yyvsp[0].string)); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 92:

    { (yyval.value) = new Value<int16_t>((yyvsp[0].string)); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 93:

    { (yyval.value) = new Value<int32_t>((yyvsp[0].string)); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 94:

    { (yyval.value) = new Value<int64_t>((yyvsp[0].string)); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 95:

    { (yyval.value) = new Value<float>((yyvsp[0].string)); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 96:

    { (yyval.value) = new Value<double>((yyvsp[0].string)); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 97:

    { (yyval.value) = new Value<std::string>((yyvsp[0].string)); free(const_cast<char*>((yyvsp[0].string))); }

    break;

  case 98:

    { (yyval.value) = new Value<bool>(true); }

    break;

  case 99:

    { (yyval.value) = new Value<bool>(false); }

    break;

  case 100:

    { (yyval.index) = (yyvsp[0].index); }

    break;

  case 101:

    { (yyval.index) = (yyvsp[0].index); }

    break;

  case 102:

    { (yyval.index) = (yyvsp[0].index); }

    break;

  case 103:

    { (yyval.index) = tokens::STRING; }

    break;

  case 104:

    { (yyval.index) = tokens::MAT3F; }

    break;

  case 105:

    { (yyval.index) = tokens::MAT3D; }

    break;

  case 106:

    { (yyval.index) = tokens::MAT4F; }

    break;

  case 107:

    { (yyval.index) = tokens::MAT4D; }

    break;

  case 108:

    { (yyval.index) = tokens::BOOL; }

    break;

  case 109:

    { (yyval.index) = tokens::SHORT; }

    break;

  case 110:

    { (yyval.index) = tokens::INT; }

    break;

  case 111:

    { (yyval.index) = tokens::LONG; }

    break;

  case 112:

    { (yyval.index) = tokens::FLOAT; }

    break;

  case 113:

    { (yyval.index) = tokens::DOUBLE; }

    break;

  case 114:

    { (yyval.index) = tokens::VEC2I; }

    break;

  case 115:

    { (yyval.index) = tokens::VEC2F; }

    break;

  case 116:

    { (yyval.index) = tokens::VEC2D; }

    break;

  case 117:

    { (yyval.index) = tokens::VEC3I; }

    break;

  case 118:

    { (yyval.index) = tokens::VEC3F; }

    break;

  case 119:

    { (yyval.index) = tokens::VEC3D; }

    break;

  case 120:

    { (yyval.index) = tokens::VEC4I; }

    break;

  case 121:

    { (yyval.index) = tokens::VEC4F; }

    break;

  case 122:

    { (yyval.index) = tokens::VEC4D; }

    break;



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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (tree, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (tree, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc, tree);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, tree);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (tree, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, tree);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, tree);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}



OPENVDB_NO_TYPE_CONVERSION_WARNING_END

// Copyright (c) 2015-2019 DNEG
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
