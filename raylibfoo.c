#include "raylib.h"
#include <time.h>

const int width = 640;
const int height = 480;
const int numBalls = 500;

typedef struct {
  int posX;
  int posY;
  int radius;
  int velX;
  int velY;
  Color col;
} Ball;

void randomize(Ball *balls) {
  SetRandomSeed(time(0));
  for (int i=0; i < numBalls; i++) {
    balls[i].posX = GetRandomValue(balls[i].radius, width - balls[i].radius);
    balls[i].posY = GetRandomValue(balls[i].radius, height - balls[i].radius);
    balls[i].radius = GetRandomValue(5, 20);
    balls[i].velX = GetRandomValue(-2, 2);
    balls[i].velY = GetRandomValue(-2, 2);
    balls[i].col = (Color){
      .r = GetRandomValue(0,255),
      .g = GetRandomValue(0,255),
      .b = GetRandomValue(0,255),
      .a = 255};
  }
}

int main(void) {
  Ball balls[numBalls];
  randomize(balls);
  SetTargetFPS(60);
  InitWindow(width, height, "raylibfoo");
  while (!WindowShouldClose())
  {
      BeginDrawing();
      ClearBackground(WHITE);

      if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        randomize(balls);
      for (int i=0; i < numBalls; i++) {
        if (balls[i].posX + balls[i].radius > width)
          balls[i].velX = -1;
        else if (balls[i].posX - balls[i].radius < 0)
          balls[i].velX = 1;
        else if (balls[i].posY + balls[i].radius > height)
          balls[i].velY = -1;
        else if (balls[i].posY - balls[i].radius < 0)
          balls[i].velY = 1;
        balls[i].posX += balls[i].velX;
        balls[i].posY += balls[i].velY;
      }
      for (int i=0; i < numBalls; i++) {
        DrawCircle(balls[i].posX, balls[i].posY, balls[i].radius, balls[i].col);
      }
      EndDrawing();
  }

  CloseWindow();

  return 0;
}