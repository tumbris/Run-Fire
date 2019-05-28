#include "Bullet.h"
using namespace sf;

Bullet::Bullet(Texture & texture, float X, float Y, int W, int H, String Name, bool is_right) {
	x = X; y = Y; w = W; h = H; name = Name; damage = 25;
	if (is_right) dx = 0.2; else { dx = -0.2; sprite.scale(-1, 1); }
	speed = 0.2; dy = 0;
	onGround = false;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(280, 215, w, h));
	sprite.setOrigin(w / 2, h / 2);
	sprite.setPosition(x + w / 2, y + h / 2);
}

Sprite Bullet::get_sprite() {
	return sprite;
}

int Bullet::update(float time, Map & map, std::vector<std::unique_ptr<Golem>> & golems) {
	int temp;
	x += dx*time;
	if (check_collision(map) == -1) return -1;
	if (check_collision(golems) == -1) return -1;

	y += dy*time;
	if (check_collision(map) == -1) return -1;
	if (check_collision(golems) == -1) return -1;

	sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
	return 0;
}

int Bullet::check_collision(Map & map) {
	try {
		for (int i = y / TITLE_SIZE; i < (y + h) / TITLE_SIZE; i++) {
			if (i < 0 || i >= map.get_h()) continue;
			for (int j = x / TITLE_SIZE; j < (x + w) / TITLE_SIZE; j++) {
				if (j < 0 || j >= map.get_w()) continue;
				if (map[i][j] == 'w')
				{
					return -1;
				}
			}
		}
	}
	catch (...) {
		return -1;
	}

	

	return 0;
}

int Bullet::check_collision(std::vector<std::unique_ptr<Golem>> & golems) {
	for (int i = 0; i < golems.size(); i++) {
		if (x >= golems[i]->get_x() && x <= golems[i]->get_x() + golems[i]->get_w() &&
			y >= golems[i]->get_y() && y <= golems[i]->get_y() + golems[i]->get_h()) {
			if (dx > 0 && golems[i]->get_right() || dx < 0 && !golems[i]->get_right()) golems[i]->health = golems[i]->health - damage;
			return -1;
		}
	}
	return 0;
}