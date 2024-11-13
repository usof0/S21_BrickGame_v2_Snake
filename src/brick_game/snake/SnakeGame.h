#ifndef BRICK_GAME_SNAKE_SNAKE_GAME_H
#define BRICK_GAME_SNAKE_SNAKE_GAME_H

#include <vector>
// #include <utility>

namespace s21 {
    enum Direction {UP, DOWN, LEFT, RIGHT};

    struct Point {
        int x;
        int y;
    };

    class SnakeGame {
    public:
        SnakeGame(int width, int height);
        void resetGame();
        void update();
        void changeDirection(Direction newDirection);
        bool isGameOver() const;
        int getScore() const;

    private:
        int width, height;
        int score;
        bool gameOver;
        Direction direction;
        std::vector<Point> snake;
        Point apple;

        void generateApple();
        void moveSnake();
        bool checkCollision() const;
        void checkEatApple() const;
    };

}   // namespace s21

#endif
