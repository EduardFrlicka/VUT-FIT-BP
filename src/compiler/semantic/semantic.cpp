#include "semantic.h"
#include "error_printer.h"
#include <iostream>

#define analyze_vector(baf)

SemanticAnalyzer::SemanticAnalyzer(const ast::Classes &__root) {
    Identifier id;

    /* INITIALIZATION */
    id = Identifier("PN");
    id.declare_define(__root.begin);
    classes.push(id);

    id = Identifier("self");
    id.declare_define(__root.begin);
    variables.push(id);

    id = Identifier("super");
    id.declare_define(__root.begin);
    variables.push(id);

    /* ANALYSYS */
    _root = analyze(__root);
    // if (res)
    //     exit(res);
}

asg::Classes &SemanticAnalyzer::root() {
    return _root;
}

asg::Classes SemanticAnalyzer::analyze(const ast::Classes &node) {
    Identifier _class;
    asg::Classes result_node;

    for (auto i : node.classes) {
        if (classes.search(i.head.derived->payload.id)) {
            auto definition = classes.get(i.head.derived->payload.id);
            error.class_redeclaration(definition, i.head.derived->it);
            res = ERR_SEMANTIC;
        } else {
            _class = Identifier(i.head.derived->payload.id);
            _class.declare_define(i.head.begin);
            classes.push(_class);
        }
    }

    for (auto i : node.classes)
        result_node.classes.push_back(analyze(i));

    return result_node;
}

asg::Class SemanticAnalyzer::analyze(const ast::Class &node) {
    asg::Class result_node;

    messages.push_frame();

    analyze(node.head);
    result_node.base = classes.get(node.head.base->payload.id);
    result_node.name = classes.get(node.head.derived->payload.id);
    if (node.object.has_value())
        result_node.object = analyze(node.object.value());

    for (auto i : node.methods)
        result_node.methods.push_back(analyze(i));
    for (auto i : node.constructors)
        result_node.constructors.push_back(analyze(i));
    for (auto i : node.syn_ports)
        result_node.syn_ports.push_back(analyze(i));

    messages.pop_frame();

    return result_node;
}

void SemanticAnalyzer::analyze(const ast::ClassHead &node) {
    if (node.derived->payload.id.is_lower()) {
        error.expected_upper(node.derived->it);
        res = ERR_SEMANTIC;
    }

    if (node.base->payload.id.is_lower()) {
        error.expected_upper(node.base->it);
        res = ERR_SEMANTIC;
    }

    if (!classes.search(node.base->payload.id)) {
        error.undeclared_class(node.base->it);
        res = ERR_SEMANTIC;
    }
}

asg::Net SemanticAnalyzer::analyze(const ast::ObjectNet &node) {
    asg::Net result_node;

    transitions.push_frame();

    for (auto place : node.net.places) {
        result_node.places.push_back(analyze(place));
    }

    for (auto transition : node.net.transitions) {
        result_node.transitions.push_back(analyze(transition));
    }

    transitions.pop_frame();

    return result_node;
}

asg::Method SemanticAnalyzer::analyze(const ast::MethodNet &node) {
    asg::Method result_node;
    variables.push_frame();
    auto message = analyze(node.message);
    result_node.selector = message.first;
    result_node.arguments = message.second;
    result_node.net = analyze(node.net);
    variables.pop_frame();

    return result_node;
}

asg::Constructor SemanticAnalyzer::analyze(const ast::Constructor &node) {
    asg::Constructor result_node;
    variables.push_frame();
    auto message = analyze(node.message);
    result_node.selector = message.first;
    result_node.arguments = message.second;
    result_node.net = analyze(node.net);
    variables.pop_frame();

    return result_node;
}

