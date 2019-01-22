#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iterator>

namespace npr
{
template <class InputIt>
std::string join(InputIt b, InputIt e, std::string sep = " ");
}

#endif