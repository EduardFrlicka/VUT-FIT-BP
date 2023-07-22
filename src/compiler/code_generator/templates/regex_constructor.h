#pragma once
#include <regex>
#include <string>

/**
 * @brief construct regex for required replacement in template based on key
 */
#define regex_replacement(key) std::regex(std::string("__") + key + "__")

/**
 * @brief construct regex for optional replacement in template based on key
 */
#define regex_optional(key) std::regex(std::string("[ \t]*/\\*\\?\\s*") + key + "\\s*?\\*/\\s*?\n?")

#define regex_special(data) std::regex(std::string("/\\*\\!\\s*") + data + "\\s*\\*/")
