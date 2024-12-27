/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <vector>
#include <string>
#include <map>

constexpr int CELL_SIZE = 32;
constexpr float CELL_SIZE_FLOAT = 32.0f;

class Cell
{
public:
	Cell(Color& color, int index)
		: m_color(color)
	,		m_colorLookup(index) {};

	Color	m_color = WHITE;
	bool	m_picked = false;
	int		m_colorLookup = -1;
};

int selected_color = 1;

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 1024, "Colors");

	HideCursor();

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Camera 
	Camera2D camera = { 0 };
	camera.target = { 0.f, 0.f };
	camera.rotation = 0.0f;
	camera.zoom = 2.0f;

	// Create the level image
	Image testImage = LoadImage("tree_8x8.png");
	Texture testTexture = LoadTextureFromImage(testImage);

	int imageSize = testImage.height * testImage.width;
	
	std::vector<Color> colors;
	std::vector<Cell*> cells;

	colors.reserve(imageSize);
	cells.reserve(imageSize);

	unsigned char* imageData = (unsigned char*)testImage.data;
	for(int i = 0; i < (imageSize * 4); i += 4)
	{
		unsigned char currentR = imageData[i];
		unsigned char currentG = imageData[i + 1];
		unsigned char currentB = imageData[i + 2];
		unsigned char currentA = imageData[i + 3];

		Color currentColor = { currentR, currentG, currentB, currentA };

		int foundIndex = -1;
		for(int j = 0; j < colors.size(); j++)
		{
			if(ColorIsEqual(currentColor, colors[j]))
			{
				foundIndex = j;
				continue;
			}
		}

		if(foundIndex == -1)
		{
			colors.push_back(currentColor);
			foundIndex = colors.size() - 1;
		}

		Cell* newCell = new Cell(currentColor, foundIndex);
		cells.push_back(newCell);
	}
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// update 
		Vector2 mousePos = GetMousePosition();
		camera.zoom += ((float)GetMouseWheelMove() * 2.f);


		if(camera.zoom == 0.0f)
		{
			camera.zoom = .1f;
		}

		int mouse_tile_pos_x = (int)(mousePos.x / (camera.zoom * CELL_SIZE_FLOAT));
		int mouse_tile_pos_y = (int)(mousePos.y / (camera.zoom * CELL_SIZE_FLOAT));

		int hoveredIndex = mouse_tile_pos_y * testImage.width + mouse_tile_pos_x;

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Cell* selectedCell = cells[hoveredIndex];

			if(selectedCell->m_colorLookup == selected_color)
			{
				selectedCell->m_picked = true;
			}
		}

		if (IsKeyReleased(KEY_ZERO)) { selected_color = 0; }
		if (IsKeyReleased(KEY_ONE)) { selected_color = 1; }
		if (IsKeyReleased(KEY_TWO)) { selected_color = 2; }
		if (IsKeyReleased(KEY_THREE)) { selected_color = 3; }
		if (IsKeyReleased(KEY_FOUR)) { selected_color = 4; }


		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// THIS IS DRAWING ON THE CAMERA
		BeginMode2D(camera);

		// draw our texture to the screen
		DrawTextureEx(testTexture, { 0, 0 },0.f, CELL_SIZE, WHITE);

		// grid
		for(int i = 0; i < testImage.width; i++)
		{
			for(int j = 0; j < testImage.height; j++)
			{
				int index = (j * testImage.height + i);
				Cell* currentCell = cells[index];
				
				if(currentCell->m_picked == false)
				{
					DrawRectangle(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);
				}

				if(index == hoveredIndex)
				{
					DrawRectangleLines(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE, YELLOW);
				}

				if(currentCell->m_picked == false)
				{
					float posX = (i * CELL_SIZE) + 16.f;
					float posY = ((j + 1) * CELL_SIZE) - 16.f;

					char buff[100];
					snprintf(buff, sizeof(buff), "%i", currentCell->m_colorLookup);
					DrawText(buff, posX, posY, 1, BLUE);
				}
				
				DrawRectangleLines(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
			}
		}


		EndMode2D();

		// THIS IS UI DRAWING ON SCREEN
		DrawCircle(mousePos.x, mousePos.y, 8, YELLOW);

		//char buff[100];
		//snprintf(buff, sizeof(buff), "(%i, %i)", mouse_tile_pos_x, mouse_tile_pos_y);
		//DrawText(buff, 640, 10, 20, RED);

		char buff[100];
		snprintf(buff, sizeof(buff), "color: %i", selected_color);
		DrawText(buff, 640, 10, 20, RED);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	//UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
