#ifndef TOML_COMPONENT_TEMPLATE_HPP_
#define TOML_COMPONENT_TEMPLATE_HPP_

template <typename T> class TomlComponentTemplate {
private:
    T value;

public:
    TomlComponentTemplate() = default;
    explicit TomlComponentTemplate(const T &value) { this->value = value; }

    auto get_value() -> T & {
        return value;
    }; // adding const keyword results in binding error

    // this function is only used for int, float, bool and string
    void set_value(const T &new_value) { value = new_value; }
};

#endif