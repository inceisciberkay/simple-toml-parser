#include "TomlComponentTable.hpp"
#include "TomlComponentArray.hpp"
#include "TomlComponentBool.hpp"
#include "TomlComponentFloat.hpp"
#include "TomlComponentInt.hpp"
#include "TomlComponentInterface.hpp"
#include "TomlComponentString.hpp"
#include <utility>

TomlComponentTable::TomlComponentTable() { type = "table"; }

TomlComponentTable::TomlComponentTable(TomlComponentTable &table) {
    type = "table";

    for (auto &it : table.get_value()) {
        TomlComponentInterface *component = nullptr;
        if (it.second->get_type() == "table") {
            component = new TomlComponentTable(
                dynamic_cast<TomlComponentTable &>(*(it.second)));
        } else if (it.second->get_type() == "array") {
            component = new TomlComponentArray(
                dynamic_cast<TomlComponentArray &>(*(it.second)));
        } else if (it.second->get_type() == "string") {
            component = new TomlComponentString(
                dynamic_cast<TomlComponentString &>(*(it.second)));
        } else if (it.second->get_type() == "int") {
            component = new TomlComponentInt(
                dynamic_cast<TomlComponentInt &>(*(it.second)));
        } else if (it.second->get_type() == "float") {
            component = new TomlComponentFloat(
                dynamic_cast<TomlComponentFloat &>(*(it.second)));
        } else if (it.second->get_type() == "bool") {
            component = new TomlComponentBool(
                dynamic_cast<TomlComponentBool &>(*(it.second)));
        }

        this->get_value().insert(
            std::pair<std::string, TomlComponentInterface *>(it.first,
                                                             component));
    }
}

TomlComponentTable::~TomlComponentTable() {
    for (auto &it : this->get_value()) {
        delete it.second;
    }

    this->get_value().clear();
}

auto TomlComponentTable::operator=(TomlComponentTable &table)
    -> TomlComponentTable & {
    type = "table";

    for (auto &it : table.get_value()) {
        TomlComponentInterface *component = nullptr;
        if (it.second->get_type() == "table") {
            component = new TomlComponentTable(
                dynamic_cast<TomlComponentTable &>(*(it.second)));
        } else if (it.second->get_type() == "array") {
            component = new TomlComponentArray(
                dynamic_cast<TomlComponentArray &>(*(it.second)));
        } else if (it.second->get_type() == "string") {
            component = new TomlComponentString(
                dynamic_cast<TomlComponentString &>(*(it.second)));
        } else if (it.second->get_type() == "int") {
            component = new TomlComponentInt(
                dynamic_cast<TomlComponentInt &>(*(it.second)));
        } else if (it.second->get_type() == "float") {
            component = new TomlComponentFloat(
                dynamic_cast<TomlComponentFloat &>(*(it.second)));
        } else if (it.second->get_type() == "bool") {
            component = new TomlComponentBool(
                dynamic_cast<TomlComponentBool &>(*(it.second)));
        }

        this->get_value().insert(
            std::pair<std::string, TomlComponentInterface *>(it.first,
                                                             component));
    }

    return *this;
}

void TomlComponentTable::add(const std::string &key,
                             TomlComponentInterface *value) {
    this->get_value().insert(
        std::pair<std::string, TomlComponentInterface *>(key, value));
}

auto TomlComponentTable::is_key_exist(const std::string &key) -> bool {
    return !(this->get_value().find(key) == this->get_value().end());
}

auto TomlComponentTable::get_component_by_key(const std::string &key)
    -> TomlComponentInterface * {
    if (this->get_value().find(key) == this->get_value().end()) {
        return nullptr;
    }
    return this->get_value().at(key);
}