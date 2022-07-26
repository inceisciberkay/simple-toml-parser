#include "TomlComponentInt.hpp"

TomlComponentInt::TomlComponentInt() { type = "int"; }

TomlComponentInt::TomlComponentInt(TomlComponentInt &obj) {
    type = "int";
    this->set_value(obj.get_value());
}

TomlComponentInt::TomlComponentInt(int n) : TomlComponentTemplate(n) {
    type = "int";
}

TomlComponentInt::~TomlComponentInt() = default;