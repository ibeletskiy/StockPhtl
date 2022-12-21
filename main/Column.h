#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

using namespace sf;

class Column {
public:
	Column() = default;
	Column(Vector2f size, Vector2f pos, int value = 0, Color c = Color::Green, Vector2f panel_size = { 60, 25 }) : value_(value) {
		shape_.setSize(size);
		shape_.setSize(size);
		panel_.setSize(panel_size);
		panel_.setFillColor(Color::White);
		panel_.setOutlineColor(Color::Black);
		panel_.setOutlineThickness(1);
		shape_.setFillColor(c);
		text_.setFillColor(Color::Black);
		text_.setCharacterSize(panel_size.y - 4);
	}

	virtual void setPosition(Vector2f pos) = 0;
	virtual void setValue(float val, int real) = 0;
	virtual void setSize(float size) = 0;

	void draw(RenderWindow& window, Vector2i mouse) {
		window.draw(shape_);
		if (contains(mouse)) {
			text_.setString(std::to_string(value_));
			panel_.setSize(Vector2f(text_.getGlobalBounds().width + 10, panel_.getSize().y));
			panel_.setPosition({ mouse.x - panel_.getSize().x, mouse.y - panel_.getSize().y});
			text_.setPosition(Vector2f(panel_.getPosition().x + 5, panel_.getPosition().y ));
			window.draw(panel_);
			text_.setFont(font);
			window.draw(text_);
		}
	}

	int getValue() {
		return value_;
	}

	bool contains(Vector2i mouse) {
		return (mouse.x >= shape_.getPosition().x &&
			mouse.x <= (shape_.getPosition().x + shape_.getSize().x) &&
			mouse.y >= shape_.getPosition().y &&
			mouse.y <= (shape_.getPosition().y + shape_.getSize().y));
	}
protected:
	int value_;
	RectangleShape shape_;
	RectangleShape panel_;
	Text text_;
};
