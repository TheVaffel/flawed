#include "../include/flawed_assert.hpp"

#include <iostream>
#include <memory>

namespace some_namespace {
    void run() {

        int v0 = 12, v1 = 23;

        float f0 = 0.5, f1 = 0.55;

        double d0 = 0.5, d1 = 0.55;

        flawed::set_assertion_handler(std::make_unique<flawed::NoOpAssertionHandler>());

        fl_assert(true);
        fl_assert(false);

        fl_assert_eq(v0, v1);
        fl_assert_eq(v0, v1);

        fl_assert_neq(v0, v1);
        fl_assert_neq(v0, v0);

        fl_assert_lt(v0, v1);
        fl_assert_lt(v0, v0);

        fl_assert_gt(v0, v1);
        fl_assert_gt(v0, v0);

        fl_assert_le(v1, v0);
        fl_assert_le(v0, v1);
        fl_assert_le(v0, v0);

        fl_assert_ge(v0, v1);
        fl_assert_ge(v0, v1);

        fl_assert_tolerance(f0, f1, 0.1);
        fl_assert_tolerance(f0, f1, 0.02);

        fl_assert_tolerance(d0, d1, 0.1);
        fl_assert_tolerance(d0, d1, 0.02);
    }
};

int main() {
    some_namespace::run();

    return 0;
}
