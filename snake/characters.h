#pragma once

#include <fsm.h>
#include <game.h>

#include <cstdlib>
#include <list>

namespace Snake
{

class FoodProvider : public Game::GameEntity<FoodProvider>
{
public:
    FoodProvider(
        std::shared_ptr<Game::Animation<FoodProvider>> availableAnimation,
        std::shared_ptr<Game::Animation<FoodProvider>> respawningAnimation
    );
    virtual ~FoodProvider() {}
    Game::Pos const& getPos() { return curPos; }
    void reposition();
    void incCnt() { cnt++; }
    void resetCnt() { cnt = 0; }
    int getCnt() const { return cnt; }
    inline auto getAvailableAnimation() const { return availableAnimation; }
    inline auto getRespawningAnimation() const { return respawningAnimation; }
    inline bool isAvailable() const { return cntRespawn == 0; }
    inline void resetCntRespawn() { cntRespawn = 0; }
    inline void incCntRespawn() { cntRespawn++; }
    inline auto getCntRespawn() const { return cntRespawn; }
private:
    Game::Pos curPos = { 1, 1 };
    int cnt = {(::rand() % 4) + 1};
    std::shared_ptr<Game::Animation<FoodProvider>> availableAnimation;
    std::shared_ptr<Game::Animation<FoodProvider>> respawningAnimation;
    int cntRespawn = {0};
    
};

typedef std::list<Game::Pos> Segments;

class Snake : public Game::GameEntity<Snake>
{
public:
    Snake(std::shared_ptr<Game::Animation<Snake>> animation);
    virtual ~Snake() {}
    inline int getDir() const { return dir; }
    void setDir(int dir);
    bool hasCrashed() const;
    inline Game::Pos const& head() const { return segments.front(); }
    inline void trimTail() { segments.pop_back(); }
    inline Segments& getSegments() { return segments; }
    inline Game::Pos const& getPos() { return head(); }

    inline auto getMovingAnimation() const { return movingAnimation; }

private:
    int dir = 'l';
    std::list<Game::Pos> segments = { {12, 10}, {11, 10}, {10, 10} };
    std::shared_ptr<Game::Animation<Snake>> movingAnimation;
};

}
