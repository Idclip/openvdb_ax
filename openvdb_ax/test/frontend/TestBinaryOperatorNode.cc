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

#include <openvdb_ax/ast/AST.h>
#include <openvdb_ax/ast/Scanners.h>
#include <openvdb_ax/ast/PrintTree.h>
#include <openvdb_ax/Exceptions.h>
#include <openvdb_ax/test/util.h>

#include <cppunit/extensions/HelperMacros.h>

#include <string>

using namespace openvdb::ax::ast;
using namespace openvdb::ax::ast::tokens;

namespace {

static const unittest_util::CodeTests tests =
{
    { "a + b;",                 Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::PLUS,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a - b;",                 Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::MINUS,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a * b;",                 Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::MULTIPLY,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a / b;",                 Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::DIVIDE,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a % b;",                 Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::MODULO,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a & b;",                 Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::BITAND,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a | b;",                 Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::BITOR,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a ^ b;",                 Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::BITXOR,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a && b;",                Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::AND,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a || b;",                Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::OR,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a == b;",                Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::EQUALSEQUALS,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a != b;",                Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::NOTEQUALS,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a > b;",                 Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::MORETHAN,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a < b;",                 Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::LESSTHAN,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a >= b;",                Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::MORETHANOREQUAL,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "a <= b;",                Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::LESSTHANOREQUAL,
                                        new Local("a"),
                                        new Local("b")
                                    )
                                )
    },
    { "(a) + (a);",             Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::PLUS,
                                        new Local("a"),
                                        new Local("a")
                                    )
                                )
    },
    { "func1() + func2();",      Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::PLUS,
                                        new FunctionCall("func1"),
                                        new FunctionCall("func2")
                                    )
                                )
    },
    { "a + b - c;",             Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::MINUS,
                                        new BinaryOperator(
                                            OperatorToken::PLUS,
                                            new Local("a"),
                                            new Local("b")
                                        ),
                                        new Local("c")
                                    )
                                )
    },
    { "~a + !b;",               Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::PLUS,
                                        new UnaryOperator(OperatorToken::BITNOT, new Local("a")),
                                        new UnaryOperator(OperatorToken::NOT, new Local("a"))
                                    )
                                )
    },
    { "++a - --b;",             Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::MINUS,
                                        new Crement(new Local("a"), Crement::Operation::Increment, false),
                                        new Crement(new Local("b"), Crement::Operation::Decrement, false)
                                    )
                                )
    },
    { "a-- + b++;",             Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::PLUS,
                                        new Crement(new Local("a"), Crement::Operation::Decrement, true),
                                        new Crement(new Local("b"), Crement::Operation::Increment, true)
                                    )
                                )
    },
    { "int(a) + float(b);",     Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::PLUS,
                                        new Cast(new Local("a"), CoreType::INT),
                                        new Cast(new Local("b"), CoreType::FLOAT)
                                    )
                                )
    },
    { "{a,b,c} + {d,e,f};",     Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::PLUS,
                                        new ArrayPack(new ExpressionList({
                                            new Local("a"),
                                            new Local("b"),
                                            new Local("c")
                                        })),
                                        new ArrayPack(new ExpressionList({
                                            new Local("d"),
                                            new Local("e"),
                                            new Local("f")
                                        }))
                                    )
                                )
    },
    { "a.x + b.y;",             Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::PLUS,
                                        new ArrayUnpack(new Local("a"), new Value<int32_t>(0)),
                                        new ArrayUnpack(new Local("b"), new Value<int32_t>(1))
                                    )
                                )
    },
    { "0 + 1s;",                Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::PLUS,
                                        new Value<int32_t>(0),
                                        new Value<int16_t>(1)
                                    )
                                )
    },
    { "0.0f + 1.0;",            Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::PLUS,
                                        new Value<float>(0.0),
                                        new Value<double>(1.0)
                                    )
                                )
    },
    { "@a + @b;",               Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::PLUS,
                                        new Attribute("a", CoreType::FLOAT, true),
                                        new Attribute("b", CoreType::FLOAT, true)
                                    )
                                )
    },
    { "\"a\" + \"b\";",         Node::Ptr(
                                    new BinaryOperator(
                                        OperatorToken::PLUS,
                                        new Value<std::string>("a"),
                                        new Value<std::string>("b")
                                    )
                                )
    },
};

}

class TestBinaryOperatorNode : public CppUnit::TestCase
{
public:

    CPPUNIT_TEST_SUITE(TestBinaryOperatorNode);
    CPPUNIT_TEST(testSyntax);
    CPPUNIT_TEST(testASTNode);
    CPPUNIT_TEST_SUITE_END();

    void testSyntax() { TEST_SYNTAX_PASSES(tests); }
    void testASTNode();
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestBinaryOperatorNode);

void TestBinaryOperatorNode::testASTNode()
{
    for (const auto& test : tests) {
        const std::string& code = test.first;
        const Node* expected = test.second.get();
        const Tree::Ptr tree = parse(code.c_str());
        CPPUNIT_ASSERT_MESSAGE(ERROR_MSG("No AST returned", code), static_cast<bool>(tree));

        // get the first statement
        const Node* result = tree->child(0)->child(0);
        CPPUNIT_ASSERT(result);
        CPPUNIT_ASSERT_MESSAGE(ERROR_MSG("Invalid AST node", code),
            Node::BinaryOperatorNode == result->nodetype());

        std::vector<const Node*> resultList, expectedList;
        linearize(*result, resultList);
        linearize(*expected, expectedList);

        if (!unittest_util::compareLinearTrees(expectedList, resultList)) {
            std::ostringstream os;
            os << "\nExpected:\n";
            openvdb::ax::ast::print(*expected, true, os);
            os << "Result:\n";
            openvdb::ax::ast::print(*result, true, os);
            CPPUNIT_FAIL(ERROR_MSG("Mismatching Trees for Binary Operator code", code) + os.str());
        }
    }
}

// Copyright (c) 2015-2019 DNEG
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
