#ifndef TOML_COMPONENT_TABLE_HPP_
#define TOML_COMPONENT_TABLE_HPP_

#include "TomlComponentCollectionInterface.hpp"
#include "TomlComponentTemplate.hpp"
#include <map>
#include <string>
class TomlComponentInterface;

class TomlComponentTable : public TomlComponentTemplate<
                               std::map<std::string, TomlComponentInterface *>>,
                           public TomlComponentCollectionInterface {
public:
    TomlComponentTable();
    TomlComponentTable(
        TomlComponentTable &); // adding const keyword results in binding error
    ~TomlComponentTable() override;

    // adding const keyword results in binding error
    auto operator=(TomlComponentTable &) -> TomlComponentTable &;

    void add(const std::string &key, TomlComponentInterface *value);
    auto is_key_exist(const std::string &key) -> bool;
    auto get_component_by_key(const std::string &key)
        -> TomlComponentInterface *;
};

#endif