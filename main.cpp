#include <raylib.h>
#include "raymath.h"
#include "character.h"
#include "prop.h"

int main()
{

    const int WINDOW_DIM[2]{384, 384};
    InitWindow(WINDOW_DIM[0], WINDOW_DIM[1], "Top Down Game!");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    float mapX{0};
    Vector2 mapPos{mapX, 0.0};

    const float mapScale{4.0f};

    SetTargetFPS(60);

    // Instantiate Knight
    Character knight{WINDOW_DIM[0], WINDOW_DIM[1]};

    // Prop array
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/log.png")}};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // Render props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());

        // Check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + WINDOW_DIM[0] > map.width * mapScale ||
            knight.getWorldPos().y + WINDOW_DIM[1] > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // Check prop collision
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec())){
                knight.undoMovement();
            }
        }

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}