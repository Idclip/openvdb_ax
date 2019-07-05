/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison interface for Yacc-like parsers in C

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
