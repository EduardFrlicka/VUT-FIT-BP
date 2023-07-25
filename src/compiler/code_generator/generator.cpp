#include "generator.h"
#include "error_printer.h"
#include <iostream>

CodeGenerator::CodeGenerator(const asg::Classes &root) : template_manager(args.compiler_templates_path) {
    CodeFiles static_files;
    CodeFiles result;

    result = generate(root);

    // static_files = load_static_code_files(args.static_templates_path);
    // result = static_files.combine({{"generated", result}});

    result.print();
}

CodeFiles CodeGenerator::generate(const asg::Classes &node) {
    CodeFiles res = template_manager.get("classes");
    res.apply({{"main", node.main.toString()}});

    for (auto i : node.classes)
        res.apply("class", generate(i));

    return res;
}

CodeFiles CodeGenerator::generate(const asg::Class &node) {
    CodeFiles res = template_manager.get("class");
    names["class_name"] = node.name.toString();
    names["base_class_name"] = node.base.toString();

    res.apply(names);

    if (node.object.has_value()) {
        res.apply("object", generate(*node.object));
    }

    for (auto &syn_port : node.syn_ports)
        res.apply("syn_port", generate(syn_port));

    for (auto &method : node.methods)
        res.apply("method", generate(method));

    for (auto &constructor : node.constructors)
        res.apply("constructor", generate(constructor));

    names.erase("class_name");
    names.erase("base_class_name");
    return res;
}

CodeFiles CodeGenerator::generate(const asg::Net &node) {
    CodeFiles res = template_manager.get("net");
    res.apply(names);

    for (auto &place : node.places)
        res.apply("place", generate(place));
    for (auto &transition : node.transitions)
        res.apply("transition", generate(transition));

    return res;
}

CodeFiles CodeGenerator::generate(const asg::Method &node) {
    CodeFiles res = template_manager.get("method");
    names["method_name"] = node.selector.toString();
    res.apply(names);

    for (auto &argument : node.arguments) {
        res.apply("argument", generate_argument(argument));
    }

    res.apply("net", generate(node.net));

    names.erase("method_name");
    return res;
}

CodeFiles CodeGenerator::generate(const asg::Constructor &node) {
    CodeFiles res = template_manager.get("constructor");
    names["method_name"] = node.selector.toString();
    res.apply(names);

    for (auto &argument : node.arguments) {
        res.apply("argument", generate_argument(argument));
    }

    res.apply("net", generate(node.net));

    names.erase("method_name");
    return res;
}

CodeFiles CodeGenerator::generate(const asg::SynPort &node) {
    CodeFiles res = template_manager.get("");
    names["syn_port_name"] = node.selector.toString();
    res.apply(names);

    for (auto &argument : node.arguments)
        res.apply("argument", generate_argument(argument));

    for (auto &pre_cond : node.pre_conds)
        res.apply("pre_cond", generate(pre_cond));

    for (auto &cond : node.conds)
        res.apply("cond", generate(cond));

    for (auto &post_cond : node.post_conds)
        res.apply("post_cond", generate(post_cond));

    if (node.guard.has_value())
        res.apply("guard", generate(*node.guard));

    names.erase("syn_port_name");
    return res;
}

CodeFiles CodeGenerator::generate(const asg::Place &node) {
    CodeFiles res = template_manager.get("place");
    names["place_name"] = node.name.toString();
    res.apply(names);

    if (node.init_state.has_value())
        res.apply("init_state", generate(*node.init_state));

    if (node.init_action.has_value())
        res.apply("init_action", generate(*node.init_action));

    names.erase("place_name");
    return res;
}

