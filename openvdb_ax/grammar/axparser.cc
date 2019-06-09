/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.4.1"

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

/* First part of user prologue.  */
#line 31 "grammar/axparser.y"

    #include <stdio.h>
    #include <iostream>

    #include <openvdb_ax/ast/AST.h>
    #include <openvdb_ax/ast/Tokens.h>

    extern int axlex();

    using namespace openvdb::ax::ast;

    void yyerror(Tree** tree, const char* s);

    // @note  Component expressions are currently fully unpacked, processed, packed, and then
    //        vector assigned. This should not be the case for locals.
    // @todo  Fix this by allowing direct assignment to local array elements and better
    //        handling of attribute elements
    Expression*
    buildComponentExpression(const std::unique_ptr<tokens::OperatorToken> op,
                             Variable::UniquePtr lhs,         // The attribute/local vector value being assigned (Attribute/Local)
                             Expression::UniquePtr lhsValue,  // The attribute/local vector value being assigned (AttibuteValue/LocalValue)
                             const int16_t index,
                             Expression::UniquePtr rhs)       // The RHS expression
    {
        assert(index >= 0 && index <= 2);

        if (op) {
            rhs.reset(new BinaryOperator(*op, new VectorUnpack(lhsValue->copy(), index), rhs.release()));
        }

        Expression::UniquePtr elements[3];
        if (index == 0) elements[0].reset(rhs.release());
        else            elements[0].reset(new VectorUnpack(lhsValue->copy(), 0));
        if (index == 1) elements[1].reset(rhs.release());
        else            elements[1].reset(new VectorUnpack(lhsValue->copy(), 1));
        if (index == 2) elements[2].reset(rhs.release());
        else            elements[2].reset(new VectorUnpack(lhsValue->copy(), 2));

        VectorPack::UniquePtr packed(new VectorPack(elements[0].release(), elements[1].release(), elements[2].release()));
        return new AssignExpression(lhs.release(), packed.release());
    }

    Expression*
    buildAttributeComponentExpression(tokens::OperatorToken* op,
                                      Attribute* attribute,
                                      const int16_t index,
                                      Expression* expression)
    {
        return buildComponentExpression(std::unique_ptr<tokens::OperatorToken>(op),
            Variable::UniquePtr(attribute),
            Expression::UniquePtr(new AttributeValue(attribute->copy())),
            index,
            Expression::UniquePtr(expression));
    }

    Expression* buildLocalComponentExpression(tokens::OperatorToken* op,
                                              Local* local,
                                              const int16_t index,
                                              Expression* expression)
    {
        return buildComponentExpression(std::unique_ptr<tokens::OperatorToken>(op),
            Variable::UniquePtr(local),
            Expression::UniquePtr(new LocalValue(local->copy())),
            index,
            Expression::UniquePtr(expression));
    }

    Attribute* buildAttribute(const std::string& name)
    {
        // remap position, velocity, normal and color to vec3s
        if (name == "P" || name == "v" || name == "N" || name == "Cd") {
            return new Attribute(name, openvdb::typeNameAsString<openvdb::Vec3s>());
        }
        else {
            return new Attribute(name, openvdb::typeNameAsString<float>());
        }
    }

#line 160 "grammar/axparser.cc"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_AX_GRAMMAR_AXPARSER_H_INCLUDED
# define YY_AX_GRAMMAR_AXPARSER_H_INCLUDED
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
    RESERVED = 258,
    TRUE = 259,
    FALSE = 260,
    SEMICOLON = 261,
    AT = 262,
    DOLLAR = 263,
    IF = 264,
    ELSE = 265,
    RETURN = 266,
    EQUALS = 267,
    PLUSEQUALS = 268,
    MINUSEQUALS = 269,
    MULTIPLYEQUALS = 270,
    DIVIDEEQUALS = 271,
    PLUSPLUS = 272,
    MINUSMINUS = 273,
    LPARENS = 274,
    RPARENS = 275,
    LCURLY = 276,
    RCURLY = 277,
    PLUS = 278,
    MINUS = 279,
    MULTIPLY = 280,
    DIVIDE = 281,
    MODULO = 282,
    BITAND = 283,
    BITOR = 284,
    BITXOR = 285,
    BITNOT = 286,
    EQUALSEQUALS = 287,
    NOTEQUALS = 288,
    MORETHAN = 289,
    LESSTHAN = 290,
    MORETHANOREQUAL = 291,
    LESSTHANOREQUAL = 292,
    AND = 293,
    OR = 294,
    NOT = 295,
    STRING = 296,
    DOUBLE = 297,
    FLOAT = 298,
    LONG = 299,
    INT = 300,
    SHORT = 301,
    BOOL = 302,
    VOID = 303,
    F_AT = 304,
    I_AT = 305,
    V_AT = 306,
    S_AT = 307,
    F_DOLLAR = 308,
    I_DOLLAR = 309,
    V_DOLLAR = 310,
    S_DOLLAR = 311,
    COMMA = 312,
    VEC3I = 313,
    VEC3F = 314,
    VEC3D = 315,
    DOT_X = 316,
    DOT_Y = 317,
    DOT_Z = 318,
    L_SHORT = 319,
    L_INT = 320,
    L_LONG = 321,
    L_FLOAT = 322,
    L_DOUBLE = 323,
    L_STRING = 324,
    IDENTIFIER = 325,
    LPAREN = 326,
    RPAREN = 327,
    LOWER_THAN_ELSE = 328
  };
#endif

/* Value type.  */
#if ! defined AXSTYPE && ! defined AXSTYPE_IS_DECLARED
union AXSTYPE
{
#line 114 "grammar/axparser.y"

    const char* string;
    uint64_t index;

