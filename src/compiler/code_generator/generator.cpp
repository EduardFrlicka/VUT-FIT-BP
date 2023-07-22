#include "generator.h"
#include "error_printer.h"

CodeGenerator::CodeGenerator(const ast::Classes &root) : template_manager(args.compiler_templates_path) {
    CodeFiles static_files;
    CodeFiles result;

    result = generate_classes(root);

    // static_files = load_static_code_files(args.static_templates_path);
    // result = static_files.combine({{"generated", result}});

    result.print();
}

CodeFiles CodeGenerator::generate_classes(const ast::Classes &node) {
    CodeFiles res;
    res = template_manager.get("classes").apply({{"main", node.main->text}});

    for (auto i : node.classes)
        res = res.combine("class", generate_class(i));

    return res;
}

CodeFiles CodeGenerator::generate_class(const ast::Class &node) {
    CodeFiles res;
    names["class_name"] = node.head.derived->text;
    names["base_class_name"] = node.head.base->text;

    res = template_manager.get("class").apply(names);
    if (node.object.has_value())
        res = res.combine({{"object", generate_object_net(*node.object)}});

    names.erase("class_name");
    names.erase("base_class_name");
    return res;
}

CodeFiles CodeGenerator::generate_object_net(const ast::ObjectNet &node) {

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
