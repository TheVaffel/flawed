#include "./abbrev.hpp"

namespace flawed {
    std::string _abbrev_string(const std::string& str, int max_length) {
        if (str.length() > max_length) {
            return str.substr(0, max_length / 2 - 3) +
                "..." +
                str.substr(str.length() - (max_length / 2 - 3));
        }

        return str;
    }
};
