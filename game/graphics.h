#pragma once

namespace Game
{

template <class E>
class Animation
{
public:
    virtual void render(E* entity) = 0;
};

}
