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
// *     Neither the name of DNEG nor the names of
// its contributors may be used to endorse or promote products derived
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

///
/// @authors Nick Avramoussis
///
/// @brief  Utility methods for OpenVDB AX in Houdini,
///         contains VEX and channel expression conversion methods.
///
///

#ifndef OPENVDB_AX_HOUDINI_AX_UTILS_HAS_BEEN_INCLUDED
#define OPENVDB_AX_HOUDINI_AX_UTILS_HAS_BEEN_INCLUDED

#include <openvdb_ax/ast/AST.h>
#include <openvdb_ax/ast/Visitor.h>
#include <openvdb_ax/ast/Scanners.h>
#include <openvdb_ax/codegen/FunctionTypes.h>
#include <openvdb_ax/codegen/Functions.h>
#include <openvdb_ax/codegen/Utils.h>
#include <openvdb_ax/compiler/Compiler.h>
#include <openvdb_ax/compiler/CustomData.h>
#include <openvdb_ax/compiler/CompilerOptions.h>

#include <openvdb/Types.h>
#include <openvdb/Metadata.h>
#include <openvdb/Exceptions.h>
#include <openvdb/openvdb.h>

#include <map>
#include <set>
#include <utility>
#include <string>

namespace openvdb_ax_houdini
{

enum class TargetType
{
    POINTS,
    VOLUMES,
    LOCAL
};

using ChannelExpressionPair = std::pair<std::string, std::string>;
using ChannelExpressionSet = std::set<ChannelExpressionPair>;

/// @brief  Find any Houdini channel expressions represented inside the
///         provided Syntax Tree.
///
/// @param  tree              The AST to parse
/// @param  exprSet           The expression set to populate
inline void findChannelExpressions(const openvdb::ax::ast::Tree& tree,
                            ChannelExpressionSet& exprSet);

/// @brief  Find any Houdini $ expressions represented inside the
///         provided Syntax Tree.
///
/// @param  tree              The AST to parse
/// @param  exprSet           The expression set to populate
inline void findDollarExpressions(const openvdb::ax::ast::Tree& tree,
                            ChannelExpressionSet& exprSet);

/// @brief  Converts a Syntax Tree which contains possible representations of
///         Houdini VEX instructions to internally supported instructions
///
/// @param  tree        The AST to convert
/// @param  targetType  The type of primitive being compiled (this can potentially
///                     alter the generated instructions)
inline void convertASTFromVEX(openvdb::ax::ast::Tree& tree,
                       const TargetType targetType);

/// @brief  Converts lookup functions within a Syntax Tree to ExternalVariable nodes
///         if the argument is a string literal. This method is much faster than using
///         the lookup functions but uses $ AX syntax which isn't typical of a Houdini
///         session.
///
/// @param  tree        The AST to convert
/// @param  targetType  The type of primitive being compiled (this can potentially
///                     alter the generated instructions)
inline void convertASTKnownLookups(openvdb::ax::ast::Tree& tree);

/// @brief  Register custom Houdini functions, making them available to the
///         core compiler. These functions generally have specific Houdini only
///         functionality.
/// @param  reg   The function registry to add register the new functions into
/// @param  options The function options
inline void registerCustomHoudiniFunctions(openvdb::ax::codegen::FunctionRegistry& reg,
                                        const openvdb::ax::FunctionOptions& options);


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

/// @brief AST scanner to find channel expressions and them to the expression set
struct FindChannelExpressions :
    public openvdb::ax::ast::Visitor<FindChannelExpressions>
{
    using openvdb::ax::ast::Visitor<FindChannelExpressions>::traverse;
    using openvdb::ax::ast::Visitor<FindChannelExpressions>::visit;

    FindChannelExpressions(ChannelExpressionSet& expressions)
        : mExpressions(expressions) {}
    ~FindChannelExpressions() = default;

    static const std::string*
    getChannelPath(const openvdb::ax::ast::ExpressionList* args)
    {
        assert(args);
        if (args->empty()) return nullptr; // avoid dync if nullptr
        const openvdb::ax::ast::Value<std::string>* const path =
            dynamic_cast<const openvdb::ax::ast::Value<std::string>*>(args->child(0));
        if (!path) return nullptr;
        return &(path->value());
    }

    /// @brief  Add channel expression function calls
    /// @param  node The FunctionCall AST node being visited
    bool visit(const openvdb::ax::ast::FunctionCall* node)
    {
        std::string type;

        if (node->name() == "lookupf" ||
            node->name() == "ch") {
            type = openvdb::typeNameAsString<float>();
        }
        else if (node->name() == "lookupvec3f" ||
                 node->name() == "chv") {
            type = openvdb::typeNameAsString<openvdb::Vec3f>();
        }
        else if (node->name() == "chramp") {
            type = "ramp";
        }

        if (type.empty()) return true;

        // Get channel arguments. If there are incorrect arguments, defer to
        // the compiler code generation function error system to report proper
        // errors later

        const openvdb::ax::ast::ExpressionList* args = node->args();;
        const std::string* path = getChannelPath(args);
        if (!path) return true;

        mExpressions.emplace(type, *path);
        return true;
    }

private:
    ChannelExpressionSet& mExpressions;
};

inline void findChannelExpressions(const openvdb::ax::ast::Tree& tree,
                                   ChannelExpressionSet& exprSet)
{
    FindChannelExpressions op(exprSet);
    op.traverse(&tree);
}


///////////////////////////////////////////////////////////////////////////


inline void findDollarExpressions(const openvdb::ax::ast::Tree& tree,
                                  ChannelExpressionSet& exprSet)
{
    openvdb::ax::ast::visitNodeType<openvdb::ax::ast::ExternalVariable>(tree,
        [&](const openvdb::ax::ast::ExternalVariable& node) -> bool {
            exprSet.emplace(node.typestr(), node.name());
            return true;
        });
}


///////////////////////////////////////////////////////////////////////////

/// @brief AST modifier to convert VEX-like syntax from Houdini to AX.
///        Finds scalar and vector channel expressions and replace with AX custom
///        data lookups. Replaces volume intrinsics @P, @ix, @iy, @iz with AX function
///        calls. In the future this may be used to translate VEX syntax to an AX AST
///        and back to text for in application conversion to AX syntax.
struct ConvertFromVEX :
    public openvdb::ax::ast::Visitor<ConvertFromVEX, false>
{
    using openvdb::ax::ast::Visitor<ConvertFromVEX, false>::traverse;
    using openvdb::ax::ast::Visitor<ConvertFromVEX, false>::visit;

    ConvertFromVEX(const TargetType targetType,
        const std::vector<const openvdb::ax::ast::Variable*>& write)
        : mTargetType(targetType)
        , mWrite(write) {}
    ~ConvertFromVEX() = default;

    /// @brief  Convert channel function calls to internally supported functions
    /// @param  node  The FunctionCall AST node being visited
    bool visit(openvdb::ax::ast::FunctionCall* node)
    {
        std::string identifier;
        if (node->name() == "ch")       identifier = "lookupf";
        else if (node->name() == "chv") identifier = "lookupvec3f";
        else return true;

        openvdb::ax::ast::ExpressionList::UniquePtr args(node->args()->copy());
        openvdb::ax::ast::FunctionCall::UniquePtr
            replacement(new openvdb::ax::ast::FunctionCall(identifier, args.release()));

        if (!node->replace(replacement.get())) {
            throw std::runtime_error("Unable to convert AX snippet to VEX. Function \"" +
                node->name() + "\" produced errors.");
        }
        replacement.release();
        return true;
    }

    /// @brief  Convert Houdini instrinsic volume attribute read accesses
    /// @param  node  The AttributeValue AST node being visited
    bool visit(openvdb::ax::ast::Attribute* node)
    {
        if (mTargetType != TargetType::VOLUMES) return true;

        if (node->name() != "P"  && node->name() != "ix" &&
            node->name() != "iy" && node->name() != "iz") {
            return true;
        }

        if (std::find(mWrite.cbegin(), mWrite.cend(), node) != mWrite.cend()) {
            throw std::runtime_error("Unable to write to a volume name \"@" +
                node->name() + "\". This is a keyword identifier");
        }

        openvdb::ax::ast::FunctionCall::UniquePtr replacement;
        if (node->name() == "P") {
            replacement.reset(new openvdb::ax::ast::FunctionCall("getvoxelpws"));
        }
        else if (node->name() == "ix") {
            replacement.reset(new openvdb::ax::ast::FunctionCall("getcoordx"));
        }
        else if (node->name() == "iy") {
            replacement.reset(new openvdb::ax::ast::FunctionCall("getcoordy"));
        }
        else if (node->name() == "iz") {
            replacement.reset(new openvdb::ax::ast::FunctionCall("getcoordz"));
        }

        if (!node->replace(replacement.get())) {
            throw std::runtime_error("Unable to convert AX snippet to VEX. Attribute \"" +
                node->name() + "\" produced errors.");
        }
        replacement.release();
        return true;
    }

private:
    const TargetType mTargetType;
    const std::vector<const openvdb::ax::ast::Variable*>& mWrite;
};

inline void convertASTFromVEX(openvdb::ax::ast::Tree& tree,
                       const TargetType targetType)
{
    std::vector<const openvdb::ax::ast::Variable*> write;
    openvdb::ax::ast::catalogueVariables(tree, nullptr, &write, &write,
        /*locals*/false, /*attributes*/true);
    ConvertFromVEX converter(targetType, write);
    converter.traverse(&tree);
}


///////////////////////////////////////////////////////////////////////////

/// @brief  Convert any lookup or channel functions to ExternalVariable nodes
///         if the path is a string literal
struct ConvertKnownLookups :
    public openvdb::ax::ast::Visitor<ConvertKnownLookups, false>
{
    using openvdb::ax::ast::Visitor<ConvertKnownLookups, false>::traverse;
    using openvdb::ax::ast::Visitor<ConvertKnownLookups, false>::visit;

    ConvertKnownLookups() = default;
    ~ConvertKnownLookups() = default;

    /// @brief  Performs the function call to external variable conversion
    /// @param  node  The FunctionCall AST node being visited
    bool visit(openvdb::ax::ast::FunctionCall* node)
    {
        const bool isFloatLookup(node->name() == "lookupf");
        const bool isVec3fLookup(node->name() == "lookupvec3f");
        if (!isFloatLookup && !isVec3fLookup) return true;

        const std::string* path =
            FindChannelExpressions::getChannelPath(node->args());

        // If for any reason we couldn't validate or get the channel path from the
        // first argument, fall back to the internal lookup functions. These will
        // error with the expected function argument style results on invalid arguments
        // and, correctly support string attribute arguments provided by s@attribute
        // (although are much slower)

        if (path) {
            std::string type;
            if (isFloatLookup) type = openvdb::typeNameAsString<float>();
            else type = openvdb::typeNameAsString<openvdb::Vec3f>();

            openvdb::ax::ast::ExternalVariable::UniquePtr replacement;
            replacement.reset(new openvdb::ax::ast::ExternalVariable(*path, type));
            node->replace(replacement.get());
            replacement.release();
        }

        return true;
    }
};

inline void convertASTKnownLookups(openvdb::ax::ast::Tree& tree)
{
    ConvertKnownLookups converter;
    converter.traverse(&tree);
}


///////////////////////////////////////////////////////////////////////////

/// @brief  Custom derived metadata for ramp channel expressions to be used
///         with codegen::ax::CustomData
template <typename ValueType>
struct RampDataCache : public openvdb::Metadata
{
public:
    using RampType = std::map<float, ValueType>;
    using Ptr = openvdb::SharedPtr<RampDataCache<ValueType>>;
    using ConstPtr = openvdb::SharedPtr<const RampDataCache<ValueType>>;

