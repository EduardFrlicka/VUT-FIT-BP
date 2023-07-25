#include "error_printer.h"
#include "generator.h"

CodeFiles CodeGenerator::generate(const asg::Expression &node) {
    if (node.is_type<asg::Expressions>())
        return generate(node.get<asg::Expressions>());
    if (node.is_type<asg::Assigment>())
        return generate(node.get<asg::Assigment>());
    if (node.is_type<asg::KeywordMessage>())
        return generate(node.get<asg::KeywordMessage>());
    if (node.is_type<asg::BinaryMessage>())
        return generate(node.get<asg::BinaryMessage>());
    if (node.is_type<asg::UnaryMessage>())
        return generate(node.get<asg::UnaryMessage>());
    if (node.is_type<asg::Literal>())
        return generate(node.get<asg::Literal>());
    if (node.is_type<asg::Variable>())
        return generate(node.get<asg::Variable>());
    if (node.is_type<asg::ClassRef>())
        return generate(node.get<asg::ClassRef>());
    if (node.is_type<asg::Bracket>())
        return generate(node.get<asg::Bracket>());
    if (node.is_type<asg::CodeBlock>())
        return generate(node.get<asg::CodeBlock>());
    if (node.is_type<asg::ConstArray>())
        return generate(node.get<asg::ConstArray>());

    internal_error("Not implemented");
}

CodeFiles CodeGenerator::generate(const asg::Expressions &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    for (auto &expr : node.exprs)
        res.apply("expression", generate(expr));

    return res;
}

CodeFiles CodeGenerator::generate(const asg::Assigment &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    /* TODO variable declaration */

    return res;
}

CodeFiles CodeGenerator::generate(const asg::KeywordMessage &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    return res;
}

CodeFiles CodeGenerator::generate(const asg::BinaryMessage &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    return res;
}

CodeFiles CodeGenerator::generate(const asg::UnaryMessage &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    return res;
}

CodeFiles CodeGenerator::generate(const asg::Literal &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    return res;
}

CodeFiles CodeGenerator::generate(const asg::Variable &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    return res;
}

CodeFiles CodeGenerator::generate(const asg::ClassRef &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    return res;
}

CodeFiles CodeGenerator::generate(const asg::Bracket &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    return res;
}

CodeFiles CodeGenerator::generate(const asg::CodeBlock &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    return res;
}

CodeFiles CodeGenerator::generate(const asg::ConstArray &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    return res;
}
