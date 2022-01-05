#pragma once

#include <iostream>

#include "../strings/data.hpp"
#include "./utils.hpp"

namespace flawed {

    class FlException : public std::runtime_error {
    public:
        FlException(const std::string& str);
    };

    class FlAssertionError : public FlException {
    public:
        FlAssertionError(const std::string& str);
    };

    void _report_internal_error(const std::string& str);
};
