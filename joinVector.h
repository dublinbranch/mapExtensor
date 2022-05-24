#ifndef JOINVECTOR_H
#define JOINVECTOR_H

#include <string>
#include <vector>

/*
use
#include <fmt/ranges.h>
fmt::print("{}\n", fmt::join(en2, " | "));
*/
std::string join(const auto& in, const char* sep = ",") {
    std::string out;
    for (const auto& el : in) {
        out += el;
        out += sep;
    }
    out.pop_back();
    return out;
}

#endif // JOINVECTOR_H
