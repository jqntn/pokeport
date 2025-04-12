#include <cstdint>
#include <raylib.h>
#include <string>

#include "graphics/diffuse.h"
#include "graphics/helmet.h"

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
  uint32_t window_width = 1280;
  uint32_t window_height = 720;
  uint32_t scale_factor = 1;

  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
  InitWindow(window_width * scale_factor,
             window_height * scale_factor,
             window_title.c_str());

  Mesh mesh = {
    .vertexCount = HELMET_VERTEX_COUNT,
    .triangleCount = HELMET_TRIANGLE_COUNT,
    .vertices = HELMET_VERTEX_DATA,
    .texcoords = HELMET_TEXCOORD_DATA,
    .normals = HELMET_NORMAL_DATA,
    .indices = HELMET_INDEX_DATA,
  };

  Image image = {
    .data = DIFFUSE_DATA,
    .width = DIFFUSE_WIDTH,
    .height = DIFFUSE_HEIGHT,
    .mipmaps = 1,
    .format = DIFFUSE_FORMAT,
  };

  UploadMesh(&mesh, false);
  Model model = LoadModelFromMesh(mesh);
  Texture2D texture = LoadTextureFromImage(image);
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
  Vector3 position = Vector3{ 0.0f, 1.0f, 0.0f };

  Camera camera = {
    .position = Vector3{ 2.0f, 2.0f, 2.0f },
    .target = position,
    .up = Vector3{ 0.0f, 1.0f, 0.0f },
    .fovy = 50.0f,
    .projection = CAMERA_PERSPECTIVE,
  };

  while (!WindowShouldClose()) {
    UpdateCamera(&camera, CAMERA_ORBITAL);

    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(camera);
    DrawModel(model, position, 1.0f, WHITE);
    DrawGrid(10, 1.0f);
    EndMode3D();

    EndDrawing();
  }

  UnloadTexture(texture);
  UnloadModel(model);

  CloseWindow();
}