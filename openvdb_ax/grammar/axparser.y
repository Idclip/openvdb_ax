///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2015-2019 DNEG
//
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
//
// Redistributions of source code must retain the above copyright
// and license notice and the following restrictions and disclaimer.
//
// *     Neither the name of DNEG nor the names
// of its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// IN NO EVENT SHALL THE COPYRIGHT HOLDERS' AND CONTRIBUTORS' AGGREGATE
// LIABILITY FOR ALL CLAIMS REGARDLESS OF THEIR BASIS EXCEED US$250.00.
//
///////////////////////////////////////////////////////////////////////////

%{
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
%}

/* Option 'parse.error verbose' tells bison to output verbose parsing errors
 * as a char* array to yyerror (axerror). Note that this is in lieu of doing
 * more specific error handling ourselves, as the actual tokens are printed
 * which is confusing.
 * @todo Implement a proper error handler
 */
%define parse.error verbose

/* Option 'api.prefix {ax}' matches the prefix option in the lexer to produce
 * prefixed C++ symbols (where 'yy' is replaced with 'ax') so we can link
 * with other flex-generated lexers in the same application.
 */
%define api.prefix {ax}

/* Tell bison to track grammar locations
 */
%locations

%union
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
}

%start statements

%token TRUE FALSE
%token SEMICOLON AT DOLLAR
%token IF ELSE
%token RETURN
%token LCURLY RCURLY
%token LSQUARE RSQUARE
%token STRING DOUBLE FLOAT LONG INT SHORT BOOL VOID
%token VEC2I VEC2F VEC2D VEC3I VEC3F VEC3D VEC4I VEC4F VEC4D
%token F_AT I_AT V_AT S_AT
%token MAT3F MAT3D MAT4F MAT4D M3F_AT M4F_AT
%token F_DOLLAR I_DOLLAR V_DOLLAR S_DOLLAR
%token DOT_X DOT_Y DOT_Z

%token <string> L_SHORT
%token <string> L_INT
%token <string> L_LONG
%token <string> L_FLOAT
%token <string> L_DOUBLE
%token <string> L_STRING
%token <string> IDENTIFIER

%type <tree> statements
%type <block> block
%type <block> body
%type <statement> statement
%type <statement> conditional_statement
%type <statement> declaration
%type <expression> assign_expression
%type <expression> expression
%type <expression> function_call_expression
%type <expression> binary_expression
%type <expression> unary_expression
%type <expression> array
%type <expression> variable_reference
%type <expression> pre_crement
%type <expression> post_crement
%type <variable> variable
%type <expressionlist> arguments
%type <attribute> attribute
%type <external> external
%type <declare_local> declare_local
%type <local> local

%type <value> literal
%type <index> type
%type <index> scalar_type
%type <index> vector_type
%type <index> matrix_type

// *************************************************************
// * Operator Precedence Definitions
// *************************************************************
//
// @note Precendence goes from lowest to highest, e.g. assignment
//   operations are generally lowest. Note that this precedence and
//   associativity is heavily based off of C++:
//   https://en.cppreference.com/w/cpp/language/operator_precedence

%left COMMA
%right EQUALS PLUSEQUALS MINUSEQUALS MULTIPLYEQUALS DIVIDEEQUALS MODULOEQUALS BITANDEQUALS BITXOREQUALS BITOREQUALS
%left OR
%left AND
%left BITOR
%left BITXOR
%left BITAND
%left EQUALSEQUALS NOTEQUALS
%left MORETHAN LESSTHAN MORETHANOREQUAL LESSTHANOREQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%left NOT BITNOT PLUSPLUS MINUSMINUS
%left LPARENS RPARENS

%nonassoc LOWER_THAN_ELSE //null token to force no associativity in conditional statement
%nonassoc ELSE

%parse-param {openvdb::ax::ast::Tree** tree}

%%

statements:
      { *tree = new Tree(); $$ = *tree; } /* nothing */
    | body { *tree = new Tree($1); $$ = *tree; }
;

block:
      LCURLY body RCURLY  { $$ = $2; }
    | LCURLY RCURLY       { $$ = new Block(); }
    | statement           { $$ = new Block(); $$->addStatement($1); }
;

body:
      body statement  { $1->addStatement($2); $$ = $1; }
    | statement       { $$ = new Block(); $$->addStatement($1); }
;

