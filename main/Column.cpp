#include "Column.h"

Column::Column(Vector2f size, Vector2f pos, int value, Color c, Vector2f panel_size) : value_(value) {
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

void Column::setPosition(Vector2f pos) {
	shape_.setPosition(Vector2f(pos.x, pos.y - shape_.getSize().y));
}

void Column::setValue(float val, int real) {
	shape_.setPosition(Vector2f(shape_.getPosition().x, shape_.getPosition().y + shape_.getSize().y - val));
	shape_.setSize(Vector2f(shape_.getSize().x, val));
	value_ = real;
}

void Column::setSize(float size) {
	shape_.setSize(Vector2f(size, shape_.getSize().y));
}

void Column::draw(RenderWindow& window, Vector2i mouse) {
	window.draw(shape_);
	if (contains(mouse)) {
		text_.setString(std::to_string(value_));
		panel_.setSize(Vector2f(text_.getGlobalBounds().width + 10, panel_.getSize().y));
		panel_.setPosition({ mouse.x - panel_.getSize().x, mouse.y - panel_.getSize().y });
		text_.setPosition(Vector2f(panel_.getPosition().x + 5, panel_.getPosition().y));
		window.draw(panel_);
		text_.setFont(font);
		window.draw(text_);
	}
}

int Column::getValue() {
	return value_;
}

bool Column::contains(Vector2i mouse) {
	return ((mouse.x >= shape_.getPosition().x &&
		mouse.x <= (shape_.getPosition().x + shape_.getSize().x) &&
		mouse.y >= shape_.getPosition().y &&
		mouse.y <= (shape_.getPosition().y + shape_.getSize().y))) ||
		((mouse.x >= shape_.getPosition().x &&
			mouse.x <= (shape_.getPosition().x + shape_.getSize().x) &&
			mouse.y <= shape_.getPosition().y &&
			mouse.y >= (shape_.getPosition().y + shape_.getSize().y)));
}
