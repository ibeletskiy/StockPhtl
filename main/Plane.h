#pragma once
#include <SFML/Graphics.hpp>
#include "Provider.h"
#include "Market.h"
#include "Button.h"
#include "Stock.h"
#include "Statistic.h"
#include <vector>

class Plane {
public:
	Plane();
	
	void play();

	void makePackages() {
		packages_.emplace_back(Package(6, new Item("Молоко", 0, 90, 60, 40, 7, 0.76)));
		packages_.emplace_back(Package(20, new Item("Хлеб", 1, 70, 50, 30, 4, 0.82)));
		packages_.emplace_back(Package(12, new Item("Яблоки", 2, 120, 80, 50, 20, 0.32)));
		packages_.emplace_back(Package(110, new Item("Сырок", 3, 70, 50, 30, 40, 0.12)));
		packages_.emplace_back(Package(100, new Item("Ролтон", 4, 70, 50, 25, 100000, 0.12)));
		packages_.emplace_back(Package(25, new Item("Макароны", 5, 80, 55, 30, 100, 0.45)));
		packages_.emplace_back(Package(60, new Item("Чай", 6, 150, 80, 60, 100, 0.37)));
		packages_.emplace_back(Package(10, new Item("Помидоры", 7, 200, 140, 120, 7, 0.25)));
		packages_.emplace_back(Package(32, new Item("Зеленый горошек", 8, 130, 90, 70, 20, 0.7)));
		packages_.emplace_back(Package(20, new Item("Гречка", 9, 170, 120, 80, 10, 0.2)));
		packages_.emplace_back(Package(10, new Item("Фарш", 10, 200, 140, 100, 5, 0.18)));
		packages_.emplace_back(Package(30, new Item("Майонез", 11, 130, 90, 80, 12, 0.7)));
		packages_.emplace_back(Package(1, new Item("Тараканы", 12, 1000, 999, 998, 900, 1)));
		packages_.emplace_back(Package(40, new Item("Мюсли", 13, 140, 100, 70, 15, 0.15)));
	}

private:
	Provider provider_;
	Stock stock_;
	Manager* manager_;
	std::vector<Market> markets_;
	std::vector<Button> market_buttons_;
	std::vector<Button> shelves_;
	std::vector <Package> packages_;
	Statistic stats_;
};
