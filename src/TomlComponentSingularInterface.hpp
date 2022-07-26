#ifndef TOML_COMPONENT_SINGULAR_HPP_
#define TOML_COMPONENT_SINGULAR_HPP_

#include "TomlComponentInterface.hpp"

class TomlComponentSingularInterface : public TomlComponentInterface {
private:
public:
    TomlComponentSingularInterface() = default;
    ~TomlComponentSingularInterface() override = default;
    // virtual std::string to_string() = 0;
};

#endif