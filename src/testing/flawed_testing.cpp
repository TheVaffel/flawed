#include "../../include/flawed_testing.hpp"
#include "../../include/flawed_assert.hpp"

#include "../../src/utils/error.hpp"
#include "../../src/utils/utils.hpp"

namespace flawed {
    static void die() { throw FlException("Died in testing"); }

    static void _print_test_failed(const std::string& test_name) {
        _flawed_println(_add_color(test_name, _fl_blue) + _add_color(" failed", _fl_red));
    }

    static void _print_test_succeeded(const std::string& test_name) {
        _flawed_println(_add_color(test_name, _fl_blue) + _add_color(" succeeded", _fl_green));
    }

    TestSuite::TestSuite(const std::string& name) {
        if (name.length() == 0) {
            _flawed_println("Unspecified test name");
            die();
        }

        this->name = name;
    }

    std::string TestSuite::getName() const {
        return this->name;
    }

    void TestSuite::addTest(const std::string& name,
                                const std::function<void()>& func) {
        this->tests.push_back(std::make_pair(name, func));
    }

    bool TestSuite::run() {

        int num_failed = 0;

        set_assertion_handler(std::make_unique<ThrowAssertionHandler>());

        for (unsigned int i = 0; i < this->tests.size(); i++) {
            bool failed = false;
            _flawed_println("Running test " + _add_color(this->tests[i].first, _fl_blue));

            try {
                this->tests[i].second();
            } catch (const std::exception& ex) {
                failed = true;
            }

            if (failed) {
                num_failed++;
                _print_test_failed(this->tests[i].first);
            } else {
                _print_test_succeeded(this->tests[i].first);
            }

            std::cout << std::endl;
        }

        if (num_failed > 0) {
            _flawed_println(_add_color(_to_string(num_failed)
                                       + " out of "
                                       + _to_string(this->tests.size()), _fl_red)
                            + _add_color(" tests failed in test suite ", _fl_red)
                            + _add_color(this->getName(), _fl_blue));
        } else {
            _flawed_println(_add_color("All tests for ", _fl_green)
                            + _add_color(this->getName(), _fl_blue)
                            + _add_color(" passed", _fl_green));
        }

        return num_failed == 0;
    }

    TestSuite* _innerTestSuiteBase;

    void createTest(const std::string& name, const std::function<void()>& test) {
        _innerTestSuiteBase->addTest(name, test);
    }

    TestSuite* _createTestSuite(const std::string& name, const std::function<void()>& testRegistrer) {
        _innerTestSuiteBase = new TestSuite(name);

        testRegistrer();

        return _innerTestSuiteBase;
    }

};



int main() {
    flawed::_flawed_println("Running tests in " + flawed::_add_color(flawed::test_suite->getName(), flawed::_fl_blue));

    bool all_succeeded = flawed::test_suite->run();

    delete flawed::test_suite;

    if (all_succeeded) {
        return 0;
    } else {
        return 1;
    }
}
