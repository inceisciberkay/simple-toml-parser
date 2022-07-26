#include "TomlComponentFloat.hpp"

TomlComponentFloat::TomlComponentFloat() { type = "float"; }

TomlComponentFloat::TomlComponentFloat(TomlComponentFloat &obj) {
    type = "float";
    this->set_value(obj.get_value());
}

TomlComponentFloat::TomlComponentFloat(float f) : TomlComponentTemplate(f) {
    type = "float";
}

TomlComponentFloat::~TomlComponentFloat() = default;