/// @brief  Syntax for a statement; a line followed by a semicolon or a
///         conditional statement
statement:
      expression SEMICOLON      { $$ = $1; }
    | declaration SEMICOLON     { $$ = $1; }
    | conditional_statement     { $$ = $1; }
    | RETURN SEMICOLON          { $$ = new Return; }
    | SEMICOLON                 { $$ = nullptr; } // only possible nullptr rule
;

/// @brief  Syntax for a conditional statement, capable of supporting a single if
///         and an optional single else clause
/// @todo   Support multiple else if statements
/// @todo   Support break keyword
conditional_statement:
      IF LPARENS expression RPARENS block %prec LOWER_THAN_ELSE   { $$ = new ConditionalStatement($3, ($5 ? $5 : new Block())); }
    | IF LPARENS expression RPARENS block ELSE block              { $$ = new ConditionalStatement($3, ($5 ? $5 : new Block()), ($7 ? $7 : new Block())); }
;

/// @brief  Syntax for a combination of all numerical expressions which can return
///         an rvalue.
expression:
      binary_expression            { $$ = $1; }
    | unary_expression             { $$ = $1; }
    | assign_expression            { $$ = $1; }
    | function_call_expression     { $$ = $1; }
    | literal                      { $$ = $1; }
    | external                     { $$ = $1; }
    | post_crement                 { $$ = $1; }
    | array                        { $$ = $1; }
    | variable_reference           { $$ = $1; }
    | LPARENS expression RPARENS   { $$ = $2; }
;

/// @brief  A function call, taking zero or any arguments
function_call_expression:
      IDENTIFIER LPARENS arguments RPARENS    { $$ = new FunctionCall($1, $3); free(const_cast<char*>($1)); }
    | IDENTIFIER LPARENS RPARENS              { $$ = new FunctionCall($1); free(const_cast<char*>($1)); }
    | scalar_type LPARENS expression RPARENS  { $$ = new Cast($3, static_cast<tokens::CoreType>($1)); }
;

/// @brief  An argument list of at least size 1
arguments:
      expression                  { $$ = new ExpressionList(); $$->addExpression($1); }
    | arguments COMMA expression  { $1->addExpression($3); $$ = $1; }
;

/// @brief  The declaration of local variables. Unlike assign expression which
///         return values (for assignment chains), assign declarations must end
///         in a statement.
declaration:
      declare_local EQUALS expression  { $$ = new AssignExpression($1, $3, false); }
    | declare_local                    { $$ = $1; }
;

/// @brief  Assign expressions for attributes and local variables
assign_expression:
      variable_reference EQUALS expression          { $$ = new AssignExpression($1, $3, false); }
    | variable_reference PLUSEQUALS expression      { $$ = new AssignExpression($1, new BinaryOperator(tokens::PLUS, $1->copy(), $3), true); }
    | variable_reference MINUSEQUALS expression     { $$ = new AssignExpression($1, new BinaryOperator(tokens::MINUS, $1->copy(), $3), true); }
    | variable_reference MULTIPLYEQUALS expression  { $$ = new AssignExpression($1, new BinaryOperator(tokens::MULTIPLY, $1->copy(), $3), true); }
    | variable_reference DIVIDEEQUALS expression    { $$ = new AssignExpression($1, new BinaryOperator(tokens::DIVIDE, $1->copy(), $3), true); }
    | variable_reference MODULOEQUALS expression    { $$ = new AssignExpression($1, new BinaryOperator(tokens::MODULO, $1->copy(), $3), true); }
    | variable_reference BITANDEQUALS expression    { $$ = new AssignExpression($1, new BinaryOperator(tokens::BITAND, $1->copy(), $3), true); }
    | variable_reference BITXOREQUALS expression    { $$ = new AssignExpression($1, new BinaryOperator(tokens::BITXOR, $1->copy(), $3), true); }
    | variable_reference BITOREQUALS expression     { $$ = new AssignExpression($1, new BinaryOperator(tokens::BITOR, $1->copy(), $3), true); }
;

