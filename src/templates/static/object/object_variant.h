#pragma once
#include "array.h"
#include "boolean.h"
#include "character.h"
#include "code_block.h"
#include "integer.h"
#include "nil.h"
#include "string.h"
#include "symbol.h"
#include "transcript.h"
#include <variant>

namespace PNtalk {
typedef std::variant<Nil, Bool, Integer, Character, String, Symbol, Array, CodeBlock, Transcript /*?__generated__*/> ObjectVariant;
}
