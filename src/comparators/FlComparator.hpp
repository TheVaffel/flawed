#pragma once

#include "../utils/utils.hpp"

#include <cxxabi.h>
#include <sstream>

namespace flawed {

    template<typename T>
    constexpr const char* _getTypeName() {
        return  __cxxabiv1::__cxa_demangle(typeid(T).name(), 0, 0, NULL);
    }

    class ComparatorBase {};

    template<typename T>
    class FlComparator : public ComparatorBase {
    public:
        void printError(const T& v0, const T& v1, float value, float tolerance) const {
            flawed_println(_assertion_failed_string +
                           " Difference exceeded tolerance in comparator for type " +
                           _getTypeName<T>());
            this->customPrintError(v0, v1, value, tolerance);
        }

        virtual void customPrintError(const T& v0, const T& v1, float value, float tolerance) const {
            std::ostringstream oss;
            oss << "Difference was " << value << ", but tolerance was " << tolerance << std::endl;
            flawed_println(oss.str());
        }

        virtual float compare(const T& v0, const T& v1) = 0;
        virtual ~FlComparator() = default;
    };
};
