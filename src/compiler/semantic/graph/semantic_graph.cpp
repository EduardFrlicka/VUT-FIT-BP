#include "semantic_graph.h"

AbstractSemanticGraph::MultiSetCount::MultiSetCount() : _value(1){};
AbstractSemanticGraph::MultiSetCount::MultiSetCount(int value) : _value(value){};
AbstractSemanticGraph::MultiSetCount::MultiSetCount(Variable value) : _value(value){};

bool AbstractSemanticGraph::MultiSetCount::is_int() const {
    return std::holds_alternative<int>(_value);
}
bool AbstractSemanticGraph::MultiSetCount::is_variable() const {

    return std::holds_alternative<Variable>(_value);
}
int AbstractSemanticGraph::MultiSetCount::get_int() const {
    return std::get<int>(_value);
}
AbstractSemanticGraph::Variable AbstractSemanticGraph::MultiSetCount::get_variable() const {
    return std::get<Variable>(_value);
}

AbstractSemanticGraph::PreCondPair::PreCondPair(const CondPair &pair) : place(pair.place), edge_expression(pair.edge_expression){};

AbstractSemanticGraph::PostCondPair::PostCondPair(const CondPair &pair) : place(pair.place), edge_expression(pair.edge_expression){};
