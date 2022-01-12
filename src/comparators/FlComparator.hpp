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
        std::string getError(const T& v0, const T& v1,
                        const std::string& sv0, const std::string& sv1,
                        int line_number, const std::string& file_name,
                        float value, float tolerance) const {

            std::string location = _get_location_str(line_number, file_name);

            std::string error_string =
                _flawed_assertion_error_getln(
                    " Difference between " + _add_color(_getTypeName<T>(), _fl_blue)
                    + "s "
                    + _add_color(sv0, _fl_red) + " and " + _add_color(sv1, _fl_green)
                    + " exceeded tolerance");
            error_string += _flawed_getln("At " + location);

            return error_string + this->customGetError(v0, v1, value, tolerance);
        }

        virtual std::string customGetError(const T& v0, const T& v1,
                                           float value, float tolerance) const {
            std::ostringstream oss;

            oss << "Difference was " << _add_color(_to_string(value), _fl_red)
                << ", but tolerance was " << _add_color(_to_string(tolerance), _fl_blue)
                << std::endl;

            return _flawed_getln(oss.str());
        }

        virtual float compare(const T& v0, const T& v1) = 0;
        virtual ~FlComparator() = default;
    };
};
