#ifndef INCLUDE_JSTEG_HPP
#define INCLUDE_JSTEG_HPP

#include <string_view>
#include <vector>

#include "jdct.hpp"

namespace jpeg
{

void serialize(const std::string &filename, std::vector<bool> &buffer);
void embed(jpeg::jdct &j, const std::string &payload, const std::string &out);
void extract(const jpeg::jdct &j, const std::string &out);

} // namespace jpeg

#endif // INCLUDE_JSTEG_HPP
