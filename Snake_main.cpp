#include <iostream>
#include <raylib.h>
#include <deque>
#include <stdexcept>

using namespace std;

const int cellsize = 30;
const int cellcount = 25;
const float baseSnakeSpeed = 0.05f;

class Snake {
public:
    deque<Vector2> body = { {6, 9}, {5, 9}, {4, 9} };
    Vector2 direction = { 1, 0 };
    float speed = baseSnakeSpeed;
    float movementAccumulator = 0.0f;

    void Move() {
        movementAccumulator += speed;
        if (movementAccumulator >= 1.0f) {
            Vector2 newHead = { body[0].x + direction.x, body[0].y + direction.y };
            body.push_front(newHead);
            body.pop_back();
            movementAccumulator = 0.0f;
        }
    }

    void Grow() {
        body.push_back(body.back());
    }

    void Draw() const {
        DrawCircle(body[0].x * cellsize + cellsize / 2, body[0].y * cellsize + cellsize / 2, cellsize / 2 - 1, GREEN);
        float eyeOffsetX = cellsize / 4;
        float eyeOffsetY = cellsize / 4;

        if (direction.x == 1) {
            DrawCircle(body[0].x * cellsize + 3 * cellsize / 4, body[0].y * cellsize + eyeOffsetY, cellsize / 8, BLACK);
            DrawCircle(body[0].x * cellsize + 3 * cellsize / 4, body[0].y * cellsize + 3 * cellsize / 4, cellsize / 8, BLACK);
        }
        else if (direction.x == -1) {
            DrawCircle(body[0].x * cellsize + eyeOffsetX, body[0].y * cellsize + eyeOffsetY, cellsize / 8, BLACK);
            DrawCircle(body[0].x * cellsize + eyeOffsetX, body[0].y * cellsize + 3 * cellsize / 4, cellsize / 8, BLACK);
        }
        else if (direction.y == 1) {
            DrawCircle(body[0].x * cellsize + eyeOffsetX, body[0].y * cellsize + 3 * cellsize / 4, cellsize / 8, BLACK);
            DrawCircle(body[0].x * cellsize + 3 * cellsize / 4, body[0].y * cellsize + 3 * cellsize / 4, cellsize / 8, BLACK);
        }
        else if (direction.y == -1) {
            DrawCircle(body[0].x * cellsize + eyeOffsetX, body[0].y * cellsize + eyeOffsetY, cellsize / 8, BLACK);
            DrawCircle(body[0].x * cellsize + 3 * cellsize / 4, body[0].y * cellsize + eyeOffsetY, cellsize / 8, BLACK);
        }

        for (size_t i = 1; i < body.size(); i++) {
            DrawCircle(body[i].x * cellsize + cellsize / 2, body[i].y * cellsize + cellsize / 2, cellsize / 2 - 1, GREEN);
        }
    }

    bool CheckFoodCollision(const Vector2& foodPos) const {
        return body[0].x == foodPos.x && body[0].y == foodPos.y;
    }

    bool CollidesWithItself() const {
        for (size_t i = 1; i < body.size(); i++) {
            if (body[0].x == body[i].x && body[0].y == body[i].y) {
                return true;
            }
        }
        return false;
    }

    bool OutOfBounds() const {
        return body[0].x <= 0 || body[0].x >= cellcount - 1 || body[0].y <= 0 || body[0].y >= cellcount - 1;
    }
};

class Food {
public:
    Vector2 position;

    Food() {
        position = GenerateRandomPos();
    }

    void Relocate() {
        position = GenerateRandomPos();
    }

    void Draw() const {
        float centerX = position.x * cellsize + cellsize / 2.0f;
        float centerY = position.y * cellsize + cellsize / 2.0f;
        float radius = cellsize / 4.3f;
        DrawCircle(centerX, centerY, radius, GOLD);
    }

    Vector2 GenerateRandomPos() const {
        return { static_cast<float>(GetRandomValue(1, cellcount - 2)), static_cast<float>(GetRandomValue(1, cellcount - 2)) };
    }
};

int main() {
    try {
        InitWindow(cellcount * cellsize, cellcount * cellsize, "Retro Snake");
        SetTargetFPS(60);

        Sound eatSound = LoadSound("/mnt/data/popup.mp3");
        Sound crashSound = LoadSound("/mnt/data/gameover.mp3");
        Music bgm = LoadMusicStream("/mnt/data/bgm.mp3");

        SetMusicVolume(bgm, 0.5f);
        PlayMusicStream(bgm);

        Snake snake;
        Food food;
        int score = 0;
        bool gameOver = false;

        while (!WindowShouldClose() && !gameOver) {
            UpdateMusicStream(bgm);

            if (IsKeyPressed(KEY_UP) && snake.direction.y == 0) snake.direction = { 0, -1 };
            if (IsKeyPressed(KEY_DOWN) && snake.direction.y == 0) snake.direction = { 0, 1 };
            if (IsKeyPressed(KEY_LEFT) && snake.direction.x == 0) snake.direction = { -1, 0 };
            if (IsKeyPressed(KEY_RIGHT) && snake.direction.x == 0) snake.direction = { 1, 0 };

            snake.Move();

            if (snake.CheckFoodCollision(food.position)) {
                food.Relocate();
                snake.Grow();
                score++;
                snake.speed += 0.01f; // Increment speed with each food eaten
                PlaySound(eatSound);
            }

            if (snake.CollidesWithItself() || snake.OutOfBounds()) {
                gameOver = true;
                PlaySound(crashSound);
                StopMusicStream(bgm);
            }

            BeginDrawing();
            ClearBackground(RED);

            DrawRectangle(0, 0, cellcount * cellsize, cellsize, BLACK);
            DrawRectangle(0, 0, cellsize, cellcount * cellsize, BLACK);
            DrawRectangle(cellcount * cellsize - cellsize, 0, cellsize, cellcount * cellsize, BLACK);
            DrawRectangle(0, cellcount * cellsize - cellsize, cellcount * cellsize, cellsize, BLACK);

            food.Draw();
            snake.Draw();
            DrawText(TextFormat("Score: %i", score), 10, 10, 20, WHITE);
            EndDrawing();
        }

        if (gameOver) {
            PlaySound(crashSound);
            for (int i = 0; i < 120; i++) {
                BeginDrawing();
                ClearBackground(RED);
                DrawText(TextFormat("Game Over! Final Score: %i", score),
                    cellcount * cellsize / 2 - MeasureText("Game Over! Final Score: 000", 44) / 2,
                    cellcount * cellsize / 2 - 22,
                    44,
                    WHITE);
                EndDrawing();
            }
        }

        UnloadSound(eatSound);
        UnloadSound(crashSound);
        UnloadMusicStream(bgm);
        CloseWindow();

    }
    catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred." << endl;
    }

    return 0;
}
