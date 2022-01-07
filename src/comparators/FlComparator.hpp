#pragma once

#include "../utils/utils.hpp"
#include "../strings/colors.hpp"
#include "../strings/data.hpp"
#include "../strings/string_conversion.hpp"

#include <cxxabi.h>
#include <sstream>

namespace flawed {

    template<typename T>
    constexpr const char* _getTypeName() {
        return  __cxxabiv1::__cxa_demangle(typeid(T).name(), 0, 0, NULL);
    }

    class ComparatorBase { public: virtual ~ComparatorBase() = default; };

    template<typename T>
    class FlComparator : public ComparatorBase {
    public:
        void printError(const T& v0, const T& v1, float value, float tolerance) const {
            _flawed_println(_assertion_failed_string +
                           " Difference exceeded tolerance in comparator for type " +
                           _add_color(_getTypeName<T>(), _fl_blue));
            this->customPrintError(v0, v1, value, tolerance);
        }

        virtual void customPrintError(const T& v0, const T& v1, float value, float tolerance) const {
            std::ostringstream oss;
            oss << "Difference was " << _add_color(_to_string(value), _fl_red)
                << ", but tolerance was " << _add_color(_to_string(tolerance), _fl_blue)
                << std::endl;
            _flawed_println(oss.str());
        }

        virtual float compare(const T& v0, const T& v1) = 0;
        virtual ~FlComparator() = default;
    };
};
