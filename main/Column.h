#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

using namespace sf;

class Column {
public:
	Column() = default;
	Column(Vector2f size, Vector2f pos, int value = 0, Vector2f panel_size = { 40, 15 }) : value_(value) {
		shape_.setSize(size);
		shape_.setSize(size);
		panel_.setSize(panel_size);
		panel_.setFillColor(Color::White);
		text_.setFillColor(Color::Black);
		text_.setCharacterSize(panel_size.x - 4);
	}

	virtual void setPosition(Vector2f pos) = 0;
	virtual void setValue(float val) = 0;
	virtual void setSize(float size) = 0;

	void draw(RenderWindow& window, Vector2i mouse) {
		window.draw(shape_);
		if (contains(mouse)) {
			panel_.setPosition({ mouse.x - panel_.getSize().x, mouse.y - panel_.getSize().y});
			text_.setString(std::to_string(value_));
			text_.setPosition(Vector2f(panel_.getPosition().x +
				(double)(panel_.getSize().x - text_.getGlobalBounds().height) / 2, 2 ));
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
