#include <raylib.h>
#include "raymath.h"

int main(){

    const int WINDOW_DIM[2]{384, 384};
    InitWindow(WINDOW_DIM[0], WINDOW_DIM[1], "Top Down Game!");
    
    Texture2D map = LoadTexture("nature_tileset/worldmap.png");
    float mapX{0};
    Vector2 mapPos{mapX, 0.0};

    float speed{4.0};

    SetTargetFPS(60);

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{0};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if (Vector2Length(direction) != 0.0){
            // set mapPos = mapPos - direction
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
        }

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
       
        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}