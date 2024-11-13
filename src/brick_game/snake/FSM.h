#ifndef BRICK_GAME_SNAKE_FSM_H
#define BRICK_GAME_SNAKE_FSM_H

namespace s21 {
    enum GameState {INIT, PLAYING, PAUSED, GAME_OVER};

    class FSM {
    public:
        FSM();
        void transitionTo(GameState state);
        GameState getState() const;

    private:
        GameState currentState;
    };

} // namespace s21

#endif
