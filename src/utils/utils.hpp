#include <iostream>

namespace flawed {
    std::string _flawed_getln(const std::string& message);
    std::string _flawed_assertion_error_getln(const std::string& message);
    std::string _get_location_str(int line_number, const std::string& file_name);
};
