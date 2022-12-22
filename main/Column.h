#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

using namespace sf;

class Column {
public:
	Column() = default;
	Column(Vector2f size, Vector2f pos, int value = 0, Color c = Color::Green, Vector2f panel_size = { 60, 25 });

	void setPosition(Vector2f pos);
	void setValue(float val, int real);
	void setSize(float size);
	int getValue();
	bool contains(Vector2i mouse);
	void draw(RenderWindow& window, Vector2i mouse);

protected:
	int value_;
	RectangleShape shape_;
	RectangleShape panel_;
	Text text_;
};
