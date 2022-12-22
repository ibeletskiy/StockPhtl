#include "Scrollbar.h"

ScrollBar::ScrollBar(int r, int length, Vector2f position, bool part_view) : part_view_(part_view) {
	circle_.setRadius(r);
	circle_.setPosition({ position.x - r + 1, position.y - r + 1 });
	line_.setSize(Vector2f(2, length));
	line_.setPosition(position);
	part_.setPosition(position);
	pressed_ = false;
}

void ScrollBar::setLinePosition(Vector2f position) {
	line_.setPosition(position);
	part_.setPosition(position);
}

void ScrollBar::setCirclePosition(Vector2f position) {
	circle_.setPosition(position);
	part_.setSize(Vector2f(2, position.x - part_.getPosition().x + circle_.getRadius()));
}

void ScrollBar::setLineColor(Color color) {
	line_.setFillColor(color);
}

void ScrollBar::setCircleColor(Color color) {
	circle_.setFillColor(color);
	part_.setFillColor(color);
}

bool ScrollBar::contains(Vector2i mouse_position) {
	return ((mouse_position.x - (circle_.getPosition().x + circle_.getRadius())) * (mouse_position.x - (circle_.getPosition().x + circle_.getRadius())) +
		(mouse_position.y - (circle_.getPosition().y + circle_.getRadius())) * (mouse_position.y - (circle_.getPosition().y + circle_.getRadius())) <= circle_.getRadius() * circle_.getRadius());
}

bool ScrollBar::pressed(Vector2i mouse_position, Event event) {
	if (contains(mouse_position)) {
		return (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left);
	}
	return false;
}

void ScrollBar::changeCircle(Vector2i mouse_position, Event event) {
	if (pressed(mouse_position, event)) {
		pressed_ = true;
	} else if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) {
		pressed_ = false;
	}
	if (pressed_) {
		if (mouse_position.y >= line_.getPosition().y && mouse_position.y <= line_.getPosition().y + line_.getSize().y) {
			circle_.setPosition(Vector2f(circle_.getPosition().x, mouse_position.y - circle_.getRadius()));
			part_.setSize(Vector2f(part_.getSize().x, circle_.getPosition().y + circle_.getRadius() - line_.getPosition().y));
		}
	}
}

double ScrollBar::getValue() {
	return part_.getSize().y / line_.getSize().y;
}

void ScrollBar::draw(RenderWindow& window) {
	window.draw(line_);
	if (part_view_) {
		window.draw(part_);
	}
	window.draw(circle_);
}