    openvdb::ax::ast::Tree* tree;
    openvdb::ax::ast::ValueBase* value;
    openvdb::ax::ast::VectorUnpack* vector_unpack;
    openvdb::ax::ast::Block* block;
    openvdb::ax::ast::Statement* statement;
    openvdb::ax::ast::Expression* expression;
    openvdb::ax::ast::ExpressionList* expressionlist;
    openvdb::ax::ast::Variable* variable;
    openvdb::ax::ast::ExternalVariable* external;
    openvdb::ax::ast::Attribute* attribute;
    openvdb::ax::ast::AttributeValue* attributevalue;
    openvdb::ax::ast::DeclareLocal* declare_local;
    openvdb::ax::ast::Local* local;

#line 304 "grammar/axparser.cc"

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

#endif /* !YY_AX_GRAMMAR_AXPARSER_H_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#define YYFINAL  97
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   729

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  219

#define YYUNDEFTOK  2
#define YYMAXUTOK   328

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
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
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if AXDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   207,   207,   208,   212,   213,   214,   218,   219,   225,
     226,   227,   228,   229,   237,   238,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     264,   265,   266,   271,   278,   283,   284,   289,   290,   297,
     298,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   345,   346,   347,   348,   349,   350,   351,   352,   357,
     358,   359,   360,   366,   367,   368,   369,   370,   371,   372,
     373,   374,   375,   376,   377,   378,   379,   380,   381,   386,
     391,   392,   393,   394,   395,   396,   397,   398,   403,   404,
     405,   406,   407,   408,   409,   410,   415,   416,   417,   424,
     431,   432,   433,   434,   435,   436,   437,   438,   443,   444,
     445,   451,   452,   453,   454,   455,   456,   462,   463,   464
};
#endif

#if AXDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "RESERVED", "TRUE", "FALSE", "SEMICOLON",
  "AT", "DOLLAR", "IF", "ELSE", "RETURN", "EQUALS", "PLUSEQUALS",
  "MINUSEQUALS", "MULTIPLYEQUALS", "DIVIDEEQUALS", "PLUSPLUS",
  "MINUSMINUS", "LPARENS", "RPARENS", "LCURLY", "RCURLY", "PLUS", "MINUS",
  "MULTIPLY", "DIVIDE", "MODULO", "BITAND", "BITOR", "BITXOR", "BITNOT",
  "EQUALSEQUALS", "NOTEQUALS", "MORETHAN", "LESSTHAN", "MORETHANOREQUAL",
  "LESSTHANOREQUAL", "AND", "OR", "NOT", "STRING", "DOUBLE", "FLOAT",
  "LONG", "INT", "SHORT", "BOOL", "VOID", "F_AT", "I_AT", "V_AT", "S_AT",
  "F_DOLLAR", "I_DOLLAR", "V_DOLLAR", "S_DOLLAR", "COMMA", "VEC3I",
  "VEC3F", "VEC3D", "DOT_X", "DOT_Y", "DOT_Z", "L_SHORT", "L_INT",
  "L_LONG", "L_FLOAT", "L_DOUBLE", "L_STRING", "IDENTIFIER", "LPAREN",
  "RPAREN", "LOWER_THAN_ELSE", "$accept", "statements", "block", "body",
  "statement", "conditional_statement", "expression", "vector_element",
  "expression_expand", "cast_expression", "function_call_expression",
  "arguments", "declare_assignment", "assign_expression",
  "assign_component_expression", "crement", "unary_expression",
  "binary_expression", "vector_literal", "attribute", "external",
  "declare_local", "local", "literal", "component", "scalar_type",
  "vector_type", YY_NULLPTR
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
     325,   326,   327,   328
};
# endif