CodeFiles CodeGenerator::generate(const asg::Transition &node) {
    CodeFiles res = template_manager.get("");
    names["transition_name"] = node.name.toString();
    res.apply(names);

    for (auto &pre_cond : node.pre_conditions)
        res.apply("pre_cond", generate(pre_cond));

    for (auto &cond : node.conditions)
        res.apply("cond", generate(cond));

    for (auto &post_cond : node.post_conditions)
        res.apply("post_cond", generate(post_cond));

    if (node.guard.has_value())
        res.apply("guard", generate(*node.guard));

    if (node.action.has_value())
        res.apply("action", generate(*node.action));

    names.erase("transition_name");
    return res;
}

CodeFiles CodeGenerator::generate(const asg::PreCondPair &node) {
    CodeFiles res = template_manager.get("");
    names["place"] = node.place.toString();
    res.apply(names);

    res.apply("multiset", generate(node.edge_expression));

    names.erase("place");
    return res;
}

CodeFiles CodeGenerator::generate(const asg::PostCondPair &node) {
    CodeFiles res = template_manager.get("");
    names["place"] = node.place.toString();
    res.apply(names);

    res.apply("multiset", generate(node.edge_expression));

    names.erase("place");
    return res;
}

CodeFiles CodeGenerator::generate(const asg::CondPair &node) {
    CodeFiles res = template_manager.get("");
    names["place"] = node.place.toString();
    res.apply(names);

    res.apply("multiset", generate(node.edge_expression));

    names.erase("place");
    return res;
}

CodeFiles CodeGenerator::generate(const asg::Guard &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    res.apply("expression", generate(node.expression));

    return res;
}

CodeFiles CodeGenerator::generate(const asg::Action &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    for (auto &temp : node.temporaries)
        res.apply("temp", generate_temporary(temp));

    res.apply("expression", generate(node.expression));

    return res;
}

CodeFiles CodeGenerator::generate(const asg::MultiSet &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    for (auto &elem : node.elements)
        res.apply("element_pair", generate(elem));

    return res;
}

CodeFiles CodeGenerator::generate(const asg::MultiSetElemPair &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    res.apply("count", generate(node.count));
    res.apply("term", generate(node.term));

    return res;
}

CodeFiles CodeGenerator::generate(const asg::MultiSetCount &node) {
    CodeFiles res;

    if (node.is_variable())
        return generate(node.get_variable());

    res = template_manager.get("");
    res.apply(names);
    res.apply("value", std::to_string(node.get_int()));
    return res;
}

CodeFiles CodeGenerator::generate(const asg::MultiSetTerm &node) {
    if (node.list.has_value())
        return generate(*node.list);

    if (node.literal.has_value())
        return generate(*node.literal);

    return generate(*node.variable);
}

CodeFiles CodeGenerator::generate(const asg::MultiSetList &node) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    for (auto &elem : node.elements)
        res.apply("element", generate(elem));

    /*TODO prolog array ??*/

    return res;
}

CodeFiles CodeGenerator::generate_argument(const Identifier &id) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    res.apply("variable_name", id.toString());

    return res;
}

CodeFiles CodeGenerator::generate_temporary(const Identifier &id) {
    CodeFiles res = template_manager.get("");
    res.apply(names);

    res.apply("variable_name", id.toString());

    return res;
}


CodeFiles CodeGenerator::load_static_code_files(std::filesystem::path dirpath) {
    std::filesystem::path templ_name;
    std::map<std::string, Code> map;
    std::filesystem::path filepath;

    for (auto file : std::filesystem::recursive_directory_iterator(dirpath)) {
        if (!file.is_regular_file()) {
            continue;
        }

        filepath = file.path();

        if (filepath.extension() == ".cpp" || filepath.extension() == ".cc") {
            templ_name = filepath.filename();
            map[templ_name] = Code(std::ifstream(filepath));
        }

        if (filepath.extension() == ".h") {
            templ_name = filepath.filename();
            map[templ_name] = Code(std::ifstream(filepath));
        }

        if (filepath.filename() == "Makefile") {
            templ_name = filepath.filename();
            map[templ_name] = Code(std::ifstream(filepath));
        }
    }
    return CodeFiles(map);
}
