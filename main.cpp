#include "raylib.h"

int main() {
    const int screenWidth  = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Simple Player Box");
    SetTargetFPS(60);

    // Player: a 50x50 box sitting on the ground, starting in the middle
    const float groundY = screenHeight - 60.0f;
    Rectangle player = {
        screenWidth / 2.0f - 25.0f,  // x
        groundY - 50.0f,             // y (box bottom rests on the ground)
        50.0f,                       // width
        50.0f                        // height
    };
    const float speed = 300.0f;      // pixels per second

    while (!WindowShouldClose()) {
        // ---------- Update ----------
        float dt = GetFrameTime();   // seconds since last frame

        if (IsKeyDown(KEY_A)) player.x -= speed * dt;  // move left
        if (IsKeyDown(KEY_D)) player.x += speed * dt;  // move right

        // Keep the player inside the window
        if (player.x < 0) player.x = 0;
        if (player.x + player.width > screenWidth) player.x = screenWidth - player.width;

        // ---------- Draw ----------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectangle(0, (int)groundY, screenWidth, 60, LIGHTGRAY);  // ground
            DrawRectangleRec(player, BLUE);                              // player

            DrawText("Press A to move left, D to move right", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}