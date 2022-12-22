#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Column.h"
#include "Button.h"

class Statistic {
public:
	Statistic() = default;
	Statistic(Vector2f size, Vector2f position, int count = 0);
	void addValue(int value);
	void draw(RenderWindow& window, Vector2i mouse);

private:
	std::vector<Column> stats_;
	Vector2f size_, position_;
	Text zero_, max_text_;
	int max_;
	int pointer_;
};

// хранит и рисует статистику