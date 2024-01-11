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

        // Big red line -------------------------------------------
        screen.drawLine(0, 0, screen.width(), screen.height(), TPixel{
                .fg=colors::FG::RED,
                .bg=colors::BG::BLACK,
                .pixel='@',
        });

        // Triangle with lines -------------------------------------
        screen.drawLine(screen.width() / 3, screen.height() / 4, screen.width() / 4, screen.height() / 2, TPixel{
                .fg=colors::FG::GREEN,
                .bg=colors::BG::BLACK,
                .pixel='@',
        });
        screen.drawLine(screen.width() / 3, screen.height() / 4, screen.width() / 2.5, screen.height() / 2, TPixel{
                .fg=colors::FG::GREEN,
                .bg=colors::BG::BLACK,
                .pixel='@',
        });
        screen.drawLine(screen.width() / 4, screen.height() / 2, screen.width() / 2.5, screen.height() / 2, TPixel{
                .fg=colors::FG::GREEN,
                .bg=colors::BG::BLACK,
                .pixel='@',
        });

        screen.draw();
        screen.swapBuffers();
        usleep(1000000/60); // 60 fps
        i++;
    }

    tgl::Screen::showCursor();
    return 0;
}