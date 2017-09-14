#pragma once

#include <ncurses.h>

namespace MyCurses
{

auto endCurses () -> void;
auto startCurses () -> void;
auto getMaxX() -> int;
auto getMaxY() -> int;

class Window
{
public:
    Window();
    Window(int startx, int starty, int width, int height);
    ~Window() { delwin(win); }

    void clear();

    inline int getchar() { wgetch(win); }
    inline void sleep(int period) { ::wtimeout(win, period); }
    void putText(int x, int y, char const* text);
    inline void putChar(int x, int y, char c) { mvwaddch(win, y, x, c); }
    inline void refresh() { wrefresh(win); }

private:
    void init(int startx, int starty, int width, int height);
    WINDOW* win;
};

}
