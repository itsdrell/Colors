#pragma once
#include "raylib.h"
#include <vector>

///------------------------------------------------------------------
class Cell
{
public:
	Cell(Color& color, int index)
		: m_color(color)
		, m_colorLookup(index) {};

	Color	m_color = WHITE;
	bool	m_picked = false;
	int		m_colorLookup = -1;
};

///------------------------------------------------------------------
class Game
{
public:
	Game();

	void Update(float ds);
	void Render() const;

private:
	Camera2D m_camera = { 0 };
	
	std::vector<Color> m_colors;
	std::vector<Cell*> m_cells;

	int m_hoveredIndex = 0;
	
	Vector2 m_mousePos;
	int m_mouseTilePosX = 0;
	int m_mouseTilePosY = 0;
	
	Image m_testImage;
	Texture m_testTexture;
};