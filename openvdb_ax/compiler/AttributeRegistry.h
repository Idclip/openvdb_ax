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
////////////////////////////////////////////////////////////////////////////

/// @file compiler/AttributeRegistry.h
///
/// @authors Nick Avramoussis, Francisco Gochez
///
/// @brief These classes contain lists of expected attributes and volumes
///   which are populated by compiler during its internal code generation.
///   These will then be requested from the inputs to the executable
///   when execute is called. In this way, accesses are requested at
///   execution time, allowing the executable objects to be shared and
///   stored.
///

#ifndef OPENVDB_AX_COMPILER_TARGET_REGISTRY_HAS_BEEN_INCLUDED
#define OPENVDB_AX_COMPILER_TARGET_REGISTRY_HAS_BEEN_INCLUDED

#include <openvdb_ax/ast/AST.h>
#include <openvdb_ax/ast/Tokens.h>
#include <openvdb_ax/ast/Scanners.h>

#include <unordered_map>

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {

namespace ax {

/// @brief This class stores a list of access names, types and their dependency
///   connections.
///
class AttributeRegistry
{
public:
    using Ptr = std::shared_ptr<AttributeRegistry>;
    using ConstPtr = std::shared_ptr<const AttributeRegistry>;

    /// @brief  Registered access details, including its name, type and whether
    ///         a write handle is required
    ///
    struct AccessData
    {
        /// @brief Storage for access name, type and writesTo details
        /// @param name      The name of the access
        /// @param type      The typename of the access
        /// @param readsFrom  Whether the access is read from
        /// @param writesTo   Whether the access is writte to
        AccessData(const Name& name,
            const ast::tokens::CoreType type,
            const bool readsFrom,
            const bool writesTo)
            : mAttrib(name, type)
            , mAccess(readsFrom, writesTo)
            , mUses()
            , mDependencies() {}

        bool reads() const { return mAccess.first; }
        bool writes() const { return mAccess.second; }
        const std::string tokenname() const { return mAttrib.tokenname(); }
        const std::string& name() const { return mAttrib.name(); }
        ast::tokens::CoreType type() const { return mAttrib.type(); }
        const std::vector<const AccessData*>& deps() const { return mDependencies; }
        const std::vector<const AccessData*>& uses() const { return mUses; }

        bool dependson(const AccessData* data) const {
            for (auto& dep : mDependencies) {
                if (dep == data) return true;
            }
            return false;
        }

        bool affectsothers() const {
            for (auto& dep : mUses) {
                if (dep != this) return true;
            }
            return false;
        }

    private:
        friend AttributeRegistry;

        const ast::Attribute mAttrib;
        const std::pair<bool, bool> mAccess;
        std::vector<const AccessData*> mUses;  // Accesses which depend on this access
        std::vector<const AccessData*> mDependencies; // Accesses which this access depends on
    };

    using AccessDataVec = std::vector<AccessData>;

    inline static AttributeRegistry::Ptr create(const ast::Tree& tree);

    inline bool isReadable(const std::string& name, const ast::tokens::CoreType type) const
    {
        return this->accessPattern(name, type).first;
    }

    /// @brief  Returns whether or not an access is required to be written to.
    ///         If no access with this name has been registered, returns false
    /// @param  name  The name of the access
    /// @param  type The type of the access
    inline bool isWritable(const std::string& name, const ast::tokens::CoreType type) const
    {
        return this->accessPattern(name, type).second;
    }

    inline std::pair<bool,bool>
    accessPattern(const std::string& name, const ast::tokens::CoreType type) const
    {
        for (const auto& data : mAccesses) {
            if ((type == ast::tokens::UNKNOWN || data.type() == type)
                && data.name() == name) {
                return data.mAccess;
            }
        }
        return std::pair<bool,bool>(false,false);
    }

    /// @brief  Returns whether or not an access is registered.
    /// @param  name The name of the access
    /// @param  type The type of the access
    inline bool isRegistered(const std::string& name, const ast::tokens::CoreType type) const
    {
        return this->accessIndex(name, type) != -1;
    }

    /// @brief  Returns whether or not an access is registered.
    /// @param  name The name of the access
    /// @param  type The type of the access
    inline int64_t
    accessIndex(const std::string& name,
            const ast::tokens::CoreType type) const
    {
        int64_t i = 0;
        for (const auto& data : mAccesses) {
            if (data.type() == type && data.name() == name) {
                return i;
            }
            ++i;
        }
        return -1;
    }

    /// @brief  Returns a const reference to the vector of registered accesss
    inline const AccessDataVec& data() const { return mAccesses; }

    void print(std::ostream& os) const;

private:
    AttributeRegistry() : mAccesses() {}

    /// @brief  Add an access to the registry, returns an index into
    ///         the registry for that access
    /// @param  name      The name of the access
    /// @param  type      The typename of the access
    /// @param  writesTo  Whether the access is required to be writeable
    ///
    inline void
    addData(const Name& name,
        const ast::tokens::CoreType type,
        const bool readsfrom,
        const bool writesto) {
        mAccesses.emplace_back(name, type, readsfrom, writesto);
    }

    AccessDataVec mAccesses;
};


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////


inline AttributeRegistry::Ptr AttributeRegistry::create(const ast::Tree& tree)
{
    AttributeRegistry::Ptr registry(new AttributeRegistry());
    std::vector<std::string> read, write, all;
    ast::catalogueAttributeTokens(tree, &read, &write, &all);

    size_t idx = 0;
    std::unordered_map<std::string, size_t> indexmap;

    auto dataBuilder =
        [&](const std::vector<std::string>& attribs,
            const bool readFlag,
            const bool writeFlag)
    {
        std::string name, type;
        for (const auto& attrib : attribs) {
            ast::Attribute::nametypeFromToken(attrib, &name, &type);
            const ast::tokens::CoreType typetoken =
                ast::tokens::tokenFromTypeString(type);
            registry->addData(name, typetoken, readFlag, writeFlag);
            indexmap[attrib] = idx++;
        }
    };

    // insert all data

    dataBuilder(read, true, false);
    dataBuilder(write, false, true);
    dataBuilder(all, true, true);

    auto depBuilder = [&](const std::vector<std::string>& attribs) {

        std::string name, type;
        for (const auto& attrib : attribs) {
            ast::Attribute::nametypeFromToken(attrib, &name, &type);
            const ast::tokens::CoreType typetoken =
                ast::tokens::tokenFromTypeString(type);

            std::vector<std::string> deps;
            ast::attributeDependencyTokens(tree, name, typetoken, deps);
            if (deps.empty()) continue;

            assert(indexmap.find(attrib) != indexmap.cend());
            const size_t index = indexmap.at(attrib);
            AccessData& access = registry->mAccesses[index];
            for (const std::string& dep : deps) {
                assert(indexmap.find(dep) != indexmap.cend());
                const size_t depindex = indexmap.at(dep);
                access.mDependencies.emplace_back(&registry->mAccesses[depindex]);
            }
        }
    };

    // initialize dependencies

    depBuilder(read);
    depBuilder(write);
    depBuilder(all);

    // Update usage from deps

    for (AccessData& access : registry->mAccesses) {
        for (const AccessData& next : registry->mAccesses) {
            // don't skip self depends as it may write to itself
            // i.e. @a = @a + 1; should add a self usage
            if (next.dependson(&access)) {
                access.mUses.emplace_back(&next);
            }
        }
    }

    return registry;
}

inline void AttributeRegistry::print(std::ostream& os) const
{
    size_t idx = 0;
    for (const auto& data : mAccesses) {
        os << "Attribute: " << data.name() << ", type: " <<
            ast::tokens::typeStringFromToken(data.type()) << '\n';
        os << "  " << "Index        : " << idx << '\n';
        os << std::boolalpha;
        os << "  " << "Reads From   : " << data.reads() << '\n';
        os << "  " << "Writes To    : " << data.writes() << '\n';
        os << std::noboolalpha;
        os << "  " << "Dependencies : " << data.mDependencies.size() << '\n';
        for (const auto& dep : data.mDependencies) {
            os << "    " << "Attribute: " << dep->name() << " type: " <<
                ast::tokens::typeStringFromToken(dep->type()) << '\n';
        }
        os << "  " << "Usage : " << data.mUses.size() << '\n';
        for (const auto& dep : data.mUses) {
            os << "    " << "Attribute: " << dep->name() << " type: " <<
                ast::tokens::typeStringFromToken(dep->type()) << '\n';
        }
        os << '\n';
        ++idx;
    }
}

}
}
}

#endif // OPENVDB_AX_COMPILER_TARGET_REGISTRY_HAS_BEEN_INCLUDED

// Copyright (c) 2015-2020 DNEG
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
