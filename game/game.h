#pragma once

#include "fsm.h"

#include <memory>

namespace Game
{

struct Pos
{
    int x;
    int y;
    bool operator==(Pos const& other) const { return x == other.x && y == other.y; }
};

template <class E>
class GameEntity
{
public:
    GameEntity(E* owner, State<E>* initState) : fsm(owner, initState) {}
    virtual ~GameEntity() {}
    void render() { fsm.render(); }
    void update() { fsm.update(); }
    Game::FSM<E>* getFSM() { return &fsm; }
private:
    Game::FSM<E> fsm;
};
}

namespace Snake
{

class World final
{
public:
    static int getSizeX();
    static int getSizeY();
private:
    World() {}
};

template <class E>
class State : public Game::State<E>
{
public:
    State(std::shared_ptr<Game::Animation<E>> animation) : animation(animation) {}
    Game::Animation<E>* getAnimation() { return animation; }
    void render(E* entity) { animation->render(entity); }
private:
    std::shared_ptr<Game::Animation<E>> animation;
};

namespace UI
{

class Setup final
{
public:
    static void init();
    static void term();
private:
    Setup() {}
};

}

}
