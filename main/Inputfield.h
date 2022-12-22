#pragma once
#include "Button.h";
#include <SFML/Graphics.hpp>

using namespace sf;

extern Font font;

class InputField : Button {
public:
	InputField(Vector2f size, Vector2f position, Color color, float border = 0, Color text_color = Color::Black,
		std::wstring name = L"", int size_ch = 0, Color title_color = Color::Black);
	void setOnlyNumbers(bool type);
	void setTitle(std::wstring name, int size, Color color = { 0, 0, 0, 255 });
	void setTitlePosition(Vector2f pos);
	void setButtonPosition(Vector2f pos);
	void setTextPosition(Vector2f pos);
	void setButtonSettings(Vector2f size, int outline_size, Color fill, Color outline = { 0, 0, 0, 255 });
	void setTextSettings(int size, Color color);
	bool isChosen();
	std::wstring getValue();
	void change(Event& now, Vector2i mouse);
	void draw(RenderWindow& window);

protected:
	Text text_;
	bool chosen_ = false;
	bool only_numbers_ = false;
	Clock clock_;
	std::wstring value;
};