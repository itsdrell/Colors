#include "Game.h"
#include "Attract.h"
#include "Playing.h"

#include "raylib.h"
#include <string>
#include <map>

///------------------------------------------------------------------
Game* g_theGame = nullptr;


///------------------------------------------------------------------
Game::Game()
{
	g_theGame = this;
	
	// Game Camera
	m_gameCamera.target = { 0.f, 0.f };
	m_gameCamera.rotation = 0.0f;
	m_gameCamera.zoom = 2.0f;

	m_UICamera.target = { 0.f, 0.f };
	m_UICamera.rotation = 0.0f;
	m_UICamera.zoom = 2.0f;

	m_gameScenes[ATTRACT] = new Attract();
	m_gameScenes[PLAYING] = new Playing();
}

///------------------------------------------------------------------
void Game::Update(float ds)
{
	if (m_gameCamera.zoom == 0.0f)
	{
		m_gameCamera.zoom = .1f;
	}

	m_gameScenes[m_currentMode]->Update(ds);
}

///------------------------------------------------------------------
void Game::Render() const
{
	// Setup the back buffer for drawing (clear color and depth buffers)
	ClearBackground(BLACK);

	m_gameScenes[m_currentMode]->Render();

	// THIS IS UI DRAWING ON SCREEN
	Vector2 mousePos = GetMousePosition();
	DrawCircle(mousePos.x, mousePos.y, 8, YELLOW);
}
