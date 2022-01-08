#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <utility>

namespace flawed {
    class TestSuiteBase {
        std::string name = "";
        std::vector<std::pair<const std::string, std::function<void()>>> tests;
    protected:

        TestSuiteBase(const std::string& name);
    public:

        void addTest(const std::string& name, const std::function<void()>& func);
        std::string getName() const;
        void run();
        virtual ~TestSuiteBase() = default;
    };

    extern std::unique_ptr<TestSuiteBase> fl_test_suite;
};
