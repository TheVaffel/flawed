#include <iostream>

#include "../utils/utils.hpp"
#include "./assert_handlers.hpp"
#include "../utils/error.hpp"

namespace flawed {

    ThrowAssertionHandler::ThrowAssertionHandler(bool silent) {
        this->silent = silent;
    }

    void ThrowAssertionHandler::handleAssertionFailed(const std::string& message) {
        if (!silent) {
            std::cerr << message << std::endl;
        }
        throw FlException("Assertion failed");
    }

    void JustPrintAssertionHandler::handleAssertionFailed(const std::string& message) {
        std::cerr << message << std::endl;
    }


    /*
     * -- Global Assertion handler
     */

    std::unique_ptr<flawed::AssertionHandler> _assertion_handler = std::make_unique<ThrowAssertionHandler>();

    void set_assertion_handler(std::unique_ptr<AssertionHandler>&& assertion_handler) {
        _assertion_handler = std::move(assertion_handler);
    }

    void _run_assertion_failed_handler(const std::string& message) {
        _assertion_handler->handleAssertionFailed(message);
    }
};
