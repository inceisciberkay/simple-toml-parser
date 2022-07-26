#ifndef TOML_COMPONENT_FLOAT_HPP_
#define TOML_COMPONENT_FLOAT_HPP_

#include "TomlComponentSingularInterface.hpp"
#include "TomlComponentTemplate.hpp"

class TomlComponentFloat : public TomlComponentSingularInterface,
                           public TomlComponentTemplate<float> {
public:
    TomlComponentFloat();
    TomlComponentFloat(TomlComponentFloat &obj); // adding const keyword results
                                                 // in binding error
    explicit TomlComponentFloat(float f);
    ~TomlComponentFloat() override;
};

#endif