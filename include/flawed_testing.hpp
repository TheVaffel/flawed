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

    std::unique_ptr<TestSuite>&& createTestSuite(const std::string& name, const std::function<void()>& func);
    void createTest(const std::string& name, const std::function<void()>& test);

    void beforeAll(const std::function<void()>& func);
    void afterAll(const std::function<void()>& func);
    void beforeEach(const std::function<void()>& func);
    void afterEach(const std::function<void()>& func);
};


extern std::unique_ptr<flawed::TestSuite> test_suite;

#define defineTestSuite(name, func) std::unique_ptr<flawed::TestSuite> test_suite = createTestSuite(name, func);

using namespace flawed;
