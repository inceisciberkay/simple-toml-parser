#include "TomlComponentString.hpp"

TomlComponentString::TomlComponentString() { type = "string"; }

TomlComponentString::TomlComponentString(TomlComponentString &obj) {
    type = "string";
    this->set_value(obj.get_value());
}

TomlComponentString::TomlComponentString(std::string str)
    : TomlComponentTemplate(str) {
    type = "string";
}

TomlComponentString::~TomlComponentString() = default;