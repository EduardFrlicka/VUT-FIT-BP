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

    names.erase("class_name");
    names.erase("base_class_name");
    return res;
}

CodeFiles CodeGenerator::generate(const asg::Net &node) {
    CodeFiles res = template_manager.get("net");
    res.apply(names);

    for (auto place : node.places)
        res.apply("place", generate(place));

    return res;
}

CodeFiles CodeGenerator::generate(const asg::Method &) {
    return CodeFiles();
}

CodeFiles CodeGenerator::generate(const asg::Constructor &) {
    return CodeFiles();
}

CodeFiles CodeGenerator::generate(const asg::SynPort &) {
    return CodeFiles();
}

CodeFiles CodeGenerator::generate(const asg::Place &node) {
    CodeFiles res = template_manager.get("place");
    names["place_name"] = node.name.toString();
    res.apply(names);

    names.erase("place_name");
    return res;
}

CodeFiles CodeGenerator::generate(const asg::Transition &) {
    return CodeFiles();
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
