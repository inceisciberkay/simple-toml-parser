#include "TomlComponentArray.hpp"
#include "TomlComponentBool.hpp"
#include "TomlComponentFloat.hpp"
#include "TomlComponentInt.hpp"
#include "TomlComponentInterface.hpp"
#include "TomlComponentString.hpp"
#include "TomlComponentTable.hpp"
#include <string>

TomlComponentArray::TomlComponentArray() { type = "array"; }

TomlComponentArray::TomlComponentArray(TomlComponentArray &array) {
    type = "array";

    for (auto *i : array.get_value()) {
        TomlComponentInterface *component = nullptr;
        if (i->get_type() == "table") {
            component = new TomlComponentTable(
                dynamic_cast<TomlComponentTable &>(*(i)));
        } else if (i->get_type() == "array") {
            component = new TomlComponentArray(
                dynamic_cast<TomlComponentArray &>(*(i)));
        } else if (i->get_type() == "string") {
            component = new TomlComponentString(
                dynamic_cast<TomlComponentString &>(*(i)));
        } else if (i->get_type() == "int") {
            component =
                new TomlComponentInt(dynamic_cast<TomlComponentInt &>(*(i)));
        } else if (i->get_type() == "float") {
            component = new TomlComponentFloat(
                dynamic_cast<TomlComponentFloat &>(*(i)));
        } else if (i->get_type() == "bool") {
            component =
                new TomlComponentBool(dynamic_cast<TomlComponentBool &>(*(i)));
        }
        this->get_value().push_back(component);
    }
}

TomlComponentArray::~TomlComponentArray() {
    for (auto *i : this->get_value()) {
        delete i;
    }

    this->get_value().clear();
}

auto TomlComponentArray::operator=(TomlComponentArray &array)
    -> TomlComponentArray & {
    type = "array";

    for (auto &i : array.get_value()) {
        TomlComponentInterface *component = nullptr;
        if (i->get_type() == "table") {
            component = new TomlComponentTable(
                dynamic_cast<TomlComponentTable &>(*(i)));
        } else if (i->get_type() == "array") {
            component = new TomlComponentArray(
                dynamic_cast<TomlComponentArray &>(*(i)));
        } else if (i->get_type() == "string") {
            component = new TomlComponentString(
                dynamic_cast<TomlComponentString &>(*(i)));
        } else if (i->get_type() == "int") {
            component =
                new TomlComponentInt(dynamic_cast<TomlComponentInt &>(*(i)));
        } else if (i->get_type() == "float") {
            component = new TomlComponentFloat(
                dynamic_cast<TomlComponentFloat &>(*(i)));
        } else if (i->get_type() == "bool") {
            component =
                new TomlComponentBool(dynamic_cast<TomlComponentBool &>(*(i)));
        }
        this->get_value().push_back(component);
    }

    return *this;
}

void TomlComponentArray::add(TomlComponentInterface *component) {
    this->get_value().push_back(component);
}