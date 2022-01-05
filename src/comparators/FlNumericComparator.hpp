#pragma once

#include <type_traits>
#include <sstream>

#include "./FlComparator.hpp"

namespace flawed {

    template<typename T>
    requires std::integral<T> || std::floating_point<T>
    class FlNumericComparator final : public FlComparator<T> {
    public:
        FlNumericComparator() {}

        virtual void printError(const T& v0, const T& v1, float value, float tolerance) const {
            std::ostringstream oss;
            oss << "Left side was " << v0
                << ", right side was " << v1
                << ", but max tolerance was " << tolerance << std::endl;

            flawed_println(oss.str());
        }

        virtual float compare(const T& v0, const T& v1) {
            return v1 - v0;
        }

        ~FlNumericComparator() { }
    };
};
