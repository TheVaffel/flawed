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
        void printError(const T& v0, const T& v1,
                        const std::string& sv0, const std::string& sv1,
                        int line_number, const std::string& file_name,
                        float value, float tolerance) const {

            std::string location = _get_location_str(line_number, file_name);

            _flawed_assertion_error_println(
                           " Difference between " + _add_color(_getTypeName<T>(), _fl_blue)
                           + "s "
                           + _add_color(sv0, _fl_red) + " and " + _add_color(sv1, _fl_green)
                           + " exceeded tolerance");
            _flawed_println("At " + location);

            this->customPrintError(v0, v1, value, tolerance);
        }

        virtual void customPrintError(const T& v0, const T& v1,
                                      float value, float tolerance) const {
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