/// @brief  A binary expression which takes a left and right hand side expression
///         and returns an expression
binary_expression:
      expression PLUS expression             { $$ = new BinaryOperator(tokens::PLUS, $1, $3); }
    | expression MINUS expression            { $$ = new BinaryOperator(tokens::MINUS, $1, $3); }
    | expression MULTIPLY expression         { $$ = new BinaryOperator(tokens::MULTIPLY, $1, $3); }
    | expression DIVIDE expression           { $$ = new BinaryOperator(tokens::DIVIDE, $1, $3); }
    | expression MODULO expression           { $$ = new BinaryOperator(tokens::MODULO, $1, $3); }
    | expression BITAND expression           { $$ = new BinaryOperator(tokens::BITAND, $1, $3); }
    | expression BITOR expression            { $$ = new BinaryOperator(tokens::BITOR, $1, $3); }
    | expression BITXOR expression           { $$ = new BinaryOperator(tokens::BITXOR, $1, $3); }
    | expression AND expression              { $$ = new BinaryOperator(tokens::AND, $1, $3); }
    | expression OR expression               { $$ = new BinaryOperator(tokens::OR, $1, $3); }
    | expression EQUALSEQUALS expression     { $$ = new BinaryOperator(tokens::EQUALSEQUALS, $1, $3); }
    | expression NOTEQUALS expression        { $$ = new BinaryOperator(tokens::NOTEQUALS, $1, $3); }
    | expression MORETHAN expression         { $$ = new BinaryOperator(tokens::MORETHAN, $1, $3); }
    | expression LESSTHAN expression         { $$ = new BinaryOperator(tokens::LESSTHAN, $1, $3); }
    | expression MORETHANOREQUAL expression  { $$ = new BinaryOperator(tokens::MORETHANOREQUAL, $1, $3); }
    | expression LESSTHANOREQUAL expression  { $$ = new BinaryOperator(tokens::LESSTHANOREQUAL, $1, $3); }
;

/// @brief  A unary expression which takes an expression and returns an expression
unary_expression:
      PLUS expression        { $$ = new UnaryOperator(tokens::PLUS, $2); }
    | MINUS expression       { $$ = new UnaryOperator(tokens::MINUS, $2); }
    | BITNOT expression      { $$ = new UnaryOperator(tokens::BITNOT, $2); }
    | NOT expression         { $$ = new UnaryOperator(tokens::NOT, $2); }
;

pre_crement:
      PLUSPLUS variable_reference    { $$ = new Crement($2, Crement::Increment, /*post*/false); }
    | MINUSMINUS variable_reference  { $$ = new Crement($2, Crement::Decrement, /*post*/false); }
;

post_crement:
      variable_reference PLUSPLUS    { $$ = new Crement($1, Crement::Increment, /*post*/true); }
    | variable_reference MINUSMINUS  { $$ = new Crement($1, Crement::Decrement, /*post*/true); }
;

/// @brief  Syntax which can return a valid variable lvalue
variable_reference:
      variable                                              { $$ = $1; }
    | pre_crement                                           { $$ = $1;}
    | variable DOT_X                                        { $$ = new ArrayUnpack($1, new Value<int32_t>(0)); }
    | variable DOT_Y                                        { $$ = new ArrayUnpack($1, new Value<int32_t>(1)); }
    | variable DOT_Z                                        { $$ = new ArrayUnpack($1, new Value<int32_t>(2)); }
    | variable LSQUARE expression RSQUARE                   { $$ = new ArrayUnpack($1, $3); }
    | variable LSQUARE expression COMMA expression RSQUARE  { $$ = new ArrayUnpack($1, $3, $5); }
;

/// @brief  Syntax for vector literals
array:
    LCURLY arguments RCURLY { $$ = new ArrayPack($2); }
;

/// @brief  Objects which are assignable are considered variables. Importantly,
///         externals are not classified in this rule as they are read only.
variable:
      attribute  { $$ = $1; }
    | local      { $$ = $1; }
;

/// @brief  Syntax for supported attribute access
attribute:
      type AT IDENTIFIER     { $$ = new Attribute($3, static_cast<tokens::CoreType>($1)); free(const_cast<char*>($3)); }
    | I_AT IDENTIFIER        { $$ = new Attribute($2, tokens::INT); free(const_cast<char*>($2)); }
    | F_AT IDENTIFIER        { $$ = new Attribute($2, tokens::FLOAT); free(const_cast<char*>($2)); }
    | V_AT IDENTIFIER        { $$ = new Attribute($2, tokens::VEC3F); free(const_cast<char*>($2)); }
    | S_AT IDENTIFIER        { $$ = new Attribute($2, tokens::STRING); free(const_cast<char*>($2)); }
    | M3F_AT IDENTIFIER      { $$ = new Attribute($2, tokens::MAT3F); free(const_cast<char*>($2)); }
    | M4F_AT IDENTIFIER      { $$ = new Attribute($2, tokens::MAT4F); free(const_cast<char*>($2)); }
    | AT IDENTIFIER          { $$ = new Attribute($2, tokens::FLOAT, true); free(const_cast<char*>($2)); }
