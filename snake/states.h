#pragma once

#include "characters.h"

namespace Snake
{

class FoodAvailableState : public Game::State<FoodProvider>
{
public:
    static FoodAvailableState* getInstance();
    void execute(FoodProvider* foodProvider) {}
    void render(FoodProvider* foodProvider) {
        foodProvider->getAvailableAnimation()->render(foodProvider);
    }
private:
    FoodAvailableState() {}
};

class FoodRespawningState : public Game::State<FoodProvider>
{
public:
    static FoodRespawningState* getInstance();
    void execute(FoodProvider* foodProvider);
    void render(FoodProvider* foodProvider) {
        foodProvider->getRespawningAnimation()->render(foodProvider);
    }
private:
    FoodRespawningState() {}
};

class SnakeMovingState : public Game::State<Snake>
{
public:
    static SnakeMovingState* getInstance();
    void execute(Snake* snake);
    void render(Snake* snake) { snake->getMovingAnimation()->render(snake); }
private:
    SnakeMovingState() {}
};

}
