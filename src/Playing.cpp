#include "Playing.h"
#include "Game.h"
#include "AABB2.h"
#include "raylib.h"
#include "UI/Widget.h"
#include "UI/ColorPickerWidget.h"

#include <map>
#include <string>
#include "GameUtils.h"
#include "raymath.h"
#include <utility>

//-----------------------------------------------------------------------------------------------
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
	//m_testImage = LoadImage("tree_8x8.png");
	//m_testImage = LoadImage("cat_cute.png");
    //m_testImage = LoadImage("unique_5_5.png");
	m_testImage = LoadImage("100_100.png");
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

		ColorLookup colorLookup = ColorToInt(currentColor);
		if(m_ColorProgress.count(colorLookup) == 0)
		{
			m_ColorProgress.insert({ colorLookup, 1 });
		}
		else
		{
            m_ColorProgress[colorLookup]++;
		}
	}

	AABB2 bounds = GetAABB2FromAABB2({.65, .1}, {.95, .9}, g_theGame->m_UIBounds);
	m_colorPicker = new ColorPickerWidget(&gameCamera, bounds, this);
	m_widgets.push_back(m_colorPicker);
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

	Vector2 mouseWorld = GetScreenToWorld2D(mousePos, gameCamera);

    m_mouseTilePosX = (int)(mouseWorld.x / (CELL_SIZE_FLOAT));
    m_mouseTilePosY = (int)(mouseWorld.y / (CELL_SIZE_FLOAT));

	m_hoveredIndex = m_mouseTilePosY * m_testImage.width + m_mouseTilePosX;

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsValidIndex(m_hoveredIndex))
	{
		Cell* selectedCell = m_cells[m_hoveredIndex];

		if ((selectedCell->m_picked == false) && (selectedCell->m_colorLookup == m_selected_color))
		{
			selectedCell->m_picked = true;

			ColorLookup colorLookup = ColorToInt(m_colors[m_selected_color]);
			m_ColorProgress[colorLookup]--;
		}
	}

	UpdateMovement(ds);

    for (Widget* currentWidget : m_widgets)
    {
        currentWidget->Update(ds);
    }
}

//-----------------------------------------------------------------------------------------------
void Playing::UpdateMovement(float ds)
{
	Camera2D& gameCamera = g_theGame->m_gameCamera;
	Camera2D& uiCamera = g_theGame->m_UICamera;
	
	gameCamera.zoom += ((float)GetMouseWheelMove() * .1f);
    if (gameCamera.zoom < 0.1f)
    {
        gameCamera.zoom = .1f;
    }

    if (IsKeyReleased(KEY_ZERO)) { m_selected_color = 0; }
    if (IsKeyReleased(KEY_ONE)) { m_selected_color = 1; }
    if (IsKeyReleased(KEY_TWO)) { m_selected_color = 2; }
    if (IsKeyReleased(KEY_THREE)) { m_selected_color = 3; }
    if (IsKeyReleased(KEY_FOUR)) { m_selected_color = 4; }

	if(IsKeyReleased(KEY_O))
	{
		m_colorPicker->m_isOpen = !m_colorPicker->m_isOpen;
	}

	Vector2 dir = { 0,0 };
	if(IsKeyDown(KEY_W))
	{
		dir = Vector2Add(dir, { 0, -1 });
	}

    if (IsKeyDown(KEY_S))
    {
        dir = Vector2Add(dir, { 0, 1 });
    }

    if (IsKeyDown(KEY_D))
    {
        dir = Vector2Add(dir, { 1, 0 });
    }

    if (IsKeyDown(KEY_A))
    {
        dir = Vector2Add(dir, { -1, 0 });
    }

	dir = Vector2Normalize(dir);
	Vector2 movement = Vector2Scale(dir, 100 * ds);

	m_position = Vector2Add(movement, m_position);

	gameCamera.target = m_position;

	CheatInputs();
}