#define YYPACT_NINF -62

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-62)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     313,   -62,   -62,   -62,   -61,   -53,     3,    23,   544,   544,
     514,   514,   514,   514,   514,   514,    13,   -62,   -62,   -62,
     -62,   -62,   -62,   -44,   -22,   -19,     5,    11,    15,    36,
      44,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
      99,   134,   313,   -62,   -62,   635,   -62,   -62,   -62,   -62,
     130,   -62,   -62,   -62,   -62,   -62,   -62,    54,     0,   138,
     113,   -62,     4,    17,   -62,   -62,   380,   -62,   144,   -62,
     -62,   -62,   146,   147,   -62,   -62,    81,   655,    20,   105,
     583,    52,    52,   -62,   619,    86,    87,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   447,   -62,   -62,   -62,
     514,   514,   514,   514,   514,   514,   514,   514,   514,   514,
     514,   514,   514,   514,   514,   514,   -62,   514,   514,   514,
     514,   514,   -62,   -62,   -62,   -62,   -62,   128,   -62,   514,
     514,   514,   514,   514,   514,   -62,   -62,   133,    88,    89,
     -62,   -62,    90,    92,   -62,   179,   154,   -62,   -62,   514,
     -62,   -62,   -62,   690,    -7,    52,    52,   145,   145,   -62,
     188,   188,   188,   619,   619,    30,    30,    30,    30,   619,
     619,   690,   690,   690,   690,   690,   514,   514,   514,   514,
     514,   690,   690,   690,   690,   690,   690,   514,   514,   514,
     514,   514,   -62,   -62,   -62,   -62,   -62,   246,     8,   380,
     600,   -62,   514,   690,   690,   690,   690,   690,   690,   690,
     690,   690,   690,   -62,   -62,   514,   690,   673,   -62
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,   116,   117,    13,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   126,   125,   124,
     123,   122,   121,     0,     0,     0,     0,     0,     0,     0,
       0,   127,   128,   129,   110,   111,   112,   113,   114,   115,
     109,     0,     3,     8,    11,     0,    25,    16,    23,    17,
       0,    20,    21,    22,    19,    18,    24,    29,    27,    40,
      28,    26,     0,     0,    97,   105,     0,    12,     0,   109,
      61,    65,     0,     0,    62,    66,     0,     0,     0,     0,
       0,    69,    70,    71,    72,     0,     0,   108,    93,    92,
      94,    95,   101,   100,   102,   103,     0,     1,     7,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    10,     0,     0,     0,
       0,     0,    63,    64,   118,   119,   120,    30,    32,     0,
       0,     0,     0,     0,     0,    67,    68,    31,     0,     0,
     106,    34,     0,     0,   107,     0,    14,     6,    33,     0,
      96,   104,    36,    37,     0,    73,    74,    75,    76,    77,
      78,    79,    80,    83,    84,    85,    86,    87,    88,    81,
      82,    41,    42,    43,    44,    45,     0,     0,     0,     0,
       0,    39,    46,    47,    48,    49,    50,     0,     0,     0,
       0,     0,    90,    98,    91,    99,     5,     0,     0,     0,
       0,    35,     0,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     4,    15,     0,    38,     0,    89
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -62,   -62,   -34,    26,   -36,   -62,   -10,   -62,     2,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   124,
     -62,   -62,   129,   -62,    24,     7,    10
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    41,   146,    42,    43,    44,    45,    46,    47,    48,
      49,   154,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,   127,    78,    79
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      77,    80,    81,    82,    83,    84,    98,    62,    66,    64,
      63,   138,   139,   201,    99,    72,    72,    65,    73,    73,
      85,    86,    10,    10,   142,   143,    88,   138,   139,    67,
     147,   100,   101,   102,   103,   104,   105,   106,   107,    10,
     108,   109,   110,   111,   112,   113,   114,   115,    89,    62,
     202,    90,    63,   100,   101,   102,   103,   104,   105,   106,
     107,   124,   125,   126,   141,   149,   117,   118,   119,   120,
     121,   122,   123,    62,   140,    91,    63,   102,   103,   104,
     141,    92,   128,    87,   137,    93,   153,   144,    85,    86,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,    94,   171,   172,   173,
     174,   175,   142,   143,    95,   124,   125,   126,    96,   181,
     182,   183,   184,   185,   186,   130,   131,   132,   133,   134,
     135,   136,    70,    74,    97,   198,   116,    71,    75,   200,
     176,   177,   178,   179,   180,   187,   188,   189,   190,   191,
     129,    85,    62,   138,   142,    63,   150,   151,   192,   193,
     194,    98,   195,   147,   199,   214,   203,   204,   205,   206,
     207,   197,   104,     0,   124,   125,   126,   208,   209,   210,
     211,   212,     0,     1,     2,     3,     4,     5,     6,     0,
       7,     0,   216,     0,     0,     0,     8,     9,    10,     0,
      11,   196,    12,    13,    62,   217,    62,    63,     0,    63,
      14,   100,   101,   102,   103,   104,     0,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    22,     0,    23,    24,
      25,    26,    27,    28,    29,    30,     0,    31,    32,    33,
       0,     0,     0,    34,    35,    36,    37,    38,    39,    40,
       1,     2,     3,     4,     5,     6,     0,     7,     0,     0,
       0,     0,     0,     8,     9,    10,     0,    11,   213,    12,
      13,     0,     0,     0,     0,     0,     0,    14,     0,     0,
       0,     0,     0,     0,     0,     0,    15,    16,    17,    18,
      19,    20,    21,    22,     0,    23,    24,    25,    26,    27,
      28,    29,    30,     0,    31,    32,    33,     0,     0,     0,
      34,    35,    36,    37,    38,    39,    40,     1,     2,     3,
       4,     5,     6,     0,     7,     0,     0,     0,     0,     0,
       8,     9,    10,     0,    11,     0,    12,    13,     0,     0,
       0,     0,     0,     0,    14,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,     0,    23,    24,    25,    26,    27,    28,    29,    30,
       0,    31,    32,    33,     0,     0,     0,    34,    35,    36,
      37,    38,    39,    40,     1,     2,     3,     4,     5,     6,
       0,     7,     0,     0,     0,     0,     0,     8,     9,    10,
       0,   145,     0,    12,    13,     0,     0,     0,     0,     0,
       0,    14,     0,     0,     0,     0,     0,     0,     0,     0,
      15,    16,    17,    18,    19,    20,    21,    22,     0,    23,
      24,    25,    26,    27,    28,    29,    30,     0,    31,    32,
      33,     0,     0,     0,    34,    35,    36,    37,    38,    39,
      40,     1,     2,     0,     4,     5,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     9,    10,   152,    11,     0,
      12,    13,     0,     0,     0,     0,     0,     0,    14,     0,
       0,     0,     0,     0,     0,     0,     0,    15,    76,    17,
      18,    19,    20,    21,    22,     0,    23,    24,    25,    26,
      27,    28,    29,    30,     0,    31,    32,    33,     0,     0,
       0,    34,    35,    36,    37,    38,    39,    40,     1,     2,
       0,     4,     5,     0,     0,     0,     0,     0,     0,     0,
       0,     8,     9,    10,     0,    11,     0,    12,    13,     0,
       0,     0,     0,     0,     0,    14,     0,     0,     0,     0,
       0,     4,     0,     0,    15,    76,    17,    18,    19,    20,
      21,    22,     0,    23,    24,    25,    26,    27,    28,    29,
      30,     0,    31,    32,    33,     0,     0,     0,    34,    35,
      36,    37,    38,    39,    40,    68,    17,    18,    19,    20,
      21,    22,     0,    23,    24,    25,    26,     0,     0,     0,
       0,     0,    31,    32,    33,     0,   100,   101,   102,   103,
     104,   105,   106,   107,    69,   108,   109,   110,   111,   112,
     113,   114,   115,   100,   101,   102,   103,   104,   105,   106,
     107,     0,   108,   109,   110,   111,   112,   113,   114,   115,
     149,    99,   100,   101,   102,   103,   104,   105,   106,   107,
       0,   108,   109,   110,   111,   112,   113,   215,   100,   101,
     102,   103,   104,   105,   106,   107,     0,   108,   109,   110,
     111,   112,   113,   114,   115,   148,     0,     0,   100,   101,
     102,   103,   104,   105,   106,   107,     0,   108,   109,   110,
     111,   112,   113,   114,   115,   218,   100,   101,   102,   103,
     104,   105,   106,   107,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   100,   101,   102,   103,   104,   105,   106,
     107,     0,   108,   109,   110,   111,   112,   113,   114,   115
};

