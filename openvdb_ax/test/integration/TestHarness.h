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

/// @file test/integration/TestHarness.h
///
/// @authors Francisco Gochez, Nick Avramoussis
///
/// @brief  Test harness and base methods

#ifndef OPENVDB_POINTS_UNITTEST_TEST_HARNESS_INCLUDED
#define OPENVDB_POINTS_UNITTEST_TEST_HARNESS_INCLUDED

#include "CompareGrids.h"

#include <openvdb_ax/ast/Tokens.h>
#include <openvdb_ax/compiler/Compiler.h>
#include <openvdb_ax/compiler/CustomData.h>

#include <openvdb/points/PointAttribute.h>
#include <openvdb/points/PointScatter.h>

#include <cppunit/TestCase.h>

#include <unordered_map>

extern int sGenerateAX;

namespace unittest_util
{

std::string loadText(const std::string& codeFileName);

void wrapExecution(openvdb::points::PointDataGrid& grid,
                   const std::string& codeFileName,
                   const std::string * const group = nullptr,
                   std::vector<std::string>* warnings = nullptr,
                   const openvdb::ax::CustomData::Ptr& data =
                       openvdb::ax::CustomData::create(),
                   const openvdb::ax::CompilerOptions& opts =
                       openvdb::ax::CompilerOptions(),
                   const bool createMissing = true);

void wrapExecution(openvdb::GridPtrVec& grids,
                   const std::string& codeFileName,
                   std::vector<std::string>* warnings = nullptr,
                   const openvdb::ax::CustomData::Ptr& data =
                       openvdb::ax::CustomData::create(),
                   const openvdb::ax::CompilerOptions& opts =
                       openvdb::ax::CompilerOptions(),
                   const bool createMissing = false);

/// @brief Structure for wrapping up most of the existing integration
///        tests with a simple interface
struct AXTestHarness
{
    AXTestHarness() :
        mInputPointGrids()
      , mOutputPointGrids()
      , mInputVolumeGrids()
      , mOutputVolumeGrids()
      , mUseVolumes(true)
      , mUsePoints(true)
      , mVolumeBounds({0,0,0},{0,0,0})
      , mOpts(openvdb::ax::CompilerOptions())
      , mCustomData(openvdb::ax::CustomData::create())
    {
        reset();
    }

    void addInputGroups(const std::vector<std::string>& names, const std::vector<bool>& defaults);
    void addExpectedGroups(const std::vector<std::string>& names, const std::vector<bool>& defaults);

    /// @brief adds attributes to input data set
    template <typename T>
    void addInputAttributes(const std::vector<std::string>& names,
                            const std::vector<T>& values)
    {
        if (mUsePoints)  addInputPtAttributes<T>(names, values);
        if (mUseVolumes) addInputVolumes(names, values);
    }


    template <typename T>
    void addInputAttribute(const std::string& name, const T& inputVal)
    {
        addInputAttributes<T>({name}, {inputVal});
    }

    /// @brief adds attributes to expected output data sets
    template <typename T>
    void addExpectedAttributes(const std::vector<std::string>& names,
                               const std::vector<T>& values)
    {
        if (mUsePoints)  addExpectedPtAttributes<T>(names, values);
        if (mUseVolumes) addExpectedVolumes<T>(names, values);
    }

    /// @brief adds attributes to both input and expected data
    template <typename T>
    void addAttributes(const std::vector<std::string>& names,
                       const std::vector<T>& inputValues,
                       const std::vector<T>& expectedValues)
    {
        if (inputValues.size() != expectedValues.size() ||
            inputValues.size() != names.size()) {
            throw std::runtime_error("bad unittest setup - input/expected value counts don't match");
        }
        addInputAttributes(names, inputValues);
        addExpectedAttributes(names, expectedValues);
    }

    /// @brief adds attributes to both input and expected data, with input data set to 0 values
    template <typename T>
    void addAttributes(const std::vector<std::string>& names,
                       const std::vector<T>& expectedValues)
    {
       std::vector<T> zeroVals(expectedValues.size(), openvdb::zeroVal<T>());
       addAttributes(names, zeroVals, expectedValues);
    }

    template <typename T>
    void addAttribute(const std::string& name, const T& inVal, const T& expVal)
    {
        addAttributes<T>({name}, {inVal}, {expVal});
    }

    template <typename T>
    void addAttribute(const std::string& name, const T& expVal)
    {
        addAttribute<T>(name, openvdb::zeroVal<T>(), expVal);
    }

    template <typename T>
    void addExpectedAttribute(const std::string& name, const T& expVal)
    {
        addExpectedAttributes<T>({name}, {expVal});
    }

