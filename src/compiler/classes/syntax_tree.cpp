#include "syntax_tree.h"

using namespace ast;

BaseNode::BaseNode(Token &_token) : token(_token) {
}

ClassesNode::ClassesNode(Token &_token) : BaseNode(_token) {
}