static const yytype_int16 yycheck[] =
{
      10,    11,    12,    13,    14,    15,    42,     0,     6,    70,
       0,     7,     8,    20,     6,     8,     9,    70,     8,     9,
       7,     8,    19,    19,     7,     8,    70,     7,     8,     6,
      66,    23,    24,    25,    26,    27,    28,    29,    30,    19,
      32,    33,    34,    35,    36,    37,    38,    39,    70,    42,
      57,    70,    42,    23,    24,    25,    26,    27,    28,    29,
      30,    61,    62,    63,    62,    57,    12,    13,    14,    15,
      16,    17,    18,    66,    70,    70,    66,    25,    26,    27,
      78,    70,    58,    70,    60,    70,    96,    70,     7,     8,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,    70,   117,   118,   119,
     120,   121,     7,     8,    70,    61,    62,    63,    19,   129,
     130,   131,   132,   133,   134,    12,    13,    14,    15,    16,
      17,    18,     8,     9,     0,   145,     6,     8,     9,   149,
      12,    13,    14,    15,    16,    12,    13,    14,    15,    16,
      12,     7,   145,     7,     7,   145,    70,    70,    70,    70,
      70,   197,    70,   199,    10,   199,   176,   177,   178,   179,
     180,   145,    27,    -1,    61,    62,    63,   187,   188,   189,
     190,   191,    -1,     4,     5,     6,     7,     8,     9,    -1,
      11,    -1,   202,    -1,    -1,    -1,    17,    18,    19,    -1,
      21,    22,    23,    24,   197,   215,   199,   197,    -1,   199,
      31,    23,    24,    25,    26,    27,    -1,    -1,    -1,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    70,
       4,     5,     6,     7,     8,     9,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    17,    18,    19,    -1,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    60,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    70,     4,     5,     6,
       7,     8,     9,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      17,    18,    19,    -1,    21,    -1,    23,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    69,    70,     4,     5,     6,     7,     8,     9,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      -1,    21,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    -1,    -1,    -1,    64,    65,    66,    67,    68,    69,
      70,     4,     5,    -1,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    -1,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    69,    70,     4,     5,
      -1,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    18,    19,    -1,    21,    -1,    23,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,     7,    -1,    -1,    40,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    70,    41,    42,    43,    44,    45,
      46,    47,    -1,    49,    50,    51,    52,    -1,    -1,    -1,
      -1,    -1,    58,    59,    60,    -1,    23,    24,    25,    26,
      27,    28,    29,    30,    70,    32,    33,    34,    35,    36,
      37,    38,    39,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      57,     6,    23,    24,    25,    26,    27,    28,    29,    30,
      -1,    32,    33,    34,    35,    36,    37,    57,    23,    24,
      25,    26,    27,    28,    29,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    20,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    23,    24,    25,    26,    27,    28,    29,
      30,    -1,    32,    33,    34,    35,    36,    37,    38,    39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    11,    17,    18,
      19,    21,    23,    24,    31,    40,    41,    42,    43,    44,
      45,    46,    47,    49,    50,    51,    52,    53,    54,    55,
      56,    58,    59,    60,    64,    65,    66,    67,    68,    69,
      70,    75,    77,    78,    79,    80,    81,    82,    83,    84,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    99,   100,    70,    70,    82,     6,    41,    70,
      93,    96,    99,   100,    93,    96,    41,    80,    99,   100,
      80,    80,    80,    80,    80,     7,     8,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    19,     0,    78,     6,
      23,    24,    25,    26,    27,    28,    29,    30,    32,    33,
      34,    35,    36,    37,    38,    39,     6,    12,    13,    14,
      15,    16,    17,    18,    61,    62,    63,    98,    98,    12,
      12,    13,    14,    15,    16,    17,    18,    98,     7,     8,
      70,    82,     7,     8,    70,    21,    76,    78,    20,    57,
      70,    70,    20,    80,    85,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    12,    13,    14,    15,
      16,    80,    80,    80,    80,    80,    80,    12,    13,    14,
      15,    16,    70,    70,    70,    70,    22,    77,    80,    10,
      80,    20,    57,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    22,    76,    57,    80,    80,    22
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    76,    76,    76,    77,    77,    78,
      78,    78,    78,    78,    79,    79,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      81,    81,    81,    82,    83,    84,    84,    85,    85,    86,
      86,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    89,    89,    89,    89,    89,    89,    89,    89,    90,
      90,    90,    90,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    92,
      93,    93,    93,    93,    93,    93,    93,    93,    94,    94,
      94,    94,    94,    94,    94,    94,    95,    95,    95,    96,
      97,    97,    97,    97,    97,    97,    97,    97,    98,    98,
      98,    99,    99,    99,    99,    99,    99,   100,   100,   100
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     3,     2,     1,     2,     1,     2,
       2,     1,     2,     1,     3,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     3,     2,     4,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     7,
       3,     3,     2,     2,     2,     2,     3,     2,     3,     3,
       2,     2,     2,     2,     3,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, openvdb::ax::ast::Tree** tree)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (tree);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, openvdb::ax::ast::Tree** tree)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, tree);
  YYFPRINTF (yyo, ")");
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
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
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

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 207 "grammar/axparser.y"
    { *tree = new Tree(); (yyval.tree) = *tree; }
#line 1776 "grammar/axparser.cc"
    break;

  case 3:
#line 208 "grammar/axparser.y"
    { *tree = new Tree((yyvsp[0].block)); (yyval.tree) = *tree; }
#line 1782 "grammar/axparser.cc"
    break;

  case 4:
#line 212 "grammar/axparser.y"
    { (yyval.block) = (yyvsp[-1].block); }
#line 1788 "grammar/axparser.cc"
    break;

  case 5:
#line 213 "grammar/axparser.y"
    { (yyval.block) = new Block(); }
#line 1794 "grammar/axparser.cc"
    break;

  case 6:
#line 214 "grammar/axparser.y"
    { (yyval.block) = new Block(); if((yyvsp[0].statement)) (yyval.block)->mList.emplace_back((yyvsp[0].statement)); }
#line 1800 "grammar/axparser.cc"
    break;

  case 7:
#line 218 "grammar/axparser.y"
    { if ((yyvsp[0].statement)) (yyvsp[-1].block)->mList.emplace_back((yyvsp[0].statement)); (yyval.block) = (yyvsp[-1].block); }
#line 1806 "grammar/axparser.cc"
    break;

  case 8:
#line 219 "grammar/axparser.y"
    { (yyval.block) = new Block(); if ((yyvsp[0].statement)) (yyval.block)->mList.emplace_back((yyvsp[0].statement)); }
#line 1812 "grammar/axparser.cc"
    break;

  case 9:
#line 225 "grammar/axparser.y"
    { (yyval.statement) = (yyvsp[-1].expression); }
#line 1818 "grammar/axparser.cc"
    break;

  case 10:
#line 226 "grammar/axparser.y"
    { (yyval.statement) = (yyvsp[-1].statement); }
#line 1824 "grammar/axparser.cc"
    break;

  case 11:
#line 227 "grammar/axparser.y"
    { (yyval.statement) = (yyvsp[0].statement); }
#line 1830 "grammar/axparser.cc"
    break;

  case 12:
#line 228 "grammar/axparser.y"
    { (yyval.statement) = new Return; }
#line 1836 "grammar/axparser.cc"
    break;

  case 13:
#line 229 "grammar/axparser.y"
    { (yyval.statement) = nullptr; }
#line 1842 "grammar/axparser.cc"
    break;

  case 14:
#line 237 "grammar/axparser.y"
    { (yyval.statement) = new ConditionalStatement((yyvsp[-1].expression), (yyvsp[0].block), new Block()); }
#line 1848 "grammar/axparser.cc"
    break;

  case 15:
#line 238 "grammar/axparser.y"
    { (yyval.statement) = new ConditionalStatement((yyvsp[-3].expression), (yyvsp[-2].block), (yyvsp[0].block)); }
#line 1854 "grammar/axparser.cc"
    break;

  case 16:
