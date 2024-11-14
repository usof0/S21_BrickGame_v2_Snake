#include "brick_game/snake/SnakeGame.h"
#include "gui/desktop/GameController.h"
#include "gui/desktop/GameView.h"
#include "brick_game/snake/FSM.h"

int main (void) {
    s21::SnakeGame game(20, 20);
    s21::FSM fsm;
    s21::GameController controller(game, fsm);
    s21::GameView view(game, controller);

    view.run();

    

    return 0;
}