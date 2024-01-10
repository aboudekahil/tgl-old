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


    tgl::Screen screen;
    tgl::Screen::hideCursor();

    while(true) {

    }

    tgl::Screen::showCursor();
    return 0;
}
