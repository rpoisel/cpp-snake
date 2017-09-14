#include "states.h"

namespace Snake
{

FoodAvailableState* FoodAvailableState::getInstance()
{
    static FoodAvailableState instance;
    return &instance;
}

FoodRespawningState* FoodRespawningState::getInstance()
{
    static FoodRespawningState instance;
    return &instance;
}

void FoodRespawningState::execute(FoodProvider* foodProvider)
{
    foodProvider->incCntRespawn();
    if (foodProvider->getCntRespawn() == 50)
    {
        foodProvider->resetCntRespawn();
        foodProvider->reposition();
        foodProvider->getFSM()->changeState(FoodAvailableState::getInstance());
    }
}

SnakeMovingState* SnakeMovingState::getInstance()
{
    static SnakeMovingState instance;
    return &instance;
}

void SnakeMovingState::execute(Snake* snake)
{
    switch(snake->getDir())
    {
        case 'h':
            snake->getSegments().insert(snake->getSegments().begin(), {
                    snake->head().x == 1 ? World::getSizeX() - 2 : snake->head().x - 1,
                    snake->head().y
                    });
            break;
        case 'l':
            snake->getSegments().insert(snake->getSegments().begin(), {
                    snake->head().x == World::getSizeX() - 2 ? 1 : snake->head().x + 1, snake->head().y
                    });
            break;
        case 'j':
            snake->getSegments().insert(snake->getSegments().begin(), {
                    snake->head().x, snake->head().y == World::getSizeY() - 2 ? 1 : snake->head().y + 1
                    });
            break;
        case 'k':
            snake->getSegments().insert(snake->getSegments().begin(), {
                    snake->head().x, snake->head().y == 1 ? World::getSizeY() - 2 : snake->head().y - 1
                    });
            break;
        default:
            break;
    }
}

}
