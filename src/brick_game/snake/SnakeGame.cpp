#include "SnakeGame.h"
// #include <cstdlib>
#include <ctime>

namespace s21 {
    // public methods:
    SnakeGame::SnakeGame(int width, int height) : width(width), height(height) {
        resetGame();
    }

    void SnakeGame::resetGame() {
        score = 0;
        gameOver = false;
        direction = RIGHT;
        snake = { {width / 2, height / 2}, {width / - 1, height / 2}, {width / 2 - 2, height / 2} };
        generateApple();
    }

    void changeDirection(Direction newDirection) {
        if ((newDirection == UP && direction != DOWN) || (newDirection == DOWN && direction != UP) || (newDirection == LEFT && direction != RIGHT) || (newDirection == RIGHT && direction != LEFT)) {
            direction = newDirection;
        }
    }

    bool SnakeGame::isGameOver() const {return gameOver;}
    int SnakeGame::getScore() const {return score;}

    void SnakeGame::update() {
        if (!gameOver) {
            if (checkCollision()) gameOver = true;
            else if (checkEatApple()) {
                score++;
                Position newTail = snake.back();
                moveSnake();
                snake.insert(snake.end(), newTail);
                generateApple();
            }
        }
    }

    // private methods:
    void SnakeGame::generateApple() {
        srand(time(nullptr));
        apple = { rand() % width, rand() % height };
    }
    
    void SnakeGame::moveSnake() {
        Position newHead = snake.front();
        switch (direction) {
            case UP: newHead.y--; break;
            case DOWN: newHead.y++; break;
            case LEFT: newHead.x--; break;
            case RIGHT: newHead.x++; break;
        }
        snake.pop_back();
        snake.insert(snake.begin(), newHead);
    }



    void checkEatApple() const {
        if (snake.front().x == apple.x && snakeGame.front().y == apple.y)
            return true;
        return false;
    }

    bool SnakeGame::checkCollision() const {
        const Position head = snake.front();
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height)
            return true;
        for (const auto& part : snake) {
            if (part != snake.front() && part == head) return true;
        }
        return false;
    }

}   // namespace s21
