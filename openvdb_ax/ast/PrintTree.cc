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

#include "PrintTree.h"

#include "AST.h"
#include "Tokens.h"
#include "Visitor.h"

#include <ostream>

namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {

namespace ax {
namespace ast {

struct PrintVisitor : public ast::Visitor<PrintVisitor>
{
    PrintVisitor(std::ostream& os,
        const bool numberStatements = true,
        const char* indent = "    ")
        : mOs(os)
        , mLevel(0)
        , mStatementNumber(numberStatements ? 0 : -1)
        , mIndent(indent) {}
    ~PrintVisitor() = default;

    using ast::Visitor<PrintVisitor>::traverse;
    using ast::Visitor<PrintVisitor>::visit;

    inline bool postOrderNodes() const { return false; }

    inline void indent() {
        for (int i(0); i < mLevel; ++i) mOs << mIndent;
    }

    bool traverse(NodeType<ast::StatementList>* stmntl) {
        this->visit(stmntl);

        const size_t children = stmntl->children();
        ++mLevel;
        if (children == 0) {
            indent();
            mOs << "<empty>\n";
        }
        else {
            for (size_t i = 0; i < children; ++i) {
                indent();
                if (mStatementNumber >= 0) {
                    mOs << '[' << mStatementNumber++ << "] ";
                }
                this->derived().traverse(stmntl->child(i));
                mOs << '\n';
            }
        }
        --mLevel;
        return true;
    }

    bool traverse(NodeType<ast::Block>* block) {
        indent();
        this->visit(block);

        const size_t children = block->children();
        ++mLevel;
        if (children == 0) {
            indent();
            mOs << "<empty>\n";
        }
        else {
            for (size_t i = 0; i < children; ++i) {
                indent();
                if (mStatementNumber >= 0) {
                    mOs << '[' << mStatementNumber++ << "] ";
                }
                this->derived().traverse(block->child(i));
                mOs << '\n';
            }
        }
        --mLevel;
        return true;
    }

    bool traverse(NodeType<ast::ExpressionList>* exprl) {
        this->visit(exprl);
        const size_t children = exprl->children();
        ++mLevel;
        if (children == 0) {
            indent();
            mOs << "<empty>\n";
        }
        else {
            for (size_t i = 0; i < children; ++i) {
                indent();
                this->derived().traverse(exprl->child(i));
            }
        }
        --mLevel;
        return true;
    }

    bool traverse(NodeType<ast::ConditionalStatement>* cond) {
        this->visit(cond);
        ++mLevel;

        indent();
        mOs << "condition:\n";

        ++mLevel;
        indent();
        this->traverse(cond->condition());
        --mLevel;

        indent();
        mOs << "branch [then]:\n";

        this->traverse(cond->thenBranch());

        if (cond->hasElseBranch()) {
            indent();
            mOs << "branch [else]:\n";

            this->traverse(cond->elseBranch());
        }
        --mLevel;
        return true;
    }

    bool traverse(NodeType<ast::Loop>* loop) {
        this->visit(loop);
        ++mLevel;

        if (loop->hasInit()) {
            indent();
            mOs << "init:\n";

            ++mLevel;
            indent();
            this->traverse(loop->initial());
            --mLevel;
        }

        indent();
        mOs << "conditional:\n";

        ++mLevel;
        indent();
        this->traverse(loop->condition());
        --mLevel;

        if (loop->hasIter()) {
            indent();
            mOs << "iterator:\n";
            ++mLevel;
            indent();
            this->traverse(loop->iteration());
            --mLevel;
        }

        indent();
        mOs << "body:\n";
        this->traverse(loop->body());

        --mLevel;
        return true;
    }

    bool traverse(const ast::AssignExpression* asgn) {
        this->visit(asgn);
        ++mLevel;
        indent();
        this->traverse(asgn->lhs());
        indent();
        this->traverse(asgn->rhs());
        --mLevel;
        return true;
    }

    bool traverse(NodeType<ast::Crement>* crmt) {
        this->visit(crmt);
        ++mLevel;
        indent();
        this->traverse(crmt->expression());
        --mLevel;
        return true;
    }

    bool traverse(NodeType<ast::UnaryOperator>* unry) {
        this->visit(unry);
        ++mLevel;
        indent();
        this->traverse(unry->expression());
        --mLevel;
        return true;
    }

    bool traverse(const ast::BinaryOperator* bin) {
        this->visit(bin);
        ++mLevel;
        indent();
        this->traverse(bin->lhs());
        indent();
        this->traverse(bin->rhs());
        --mLevel;
        return true;
    }

    bool traverse(NodeType<ast::Cast>* cast) {
        this->visit(cast);
        ++mLevel;
        indent();
        this->traverse(cast->expression());
        --mLevel;
        return true;
    }

    bool traverse(NodeType<ast::FunctionCall>* call) {
        this->visit(call);
        ++mLevel;
        indent();
        this->traverse(call->args());
        --mLevel;
        return true;
    }

    bool traverse(NodeType<ast::ArrayPack>* pack) {
        this->visit(pack);
        ++mLevel;
        indent();
        this->derived().traverse(pack->args());
        --mLevel;
        return true;
    }

    bool traverse(NodeType<ast::ArrayUnpack>* pack) {
        this->visit(pack);
        ++mLevel;
        indent();
        mOs << "expression: ";
        this->traverse(pack->expression());
        indent();
        mOs << "component(s) : ";
        this->traverse(pack->components());
        --mLevel;
        return true;
    }

    bool visit(const ast::StatementList* node);
    bool visit(const ast::Block* node);
    bool visit(const ast::ConditionalStatement* node);
    bool visit(const ast::Loop* node);
    bool visit(const ast::Keyword* node);
    bool visit(const ast::AssignExpression* node);
    bool visit(const ast::Crement* node);
    bool visit(const ast::ExpressionList* node);
    bool visit(const ast::UnaryOperator* node);
    bool visit(const ast::BinaryOperator* node);
    bool visit(const ast::Cast* node);
    bool visit(const ast::FunctionCall* node);
    bool visit(const ast::Attribute* node);
    bool visit(const ast::ExternalVariable* node);
    bool visit(const ast::DeclareLocal* node);
    bool visit(const ast::Local* node);
    bool visit(const ast::ArrayUnpack* node);
    bool visit(const ast::ArrayPack* node);

    bool visit(const ast::Value<bool>* node) {
        return this->visitValue(node);
    }
    bool visit(const ast::Value<int16_t>* node) {
        return this->visitValue(node);
    }
    bool visit(const ast::Value<int32_t>* node) {
        return this->visitValue(node);
    }
    bool visit(const ast::Value<int64_t>* node) {
        return this->visitValue(node);
    }
    bool visit(const ast::Value<float>* node) {
        return this->visitValue(node);
    }
    bool visit(const ast::Value<double>* node) {
        return this->visitValue(node);
    }
    bool visit(const ast::Value<std::string>* node) {
        return this->visitValue(node);
    }

protected:
    template <typename T>
    bool visitValue(const ast::Value<T>* node);

private:
    std::ostream& mOs;
    int mLevel;
    int64_t mStatementNumber;
    const char* mIndent;
};

bool PrintVisitor::visit(const ast::StatementList* node)
{
    mOs << node->nodename() << ": " << node->size() << " statement(s)" << '\n';
    return true;
}


bool PrintVisitor::visit(const ast::Block* node)
{
    mOs << node->nodename() << ": " << node->size() << " statement(s)" << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::ConditionalStatement* node)
{
    mOs << node->nodename() << ": " << (node->hasElseBranch() ? "two branches " : "one branch") << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::AssignExpression* node)
{
    mOs << node->nodename() << ": " << tokens::operatorNameFromToken(node->operation()) << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::Loop* node)
{
    mOs << tokens::loopNameFromToken(node->loopType()) <<" "<< node->nodename() << ": " << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::Keyword* node)
{
    mOs << node->nodename() << ": " << tokens::keywordNameFromToken(node->keyword()) << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::Crement* node)
{
    mOs << node->nodename() << ':';
    if (node->post()) mOs << " post-";
    else              mOs << " pre-";
    if (node->increment()) mOs << "increment ";
    else                   mOs << "decrement ";
    mOs << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::ExpressionList* node)
{
    mOs << node->nodename() << ": " << node->size() << " element(s)" << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::UnaryOperator* node)
{
    mOs << node->nodename() << ": " <<  tokens::operatorNameFromToken(node->operation()) << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::BinaryOperator* node)
{
    mOs << node->nodename() << ": " <<  tokens::operatorNameFromToken(node->operation()) << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::Cast* node)
{
    mOs << node->nodename() << ": " << tokens::typeStringFromToken(node->type()) << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::FunctionCall* node)
{
    mOs << node->nodename() << ": " << node->name() << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::Attribute* node)
{
    mOs << node->nodename() << ": " << node->symbolseparator()
        << '(' << node->typestr() << (node->inferred() ? " - inferred": "")
        << ") " << node->name() << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::DeclareLocal* node)
{
    mOs << node->nodename() << ": (" <<  node->typestr() << ") " << node->name() << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::Local* node)
{
    mOs << node->nodename() << ' ' << node->name() << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::ArrayUnpack* node)
{
    mOs << node->nodename() << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::ArrayPack* node)
{
    mOs << node->nodename() << ": " << node->numArgs() << " element(s)" << '\n';
    return true;
}

bool PrintVisitor::visit(const ast::ExternalVariable* node)
{
    mOs << node->nodename() << ": " << node->symbolseparator()
        << '(' << node->typestr() << ") " << node->name() << '\n';
    return true;
}

template <typename T>
bool PrintVisitor::visitValue(const ast::Value<T>* node)
{
    mOs << node->nodename() << ": " << node->value() << '\n';
    return true;
}


////////////////////////////////////////////////////////////////////////////////


void print(const ast::Node& node,
    const bool numberStatements,
    std::ostream& os,
    const char* indent)
{
    PrintVisitor visitor(os, numberStatements, indent);
    visitor.traverse(&node);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct ReprintVisitor : public ast::Visitor<ReprintVisitor>
{
    ReprintVisitor(std::ostream& os, const char* indent = "    ")
        : mOs(os)
        , mLevel(0)
        , mIndent(indent) {}
    ~ReprintVisitor() = default;

    using ast::Visitor<ReprintVisitor>::traverse;
    using ast::Visitor<ReprintVisitor>::visit;

    inline bool postOrderNodes() const { return false; }

    inline void indent() {
        for (int i = 0; i < mLevel; ++i) mOs << mIndent;
    }

    bool traverse(NodeType<ast::Block>* block) {
        const size_t children = block->children();
        mOs << '\n';
        indent();
        mOs << '{' << '\n';
        ++mLevel;
        for (size_t i = 0; i < children; ++i) {
            indent();
            this->derived().traverse(block->child(i));
            if (block->child(i)->nodetype() !=
                ast::Node::ConditionalStatementNode) {
                mOs << ';' << '\n';
            }
        }
        --mLevel;
        indent();
        mOs << '}' << '\n';
        return true;
    }

    bool traverse(NodeType<ast::StatementList>* stmtl) {
        const size_t children = stmtl->children();
        for (size_t i = 0; i < children; ++i) {
            this->derived().traverse(stmtl->child(i));
            if (i != children-1) mOs << ';' << ' ';
        }
        return true;
    }

    bool traverse(NodeType<ast::ExpressionList>* exprl) {
        const size_t children = exprl->children();
        for (size_t i = 0; i < children; ++i) {
            this->derived().traverse(exprl->child(i));
            if (i != children-1) mOs << ',' << ' ';
        }
        return true;
    }

    bool traverse(NodeType<ast::ConditionalStatement>* cond) {
        mOs << "if (";
        this->traverse(cond->condition());
        mOs << ')';
        this->traverse(cond->thenBranch());
        indent();

        if (cond->hasElseBranch()) {
            mOs << "else";
            this->traverse(cond->elseBranch());
        }
        return true;
    }

    bool traverse(NodeType<ast::Loop>* loop) {
        const ast::tokens::LoopToken loopType = loop->loopType();
        if (loopType == ast::tokens::LoopToken::FOR) {
            mOs << "for (";
            if (loop->hasInit()) this->traverse(loop->initial());
            mOs <<"; ";
            this->traverse(loop->condition());
            mOs <<"; ";
            if (loop->hasIter()) this->traverse(loop->iteration());
            mOs<<")";
            this->traverse(loop->body());
        }
        else if (loopType == ast::tokens::LoopToken::DO) {
            mOs << "do";
            this->traverse(loop->body());
            indent();
            mOs <<"while (";
            this->traverse(loop->condition());
            mOs <<")";
        }
        else  {
            mOs <<"while (";
            this->traverse(loop->condition());
            mOs <<")";
            this->traverse(loop->body());
        }
        return true;
    }

    bool traverse(const ast::AssignExpression* asgn) {
        this->traverse(asgn->lhs());
        this->visit(asgn);
        if (!asgn->isCompound()) {
            this->traverse(asgn->rhs());
        }
        else {
            // For compound assignments, don't traverse the left hand side
            // of the right hand side of the binary expression. i.e:
            // a += 5;  ->  a = a + 5;  ->  traverse(a) = <ignore> + traverse(5)
            const ast::BinaryOperator* rhs =
                static_cast<const ast::BinaryOperator*>(asgn->rhs());
            this->traverse(rhs->rhs());
        }
        return true;
    }

    bool traverse(NodeType<ast::Crement>* crmt) {
        if (crmt->pre()) this->visit(crmt);
        this->traverse(crmt->expression());
        if (crmt->post()) this->visit(crmt);
        return true;
    }

    bool traverse(NodeType<ast::UnaryOperator>* unry) {
        this->visit(unry);
        this->traverse(unry->expression());
        return true;
    }

    bool traverse(const ast::BinaryOperator* bin) {
        // The AST currently doesn't store what expressions were encapsulated
        // by parenthesis and instead infers precedences from the token order
        // set out in the parser. This means that traversal determines precedence.
        // Unfortunately, statements like "a+b+c" and "a+(b+c)" both get re-printed
        // as "a+b+c". For now, every binary expression is encapsulated to
        // ensure the operation order is preserved, resulting in (a+(b+c)) for
        // the above example.
        mOs << '(';
        this->traverse(bin->lhs());
        this->visit(bin);
        this->traverse(bin->rhs());
        mOs << ')';
        return true;
    }

    bool traverse(NodeType<ast::Cast>* cast) {
        this->visit(cast);
        mOs << '(';
        this->traverse(cast->expression());
        mOs << ')';
        return true;
    }

    bool traverse(NodeType<ast::FunctionCall>* call) {
        this->visit(call);
        mOs << '(';
        this->traverse(call->args());
        mOs << ')';
        return true;
    }

    bool traverse(NodeType<ast::ArrayPack>* pack) {
        mOs << '{';
        this->traverse(pack->args());
        mOs << '}';
        return true;
    }

    bool traverse(NodeType<ast::ArrayUnpack>* pack) {
        this->traverse(pack->expression());
        mOs << '[';
        this->traverse(pack->components());
        mOs << ']';
        return true;
    }

    bool visit(const ast::AssignExpression* node);
    bool visit(const ast::Crement* node);
    bool visit(const ast::UnaryOperator* node);
    bool visit(const ast::BinaryOperator* node);
    bool visit(const ast::Cast* node);
    bool visit(const ast::FunctionCall* node);
    bool visit(const ast::Attribute* node);
    bool visit(const ast::ExternalVariable* node);
    bool visit(const ast::DeclareLocal* node);
    bool visit(const ast::Local* node);
    bool visit(const ast::Keyword* node);

    bool visit(const ast::Value<bool>* node) {
        return this->visitValue(node);
    }
    bool visit(const ast::Value<int16_t>* node) {
        return this->visitValue(node);
    }
    bool visit(const ast::Value<int32_t>* node) {
        return this->visitValue(node);
    }
    bool visit(const ast::Value<int64_t>* node) {
        return this->visitValue(node);
    }
    bool visit(const ast::Value<float>* node) {
        return this->visitValue(node);
    }
    bool visit(const ast::Value<double>* node) {
        return this->visitValue(node);
    }
    bool visit(const ast::Value<std::string>* node) {
        return this->visitValue(node);
    }

protected:
    template <typename T>
    bool visitValue(const ast::Value<T>* node);
private:
    std::ostream& mOs;
    int mLevel;
    const char* mIndent;
};


bool ReprintVisitor::visit(const ast::AssignExpression* node)
{
    mOs << ' ' << tokens::operatorNameFromToken(node->operation()) << ' ';
    return true;
}

bool ReprintVisitor::visit(const ast::Crement* node)
{
    if (node->increment()) mOs << "++";
    if (node->decrement()) mOs << "--";
    return true;
}

bool ReprintVisitor::visit(const ast::UnaryOperator* node)
{
    mOs << tokens::operatorNameFromToken(node->operation());
    return true;
}

bool ReprintVisitor::visit(const ast::BinaryOperator* node)
{
    mOs << ' ' << tokens::operatorNameFromToken(node->operation()) << ' ';
    return true;
}

bool ReprintVisitor::visit(const ast::Cast* node)
{
    mOs << node->typestr();
    return true;
}

bool ReprintVisitor::visit(const ast::FunctionCall* node)
{
    mOs << node->name();
    return true;
}

bool ReprintVisitor::visit(const ast::Attribute* node)
{
    mOs << node->typestr() << node->symbolseparator() << node->name();
    return true;
}

bool ReprintVisitor::visit(const ast::DeclareLocal* node)
{
    mOs << node->typestr() << ' ' << node->name();
    return true;
}

bool ReprintVisitor::visit(const ast::Local* node)
{
    mOs << node->name();
    return true;
}

bool ReprintVisitor::visit(const ast::Keyword* node)
{
    mOs << tokens::keywordNameFromToken(node->keyword());
    return true;
}

bool ReprintVisitor::visit(const ast::ExternalVariable* node)
{
    mOs << node->typestr() << node->symbolseparator() << node->name();
    return true;
}

template <typename T>
bool ReprintVisitor::visitValue(const ast::Value<T>* node)
{
    if (std::is_same<T, bool>::value) mOs << std::boolalpha;
    if (std::is_same<T, std::string>::value) mOs << '"';
    mOs << node->value();
    if (std::is_same<T, bool>::value) mOs << std::noboolalpha;
    if (std::is_same<T, std::string>::value) mOs << '"';
    if (std::is_same<T, int16_t>::value) mOs << 's';
    if (std::is_same<T, int64_t>::value) mOs << 'l';
    if (std::is_same<T, float>::value)   mOs << 'f';
    return true;
}

////////////////////////////////////////////////////////////////////////////////


void reprint(const ast::Node& node, std::ostream& os, const char* indent)
{
    ReprintVisitor visitor(os, indent);
    visitor.traverse(&node);
}


} // namespace ast
} // namespace ax

}
} // namespace openvdb

// Copyright (c) 2015-2020 DNEG
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )

