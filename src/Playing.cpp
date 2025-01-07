#include "Playing.h"
#include "Game.h"
#include "AABB2.h"
#include "raylib.h"

#include <map>
#include <string>
#include "GameUtils.h"

//-----------------------------------------------------------------------------------------------
int selected_color = 1;

constexpr int CELL_SIZE = 32;
constexpr float CELL_SIZE_FLOAT = 32.0f;

//-----------------------------------------------------------------------------------------------
Playing::Playing()
{
	// Game Camera
	Camera2D& gameCamera = g_theGame->m_gameCamera;
	gameCamera.target = { 0.f, 0.f };
	gameCamera.rotation = 0.0f;
	gameCamera.zoom = 2.0f;

	// Create the level image
	m_testImage = LoadImage("tree_8x8.png");
	m_testTexture = LoadTextureFromImage(m_testImage);

	int imageSize = m_testImage.height * m_testImage.width;

	m_colors.reserve(imageSize);
	m_cells.reserve(imageSize);

	unsigned char* imageData = (unsigned char*)m_testImage.data;
	for (int i = 0; i < (imageSize * 4); i += 4)
	{
		unsigned char currentR = imageData[i];
		unsigned char currentG = imageData[i + 1];
		unsigned char currentB = imageData[i + 2];
		unsigned char currentA = imageData[i + 3];

		Color currentColor = { currentR, currentG, currentB, currentA };

		int foundIndex = -1;
		for (int j = 0; j < m_colors.size(); j++)
		{
			if (ColorIsEqual(currentColor, m_colors[j]))
			{
				foundIndex = j;
				continue;
			}
		}

		if (foundIndex == -1)
		{
			m_colors.push_back(currentColor);
			foundIndex = m_colors.size() - 1;
		}

		Cell* newCell = new Cell(currentColor, foundIndex);
		m_cells.push_back(newCell);
	}
}

//-----------------------------------------------------------------------------------------------
Playing::~Playing()
{
	for(Cell* currentCell : m_cells)
	{
		delete currentCell;
	}
}

//-----------------------------------------------------------------------------------------------
void Playing::OnEnter()
{

}

//-----------------------------------------------------------------------------------------------
void Playing::OnExit()
{

}

//-----------------------------------------------------------------------------------------------
void Playing::Update(float ds)
{
	Camera2D& gameCamera = g_theGame->m_gameCamera;
	Vector2 mousePos = GetMousePosition();
	gameCamera.zoom += ((float)GetMouseWheelMove() * 2.f);


	if (gameCamera.zoom == 0.0f)
	{
		gameCamera.zoom = .1f;
	}

	m_mouseTilePosX = (int)(mousePos.x / (gameCamera.zoom * CELL_SIZE_FLOAT));
	m_mouseTilePosY = (int)(mousePos.y / (gameCamera.zoom * CELL_SIZE_FLOAT));

	m_hoveredIndex = m_mouseTilePosY * m_testImage.width + m_mouseTilePosX;

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		Cell* selectedCell = m_cells[m_hoveredIndex];

		if (selectedCell->m_colorLookup == selected_color)
		{
			selectedCell->m_picked = true;
		}
	}

	if (IsKeyReleased(KEY_ZERO)) { selected_color = 0; }
	if (IsKeyReleased(KEY_ONE)) { selected_color = 1; }
	if (IsKeyReleased(KEY_TWO)) { selected_color = 2; }
	if (IsKeyReleased(KEY_THREE)) { selected_color = 3; }
	if (IsKeyReleased(KEY_FOUR)) { selected_color = 4; }
}

//-----------------------------------------------------------------------------------------------
void Playing::Render() const
{
	// Setup the back buffer for drawing (clear color and depth buffers)
	ClearBackground(BLACK);

	//DrawPicture();
	DrawUI();

	char buff[100];
	snprintf(buff, sizeof(buff), "color: %i", selected_color);
	DrawText(buff, 640, 10, 20, RED);
}

//-----------------------------------------------------------------------------------------------
void Playing::DrawPicture() const
{
    // THIS IS DRAWING ON THE m_camera
    BeginMode2D(g_theGame->m_gameCamera);

    // draw our texture to the screen
    DrawTextureEx(m_testTexture, { 0, 0 }, 0.f, CELL_SIZE, WHITE);

    // grid
    for (int i = 0; i < m_testImage.width; i++)
    {
        for (int j = 0; j < m_testImage.height; j++)
        {
            int index = (j * m_testImage.height + i);
            Cell* currentCell = m_cells[index];

            if (currentCell->m_picked == false)
            {
                DrawRectangle(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);
            }

            if (index == m_hoveredIndex)
            {
                DrawRectangleLines(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE, YELLOW);
            }

            if (currentCell->m_picked == false)
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
}

//-----------------------------------------------------------------------------------------------
void Playing::DrawUI() const
{
	BeginMode2D(g_theGame->m_UICamera);

	DrawAABB2(g_theGame->m_UIBounds, WHITE);
	DrawCircle(0, 0,6, RED);


	EndMode2D();
}