//-----------------------------------------------------------------------------------------------
void Playing::CheatInputs()
{
	if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT))
	{
		if(IsKeyPressed(KEY_ONE))
		{
			for(Cell* currentCell : m_cells)
			{
				currentCell->m_picked = true;
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------
bool Playing::IsValidIndex(int index)
{
	return (m_hoveredIndex > 0) && m_hoveredIndex < m_cells.size();
}

//-----------------------------------------------------------------------------------------------
void Playing::Render() const
{
	// Setup the back buffer for drawing (clear color and depth buffers)
	ClearBackground(BLACK);

	DrawPicture();
	DrawUI();

	char buff[100];
	snprintf(buff, sizeof(buff), "color: %i", m_selected_color);
	DrawText(buff, 640, 10, 20, RED);


	// debug
    Camera2D& gameCamera = g_theGame->m_gameCamera;
    Vector2 mousePos = GetMousePosition();

	Vector2 mouseWorld = GetScreenToWorld2D(mousePos, gameCamera);

    float offsetX = (mousePos.x / (gameCamera.zoom * CELL_SIZE_FLOAT)) + gameCamera.target.x;
    float offsetY = (mousePos.y / (gameCamera.zoom * CELL_SIZE_FLOAT)) + gameCamera.target.y;
    

	//snprintf(buff, sizeof(buff), "fps: %d", GetFPS());
	snprintf(buff, sizeof(buff), "z: %f", gameCamera.zoom);
	DrawText(buff, 1000, 10, 30, RED);
}

//-----------------------------------------------------------------------------------------------
void Playing::DrawPicture() const
{
    // THIS IS DRAWING ON THE m_camera
    BeginMode2D(g_theGame->m_gameCamera);

    // draw our texture to the screen
    DrawTextureEx(m_testTexture, { 0, 0 }, 0.f, CELL_SIZE, WHITE);

	Vector2 pos = g_theGame->m_gameCamera.target;
    int posIndexX = (int)(pos.x / (CELL_SIZE_FLOAT));
    int posIndexY = (int)(pos.y / (CELL_SIZE_FLOAT));

	int hoverX = 0;
	int hoverY = 0;

	// why am I drawing in this order instead of width then hight? Like the first loop should be y...
    // grid
    for (int i = 0; i < m_testImage.width; i++)
    {
        for (int j = 0; j < m_testImage.height; j++)
        {
            int index = (j * m_testImage.height + i);
			if (index >= m_cells.size()) // BUG
				continue;

			// HACK
			// Just try and only draw tiles that are X cells away?
            float distanceSquared = Vector2DistanceSqr({ (float)posIndexX, (float)posIndexY }, { (float)i, (float)j });
            if (distanceSquared > 1000)
            {
                //continue;
            }

            Cell* currentCell = m_cells[index];

            if (currentCell->m_picked == false)
            {
				Color drawColor = (currentCell->m_colorLookup == m_selected_color) ? WHITE : Color{235, 235, 235, 255};
				DrawRectangle(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE, drawColor);
            }

            if (currentCell->m_picked == false)
            {
                float posX = (i * CELL_SIZE) + 16.f;
                float posY = ((j + 1) * CELL_SIZE) - 16.f;

				// dont draw text if its not going to be readable. Hack optimization
				if (g_theGame->m_gameCamera.zoom >= 1.f)
				{
                    char buff[100];
                    snprintf(buff, sizeof(buff), "%i", currentCell->m_colorLookup);
                    DrawText(buff, posX, posY, 1, BLUE);

				}
				else
				{
					DrawRectangleLines(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
				}
            }

			// TODO : this needs to be draw outside of this loop silly
            if (index == m_hoveredIndex)
            {
				hoverX = i;
				hoverY = j;
            }
        }
    }

    DrawRectangleLines(hoverX * CELL_SIZE, hoverY * CELL_SIZE, CELL_SIZE, CELL_SIZE, MAGENTA);

    EndMode2D();
}

//-----------------------------------------------------------------------------------------------
void Playing::DrawUI() const
{
	BeginMode2D(g_theGame->m_UICamera);

	//DrawColorSelector();

	DrawAABB2(g_theGame->m_UIBounds, WHITE);
	DrawCircle(0, 0,6, RED);

	for(Widget* currentWidget : m_widgets)
	{
		currentWidget->Render();
	}

	
	EndMode2D();
}

//-----------------------------------------------------------------------------------------------
void Playing::DrawColorSelector() const
{
	AABB2 theBounds = g_theGame->m_UIBounds;

	AABB2 colorSelectorBounds = GetAABB2FromAABB2({.1f, .9f}, {.9f, .8f}, theBounds);
	DrawAABB2(colorSelectorBounds, WHITE);
}