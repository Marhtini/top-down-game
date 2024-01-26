#include <raylib.h>
#include "raymath.h"
#include "character.h"

int main()
{

    const int WINDOW_DIM[2]{384, 384};
    InitWindow(WINDOW_DIM[0], WINDOW_DIM[1], "Top Down Game!");

    Texture2D map = LoadTexture("nature_tileset/worldmap.png");
    float mapX{0};
    Vector2 mapPos{mapX, 0.0};
    
    SetTargetFPS(60);

    // Instantiate Knight
    Character knight{};
    knight.setScreenPos(WINDOW_DIM[0], WINDOW_DIM[1]);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        knight.tick(GetFrameTime());

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}