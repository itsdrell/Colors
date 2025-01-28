#pragma once
#include "Scene.h"

#include <vector>
#include "raylib.h"
#include <map>

///------------------------------------------------------------------
class Widget;
class ColorPickerWidget;

typedef int ColorLookup;

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
	void UpdateMovement(float ds);
	void CheatInputs();
	bool IsValidIndex(int index);

	virtual void Render() const;

private:
	void DrawPicture() const;
	void DrawUI() const;
	void DrawColorSelector() const;

public:
	std::vector<Color> m_colors;
	std::vector<Cell*> m_cells;

	std::map<ColorLookup, int> m_ColorProgress;

	int m_hoveredIndex = 0;
	int m_mouseTilePosX = 0;
	int m_mouseTilePosY = 0;

	int m_selected_color = 1;

	Image m_testImage;
	Texture m_testTexture;

	Vector2 m_position = { 0,0 };

	std::vector<Widget*> m_widgets;
	ColorPickerWidget* m_colorPicker = nullptr;
};