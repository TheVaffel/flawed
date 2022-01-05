#include "../../include/testing.hpp"
#include "../../src/utils/error.hpp"
#include "../../include/flawed_assert.hpp"

namespace flawed {
    void die() { throw FlException("Died in testing"); }

    TestBase::TestBase(const std::string& name) {
        if (name.length() == 0) {
            std::cerr << _flawed_title << " Unspecified test name" << std::endl;
            die();
        }

        this->name = name;
    }

    std::string TestBase::getName() {
        return this->name;
    }

};


int main() {
    std::cerr << flawed::_flawed_title << " Running tests in " << flawed::test->getName() << std::endl;

    flawed::test->run();
}
