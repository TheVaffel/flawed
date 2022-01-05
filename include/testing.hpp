#include <string>
#include <memory>

namespace flawed {
    void die();

    class TestBase {
        std::string name = "";
    protected:

        TestBase(const std::string& name);
    public:

        std::string getName();
        virtual void run() = 0;
    };

    extern std::unique_ptr<TestBase> test;
};
