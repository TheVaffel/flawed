
namespace flawed {

    /*
     * -- String converters
     */

    template <typename T>
    concept _fl_stringable = std::is_arithmetic<T>::value || std::convertible_to<T, std::string>;

    template <typename T>
    requires std::is_arithmetic<T>::value
    static std::string _to_string(const T& t) {
        std::ostringstream oss;
        oss << t;
        return oss.str();
    }

    template <typename T>
    requires std::convertible_to<T, std::string>
    static std::string _to_string(const T &t) { return (std::string)t; }
};
