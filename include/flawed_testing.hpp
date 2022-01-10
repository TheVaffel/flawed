#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <utility>

namespace flawed {
    class TestSuite {
        std::string name = "";
        std::vector<std::pair<const std::string, std::function<void()>>> tests;
    public:

        TestSuite(const std::string& name);

        std::string getName() const;

        void addTest(const std::string& name, const std::function<void()>& func);

        // Returns whether all tests succeeded
        bool run();
    };


    extern TestSuite* test_suite;

    TestSuite* _createTestSuite(const std::string& name, const std::function<void()>& func);
    void createTest(const std::string& name, const std::function<void()>& test);
};

#define createTestSuite(name, func) TestSuite* flawed::test_suite = _createTestSuite(name, func);

using namespace flawed;
