#include "player.h"

Player::Player() {
	
}

void Player::Start(Texture &tex, Texture &texPel) {
	texture = tex;
	texturePeluru = texPel;

	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 60, 49));

	spritePeluru.setTexture(texturePeluru);
	spritePeluru.setTextureRect(IntRect(0, 0, 37, 7));
}

bool Player::CollidePeluru(FloatRect collider) {
	for (int i = 0; i < peluru.size(); i++) {
		if (FloatRect(peluru[i].x, peluru[i].y, 37, 7).intersects(collider)) {
			peluru.erase(peluru.begin() + i);
			return true;
		}
	}

	return false;
}

void Player::Tembak() {
	peluru.push_back(position + Vector2f(30, 5));
}

void Player::Update() {
	sprite.setPosition(position - Vector2f(60, 49) / 2.f);

	for (int i = 0; i < peluru.size(); i++) {
		peluru[i].x += 10.f;
	}
}

void Player::Draw(RenderWindow& win) {
	win.draw(sprite);

	for (int i = peluru.size() - 1; i >= 0; i--) {
		spritePeluru.setPosition(peluru[i]);
		
		win.draw(spritePeluru);

		if (peluru[i].x > win.getSize().x) peluru.erase(peluru.begin() + i);
	}
}