#include "./abbrev.hpp"

namespace flawed {
    static const int _FL_MAX_STRING_LENGTH = 80;
    static const int _FL_STRING_ABBREV_END_LENGTH = 30;

    std::string _abbrev_string(const std::string& str) {
        if (str.length() > _FL_MAX_STRING_LENGTH) {
            return str.substr(0, _FL_STRING_ABBREV_END_LENGTH) +
                "[...]" +
                str.substr(str.length() - _FL_STRING_ABBREV_END_LENGTH);
        }

        return str;
    }
};