    /// @brief excecutes a snippet of code contained in a file to the input data sets
    void executeCode(const std::string& codeFile,
                     const std::string * const group = nullptr,
                     std::vector<std::string>* warnings = nullptr,
                     const bool createMissing = false);

    /// @brief rebuilds the input and output data sets to their default harness states. This
    ///        sets the bounds of volumes to a single voxel, with a single and four point grid
    void reset();

    /// @brief reset the input data to a set amount of points per voxel within a given bounds
    /// @note  The bounds is also used to fill the volume data of numerical vdb volumes when
    ///        calls to addAttribute functions are made, where as points have their positions
    ///        generated here
    void reset(const openvdb::Index64, const openvdb::CoordBBox&);

    /// @brief reset all grids without changing the harness data. This has the effect of zeroing
    ///        out all volume voxel data and point data attributes (except for position) without
    ///        changing the number of points or voxels
    void resetInputsToZero();

    /// @brief compares the input and expected point grids and outputs a report of differences to
    /// the provided stream
    bool checkAgainstExpected(std::ostream& sstream);

    /// @brief Toggle whether to execute tests for points or volumes
    void testVolumes(const bool);
    void testPoints(const bool);

    template <typename T>
    void addInputPtAttributes(const std::vector<std::string>& names, const std::vector<T>& values);

    template <typename T>
    void addInputVolumes(const std::vector<std::string>& names, const std::vector<T>& values);

    template <typename T>
    void addExpectedPtAttributes(const std::vector<std::string>& names, const std::vector<T>& values);

    template <typename T>
    void addExpectedVolumes(const std::vector<std::string>& names, const std::vector<T>& values);

    std::vector<openvdb::points::PointDataGrid::Ptr> mInputPointGrids;
    std::vector<openvdb::points::PointDataGrid::Ptr> mOutputPointGrids;

    openvdb::GridPtrVec mInputVolumeGrids;
    openvdb::GridPtrVec mOutputVolumeGrids;

    bool mUseVolumes;
    bool mUsePoints;
    openvdb::CoordBBox mVolumeBounds;

    openvdb::ax::CompilerOptions mOpts;
    openvdb::ax::CustomData::Ptr mCustomData;

};

class AXTestCase : public CppUnit::TestCase
{
public:
    void tearDown() override
    {
        std::string out;
        for (auto& test : mTestFiles) {
            if (!test.second) out += test.first + "\n";
        }
        CPPUNIT_ASSERT_MESSAGE("unused tests left in test case:\n" + out,
            out.empty());
    }

    // @todo make pure
    virtual std::string dir() const { return ""; }

    /// @brief  Register an AX code snippet with this test. If the tests
    ///         have been launched with -g, the code is also serialized
    ///         into the test directory
    void registerTest(const std::string& code,
            const std::string& filename,
            const std::ios_base::openmode flags = std::ios_base::out)
    {
        if (flags & std::ios_base::out) {
            CPPUNIT_ASSERT_MESSAGE(
                "duplicate test file found during test setup:\n" + filename,
                mTestFiles.find(filename) == mTestFiles.end());
            mTestFiles[filename] = false;
        }
        if (flags & std::ios_base::app) {
            CPPUNIT_ASSERT_MESSAGE(
                "test not found during ofstream append:\n" + filename,
                mTestFiles.find(filename) != mTestFiles.end());
        }

        if (sGenerateAX) {
            std::ofstream outfile;
            outfile.open(this->dir() + "/" + filename, flags);
            outfile << code << std::endl;
            outfile.close();
        }
    }

    template <typename ...Args>
    void execute(const std::string& filename, Args&&... args)
    {
        CPPUNIT_ASSERT_MESSAGE(
            "test not found during execution:\n" + this->dir() + "/" + filename,
            mTestFiles.find(filename) != mTestFiles.end());
        mTestFiles[filename] = true; // has been used

          // execute
        mHarness.executeCode(this->dir() + "/" + filename, args...);

        // check
        std::stringstream out;
        const bool correct = mHarness.checkAgainstExpected(out);
        CPPUNIT_ASSERT_MESSAGE(out.str(), correct);
    }

protected:
    AXTestHarness mHarness;
    std::unordered_map<std::string, bool> mTestFiles;
};

} // namespace unittest_util


#define GET_TEST_DIRECTORY() \
        std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of('.')); \

#define AXTESTS_STANDARD_ASSERT_HARNESS(harness) \
    {   std::stringstream out; \
        const bool correct = harness.checkAgainstExpected(out); \
        CPPUNIT_ASSERT_MESSAGE(out.str(), correct); }

#define AXTESTS_STANDARD_ASSERT() \
      AXTESTS_STANDARD_ASSERT_HARNESS(mHarness);

#endif // OPENVDB_POINTS_UNITTEST_TEST_HARNESS_INCLUDED

// Copyright (c) 2015-2020 DNEG
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
