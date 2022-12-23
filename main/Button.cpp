#include "Button.h"

extern Font font;

Button::Button(Vector2f size, Vector2f position, Color color, float border, std::wstring name, int size_ch, Color title_color) {
	field_.setSize(size);
	field_.setPosition(position);
	field_.setFillColor(color);
	field_.setOutlineColor(Color(255, 255, 255, 255));
	backlight_thickness_ = border;
	title_.setString(name);
	title_.setCharacterSize(size_ch);
	title_.setFillColor(title_color);
	backlight_ = 0;
}

void Button::setTitle(std::wstring name, int size, Color color) {
	title_.setString(name);
	title_.setCharacterSize(size);
	title_.setFillColor(color);
}

Vector2f Button::getPosition() {
	return field_.getPosition();
}

void Button::setTitlePosition(Vector2f pos) {
	title_.setPosition(pos);
}

void Button::setBacklight(int val, int thickness, Color color) {
	backlight_ = val;
	backlight_thickness_ = thickness;
}

void Button::setButtonPosition(Vector2f pos) {
	field_.setPosition(pos);
}

void Button::setButtonSize(Vector2f size, int size_thickness) {
	field_.setSize(size);
	backlight_thickness_ = size_thickness;
}

void Button::setButtonColor(Color fill_color, Color outline_color) {
	field_.setFillColor(fill_color);
	field_.setOutlineColor(outline_color);
}

void Button::setOutline(Color color, int thickness) {
	field_.setOutlineColor(color);
	field_.setOutlineThickness(thickness);
}
	
bool Button::contains(const Vector2i& mouse) {
	bool check = (mouse.x >= field_.getPosition().x &&
		mouse.x <= (field_.getPosition().x + field_.getSize().x) &&
		mouse.y >= field_.getPosition().y &&
		mouse.y <= (field_.getPosition().y + field_.getSize().y));
	if (backlight_ >= 0) {
		if (check ^ backlight_) {
			backlight_ ^= 1;
		}
	}
	if (backlight_ == 1 || backlight_ == -1) {
		field_.setOutlineThickness(backlight_thickness_);
	} else {
		field_.setOutlineThickness(0);
	}
	return check;
}

bool Button::pressed(Vector2i& mouse, Event now) {
	return (contains(mouse) && now.type == Event::MouseButtonPressed && now.key.code == Mouse::Left);
}

bool Button::rightPressed(Vector2i& mouse, Event now) {
	return (contains(mouse) && now.type == Event::MouseButtonPressed && now.key.code == Mouse::Right);
}

void Button::draw(RenderWindow& window) {
	window.draw(field_);
	title_.setFont(font);
	window.draw(title_);
}