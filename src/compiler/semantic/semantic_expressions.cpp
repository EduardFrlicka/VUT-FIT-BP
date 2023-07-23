#include "error_printer.h"
#include "semantic.h"

asg::Expression SemanticAnalyzer::analyze(const ast::Expression &node) {
    if (node.is_type<ast::ExpressionPair>())
        return analyze(node.get<ast::ExpressionPair>());

    if (node.is_type<ast::CascadeUnary>())
        return analyze(node.get<ast::CascadeUnary>());

    if (node.is_type<ast::CascadeBinary>())
        return analyze(node.get<ast::CascadeBinary>());

    if (node.is_type<ast::CascadeKeyWord>())
        return analyze(node.get<ast::CascadeKeyWord>());

    if (node.is_type<ast::ExpressionIdentifier>())
        return analyze(node.get<ast::ExpressionIdentifier>());

    if (node.is_type<ast::ExpressionValue>())
        return analyze(node.get<ast::ExpressionValue>());

    if (node.is_type<ast::ExpressionUnary>())
        return analyze(node.get<ast::ExpressionUnary>());

    if (node.is_type<ast::ExpressionBinary>())
        return analyze(node.get<ast::ExpressionBinary>());

    if (node.is_type<ast::ExpressionKeyWord>())
        return analyze(node.get<ast::ExpressionKeyWord>());

    if (node.is_type<ast::Assgiment>())
        return analyze(node.get<ast::Assgiment>());

    if (node.is_type<ast::Bracket>())
        return analyze(node.get<ast::Bracket>());

    if (node.is_type<ast::CodeBlock>())
        return analyze(node.get<ast::CodeBlock>());

    if (node.is_type<ast::ConstArray>())
        return analyze(node.get<ast::ConstArray>());

    internal_error("Unknown expression type");
}

asg::Expression SemanticAnalyzer::analyze(const ast::ExpressionPair &node) {
    asg::Expressions result_node;
    asg::Expression left;
    asg::Expression right;

    left = analyze(node.first);
    right = analyze(node.second);

    if (left.is_type<asg::Expressions>()) {
        const auto &exprs = left.get<asg::Expressions>().exprs;
        result_node.exprs.insert(result_node.exprs.end(), exprs.begin(), exprs.end());
    } else
        result_node.exprs.push_back(left);

    if (right.is_type<asg::Expressions>()) {
        const auto &exprs = right.get<asg::Expressions>().exprs;
        result_node.exprs.insert(result_node.exprs.end(), exprs.begin(), exprs.end());
    } else
        result_node.exprs.push_back(right);

    return result_node;
}

asg::Expression SemanticAnalyzer::analyze(const ast::CascadeUnary &node) {
    asg::UnaryMessage message;
    asg::Expression recv = analyze(node.recv);

    message.selector = Identifier(node.message_selector.payload.id);

    if (!node.recv.iscascade()) {
        message.recv = recv;
        return asg::Expressions({message});
    }

    auto exprs = recv.get<asg::Expressions>().exprs;

    if (exprs.back().is_type<asg::UnaryMessage>()) {
        message.recv = exprs.back().get<asg::UnaryMessage>().recv;
    }

    if (exprs.back().is_type<asg::BinaryMessage>()) {
        message.recv = exprs.back().get<asg::BinaryMessage>().recv;
    }

    if (exprs.back().is_type<asg::KeywordMessage>()) {
        message.recv = exprs.back().get<asg::KeywordMessage>().recv;
    }

    exprs.push_back(message);
    return asg::Expressions(exprs);
}

asg::Expression SemanticAnalyzer::analyze(const ast::CascadeBinary &node) {
    asg::BinaryMessage message;
    asg::Expression recv = analyze(node.recv);

    message.argument = analyze(node.argument);
    message.selector = node.message_selector.type;

    if (!node.recv.iscascade()) {
        message.recv = recv;
        return asg::Expressions({message});
    }

    auto exprs = recv.get<asg::Expressions>().exprs;

    if (exprs.back().is_type<asg::UnaryMessage>()) {
        message.recv = exprs.back().get<asg::UnaryMessage>().recv;
    }

    if (exprs.back().is_type<asg::BinaryMessage>()) {
        message.recv = exprs.back().get<asg::BinaryMessage>().recv;
    }

    if (exprs.back().is_type<asg::KeywordMessage>()) {
        message.recv = exprs.back().get<asg::KeywordMessage>().recv;
    }

    exprs.push_back(message);
    return asg::Expressions(exprs);
}

