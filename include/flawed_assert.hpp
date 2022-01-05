#pragma once

#include <cstdio>
#include <type_traits>
#include <string>
#include <sstream>
#include <memory>

#include "../src/assert/assert_handlers.hpp"
#include "../src/strings/data.hpp"
#include "../src/strings/colors.hpp"
#include "../src/strings/abbrev.hpp"
#include "../src/strings/string_conversion.hpp"

#include "../src/comparators/FlComparator.hpp"
#include "../src/comparators/FlNumericComparator.hpp"
#include "../src/comparators/comparator_registry.hpp"

namespace flawed {

/*
 * -- Utility functions for assertion macros
 */

    template <typename T>
    static bool _eq(const T& v0, const T& v1) {
        return v0 == v1;
    }

    template <typename T>
    static bool _neq(const T& v0, const T& v1) {
        return v0 != v1;
    }

    template <typename T>
    static bool _lt(const T& v0, const T& v1) {
        return v0 < v1;
    }

    template <typename T>
    static bool _gt(const T& v0, const T& v1) {
        return v0 > v1;
    }

    template <typename T>
    static bool _le(const T& v0, const T& v1) {
        return v0 <= v1;
    }

    template <typename T>
    static bool _ge(const T& v0, const T& v1) {
        return v0 >= v1;
    }

    template<typename T>
    void _fl_assert_tolerance(const T& x, const T& y,
                              float tolerance,
                              int line_number, const std::string& file_name ) {
        float value = _compare(x, y);
        if (std::abs(value) > tolerance) {
            flawed::_printComparatorError<T>(x, y, value, tolerance);
            flawed::_run_assertion_handler();
            std::cout << "Did some assertion thing" << std::endl;
        }
    }

};


/*
 * -- Assert macros
 */

#define fl_assert(x)                                                    \
    {                                                                   \
        if (!x) {                                                       \
            fprintf(stderr, "%s %s \"%s\" at line %d in file %s\n",     \
                    ::flawed::_flawed_title.c_str(), ::flawed::_assertion_failed_string.c_str(), \
                    ::flawed::_add_color(#x, ::flawed::_fl_blue).c_str(), __LINE__, __FILE__); \
            flawed::_run_assertion_handler();                           \
        }                                                               \
    }

#define _fl_assert_op(op, v0, v1, error_message)                        \
    {                                                                   \
        if (!op(v0, v1)) {                                              \
            fprintf(stderr,                                             \
                    "%s %s Expected that %s %s %s, but it was "         \
                    "not the case:"                                     \
                    "\nAt %s:%s\n\tLeft side: %s\n\tRight side: %s\n",  \
                    ::flawed::_flawed_title.c_str(), ::flawed::_assertion_failed_string.c_str(), \
                    ::flawed::_add_color(#v0, ::flawed::_fl_green).c_str(), error_message, \
                    ::flawed::_add_color(#v1, ::flawed::_fl_red).c_str(), \
                    ::flawed::_add_color(__FILE__, ::flawed::_fl_red).c_str(), \
                    ::flawed::_add_color(::flawed::_to_string(__LINE__), ::flawed::_fl_red).c_str(), \
                    ::flawed::_add_color(::flawed::_abbrev_string(::flawed::_to_string(v0)), ::flawed::_fl_green).c_str(), \
                    ::flawed::_add_color(::flawed::_abbrev_string(::flawed::_to_string(v1)), ::flawed::_fl_red).c_str()); \
            flawed::_run_assertion_handler();                           \
        }                                                               \
    }


#define fl_assert_eq(x, y)                                      \
    { _fl_assert_op(::flawed::_eq, x, y, "was equal to"); }

#define fl_assert_neq(x, y)                                             \
    { _fl_assert_op(::flawed::_neq, x, y, "was not equal to"); }

#define fl_assert_lt(x, y)                                      \
    { _fl_assert_op(::flawed::_lt, x, y, "was less than"); }

#define fl_assert_gt(x, y)                                      \
    { _fl_assert_op(::flawed::_gt, x, y, "was greater than"); }

#define fl_assert_le(x, y)                                              \
    { _fl_assert_op(::flawed::_le, x, y, "was less than or equal to"); }

#define fl_assert_ge(x, y)                                              \
    { _fl_assert_op(::flawed::_ge, x, y, "was greater than or equal to"); }

#define fl_assert_tolerance(x, y, tolerance) \
    { ::flawed::_fl_assert_tolerance(x, y, tolerance, __LINE__, __FILE__); }