;

/// @brief  Syntax for supported external variable access
external:
      type DOLLAR IDENTIFIER  { $$ = new ExternalVariable($3, static_cast<tokens::CoreType>($1)); free(const_cast<char*>($3)); }
    | I_DOLLAR IDENTIFIER     { $$ = new ExternalVariable($2, tokens::INT); free(const_cast<char*>($2)); }
    | F_DOLLAR IDENTIFIER     { $$ = new ExternalVariable($2, tokens::FLOAT); free(const_cast<char*>($2)); }
    | V_DOLLAR IDENTIFIER     { $$ = new ExternalVariable($2, tokens::VEC3F); free(const_cast<char*>($2)); }
    | S_DOLLAR IDENTIFIER     { $$ = new ExternalVariable($2, tokens::STRING); free(const_cast<char*>($2)); }
    | DOLLAR IDENTIFIER       { $$ = new ExternalVariable($2, tokens::FLOAT); free(const_cast<char*>($2)); }
;

/// @brief  Syntax for the declaration of supported local variable types
declare_local:
    type IDENTIFIER    { $$ = new DeclareLocal($2, static_cast<tokens::CoreType>($1)); free(const_cast<char*>($2)); }
;

/// @brief  Syntax for text identifiers which resolves to a local. Types have
///         have their own tokens which do not evaluate to a local variable
/// @note   Anything which uses an IDENTIFIER must free the returned char array
local:
    IDENTIFIER  { $$ = new Local($1); free(const_cast<char*>($1)); }
;

/// @brief  Syntax numerical and boolean literal values
/// @note   Anything which uses one of the below tokens must free the returned char
///         array (aside from TRUE and FALSE tokens)
literal:
      L_SHORT         { $$ = new Value<int16_t>($1); free(const_cast<char*>($1)); }
    | L_INT           { $$ = new Value<int32_t>($1); free(const_cast<char*>($1)); }
    | L_LONG          { $$ = new Value<int64_t>($1); free(const_cast<char*>($1)); }
    | L_FLOAT         { $$ = new Value<float>($1); free(const_cast<char*>($1)); }
    | L_DOUBLE        { $$ = new Value<double>($1); free(const_cast<char*>($1)); }
    | L_STRING        { $$ = new Value<std::string>($1); free(const_cast<char*>($1)); }
    | TRUE            { $$ = new Value<bool>(true); }
    | FALSE           { $$ = new Value<bool>(false); }
;

type:
      scalar_type   { $$ = $1; }
    | vector_type   { $$ = $1; }
    | matrix_type   { $$ = $1; }
    | STRING        { $$ = tokens::STRING; }
;

/// @brief  Matrix types
matrix_type:
      MAT3F   { $$ = tokens::MAT3F; }
    | MAT3D   { $$ = tokens::MAT3D; }
    | MAT4F   { $$ = tokens::MAT4F; }
    | MAT4D   { $$ = tokens::MAT4D; }
;

/// @brief  Scalar types
scalar_type:
      BOOL    { $$ = tokens::BOOL; }
    | SHORT   { $$ = tokens::SHORT; }
    | INT     { $$ = tokens::INT; }
    | LONG    { $$ = tokens::LONG; }
    | FLOAT   { $$ = tokens::FLOAT; }
    | DOUBLE  { $$ = tokens::DOUBLE; }
;

/// @brief  Vector types
vector_type:
      VEC2I   { $$ = tokens::VEC2I; }
    | VEC2F   { $$ = tokens::VEC2F; }
    | VEC2D   { $$ = tokens::VEC2D; }
    | VEC3I   { $$ = tokens::VEC3I; }
    | VEC3F   { $$ = tokens::VEC3F; }
    | VEC3D   { $$ = tokens::VEC3D; }
    | VEC4I   { $$ = tokens::VEC4I; }
    | VEC4F   { $$ = tokens::VEC4F; }
    | VEC4D   { $$ = tokens::VEC4D; }
;

%%

OPENVDB_NO_TYPE_CONVERSION_WARNING_END

// Copyright (c) 2015-2019 DNEG
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
