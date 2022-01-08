#pragma once

#include <typeinfo>
#include <map>
#include <string>
#include <memory>
#include <concepts>

#include "../utils/error.hpp"

#include "./FlComparator.hpp"

namespace flawed {

    extern std::map<std::string, std::shared_ptr<ComparatorBase>> _comparatorMap;

    template<typename T>
    float _compare(const T& v0, const T& v1) {
        std::string type_name = _getTypeName<T>();
        if (_comparatorMap.find(type_name) == _comparatorMap.end()) {
            _report_internal_error("Could not find comparator for type " + type_name);
        }

        return std::static_pointer_cast<FlComparator<T>>(
            _comparatorMap[type_name]
            )->compare(v0, v1);
    }

    template<typename T>
    void _printComparatorError(const T& x, const T& y,
                               const std::string& sx, const std::string& sy,
                               int line_number, const std::string& file_name,
                               float value, float tolerance) {
        std::string type_name = _getTypeName<T>();
        if (_comparatorMap.find(type_name) == _comparatorMap.end()) {
            _report_internal_error("Could not find comparator for type " +
                                   type_name +
                                   " for printing error");
        }

        return std::static_pointer_cast<FlComparator<T>>(
            _comparatorMap[type_name]
            )->printError(x, y, sx, sy, line_number, file_name, value, tolerance);
    }


    template<typename T, typename ComparatorType, typename... Args>
    requires std::derived_from<ComparatorType, FlComparator<T>>
    void registerComparator(const Args&... args) {
        _comparatorMap[_getTypeName<T>()] = std::make_shared<ComparatorType>(args...);
    }


    /*
     * Not necessary for most use cases
     */
    template<typename T>
    void unregisterClassComparator() {
        _comparatorMap.erase(typeid(T).name());
    }
};
