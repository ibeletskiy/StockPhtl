#include "Inputfield.h"

InputField::InputField(Vector2f size, Vector2f position, Color color, float border, Color text_color,
	std::wstring name, int size_ch, Color title_color) :
	Button(size, position, color, border, name, size_ch, text_color) {
	text_.setPosition({ position.x + 5, position.y + 2 });
	text_.setCharacterSize(size.y - 10);
	text_.setFillColor(text_color);
}

void InputField::setOnlyNumbers(bool type) {
	only_numbers_ = type;
}

void InputField::setTitle(std::wstring name, int size, Color color) {
	Button::setTitle(name, size, color);
}

void InputField::setTitlePosition(Vector2f pos) {
	Button::setTitlePosition(pos);
}

void InputField::setButtonPosition(Vector2f pos) {
	Button::setButtonPosition(pos);
}

void InputField::setTextPosition(Vector2f pos) {
	text_.setPosition(pos);
}

void InputField::setButtonSettings(Vector2f size, int outline_size, Color fill, Color outline) {
	Button::setButtonSize(size, outline_size);
	Button::setButtonColor(fill, outline);
}

void InputField::setTextSettings(int size, Color color) {
	text_.setCharacterSize(size);
	text_.setFillColor(color);
}

std::wstring InputField::getValue() {
	return text_.getString();
}

bool InputField::isChosen() {
	return chosen_;
}

void InputField::change(Event& now, Vector2i mouse) {
	if (chosen_) {
		if (now.key.code == Keyboard::Backspace && value.size() != 0) {
			Time time = clock_.getElapsedTime();
			if (time > milliseconds(130)) {
				clock_.restart();
				value.pop_back();
			}
		}
		if (now.type == Event::TextEntered) {
			if (now.text.unicode < 128 && now.text.unicode != 8 ||
				now.text.unicode >= 1025 && now.text.unicode <= 1105) {
				if (!only_numbers_ || (now.text.unicode >= (wchar_t)'0' && now.text.unicode <= (wchar_t)'9')) {
					value += now.text.unicode;
				}
			}
		}
		text_.setString(value);
		int left = text_.getLocalBounds().left;
		int width = text_.getLocalBounds().width;
		if (text_.getPosition().x + text_.getLocalBounds().width >= field_.getPosition().x + field_.getSize().x) {
			value.pop_back();
			text_.setString(value);
		}
	}
	if (contains(mouse) && now.type == Event::MouseButtonPressed && now.key.code == Mouse::Left) {
		chosen_ = true;
		backlight_ = -1;
	} else if (!contains(mouse) &&
		(now.key.code == Mouse::Left && now.type == Event::MouseButtonPressed)
		|| now.key.code == Keyboard::Enter) {
		chosen_ = false;
		backlight_ = -2;
	} else if (backlight_ != -1) {
		backlight_ = -2;
	}
}

void InputField::draw(RenderWindow& window) {
	Button::draw(window);
	text_.setFont(font);
	window.draw(text_);
}
