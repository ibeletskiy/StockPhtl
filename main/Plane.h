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
		InputField days_field({ 1, 1 }, { 1, 1 }, Color::White);
		days_field.setOnlyNumbers(true);
		InputField types_field({ 1, 1 }, { 1, 1 }, Color::White);
		types_field.setOnlyNumbers(true);
		InputField markets_field({ 1, 1 }, { 1, 1 }, Color::White);
		markets_field.setOnlyNumbers(true);
		while (window.isOpen()) {
			window.clear(Color::White);
			Event event;
			Vector2i mouse_position = Mouse::getPosition(window);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
				}
				days_field.change(event, mouse_position);
				types_field.change(event, mouse_position);
				markets_field.change(event, mouse_position);
			}

			days_field.draw(window);
			types_field.draw(window);
			markets_field.draw(window);

			window.display();
		}
		if (days_field.getValue() != L"") {
			days_ = std::min(30, std::stoi(days_field.getValue()));
		}
		if (types_field.getValue() != L"") {
			types_ = std::min(17, std::stoi(types_field.getValue()));
		}
		if (markets_field.getValue() != L"") {
			markets_ = std::min(9, std::stoi(markets_field.getValue()));
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
		markets_ = 0;
		getStart();
		
	}
	
	void play();

	void makePackages() {
		packages_.emplace_back(Package(10, new Item("������", 0, 90, 60, 40, 7, 0.76)));
		packages_.emplace_back(Package(10, new Item("����", 1, 70, 50, 30, 4, 0.82)));
		packages_.emplace_back(Package(10, new Item("������", 2, 120, 80, 50, 20, 0.32)));
		packages_.emplace_back(Package(10, new Item("�����", 3, 70, 50, 30, 40, 0.12)));
		packages_.emplace_back(Package(10, new Item("������", 4, 70, 50, 25, 100000, 0.12)));
		packages_.emplace_back(Package(10, new Item("��������", 5, 80, 55, 30, 100, 0.45)));
		packages_.emplace_back(Package(10, new Item("���", 6, 150, 80, 60, 100, 0.37)));
		packages_.emplace_back(Package(10, new Item("��������", 7, 200, 140, 120, 7, 0.25)));
	}

private:
	// ��� ��� ����� ������� (������ � ������)
	Color back_color_, green_, red_, grey_;
	std::vector<RectangleShape> edges;
	Statistic stats_;
	std::vector<Button> shelves_;
	std::vector<Button> market_buttons_;
	Button manager_choose_, types_choose_;

	int days_, types_, markets_;
	Provider* provider_;
	Stock* stock_;
	Manager* manager_;
	std::vector<Market*> markets_;
	std::vector <Package> packages_;
	Statistic stats_;
};
