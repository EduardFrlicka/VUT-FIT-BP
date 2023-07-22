#include "object.h"
#include "string.h"
#include <deque>
#include <thread>

int main() {
    auto s = PN::String();
    s.message("at", {});
    s.message("_eq_", {});
}