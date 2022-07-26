#include "OutputString.hpp"
#include "TomlComponentArray.hpp"
#include "TomlComponentBool.hpp"
#include "TomlComponentFloat.hpp"
#include "TomlComponentInt.hpp"
#include "TomlComponentInterface.hpp"
#include "TomlComponentString.hpp"
#include "TomlComponentTable.hpp"
#include <iostream>
#include <utility>

void OutputString::get_output(TomlComponentInterface *item) {
    std::string result;

    if (item->get_type() == "table") {
        int count = 1;
        helper_table(dynamic_cast<TomlComponentTable *>(item)->get_value(),
                     result, count);
    } else if (item->get_type() == "array") {
        int count = 1;
        helper_array(dynamic_cast<TomlComponentArray *>(item)->get_value(),
                     result, count);
    } else if (item->get_type() == "string") {
        result = dynamic_cast<TomlComponentString *>(item)->get_value() + "\n";
    } else if (item->get_type() == "int") {
        result = std::to_string(
                     dynamic_cast<TomlComponentInt *>(item)->get_value()) +
                 "\n";
    } else if (item->get_type() == "float") {
        result = std::to_string(
                     dynamic_cast<TomlComponentFloat *>(item)->get_value()) +
                 "\n";

    } else if (item->get_type() == "bool") {
        result = dynamic_cast<TomlComponentBool *>(item)->get_value()
                     ? "true\n"
                     : "false\n";
    }

    std::cout << result << std::endl;
}

void OutputString::helper_table(
    const std::map<std::string, TomlComponentInterface *> &map,
    std::string &str, int count) {
    str += "{\n";

    for (const auto &it : map) {
        for (int i = 0; i < count; i++) {
            str += "\t";
        }

        str += it.first;
        str += ": ";

        if (it.second->get_type() == "table") {
            // for (int i = 0; i < count; i++) {
            // str += "\t";
            // }
            helper_table(
                dynamic_cast<TomlComponentTable *>(it.second)->get_value(), str,
                count + 1);
        } else if (it.second->get_type() == "array") {
            // for (int i = 0; i < count; i++) {
            // str += "\t";
            //}
            helper_array(
                dynamic_cast<TomlComponentArray *>(it.second)->get_value(), str,
                count + 1);
        } else if (it.second->get_type() == "string") {
            str += dynamic_cast<TomlComponentString *>(it.second)->get_value();
            str += "\n";
        } else if (it.second->get_type() == "int") {
            str += std::to_string(
                dynamic_cast<TomlComponentInt *>(it.second)->get_value());
            str += "\n";
        } else if (it.second->get_type() == "float") {
            str += std::to_string(
                dynamic_cast<TomlComponentFloat *>(it.second)->get_value());
            str += "\n";
        } else if (it.second->get_type() == "bool") {
            str += dynamic_cast<TomlComponentBool *>(it.second)->get_value()
                       ? "true\n"
                       : "false\n";
        }
    }
    for (int i = 0; i < count - 1; i++) {
        str += "\t";
    }
    str += "}\n";
}

void OutputString::helper_array(
    const std::vector<TomlComponentInterface *> &arr, std::string &str,
    int count) {
    str += "[\n";

    for (const auto &component : arr) {
        for (int i = 0; i < count; i++) {
            str += "\t";
        }

        if (component->get_type() == "table") {
            helper_table(
                dynamic_cast<TomlComponentTable *>(component)->get_value(), str,
                count + 1);
        } else if (component->get_type() == "array") {
            helper_array(
                dynamic_cast<TomlComponentArray *>(component)->get_value(), str,
                count + 1);
        } else if (component->get_type() == "string") {
            str += dynamic_cast<TomlComponentString *>(component)->get_value();
            str += "\n";
        } else if (component->get_type() == "int") {
            str += std::to_string(
                dynamic_cast<TomlComponentInt *>(component)->get_value());
            str += "\n";
        } else if (component->get_type() == "float") {
            str += std::to_string(
                dynamic_cast<TomlComponentFloat *>(component)->get_value());
            str += "\n";
        } else if (component->get_type() == "bool") {
            str += dynamic_cast<TomlComponentBool *>(component)->get_value()
                       ? "true\n"
                       : "false\n";
        }
    }

    for (int i = 0; i < count - 1; i++) {
        str += "\t";
    }
    str += "]\n";
}