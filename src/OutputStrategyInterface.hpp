#ifndef OUTPUT_STRATEGY_INTERFACE_HPP_
#define OUTPUT_STRATEGY_INTERFACE_HPP_

class TomlComponentInterface;

class OutputStrategyInterface {
public:
    virtual ~OutputStrategyInterface() = default;
    virtual void get_output(TomlComponentInterface *) = 0;
};

#endif