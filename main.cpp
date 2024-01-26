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

    const float mapScale{4.0f};

    SetTargetFPS(60);

    // Instantiate Knight
    Character knight{WINDOW_DIM[0], WINDOW_DIM[1]};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        knight.tick(GetFrameTime());

        // Check map bounds
        if (knight.getWorldPos().x < 0.f || 
        knight.getWorldPos().y < 0.f || 
        knight.getWorldPos().x + WINDOW_DIM[0] > map.width * mapScale || 
        knight.getWorldPos().y + WINDOW_DIM[1] > map.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}