#line 244 "grammar/axparser.y"
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1860 "grammar/axparser.cc"
    break;

  case 17:
#line 245 "grammar/axparser.y"
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1866 "grammar/axparser.cc"
    break;

  case 18:
#line 246 "grammar/axparser.y"
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1872 "grammar/axparser.cc"
    break;

  case 19:
#line 247 "grammar/axparser.y"
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1878 "grammar/axparser.cc"
    break;

  case 20:
#line 248 "grammar/axparser.y"
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1884 "grammar/axparser.cc"
    break;

  case 21:
#line 249 "grammar/axparser.y"
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1890 "grammar/axparser.cc"
    break;

  case 22:
#line 250 "grammar/axparser.y"
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1896 "grammar/axparser.cc"
    break;

  case 23:
#line 251 "grammar/axparser.y"
    { (yyval.expression) = (yyvsp[0].expression); }
#line 1902 "grammar/axparser.cc"
    break;

  case 24:
#line 252 "grammar/axparser.y"
    { (yyval.expression) = (yyvsp[0].value); }
#line 1908 "grammar/axparser.cc"
    break;

  case 25:
#line 253 "grammar/axparser.y"
    { (yyval.expression) = (yyvsp[0].vector_unpack); }
#line 1914 "grammar/axparser.cc"
    break;

  case 26:
#line 254 "grammar/axparser.y"
    { (yyval.expression) = (yyvsp[0].value); }
#line 1920 "grammar/axparser.cc"
    break;

  case 27:
#line 255 "grammar/axparser.y"
    { (yyval.expression) = (yyvsp[0].external); }
#line 1926 "grammar/axparser.cc"
    break;

  case 28:
#line 256 "grammar/axparser.y"
    { (yyval.expression) = new LocalValue((yyvsp[0].local)); }
#line 1932 "grammar/axparser.cc"
    break;

  case 29:
#line 257 "grammar/axparser.y"
    { (yyval.expression) = new AttributeValue((yyvsp[0].attribute)); }
#line 1938 "grammar/axparser.cc"
    break;

  case 30:
#line 264 "grammar/axparser.y"
    { (yyval.vector_unpack) = new VectorUnpack(new AttributeValue((yyvsp[-1].attribute)), (yyvsp[0].index)); }
#line 1944 "grammar/axparser.cc"
    break;

  case 31:
#line 265 "grammar/axparser.y"
    { (yyval.vector_unpack) = new VectorUnpack(new LocalValue((yyvsp[-1].local)), (yyvsp[0].index)); }
#line 1950 "grammar/axparser.cc"
    break;

  case 32:
#line 266 "grammar/axparser.y"
    { (yyval.vector_unpack) = new VectorUnpack((yyvsp[-1].external), (yyvsp[0].index)); }
#line 1956 "grammar/axparser.cc"
    break;

  case 33:
#line 271 "grammar/axparser.y"
    { (yyval.expression) = (yyvsp[-1].expression); }
#line 1962 "grammar/axparser.cc"
    break;

  case 34:
#line 278 "grammar/axparser.y"
    { (yyval.expression) = new Cast((yyvsp[0].expression), (yyvsp[-1].string)); }
#line 1968 "grammar/axparser.cc"
    break;

  case 35:
#line 283 "grammar/axparser.y"
    { (yyval.expression) = new FunctionCall((yyvsp[-3].string), (yyvsp[-1].expressionlist)); free((char*)(yyvsp[-3].string)); }
#line 1974 "grammar/axparser.cc"
    break;

  case 36:
#line 284 "grammar/axparser.y"
    { (yyval.expression) = new FunctionCall((yyvsp[-2].string)); free((char*)(yyvsp[-2].string)); }
#line 1980 "grammar/axparser.cc"
    break;

  case 37:
#line 289 "grammar/axparser.y"
    { (yyval.expressionlist) = new ExpressionList(); (yyval.expressionlist)->mList.emplace_back((yyvsp[0].expression)); }
#line 1986 "grammar/axparser.cc"
    break;

  case 38:
#line 290 "grammar/axparser.y"
    { (yyvsp[-2].expressionlist)->mList.emplace_back((yyvsp[0].expression)); (yyval.expressionlist) = (yyvsp[-2].expressionlist); }
#line 1992 "grammar/axparser.cc"
    break;

  case 39:
#line 297 "grammar/axparser.y"
    { (yyval.statement) = new AssignExpression((yyvsp[-2].declare_local), (yyvsp[0].expression)); }
#line 1998 "grammar/axparser.cc"
    break;

  case 40:
#line 298 "grammar/axparser.y"
    { (yyval.statement) = (yyvsp[0].declare_local); }
#line 2004 "grammar/axparser.cc"
    break;

  case 41:
#line 307 "grammar/axparser.y"
    { (yyval.expression) = new AssignExpression((yyvsp[-2].attribute), (yyvsp[0].expression)); }
#line 2010 "grammar/axparser.cc"
    break;

  case 42:
#line 308 "grammar/axparser.y"
    { (yyval.expression) = new AssignExpression((yyvsp[-2].attribute), new BinaryOperator(tokens::PLUS, new AttributeValue((yyvsp[-2].attribute)->copy()), (yyvsp[0].expression))); }
#line 2016 "grammar/axparser.cc"
    break;

  case 43:
#line 309 "grammar/axparser.y"
    { (yyval.expression) = new AssignExpression((yyvsp[-2].attribute), new BinaryOperator(tokens::MINUS, new AttributeValue((yyvsp[-2].attribute)->copy()), (yyvsp[0].expression))); }
#line 2022 "grammar/axparser.cc"
    break;

  case 44:
#line 310 "grammar/axparser.y"
    { (yyval.expression) = new AssignExpression((yyvsp[-2].attribute), new BinaryOperator(tokens::MULTIPLY, new AttributeValue((yyvsp[-2].attribute)->copy()), (yyvsp[0].expression))); }
#line 2028 "grammar/axparser.cc"
    break;

  case 45:
#line 311 "grammar/axparser.y"
    { (yyval.expression) = new AssignExpression((yyvsp[-2].attribute), new BinaryOperator(tokens::DIVIDE, new AttributeValue((yyvsp[-2].attribute)->copy()), (yyvsp[0].expression))); }
#line 2034 "grammar/axparser.cc"
    break;

  case 46:
#line 312 "grammar/axparser.y"
    { (yyval.expression) = new AssignExpression((yyvsp[-2].local), (yyvsp[0].expression)); }