asg::Expression SemanticAnalyzer::analyze(const ast::CascadeKeyWord &node) {
    asg::KeywordMessage message;
    Identifier selector;
    asg::Expression recv = analyze(node.recv);

    for (auto i : node.selector) {
        selector = selector + i.payload.id;
    }

    for (auto i : node.arguments) {
        message.arguments.push_back(analyze(i));
    }

    message.selector = selector;

    if (!node.recv.iscascade()) {
        message.recv = recv;
        return asg::Expressions({message});
    }

    auto exprs = recv.get<asg::Expressions>().exprs;

    if (exprs.back().is_type<asg::UnaryMessage>()) {
        message.recv = exprs.back().get<asg::UnaryMessage>().recv;
    }

    if (exprs.back().is_type<asg::BinaryMessage>()) {
        message.recv = exprs.back().get<asg::BinaryMessage>().recv;
    }

    if (exprs.back().is_type<asg::KeywordMessage>()) {
        message.recv = exprs.back().get<asg::KeywordMessage>().recv;
    }

    exprs.push_back(message);
    return asg::Expressions(exprs);
}

asg::Expression SemanticAnalyzer::analyze(const ast::ExpressionIdentifier &node) {
    Identifier var;
    if (node.value.payload.id.is_upper()) {
        return asg::ClassRef(node.value.payload.id);
    }
    /* is variable */
    if (!variables.search(node.value.payload.id)) {
        res = ERR_SEMANTIC;
        error.undeclared_variable(node.value.it);
        return asg::Variable();
    }

    var = variables.get(node.value.payload.id);

    if (!var.defined) {
        error.undefined_variable(var, node.value.it);
        res = ERR_SEMANTIC;
    }

    return asg::Variable(var);
}

asg::Expression SemanticAnalyzer::analyze(const ast::ExpressionValue &node) {
    asg::Literal result_node;

    result_node.value = node.value.payload;

    return result_node;
}

asg::Expression SemanticAnalyzer::analyze(const ast::ExpressionUnary &node) {
    asg::UnaryMessage result_node;

    result_node.recv = analyze(node.recv);
    result_node.selector = Identifier(node.message_selector.payload.id);

    return result_node;
}

asg::Expression SemanticAnalyzer::analyze(const ast::ExpressionBinary &node) {
    asg::BinaryMessage result_node;

    result_node.recv = analyze(node.recv);
    result_node.selector = node.message_selector.type;
    result_node.argument = analyze(node.argument);

    return result_node;
}

asg::Expression SemanticAnalyzer::analyze(const ast::ExpressionKeyWord &node) {
    asg::KeywordMessage result_node;
    Identifier selector;

    for (auto i : node.selector) {
        selector = selector + i.payload.id;
    }

    for (auto i : node.arguments) {
        result_node.arguments.push_back(analyze(i));
    }

    result_node.recv = analyze(node.recv);
    result_node.selector = selector;

    return result_node;
}

asg::Expression SemanticAnalyzer::analyze(const ast::Assgiment &node) {
    Identifier var;
    asg::Assigment result_node;

    if (!node.target.payload.id.is_lower()) {
        error.expected_lower(node.target.it);
        res = ERR_SEMANTIC;
    }

    if (!variables.search(node.target.payload.id)) {
        var = Identifier(node.target.payload.id);
        var.declare_define(node.target.it);
        variables.push(var);
    }

    variables.get(node.target.payload.id).define(node.value.begin, node.value.end);
    result_node.target = variables.get(node.target.payload.id);

    result_node.value = analyze(node.value);

    return result_node;
}

asg::Expression SemanticAnalyzer::analyze(const ast::Bracket &node) {
    return asg::Bracket(analyze(node.expr));
}

asg::Expression SemanticAnalyzer::analyze(const ast::CodeBlock &node) {
    asg::CodeBlock result_node;
    Identifier var;
    variables.push_frame();

    for (auto variable : node.arguments) {
        if (!variable.payload.id.is_lower()) {
            error.expected_lower(variable.it);
            res = ERR_SEMANTIC;
        }

        if (variables.search(variable.payload.id)) {
            error.variable_redeclaration(variables.get(variable.payload.id), variable.it);
            res = ERR_SEMANTIC;
        }

        var = Identifier(variable.payload.id);
        var.declare_define(variable.it);
        variables.push(var);
        result_node.arguments.push_back(var);
    }

    for (auto variable : node.temps) {
        if (!variable.payload.id.is_lower()) {
            error.expected_lower(variable.it);
            res = ERR_SEMANTIC;
        }

        if (variables.search(variable.payload.id)) {
            error.variable_redeclaration(variables.get(variable.payload.id), variable.it);
            res = ERR_SEMANTIC;
        }

        var = Identifier(variable.payload.id);
        var.declare(variable.it);
        variables.push(var);
        result_node.temps.push_back(var);
    }

    result_node.expr = analyze(node.expr);

    variables.pop_frame();
    return result_node;
}

asg::Expression SemanticAnalyzer::analyze(const ast::ConstArray &node) {
    asg::ConstArray result_node;

    for (auto elem : node.elements) {
        result_node.elements.push_back(asg::Literal(elem.payload));
    }

    return result_node;
}
