#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Column.h"

using namespace sf;

extern Font font;

class Statistic {
public:
	Statistic() = default;
	Statistic(Vector2f size, Vector2f position, int count = 0);
	void setColor(Color good, Color bad);
	int getValue(int i);
	void setTextColor(Color color);
	void addValue(int value);
	void draw(RenderWindow& window, Vector2i mouse);

private:
	std::vector<Column> stats_;
	Vector2f size_, position_;
	Text zero_, max_text_;
	Color good_, bad_;
	int max_;
	int pointer_;
};

// хранит и рисует статистику