#include <flawed_testing.hpp>
#include <flawed_assert.hpp>

createTestSuite("Test suite 1", [] {
    createTest("A nice succeeding test", [] {
        std::cout << "Hello, I'm a succeeding test :)" << std::endl;
    });

    createTest("A not so nice failing test", [] {
        std::cout << "Evil ensues" << std::endl;
        throw std::runtime_error("Oh no");
    });
});
