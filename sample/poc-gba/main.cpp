#include <cstdint>
#include <raylib.h>
#include <string>

extern "C"
{
  __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
  __declspec(dllexport) unsigned long AmdPowerXpressRequestHighPerformance =
    0x00000001;
}

int
main()
{
  std::string window_title = "pokeport";
  uint32_t window_width = 240;
  uint32_t window_height = 160;
  uint32_t scale_factor = 4;

  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(window_width * scale_factor,
             window_height * scale_factor,
             window_title.c_str());

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello, Raylib!", 0, 0, 32, LIGHTGRAY);
    EndDrawing();
  }

  CloseWindow();
}