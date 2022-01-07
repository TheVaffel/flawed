#pragma once

#include <cstdio>
#include <type_traits>
#include <string>
#include <sstream>
#include <memory>

#include "../src/assert/assert_handlers.hpp"
#include "../src/assert/asserts.hpp"

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
};


/*
 * -- Assert macros
 */

#define fl_assert(x)                                                           \
  { ::flawed::_fl_assert(x, #x, __LINE__, __FILE__); }


#define _fl_assert_op(op, v0, v1, error_message)                        \
    { \
        ::flawed::_fl_assert_op(op(v0, v1), v0, v1, #v0, #v1, error_message, __LINE__, __FILE__); \
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
