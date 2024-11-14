#include "GameView.h"
#include <cairo.h>

namespace s21 {

    GameView::GameView(SnakeGame& game, GameController& controller)
        : game(game), controller(controller), lastInputTime(std::chrono::steady_clock::now()) {
    }

    void GameView::run() {
        gtk_init(nullptr, nullptr);

        g_print("Checking before creating the window:\n");
        // Create main window
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "Snake Game");
        gtk_window_set_default_size(GTK_WINDOW(window), game.getWidth() * cellSize, game.getHeigh() * cellSize);
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

        g_print("Checking before creating the drawing area:\n");
        // Create drawing area
        drawingArea = gtk_drawing_area_new();
        gtk_container_add(GTK_CONTAINER(window), drawingArea);
        g_signal_connect(drawingArea, "draw", G_CALLBACK(onDrawEvent), this);

        g_print("Checking before connect key press event:\n");
        // Connect key press event
        gtk_widget_set_events(window, GDK_KEY_PRESS_MASK);
        g_signal_connect(window, "key-press-event", G_CALLBACK(onKeyPress), this);

        g_print("Checking before start game update:\n");
        // Start the game update timer (refreshes every 100ms)
        g_timeout_add(200, onGameUpdateWrapper, this);

        g_print("Checking show all:\n");
        gtk_widget_show_all(window);

        g_print("Game showed\n");  
        gtk_main();
    }

    gboolean GameView::onDrawEvent(GtkWidget *widget, cairo_t *cr, gpointer data) {
        auto *view = static_cast<GameView*>(data);
        view->drawGame(cr);
        return FALSE;
    }

    gboolean GameView::onKeyPress(GtkWidget *widget, GdkEventKey *event, gpointer data) {
        auto *view = static_cast<GameView*>(data);

        // Get the current time
        auto now = std::chrono::steady_clock::now();
        auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - view->lastInputTime).count();

        // Process the input only if enough time has passed
        if (elapsedMs >= view->inputDelayMs) {
            switch (event->keyval) {
                case GDK_KEY_Up:
                    view->controller.handleInput(UP);
                    break;
                case GDK_KEY_Down:
                    view->controller.handleInput(DOWN);
                    break;
                case GDK_KEY_Left:
                    view->controller.handleInput(LEFT);
                    break;
                case GDK_KEY_Right:
                    view->controller.handleInput(RIGHT);
                    break;
            }

            // Update last input time to the current time
            view->lastInputTime = now;
        }

        view->onGameUpdate();
        // view->controller.updateGame();
        gtk_widget_queue_draw(view->drawingArea);  // Refresh the screen
        return TRUE;

    }

    gboolean GameView::onGameUpdateWrapper(gpointer data) {
        auto *view = static_cast<GameView*>(data);
        return view->onGameUpdate();
    }

    gboolean GameView::onGameUpdate() {
        g_print("Checking if game is over: %d\n", game.isGameOver());

        if (!game.isGameOver()) {
            controller.updateGame();                  // Update the game state
            gtk_widget_queue_draw(drawingArea);       // Force redraw of the game area
            
            g_print("Game updated\n");  
            
            return TRUE;                              // Keep the timer running
        }
        return FALSE;                                 // Stop the timer if the game is over
    }

    void GameView::drawGame(cairo_t *cr) {
        // Clear the screen
        cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
        cairo_paint(cr);

        // Draw the snake
        cairo_set_source_rgb(cr, 0.0, 1.0, 0.0);
        for (const auto &segment : game.getSnake()) {
            cairo_rectangle(cr, segment.x * cellSize, segment.y * cellSize, cellSize, cellSize);
            cairo_fill(cr);
        }

        // Draw the apple
        cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
        cairo_rectangle(cr, game.getApple().x * cellSize, game.getApple().y * cellSize, cellSize, cellSize);
        cairo_fill(cr);
    }

    // void setInputDelayMs(int n) {
    //     inputDelayMs = n;
    // }
}
