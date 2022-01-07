
#include "./utils.hpp"
#include "../strings/data.hpp"
#include "../strings/colors.hpp"
#include "../strings/string_conversion.hpp"

#include <sstream>

namespace flawed {
    void _flawed_println(const std::string& message) {
        std::cerr << flawed::_flawed_title
                  << " "
                  << message
                  << std::endl;
    }

    void _flawed_assertion_error_println(const std::string& message) {
        std::cerr << flawed::_flawed_title
                  << " "
                  << flawed::_assertion_failed_string
                  << " "
                  << message
                  << std::endl;
    }

    std::string _get_location_str(int line_number, const std::string& file_name) {
            std::ostringstream oss;
            oss << _add_color(file_name, _fl_red) << ":" << _add_color(_to_string(line_number), _fl_red);
            return oss.str();
    }
};
