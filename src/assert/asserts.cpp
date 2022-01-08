#include "./asserts.hpp"

#include <sstream>
#include <stdexcept>

#include "../utils/utils.hpp"
#include "../strings/abbrev.hpp"

namespace flawed {

    void _fl_assert_print_location(int line_number, const std::string& file_name) {
        std::string location = _get_location_str(line_number, file_name);

        std::ostringstream oss;
        oss << "At " << location;
        _flawed_println(oss.str());
    }

    void _fl_print_assertion_failed_op_header(const std::string& s0,
                                              const std::string& s1,
                                              const std::string& op_error) {
        std::ostringstream oss;
        oss << "Expected that "
            << _add_color(s0, _fl_red) << " "
            << op_error << " "
            << _add_color(s1, _fl_green)
            << ", but it was not the case.";

        _flawed_assertion_error_println(oss.str());
    }

    void _fl_assert(bool b, const std::string assert_str, int line_number, const std::string& file_name) {
        if (!b) {
            std::ostringstream oss;
            const std::string location = _get_location_str(line_number, file_name);

            oss << "\"" << _add_color(assert_str, _fl_blue) << "\" at " << location;

            _flawed_assertion_error_println(oss.str());

            _run_assertion_failed_handler();
        }
    }

    void _fl_assert_not_throwing(const std::function<void()>& func,
                                 const std::string& sfunc,
                                 int line_number,
                                 const std::string& file_name) {
        try {
            func();
        } catch (const std::exception& ex) {
            std::string location = _get_location_str(line_number, file_name);
            _flawed_assertion_error_println("Expected " +
                                            _add_color(_abbrev_string(sfunc, 70), _fl_red) +
                                            " not to throw, but it did");
            _flawed_println("At " + location);

            _flawed_println(std::string("what(): ") + ex.what());

            _run_assertion_failed_handler();
        }
    }

    void _fl_assert_throwing(const std::function<void()>& func,
                             const std::string& sfunc,
                             int line_number,
                             const std::string& file_name) {
        bool thrown = false;
        try {
            func();
        } catch (...) {
            thrown = true;
        }

        if (!thrown) {
            std::string location = _get_location_str(line_number, file_name);
            _flawed_assertion_error_println("Expected " +
                                            _add_color(_abbrev_string(sfunc, 70), _fl_red) +
                                            " to throw, but it didn't");
            _flawed_println("At " + location);

            _run_assertion_failed_handler();
        }
    }

};