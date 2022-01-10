#include <iostream>

#include "../utils/utils.hpp"
#include "./assert_handlers.hpp"
#include "../utils/error.hpp"

namespace flawed {
    void ThrowAssertionHandler::handleAssertionFailed() {
        throw FlException("Assertion failed");
    }

    void NoOpAssertionHandler::handleAssertionFailed() { }


    /*
     * -- Global Assertion handler
     */

    std::unique_ptr<flawed::AssertionHandler> _assertion_handler = std::make_unique<ThrowAssertionHandler>();

    void set_assertion_handler(std::unique_ptr<AssertionHandler>&& assertion_handler) {
        _assertion_handler = std::move(assertion_handler);
    }

    void _run_assertion_failed_handler() {
        _assertion_handler->handleAssertionFailed();
    }
};
