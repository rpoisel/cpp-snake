#include "cursesui.h"
#include "characters.h"
#include "game.h"

#include <sstream>

namespace Snake
{
namespace UI
{

WindowManager* WindowManager::getInstance()
{
    static WindowManager instance;
    return &instance;
}

void Curses::drawScoreText()
{
    std::stringstream s;
    s << "Score: " << snake.getSegments().size();
    WindowManager::getInstance()->getWindow().putText(
        (World::getSizeX() - s.str().length()) / 2, 0 , s.str().c_str()
    );
}

void Curses::render(std::list<std::shared_ptr<FoodProvider>> entities)
{
    WindowManager::getInstance()->getWindow().clear();

    drawScoreText();

    for (auto entity : entities)
    {
        entity->render();
    }
    snake.render();

    WindowManager::getInstance()->getWindow().refresh();
}

void Curses::boom()
{
    auto h = snake.head();
    WindowManager::getInstance()->getWindow().putText(h.x - 3, h.y, ">> BOOM <<");
}

int Curses::getcharBlocking()
{
    return ::getch();
}

int Curses::getcharNonBlocking()
{
    return WindowManager::getInstance()->getWindow().getchar();
}

void Setup::init()
{
    Curses::init();
}

void Setup::term()
{
}

void FoodProviderAvailableAnimation::render(FoodProvider* foodProvider)
{
    switch (foodProvider->getCnt())
    {
        case 1:
            UI::WindowManager::getInstance()->getWindow().putChar(foodProvider->getPos().x, foodProvider->getPos().y, '|');
            break;
        case 2:
            UI::WindowManager::getInstance()->getWindow().putChar(foodProvider->getPos().x, foodProvider->getPos().y, '/');
            break;
        case 3:
            UI::WindowManager::getInstance()->getWindow().putChar(foodProvider->getPos().x, foodProvider->getPos().y, '-');
            break;
        case 4:
            UI::WindowManager::getInstance()->getWindow().putChar(foodProvider->getPos().x, foodProvider->getPos().y, '\\');
            break;
        default:
            foodProvider->resetCnt();
    }
    foodProvider->incCnt();
}

void FoodProviderRespawningAnimation::render(FoodProvider* foodProvider)
{
    UI::WindowManager::getInstance()->getWindow().putChar(foodProvider->getPos().x, foodProvider->getPos().y, 'X');
}

void SnakeMovingAnimation::render(Snake* snake)
{
    for (Segments::const_iterator it = snake->getSegments().begin(); it != snake->getSegments().end(); it++)
    {
        UI::WindowManager::getInstance()->getWindow().putChar(it->x, it->y, '#');
    }
}

}

int World::getSizeX()
{
    return MyCurses::getMaxX();
}

int World::getSizeY()
{
    return MyCurses::getMaxY();
}

}

