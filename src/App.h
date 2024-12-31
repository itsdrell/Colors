#pragma once


class Game;


class App
{
public:
	App();
	~App();

	void Update();
	void Render() const;

private:
	Game* m_game = nullptr;
};