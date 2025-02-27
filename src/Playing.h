#pragma once
#include "Scene.h"

#include <vector>
#include "raylib.h"
#include <map>
#include <thread>
#include <string>

///------------------------------------------------------------------
class Widget;
class ColorPickerWidget;
class TextButton;

typedef int ColorLookup;

constexpr float AUTO_SAVE_TIME = 5.f;

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
	
	void CheckIfPaintingIsFinished();
	void CheatInputs();
	bool IsValidIndex(int index);

	void SaveThread();
	void SaveProgressToFile(const std::string& filePath);

	virtual void Render() const;

private:
	void DrawPicture() const;
	void DrawUI() const;
	void DrawFinished() const;

public:
	bool m_isFinished = false;

	std::vector<Color> m_colors;
	std::vector<Cell*> m_cells;

	std::map<ColorLookup, int> m_ColorProgress;

	int m_hoveredIndex = 0;
	int m_mouseTilePosX = 0;
	int m_mouseTilePosY = 0;

	int m_selected_color = 0;

	Image m_testImage;
	Texture m_testTexture;

	Texture m_carolinePointing;

	Vector2 m_position = { 0,0 };

	std::vector<Widget*> m_widgets;
	ColorPickerWidget* m_colorPicker = nullptr;
	TextButton* m_backToMenuButton = nullptr;

	std::thread m_saveThread;
	float m_saveCoolown = AUTO_SAVE_TIME;
	bool m_threadFinished = false;
};