#include "../include/flawed_testing.hpp"
#include "../include/flawed_assert.hpp"

#include <memory>
#include <exception>

/* class CustomTest : public TestSuiteBase {
public:
CustomTest() : TestSuiteBase("Custom Test") { */


createTestSuite("Custom Test", [] {
    // this->addTest("Most basic test", [] {
    createTest("Most basic test", [] {
            std::cout << "Hello hello" << std::endl;

            fl_assert("Everything is good" == std::string("Everything is good"));

            fl_assert_eq(std::string("Everything is bad"), std::string("Everything is good"));
        });

    // this->addTest("Throwing test", [] {
    createTest("Throwing test", [] {
            fl_assert_not_throwing([] {
                std::cout << "Harmless function running" << std::endl;
            });

            fl_assert_throwing([] {
                std::cout << "Harmful function running" << std::endl;
                throw std::runtime_error("Something bad happened!");
            });

            fl_assert_throwing([] {
                std::cout << "Harmless function running, expected to harm" << std::endl;
            });
        });

    // this->addTest("Throwing test 2", [] {
    createTest("Throwing test 2", [] {
            fl_assert_not_throwing([] {
                std::cout << "For my next trick, I will make bad code fail unexpectedly:" << std::endl;
                throw std::runtime_error("Oh no");
            });
        });

    // this->addTest("Succeeding test", [] {
    createTest("Succeeding test", [] {
        std::cout << "This is a test that actually succeeds. Woohoo!" << std::endl;
    });
});

// std::unique_ptr<TestSuiteBase> flawed::fl_test_suite =
//     std::make_unique<CustomTest>();
