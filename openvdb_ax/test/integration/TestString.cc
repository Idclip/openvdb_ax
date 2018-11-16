///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2015-2018 DNEG Visual Effects
//
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
//
// Redistributions of source code must retain the above copyright
// and license notice and the following restrictions and disclaimer.
//
// *     Neither the name of DNEG Visual Effects nor the names
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

#include "TestHarness.h"

#include <openvdb_ax/test/util.h>

#include <cppunit/extensions/HelperMacros.h>

using namespace openvdb::points;

class TestString : public unittest_util::AXTestCase
{
public:
    void setUp() override;

    CPPUNIT_TEST_SUITE(TestString);
    CPPUNIT_TEST(testDeclare);
    CPPUNIT_TEST(testAssignFromLocals);
    CPPUNIT_TEST(testAssignFromAttributes);
    CPPUNIT_TEST(testBinaryConcat);
    CPPUNIT_TEST(testAssignNewOverwrite);
    CPPUNIT_TEST_SUITE_END();

    void testDeclare();
    void testAssignFromLocals();
    void testAssignFromAttributes();
    void testBinaryConcat();
    void testAssignNewOverwrite();
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestString);

// we override this since none of these tests should be run on volumes, so it's easier to enforce
// this in one place
void TestString::setUp()
{
    unittest_util::AXTestCase::setUp();
    mHarness.testVolumes(false);
}

void
TestString::testDeclare()
{
    mHarness.addAttribute<std::string>("string_test", "test");
    mHarness.executeCode("test/snippets/string/declare");

    AXTESTS_STANDARD_ASSERT();
}

void
TestString::testAssignFromLocals()
{
    mHarness.addAttributes<std::string>(unittest_util::nameSequence("string_test", 4),
        {"test", "test", "new string size", ""});
    mHarness.executeCode("test/snippets/string/assignFromLocals");

    AXTESTS_STANDARD_ASSERT();
}

void
TestString::testAssignFromAttributes()
{
    mHarness.addInputAttributes<std::string>({"string_test1"}, {"test"});
    mHarness.addExpectedAttributes<std::string>(unittest_util::nameSequence("string_test", 6),
        {"new value", "test", "new value", "new value", "", ""});
    mHarness.executeCode("test/snippets/string/assignFromAttributes");

    AXTESTS_STANDARD_ASSERT();
}

void
TestString::testBinaryConcat()
{
    mHarness.addExpectedAttributes<std::string>(unittest_util::nameSequence("string_test", 6),
        {"test new value", "test new value", "test new value", "test new value", "", "test new value"});
    mHarness.executeCode("test/snippets/string/binaryConcat");

    AXTESTS_STANDARD_ASSERT();
}

void
TestString::testAssignNewOverwrite()
{
    mHarness.addExpectedAttributes<std::string>({"string_test1", "string_test2"},
        {"next_value", "new_value"});
    mHarness.executeCode("test/snippets/string/assignNewOverwrite");

    AXTESTS_STANDARD_ASSERT();
}

// Copyright (c) 2015-2018 DNEG Visual Effects
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
