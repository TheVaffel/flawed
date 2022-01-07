#pragma once

#include <memory>

namespace flawed {

    /*
     * -- Assertionhandler interface and pre-implemented handlers
     */
    class AssertionHandler {
    public:
        virtual void handleAssertionFailed() = 0;
        virtual ~AssertionHandler() = default;
    };

    class ThrowAssertionHandler : public AssertionHandler {
    public:
        virtual void handleAssertionFailed();
    };

    class NoOpAssertionHandler : public AssertionHandler {
    public:
        virtual void handleAssertionFailed();
    };


    /*
     * -- External controls
     */

    void set_assertion_handler(std::unique_ptr<AssertionHandler>&& assertion_handler);

    void _run_assertion_failed_handler();
};
