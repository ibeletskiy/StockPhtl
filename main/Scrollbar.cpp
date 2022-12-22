#include "Scrollbar.h"

ScrollBar::ScrollBar(int r, int length, Vector2f position, bool part_view) : part_view_(part_view) {
	circle_.setRadius(r);
	line_.setSize(Vector2f(length, 3));
	line_.setPosition(position);
	part_.setPosition(position);
}

void ScrollBar::setLinePosition(Vector2f position) {
	line_.setPosition(position);
	part_.setPosition(position);
}

void ScrollBar::setCirclePosition(Vector2f position) {
	circle_.setPosition(position);
	part_.setSize(Vector2f(position.x - part_.getPosition().x + circle_.getRadius(), 3));
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
	if (mouse_position.x >= line_.getPosition().x && mouse_position.x <= line_.getPosition().x + line_.getSize().x) {
		circle_.setPosition(Vector2f(mouse_position.x - circle_.getRadius(), circle_.getPosition().y));
		part_.setSize(Vector2f(circle_.getPosition().x + circle_.getRadius() - line_.getPosition().x, part_.getSize().y));
	}
}

double ScrollBar::getValue() {
	return part_.getSize().x / line_.getSize().x;
}

void ScrollBar::draw(RenderWindow& window) {
	window.draw(line_);
	if (part_view_) {
		window.draw(part_);
	}
	window.draw(circle_);
}
