#include "semantic_expression_graph.h"

AbstractSemanticGraph::Expression::Expression() {
    value = nullptr;
};

AbstractSemanticGraph::Expression::Expression(const Expressions &_val) {
    value = std::make_shared<ExprVariant>(ExprVariant(_val));
};

AbstractSemanticGraph::Expression::Expression(const Assigment &_val) {
    value = std::make_shared<ExprVariant>(ExprVariant(_val));
};

AbstractSemanticGraph::Expression::Expression(const KeywordMessage &_val) {
    value = std::make_shared<ExprVariant>(ExprVariant(_val));
};

AbstractSemanticGraph::Expression::Expression(const BinaryMessage &_val) {
    value = std::make_shared<ExprVariant>(ExprVariant(_val));
};

AbstractSemanticGraph::Expression::Expression(const UnaryMessage &_val) {
    value = std::make_shared<ExprVariant>(ExprVariant(_val));
};

AbstractSemanticGraph::Expression::Expression(const Literal &_val) {
    value = std::make_shared<ExprVariant>(ExprVariant(_val));
};

AbstractSemanticGraph::Expression::Expression(const Variable &_val) {
    value = std::make_shared<ExprVariant>(ExprVariant(_val));
};

AbstractSemanticGraph::Expression::Expression(const ClassRef &_val) {
    value = std::make_shared<ExprVariant>(ExprVariant(_val));
};

AbstractSemanticGraph::Expression::Expression(const Bracket &_val) {
    value = std::make_shared<ExprVariant>(ExprVariant(_val));
};

AbstractSemanticGraph::Expression::Expression(const CodeBlock &_val) {
    value = std::make_shared<ExprVariant>(ExprVariant(_val));
};

AbstractSemanticGraph::Expression::Expression(const ConstArray &_val) {
    value = std::make_shared<ExprVariant>(ExprVariant(_val));
};

AbstractSemanticGraph::Expressions::Expressions(){};

AbstractSemanticGraph::Expressions::Expressions(const std::deque<Expression> &_exprs) : exprs(_exprs){};

AbstractSemanticGraph::Variable::Variable(){};

AbstractSemanticGraph::Variable::Variable(const Identifier &_id) : id(_id){};

AbstractSemanticGraph::ClassRef::ClassRef(){};

AbstractSemanticGraph::ClassRef::ClassRef(const Identifier &_id) : id(_id){};

AbstractSemanticGraph::Bracket::Bracket(){};

AbstractSemanticGraph::Bracket::Bracket(const Expression &_expr) : expr(_expr){};

AbstractSemanticGraph::Literal::Literal(){};

AbstractSemanticGraph::Literal::Literal(TokenPayload _val) : value(_val){};