    RampDataCache() : mData() {}
    virtual ~RampDataCache() {}
    virtual openvdb::Name typeName() const { return str(); }
    virtual openvdb::Metadata::Ptr copy() const {
        openvdb::Metadata::Ptr metadata(new RampDataCache<ValueType>());
        metadata->copy(*this);
        return metadata;
    }
    virtual void copy(const openvdb::Metadata& other) {
        const RampDataCache* t = dynamic_cast<const RampDataCache*>(&other);
        if (t == nullptr) OPENVDB_THROW(openvdb::TypeError, "Incompatible type during copy");
        mData = t->mData;
    }
    virtual std::string str() const { return "<compiler ramp data>"; }
    virtual bool asBool() const { return true; }
    virtual openvdb::Index32 size() const {
        return static_cast<openvdb::Index32>(mData.size());
    }

    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////

    inline void insertRampPoint(const float pos, const ValueType& value)
    {
        mData[pos] = value;
    }

    inline void clearRampPoints() { mData.clear(); }

    RampType& value() { return mData; }
    const RampType& value() const { return mData; }

protected:
    virtual void readValue(std::istream&s, openvdb::Index32 numBytes) {
        OPENVDB_THROW(openvdb::TypeError, "Metadata has unknown type");
    }
    virtual void writeValue(std::ostream&) const {
        OPENVDB_THROW(openvdb::TypeError, "Metadata has unknown type");
    }

private:
    RampType mData;
};

/// @brief chramp function to query channel referenced ramps in Houdini
///
struct Chramp : public openvdb::ax::codegen::FunctionBase
{
    using FunctionBase = openvdb::ax::codegen::FunctionBase;

    struct Internal : public FunctionBase
    {
        inline FunctionBase::Context context() const override final {
            return FunctionBase::All;
        }
        inline const std::string identifier() const override final {
            return std::string("internal_chramp");
        }
        inline void getDocumentation(std::string& doc) const override final {
            doc = "Internal function for querying ramp data";
        }

        inline static FunctionBase::Ptr
        create(const openvdb::ax::FunctionOptions&) {
            return FunctionBase::Ptr(new Internal());
        }

        Internal() : FunctionBase({
                DECLARE_FUNCTION_SIGNATURE_OUTPUT(sample_map, 1)
            }) {}

    private:

        static void sample_map(const uint8_t* const name, float position, const void* const data, float (*out)[3])
        {
            using FloatRampCacheType = RampDataCache<float>;
            using FloatRamp = FloatRampCacheType::RampType;
            using VectorRampCacheType = RampDataCache<openvdb::math::Vec3<float>>;
            using VectorRamp = VectorRampCacheType::RampType;

            const openvdb::ax::CustomData* const customData =
                static_cast<const openvdb::ax::CustomData* const>(data);

            // clamp
            position = position > 0.0f ? position < 1.0f ? position : 1.0f : 0.0f;

            const std::string nameString(reinterpret_cast<const char* const>(name));

            const FloatRampCacheType* const floatRampData =
                customData->getData<FloatRampCacheType>(nameString);

            if (floatRampData) {
                const FloatRamp& ramp = floatRampData->value();
                auto upper = ramp.upper_bound(position);

                if (upper == ramp.begin()) {
                    (*out)[0] = upper->second;
                    (*out)[1] = (*out)[0];
                    (*out)[2] = (*out)[0];
                }
                else if (upper == ramp.end()) {
                    (*out)[0] = (--upper)->second;
                    (*out)[1] = (*out)[0];
                    (*out)[2] = (*out)[0];
                }
                else {
                    const float maxPos = upper->first;
                    const float maxVal = upper->second;

                    --upper;

                    const float minPos = upper->first;
                    const float minVal = upper->second;
                    const float coef = (position - minPos) / (maxPos - minPos);

                    // lerp
                    (*out)[0] = (minVal * (1.0f - coef)) + (maxVal * coef);
                    (*out)[1] = (*out)[0];
                    (*out)[2] = (*out)[0];
                }

                return;
            }

            const VectorRampCacheType* const vectorRampData =
                customData->getData<VectorRampCacheType>(nameString);

            if (vectorRampData) {
                const VectorRamp& ramp = vectorRampData->value();
                auto upper = ramp.upper_bound(position);

                if (upper == ramp.begin()) {
                    const openvdb::Vec3f& value = upper->second;
                    (*out)[0] = value[0];
                    (*out)[1] = value[1];
                    (*out)[2] = value[2];
                }
                else if (upper == ramp.end()) {
                    const openvdb::Vec3f& value = (--upper)->second;
                    (*out)[0] = value[0];
                    (*out)[1] = value[1];
                    (*out)[2] = value[2];
                }
                else {
                    const float maxPos = upper->first;
                    const openvdb::Vec3f& maxVal = upper->second;

                    --upper;

                    const float minPos = upper->first;
                    const openvdb::Vec3f& minVal = upper->second;
                    const float coef = (position - minPos) / (maxPos - minPos);

                    // lerp
                    const openvdb::Vec3f value = (minVal * (1.0f - coef)) + (maxVal * coef);
                    (*out)[0] = value[0];
                    (*out)[1] = value[1];
                    (*out)[2] = value[2];
                }
            }
        }
    };

