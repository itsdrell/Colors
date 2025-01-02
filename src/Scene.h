#pragma once

///------------------------------------------------------------------
class Scene
{
public:
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

public:
	virtual void Update(float ds) = 0;
	virtual void Render() const = 0;
};