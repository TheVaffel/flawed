
#include "./utils.hpp"
#include "../strings/data.hpp"

namespace flawed {
    void flawed_println(const std::string& message) {
        std::cerr << flawed::_flawed_title
                  << " "
                  << message
                  << std::endl;
    }
};
