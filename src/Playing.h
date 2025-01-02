#pragma once
#include "Scene.h"

#include <vector>
#include "raylib.h"

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
class Playing : public Scene
{
public:
	Playing();
	~Playing();

public:
	virtual void OnEnter();
	virtual void OnExit();

public:
	virtual void Update(float ds);
	virtual void Render() const;

public:
	std::vector<Color> m_colors;
	std::vector<Cell*> m_cells;

	int m_hoveredIndex = 0;
	int m_mouseTilePosX = 0;
	int m_mouseTilePosY = 0;

	Image m_testImage;
	Texture m_testTexture;
};