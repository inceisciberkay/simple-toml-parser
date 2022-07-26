#include "TomlComponentBool.hpp"

TomlComponentBool::TomlComponentBool() { type = "bool"; }

TomlComponentBool::TomlComponentBool(TomlComponentBool &obj) {
    type = "bool";
    this->set_value(obj.get_value());
}

TomlComponentBool::TomlComponentBool(bool b) : TomlComponentTemplate(b) {
    type = "bool";
}

TomlComponentBool::~TomlComponentBool() = default;