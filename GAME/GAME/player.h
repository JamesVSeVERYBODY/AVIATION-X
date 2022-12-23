#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

using namespace sf;
class Player {
private:
	Vector2f position;
	Vector2f velocity;

	Texture texture;
	Sprite sprite;

	Texture texturePeluru;
	Sprite spritePeluru;
	std::vector<Vector2f> peluru;

public:
	Player();
	void Start(Texture &texture, Texture &texPel);

	void SetPosition(Vector2f pos) { position = pos; }
	Sprite GetSprite() { return sprite; }
	Vector2f GetPosition() { return position; }

	bool CollidePeluru(FloatRect collider);
	void Tembak();
	void Update();

	void Draw(RenderWindow &win);
};