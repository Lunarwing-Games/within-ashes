#include <raylib.h>
#include <string>

int main(void)
{
    const int wWidth = 800;
    const int wHeight = 600;
    const int Framerate = 60;
    const std::string title = "Within Ashes";

    InitAudioDevice();
    InitWindow(wWidth, wHeight, title.c_str());
    SetTargetFPS(Framerate);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("WA Test 01", 128, 0, 20, BLACK);
            DrawFPS(0, 0);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}