#include <cstdio>
#include "raylib.h"


// BALL Structure

struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle((int) x, (int) y, radius, WHITE);	
	}
	
};
struct Ball ball;


// PADDLE Structure

struct Paddle
{
	float x, y;
	float speed;
	float width, height;
	float maxY, minY;

	Rectangle GetRect()
	{
		return Rectangle { x - width / 2, y - height / 2, 10, 100 };
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), WHITE);
	}
};
struct Paddle leftPaddle;
struct Paddle rightPaddle;


// Border Structure

struct Border
{
	float x, y;
	float width, height;

	Rectangle GetRect()
	{
		return Rectangle { x, y, width, height };
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), WHITE);
	}
};
struct Border topBorder;
struct Border bottomBorder;





void GameScreen()
{
		// Winner Text Variable

	const char *winnerText = nullptr;


	// Player Score

	int RS = 0;
	int LS = 0;


	// Ball 

	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 300;
	ball.speedY = 300;


	// Left Paddle

	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 800;
	leftPaddle.maxY = GetScreenHeight() - leftPaddle.height;
	leftPaddle.minY = 0;


	// Right Paddle

	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 800;
	rightPaddle.maxY = GetScreenHeight() - rightPaddle.height;
	rightPaddle.minY = 0;


	// Top Border

	topBorder.x = 0;
	topBorder.y = 0;
	topBorder.width = GetScreenWidth();
	topBorder.height = 5;


	// Bottom Border

	bottomBorder.x = 0;
	bottomBorder.y = GetScreenHeight() - 5;
	bottomBorder.width = GetScreenWidth();
	bottomBorder.height = GetScreenHeight();


	// Game Loop

	while(!WindowShouldClose())
	{
		// INT score converted to CHAR

		char leftScore[10];
		sprintf(leftScore, "%i", LS);
		char rightScore[10];
		sprintf(rightScore, "%i", RS);


		// Initial ball movement

		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();


		// Ball UP and DOWN Collision

		if (ball.y < 0 )
		{
			ball.y = 0;
			ball.speedY *= -1;
		}
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}


		// Paddle Controls

		if (IsKeyDown(KEY_LEFT_SHIFT))
		{
			leftPaddle.y -= leftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_LEFT_CONTROL))
		{
			leftPaddle.y += leftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_RIGHT_SHIFT))
		{
			rightPaddle.y -= rightPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_RIGHT_CONTROL))
		{
			rightPaddle.y += rightPaddle.speed * GetFrameTime();
		}


		// Ball and Paddle Collision

		if (CheckCollisionCircleRec( Vector2{ball.x, ball.y}, ball.radius, leftPaddle.GetRect() ))
		{
			if (ball.speedX < 0)
			{
				ball.speedX *= -1.1;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedY + 50;
			}
		}
		if (CheckCollisionCircleRec( Vector2{ball.x, ball.y}, ball.radius, rightPaddle.GetRect() ))
		{
			if (ball. speedX > 0)
			{
				ball.speedX *= -1.1;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedY + 50;
			}
		}

		// Paddle and Border Collision
		if (CheckCollisionRecs(leftPaddle.GetRect(), topBorder.GetRect() ))
		{
			leftPaddle.y = topBorder.height + 50;
		}
		if (CheckCollisionRecs(leftPaddle.GetRect(), bottomBorder.GetRect() ))
		{
			leftPaddle.y = bottomBorder.height - 50;
		}
		if (CheckCollisionRecs(rightPaddle.GetRect(), topBorder.GetRect() ))
		{
			rightPaddle.y = topBorder.height + 50;
		}
		if (CheckCollisionRecs(rightPaddle.GetRect(), bottomBorder.GetRect() ))
		{
			rightPaddle.y = bottomBorder.height - 50;
		}


		// Win Stat

		if (ball.x < 0)
		{
			winnerText = "Right Player Wins!";
		}
			
		if (ball.x > GetScreenWidth())
		{
			winnerText = "Left Player Wins!";
		}


		// Ball Reset and Score Counter

		if (winnerText)
		{
			if (ball.x < 0)
			{
				RS +=1;
			}
			if (ball.x > GetScreenWidth())
			{
				LS +=1;
			}
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 300;
			ball.speedY = 300;
			winnerText = nullptr;
		}

		// Drawing Objects

		BeginDrawing();

			ClearBackground(BLACK);
			

			// Evironment Objects			
			topBorder.Draw();
			bottomBorder.Draw();
			//DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), WHITE);


			// Show FPS
			DrawFPS(GetScreenWidth() /2, 10);


			// Objects
			ball.Draw();
			leftPaddle.Draw();
			rightPaddle.Draw();
			DrawText(leftScore, GetScreenWidth() / 2 / 2, 10, 80, WHITE);
			DrawText(rightScore, GetScreenWidth() / 4 * 3, 10, 80, WHITE);


			// Win Text Show
			// if (winnerText)
			// {
			// 	int textWidth = MeasureText(winnerText, 60);
			// 	DrawText (winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() /2 - 30, 60, YELLOW);
			// }

		EndDrawing();
	}

}


// Start Screen...
void StartScreen()
{
	const char *Title = "PONG";
	int textWidth = MeasureText(Title, 100);

	// Ball 

	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 300;
	ball.speedY = 500;

	while (!WindowShouldClose())
	{
		// Initial ball movement

		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();


		// Ball UP and DOWN Collision

		if (ball.y < 20 )
		{
			ball.y = 20;
			ball.speedY *= -1;
		}
		if (ball.y > GetScreenHeight() - 20)
		{
			ball.y = GetScreenHeight() - 20;
			ball.speedY *= -1;
		}
		if (ball.x < 20)
		{
			ball.x = 20;
			ball.speedX *= -1;
		}
		if (ball.x > GetScreenWidth() - 20)
		{
			ball.x = GetScreenWidth() - 20;
			ball.speedX *= -1;
		}


		// Window Size Control

		if (IsKeyPressed(KEY_F))
		{
			ToggleFullscreen();
		}


		if (IsKeyPressed(KEY_S))
		{
			GameScreen();
		}

		BeginDrawing();
			ClearBackground(RAYWHITE);

			DrawRectangle(20, 20, GetScreenWidth() - 40, GetScreenHeight() - 40, BLACK);

			
			DrawText(Title, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - textWidth / 2, 100, RAYWHITE);

			// TODO: put a start button
			
			// TODO: Collide the Ball with the text
			DrawRectangleLines(GetScreenWidth() / 2 - textWidth / 2 - 5, GetScreenHeight() / 2 - textWidth / 2 + 5, 
								GetScreenWidth() / 2 - textWidth - 90, GetScreenHeight() / 2 - textWidth - 10, WHITE);

			

			ball.Draw();

		EndDrawing();
	}
	CloseWindow();
}


// MAIN Function

int main(void)
{
	const int screenHeight = 1280;
	const int screenWidth = 720;


	// Initalizing window

	InitWindow(screenHeight, screenWidth, "PONG by Omkar");
	SetWindowState(FLAG_VSYNC_HINT);

	StartScreen();
	//GameScreen();


	CloseWindow();

	return 0;
}