#ifndef TOML_COMPONENT_INT_HPP_
#define TOML_COMPONENT_INT_HPP_

#include "TomlComponentSingularInterface.hpp"
#include "TomlComponentTemplate.hpp"

class TomlComponentInt : public TomlComponentSingularInterface,
                         public TomlComponentTemplate<int> {
public:
    TomlComponentInt();
    TomlComponentInt(
        TomlComponentInt &); // adding const keyword results in binding error
    explicit TomlComponentInt(int n);
    ~TomlComponentInt() override;
};

#endif