asg::SynPort SemanticAnalyzer::analyze(const ast::SynPort &node) {
    asg::SynPort result_node;
    variables.push_frame();

    auto message = analyze(node.message);
    result_node.selector = message.first;
    result_node.arguments = message.second;

    /* TODO check if has effect */
    if (node.conditions.has_value())
        analyze(node.conditions.value());
    if (node.pre_conditions.has_value())
        analyze(node.pre_conditions.value());
    if (node.guard.has_value())
        analyze(node.guard.value());
    if (node.post_contitions.has_value())
        analyze(node.post_contitions.value());

    variables.pop_frame();
    return result_node;
}
std::pair<Identifier, std::deque<Identifier>> SemanticAnalyzer::analyze(const ast::Message &node) {
    BasicIdentifier id;
    Identifier var;
    std::deque<Identifier> vars;
    Identifier message;

    if (node.unary.has_value()) {
        id = node.unary->payload.id;
        if (node.unary->payload.id.is_upper()) {
            error.expected_lower(node.unary->it);
            res = ERR_SEMANTIC;
        }
    }

    if (node.binary.has_value()) {
        id = node.binary->first->text;

        if (node.binary->second->payload.id.is_upper()) {
            error.expected_lower(node.binary->second->it);
        }

        var = Identifier(node.binary->second->payload.id);
        var.declare_define(node.binary->second->it);
        vars.push_back(var);
        variables.push(var);
    }

    if (node.keys.size() > 0) {
        for (auto kv : node.keys) {
            id += kv.first->payload.id;

            if (kv.second->payload.id.is_upper()) {
                error.expected_lower(kv.second->it);
                res = ERR_SEMANTIC;
            }
            var = Identifier(kv.second->payload.id);
            var.declare_define(kv.second->it);
            vars.push_back(var);
            variables.push(var);
        }
    }

    if (messages.search(id)) {
        error.message_redeclaration(messages.get(id), node.begin);
    }

    message = Identifier(id);
    message.declare_define(node.begin, node.end);
    messages.push(message);

    return std::make_pair(message, vars);
}
asg::Net SemanticAnalyzer::analyze(const ast::Net &node) {
    asg::Net result_node;

    places.push_frame();
    transitions.push_frame();

    for (auto place : node.places) {
        result_node.places.push_back(analyze(place));
    }

    for (auto transition : node.transitions) {
        result_node.transitions.push_back(analyze(transition));
    }

    places.pop_frame();
    transitions.pop_frame();
    return result_node;
}
asg::Place SemanticAnalyzer::analyze(const ast::Place &node) {
    asg::Place result_node;
    Identifier place;

    if (places.search(node.name->payload.id)) {
        error.place_redeclaration(places.get(node.name->payload.id), node.name->it);
        res = ERR_SEMANTIC;
    }
    place = Identifier(node.name->payload.id);
    place.declare_define(node.name->it);
    result_node.name = place;
    places.push(place);

    if (node.init_state.has_value())
        result_node.init_state = analyze(node.init_state.value());

    /* TODO variables ?? */

    if (node.init_func.has_value())
        result_node.init_action = analyze(node.init_func.value());

    return result_node;
}

asg::Action SemanticAnalyzer::analyze(const ast::InitAction &node) {
    asg::Action result_node;
    Identifier var;

    variables.push_frame();

    for (auto temp_var : node.temporaries) {
        if (temp_var.payload.id.is_upper()) {
            error.expected_lower(temp_var.it);
            res = ERR_SEMANTIC;
        }

        if (variables.search(temp_var.payload.id)) {
            error.variable_redeclaration(variables.get(temp_var.payload.id), temp_var.it);
            res = ERR_SEMANTIC;
        }

        var = Identifier(temp_var.payload.id);
        var.declare(temp_var.it);
        variables.push(var);
        result_node.temporaries.push_back(var);
    }

    result_node.expression = analyze(node.expr);

    variables.pop_frame();

    return result_node;
}

asg::Transition SemanticAnalyzer::analyze(const ast::Transition &node) {
    asg::Transition result_node;
    Identifier transition;

    if (transitions.search(node.name->payload.id)) {
        error.transition_redeclaration(transitions.get(node.name->payload.id), node.name->it);
        res = ERR_SEMANTIC;
    }

    transition = Identifier(node.name->payload.id);
    transition.declare_define(node.name->it);
    transitions.push(transition);
    result_node.name = transition;

    variables.push_frame();

    /* TODO check if has effect */

    if (node.conditions.has_value())
        result_node.conditions = analyze(node.conditions.value());
    if (node.pre_conditions.has_value())
        result_node.pre_conditions = analyze(node.pre_conditions.value());
    if (node.guard.has_value())
        result_node.guard = analyze(node.guard.value());
    if (node.action.has_value())
        result_node.action = analyze(node.action.value());
    if (node.post_contitions.has_value())
        result_node.post_conditions = analyze(node.post_contitions.value());

    variables.pop_frame();
    return result_node;
}

asg::CondPair SemanticAnalyzer::analyze(const ast::ConditionPair &node) {
    asg::CondPair result_node;

    if (!places.search(node.first->payload.id)) {
        error.place_not_found(node.first->it);
        res = ERR_SEMANTIC;
    }

    result_node.place = places.get(node.first->payload.id);

    result_node.edge_expression = analyze(node.second);

    return result_node;
}

std::deque<asg::CondPair> SemanticAnalyzer::analyze(const ast::Condition &node) {
    std::deque<asg::CondPair> result_array;

    for (auto i : node.conditions) {
        result_array.push_back(analyze(i));
    }

    return result_array;
}

