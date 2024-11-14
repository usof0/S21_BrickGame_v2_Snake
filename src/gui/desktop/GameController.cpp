#include "GameController.h"

namespace s21 {
    GameController::GameController(SnakeGame& game, FSM& fsm) : game(game), fsm(fsm) {}

    void GameController::handleInput(Direction direction) {
        game.changeDirection(direction);
    }

    void GameController::updateGame() {
        game.update();
        if (game.isGameOver()) fsm.transitionTo(GAME_OVER);
    }
}   // namespace s21