    inline FunctionBase::Context context() const override final {
        return openvdb::ax::codegen::FunctionBase::All;
    }
    inline const std::string identifier() const override final {
        return std::string("chramp");
    }
    inline void getDocumentation(std::string& doc) const override final {
        doc = "Evaluate the channel referenced ramp value.";
    }

    Chramp() : openvdb::ax::codegen::FunctionBase({
            openvdb::ax::codegen::FunctionSignature<
                openvdb::ax::codegen::V3F*(const uint8_t* const, float)>::create
                    (nullptr, std::string("chramp"), 0)
        }) {}

    inline void getDependencies(std::vector<std::string>& identifiers) const override {
        identifiers.emplace_back("internal_chramp");
    }

    inline static FunctionBase::Ptr
    create(const openvdb::ax::FunctionOptions&) {
        return FunctionBase::Ptr(new Chramp());
    }

    llvm::Value*
    generate(const std::vector<llvm::Value*>& args,
         const std::unordered_map<std::string, llvm::Value*>& globals,
         llvm::IRBuilder<>& builder) const override {

        std::vector<llvm::Value*> internalArgs(args);
        internalArgs.emplace_back(globals.at("custom_data"));

        std::vector<llvm::Value*> results;
        Internal func;
        func.execute(internalArgs, globals, builder, &results);
        return results.front();
     }
};


///////////////////////////////////////////////////////////////////////////


void registerCustomHoudiniFunctions(openvdb::ax::codegen::FunctionRegistry& reg,
                                    const openvdb::ax::FunctionOptions& options)
{
    // @note - we could alias matching functions such as ch and chv here, but we opt
    // to use the modifier so that all supported VEX conversion is in one place. chramp
    // is a re-implemented function and is not currently supported outside of the Houdini
    // plugin

    if (!options.mLazyFunctions) {
        reg.insertAndCreate("chramp", openvdb_ax_houdini::Chramp::create, options);
        reg.insertAndCreate("internal_chramp",
            openvdb_ax_houdini::Chramp::Internal::create, options, true);
    }
    else {
        reg.insert("chramp", openvdb_ax_houdini::Chramp::create);
        reg.insert("internal_chramp", openvdb_ax_houdini::Chramp::Internal::create,  true);
    }
}

} // namespace openvdb_ax_houdini

#endif // OPENVDB_AX_HOUDINI_AX_UTILS_HAS_BEEN_INCLUDED

// Copyright (c) 2015-2019 DNEG
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
