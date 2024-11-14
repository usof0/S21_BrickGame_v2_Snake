#ifndef GUI_DESKTOP_GAME_VIEW_H
#define GUI_DESKTOP_GAME_VIEW_H

#include <gtk/gtk.h>
#include <chrono>
#include "../../brick_game/snake/SnakeGame.h"
#include "GameController.h"

namespace s21 {

    class GameView {
    public:
        GameView(SnakeGame& game, GameController& controller);
        void run();
        // void setInputDelayMs(int n);

    private:
        // GTK+ Widgets
        GtkWidget *window;
        GtkWidget *drawingArea;
        
        // Game Logic
        SnakeGame &game;
        GameController &controller;
        const int cellSize = 40;  // Size of each cell in pixels     
        std::chrono::time_point<std::chrono::steady_clock> lastInputTime;
        int inputDelayMs = 40;  // Adjust delay in milliseconds

        // Private Methods
        static gboolean onDrawEvent(GtkWidget *widget, cairo_t *cr, gpointer data);
        static gboolean onKeyPress(GtkWidget *widget, GdkEventKey *event, gpointer data);
        static gboolean onGameUpdateWrapper(gpointer data);  // Wrapper for onGameUpdate
        gboolean onGameUpdate();  // Called periodically to update the game

        void drawGame(cairo_t *cr);  // Draws the current game state


    };

} 

#endif // namespace s21
