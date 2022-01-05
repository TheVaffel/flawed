#include "./colors.hpp"

namespace flawed {

    std::string _add_color(const std::string& str, const std::string& color) {
        return "\033[" + color + "m" + str + "\033[39m\033[49m";
    }

}
