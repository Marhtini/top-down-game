#include <raylib.h>
#include "raymath.h"

class Character{
    public:
        Vector2 getWorldPos(){ return worldPos;}
    
    private:
        Texture2D texture;
        Texture2D idle;
        Texture2D run;
        Vector2 screenPos;
        Vector2 worldPos;
        // 1: facing right, -1: facing left.
        float rightLeft{1.f};
        // Animation variables
        float runningTime{0};
        int frame{0};
        const int MAXFRAMES{6};
        const float UPDATETIME{1.f/12.f};

};


int main(){

    const int WINDOW_DIM[2]{384, 384};
    InitWindow(WINDOW_DIM[0], WINDOW_DIM[1], "Top Down Game!");
    
    Texture2D map = LoadTexture("nature_tileset/worldmap.png");
    float mapX{0};
    Vector2 mapPos{mapX, 0.0};
    
    // Movement speed (scale)
    float speed{4.0};

    Texture2D knight{};
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");

    Vector2 knightPos{
        (float)WINDOW_DIM[0]/2.0f - 4.0f * (0.5f * (float)knight_idle.width/6.0f),
        (float)WINDOW_DIM[1]/2.0f - 4.0f * (0.5f * (float)knight_idle.height)
    };

    // 1: facing right, -1: facing left.
    float rightLeft{1.f};

    // Animation variables
    float runningTime{0};
    int frame{0};
    const int MAXFRAMES{6};
    const float UPDATETIME{1.f/12.f};

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
            // check if left or right
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            knight = knight_run;

        }
        else{
            knight = knight_idle;
        }

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // update animation frame
        runningTime += GetFrameTime();
        if (runningTime >= UPDATETIME){
            frame++;
            runningTime = 0.f;
            if (frame > MAXFRAMES) frame = 0;
        }

        // Draw the character
        Rectangle source{frame * (float)knight.width / 6.f, 0.f, rightLeft * (float)knight.width / 6.f, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}