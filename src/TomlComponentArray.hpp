#ifndef TOML_COMPONENT_ARRAY_HPP_
#define TOML_COMPONENT_ARRAY_HPP_

#include "TomlComponentCollectionInterface.hpp"
#include "TomlComponentTemplate.hpp"
#include <vector>
class TomlComponentInterface;

class TomlComponentArray
    : public TomlComponentTemplate<std::vector<TomlComponentInterface *>>,
      public TomlComponentCollectionInterface {
public:
    TomlComponentArray();
    TomlComponentArray(
        TomlComponentArray &); // adding const keyword results in binding error
    ~TomlComponentArray() override;

    auto operator=(TomlComponentArray &) -> TomlComponentArray
        &; // adding const keyword results in binding error

    void add(TomlComponentInterface *value);
};

#endif