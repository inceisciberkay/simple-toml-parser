#ifndef TOML_PARSER_HPP_
#define TOML_PARSER_HPP_

#include "TomlComponentTable.hpp"
#include <string>
#include <vector>
class TomlComponentCollectionInterface;

class TomlParser {

public:
    void split_string_comma(std::vector<std::string> *csv, std::string str);
    TomlParser();
    auto read_file_onto_string(const std::string &file_name) -> std::string;
    auto parse_toml_string(std::string file_contents) -> TomlComponentTable;

protected:
    void helper(TomlComponentCollectionInterface *collection, std::string key,
                const std::string &value);
};

#endif