#pragma once

#include <memory>

namespace flawed {

    /*
     * -- Assertionhandler interface and pre-implemented handlers
     */
    class AssertionHandler {
    public:
        virtual void handleAssertionFailed(const std::string& message) = 0;
        virtual ~AssertionHandler() = default;
    };

    class ThrowAssertionHandler : public AssertionHandler {
        bool silent;
    public:
        ThrowAssertionHandler(bool silent = false);

        virtual void handleAssertionFailed(const std::string& message);
    };

    class JustPrintAssertionHandler : public AssertionHandler {
    public:
        virtual void handleAssertionFailed(const std::string& message);
    };


    /*
     * -- External controls
     */

    void set_assertion_handler(std::unique_ptr<AssertionHandler>&& assertion_handler);

    void _run_assertion_failed_handler(const std::string& message);
};
