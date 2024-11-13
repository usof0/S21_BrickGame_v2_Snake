#ifndef GUI_DESKTOP_GAME_CONTROLLER_H
#define GUI_DESKTOP_GAME_CONTROLLER_H

#include "SnakeGame.h"
#include "FSM.h"

namespace s21 {
    class GameController {
    public:
        GameController(SnakeGame& game, FSM& fsm);
        void hanleInput(Direction direction);
        void updateGame();
        
    private:
        SnakeGame& game;
        FSM& fsm;

    }
}   // namespace s21

#endif
