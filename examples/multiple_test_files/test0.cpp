#include <flawed_testing.hpp>
#include <flawed_assert.hpp>

defineTestSuite("Test suite 0", [] {
    createTest("One succeeding test", [] {
        std::cout << "This is a nice test which succeeds" << std::endl;
    });

    createTest("Another succeeding test", [] {
        std::cout << "This is another nice test which succeeds" << std::endl;
    });
});
