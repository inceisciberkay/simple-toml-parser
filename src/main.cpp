#include "OutputStrategyInterface.hpp"
#include "OutputString.hpp"
#include "TomlComponentTable.hpp"
#include "TomlParser.hpp"
#include <iostream>
#include <string>

auto main(int argc, char **argv) -> int {
    TomlParser toml_parser;

    for (int i = 1; i < argc; i++) {
        std::string file_contents = toml_parser.read_file_onto_string(argv[i]);

        if (file_contents.empty()) {
            std::cout << "File could not be found" << std::endl;
        } else {
            TomlComponentTable toml =
                toml_parser.parse_toml_string(file_contents);
            OutputStrategyInterface *strategy = new OutputString();
            strategy->get_output(&toml);
            delete strategy;
        }
    }

    return 0;
}
