#include "characters.h"
#include "states.h"

#include <algorithm>

namespace Snake
{

FoodProvider::FoodProvider(
        std::shared_ptr<Game::Animation<FoodProvider>> availableAnimation,
        std::shared_ptr<Game::Animation<FoodProvider>> respawningAnimation
    ) :
    GameEntity(this, FoodAvailableState::getInstance()),
    availableAnimation(availableAnimation),
    respawningAnimation(respawningAnimation)
{
    reposition();
}

void FoodProvider::reposition()
{
    curPos.x = (rand() % (World::getSizeX() - 2) + 1);
    curPos.y = (rand() % (World::getSizeY() - 2) + 1);
}

Snake::Snake(std::shared_ptr<Game::Animation<Snake>> animation) :
        GameEntity(this, SnakeMovingState::getInstance()), movingAnimation(animation) {}

void Snake::setDir(int dir)
{
    if (dir != -1 && (dir == 'h' || dir == 'j' || dir == 'k' || dir == 'l'))
    {
        this->dir = dir;
    }
}

bool Snake::hasCrashed() const
{
    auto begin = segments.begin();
    std::advance(begin, 1);
    return std::find(begin, segments.end(), segments.front()) != segments.end();
}

}

