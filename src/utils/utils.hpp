#include <iostream>

namespace flawed {
    void _flawed_println(const std::string& message);
    void _flawed_assertion_error_println(const std::string& message);
    std::string _get_location_str(int line_number, const std::string& file_name);
};
