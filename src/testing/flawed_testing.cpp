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
            std::cerr << _flawed_getln(std::string("Got error: ") + ex.what());
        }

        return succeeded;
    }

    /*
     * Custom setup functions
     */
    static std::unique_ptr<std::function<void()>> onBeforeAll,
        onAfterAll,
        onBeforeEach,
        onAfterEach;

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

        if (onBeforeAll) {
            (*onBeforeAll)();
        }

        for (unsigned int i = 0; i < this->tests.size(); i++) {
            if (onBeforeEach) {
                (*onBeforeEach)();
            }

            bool succeeded = _run_test(this->tests[i].first, this->tests[i].second);

            if (onAfterEach) {
                (*onAfterEach)();
            }

            if (!succeeded) {
                num_failed++;
                _print_test_failed(this->tests[i].first);
            } else {
                _print_test_succeeded(this->tests[i].first);
            }

            std::cout << std::endl;
        }

        if (onAfterAll) {
            (*onAfterAll)();
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

    std::unique_ptr<TestSuite> _innerTestSuiteBase;

    void createTest(const std::string& name, const std::function<void()>& test) {
        _innerTestSuiteBase->addTest(name, test);
    }

    void beforeAll(const std::function<void()>& func) {
        onBeforeAll = std::make_unique<std::function<void()>>(func);
    }

    void beforeEach(const std::function<void()>& func) {
        onBeforeEach = std::make_unique<std::function<void()>>(func);
    }

    void afterAll(const std::function<void()>& func) {
        onAfterAll = std::make_unique<std::function<void()>>(func);
    }

    void afterEach(const std::function<void()>& func) {
        onAfterEach = std::make_unique<std::function<void()>>(func);
    }


    std::unique_ptr<TestSuite>&& createTestSuite(const std::string& name, const std::function<void()>& testRegistrer) {
        _innerTestSuiteBase = std::make_unique<TestSuite>(name);

        testRegistrer();

        return std::move(_innerTestSuiteBase);
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

    bool all_succeeded = test_suite->run();


    if (all_succeeded) {
        return 0;
    } else {
        return 1;
    }
}
