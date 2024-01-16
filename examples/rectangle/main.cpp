#include "../../src/tgl.h"

using namespace tgl;


int main() {
    tgl::internal::clear_window();


    tgl::Screen screen;
    tgl::Screen::hideCursor();

    int i = 0;
    while (i < 100) {
        screen.fill(TPixel{
                .fg=colors::FG::BLACK,
                .bg=colors::BG::BLACK,
                .pixel=' '
        });


        // Red rect -------------------------------------
        screen.drawRect(screen.width() / 3, screen.height() / 4, 10, 10, TPixel{
                .fg=colors::FG::RED,
                .bg=colors::BG::BLACK,
                .pixel='@',
        });

        // Red rect Green Background -------------------------------------
        screen.drawRect(5, 5, 100, 30, TPixel{
                .fg=colors::FG::RED,
                .bg=colors::BG::GREEN,
                .pixel='+',
        });

        screen.draw();
        screen.swapBuffers();
        usleep(1000000 / 60); // 60 fps
        i++;
    }

    tgl::Screen::showCursor();
    return 0;
}