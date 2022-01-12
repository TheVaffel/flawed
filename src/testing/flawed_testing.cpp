#include "../../include/flawed_testing.hpp"
#include "../../include/flawed_assert.hpp"

#include "../../src/utils/error.hpp"
#include "../../src/utils/utils.hpp"

namespace flawed {
    static void die() { throw FlException("Died in testing"); }

    static void _print_test_failed(const std::string& test_name) {
        std::cerr << _flawed_getln(_add_color(test_name, _fl_blue) + _add_color(" failed", _fl_red));
    }

    static void _print_test_succeeded(const std::string& test_name) {
        std::cerr << _flawed_getln(_add_color(test_name, _fl_blue) + _add_color(" succeeded", _fl_green));
    }

    static bool _run_test(const std::string& name, const std::function<void()>& func) {

        bool succeeded = true;
        std::cerr << _flawed_getln("Running test " + _add_color(name, _fl_blue));

        try {
            func();
        } catch (const std::exception& ex) {
            succeeded = false;
        }

        return succeeded;
    }

    TestSuite::TestSuite(const std::string& name) {
        if (name.length() == 0) {
            std::cerr << _flawed_getln("Unspecified test name");
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

        set_assertion_handler(std::make_unique<ThrowAssertionHandler>(true));

        for (unsigned int i = 0; i < this->tests.size(); i++) {
            bool succeeded = _run_test(this->tests[i].first, this->tests[i].second);

            if (!succeeded) {
                num_failed++;
                _print_test_failed(this->tests[i].first);
            } else {
                _print_test_succeeded(this->tests[i].first);
            }

            std::cout << std::endl;
        }

        if (num_failed > 0) {
            std::cerr << _flawed_getln(_add_color(_to_string(num_failed)
                                                  + " out of "
                                                  + _to_string(this->tests.size()), _fl_red)
                                       + _add_color(" tests failed in test suite ", _fl_red)
                                       + _add_color(this->getName(), _fl_blue));
        } else {
            std::cerr << _flawed_getln(_add_color("All tests for ", _fl_green)
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

    static void _print_test_suite_header(const std::string& suite_name) {
        std::string header_text = "Running tests in " + suite_name;
        std::string colored_header_text = "Running tests in " + _add_color(suite_name, _fl_blue);

        std::string line;
        line.resize(header_text.length());
        std::fill(line.begin(), line.end(), '=');

        std::string header = flawed::_flawed_getln(line) +
            flawed::_flawed_getln(colored_header_text) +
            flawed::_flawed_getln(line);
    }
};

int main() {

    _print_test_suite_header(test_suite->getName());

    bool all_succeeded = flawed::test_suite->run();

    delete flawed::test_suite;

    if (all_succeeded) {
        return 0;
    } else {
        return 1;
    }
}
