#include "../../src/tgl.h"
#include <cmath>
#include <vector>
#include <chrono>
#include <thread>

using namespace tgl;

struct bubble {
    float x;
    float y;
    float r;
    float r2;

    float vx, vy;

    explicit bubble(float x, float y, float r) : x(x), y(y), r(r), r2(r / 2), vx(0), vy(0) {
    }

    [[nodiscard]] bool isColliding(bubble other) const {
        return std::hypot(x - other.x, y - other.y) <= (r + other.r);
    }

    void move() {
        x += vx;
        y += vy;
    }
};

float randf(float min, float max) {
    return ((static_cast<float>(rand()) / RAND_MAX) * (max - min)) + min;
}

int main() {
    srand(time(0));
    tgl::internal::clear_window();
    tgl::Screen screen;
    tgl::Screen::hideCursor();

    TPixel p{
            .fg=tgl::colors::FG::RED,
            .bg=tgl::colors::BG::GREEN,
            .pixel='*'
    };
    std::vector<bubble> group;
    for (int i = 0; i < 12; i++) {
        bubble item(randf(10, screen.width() - 10), randf(10, screen.height() - 10), 5);
        item.vx = randf(.01, 1);
        item.vy = randf(.01, 1);
        group.push_back(item);
    }

    int i = 0;
    while (i < 1000) {
        screen.fill(TPixel{
                .fg=tgl::colors::FG::DEFAULT,
                .bg=tgl::colors::BG::DEFAULT,
                .pixel=' '
        });
        for (auto &item: group) {
            item.move();
        }

        for (auto &item: group) {
            if (item.x < item.r || item.x > (screen.width() - item.r)) {
                item.vx *= -1;
            }

            if (item.y < item.r2 || item.y > (screen.height() - item.r2)) {
                item.vy *= -1;
            }
        }

        for (auto &item: group) {
            screen.drawEllipse(item.x, item.y, item.r, item.r2, p);
        }
        i++;

        screen.draw();
        screen.swapBuffers();
        std::this_thread::sleep_for(std::chrono::microseconds(1000000 / 24));
    }

    tgl::Screen::showCursor();
    return 0;
}