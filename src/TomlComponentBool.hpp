#ifndef TOML_COMPONENT_BOOL_HPP_
#define TOML_COMPONENT_BOOL_HPP_

#include "TomlComponentSingularInterface.hpp"
#include "TomlComponentTemplate.hpp"

class TomlComponentBool : public TomlComponentSingularInterface,
                          public TomlComponentTemplate<bool> {
public:
    TomlComponentBool();
    TomlComponentBool(
        TomlComponentBool &); // adding const keyword results in binding error
    explicit TomlComponentBool(bool b);
    ~TomlComponentBool() override;
};

#endif