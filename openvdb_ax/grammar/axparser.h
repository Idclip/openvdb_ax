/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 158 "grammar/axparser.h"

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
