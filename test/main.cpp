#include "../src/tgl.h"
#include <unistd.h>
#include <cmath>
#include <valarray>

typedef struct p {
    tgl::TPixel v;
    float x{};
    float y{};
} p;

using namespace tgl::colors;

int main() {
    tgl::internal::clear_window();

    p person{{FG_COLORS::FG_DEFAULT, BG_COLORS::BG_RED, '@'}, 2.f, 2.f};

    tgl::Screen screen(5, 5);
    tgl::Screen::hideCursor();
    tgl::TPixel p{.fg = FG_COLORS::FG_DEFAULT, .bg = BG_COLORS::BG_DEFAULT, .pixel = ' '};
    int t = 0;
    float angle = 0.01;
    while (t++ < 10000) {
        screen.fill(p);
        float x2 = person.x + 1;
        float y2 = person.y + 1;
        screen.drawLine(person.x, person.y, x2, y2, person.v);
        screen.draw();
        angle += 0.05;
    }

    tgl::Screen::showCursor();
    return 0;
}
