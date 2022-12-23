#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Button {
public:
	Button() = default;
	Button(Vector2f size, Vector2f position, Color color, float border = 0,
		std::wstring name = L"", int size_ch = 20, Color title_color = Color::Black);
	void setTitle(std::wstring name, int size, Color color = { 0, 0, 0, 255 });
	void setTitlePosition(Vector2f pos);
	void setButtonPosition(Vector2f pos);
	void setButtonSize(Vector2f size, int size_thickness = 0);
	Vector2f getPosition();
	void setButtonColor(Color fill_color, Color outline_color = { 255, 255, 255, 255 });
	virtual bool contains(const Vector2i& mouse);
	bool pressed(Vector2i& mouse, Event now);
	bool rightPressed(Vector2i& mouse, Event now);
	void setBacklight(int value, int thickness, Color color = Color::White);
	void setOutline(Color color, int thickness);
	void draw(RenderWindow& window);

protected:
	Text title_;
	int backlight_thickness_;
	int backlight_;
	RectangleShape field_;
};