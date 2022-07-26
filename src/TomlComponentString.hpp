#ifndef TOML_COMPONENT_STRING_HPP_
#define TOML_COMPONENT_STRING_HPP_

#include "TomlComponentSingularInterface.hpp"
#include "TomlComponentTemplate.hpp"
#include <string>

class TomlComponentString : public TomlComponentSingularInterface,
                            public TomlComponentTemplate<std::string> {
public:
    TomlComponentString();
    TomlComponentString(
        TomlComponentString &); // adding const keyword results in binding error
    explicit TomlComponentString(std::string);
    ~TomlComponentString() override;
};

#endif