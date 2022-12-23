#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class ScrollBar {
public:
	ScrollBar() = default;
	ScrollBar(int r, int length, Vector2f position, bool part_view = 0);

	void setLinePosition(Vector2f position);
	void setCirclePosition(Vector2f position);
	void setLineColor(Color color);
	void setCircleColor(Color color);
	bool contains(Vector2i mouse_position);
	bool pressed(Vector2i mouse_position, Event event);
	void changeCircle(Vector2i mouse_position, Event event);
	bool isChosen();
	double getValue();
	void draw(RenderWindow& window);

private: 
	CircleShape circle_;
	RectangleShape line_, part_;
	bool part_view_;
	bool pressed_;
};

