#pragma once

#include <string>

namespace flawed {
    const std::string _fl_red        = "31";
    const std::string _fl_green      = "32";
    const std::string _fl_blue       = "34";
    const std::string _fl_default    = "39";

    const std::string _fl_bg_red     = "41";
    const std::string _fl_bg_green   = "42";
    const std::string _fl_bg_blue    = "44";
    const std::string _fl_bg_default = "49";

    std::string _add_color(const std::string& str, const std::string& color);
};
