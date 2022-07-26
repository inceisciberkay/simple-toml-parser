#ifndef OUTPUT_STRING_HPP_
#define OUTPUT_STRING_HPP_

#include "OutputStrategyInterface.hpp"
#include <map>
#include <string>
#include <vector>
class TomlComponentInterface;

class OutputString : public OutputStrategyInterface {
public:
    void get_output(TomlComponentInterface *) override;

protected:
    void
    helper_table(const std::map<std::string, TomlComponentInterface *> &map,
                 std::string &str, int count);

    void helper_array(const std::vector<TomlComponentInterface *> &arr,
                      std::string &str, int count);
};

#endif