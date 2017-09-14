#pragma once

#include <characters.h>
#include <game.h>
#include "graphics.h"

#include <mycurses.h>

#include <list>
#include <memory>

namespace Snake
{
namespace UI
{

class WindowManager
{
public:
    static WindowManager* getInstance();
    MyCurses::Window& getWindow() { return window; }
private:
    WindowManager() :
        window(0, 0, World::getSizeX(), World::getSizeY()) {}

    MyCurses::Window window;
};

class Curses
{
public:
    Curses(Snake& snake) : snake(snake) {}
    static void init() { MyCurses::startCurses(); }

    void render(std::list<std::shared_ptr<FoodProvider>> entities);
    void boom();
    int getcharBlocking();
    int getcharNonBlocking();
private:
    void drawScoreText();
    Snake& snake;
};

class FoodProviderAvailableAnimation : public Game::Animation<FoodProvider>
{
public:
    void render(FoodProvider* foodProvider);
private:
};

class FoodProviderRespawningAnimation : public Game::Animation<FoodProvider>
{
public:
    void render(FoodProvider* foodProvider);
private:
};

class SnakeMovingAnimation : public Game::Animation<Snake>
{
public:
    void render(Snake* snake);
private:
};

}
}
