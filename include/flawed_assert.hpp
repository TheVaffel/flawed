#pragma once

#include <cstdio>
#include <type_traits>
#include <string>
#include <sstream>
#include <memory>

#include "../src/assert/asserts.hpp"

namespace flawed {

/*
 * -- Utility functions for assertion macros
 */

    template <typename T, typename U>
    requires std::equality_comparable_with<T, U>
    bool _eq(const T& v0, const U& v1) {
        return v0 == v1;
    }

    template <typename T, typename U>
    requires std::equality_comparable_with<T, U>
    bool _neq(const T& v0, const U& v1) {
        return v0 != v1;
    }

    template <typename T, typename U>
    bool _lt(const T& v0, const U& v1) {
        return v0 < v1;
    }

    template <typename T, typename U>
    bool _gt(const T& v0, const U& v1) {
        return v0 > v1;
    }

    template <typename T, typename U>
    bool _le(const T& v0, const U& v1) {
        return v0 <= v1;
    }

    template <typename T, typename U>
    bool _ge(const T& v0, const U& v1) {
        return v0 >= v1;
    }
};


/*
 * -- Assert macros
 */

#ifdef FLAWED_IGNORE
#define _FLAWED_ID(x) { ; }
#else
#define _FLAWED_ID(x) x
#endif

#define fl_assert(x)                                                           \
  _FLAWED_ID({ ::flawed::_fl_assert(x, #x, __LINE__, __FILE__); })

#define _fl_assert_op(op, v0, v1, error_message)                               \
  _FLAWED_ID({                                                                 \
    ::flawed::_fl_assert_op(op(v0, v1), v0, v1, #v0, #v1, error_message,       \
                            __LINE__, __FILE__);                               \
  })

#define fl_assert_eq(x, y)                                                     \
  _FLAWED_ID({ _fl_assert_op(::flawed::_eq, x, y, "was equal to"); })

#define fl_assert_neq(x, y)                                                    \
  _FLAWED_ID({ _fl_assert_op(::flawed::_neq, x, y, "was not equal to"); })

#define fl_assert_lt(x, y)                                                     \
  _FLAWED_ID({ _fl_assert_op(::flawed::_lt, x, y, "was less than"); })

#define fl_assert_gt(x, y)                                                     \
  _FLAWED_ID({ _fl_assert_op(::flawed::_gt, x, y, "was greater than"); })

#define fl_assert_le(x, y)                                                     \
  _FLAWED_ID(                                                                  \
      { _fl_assert_op(::flawed::_le, x, y, "was less than or equal to"); })

#define fl_assert_ge(x, y)                                                     \
  _FLAWED_ID(                                                                  \
      { _fl_assert_op(::flawed::_ge, x, y, "was greater than or equal to"); })

#define fl_assert_tolerance(x, y, tolerance)                                   \
  _FLAWED_ID({                                                                 \
    ::flawed::_fl_assert_tolerance(x, y, #x, #y, tolerance, __LINE__,          \
                                   __FILE__);                                  \
  })

#define fl_assert_not_throwing(func)                                           \
  _FLAWED_ID(                                                                  \
      { ::flawed::_fl_assert_not_throwing(func, #func, __LINE__, __FILE__); })

#define fl_assert_throwing(func)                                               \
  _FLAWED_ID(                                                                  \
      { ::flawed::_fl_assert_throwing(func, #func, __LINE__, __FILE__); })