std::deque<asg::PreCondPair> SemanticAnalyzer::analyze(const ast::PreCondition &node) {
    std::deque<asg::PreCondPair> result_array;

    for (auto i : node.conditions) {
        result_array.push_back(analyze(i));
    }

    return result_array;
}

std::deque<asg::PostCondPair> SemanticAnalyzer::analyze(const ast::PostCondition &node) {
    std::deque<asg::PostCondPair> result_array;

    for (auto i : node.conditions) {
        result_array.push_back(analyze(i));
    }

    return result_array;
}

asg::Guard SemanticAnalyzer::analyze(const ast::Guard &node) {
    asg::Guard result_node;
    asg::Expression expr;

    /* TODO */
    if (!node.expr.issecundary()) {
        std::cout << node.expr.value->index() << std::endl;
        error.expression_primary_expected(node.expr.begin, node.expr.end);
        res = ERR_SEMANTIC;
    }

    expr = analyze(node.expr);

    if (expr.is_type<asg::Expressions>())
        result_node.expression = expr.get<asg::Expressions>();
    else
        result_node.expression = asg::Expressions({expr});

    return result_node;
}
asg::Action SemanticAnalyzer::analyze(const ast::Action &node) {
    asg::Action result_node;
    Identifier var;

    variables.push_frame();

    for (auto temp_var : node.temporaries) {
        if (temp_var.payload.id.is_upper()) {
            error.expected_lower(temp_var.it);
            res = ERR_SEMANTIC;
        }

        if (variables.search(temp_var.payload.id)) {
            error.variable_redeclaration(variables.get(temp_var.payload.id), temp_var.it);
            res = ERR_SEMANTIC;
        }

        var = Identifier(temp_var.payload.id);
        var.declare(temp_var.it);
        variables.push(var);
        result_node.temporaries.push_back(var);
    }

    result_node.expression = analyze(node.expr);

    variables.pop_frame();

    return result_node;
}

asg::MultiSet SemanticAnalyzer::analyze(const ast::MultiSet &node) {
    asg::MultiSet result_node;

    /* TODO variables ? */

    for (auto i : node.elements) {
        result_node.elements.push_back(analyze(i));
    }

    return result_node;
}
asg::MultiSetElemPair SemanticAnalyzer::analyze(const ast::MultiSetElem &node) {
    asg::MultiSetElemPair result_node;

    result_node.term = analyze(node.term);

    /* TODO variables ? */

    if (!node.count.has_value())
        return result_node;

    if (node.count->type == tokenIdentifier) {
        if (!variables.search(node.count->payload.id)) {
            error.undeclared_variable(node.count->it);
            res = ERR_SEMANTIC;
        } else if (!variables.get(node.count->payload.id).defined) {
            error.undefined_variable(variables.get(node.count->payload.id), node.count->it);
            res = ERR_SEMANTIC;
        } else {
            result_node.count = asg::Variable(variables.get(node.count->payload.id));
        }
    }

    if (node.count->type == tokenInteger) {
        if (node.count->payload.integer_number.number < 0) {
            error.negative_count_in_multiset(node.count->it);
            res = ERR_SEMANTIC;
        } else {
            result_node.count = node.count->payload.integer_number.number;
        }
    }

    return result_node;
}

asg::MultiSetTerm SemanticAnalyzer::analyze(const ast::MultiSetTerm &node) {
    asg::MultiSetTerm result_node;
    Identifier var;

    if (node.list.has_value()) {
        result_node.list = analyze(*node.list);
        return result_node;
    }

    if (node.value->type == tokenIdentifier) {
        if (node.value->payload.id.is_upper()) {
            error.expected_lower(node.value->it);
            res = ERR_SEMANTIC;
        }

        if (variables.search(node.value->payload.id)) {
            result_node.variable = variables.get(node.value->payload.id);
        } else {
            var = Identifier(node.value->payload.id);
            var.declare_define(node.value->it);
            variables.push(var);
            result_node.variable = var;
        }
    }

    if (node.value->isliteral()) {
        result_node.literal = asg::Literal(node.value->payload, node.value->type);
    }

    return result_node;
}

asg::MultiSetList SemanticAnalyzer::analyze(const ast::MultiSetTerm::MultiSetList &node) {
    asg::MultiSetList result_node;

    for (auto const &i : node.values) {
        result_node.elements.push_back(analyze(i));
    }

    if (node.tail.has_value()) {
        if (node.tail->payload.id.is_upper()) {
            error.expected_lower(node.tail->it);
            res = ERR_SEMANTIC;
        }
        if (variables.search(node.tail->payload.id)) {
        }
    }

    return result_node;
    /*end*/
}
