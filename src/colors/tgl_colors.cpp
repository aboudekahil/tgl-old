//
// Created by aboud on 1/4/2024.
//

#include <ostream>
#include "tgl_colors.h"

namespace tgl::colors {

    std::ostream &operator<<(std::ostream &out, FG_COLORS c) {
        out << get_fg_color(c);
        return out;
    }


    std::ostream &operator<<(std::ostream &out, BG_COLORS c) {
        out << get_bg_color(c);
        return out;
    }
}
