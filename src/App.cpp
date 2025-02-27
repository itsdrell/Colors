#pragma once
#include "App.h"
#include "Game.h"
#include "raylib.h"
#include "resource_dir.h"

///------------------------------------------------------------------
App* g_theApp = nullptr;

///------------------------------------------------------------------
App::App()
{
	g_theApp = this;
	
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(m_screenSize.x, m_screenSize.y, "Colors");

	HideCursor();

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("Resources");
	
	m_game = new Game();
}

///------------------------------------------------------------------
App::~App()
{
	delete m_game;
}

///------------------------------------------------------------------
void App::Update()
{
	m_game->Update(1.f / 60.f);
}

///------------------------------------------------------------------
void App::Render() const
{
	// drawing
	BeginDrawing();
	
	m_game->Render();

	// end the frame and get ready for the next one  (display frame, poll input, etc...)
	EndDrawing();
}
