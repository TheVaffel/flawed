
#include "./utils.hpp"
#include "../strings/data.hpp"
#include "../strings/colors.hpp"
#include "../strings/string_conversion.hpp"

#include <sstream>

namespace flawed {
    std::string _flawed_getln(const std::string& message) {
        return flawed::_flawed_title
                  + " "
                  + message
                  + "\n";
    }

    std::string _flawed_assertion_error_getln(const std::string& message) {
        return flawed::_flawed_title
            + " "
            + flawed::_assertion_failed_string
            + " "
            + message
            + "\n";
    }

    std::string _get_location_str(int line_number, const std::string& file_name) {
            std::ostringstream oss;
            oss << _add_color(file_name, _fl_red) << ":" << _add_color(_to_string(line_number), _fl_red);
            return oss.str();
    }
};
