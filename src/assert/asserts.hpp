#pragma once


#include "../comparators/comparator_registry.hpp"
#include "./assert_handlers.hpp"

namespace flawed {

    template<typename T>
    void _fl_assert_tolerance(const T& x, const T& y,
                              float tolerance,
                              int line_number, const std::string& file_name ) {
        float value = _compare(x, y);
        if (std::abs(value) > tolerance) {
            flawed::_printComparatorError<T>(x, y, value, tolerance);
            flawed::_run_assertion_failed_handler();
        }
    }

    template<typename T>
    static void _print_op_left_side(const T& v) {
        _flawed_println("\tLeft side: " + _add_color(_to_string(v), _fl_red));
    }

    template<typename T>
    static void _print_op_right_side(const T& v) {
        _flawed_println("\tRight side: " + _add_color(_to_string(v), _fl_green));
    }

    void _fl_assert_print_location(int line_number, const std::string& file_name);
    void _fl_print_assertion_failed_op_header(const std::string& s0, const std::string& s1, const std::string& comp_error);

    template<typename T>
    static void _print_op_assertion_failed_message(const T& v0, const T& v1,
                                                   const std::string& s0, const std::string& s1,
                                                   const std::string& op_error,
                                                   int line_number,
                                                   const std::string& file_name) {
            _fl_print_assertion_failed_op_header(s1, s1, op_error);

            _fl_assert_print_location(line_number, file_name);

            _print_op_left_side(v0);
            _print_op_right_side(v1);
    }

    template<typename T>
    void _fl_assert_op(bool b,
                       const T& v0, const T& v1,
                       const std::string& sv0, const std::string& sv1,
                       const std::string& error,
                       int line_number,
                       const std::string& file_name) {
        if (!b) {
            flawed::_print_op_assertion_failed_message(v0, v1, sv0, sv1, error, line_number, file_name);
            flawed::_run_assertion_failed_handler();
        }
    }



    void _fl_assert(bool b, const std::string assert_str, int line_number, const std::string& file_name);
};
