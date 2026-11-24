// Simple 2D box game using raylib.
// Move the blue box around the window with W A S D. Press Esc to quit.

#include "raylib.h"
#include <cmath>

int main() {
    const int screenWidth  = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Simple Player Box");
    SetTargetFPS(60);

    // Player: a 50x50 box starting in the middle of the window
    Rectangle player = {
        screenWidth  / 2.0f - 25.0f,  // x
        screenHeight / 2.0f - 25.0f,  // y
        50.0f,                        // width
        50.0f                         // height
    };
    const float speed = 300.0f;       // pixels per second

    while (!WindowShouldClose()) {    // closes on Esc or the window's X button
        // ---------- Update ----------
        float dt = GetFrameTime();    // seconds since the last frame

        // Work out which way the player wants to go
        float moveX = 0.0f;
        float moveY = 0.0f;
        if (IsKeyDown(KEY_W)) moveY -= 1.0f;   // up
        if (IsKeyDown(KEY_S)) moveY += 1.0f;   // down
        if (IsKeyDown(KEY_A)) moveX -= 1.0f;   // left
        if (IsKeyDown(KEY_D)) moveX += 1.0f;   // right

        // Make diagonal movement the same speed as straight movement
        float length = std::sqrt(moveX * moveX + moveY * moveY);
        if (length > 0.0f) {
            player.x += (moveX / length) * speed * dt;
            player.y += (moveY / length) * speed * dt;
        }

        // Keep the player inside the window
        if (player.x < 0) player.x = 0;
        if (player.y < 0) player.y = 0;
        if (player.x + player.width  > screenWidth)  player.x = screenWidth  - player.width;
        if (player.y + player.height > screenHeight) player.y = screenHeight - player.height;

        // ---------- Draw ----------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // A light grid so you can see the box moving across the plane
            for (int x = 0; x < screenWidth; x += 50)  DrawLine(x, 0, x, screenHeight, LIGHTGRAY);
            for (int y = 0; y < screenHeight; y += 50) DrawLine(0, y, screenWidth, y, LIGHTGRAY);

            DrawRectangleRec(player, BLUE);
            DrawText("W A S D to move   |   Esc to quit", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
