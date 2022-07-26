#ifndef TOML_COMPONENT_INTERFACE_HPP_
#define TOML_COMPONENT_INTERFACE_HPP_

#include "OutputStrategyInterface.hpp"
#include <iostream>

class TomlComponentInterface {
protected:
    std::string type;

public:
    virtual ~TomlComponentInterface() {}

    auto get_type() -> std::string { return type; }
    auto is_collection() -> bool { return type == "array" || type == "table"; }
};

#endif