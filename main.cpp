#include "characters.h"
#include "states.h"
#include <cursesui.h>
#include <fsm.h>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    size_t numFoodProviders = 100;
    try
    {
        if (argc > 1)
        {
            numFoodProviders = std::stoi(argv[1]);
        }
    }
    catch(std::invalid_argument& exc)
    {
        std::cerr << "Error parsing command line argument: " << exc.what() << std::endl;
        return EXIT_FAILURE;
    }
    srand(time(NULL));

    Snake::UI::Setup::init();

    Snake::Snake snake(std::make_shared<Snake::UI::SnakeMovingAnimation>());


    std::list<std::shared_ptr<Snake::FoodProvider>> foodProviders;
    for (size_t cnt = 0; cnt < numFoodProviders; cnt++)
    {
        foodProviders.push_back(std::make_shared<Snake::FoodProvider>(
            std::make_shared<Snake::UI::FoodProviderAvailableAnimation>(),
            std::make_shared<Snake::UI::FoodProviderRespawningAnimation>()
            ));
    }

    Snake::UI::Curses ui(snake);

    int c = ui.getcharNonBlocking();
    while(c != 27 && c != 'q')
    {
        snake.setDir(c);

        snake.update();
        std::for_each(foodProviders.begin(), foodProviders.end(),
            [](std::shared_ptr<Snake::FoodProvider>& foodProvider) { foodProvider->update(); });

        bool hasEaten = false;
        for (auto& foodProvider : foodProviders)
        {
            hasEaten = foodProvider->isAvailable() && snake.head() == foodProvider->getPos();
            if (hasEaten)
            {
                foodProvider->getFSM()->changeState(
                    Snake::FoodRespawningState::getInstance()
                );
                break;
            }
        }
        if (!hasEaten)
        {
            snake.trimTail();
        }
        if (snake.hasCrashed())
        {
            ui.boom();
            ui.getcharBlocking();
            break;
        }

        ui.render(foodProviders);
        usleep(100000);
        c = ui.getcharNonBlocking();
    }

    return 0;
}
