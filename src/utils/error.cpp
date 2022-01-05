#include "./error.hpp"

namespace flawed {

    FlException::FlException(const std::string& str) : std::runtime_error(_flawed_title + " " + str) { }

    FlAssertionError::FlAssertionError(const std::string& str) : FlException(_assertion_failed_string + " " + str) { }

    void _report_internal_error(const std::string& str) {
        flawed_println(_add_color("Encountered internal error:", _fl_bg_red) +  " " + str);
        throw std::logic_error(str);
    }
};
