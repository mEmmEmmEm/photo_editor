#ifndef FILTER_PARSER_H
#define FILTER_PARSER_H

#include <string>
#include <unordered_map>

using Params = std::unordered_map<std::string, std::string>;

// Разбирает строку аргумента фильтра
void parse_filter_arg(const std::string& arg, std::string& filter_name, Params& params);

#endif // FILTER_PARSER_H
