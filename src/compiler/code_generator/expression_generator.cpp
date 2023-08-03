#include "error_printer.h"
#include "generator.h"

CodeFiles CodeGenerator::generate(const asg::Expression &node) {
    // for (auto name : names)
    // std::cout << name.first << ":" << name.second << ", ";
    // std::cout << std::endl;

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
    CodeFiles elem;
    CodeFiles res = template_manager.get("expressions");
    // std::cout << "expressions" << std::endl;
    res.apply(names);
    res.remove_optional_slots_from_filenames();

    for (auto &expr : node.exprs) {
        elem = template_manager.get("expressions_elem");
        // std::cout << "expressions_elem" << std::endl;
        elem.apply(names);
        elem.apply("value", generate(expr));
        elem.remove_optional_slots_from_filenames();

        res.apply("expression_elem", elem);
    }

    return res;
}

CodeFiles CodeGenerator::generate(const asg::Assigment &node) {
    CodeFiles res = template_manager.get("assigment");
    // std::cout << "assigment" << std::endl;
    res.apply(names);
    res.remove_optional_slots_from_filenames();

    res.apply("target", node.target.toString());
    res.apply("value", generate(node.value));

    return res;
}

CodeFiles CodeGenerator::generate(const asg::KeywordMessage &node) {
    CodeFiles arg;
    CodeFiles res = template_manager.get("keyword_message");
    // std::cout << "keyword_message" << std::endl;
    res.apply(names);
    res.remove_optional_slots_from_filenames();
    res.apply("message_selector", node.selector.toString());
    res.apply("reciever", generate(node.recv));

    for (auto &argument : node.arguments) {
        arg = template_manager.get("keyword_message_argument");
        // std::cout << "keyword_message_argument" << std::endl;
        arg.apply(names);
        arg.apply("expression", generate(argument));
        res.apply("argument", arg);
    }

    return res;
}

CodeFiles CodeGenerator::generate(const asg::BinaryMessage &node) {
    CodeFiles res;
    std::string template_name;

    switch (node.selector) {
    case tokenAdd:
        template_name = "add";
        break;
    case tokenSub:
        template_name = "sub";
        break;
    case tokenIDiv:
        template_name = "idiv";
        break;
    case tokenMul:
        template_name = "mul";
        break;
    case tokenEq:
        template_name = "eq";
        break;
    case tokenNotEq:
        template_name = "neq";
        break;
    case tokenEqIdentity:
        template_name = "eq_identity";
        break;
    case tokenNotEqIdentity:
        template_name = "neq_identity";
        break;
    case tokenLess:
        template_name = "lt";
        break;
    case tokenGreater:
        template_name = "gt";
        break;
    case tokenLessEq:
        template_name = "lte";
        break;
    case tokenGreaterEq:
        template_name = "gte";
        break;
    case tokenAnd:
        template_name = "and";
        break;
    case tokenOr:
        template_name = "or";
        break;
    case tokenMod:
        template_name = "mod";
        break;
    case tokenDiv:
        template_name = "div";
        break;
    default:
        internal_error("Not implemented");
    }

    res = template_manager.get(template_name);
    res.apply(names);
    // std::cout << template_name << std::endl;
    res.remove_optional_slots_from_filenames();
    res.apply({
        {"reciever", generate(node.recv)},
        {"argument", generate(node.argument)},
    });

    return res;
}

CodeFiles CodeGenerator::generate(const asg::UnaryMessage &node) {
    CodeFiles res = template_manager.get("unary_message");
    // std::cout << "unary_message" << std::endl;
    res.apply(names);
    res.remove_optional_slots_from_filenames();
    res.apply("message_selector", node.selector.toString());
    res.apply("reciever", generate(node.recv));
    return res;
}

CodeFiles CodeGenerator::generate(const asg::Literal &node) {
    CodeFiles res;
    std::string template_name;
    std::string value;

    switch (node.type) {
    case tokenChar:
        template_name = "character";
        value = node.value.character.toString();
        break;
    case tokenFloat:
        template_name = "float";
        value = node.value.float_number.toString();
        break;
    case tokenInteger:
        template_name = "integer";
        value = node.value.integer_number.toString();
        break;
    case tokenSymbol:
        template_name = "symbol";
        value = node.value.symbol.toString();
        break;
    case tokenString:
        template_name = "string";
        value = node.value.string.toString();
        break;
    case tokenTrue:
        template_name = "true";
        break;
    case tokenFalse:
        template_name = "false";
        break;
    case tokenNil:
        template_name = "nil";
        break;

    default:
        internal_error("Not implemented %d", (int)node.type);
    }

    res = template_manager.get(template_name);
    res.apply(names);
    // std::cout << template_name << std::endl;
    res.remove_optional_slots_from_filenames();
    res.apply("value", value);

    return res;
}

CodeFiles CodeGenerator::generate(const asg::Variable &node) {
    CodeFiles res = template_manager.get("variable");
    // std::cout << "variable" << std::endl;
    res.apply(names);
    res.remove_optional_slots_from_filenames();
    res.apply("identifier", node.id.toString());

    return res;
}

CodeFiles CodeGenerator::generate(const asg::ClassRef &node) {
    CodeFiles res = template_manager.get("class_ref");
    // std::cout << "class_ref" << std::endl;
    res.apply(names);
    res.remove_optional_slots_from_filenames();
    res.apply("identifier", node.id.toString());

    return res;
}

CodeFiles CodeGenerator::generate(const asg::Bracket &node) {
    CodeFiles res = template_manager.get("bracket");
    // std::cout << "bracket" << std::endl;
    res.apply(names);
    res.remove_optional_slots_from_filenames();
    res.apply("expression", generate(node.expr));

    return res;
}

CodeFiles CodeGenerator::generate(const asg::CodeBlock &node) {
    CodeFiles res = template_manager.get("code_block");
    // std::cout << "code_block" << std::endl;
    res.apply(names);
    res.remove_optional_slots_from_filenames();

    for (auto &temp : node.temps)
        res.apply("temporary", generate_method_argument(temp));

    for (auto &argument : node.arguments)
        res.apply("argument", generate_method_argument(argument));

    res.apply("expression", generate(node.expr));

    return res;
}

CodeFiles CodeGenerator::generate(const asg::ConstArray &node) {
    CodeFiles elem;
    CodeFiles res = template_manager.get("const_array");
    // std::cout << "const_array" << std::endl;
    res.apply(names);
    res.remove_optional_slots_from_filenames();

    for (auto &element : node.elements) {
        elem = template_manager.get("const_array_elem");
        // std::cout << "const_array_elem" << std::endl;
        elem.apply(names);
        elem.apply("expression", generate(element));
        res.apply("element", elem);
    }

    return res;
}
