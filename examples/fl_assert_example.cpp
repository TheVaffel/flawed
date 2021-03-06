#include "../include/flawed_assert.hpp"

#include <iostream>
#include <memory>

class CustomIntegralComparator : public flawed::FlComparator<int> {
    virtual float compare(const int& v0, const int& v1) override {
        return v1 - v0;
    }
};

namespace some_namespace {
    void run() {
        std::cout << "Beginning of run" << std::endl;

        int v0 = 12, v1 = 23;

        float f0 = 0.5, f1 = 0.55;

        double d0 = 0.5, d1 = 0.55;

        flawed::set_assertion_handler(std::make_unique<flawed::JustPrintAssertionHandler>());
        flawed::registerComparator<int, CustomIntegralComparator>();

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

        // Testing int comparator
        fl_assert_tolerance(v0, v1, 10);

        std::cout << "End of run" << std::endl;
    }
};

int main() {
    some_namespace::run();

    return 0;
}
