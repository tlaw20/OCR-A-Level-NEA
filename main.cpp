// Simple 2D game using raylib: a sprite (picture) moved around with W A S D.
// The picture is loaded from assets/player.png. Press Esc to quit.

#include "raylib.h"
#include <cmath>

int main() {
    const int screenWidth  = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Simple Player Sprite");
    SetTargetFPS(60);

    // Look for files next to the .exe, no matter where the game was started from
    ChangeDirectory(GetApplicationDirectory());

    // Load the sprite. This must happen AFTER InitWindow.
    Texture2D sprite = LoadTexture("assets/player.png");
    SetTextureFilter(sprite, TEXTURE_FILTER_POINT);   // keeps pixel art sharp when scaled
    const bool spriteLoaded = (sprite.id != 0);       // id 0 means the file wasn't found

    // Player size: the size of the picture times a scale (2.0f would draw it twice as big)
    const float scale = 1.0f;
    const float playerWidth  = spriteLoaded ? sprite.width  * scale : 50.0f;
    const float playerHeight = spriteLoaded ? sprite.height * scale : 50.0f;

    Rectangle player = {
        screenWidth  / 2.0f - playerWidth  / 2.0f,   // x
        screenHeight / 2.0f - playerHeight / 2.0f,   // y
        playerWidth,
        playerHeight
    };
    const float speed = 300.0f;       // pixels per second
    bool facingRight = true;          // the picture is assumed to face right

    while (!WindowShouldClose()) {    // closes on Esc or the window's X button
        // ---------- Update ----------
        float dt = GetFrameTime();

        float moveX = 0.0f;
        float moveY = 0.0f;
        if (IsKeyDown(KEY_W)) moveY -= 1.0f;
        if (IsKeyDown(KEY_S)) moveY += 1.0f;
        if (IsKeyDown(KEY_A)) moveX -= 1.0f;
        if (IsKeyDown(KEY_D)) moveX += 1.0f;

        if (moveX > 0.0f) facingRight = true;
        if (moveX < 0.0f) facingRight = false;

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

            for (int x = 0; x < screenWidth; x += 50)  DrawLine(x, 0, x, screenHeight, LIGHTGRAY);
            for (int y = 0; y < screenHeight; y += 50) DrawLine(0, y, screenWidth, y, LIGHTGRAY);

            if (spriteLoaded) {
                // 'source' is the part of the picture to use: all of it.
                // A negative width flips the picture left-to-right.
                Rectangle source = {
                    0.0f, 0.0f,
                    facingRight ? (float)sprite.width : -(float)sprite.width,
                    (float)sprite.height
                };
                // Draw that picture so it fills the player's rectangle
                DrawTexturePro(sprite, source, player, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
            } else {
                // Fallback so you can see something is wrong: a blue box and a message
                DrawRectangleRec(player, BLUE);
                DrawText("Could not load assets/player.png", 10, 40, 20, RED);
            }

            DrawText("W A S D to move   |   Esc to quit", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    UnloadTexture(sprite);   // free the picture's memory
    CloseWindow();
    return 0;
}