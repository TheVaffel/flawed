#pragma once

#include <type_traits>
#include <sstream>

#include "./FlComparator.hpp"
#include "../strings/string_conversion.hpp"

namespace flawed {

    template<typename T>
    requires std::floating_point<T>
    class FlNumericComparator final : public FlComparator<T> {
    public:
        FlNumericComparator() {}

        virtual std::string customGetError(const T& v0, const T& v1, float value, float tolerance) const override {
            std::ostringstream oss;
            oss << "Left side was " << _add_color(_to_string(v0), _fl_green)
                << ", right side was " << _add_color(_to_string(v1), _fl_red)
                << ", but max tolerance was " << _add_color(_to_string(tolerance), _fl_blue);

            return _flawed_getln(oss.str());
        }

        virtual float compare(const T& v0, const T& v1) override {
            return v1 - v0;
        }

        ~FlNumericComparator() { }
    };
};
