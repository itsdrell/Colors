#pragma once
#include "raylib.h"

///------------------------------------------------------------------
class Game;

///------------------------------------------------------------------
class App
{
public:
	App();
	~App();

	void Update();
	void Render() const;

public:
	Vector2 m_screenSize = { 1280, 1024 };

private:
	Game* m_game = nullptr;
};

///------------------------------------------------------------------
extern App* g_theApp;