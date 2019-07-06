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

#ifndef OPENVDB_AX_AST_VISITOR_HAS_BEEN_INCLUDED
#define OPENVDB_AX_AST_VISITOR_HAS_BEEN_INCLUDED

#include "Tokens.h"
#include "Literals.h"

#include <openvdb/Types.h>
#include <openvdb/util/Name.h>
#include <openvdb_ax/version.h>
#include <openvdb_ax/ast/AST.h>

#include <type_traits>
#include <memory>
#include <utility>
#include <vector>

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {

namespace ax {
namespace ast {

template <typename Derived, bool ConstVisit=true>
struct Visitor
{
    template <typename NodeT>
    using NodeType = typename std::conditional<ConstVisit, const NodeT, NodeT>::type;

    inline Derived& derived() {
        return *static_cast<Derived*>(this);
    }

    /// @brief  Define whether this traversla scheme should post visit the nodes. For example,
    ///   a statment "@a=a;" visited in post traversal will visit the nodes in order:
    ///      '(local, attrib), assign'
    ///   the same statement with pre traversal will visit the nodes in order:
    ///      'assign, (local, attrib)'
    inline bool postOrderNodes() const { return true; }

    /// @brief  Completely reverse the traversal order
    inline bool reverse() const { return false; }

    /// @brief  Whether to visit nodes mutiple times at each stage of
    ///   their class hierarchy
    inline bool visitNodeHierarchies() const { return false; }

    ///

    bool traverse(NodeType<ast::Node>* node) {
        if (!node) return true;
        switch (node->nodetype()) {
            case Node::TreeNode : return this->derived().traverse(static_cast<NodeType<ast::Tree>*>(node));
            case Node::BlockNode : return this->derived().traverse(static_cast<NodeType<ast::Block>*>(node));
            case Node::ExpressionListNode : return this->derived().traverse(static_cast<NodeType<ast::ExpressionList>*>(node));
            case Node::ConditionalStatementNode : return this->derived().traverse(static_cast<NodeType<ast::ConditionalStatement>*>(node));
            case Node::AssignExpressionNode : return this->derived().traverse(static_cast<NodeType<ast::AssignExpression>*>(node));
            case Node::CrementNode : return this->derived().traverse(static_cast<NodeType<ast::Crement>*>(node));
            case Node::UnaryOperatorNode : return this->derived().traverse(static_cast<NodeType<ast::UnaryOperator>*>(node));
            case Node::BinaryOperatorNode : return this->derived().traverse(static_cast<NodeType<ast::BinaryOperator>*>(node));
            case Node::CastNode : return this->derived().traverse(static_cast<NodeType<ast::Cast>*>(node));
            case Node::AttributeNode : return this->derived().traverse(static_cast<NodeType<ast::Attribute>*>(node));
            case Node::FunctionCallNode : return this->derived().traverse(static_cast<NodeType<ast::FunctionCall>*>(node));
            case Node::ExternalVariableNode : return this->derived().traverse(static_cast<NodeType<ast::ExternalVariable>*>(node));
            case Node::DeclareLocalNode : return this->derived().traverse(static_cast<NodeType<ast::DeclareLocal>*>(node));
            case Node::ReturnNode : return this->derived().traverse(static_cast<NodeType<ast::Return>*>(node));
            case Node::ArrayPackNode : return this->derived().traverse(static_cast<NodeType<ast::ArrayPack>*>(node));
            case Node::ArrayUnpackNode : return this->derived().traverse(static_cast<NodeType<ast::ArrayUnpack>*>(node));
            case Node::LocalNode : return this->derived().traverse(static_cast<NodeType<ast::Local>*>(node));
            case Node::ValueBoolNode : return this->derived().traverse(static_cast<NodeType<ast::Value<bool>>*>(node));
            case Node::ValueInt16Node : return this->derived().traverse(static_cast<NodeType<ast::Value<int16_t>>*>(node));
            case Node::ValueInt32Node : return this->derived().traverse(static_cast<NodeType<ast::Value<int32_t>>*>(node));
            case Node::ValueInt64Node : return this->derived().traverse(static_cast<NodeType<ast::Value<int64_t>>*>(node));
            case Node::ValueFloatNode : return this->derived().traverse(static_cast<NodeType<ast::Value<float>>*>(node));
            case Node::ValueDoubleNode : return this->derived().traverse(static_cast<NodeType<ast::Value<double>>*>(node));
            case Node::ValueStrNode : return this->derived().traverse(static_cast<NodeType<ast::Value<std::string>>*>(node));
            default : return true;
        }
    }

    bool traverse(NodeType<ast::Tree>* tree) {
        return this->defaultTraversal<ast::Tree>(tree);
    }

    bool traverse(NodeType<ast::Block>* block) {
        return this->defaultTraversal<ast::Block>(block);
    }

    bool traverse(NodeType<ast::ExpressionList>* exprlist) {
        return this->defaultTraversal<ast::ExpressionList>(exprlist);
    }

    bool traverse(NodeType<ast::ConditionalStatement>* cond) {
        return this->defaultTraversal<ast::ConditionalStatement>(cond);
    }

    bool traverse(NodeType<ast::AssignExpression>* asgn) {
        return this->defaultTraversal<ast::AssignExpression>(asgn);
    }

    bool traverse(NodeType<ast::Crement>* crmt) {
        return this->defaultTraversal<ast::Crement>(crmt);
    }

    bool traverse(NodeType<ast::UnaryOperator>* unry) {
        return this->defaultTraversal<ast::UnaryOperator>(unry);
    }

    bool traverse(NodeType<ast::BinaryOperator>* bin) {
        return this->defaultTraversal<ast::BinaryOperator>(bin);
    }

    bool traverse(NodeType<ast::Cast>* cast) {
        return this->defaultTraversal<ast::Cast>(cast);
    }

    bool traverse(NodeType<ast::FunctionCall>* call) {
        return this->defaultTraversal<ast::FunctionCall>(call);
    }

    bool traverse(NodeType<ast::Return>* ret) {
        return this->defaultTraversal<ast::Return>(ret);
    }

    bool traverse(NodeType<ast::Attribute>* attr) {
        return this->defaultTraversal<ast::Attribute>(attr);
    }

    bool traverse(NodeType<ast::ExternalVariable>* ext) {
        return this->defaultTraversal<ast::ExternalVariable>(ext);
    }

    bool traverse(NodeType<ast::DeclareLocal>* decl) {
        return this->defaultTraversal<ast::DeclareLocal>(decl);
    }

    bool traverse(NodeType<ast::Local>* loc) {
        return this->defaultTraversal<ast::Local>(loc);
    }

    bool traverse(NodeType<ast::ArrayPack>* pack) {
        return this->defaultTraversal<ast::ArrayPack>(pack);
    }

    bool traverse(NodeType<ast::ArrayUnpack>* pack) {
        return this->defaultTraversal<ast::ArrayUnpack>(pack);
    }

    bool traverse(NodeType<ast::Value<bool>>* val) {
        return this->defaultTraversal<ast::Value<bool>>(val);
    }

    bool traverse(NodeType<ast::Value<int16_t>>* val) {
        return this->defaultTraversal<ast::Value<int16_t>>(val);
    }

    bool traverse(NodeType<ast::Value<int32_t>>* val) {
        return this->defaultTraversal<ast::Value<int32_t>>(val);
    }

    bool traverse(NodeType<ast::Value<int64_t>>* val) {
        return this->defaultTraversal<ast::Value<int64_t>>(val);
    }

    bool traverse(NodeType<ast::Value<float>>* val) {
        return this->defaultTraversal<ast::Value<float>>(val);
    }

    bool traverse(NodeType<ast::Value<double>>* val) {
        return this->defaultTraversal<ast::Value<double>>(val);
    }

    bool traverse(NodeType<ast::Value<std::string>>* val) {
        return this->defaultTraversal<ast::Value<std::string>>(val);
    }

    // visits for pure virtual nodes. These are only hit if
    // visitNodeHierarchies is true
    inline bool visit(NodeType<ast::Node>*) { return true; }
    inline bool visit(NodeType<ast::Statement>*) { return true; }
    inline bool visit(NodeType<ast::Expression>*) { return true; }
    inline bool visit(NodeType<ast::Keyword>*) { return true; }
    inline bool visit(NodeType<ast::Variable>*) { return true; }
    inline bool visit(NodeType<ast::ValueBase>*) { return true; }

    // visits for all concrete node types
    inline bool visit(NodeType<ast::Tree>*) { return true; }
    inline bool visit(NodeType<ast::Block>*) { return true; }
    inline bool visit(NodeType<ast::ExpressionList>*) { return true; }
    inline bool visit(NodeType<ast::ConditionalStatement>*) { return true; }
    inline bool visit(NodeType<ast::AssignExpression>*) { return true; }
    inline bool visit(NodeType<ast::Crement>*) { return true; }
    inline bool visit(NodeType<ast::UnaryOperator>*) { return true; }
    inline bool visit(NodeType<ast::BinaryOperator>*) { return true; }
    inline bool visit(NodeType<ast::Cast>*) { return true; }
    inline bool visit(NodeType<ast::FunctionCall>*) { return true; }
    inline bool visit(NodeType<ast::Return>*) { return true; }
    inline bool visit(NodeType<ast::Attribute>*) { return true; }
    inline bool visit(NodeType<ast::ExternalVariable>*) { return true; }
    inline bool visit(NodeType<ast::DeclareLocal>*) { return true; }
    inline bool visit(NodeType<ast::Local>*) { return true; }
    inline bool visit(NodeType<ast::ArrayPack>*) { return true; }
    inline bool visit(NodeType<ast::ArrayUnpack>*) { return true; }
    inline bool visit(NodeType<ast::Value<bool>>*) { return true; }
    inline bool visit(NodeType<ast::Value<int16_t>>*) { return true; }
    inline bool visit(NodeType<ast::Value<int32_t>>*) { return true; }
    inline bool visit(NodeType<ast::Value<int64_t>>*) { return true; }
    inline bool visit(NodeType<ast::Value<float>>*) { return true; }
    inline bool visit(NodeType<ast::Value<double>>*) { return true; }
    inline bool visit(NodeType<ast::Value<std::string>>*) { return true; }

private:
    // For const visits, simply return the node
    template <bool V, typename T>
    inline typename std::enable_if<V, const T*>::type
    node(const T& node) {
        return &node;
    }

    // For non-const visits, const cast the node.
    template <bool V, typename T>
    inline typename std::enable_if<!V, typename std::remove_const<T>::type*>::type
    node(const T& node) {
        return &(const_cast<T&>(node));
    }

    template <typename T>
    bool hierarchyvisits(T& node)
    {
        if (!this->derived().visit(this->node<ConstVisit>(node))) return false;
        if (auto base = node.T::basetype()) {
            return hierarchyvisits(*base);
        }
        return true;
    }

    template <typename NodeT>
    inline bool defaultTraversal(NodeType<NodeT>* node)
    {
        if (!node) return true;
        const size_t children = node->children();

        if (this->derived().postOrderNodes()) {
            if (this->derived().reverse()) {
                if (children != 0) {
                    for (int64_t i = static_cast<int64_t>(children - 1); i >= 0; --i) {
                        auto child = this->node<ConstVisit>(*(node->child(i)));
                        if (!this->derived().traverse(child)) {
                            return false;
                        }
                    }
                }
            }
            else {
                for (size_t i = 0; i < children; ++i) {
                    auto child = this->node<ConstVisit>(*(node->child(i)));
                    if (!this->derived().traverse(child)) {
                        return false;
                    }
                }
            }
            if (this->derived().visitNodeHierarchies()) {
                return this->hierarchyvisits(*node);
            }
            else {
                return this->derived().visit(node);
            }
        }
        else {
            if (this->derived().visitNodeHierarchies()) {
                if (!this->hierarchyvisits(*node)) return false;
            }
            else {
                if (!this->derived().visit(node)) return false;
            }
            if (this->derived().reverse()) {
                if (children != 0) {
                    for (int64_t i = static_cast<int64_t>(children - 1); i >= 0; --i) {
                        auto child = this->node<ConstVisit>(*(node->child(i)));
                        if (!this->derived().traverse(child)) {
                            return false;
                        }
                    }
                }
            }
            else {
                for (size_t i = 0; i < children; ++i) {
                    auto child = this->node<ConstVisit>(*(node->child(i)));
                    if (!this->derived().traverse(child)) {
                        return false;
                    }
                }
            }
            return true;
        }
    }
};

} // namespace ast
} // namespace ax

}
} // namespace openvdb

#endif // OPENVDB_AX_AST_VISITOR_HAS_BEEN_INCLUDED