#line 2040 "grammar/axparser.cc"
    break;

  case 47:
#line 313 "grammar/axparser.y"
    { (yyval.expression) = new AssignExpression((yyvsp[-2].local), new BinaryOperator(tokens::PLUS, new LocalValue((yyvsp[-2].local)->copy()), (yyvsp[0].expression))); }
#line 2046 "grammar/axparser.cc"
    break;

  case 48:
#line 314 "grammar/axparser.y"
    { (yyval.expression) = new AssignExpression((yyvsp[-2].local), new BinaryOperator(tokens::MINUS, new LocalValue((yyvsp[-2].local)->copy()), (yyvsp[0].expression))); }
#line 2052 "grammar/axparser.cc"
    break;

  case 49:
#line 315 "grammar/axparser.y"
    { (yyval.expression) = new AssignExpression((yyvsp[-2].local), new BinaryOperator(tokens::MULTIPLY, new LocalValue((yyvsp[-2].local)->copy()), (yyvsp[0].expression))); }
#line 2058 "grammar/axparser.cc"
    break;

  case 50:
#line 316 "grammar/axparser.y"
    { (yyval.expression) = new AssignExpression((yyvsp[-2].local), new BinaryOperator(tokens::DIVIDE, new LocalValue((yyvsp[-2].local)->copy()), (yyvsp[0].expression))); }
#line 2064 "grammar/axparser.cc"
    break;

  case 51:
#line 327 "grammar/axparser.y"
    { (yyval.expression) = buildAttributeComponentExpression(nullptr, (yyvsp[-3].attribute), (yyvsp[-2].index), (yyvsp[0].expression)); }
#line 2070 "grammar/axparser.cc"
    break;

  case 52:
#line 328 "grammar/axparser.y"
    { (yyval.expression) = buildAttributeComponentExpression(new tokens::OperatorToken(tokens::PLUS), (yyvsp[-3].attribute), (yyvsp[-2].index), (yyvsp[0].expression)); }
#line 2076 "grammar/axparser.cc"
    break;

  case 53:
#line 329 "grammar/axparser.y"
    { (yyval.expression) = buildAttributeComponentExpression(new tokens::OperatorToken(tokens::MINUS), (yyvsp[-3].attribute), (yyvsp[-2].index), (yyvsp[0].expression)); }
#line 2082 "grammar/axparser.cc"
    break;

  case 54:
#line 330 "grammar/axparser.y"
    { (yyval.expression) = buildAttributeComponentExpression(new tokens::OperatorToken(tokens::MULTIPLY), (yyvsp[-3].attribute), (yyvsp[-2].index), (yyvsp[0].expression)); }
#line 2088 "grammar/axparser.cc"
    break;

  case 55:
#line 331 "grammar/axparser.y"
    { (yyval.expression) = buildAttributeComponentExpression(new tokens::OperatorToken(tokens::DIVIDE), (yyvsp[-3].attribute), (yyvsp[-2].index), (yyvsp[0].expression)); }
#line 2094 "grammar/axparser.cc"
    break;

  case 56:
#line 332 "grammar/axparser.y"
    { (yyval.expression) = buildLocalComponentExpression(nullptr, (yyvsp[-3].local), (yyvsp[-2].index), (yyvsp[0].expression)); }
#line 2100 "grammar/axparser.cc"
    break;

  case 57:
#line 333 "grammar/axparser.y"
    { (yyval.expression) = buildLocalComponentExpression(new tokens::OperatorToken(tokens::PLUS), (yyvsp[-3].local), (yyvsp[-2].index), (yyvsp[0].expression)); }
#line 2106 "grammar/axparser.cc"
    break;

  case 58:
#line 334 "grammar/axparser.y"
    { (yyval.expression) = buildLocalComponentExpression(new tokens::OperatorToken(tokens::MINUS), (yyvsp[-3].local), (yyvsp[-2].index), (yyvsp[0].expression)); }
#line 2112 "grammar/axparser.cc"
    break;

  case 59:
#line 335 "grammar/axparser.y"
    { (yyval.expression) = buildLocalComponentExpression(new tokens::OperatorToken(tokens::MULTIPLY), (yyvsp[-3].local), (yyvsp[-2].index), (yyvsp[0].expression)); }
#line 2118 "grammar/axparser.cc"
    break;

  case 60:
#line 336 "grammar/axparser.y"
    { (yyval.expression) = buildLocalComponentExpression(new tokens::OperatorToken(tokens::DIVIDE), (yyvsp[-3].local), (yyvsp[-2].index), (yyvsp[0].expression)); }
#line 2124 "grammar/axparser.cc"
    break;

  case 61:
#line 345 "grammar/axparser.y"
    { (yyval.expression) = new Crement((yyvsp[0].attribute), new AttributeValue((yyvsp[0].attribute)->copy()), Crement::Increment, /*post*/false); }
#line 2130 "grammar/axparser.cc"
    break;

  case 62:
#line 346 "grammar/axparser.y"
    { (yyval.expression) = new Crement((yyvsp[0].attribute), new AttributeValue((yyvsp[0].attribute)->copy()), Crement::Decrement, /*post*/false); }
#line 2136 "grammar/axparser.cc"
    break;

  case 63:
#line 347 "grammar/axparser.y"
    { (yyval.expression) = new Crement((yyvsp[-1].attribute), new AttributeValue((yyvsp[-1].attribute)->copy()), Crement::Increment, /*post*/true); }
#line 2142 "grammar/axparser.cc"
    break;

  case 64:
#line 348 "grammar/axparser.y"
    { (yyval.expression) = new Crement((yyvsp[-1].attribute), new AttributeValue((yyvsp[-1].attribute)->copy()), Crement::Decrement, /*post*/true); }
#line 2148 "grammar/axparser.cc"
    break;

  case 65:
#line 349 "grammar/axparser.y"
    { (yyval.expression) = new Crement((yyvsp[0].local), new LocalValue((yyvsp[0].local)->copy()), Crement::Increment, /*post*/false); }
#line 2154 "grammar/axparser.cc"
    break;

  case 66:
#line 350 "grammar/axparser.y"
    { (yyval.expression) = new Crement((yyvsp[0].local), new LocalValue((yyvsp[0].local)->copy()), Crement::Decrement, /*post*/false); }
#line 2160 "grammar/axparser.cc"
    break;

  case 67:
#line 351 "grammar/axparser.y"
    { (yyval.expression) = new Crement((yyvsp[-1].local), new LocalValue((yyvsp[-1].local)->copy()), Crement::Increment, /*post*/true); }
