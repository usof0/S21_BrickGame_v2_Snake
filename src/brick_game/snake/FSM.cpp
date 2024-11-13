#include "FSM.h"

namespace s21 {
    FSM::FSM : currentState(INIT) {}

    void FSM::transitionTo(GameState state) {
        currentState = state;
    }

    GameState FSM::getState() const {
        return currentState;
    }

} // namespase s21
