#ifndef TOML_COMPONENT_COLLECTION_INTERFACE_HPP_
#define TOML_COMPONENT_COLLECTION_INTERFACE_HPP_

#include "TomlComponentInterface.hpp"

class TomlComponentCollectionInterface : public TomlComponentInterface {
private:
public:
    TomlComponentCollectionInterface() = default;
    ~TomlComponentCollectionInterface() override = default;

    // std::string to_string() {
    // std::string str = "";
    // int count = 1;
    // to_string_helper(str, count);
    // return str;
    // }
    // virtual void to_string_helper(std::string &str, int count) = 0;
};

#endif