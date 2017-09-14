#include "mycurses.h"
#include <cstdlib>
#include <system_error>

namespace MyCurses
{

static bool curses_started = false;
static int maxX;
static int maxY;

auto endCurses () -> void
{
    if (curses_started && !isendwin())
    {
        endwin();
    }
}

auto startCurses () -> void
{
    if (curses_started)
    {
        ::refresh();
    }
    else
    {
        initscr();
        cbreak();
        noecho();
        curs_set(0);
        keypad(stdscr, 1);
        atexit(endCurses);
        getmaxyx(stdscr,maxY, maxX);
        curses_started = true;
    }
}

auto getMaxX() -> int
{
    return maxX;
}

auto getMaxY() -> int
{
    return maxY;
}

Window::Window()
{
    init(0, 0, maxX, maxY);
}

Window::Window(int startx, int starty, int width, int height)
{
    init(startx, starty, width, height);
}

void Window::init(int startx, int starty, int width, int height)
{
    ::refresh();
    win = newwin(height, width, starty, startx);
    nodelay(win, TRUE);
    if (!win)
    {
        throw std::system_error(ENOMEM, std::generic_category());
    }
    this->clear();
}

void Window::putText(int x, int y, char const* text)
{
    mvwprintw(win, y, x, text);
    wrefresh(win);
}

void Window::clear()
{
    wclear(win);
    box(win, 0, 0);
}

}
