#pragma once
#include "raylib.h"
#include "AABB2.h"

///------------------------------------------------------------------
class Scene;

///------------------------------------------------------------------
enum GameMode
{
	ATTRACT,
	PLAYING,

	NUM_MODES
};

///------------------------------------------------------------------
class Game
{
public:
	Game();

	void Update(float ds);
	void Render() const;

public:
	Camera2D m_gameCamera = { 0 };
	Camera2D m_UICamera = { 0 };
	AABB2 m_UIBounds;
	
	Vector2 m_mousePos;

	GameMode m_currentMode = PLAYING;
	Scene* m_gameScenes[GameMode::NUM_MODES];
};

extern Game* g_theGame;