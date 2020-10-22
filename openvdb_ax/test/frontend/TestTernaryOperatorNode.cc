///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2015-2020 DNEG
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

#include "../ast/AST.h"
#include "../ast/Scanners.h"
#include "../ast/PrintTree.h"
#include "../Exceptions.h"
#include "../test/util.h"

#include <cppunit/extensions/HelperMacros.h>

#include <string>

using namespace openvdb::ax::ast;
using namespace openvdb::ax::ast::tokens;

namespace {

static const unittest_util::CodeTests tests =
{
    { "true ? 1 : 0;",                                   Node::Ptr(new TernaryOperator(new Value<bool>(true), new Value<int32_t>(1), new Value<int32_t>(0)))},
    { "true ? a : 1.5f;",                                Node::Ptr(new TernaryOperator(new Value<bool>(true), new Local("a"), new Value<float>(1.5f)))},
    { "false ? true : false;",                           Node::Ptr(new TernaryOperator(new Value<bool>(false), new Value<bool>(true), new Value<bool>(false)))},
    { "a == b ? 1 : 0;",                                 Node::Ptr(new TernaryOperator(
                                                            new BinaryOperator(
                                                                new Local("a"),
                                                                new Local("b"),
                                                                OperatorToken::EQUALSEQUALS),
                                                            new Value<int32_t>(1),
                                                            new Value<int32_t>(0)))},
    { "a++ ? 1 : 0;",                                   Node::Ptr(new TernaryOperator(
                                                            new Crement(new Local("a"), Crement::Operation::Increment, true),
                                                            new Value<int32_t>(1),
                                                            new Value<int32_t>(0)))},
    { "@a ? 1 : 0;",                                    Node::Ptr(new TernaryOperator(new Attribute("a", CoreType::FLOAT, true), new Value<int32_t>(1), new Value<int32_t>(0)))},
    { "func() ? 1 : 0;",                                Node::Ptr(new TernaryOperator(new FunctionCall("func"), new Value<int32_t>(1), new Value<int32_t>(0)))},
    { "(true) ? 1 : 0;",                                Node::Ptr(new TernaryOperator(new Value<bool>(true), new Value<int32_t>(1), new Value<int32_t>(0)))},
    { "true ? 3 : 2 ? 1 : 0;",                          Node::Ptr(new TernaryOperator(
                                                            new Value<bool>(true),
                                                            new Value<int32_t>(3),
                                                            new TernaryOperator(new Value<int32_t>(2), new Value<int32_t>(1), new Value<int32_t>(0))))},
    { "(true ? 3 : 2) ? 1 : 0;",                        Node::Ptr(new TernaryOperator(
                                                            new TernaryOperator(new Value<bool>(true), new Value<int32_t>(3), new Value<int32_t>(2)),
                                                            new Value<int32_t>(1),
                                                            new Value<int32_t>(0)))},
    { "true ? \"foo\" : \"bar\";",                          Node::Ptr(new TernaryOperator(new Value<bool>(true), new Value<std::string>("foo"), new Value<std::string>("bar")))},
    { "true ? voidfunc1() : voidfunc2();",              Node::Ptr(new TernaryOperator(new Value<bool>(true), new FunctionCall("voidfunc1"), new FunctionCall("voidfunc2")))},
    { "true ? {1,1,1} : {0,0,0};",                      Node::Ptr(new TernaryOperator(
                                                            new Value<bool>(true),
                                                            new ArrayPack({
                                                                new Value<int32_t>(1),
                                                                new Value<int32_t>(1),
                                                                new Value<int32_t>(1)
                                                            })
                                                            ,
                                                            new ArrayPack({
                                                                new Value<int32_t>(0),
                                                                new Value<int32_t>(0),
                                                                new Value<int32_t>(0)
                                                            })
                                                            ))},
    { "true ? false ? 3 : 2 : 1;" ,                     Node::Ptr(new TernaryOperator(
                                                            new Value<bool>(true),
                                                            new TernaryOperator(
                                                                new Value<bool>(false),
                                                                new Value<int32_t>(3),
                                                                new Value<int32_t>(2)),
                                                            new Value<int32_t>(1)))},
    { "true ? false ? 3 : 2 : (true ? 4 : 5);" ,        Node::Ptr(new TernaryOperator(
                                                            new Value<bool>(true),
                                                            new TernaryOperator(
                                                                new Value<bool>(false),
                                                                new Value<int32_t>(3),
                                                                new Value<int32_t>(2)),
                                                            new TernaryOperator(
                                                                new Value<bool>(true),
                                                                new Value<int32_t>(4),
                                                                new Value<int32_t>(5))))},
    { "true ? : 0;",                                   Node::Ptr(new TernaryOperator(new Value<bool>(true), nullptr, new Value<int32_t>(0)))},
};

}

class TestTernaryOperatorNode : public CppUnit::TestCase
{
    public:

    CPPUNIT_TEST_SUITE(TestTernaryOperatorNode);
    CPPUNIT_TEST(testSyntax);
    CPPUNIT_TEST(testASTNode);
    CPPUNIT_TEST_SUITE_END();

    void testSyntax() { TEST_SYNTAX_PASSES(tests); }
    void testASTNode();
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestTernaryOperatorNode);

void TestTernaryOperatorNode::testASTNode()
{
    for (const auto& test : tests) {
        const std::string& code = test.first;
        const Node* expected = test.second.get();
        const Tree::ConstPtr tree = parse(code.c_str());
        CPPUNIT_ASSERT_MESSAGE(ERROR_MSG("No AST returned", code), static_cast<bool>(tree));

        // get the first statement
        const Node* result = tree->child(0)->child(0);
        CPPUNIT_ASSERT(result);
        CPPUNIT_ASSERT_MESSAGE(ERROR_MSG("Invalid AST node", code),
            Node::TernaryOperatorNode == result->nodetype());

        std::vector<const Node*> resultList, expectedList;
        linearize(*result, resultList);
        linearize(*expected, expectedList);

        if (!unittest_util::compareLinearTrees(expectedList, resultList)) {
            std::ostringstream os;
            os << "\nExpected:\n";
            openvdb::ax::ast::print(*expected, true, os);
            os << "Result:\n";
            openvdb::ax::ast::print(*result, true, os);
            CPPUNIT_FAIL(ERROR_MSG("Mismatching Trees for Ternary Operator code", code) + os.str());
        }
    }
}

// Copyright (c) 2015-2020 DNEG
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
