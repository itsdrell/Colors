#include "Game.h"
#include "Attract.h"
#include "Playing.h"
#include "App.h"


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

	m_UICamera.rotation = 0.0f;
	m_UICamera.zoom = 1.0f;
	
	Vector2 center = { g_theApp->m_screenSize.x * .5f, g_theApp->m_screenSize.y * 0.5f };
	m_UICamera.offset = { center.x, center.y };
	m_UICamera.target = { center.x, center.y };

	m_UIBounds = AABB2(0, 0, g_theApp->m_screenSize.x, g_theApp->m_screenSize.y);

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
