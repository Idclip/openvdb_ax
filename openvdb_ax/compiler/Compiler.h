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

/// @file compiler/Compiler.h
///
/// @authors Nick Avramoussis, Francisco Gochez, Richard Jones
///
/// @brief  The OpenVDB AX Compiler class provides methods to generate
///   AX executables from a provided AX AST (or directly from a given
///   string). The class object exists to cache various structures,
///   primarily LLVM constructs, which benefit from existing across
///   additional compilation runs.
///

#ifndef OPENVDB_AX_COMPILER_HAS_BEEN_INCLUDED
#define OPENVDB_AX_COMPILER_HAS_BEEN_INCLUDED

#include <openvdb_ax/ast/AST.h>
#include <openvdb_ax/compiler/CompilerOptions.h>
#include <openvdb_ax/compiler/CustomData.h>

#include <memory>

// forward
namespace llvm {
class LLVMContext;
}

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {

namespace ax {

namespace codegen {
// forward
class FunctionRegistry;
}

/// @brief  Initializes llvm. Must be called before any AX compilation or execution is performed.
void initialize();

/// @brief  Check to see if llvm has been initialized.
bool isInitialized();

/// @brief  Shuts down llvm. Must be called on application termination
void uninitialize();

/// @brief  The compiler class.  This holds an llvm context and set of compiler options, and constructs
///         executable objects (e.g. PointExecutable or VolumeExecutable) from a syntax tree or
///         snippet of code.
class Compiler
{
public:

    using Ptr = std::shared_ptr<Compiler>;
    using UniquePtr = std::unique_ptr<Compiler>;

    /// @brief Construct a compiler object with given settings
    /// @param options CompilerOptions object with various settings
    Compiler(const CompilerOptions& options = CompilerOptions());

    ~Compiler() = default;

    /// @brief Static method for creating Compiler objects
    static UniquePtr create(const CompilerOptions& options = CompilerOptions());

    /// @brief Compile/build a given AST into an executable object of the given type.
    /// @param syntaxTree An abstract syntax tree to compile
    /// @param data External/custom data which is to be referenced by the executable object. It
    ///        allows one to reference data held elsewhere, such as inside of a DCC, inside of the
    ///        executable
    /// @param compilerErrors A vector of strings where errors are inserted into
    template <typename ExecutableT>
    typename ExecutableT::Ptr
    compile(const ast::Tree& syntaxTree,
            const CustomData::Ptr data = CustomData::Ptr(),
            std::vector<std::string>* compilerErrors = nullptr);

    /// @brief Compile/build a given snippet of AX code into an executable object of the given type.
    /// @param code A string of AX code
    /// @param data External/custom data which is to be referenced by the executable object. It
    ///        allows one to reference data held elsewhere, such as inside of a DCC, from inside
    ///        the AX code
    /// @param compilerErrors A vector of strings where errors are inserted into
    template <typename ExecutableT>
    typename ExecutableT::Ptr
    compile(const std::string& code,
            const CustomData::Ptr data = CustomData::Ptr(),
            std::vector<std::string>* compilerErrors = nullptr)
    {
        ast::Tree::Ptr syntaxTree = ast::parse(code.c_str());
        return compile<ExecutableT>(*syntaxTree, data, compilerErrors);
    }

    /// @brief Sets the compiler's function registry object.
    /// @param functionRegistry A unique pointer to a FunctionRegistry object.  The compiler will
    ///        take ownership of the registry that was passed in.
    /// @todo  Perhaps allow one to register individual functions into this class rather than the entire
    ///        registry at once, and/or allow one to extract a pointer to the registry and update it
    ///        manually.
    void setFunctionRegistry(std::unique_ptr<codegen::FunctionRegistry>&& functionRegistry);

private:
    std::shared_ptr<llvm::LLVMContext> mContext;
    const CompilerOptions mCompilerOptions;
    std::shared_ptr<codegen::FunctionRegistry> mFunctionRegistry;
};


}
}
}

#endif // OPENVDB_AX_COMPILER_HAS_BEEN_INCLUDED

// Copyright (c) 2015-2020 DNEG
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