#line 2166 "grammar/axparser.cc"
    break;

  case 68:
#line 352 "grammar/axparser.y"
    { (yyval.expression) = new Crement((yyvsp[-1].local), new LocalValue((yyvsp[-1].local)->copy()), Crement::Decrement, /*post*/true); }
#line 2172 "grammar/axparser.cc"
    break;

  case 69:
#line 357 "grammar/axparser.y"
    { (yyval.expression) = new UnaryOperator(tokens::PLUS, (yyvsp[0].expression)); }
#line 2178 "grammar/axparser.cc"
    break;

  case 70:
#line 358 "grammar/axparser.y"
    { (yyval.expression) = new UnaryOperator(tokens::MINUS, (yyvsp[0].expression)); }
#line 2184 "grammar/axparser.cc"
    break;

  case 71:
#line 359 "grammar/axparser.y"
    { (yyval.expression) = new UnaryOperator(tokens::BITNOT, (yyvsp[0].expression)); }
#line 2190 "grammar/axparser.cc"
    break;

  case 72:
#line 360 "grammar/axparser.y"
    { (yyval.expression) = new UnaryOperator(tokens::NOT, (yyvsp[0].expression)); }
#line 2196 "grammar/axparser.cc"
    break;

  case 73:
#line 366 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::PLUS, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2202 "grammar/axparser.cc"
    break;

  case 74:
#line 367 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::MINUS, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2208 "grammar/axparser.cc"
    break;

  case 75:
#line 368 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::MULTIPLY, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2214 "grammar/axparser.cc"
    break;

  case 76:
#line 369 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::DIVIDE, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2220 "grammar/axparser.cc"
    break;

  case 77:
#line 370 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::MODULO, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2226 "grammar/axparser.cc"
    break;

  case 78:
#line 371 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::BITAND, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2232 "grammar/axparser.cc"
    break;

  case 79:
#line 372 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::BITOR, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2238 "grammar/axparser.cc"
    break;

  case 80:
#line 373 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::BITXOR, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2244 "grammar/axparser.cc"
    break;

  case 81:
#line 374 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::AND, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2250 "grammar/axparser.cc"
    break;

  case 82:
#line 375 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::OR, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2256 "grammar/axparser.cc"
    break;

  case 83:
#line 376 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::EQUALSEQUALS, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2262 "grammar/axparser.cc"
    break;

  case 84:
#line 377 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::NOTEQUALS, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2268 "grammar/axparser.cc"
    break;

  case 85:
#line 378 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::MORETHAN, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2274 "grammar/axparser.cc"
    break;

  case 86:
#line 379 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::LESSTHAN, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2280 "grammar/axparser.cc"
    break;

  case 87:
#line 380 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::MORETHANOREQUAL, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2286 "grammar/axparser.cc"
    break;

  case 88:
#line 381 "grammar/axparser.y"
    { (yyval.expression) = new BinaryOperator(tokens::LESSTHANOREQUAL, (yyvsp[-2].expression), (yyvsp[0].expression)); }
#line 2292 "grammar/axparser.cc"
    break;

  case 89:
#line 386 "grammar/axparser.y"
    { (yyval.value) = new VectorPack((yyvsp[-5].expression), (yyvsp[-3].expression), (yyvsp[-1].expression)); }
#line 2298 "grammar/axparser.cc"
    break;

  case 90:
#line 391 "grammar/axparser.y"
    { (yyval.attribute) = new Attribute((yyvsp[0].string), (yyvsp[-2].string)); free((char*)(yyvsp[0].string)); }
#line 2304 "grammar/axparser.cc"
    break;

  case 91:
#line 392 "grammar/axparser.y"
    { (yyval.attribute) = new Attribute((yyvsp[0].string), (yyvsp[-2].string)); free((char*)(yyvsp[0].string)); }
#line 2310 "grammar/axparser.cc"
    break;

  case 92:
#line 393 "grammar/axparser.y"
    { (yyval.attribute) = new Attribute((yyvsp[0].string), openvdb::typeNameAsString<int32_t>()); free((char*)(yyvsp[0].string)); }
#line 2316 "grammar/axparser.cc"
    break;

  case 93:
#line 394 "grammar/axparser.y"
    { (yyval.attribute) = new Attribute((yyvsp[0].string), openvdb::typeNameAsString<float>()); free((char*)(yyvsp[0].string)); }
#line 2322 "grammar/axparser.cc"
    break;

  case 94:
#line 395 "grammar/axparser.y"
    { (yyval.attribute) = new Attribute((yyvsp[0].string), openvdb::typeNameAsString<openvdb::Vec3s>()); free((char*)(yyvsp[0].string)); }
#line 2328 "grammar/axparser.cc"
    break;

  case 95:
#line 396 "grammar/axparser.y"
    { (yyval.attribute) = new Attribute((yyvsp[0].string), openvdb::typeNameAsString<std::string>()); free((char*)(yyvsp[0].string)); }
#line 2334 "grammar/axparser.cc"
    break;

  case 96:
#line 397 "grammar/axparser.y"
    { (yyval.attribute) = new Attribute((yyvsp[0].string), openvdb::typeNameAsString<std::string>()); free((char*)(yyvsp[0].string)); }
#line 2340 "grammar/axparser.cc"
    break;

  case 97:
#line 398 "grammar/axparser.y"
    { (yyval.attribute) = new Attribute((yyvsp[0].string), openvdb::typeNameAsString<float>(), true); free((char*)(yyvsp[0].string)); }
#line 2346 "grammar/axparser.cc"
    break;

  case 98:
#line 403 "grammar/axparser.y"
    { (yyval.external) = new ExternalVariable((yyvsp[0].string), (yyvsp[-2].string)); free((char*)(yyvsp[0].string)); }
#line 2352 "grammar/axparser.cc"
    break;

  case 99:
#line 404 "grammar/axparser.y"
    { (yyval.external) = new ExternalVariable((yyvsp[0].string), (yyvsp[-2].string)); free((char*)(yyvsp[0].string)); }
#line 2358 "grammar/axparser.cc"
    break;

  case 100:
#line 405 "grammar/axparser.y"
    { (yyval.external) = new ExternalVariable((yyvsp[0].string), openvdb::typeNameAsString<int32_t>()); free((char*)(yyvsp[0].string)); }
#line 2364 "grammar/axparser.cc"
    break;

  case 101:
#line 406 "grammar/axparser.y"
    { (yyval.external) = new ExternalVariable((yyvsp[0].string), openvdb::typeNameAsString<float>()); free((char*)(yyvsp[0].string)); }
