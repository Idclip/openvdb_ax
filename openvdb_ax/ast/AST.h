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

#ifndef OPENVDB_AX_AST_HAS_BEEN_INCLUDED
#define OPENVDB_AX_AST_HAS_BEEN_INCLUDED

#include "Tokens.h"
#include "Literals.h"

#include <openvdb/Types.h>
#include <openvdb/util/Name.h>
#include <openvdb_ax/version.h>

#include <memory>
#include <utility>
#include <vector>

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {

namespace ax {
namespace ast {

/// Forward declaration of the AST
struct Tree;

/// @brief  Construct an abstract syntax tree from a code snippet
///
std::shared_ptr<Tree> parse(const char* code);


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// Forward declarations of all AST nodes

struct Node;
struct Statement;
struct Block;
struct Expression;
struct ExpressionList;
struct ConditionalStatement;
struct AssignExpression;
struct Crement;
struct UnaryOperator;
struct BinaryOperator;
struct Cast;
struct Variable;
struct Attribute;
struct ExternalVariable;
struct DeclareLocal;
struct Local;
struct ValueBase;

// ----------------------------------------------------------------------------
// Visitor Objects
// ----------------------------------------------------------------------------

struct Node
{
    using Ptr = std::shared_ptr<Node>;
    using UniquePtr = std::unique_ptr<Node>;

    enum NodeType {
        TreeNode,
        BlockNode,
        ExpressionNode,
        ExpressionListNode,
        ConditionalStatementNode,
        AssignExpressionNode,
        CrementNode,
        UnaryOperatorNode,
        BinaryOperatorNode,
        CastNode,
        AttributeNode,
        FunctionCallNode,
        ExternalVariableNode,
        DeclareLocalNode,
        ReturnNode,
        ArrayPackNode,
        ArrayUnpackNode,
        LocalNode,
        ValueBoolNode,
        ValueInt16Node,
        ValueInt32Node,
        ValueInt64Node,
        ValueFloatNode,
        ValueDoubleNode,
        ValueStrNode
    };

    Node() = default;
    virtual ~Node() = default;
    virtual Node* copy() const = 0;

    // basic children methods
    virtual size_t children() const = 0;
    virtual const Node* child(const size_t) const = 0;

    // type and name methods
    virtual NodeType nodetype() const = 0;
    virtual const char* nodename() const = 0;
    virtual const char* subname() const = 0;

    // @todo replace with enum comp
    template <typename NodeT>
    inline bool isType() const {
        return dynamic_cast<const NodeT*>(this);
    }

    /// @brief Returns the child index of this node in relation to its
    ///   parent, or -1 if no valid index is found (usually representing
    ///   the top most node i.e. tree)
    inline int64_t childidx() const
    {
        const Node* p = this->parent();
        if (!p) return -1;
        size_t i = 0;
        const size_t count = p->children();
        for (; i < count; ++i) {
            if (p->child(i) == this) break;
        }
        if (i == count) return -1;
        return static_cast<int64_t>(i);
    }

    /// @brief  In place replacement. If this function returns true,
    ///   the execution node will have been destroyed in favour of the
    ///   provided argument. No further calls to this should be made
    inline bool replace(Node* node)
    {
        const int64_t idx = this->childidx();
        if (idx == -1) return false; // avoid second vcall
        return this->parent()->replacechild(idx, node);
    }

    /// @brief  Virtual method that attempted to replace a child at
    ///   index i with a provided node type. Returns false if the
    ///   replacement was unsuccessful, which can occur if the index
    ///   is out of range or if provided node is of an incompatible
    ///   type.
    /// @note  This method may invoke a dynamic cast on the provided
    ///   node. It will always invoke a dynamic cast on successful
    ///   replacements.
    virtual bool replacechild(const size_t, Node*) { return false; }

    // parent methods
    inline const Node* parent() const { return mParent; }
    inline void setParent(Node* parent) {
#ifndef NDEBUG
        bool hasChild = false;
        for (size_t i = 0; i < parent->children(); ++i)
            hasChild |= parent->child(i) == this;
        assert(hasChild);
#endif
        mParent = parent;
    }

private:
    inline Node* parent() { return mParent; }
    Node* mParent = nullptr;
};

/* Concrete Nodes ------------------------------------------------------------- */

// Statements are anything that can make up a line, i.e. everything inbetween
// semicolons
struct Statement : public Node
{
    using Ptr = std::shared_ptr<Statement>;
    using UniquePtr = std::unique_ptr<Statement>;
    ~Statement() override = default;
    virtual Statement* copy() const override = 0;
    const char* nodename() const override { return "statement"; }
    const char* subname() const override { return "stm"; }
};

// Expressions only contain identifiers, literals and operators, and can be
// reduced to some kind of value. For example:
//    3 + 5
//    min(3, 2)
struct Expression : public Statement
{
    using Ptr = std::shared_ptr<Expression>;
    using UniquePtr = std::unique_ptr<Expression>;
    ~Expression() override = default;
    virtual Expression* copy() const override = 0;
    const char* nodename() const override { return "expression"; }
    const char* subname() const override { return "exp"; }
};

struct Block : public Statement
{
    using UniquePtr = std::unique_ptr<Block>;

    Block() : mList() {}
    Block(Statement* statement)
        : mList() {
        this->addStatement(statement);
    }
    Block(const std::vector<Statement*>& statements)
        : mList() {
        for (Statement* statement : statements) {
            this->addStatement(statement);
        }
    }
    Block(const Block& other) : mList() {
        for (const Statement::UniquePtr& stmnt : other.mList) {
            this->addStatement(stmnt->copy());
        }
    }
    ~Block() override = default;

    Block* copy() const override final { return new Block(*this); }
    NodeType nodetype() const override { return Node::BlockNode; }
    const char* nodename() const override { return "block"; }
    const char* subname() const override { return "blk"; }
    //
    size_t children() const override final { return this->size(); }
    const Statement* child(const size_t i) const override final {
        if (i >= mList.size()) return nullptr;
        return mList[i].get();
    }
    //
    inline size_t size() const { return mList.size(); }
    inline void addStatement(Statement* stmnt) {
        if (stmnt) {
            mList.emplace_back(stmnt);
            stmnt->setParent(this);
        }
    }

    inline bool replacechild(const size_t i, Node* node) override final {
        if (mList.size() <= i) return false;
        Expression* expr = dynamic_cast<Expression*>(node);
        if (!expr) return false;
        mList[i].reset(expr);
        mList[i]->setParent(this);
        return true;
    }

private:
    std::vector<Statement::UniquePtr> mList;
};

// A tree is a list of statements that make up the whole program
struct Tree : public Node
{
    using Ptr = std::shared_ptr<Tree>;
    using ConstPtr = std::shared_ptr<const Tree>;
    using UniquePtr = std::unique_ptr<Tree>;

    Tree(Block* block = new Block())
        : mBlock(block) {
            mBlock->setParent(this);
    }
    Tree(const Tree& other)
        : mBlock(new Block(*other.mBlock)) {
            mBlock->setParent(this);
        }
    ~Tree() override = default;

    Tree* copy() const override final { return new Tree(*this); }
    NodeType nodetype() const override { return Node::TreeNode; }
    const char* nodename() const override { return "tree"; }
    const char* subname() const override { return "tree"; }
    //
    size_t children() const override final { return 1; }
    const Block* child(const size_t i) const override final {
        if (i == 0) return mBlock.get();
        return nullptr;
    }

private:
    Block::UniquePtr mBlock;
};

struct ExpressionList : public Statement
{
    using UniquePtr = std::unique_ptr<ExpressionList>;

    ExpressionList() : mList() {}
    ExpressionList(Expression* expression)
        : mList() {
        this->addExpression(expression);
    }
    ExpressionList(const std::vector<Expression*>& expressions)
        : mList() {
        for (Expression* expression : expressions) {
            this->addExpression(expression);
        }
    }
    ExpressionList(const ExpressionList& other)
        : mList() {
        for (const Expression::UniquePtr& expr : other.mList) {
            this->addExpression(expr->copy());
        }
    }
    ~ExpressionList() override = default;

    ExpressionList* copy() const override final { return new ExpressionList(*this); }
    NodeType nodetype() const override { return Node::ExpressionListNode; }
    const char* nodename() const override { return "expression list"; }
    const char* subname() const override { return "expl"; }
    //
    size_t children() const override final { return this->size(); }
    const Expression* child(const size_t i) const override final {
        if (i >= mList.size()) return nullptr;
        return mList[i].get();
    }
    //
    inline size_t size() const { return mList.size(); }
    inline bool empty() const { return mList.empty(); }
    inline void addExpression(Expression* expr) {
        if (expr) {
            mList.emplace_back(expr);
            expr->setParent(this);
        }
    }

    inline bool replacechild(const size_t i, Node* node) override final {
        if (mList.size() <= i) return false;
        Expression* expr = dynamic_cast<Expression*>(node);
        mList[i].reset(expr);
        mList[i]->setParent(this);
        return true;
    }

private:
    std::vector<Expression::UniquePtr> mList;
};

struct ConditionalStatement : public Statement
{
    using UniquePtr = std::unique_ptr<ConditionalStatement>;

    ConditionalStatement(Expression* conditional,
                         Block* thenBranch,
                         Block* elseBranch = new Block())
        : mConditional(conditional)
        , mThenBranch(thenBranch)
        , mElseBranch(elseBranch) {
            assert(mConditional);
            assert(mThenBranch);
            assert(mElseBranch);
            mConditional->setParent(this);
            mThenBranch->setParent(this);
            mElseBranch->setParent(this);
        }
    ConditionalStatement(const ConditionalStatement& other)
        : mConditional(other.mConditional->copy())
        , mThenBranch(new Block(*other.mThenBranch))
        , mElseBranch(new Block(*other.mElseBranch)) {
            mConditional->setParent(this);
            mThenBranch->setParent(this);
            mElseBranch->setParent(this);
        }
    ~ConditionalStatement() override = default;

    ConditionalStatement* copy() const override final { return new ConditionalStatement(*this); }
    NodeType nodetype() const override { return Node::ConditionalStatementNode; }
    const char* nodename() const override { return "conditional statement"; }
    const char* subname() const override { return "cond"; }
    //
    size_t children() const override final { return 3; }
    const Statement* child(const size_t i) const override final {
        if (i == 0) return this->condition();
        if (i == 1) return this->thenBranch();
        if (i == 2) return this->elseBranch();
        return nullptr;
    }
    //
    inline bool hasElseBranch() const {
        return static_cast<bool>(this->elseBranch());
    }
    size_t branchCount() const {
        return this->hasElseBranch() ? 2 : 1;
    }
    const Expression* condition() const { return mConditional.get(); }
    const Block* thenBranch() const { return mThenBranch.get(); }
    const Block* elseBranch() const { return mElseBranch.get(); }

    inline bool replacechild(const size_t i, Node* node) override final
    {
        if (i == 0) {
            Expression* expr = dynamic_cast<Expression*>(node);
            if (!expr) return false;
            mConditional.reset(expr);
            mConditional->setParent(this);
            return true;
        }
        else if (i == 1 || i == 2) {
            Block* blk = dynamic_cast<Block*>(node);
            if (!blk) return false;
            if (i == 1) {
                mThenBranch.reset(blk);
                mThenBranch->setParent(this);
            }
            else {
                mElseBranch.reset(blk);
                mElseBranch->setParent(this);
            }
            return true;
        }
        return false;
    }

private:
    Expression::UniquePtr mConditional;
    Block::UniquePtr mThenBranch;
    Block::UniquePtr mElseBranch;
};

struct BinaryOperator : public Expression
{
    using UniquePtr = std::unique_ptr<BinaryOperator>;

    BinaryOperator(const tokens::OperatorToken op,
            Expression* left,
            Expression* right)
        : mOperation(op)
        , mLeft(left)
        , mRight(right) {
            assert(mLeft);
            assert(mRight);
            mLeft->setParent(this);
            mRight->setParent(this);
        }
    BinaryOperator(const std::string& op,
            Expression* left,
            Expression* right)
        : BinaryOperator(tokens::operatorTokenFromName(op), left, right) {}
    BinaryOperator(const BinaryOperator& other)
        : mOperation(other.mOperation)
        , mLeft(other.mLeft->copy())
        , mRight(other.mRight->copy()) {
            mLeft->setParent(this);
            mRight->setParent(this);
        }
    ~BinaryOperator() override = default;

    BinaryOperator* copy() const override final { return new BinaryOperator(*this); }
    NodeType nodetype() const override { return Node::BinaryOperatorNode; }
    const char* nodename() const override { return "binary"; }
    const char* subname() const override { return "bin"; }
    //
    size_t children() const override final { return 2; }
    const Expression* child(const size_t i) const override final {
        if (i == 0) return mLeft.get();
        if (i == 1) return mRight.get();
        return nullptr;
    }
    inline tokens::OperatorToken operation() const { return mOperation; }
    const Expression* lhs() const { return mLeft.get(); }
    const Expression* rhs() const { return mRight.get(); }

    inline bool replacechild(const size_t i, Node* node) override final {
        if (i > 1) return false;
        Expression* expr = dynamic_cast<Expression*>(node);
        if (!expr) return false;
        if (i == 0) {
            mLeft.reset(expr);
            mLeft->setParent(this);
        }
        else if (i == 1) {
            mRight.reset(expr);
            mRight->setParent(this);
        }
        return true;
    }

private:
    const tokens::OperatorToken mOperation;
    Expression::UniquePtr mLeft;
    Expression::UniquePtr mRight;
};

// AssignExpression are of the form lvalue = expression
// Since they can be chained together, they are also expressions
struct AssignExpression : public Expression
{
    using UniquePtr = std::unique_ptr<AssignExpression>;

    AssignExpression(Expression* lhs, Expression* rhs, const bool isCompound)
        : mCompound(isCompound)
        , mRHS(rhs)
        , mLHS(lhs) {
            assert(mLHS);
            assert(mRHS);
            mLHS->setParent(this);
            mRHS->setParent(this);
        }
    AssignExpression(const AssignExpression& other)
        : mCompound(other.mCompound)
        , mRHS(other.mRHS->copy())
        , mLHS(other.mLHS->copy()) {
            mLHS->setParent(this);
            mRHS->setParent(this);
        }

    ~AssignExpression() override = default;

    AssignExpression* copy() const override final { return new AssignExpression(*this); }
    NodeType nodetype() const override { return Node::AssignExpressionNode; }
    const char* nodename() const override { return "assignment expression"; }
    const char* subname() const override { return "asgn"; }
    //
    size_t children() const override final { return 2; }
    const Expression* child(const size_t i) const override final {
        if (i == 0) return this->rhs();
        if (i == 1) return this->lhs();
        return nullptr;
    }
    const Expression* lhs() const { return mLHS.get(); }
    const Expression* rhs() const { return mRHS.get(); }
    //
    inline bool isCompound() const { return mCompound; }
    inline tokens::OperatorToken operation() const {
        if (this->isCompound()) {
            assert(mRHS->isType<BinaryOperator>());
            const tokens::OperatorToken binary =
                static_cast<BinaryOperator*>(mRHS.get())->operation();

            switch (binary) {
                case tokens::PLUS      : return tokens::PLUSEQUALS;
                case tokens::MINUS     : return tokens::MINUSEQUALS;
                case tokens::MULTIPLY  : return tokens::MULTIPLYEQUALS;
                case tokens::DIVIDE    : return tokens::DIVIDEEQUALS;
                case tokens::MODULO    : return tokens::MODULOEQUALS;
                case tokens::BITAND    : return tokens::BITANDEQUALS;
                case tokens::BITXOR    : return tokens::BITXOREQUALS;
                case tokens::BITOR     : return tokens::BITOREQUALS;
                default : {
                    assert(false && "Invalid compund assignment in AST.");
                }
            }
        }
        return tokens::EQUALS;
    }

    inline bool replacechild(const size_t i, Node* node) override final {
        if (i > 1) return false;
        Expression* expr = dynamic_cast<Expression*>(node);
        if (!expr) return false;
        if (i == 0) {
            mRHS.reset(expr);
            mRHS->setParent(this);
        }
        else if (i == 1) {
            mLHS.reset(expr);
            mLHS->setParent(this);
        }
        return true;
    }

private:
    const bool mCompound;
    Expression::UniquePtr mRHS;
    Expression::UniquePtr mLHS;
};

struct Crement : public Expression
{
    using UniquePtr = std::unique_ptr<Crement>;

    enum Operation {
        Increment,
        Decrement
    };

    Crement(Expression* expression, const Operation operation, bool post)
        : mExpression(expression)
        , mOperation(operation)
        , mPost(post) {
            mExpression->setParent(this);
        }
    Crement(const Crement& other)
        : mExpression(other.mExpression->copy())
        , mOperation(other.mOperation)
        , mPost(other.mPost) {
            mExpression->setParent(this);
        }
    ~Crement() override = default;

    Crement* copy() const override final { return new Crement(*this); }
    NodeType nodetype() const override { return Node::CrementNode; }
    const char* nodename() const override { return "crement"; }
    const char* subname() const override { return "crmt"; }
    //
    size_t children() const override final { return 1; }
    const Expression* child(const size_t i) const override final {
        if (i == 0) return this->expression();
        return nullptr;
    }
    const Expression* expression() const { return mExpression.get(); }
    //
    inline Operation operation() const { return mOperation; }
    inline bool increment() const { return mOperation == Increment; }
    inline bool decrement() const { return mOperation == Decrement; }
    inline bool pre() const { return !mPost; }
    inline bool post() const { return mPost; }

    inline bool replacechild(const size_t i, Node* node) override final {
        if (i != 0) return false;
        Expression* expr = dynamic_cast<Expression*>(node);
        if (!expr) return false;
        mExpression.reset(expr);
        mExpression->setParent(this);
        return true;
    }

private:
    Expression::UniquePtr mExpression;
    const Operation mOperation;
    const bool mPost;
};

struct UnaryOperator : public Expression
{
    using UniquePtr = std::unique_ptr<UnaryOperator>;

    UnaryOperator(const tokens::OperatorToken op, Expression* expression)
        : mOperation(op)
        , mExpression(expression) {
            assert(expression);
            mExpression->setParent(this);
        }
    UnaryOperator(const std::string& op, Expression* expression)
        : UnaryOperator(tokens::operatorTokenFromName(op), expression) {}
    UnaryOperator(const UnaryOperator& other)
        : mOperation(other.mOperation)
        , mExpression(other.mExpression->copy()) {
            mExpression->setParent(this);
        }
    ~UnaryOperator() override = default;

    UnaryOperator* copy() const override final { return new UnaryOperator(*this); }
    NodeType nodetype() const override { return Node::UnaryOperatorNode; }
    const char* nodename() const override { return "unary"; }
    const char* subname() const override { return "unry"; }
    //
    size_t children() const override final { return 1; }
    const Expression* child(const size_t i) const override final {
        if (i == 0) return this->expression();
        return nullptr;
    }
    //
    inline tokens::OperatorToken operation() const { return mOperation; }
    const Expression* expression() const { return mExpression.get(); }

    inline bool replacechild(const size_t i, Node* node) override final {
        if (i != 0) return false;
        Expression* expr = dynamic_cast<Expression*>(node);
        if (!expr) return false;
        mExpression.reset(expr);
        mExpression->setParent(this);
        return true;
    }

private:
    const tokens::OperatorToken mOperation;
    Expression::UniquePtr mExpression;
};

struct Cast : public Expression
{
    using UniquePtr = std::unique_ptr<Cast>;

    Cast(Expression* expression, const tokens::CoreType type)
        : Expression()
        , mType(type)
        , mExpression(expression) {
            assert(mExpression);
            mExpression->setParent(this);
        }
    Cast(const Cast& other)
        : Expression()
        , mType(other.mType)
        , mExpression(other.mExpression->copy()) {
            mExpression->setParent(this);
        }
    ~Cast() override = default;

    Cast* copy() const override final { return new Cast(*this); }
    NodeType nodetype() const override { return Node::CastNode; }
    const char* nodename() const override { return "cast"; }
    const char* subname() const override { return "cast"; }
    //
    size_t children() const override final { return 1; }
    const Expression* child(const size_t i) const override final {
        if (i == 0) return this->expression();
        return nullptr;
    }
    //
    const Expression* expression() const { return mExpression.get(); }
    inline tokens::CoreType type() const { return mType; }
    inline std::string typestr() const { return ast::tokens::typeStringFromToken(mType); }

    inline bool replacechild(const size_t i, Node* node) override final {
        if (i != 0) return false;
        Expression* expr = dynamic_cast<Expression*>(node);
        if (!expr) return false;
        mExpression.reset(expr);
        mExpression->setParent(this);
        return true;
    }

private:
    const tokens::CoreType mType;
    Expression::UniquePtr mExpression;
};

struct FunctionCall : public Expression
{
    using UniquePtr = std::unique_ptr<FunctionCall>;

    FunctionCall(const std::string& function,
        ExpressionList* arguments = new ExpressionList())
        : mFunctionName(function)
        , mArguments(arguments) {
            assert(arguments);
            mArguments->setParent(this);
        }
    FunctionCall(const FunctionCall& other)
        : mFunctionName(other.mFunctionName)
        , mArguments(other.mArguments->copy()) {
            mArguments->setParent(this);
        }
    ~FunctionCall() override = default;

    FunctionCall* copy() const override final { return new FunctionCall(*this); }
    NodeType nodetype() const override { return Node::FunctionCallNode; }
    const char* nodename() const override { return "function call"; }
    const char* subname() const override { return "call"; }
    //
    size_t children() const override final { return 1; }
    const ExpressionList* child(const size_t i) const override final {
        if (i == 0) return this->args();
        return nullptr;
    }
    //
    inline const Name& name() const { return mFunctionName; }
    inline size_t numArgs() const { return mArguments->size(); }
    const ExpressionList* args() const { return mArguments.get(); }

    inline bool replacechild(const size_t i, Node* node) override final {
        if (i != 0) return false;
        ExpressionList* exprl = dynamic_cast<ExpressionList*>(node);
        if (!exprl) return false;
        mArguments.reset(exprl);
        mArguments->setParent(this);
        return true;
    }

private:
    const std::string mFunctionName;
    ExpressionList::UniquePtr mArguments;
};

struct Keyword : public Expression
{
    using UniquePtr = std::unique_ptr<Keyword>;
    ~Keyword() override = default;
    const char* nodename() const override { return "keyword"; }
    const char* subname() const override { return "keyw"; }
    size_t children() const override final { return 0; }
    const Node* child(const size_t) const override final {
        return nullptr;
    }
};

struct Return : public Keyword
{
    using UniquePtr = std::unique_ptr<Return>;
    ~Return() override = default;
    Return* copy() const override final { return new Return(*this); }
    NodeType nodetype() const override { return Node::ReturnNode; }
    const char* nodename() const override { return "return"; }
    const char* subname() const override { return "ret"; }
};

struct Variable : public Expression
{
    using UniquePtr = std::unique_ptr<Variable>;

    Variable(const Name& name)
        : Expression(), mName(name) {}
    Variable(const Variable& other)
        : Expression(), mName(other.mName) {}
    ~Variable() override = default;

    virtual Variable* copy() const override = 0;
    const char* nodename() const override { return "var"; }
    const char* subname() const override { return "var"; }
    //
    size_t children() const override { return 0; }
    const Node* child(const size_t) const override {
        return nullptr;
    }
    //
    inline const Name& name() const { return mName; }

private:
    const Name mName;
};

struct Attribute : public Variable
{
    using UniquePtr = std::unique_ptr<Attribute>;

    Attribute(const std::string& name, const tokens::CoreType type,
              const bool typeInferred = false)
        : Variable(name)
        , mType(type)
        , mTypeInferred(typeInferred) {}
    Attribute(const std::string& name, const std::string& token,
              const bool typeInferred = false)
        : Attribute(name, tokens::tokenFromTypeString(token), typeInferred) {}
    Attribute(const Attribute& other)
        : Variable(other)
        , mType(other.mType)
        , mTypeInferred(other.mTypeInferred) {}
    ~Attribute() override = default;

    Attribute* copy() const override final { return new Attribute(*this); }
    NodeType nodetype() const override { return Node::AttributeNode; }
    const char* nodename() const override { return "attribute"; }
    const char* subname() const override { return "atr"; }
    //
    inline bool inferred() const { return mTypeInferred; }
    inline tokens::CoreType type() const { return mType; }
    inline std::string typestr() const { return ast::tokens::typeStringFromToken(mType); }
    inline std::string tokenname() const {
        return this->typestr() +
            this->symbolseparator() +
            this->name();
    }
    //
    static inline char symbolseparator() { return '@'; }
    static inline std::string
    tokenFromNameType(const std::string& name, const tokens::CoreType type) {
        return ast::tokens::typeStringFromToken(type) +
            Attribute::symbolseparator() + name;
    }
    static inline bool
    nametypeFromToken(const std::string& token, std::string* name, std::string* type) {
        const size_t at = token.find(symbolseparator());
        if (at == std::string::npos) return false;
        if (type) {
            *type = token.substr(0, at);
            if (type->empty()) {
                *type = ast::tokens::typeStringFromToken(tokens::CoreType::FLOAT);
            }
        }
        if (name) *name = token.substr(at + 1, token.size());
        return true;
    }

private:
    const tokens::CoreType mType;
    const bool mTypeInferred;
};

struct ExternalVariable : public Variable
{
    using UniquePtr = std::unique_ptr<ExternalVariable>;

    ExternalVariable(const std::string& name, const tokens::CoreType type)
        : Variable(name)
        , mType(type) {}
    ExternalVariable(const std::string& name, const std::string& token)
        : ExternalVariable(name, tokens::tokenFromTypeString(token)) {}
    ExternalVariable(const ExternalVariable& other)
        : Variable(other)
        , mType(other.mType) {}
    ~ExternalVariable() override = default;

    ExternalVariable* copy() const override final { return new ExternalVariable(*this); }
    NodeType nodetype() const override { return Node::ExternalVariableNode; }
    const char* nodename() const override { return "external"; }
    const char* subname() const override { return "ext"; }
    //
    inline tokens::CoreType type() const { return mType; }
    inline std::string typestr() const { return ast::tokens::typeStringFromToken(mType); }
    inline const std::string tokenname() const {
        return this->typestr() +
            this->symbolseparator() +
            this->name();
    }
    //
    static inline char symbolseparator() { return '$'; }
    static inline std::string
    tokenFromNameType(const std::string& name, const tokens::CoreType type) {
        return ast::tokens::typeStringFromToken(type) +
            ExternalVariable::symbolseparator() + name;
    }
    static inline bool
    nametypeFromToken(const std::string& token, std::string* name, std::string* type) {
        const size_t at = token.find(symbolseparator());
        if (at == std::string::npos) return false;
        if (type) {
            *type = token.substr(0, at);
            if (type->empty()) {
                *type = ast::tokens::typeStringFromToken(tokens::CoreType::FLOAT);
            }
        }
        if (name) *name = token.substr(at + 1, token.size());
        return true;
    }

private:
    const tokens::CoreType mType;
};

struct DeclareLocal : public Variable
{
    using UniquePtr = std::unique_ptr<DeclareLocal>;

    DeclareLocal(const std::string& name, const tokens::CoreType type)
        : Variable(name)
        , mType(type) {}
    DeclareLocal(const DeclareLocal& other)
        : Variable(other)
        , mType(other.mType) {}
    ~DeclareLocal() override = default;

    DeclareLocal* copy() const override final { return new DeclareLocal(*this); }
    NodeType nodetype() const override { return Node::DeclareLocalNode; }
    const char* nodename() const override { return "declaration"; }
    const char* subname() const override { return "dcl"; }
    //
    inline tokens::CoreType type() const { return mType; }
    inline std::string typestr() const { return ast::tokens::typeStringFromToken(mType); }
private:
    const tokens::CoreType mType;
};

struct Local : public Variable
{
    using UniquePtr = std::unique_ptr<Local>;

    Local(const std::string& name)
        : Variable(name) {}
    ~Local() override = default;

    Local* copy() const override final { return new Local(*this); }
    NodeType nodetype() const override { return Node::LocalNode; }
    const char* nodename() const override { return "local"; }
    const char* subname() const override { return "lcl"; }
};

struct ArrayUnpack : public Expression
{
    using UniquePtr = std::unique_ptr<ArrayUnpack>;

    ArrayUnpack(Expression* expression,
        Expression* component0,
        Expression* component1 = nullptr)
        : Expression()
        , mComponents(new ExpressionList())
        , mExpression(expression) {
            assert(component0);
            assert(mExpression);
            mComponents->addExpression(component0);
            mComponents->addExpression(component1);
            mExpression->setParent(this);
            mComponents->setParent(this);
        }
    ArrayUnpack(const ArrayUnpack& other)
        : mComponents(other.mComponents->copy())
        , mExpression(other.mExpression->copy()) {
            mExpression->setParent(this);
            mComponents->setParent(this);
        }
    ~ArrayUnpack() override = default;

    ArrayUnpack* copy() const override final { return new ArrayUnpack(*this); }
    NodeType nodetype() const override { return Node::ArrayUnpackNode; }
    const char* nodename() const override { return "array unpack"; }
    const char* subname() const override { return "unpk"; }
    //
    size_t children() const override final { return 2; }
    const Statement* child(const size_t i) const override final {
        if (i == 0) return this->components();
        if (i == 1) return this->expression();
        return nullptr;
    }
    //
    inline bool isMatrixIndex() const {
        // assumes that component0 is always valid
        return static_cast<bool>(this->component1());
    }
    inline const Expression* component0() const { return mComponents->child(0); }
    inline const Expression* component1() const { return mComponents->child(1); }
    inline const ExpressionList* components() const { return mComponents.get(); }
    inline const Expression* expression() const { return mExpression.get(); }

    inline bool replacechild(const size_t i, Node* node) override final {
        if (i > 1) return false;
        if (i == 0) {
            ExpressionList* exprl = dynamic_cast<ExpressionList*>(node);
            if (!exprl) return false;
            mComponents.reset(exprl);
            mComponents->setParent(this);
        }
        else if (i == 1) {
            Expression* expr = dynamic_cast<Expression*>(node);
            if (!expr) return false;
            mExpression.reset(expr);
            mExpression->setParent(this);
        }
        return true;
    }

private:
    ExpressionList::UniquePtr mComponents;
    Expression::UniquePtr mExpression;
};

struct ArrayPack : public Expression
{
    using UniquePtr = std::unique_ptr<ArrayPack>;

    ArrayPack(ExpressionList* arguments)
        : Expression()
        , mArguments(arguments) {
            assert(mArguments);
            mArguments->setParent(this);
        }
    ArrayPack(const ArrayPack& other)
        : mArguments(new ExpressionList(*other.mArguments)) {
            mArguments->setParent(this);
        }
    ~ArrayPack() override = default;

    ArrayPack* copy() const override final { return new ArrayPack(*this); }
    NodeType nodetype() const override { return Node::ArrayPackNode; }
    const char* nodename() const override { return "array pack"; }
    const char* subname() const override { return "pack"; }
    //
    size_t children() const override final { return 1; }
    const ExpressionList* child(const size_t i) const override final {
        if (i == 0) return this->args();
        return nullptr;
    }
    //
    inline size_t numArgs() const { return mArguments->size(); }
    const ExpressionList* args() const { return mArguments.get(); }

    inline bool replacechild(const size_t i, Node* node) override final {
        if (i != 0) return false;
        ExpressionList* exprl = dynamic_cast<ExpressionList*>(node);
        if (!exprl) return false;
        mArguments.reset(exprl);
        mArguments->setParent(this);
        return true;
    }

private:
    ExpressionList::UniquePtr mArguments;
};

// ValueBases are a base class for anything that holds a value
// Derived classes store the actual typed values
struct ValueBase : public Expression
{
    ~ValueBase() override = default;
};

template <typename T>
struct Value : public ValueBase
{
    using UniquePtr = std::unique_ptr<Value<T>>;

    using Type = T;
    using LiteralLimitsT = LiteralLimits<Type>;
    using ContainerType = typename LiteralLimitsT::ContainerT;

    static constexpr bool IsSupported =
        std::is_same<T, bool>::value ||
        std::is_same<T, int16_t>::value ||
        std::is_same<T, int32_t>::value ||
        std::is_same<T, int64_t>::value ||
        std::is_same<T, float>::value ||
        std::is_same<T, double>::value;
    static_assert(IsSupported, "Incompatible ast::Value node instantiated.");

    /// @note   Value literals are always positive (negation is performed
    ///         as a unary operation)
    /// @brief  Literals store their value as ContainerType, which is guaranteed
    ///         to be at least large enough to represent the maximum possible
    ///         supported type for the requested precision.

    Value(const std::string number)
        : mValue(LiteralLimitsT::onLimitOverflow())
        , mText(nullptr) {
            try {
                mValue = LiteralLimitsT::convert(number);
            }
            catch (std::out_of_range&) {
                mText.reset(new std::string(number));
            }
        }
    Value(const ContainerType value)
        : mValue(value), mText(nullptr) {}

    Value(const Value<T>& other)
        : mValue(other.mValue)
        , mText(other.mText ? new std::string(*other.mText) : nullptr) {}
    ~Value() override = default;

    Value<Type>* copy() const override final { return new Value<Type>(*this); }
    NodeType nodetype() const override {
        if (std::is_same<T, bool>::value)    return Node::ValueBoolNode;
        if (std::is_same<T, int16_t>::value) return Node::ValueInt16Node;
        if (std::is_same<T, int32_t>::value) return Node::ValueInt32Node;
        if (std::is_same<T, int64_t>::value) return Node::ValueInt64Node;
        if (std::is_same<T, float>::value)   return Node::ValueFloatNode;
        if (std::is_same<T, double>::value)  return Node::ValueDoubleNode;
    }
    const char* nodename() const override {
        if (std::is_same<T, bool>::value)    return "boolean literal";
        if (std::is_same<T, int16_t>::value) return "short (16bit) literal";
        if (std::is_same<T, int32_t>::value) return "integer (32bit) literal";
        if (std::is_same<T, int64_t>::value) return "long (64bit) literal";
        if (std::is_same<T, float>::value)   return "float (32bit) literal";
        if (std::is_same<T, double>::value)  return "double (64bit) literal";
    }
    const char* subname() const override {
        if (std::is_same<T, bool>::value)    return "bool";
        if (std::is_same<T, int16_t>::value) return "shrt";
        if (std::is_same<T, int32_t>::value) return "int";
        if (std::is_same<T, int64_t>::value) return "long";
        if (std::is_same<T, float>::value)   return "flt";
        if (std::is_same<T, double>::value)  return "dble";
    }
    //
    size_t children() const override final { return 0; }
    const Node* child(const size_t) const override final { return nullptr; }
    //
    inline bool overflow() const { return static_cast<bool>(this->text()); }
    inline const std::string* text() const { return mText.get(); }
    inline ContainerType asContainerType() const { return mValue; }
    inline T value() const { return static_cast<T>(mValue); }

private:
    // A container of a max size defined by LiteralValueContainer to hold values
    // which may be out of scope. This is only used for warnings
    ContainerType mValue;
    // The original string representation of the variable used for warnings if
    // it's unable to be represented (usually due to overflow)
    std::unique_ptr<std::string> mText;
};

template <>
struct Value<std::string> : public ValueBase
{
    using UniquePtr = std::unique_ptr<Value<std::string>>;

    using Type = std::string;
    Value(const Type& value) : mValue(value) {}
    Value(const Value<Type>& other) : mValue(other.mValue) {}
    ~Value() override = default;

    Value<Type>* copy() const override final { return new Value<Type>(*this); }
    NodeType nodetype() const override { return Node::ValueStrNode; }
    const char* nodename() const override { return "string value"; }
    const char* subname() const override { return "str"; }
    //
    size_t children() const override final { return 0; }
    const Node* child(const size_t) const override final { return nullptr; }
    //
    inline const std::string& value() const { return mValue; }

private:
    const Type mValue;
};

} // namespace ast
} // namespace ax

}
} // namespace openvdb

extern FILE* yyin;
extern int yyparse(openvdb::ax::ast::Tree** tree);

#endif // OPENVDB_AX_AST_HAS_BEEN_INCLUDED

// Copyright (c) 2015-2019 DNEG
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
