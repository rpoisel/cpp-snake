#pragma once

#include "graphics.h"

namespace Game
{

template <class E>
class State
{
public:
    virtual void execute(E* entity) = 0;
    virtual void render(E* entity) = 0;
private:
};

template <class E>
class FSM
{
public:
    FSM(E* owner, State<E>* initState) : owner(owner), curState(initState) {}
    void update() { curState->execute(owner); }
    void render() { curState->render(owner); }
    void changeState(State<E>* newState) { curState = newState; }
private:
    E* owner;
    State<E>* curState;
};

}
