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

#include <cppunit/extensions/HelperMacros.h>

#include <openvdb_ax/compiler/Compiler.h>
#include <openvdb_ax/Exceptions.h>

#include <string>

#include "test/util.h"

namespace {

static const unittest_util::CodeTests tests =
{
    // invalid r-value syntax
    { "@a = @;",                       nullptr },
    { "@a = =;",                       nullptr },
    { "@a = +;",                       nullptr },
    { "@a = -;",                       nullptr },
    { "@a = *;",                       nullptr },
    { "@a = /;",                       nullptr },
    { "@a = %;",                       nullptr },
    { "@a = |;",                       nullptr },
    { "@a = &;",                       nullptr },
    { "@a = ^;",                       nullptr },
    { "@a = ~;",                       nullptr },
    { "@a = ==;",                      nullptr },
    { "@a = !=;",                      nullptr },
    { "@a = >;",                       nullptr },
    { "@a = <;",                       nullptr },
    { "@a = >=;",                      nullptr },
    { "@a = <=;",                      nullptr },
    { "@a = +=;",                      nullptr },
    { "@a = -=;",                      nullptr },
    { "@a = *=;",                      nullptr },
    { "@a = /=;",                      nullptr },
    { "@a = ++;",                      nullptr },
    { "@a = --;",                      nullptr },
    { "@a = &&;",                      nullptr },
    { "@a = ||;",                      nullptr },
    { "@a = !;",                       nullptr },
    { "@a = ,;",                       nullptr },
    { "@a = (;",                       nullptr },
    { "@a = );",                       nullptr },
    { "@a = {;",                       nullptr },
    { "@a =};",                        nullptr },
    { "@a = .x;",                      nullptr },
    { "@a = .y;",                      nullptr },
    { "@a = .z;",                      nullptr },
    { "@a = .r;",                      nullptr },
    { "@a = .g;",                      nullptr },
    { "@a = .b;",                      nullptr },
    { "@a = f@;",                      nullptr },
    { "@a = i@;",                      nullptr },
    { "@a = v@;",                      nullptr },
    { "@a = s@;",                      nullptr },
    { "@a = if;",                      nullptr },
    { "@a = else;",                    nullptr },
    { "@a = return;",                  nullptr },
    { "@a = ;",                        nullptr },
    { "@a = {};",                      nullptr },
    //{ "@a = {1};",                     nullptr },
    { "@a = \"a;",                     nullptr },
    { "v@a.a = 0;",                    nullptr },

    { "$a = $;",                       nullptr },
    { "$a = =;",                       nullptr },
    { "$a = +;",                       nullptr },
    { "$a = -;",                       nullptr },
    { "$a = *;",                       nullptr },
    { "$a = /;",                       nullptr },
    { "$a = %;",                       nullptr },
    { "$a = |;",                       nullptr },
    { "$a = &;",                       nullptr },
    { "$a = ^;",                       nullptr },
    { "$a = ~;",                       nullptr },
    { "$a = ==;",                      nullptr },
    { "$a = !=;",                      nullptr },
    { "$a = >;",                       nullptr },
    { "$a = <;",                       nullptr },
    { "$a = >=;",                      nullptr },
    { "$a = <=;",                      nullptr },
    { "$a = +=;",                      nullptr },
    { "$a = -=;",                      nullptr },
    { "$a = *=;",                      nullptr },
    { "$a = /=;",                      nullptr },
    { "$a = ++;",                      nullptr },
    { "$a = --;",                      nullptr },
    { "$a = &&;",                      nullptr },
    { "$a = ||;",                      nullptr },
    { "$a = !;",                       nullptr },
    { "$a = ,;",                       nullptr },
    { "$a = (;",                       nullptr },
    { "$a = );",                       nullptr },
    { "$a = {;",                       nullptr },
    { "$a =};",                        nullptr },
    { "$a = .x;",                      nullptr },
    { "$a = .y;",                      nullptr },
    { "$a = .z;",                      nullptr },
    { "$a = .r;",                      nullptr },
    { "$a = .g;",                      nullptr },
    { "$a = .b;",                      nullptr },
    { "$a = f$;",                      nullptr },
    { "$a = i$;",                      nullptr },
    { "$a = v$;",                      nullptr },
    { "$a = s$;",                      nullptr },
    { "$a = if;",                      nullptr },
    { "$a = else;",                    nullptr },
    { "$a = return;",                  nullptr },
    { "$a = ;",                        nullptr },
    { "$a = {};",                      nullptr },
    { "$a = {1};",                     nullptr },
    { "$a = \"a;",                     nullptr },
    { "v$a[0] = 0;",                   nullptr },
    { "v$a.a = 0;",                    nullptr },

    // @todo these should probably be valid syntax and the code
    // generators should handle assignments based on the current
    // r/lvalues
    { "5 = 5;",                        nullptr },
    { "$a = 5;",                       nullptr },

    // invalid l-value
    // TODO: these should fail syntax tests
    // {"+@a = 0;",                   nullptr },
    // {"-@a = 0;",                   nullptr },
    // {"~@a = 0;",                   nullptr },
    // {"!@a = 0;",                   nullptr },
    // { "++@a = 0;",                     nullptr },
    // { "--@a = 0;",                     nullptr },
    { "=@a;",                          nullptr },
    { "*@a;",                          nullptr },
    { "/@a;",                          nullptr },
    { "%@a;",                          nullptr },
    { "|@a;",                          nullptr },
    { "&@a;",                          nullptr },
    { "^@a;",                          nullptr },
    { "==@a;",                         nullptr },
    { "!=@a;",                         nullptr },
    { ">@a;",                          nullptr },
    { "<@a;",                          nullptr },
    { ">=@a;",                         nullptr },
    { "<=@a;",                         nullptr },
    { "+=@a;",                         nullptr },
    { "-=@a;",                         nullptr },
    { "*=@a;",                         nullptr },
    { "/=@a;",                         nullptr },
    { "&&@a;",                         nullptr },
    { "||@a;",                         nullptr },
    { ",@a;",                          nullptr },
    { "(@a;",                          nullptr },
    { ")@a;",                          nullptr },
    { "{@a;",                          nullptr },
    { "}@a;",                          nullptr },
    { ".x@a;",                         nullptr },
    { ".y@a;",                         nullptr },
    { ".z@a;",                         nullptr },
    { ".r@a;",                         nullptr },
    { ".g@a;",                         nullptr },
    { ".b@a;",                         nullptr },
    { "@@a;",                          nullptr },
    { "f@@a;",                         nullptr },
    { "i@@a;",                         nullptr },
    { "v@@a;",                         nullptr },
    { "s@@a;",                         nullptr },
    { "if@a;",                         nullptr },
    { "else@a;",                       nullptr },
    { "return@a;",                     nullptr },
    { "{}@a;",                         nullptr },
    { "{1}@a;",                        nullptr },
    { "\"a\"@a;",                      nullptr },
    { "b@a;",                          nullptr },
    { "sht@a;",                        nullptr },
    { "it@a;",                         nullptr },
    { "l@a;",                          nullptr },
    { "flt@a;",                        nullptr },
    { "dbl@a;",                        nullptr },
    { "vecint@a;",                     nullptr },
    { "vint@a;",                       nullptr },
    { "vfloat@a;",                     nullptr },
    { "vecflt@a;",                     nullptr },
    { "vflt@a;",                       nullptr },
    { "vdouble@a;",                    nullptr },
    { "vecdbl@a;",                     nullptr },
    { "vdbl@a;",                       nullptr },
    { "str@a;",                        nullptr },

    { "++$a = 0;",                     nullptr },
    { "--$a = 0;",                     nullptr },
    { "=$a;",                          nullptr },
    { "*$a;",                          nullptr },
    { "/$a;",                          nullptr },
    { "%$a;",                          nullptr },
    { "|$a;",                          nullptr },
    { "&$a;",                          nullptr },
    { "^$a;",                          nullptr },
    { "==$a;",                         nullptr },
    { "!=$a;",                         nullptr },
    { ">$a;",                          nullptr },
    { "<$a;",                          nullptr },
    { ">=$a;",                         nullptr },
    { "<=$a;",                         nullptr },
    { "+=$a;",                         nullptr },
    { "-=$a;",                         nullptr },
    { "*=$a;",                         nullptr },
    { "/=$a;",                         nullptr },
    { "&&$a;",                         nullptr },
    { "||$a;",                         nullptr },
    { ",$a;",                          nullptr },
    { "($a;",                          nullptr },
    { ")$a;",                          nullptr },
    { "{$a;",                          nullptr },
    { "}$a;",                          nullptr },
    { ".x$a;",                         nullptr },
    { ".y$a;",                         nullptr },
    { ".z$a;",                         nullptr },
    { ".r$a;",                         nullptr },
    { ".g$a;",                         nullptr },
    { ".b$a;",                         nullptr },
    { "$$a;",                          nullptr },
    { "f$$a;",                         nullptr },
    { "i$$a;",                         nullptr },
    { "v$$a;",                         nullptr },
    { "s$$a;",                         nullptr },
    { "if$a;",                         nullptr },
    { "else$a;",                       nullptr },
    { "return$a;",                     nullptr },
    { "{}$a;",                         nullptr },
    { "{1}$a;",                        nullptr },
    { "\"a\"$a;",                      nullptr },
    { "b$a;",                          nullptr },
    { "sht$a;",                        nullptr },
    { "it$a;",                         nullptr },
    { "l$a;",                          nullptr },
    { "flt$a;",                        nullptr },
    { "dbl$a;",                        nullptr },
    { "vecint$a;",                     nullptr },
    { "vint$a;",                       nullptr },
    { "vfloat$a;",                     nullptr },
    { "vecflt$a;",                     nullptr },
    { "vflt$a;",                       nullptr },
    { "vdouble$a;",                    nullptr },
    { "vecdbl$a;",                     nullptr },
    { "vdbl$a;",                       nullptr },
    { "str$a;",                        nullptr },

    { "a ! a;",                        nullptr },
    { "a ~ a;",                        nullptr },
    { "a \\ a;",                       nullptr },
    { "a ? a;",                        nullptr },
    { "bool + a;",                     nullptr },
    { "bool a + a;",                   nullptr },
    { "return + a;",                   nullptr },
    { "if + a;",                       nullptr },
    { "a + if(true) {};",              nullptr },
    { "{} + {};",                      nullptr },
    { "~ + !;",                        nullptr },
    { "+ + -;",                        nullptr },
    { "; + ;",                         nullptr },
    { "int();",                        nullptr },
    { "int(return);",                  nullptr },
    { "int(if(true) {});",             nullptr },
    { "int(;);",                       nullptr },
    { "int(bool a;);",                 nullptr },
    { "int(bool a);",                  nullptr },
    { "int{a};",                       nullptr },
    { "int[a];",                       nullptr },
    { "string(a);",                    nullptr },
    { "vector(a);",                    nullptr },
    { "vec3i(a);",                     nullptr },
    { "vec3f(a);",                     nullptr },
    { "vec3d(a);",                     nullptr },

    // invalid if block
    { "if (a) {b}",                    nullptr },
    { "if (a) else ();",               nullptr },
    { "if (); else (a);",              nullptr },
    { "if (a) if(b) {if (c)} else {}", nullptr },
    { "if (if(a));",                   nullptr },
    { "if ();",                        nullptr },
    { "if (); else ;",                 nullptr },
    { "if (); else ();",               nullptr },
    { "if (); else () {}",             nullptr },
    { "if (); elf {}",                 nullptr },
    { "if (a) {} elif (b) {}",         nullptr },
    { "else {}",                       nullptr },
    { "else ;",                        nullptr },
    { "if a;",                         nullptr },
    { "if a {} elif b {}",             nullptr },
    { "if (a); else ; else ;",         nullptr },
    { "else (a); ",                    nullptr },
    { "if (a) {}; else {};",           nullptr },
    { "if (a) {b = 1} else {};",       nullptr },
    { "if (a) {} ; else {}",           nullptr },
    { "if () {}; else (a);",           nullptr },

    // invalid crement
    { "++5;",                          nullptr },
    { "5++;",                          nullptr },
    { "--5;",                          nullptr },
    { "5--;",                          nullptr },
    { "++5--;",                        nullptr },
    { "++5++;",                        nullptr },
    { "--5++;",                        nullptr },
    { "--5--;",                        nullptr },
    { "{ 1, 1, 1}++;",                 nullptr },
    { "++{ 1, 1, 1};",                 nullptr },
    { "--{ 1, 1, 1};",                 nullptr },
    { "{ 1, 1, 1}--;",                 nullptr },
    { "++{ 1, 1, 1}++;",               nullptr },
    { "++{ 1, 1, 1}--;",               nullptr },
    { "--{ 1, 1, 1}--;",               nullptr },
    { "++{ 1, 1, 1}--;",               nullptr },
    { "++a-;",                         nullptr },
    //{ "++a--;",                        nullptr },
    //{ "++a++;",                        nullptr },
    //{ "--a++;",                        nullptr },
    //{ "--a--;",                        nullptr },
    //{ "----a;",                        nullptr },
    //{ "++++a;",                        nullptr },
    //{ "a.x--;",                        nullptr },
    //{ "-a.y--;",                       nullptr },
    //{ "++a.z;",                        nullptr },
    //{ "++@a--;",                       nullptr },
    //{ "@a.x--;",                       nullptr },
    //{ "-@a.y--;",                      nullptr },
    //{ "++@a.z;",                       nullptr },
    { "++$a--;",                       nullptr },
    { "$a.x--;",                       nullptr },
    { "-$a.y--;",                      nullptr },
    { "++$a.z;",                       nullptr },
    { "--f();",                        nullptr },
    { "f()++;",                        nullptr },
    { "return++;",                     nullptr },
    { "--return;",                     nullptr },
    { "true++;",                       nullptr },
    { "--false;",                      nullptr },
    { "--if;",                         nullptr },
    { "if++;",                         nullptr },
    { "else++;",                       nullptr },
    { "--else;",                       nullptr },
    { "--bool;",                       nullptr },
    { "short++;",                      nullptr },
    { "--int;",                        nullptr },
    { "long++;",                       nullptr },
    { "--float;",                      nullptr },
    { "++double;",                     nullptr },
    { "--vector;",                     nullptr },
    { "matrix--;",                     nullptr },
    { "--();",                         nullptr },
    { "()++;",                         nullptr },
    { "{}++;",                         nullptr },
    { "--{};",                         nullptr },
    { "--,;",                          nullptr },
    { ",--;",                          nullptr },

    // invalid declare
    { "int;",                          nullptr },
    { "int 1;",                        nullptr },
    { "string int;",                   nullptr },
    { "int bool a;",                   nullptr },
    { "int a",                         nullptr },
    { "vector a",                      nullptr },
    { "vector float a",                nullptr },

    // invalid function
    { "function(;",                    nullptr },
    { "function);",                    nullptr },
    { "return();",                     nullptr },
    { "function(bool);",               nullptr },
    { "function(bool a);",             nullptr },
    { "function(+);",                  nullptr },
    { "function(!);",                  nullptr },
    { "function(~);",                  nullptr },
    { "function(-);",                  nullptr },
    { "function(&&);",                 nullptr },
    { "function({});",                 nullptr },
    { "function{};" ,                  nullptr },
    { "function(if(true) {});",        nullptr },
    { "function(return);",             nullptr },
    { "function(return;);",            nullptr },
    { "\"function\"();" ,              nullptr },
    { "();",                           nullptr },
    { "@a();",                         nullptr },
    { "$a();",                         nullptr },
    { "+();",                          nullptr },
    { "10();",                         nullptr },

    // invalid keyword return
    { "return return;",                nullptr },
    { "return",                        nullptr },
    { "int return;",                   nullptr },
    { "return return;",                nullptr },
    { "return max(1, 2);",             nullptr },
    { "return 1 + a;",                 nullptr },
    { "return !a;",                    nullptr },
    { "return a = 1;",                 nullptr },
    { "return a.x = 1;",               nullptr },
    { "return ++a;",                   nullptr },
    { "return int(a);",                nullptr },
    { "return {1, 2, 3};",             nullptr },
    { "return a[1];",                  nullptr },
    { "return true;",                  nullptr },
    { "return 0;",                     nullptr },
    { "return (1);",                   nullptr },
    { "return \"a\";",                 nullptr },
    { "return int a;",                 nullptr },
    { "return a;",                     nullptr },
    { "return @a;",                    nullptr },

    // invalid unary
    { "+bool;" ,                       nullptr },
    { "+bool a;" ,                     nullptr },
    { "bool -a;" ,                     nullptr },
    { "-return;" ,                     nullptr },
    { "!return;" ,                     nullptr },
    { "+return;" ,                     nullptr },
    { "~return;" ,                     nullptr },
    { "~if(a) {};" ,                   nullptr },
    { "if(a) -{};" ,                   nullptr },
    { "if(a) {} !else {};",            nullptr },
    { "~;",                            nullptr },
    { "!;",                            nullptr },
    { "+;",                            nullptr },
    { "-;",                            nullptr },
    // @todo  unary crementation expressions should be parsable but perhaps
    //        not compilable
    { "---a;" ,                        nullptr },
    { "+++a;" ,                        nullptr },

    // invalid value
    { ".0.0;",                         nullptr },
    { ".0.0f;",                        nullptr },
    { ".f;",                           nullptr },
    { "0..0;",                         nullptr },
    { "0.0l;",                         nullptr },
    { "0.0ls;",                        nullptr },
    { "0.0s;",                         nullptr },
    { "0.0sf;",                        nullptr },
    { "0.a",                           nullptr },
    { "0.af",                          nullptr },
    { "00ls;",                         nullptr },
    { "0ef;",                          nullptr },
    { "0f0;",                          nullptr },
    { "1.0f.0;",                       nullptr },
    { "1.\"1\";",                      nullptr },
    { "1.e6f;",                        nullptr },
    { "10000000.00000001s;",           nullptr },
    { "1e.6f;",                        nullptr },
    { "1Ee6;",                         nullptr },
    { "1ee6;",                         nullptr },
    { "1eE6f;",                        nullptr },
    { "1ee6f;",                        nullptr },
    { "1l.0;",                         nullptr },
    { "1s.0;",                         nullptr },
    { "\"1.\"2;",                      nullptr },
    { "a.0",                           nullptr },
    { "a.0f",                          nullptr },
    { "false.0;",                      nullptr },
    { "true.;",                        nullptr },

    // invalid vector
    { "(1,2,3);",                      nullptr },
    { "{1,2,3];",                      nullptr },
    { "[1,2,3};",                      nullptr },
    { "{,,};",                         nullptr },
    { "{,2,3};",                       nullptr },

    // invalid vector unpack
    { "5.x;",                          nullptr },
    { "foo.2;",                        nullptr },
    { "a.w;",                          nullptr },
    { "a.X;",                          nullptr },
    { "a.Y;",                          nullptr },
    { "a.Z;",                          nullptr },
    { "@a.X;",                         nullptr },
    { "@a.Y;",                         nullptr },
    { "@a.Z;",                         nullptr },
    { "$a.X;",                         nullptr },
    { "$a.Y;",                         nullptr },
    { "$a.Z;",                         nullptr },
    { "a.xx;",                         nullptr },
    { "a++.x",                         nullptr },
    { "++a.x",                         nullptr },
    { "func().x",                      nullptr },
    { "int(y).x",                      nullptr },
    { "vector foo.x",                  nullptr },
    { "(a + b).x",                     nullptr },
    { "(a).x;",                        nullptr },
    { "(@a).x;",                       nullptr },
    { "@.x;",                          nullptr },
    { "($a).x;",                       nullptr },
    { "$.x;",                          nullptr },
    { "true.x;",                       nullptr },
    { "a.rx;",                         nullptr },
    { "a.rgb;",                        nullptr },
};

}

class TestSyntaxFailures : public CppUnit::TestCase
{
public:

    CPPUNIT_TEST_SUITE(TestSyntaxFailures);
    CPPUNIT_TEST(testSyntax);
    CPPUNIT_TEST_SUITE_END();

    void testSyntax() { TEST_SYNTAX_FAILS(tests); }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestSyntaxFailures);
// Copyright (c) 2015-2019 DNEG
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
