#include "TomlParser.hpp"
#include "TomlComponentArray.hpp"
#include "TomlComponentBool.hpp"
#include "TomlComponentCollectionInterface.hpp"
#include "TomlComponentFloat.hpp"
#include "TomlComponentInt.hpp"
#include "TomlComponentInterface.hpp"
#include "TomlComponentString.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

TomlParser::TomlParser() = default;

// takes file name as input and returns a string containing the file contents
auto TomlParser::read_file_onto_string(const std::string &file_name)
    -> std::string {
    // ifstream destructor closes the file automatically, no need to close it
    // explicitly
    std::ifstream file("../" + file_name);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string file_string = buffer.str();

    return file_string;
}

// takes a string containing file contents and returns the corresponding toml
// table
auto TomlParser::parse_toml_string(std::string file_contents)
    -> TomlComponentTable {
    auto *main_table = new TomlComponentTable();

    // reshaping the string file_contents
    std::string shaped_string;
    std::string map_name;

    // handling comments TODO: sees as comment: "some text # some text"
    std::string file_contents_without_comments;
    int position_of_new_line_character = file_contents.find('\n');
    while (position_of_new_line_character != std::string::npos) {
        position_of_new_line_character = file_contents.find('\n');
        std::string line_with_spaces =
            file_contents.substr(0, position_of_new_line_character);

        if (line_with_spaces.find('#') != std::string::npos) {
            line_with_spaces =
                line_with_spaces.substr(0, line_with_spaces.find('#'));
        }
        file_contents_without_comments += line_with_spaces;
        file_contents_without_comments += '\n';
        file_contents.erase(0, position_of_new_line_character + 1);
    }

    position_of_new_line_character = file_contents_without_comments.find('\n');
    while (position_of_new_line_character != std::string::npos) {
        position_of_new_line_character =
            file_contents_without_comments.find('\n');
        std::string line_with_spaces = file_contents_without_comments.substr(
            0, position_of_new_line_character);

        // handling multiple line strings
        if (line_with_spaces.find("'''") != std::string::npos) {
            while (!std::regex_match(
                line_with_spaces,
                std::regex(R"a(.*= *'''.*''' *)a", std::regex::extended))) {
                file_contents_without_comments.erase(
                    0, position_of_new_line_character + 1);
                position_of_new_line_character =
                    file_contents_without_comments.find('\n');
                line_with_spaces += '\n';
                line_with_spaces += file_contents_without_comments.substr(
                    0, position_of_new_line_character);
            }
        } else if (line_with_spaces.find(R"(""")") != std::string::npos) {
            while (!std::regex_match(
                line_with_spaces,
                std::regex(R"a(.*= *""".*""" *)a", std::regex::extended))) {
                file_contents_without_comments.erase(
                    0, position_of_new_line_character + 1);
                position_of_new_line_character =
                    file_contents_without_comments.find('\n');
                line_with_spaces += '\n';
                line_with_spaces += file_contents_without_comments.substr(
                    0, position_of_new_line_character);
            }
        }
        // handling multiple line arrays
        else if (std::regex_search(line_with_spaces,
                                   std::regex(R"a(.*= *\[)a"))) {
            int position_of_bracket = file_contents_without_comments.find('[');
            std::string inline_array_with_spaces =
                file_contents_without_comments.substr(0,
                                                      position_of_bracket + 1);
            file_contents_without_comments.erase(0, position_of_bracket + 1);
            int position_of_closing_bracket = 0;

            int count = 1;
            for (int i = 0; i < file_contents_without_comments.size(); ++i) {
                if (file_contents_without_comments[i] == '[') {
                    inline_array_with_spaces +=
                        file_contents_without_comments[i];
                    count++;
                } else if (file_contents_without_comments[i] == ']') {
                    inline_array_with_spaces +=
                        file_contents_without_comments[i];
                    position_of_closing_bracket = i;
                    count--;
                } else if (file_contents_without_comments[i] == '\\' &&
                           file_contents_without_comments[i + 1] == 'n') {
                    i++;
                } else {
                    inline_array_with_spaces +=
                        file_contents_without_comments[i];
                }

                if (count == 0) {
                    break;
                }
            }
            line_with_spaces = inline_array_with_spaces;
            position_of_new_line_character = position_of_closing_bracket;
        }

        // handling multiple line tables
        else if (std::regex_search(line_with_spaces,
                                   std::regex(R"a(.*= *\{)a"))) {
            int position_of_bracket = file_contents_without_comments.find('{');
            std::string inline_table_with_spaces =
                file_contents_without_comments.substr(0,
                                                      position_of_bracket + 1);
            file_contents_without_comments.erase(0, position_of_bracket + 1);
            int position_of_closing_bracket = 0;

            int count = 1;
            for (int i = 0; i < file_contents_without_comments.size(); ++i) {
                if (file_contents_without_comments[i] == '{') {
                    inline_table_with_spaces +=
                        file_contents_without_comments[i];
                    count++;
                } else if (file_contents_without_comments[i] == '}') {
                    inline_table_with_spaces +=
                        file_contents_without_comments[i];
                    position_of_closing_bracket = i;
                    count--;
                } else if (file_contents_without_comments[i] == '\\' &&
                           file_contents_without_comments[i + 1] == 'n') {
                    i++;
                } else {
                    inline_table_with_spaces +=
                        file_contents_without_comments[i];
                }

                if (count == 0) {
                    break;
                }
            }
            line_with_spaces = inline_table_with_spaces;
            position_of_new_line_character = position_of_closing_bracket;
        }

        // erasing spaces in line
        std::string line;

        // TODO: enhance this regex expression to support escapes inside
        // strings that are located inside either table or array as such:
        // contributors =
        // [
        //"Foo Bar \" <foo@example.com>",
        //{ name = "Baz Qux", email = "bazqux@example.com", url =
        //"https://example.com/bazqux" }
        //]
        std::regex e(R"([^\s"']+|"[^"]*"|'[^']*')");
        for (std::sregex_iterator i = std::sregex_iterator(
                 line_with_spaces.begin(), line_with_spaces.end(), e);
             i != std::sregex_iterator(); ++i) {
            std::smatch match = *i;
            std::string match_str = match.str();
            line += match_str;
        }
        // all of the spaces inside the line were trimmed (expect the ones
        // inside quotes)
        std::smatch match;

        if (line.empty() || std::regex_match(line, std::regex(R"( *)"))) {
            // do nothing, empty line
        } else if (std::regex_match(line, match, std::regex(R"(\[(.*)\])"))) {
            map_name = match[1];
            // for the remaining lines, map_name will be inserted at the
            // beginning
        } else {
            if (!map_name.empty()) {
                std::string insert_at_beginning = map_name + ".";
                line = insert_at_beginning + line;
            }

            int position_of_equal_sign = line.find('=');
            std::string key = line.substr(0, position_of_equal_sign);
            std::string value = line.substr(position_of_equal_sign + 1);

            if ((value.length() >= 3 && value.substr(0, 3) == "'''") ||
                value.substr(0, 3) == R"(""")") {
                value = value.substr(2, value.length() - 4);
            }

            helper(main_table, key, value);
        }

        file_contents_without_comments.erase(0, position_of_new_line_character +
                                                    1);
    }
    TomlComponentTable return_table = *main_table;
    delete main_table;
    return return_table;
}

// the function assumes that all the components are seperated by a new line
// (no multiple line components)
void TomlParser::helper(TomlComponentCollectionInterface *collection,
                        std::string key, const std::string &value) {

    if (collection->get_type() == "array") { // ignore key computations
    } else {                                 // else, it is table
        int position_of_dot = key.find('.');

        while (position_of_dot != std::string::npos) {
            std::string table_key = key.substr(0, position_of_dot);
            TomlComponentCollectionInterface *new_table = nullptr;

            if (dynamic_cast<TomlComponentTable *>(collection)
                    ->is_key_exist(table_key)) {
                new_table = dynamic_cast<TomlComponentTable *>(
                    dynamic_cast<TomlComponentTable *>(collection)
                        ->get_component_by_key(table_key));
            } else {
                new_table = new TomlComponentTable();
                dynamic_cast<TomlComponentTable *>(collection)
                    ->add(table_key, new_table);
            }
            collection = new_table;
            key.erase(0, position_of_dot + 1);
            position_of_dot = key.find('.');
        }
        // end of while loop, key is now property name
    }

    TomlComponentInterface *component = nullptr;
    std::smatch match;
    // if (std::regex_match(value, match,
    // std::regex(R"foo("(?:[^"\\]|\\.)*"|'(?:[^'\\]|\\.)*')foo")))
    if (std::regex_match(value, match,
                         std::regex(R"f(".*"|'.*')f",
                                    std::regex::extended))) { // value is string
        component = new TomlComponentString(
            match[0].str().substr(1, match[0].str().length() - 2));
    } else if (std::regex_match(
                   value, match,
                   std::regex(R"f([+-]?\d+)f"))) { // value is integer
        component = new TomlComponentInt(std::stoi(match[0].str()));
    } else if (std::regex_match(
                   value, match,
                   std::regex(R"f([+-]?\d+\.\d+)f"))) { // value in float
                                                        // (fractional)
        component = new TomlComponentFloat(std::stof(match[0].str()));
    } else if (value == "true" ||
               value == "false") { // value is boolean (true or false)

        component = (value == "true") ? new TomlComponentBool(true)
                                      : new TomlComponentBool(false);
    } else if (std::regex_match(
                   value, match,
                   std::regex(
                       R"f(0x[0123456789ABCDEFabcdef]+)f"))) { // value is
                                                               // hexadecimal
        int x = 0;
        std::stringstream ss;
        ss << std::hex << match[0];
        ss >> x;
        component = new TomlComponentInt(x);

    } else if (std::regex_match(
                   value, match,
                   std::regex(R"f(0o[01234567]+)f"))) { // value is octal
        int x = 0;
        std::stringstream ss;
        ss << std::oct << match[0].str().substr(2);
        ss >> x;
        component = new TomlComponentInt(x);

    } else if (std::regex_match(
                   value, match,
                   std::regex(R"f(0b[01]+)f"))) { // value is binary

        component = new TomlComponentInt(
            std::stoi(match[0].str().substr(2), nullptr, 2));

    } else if (std::regex_match(
                   value, match,
                   std::regex(
                       R"f([+-]?\d+[eE][+-]?\d+)f"))) { // value is exponent

        component = new TomlComponentFloat(std::atof(value.c_str()));
    } else if (std::regex_match(
                   value, match,
                   std::regex(
                       R"([+-]?\d+\.\d+[eE][+-]?\d+)"))) { // value is both
                                                           // fractional and
                                                           // exponent
        component = new TomlComponentFloat(std::atof(value.c_str()));

    } else if (
        std::regex_match(
            value, match,
            std::regex(
                R"(\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}\.*\d*)"))) { // value
                                                                    // is
                                                                    // local
                                                                    // date-time
        component = new TomlComponentString(value);
    } else if (value[0] == '{' &&
               value[value.length() - 1] == '}') { // value is inline map
        component = new TomlComponentTable();
        std::string values_inside_table = value.substr(1, value.size() - 2);
        auto *csv = new std::vector<std::string>();
        split_string_comma(csv, values_inside_table);

        for (auto &i : *csv) {
            int position_of_equal_sign = i.find('=');
            std::string inline_key = i.substr(0, position_of_equal_sign);
            std::string inline_value = i.substr(position_of_equal_sign + 1);

            helper(dynamic_cast<TomlComponentTable *>(component), inline_key,
                   inline_value);
        }

        delete csv;
    } else if (value[0] == '[' &&
               value[value.length() - 1] == ']') { // value is array
        component = new TomlComponentArray();
        std::string values_inside_array = value.substr(1, value.size() - 2);
        auto *csv = new std::vector<std::string>();
        split_string_comma(csv, values_inside_array);

        for (auto &i : *csv) {
            helper(dynamic_cast<TomlComponentArray *>(component), "",
                   i); // key is not important in this context
        }
        delete csv;
    }
    // TODO: handling unsupported format, program should terminate and print
    // out problematic line number
    else {
        std::cout << "unsupported format: " << value << std::endl;
        return;
    }

    if (collection->get_type() == "array") {
        dynamic_cast<TomlComponentArray *>(collection)->add(component);

    } else if (!dynamic_cast<TomlComponentTable *>(collection)
                    ->is_key_exist(key)) {
        dynamic_cast<TomlComponentTable *>(collection)->add(key, component);
    }
}

void TomlParser::split_string_comma(std::vector<std::string> *csv,
                                    std::string str) {
    // not a base case, just checking the edge
    if (str.empty()) {
        return;
    }

    char c = str[0];
    char o = 'a';

    switch (c) {
    case '{':
        o = '}';
        break;
    case '[':
        o = ']';
        break;
    case '\'':
        o = '\'';
        break;
    case '"':
        o = '"';
        break;
    default:
        o = 'a';
        break;
    }

    int count = 0;
    int str_length = str.length();
    for (int i = 0; i < str_length; i++) {
        if (c == '\'' || c == '"') {
            if ((i == 0 && str[i] == c) ||
                (i > 0 && str[i] == c && str[i - 1] != '\\')) {
                count++;
            }
        } else {
            if (str[i] == c) {
                count++;

            } else if (str[i] == o) {
                count--;
            }
        }

        if (str[i] == ',' && (count % 2 == 0 || o == 'a')) {
            csv->push_back(str.substr(0, i));
            str.erase(0, i + 1);
            break;
        }

        // base case
        if (i == str_length - 1) {
            csv->push_back(str);
            return;
        }
    }

    split_string_comma(csv, str);
}

// TODO:
// separators
// infinity
// not a number
// offset datetime
// local date
// local time
// array of tables: [[table_name]]
