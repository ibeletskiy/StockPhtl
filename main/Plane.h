#pragma once
#include <SFML/Graphics.hpp>
#include "Provider.h"
#include "Market.h"
#include "Button.h"
#include "Stock.h"
#include "Statistic.h"
#include "Inputfield.h"
#include <vector>

class Plane {
public:

	void getStart() {
		RenderWindow window(VideoMode(1000, 800), "get started", Style::Close | Style::Titlebar);
		InputField days_field();
		InputField types_field();
		InputField markets_field();
		while (window.isOpen()) {
			Event event;
			Vector2i mouse_position = Mouse::getPosition(window);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
				}

			}
		}
	}
	
	Plane() {
		back_color_ = Color();
		green_ = Color();
		red_ = Color();
		grey_ = Color();
		edges.resize(4);
		edges[0] = RectangleShape();
		edges[1] = RectangleShape();
		edges[2] = RectangleShape();
		edges[3] = RectangleShape();
		stats_ = Statistic();
		days_ = 0;
		types_ = 0;
		getStart();
	}
	
	void play();

	void makePackages() {
		packages_.emplace_back(Package(10, new Item("Молоко", 0, 90, 60, 40, 7, 0.76)));
		packages_.emplace_back(Package(10, new Item("Хлеб", 1, 70, 50, 30, 4, 0.82)));
		packages_.emplace_back(Package(10, new Item("Яблоки", 2, 120, 80, 50, 20, 0.32)));
		packages_.emplace_back(Package(10, new Item("Сырок", 3, 70, 50, 30, 40, 0.12)));
		packages_.emplace_back(Package(10, new Item("Ролтон", 4, 70, 50, 25, 100000, 0.12)));
		packages_.emplace_back(Package(10, new Item("Макароны", 5, 80, 55, 30, 100, 0.45)));
		packages_.emplace_back(Package(10, new Item("Чай", 6, 150, 80, 60, 100, 0.37)));
		packages_.emplace_back(Package(10, new Item("Помидоры", 7, 200, 140, 120, 7, 0.25)));
	}

private:
	// все что нужно заранее (строго в фронте)
	Color back_color_, green_, red_, grey_;
	std::vector<RectangleShape> edges;
	Statistic stats_;
	std::vector<Button> shelves_;
	std::vector<Button> market_buttons_;
	Button manager_choose_;

	int days_, types_, markets_;
	Provider* provider_;
	Stock* stock_;
	Manager* manager_;
	std::vector<Market*> markets_;
	std::vector <Package> packages_;
	Statistic stats_;
};
