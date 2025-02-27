#pragma once
#include "Scene.h"
///------------------------------------------------------------------
class TextButton;

///------------------------------------------------------------------
class Attract : public Scene
{
public:
	Attract();
	~Attract();

public:
	virtual void OnEnter();
	virtual void OnExit();

public:
	virtual void Update(float ds);
	virtual void Render() const;

private:
	TextButton* m_startButton = nullptr;
};