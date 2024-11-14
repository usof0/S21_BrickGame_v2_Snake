#include "SnakeGame.h"
#include <cstdlib>
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

    void SnakeGame::changeDirection(Direction newDirection) {
        if ((newDirection == UP && direction != DOWN) || (newDirection == DOWN && direction != UP) || (newDirection == LEFT && direction != RIGHT) || (newDirection == RIGHT && direction != LEFT)) {
            direction = newDirection;
        }
    }

    bool SnakeGame::isGameOver() const {return gameOver;}
    int SnakeGame::getScore() const {return score;}

    void SnakeGame::update() {
        if (!gameOver) {
            // moveSnake();
            if (checkCollision()) gameOver = true;
            else if (checkEatApple()) {
                generateApple();
                score++;
                Point newTail = snake.back();
                moveSnake();
                snake.insert(snake.end(), newTail);
            } else moveSnake();
        }
    }

    int SnakeGame::getWidth() const {
        return width;
    }

    int SnakeGame::getHeigh() const {
        return height;
    }

    std::vector<Point> SnakeGame::getSnake() const {
        return snake;
    }
    Point SnakeGame::getApple() const {
        return apple;
    }

    // private methods:
    void SnakeGame::generateApple() {
        srand(time(nullptr));
        apple = { rand() % width, rand() % height };
    }
    
    void SnakeGame::moveSnake() {
        Point newHead = snake.front();
        switch (direction) {
            case UP: newHead.y--; break;
            case DOWN: newHead.y++; break;
            case LEFT: newHead.x--; break;
            case RIGHT: newHead.x++; break;
        }
        snake.insert(snake.begin(), newHead);
        snake.pop_back();
        
    }


    bool SnakeGame::checkEatApple() const {
        if (snake.front().x == apple.x && snake.front().y == apple.y)
            return true;
        return false;
    }

    bool SnakeGame::checkCollision() const {
        const Point head = snake.front();
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height)
            return true;
        for (int i = 1; i < snake.size(); i++) {
            if (head.x == snake[i].x && head.y == snake[i].y) return true;
        }
        // for (const auto& part : snake) {
        //     if ((part.x == snake.front().x && part.y == snake.front().y) && (part.x == head.x && part.y == head.y)) return true;
        // }
        return false;
    }

}   // namespace s21