#line 2370 "grammar/axparser.cc"
    break;

  case 102:
#line 407 "grammar/axparser.y"
    { (yyval.external) = new ExternalVariable((yyvsp[0].string), openvdb::typeNameAsString<openvdb::Vec3s>()); free((char*)(yyvsp[0].string)); }
#line 2376 "grammar/axparser.cc"
    break;

  case 103:
#line 408 "grammar/axparser.y"
    { (yyval.external) = new ExternalVariable((yyvsp[0].string), openvdb::typeNameAsString<std::string>()); free((char*)(yyvsp[0].string)); }
#line 2382 "grammar/axparser.cc"
    break;

  case 104:
#line 409 "grammar/axparser.y"
    { (yyval.external) = new ExternalVariable((yyvsp[0].string), openvdb::typeNameAsString<std::string>()); free((char*)(yyvsp[0].string)); }
#line 2388 "grammar/axparser.cc"
    break;

  case 105:
#line 410 "grammar/axparser.y"
    { (yyval.external) = new ExternalVariable((yyvsp[0].string), openvdb::typeNameAsString<float>()); free((char*)(yyvsp[0].string)); }
#line 2394 "grammar/axparser.cc"
    break;

  case 106:
#line 415 "grammar/axparser.y"
    { (yyval.declare_local) = new DeclareLocal((yyvsp[0].string), (yyvsp[-1].string)); free((char*)(yyvsp[0].string)); }
#line 2400 "grammar/axparser.cc"
    break;

  case 107:
#line 416 "grammar/axparser.y"
    { (yyval.declare_local) = new DeclareLocal((yyvsp[0].string), (yyvsp[-1].string)); free((char*)(yyvsp[0].string)); }
#line 2406 "grammar/axparser.cc"
    break;

  case 108:
#line 417 "grammar/axparser.y"
    { (yyval.declare_local) = new DeclareLocal((yyvsp[0].string), openvdb::typeNameAsString<std::string>()); free((char*)(yyvsp[0].string)); }
#line 2412 "grammar/axparser.cc"
    break;

  case 109:
#line 424 "grammar/axparser.y"
    { (yyval.local) = new Local((yyvsp[0].string)); free((char*)(yyvsp[0].string)); }
#line 2418 "grammar/axparser.cc"
    break;

  case 110:
#line 431 "grammar/axparser.y"
    { (yyval.value) = new Value<int16_t>((yyvsp[0].string)); free((char*)(yyvsp[0].string)); }
#line 2424 "grammar/axparser.cc"
    break;

  case 111:
#line 432 "grammar/axparser.y"
    { (yyval.value) = new Value<int32_t>((yyvsp[0].string)); free((char*)(yyvsp[0].string)); }
#line 2430 "grammar/axparser.cc"
    break;

  case 112:
#line 433 "grammar/axparser.y"
    { (yyval.value) = new Value<int64_t>((yyvsp[0].string)); free((char*)(yyvsp[0].string)); }
#line 2436 "grammar/axparser.cc"
    break;

  case 113:
#line 434 "grammar/axparser.y"
    { (yyval.value) = new Value<float>((yyvsp[0].string)); free((char*)(yyvsp[0].string)); }
#line 2442 "grammar/axparser.cc"
    break;

  case 114:
#line 435 "grammar/axparser.y"
    { (yyval.value) = new Value<double>((yyvsp[0].string)); free((char*)(yyvsp[0].string)); }
#line 2448 "grammar/axparser.cc"
    break;

  case 115:
#line 436 "grammar/axparser.y"
    { (yyval.value) = new Value<std::string>((yyvsp[0].string)); free((char*)(yyvsp[0].string)); }
#line 2454 "grammar/axparser.cc"
    break;

  case 116:
#line 437 "grammar/axparser.y"
    { (yyval.value) = new Value<bool>(true); }
#line 2460 "grammar/axparser.cc"
    break;

  case 117:
#line 438 "grammar/axparser.y"
    { (yyval.value) = new Value<bool>(false); }
#line 2466 "grammar/axparser.cc"
    break;

  case 118:
#line 443 "grammar/axparser.y"
    { (yyval.index) = 0; }
#line 2472 "grammar/axparser.cc"
    break;

  case 119:
#line 444 "grammar/axparser.y"
    { (yyval.index) = 1; }
#line 2478 "grammar/axparser.cc"
    break;

  case 120:
#line 445 "grammar/axparser.y"
    { (yyval.index) = 2; }
#line 2484 "grammar/axparser.cc"
    break;

  case 121:
#line 451 "grammar/axparser.y"
    { (yyval.string) = openvdb::typeNameAsString<bool>(); }
#line 2490 "grammar/axparser.cc"
    break;

  case 122:
#line 452 "grammar/axparser.y"
    { (yyval.string) = openvdb::typeNameAsString<int16_t>(); }
#line 2496 "grammar/axparser.cc"
    break;

  case 123:
#line 453 "grammar/axparser.y"
    { (yyval.string) = openvdb::typeNameAsString<int32_t>(); }
#line 2502 "grammar/axparser.cc"
    break;

  case 124:
#line 454 "grammar/axparser.y"
    { (yyval.string) = openvdb::typeNameAsString<int64_t>(); }
#line 2508 "grammar/axparser.cc"
    break;

  case 125:
#line 455 "grammar/axparser.y"
    { (yyval.string) = openvdb::typeNameAsString<float>(); }
#line 2514 "grammar/axparser.cc"
    break;

  case 126:
#line 456 "grammar/axparser.y"
    { (yyval.string) = openvdb::typeNameAsString<double>(); }
#line 2520 "grammar/axparser.cc"
    break;

  case 127:
#line 462 "grammar/axparser.y"
    { (yyval.string) = openvdb::typeNameAsString<openvdb::Vec3i>(); }
#line 2526 "grammar/axparser.cc"
    break;

  case 128:
#line 463 "grammar/axparser.y"
    { (yyval.string) = openvdb::typeNameAsString<openvdb::Vec3s>(); }
#line 2532 "grammar/axparser.cc"
    break;

  case 129:
#line 464 "grammar/axparser.y"
    { (yyval.string) = openvdb::typeNameAsString<openvdb::Vec3d>(); }
#line 2538 "grammar/axparser.cc"
    break;


#line 2542 "grammar/axparser.cc"

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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
#line 466 "grammar/axparser.y"


// Copyright (c) 2015-2019 DNEG
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
