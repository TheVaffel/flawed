#include "./comparator_registry.hpp"

#include "./FlNumericComparator.hpp"

#include <memory>

namespace flawed {

    std::map<std::string, std::shared_ptr<ComparatorBase>> _comparatorMap = {
        { _getTypeName<float>(), std::make_shared<FlNumericComparator<float>>() },
        { _getTypeName<double>(), std::make_shared<FlNumericComparator<double>>() }
    };

};
