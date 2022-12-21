#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Statistic.h"

using namespace sf;

int main() {
	font.loadFromFile("framd.ttf");
	Statistic s({ 800, 200 }, { 50, 50 }, 30);
	s.addValue(10);
	s.addValue(5);
	s.addValue(15);
	s.addValue(5);
	s.addValue(4);
	s.addValue(5);
	s.addValue(7);
	s.addValue(9);
	s.addValue(11);
	s.addValue(5);
	s.addValue(-10);
	RenderWindow window(VideoMode(1000, 1000), "stock", Style::Close | Style::Titlebar);
	while (window.isOpen()) {
		window.clear(Color::White);
		Vector2i mouse = Mouse::getPosition(window);
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
		}
		s.draw(window, mouse);
		window.display();
	}
}