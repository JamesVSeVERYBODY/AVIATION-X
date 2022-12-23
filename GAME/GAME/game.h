#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "player.h"

using namespace sf;
class Game {
private:
	RenderWindow* window;
	Player player;

	std::vector<Vector2f> enemies;

	Font font;

public:
	Game(RenderWindow* win);
	void MainMenu();
	void Start();
	void GameOver();
};