#pragma once
#include <SFML/Graphics.hpp>
#include "Provider.h"
#include "Market.h"
#include "Button.h"
#include "Stock.h"
#include "Statistic.h"
#include "Scrollbar.h"
#include "Inputfield.h"
#include <vector>
#include <random>
#include <chrono>

static std::mt19937 rnd(std::chrono::steady_clock().now().time_since_epoch().count());

class Plane {
public:

	void getStart() {
		RenderWindow window(VideoMode(1400, 1000), "get started", Style::Close | Style::Titlebar);
		InputField days_field({ 1, 1 }, { 1, 1 }, Color::White);
		days_field.setOnlyNumbers(true);
		InputField types_field({ 1, 1 }, { 1, 1 }, Color::White);
		types_field.setOnlyNumbers(true);
		InputField markets_field({ 1, 1 }, { 1, 1 }, Color::White);
		markets_field.setOnlyNumbers(true);
		while (window.isOpen()) {
			window.clear(back_color_);
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
			markets_cnt_ = std::min(9, std::stoi(markets_field.getValue()));
		}
	}

	void initialization() {
		for (int i = 0; i < markets_cnt_; ++i) {
			markets_.push_back(new Market(packages_));
		}
		provider_ = new Provider(packages_);
		for (int i = 0; i < packages_.size(); ++i) {
			max_count_.push_back(50);
		}
		stock_ = new Stock(markets_, packages_, max_count_, provider_);
		manager_ = new Smart();
		manager_->setStock(stock_);
		stock_->setManager(manager_);
	}

	Plane() {
		back_color_ = Color(13, 18, 43, 255);
		green_ = Color(130, 209, 25, 255);
		red_ = Color(182, 13, 58, 255);
		grey_ = Color(204, 204, 204, 255);
		edges_.resize(4);
		edges_[0] = RectangleShape({ 1400, 400 });
		edges_[0].setPosition({0, 0});
		edges_[0].setFillColor(back_color_);
		edges_[1] = RectangleShape({ 60, 565 });
		edges_[1].setPosition({ 0, 400 });
		edges_[1].setFillColor(back_color_);
		edges_[2] = RectangleShape({600, 565 });
		edges_[2].setPosition({800, 400});
		edges_[2].setFillColor(back_color_);
		edges_[3] = RectangleShape({1400, 35});
		edges_[3].setPosition({0, 965});
		edges_[3].setFillColor(back_color_);
		stats_ = Statistic();
		manager_choose_ = Button();
		types_choose_ = Button();
		bar_ = ScrollBar();
		days_ = 1;
		types_ = 0;
		markets_cnt_ = 0;
		getStart();
		shuffle(packages_.begin(), packages_.end(), rnd);
		while (types_ < packages_.size()) packages_.pop_back();
		// где то тут должны быть инициализация склада магазинов и поставщика, но пока что ее забыли
		shelves_.resize(6);
		for (int i = 0; i < shelves_.size(); ++i) {
			shelves_[i] = Button({ 740, 79 }, Vector2f(60, 400 + 81 * i), green_);
		}
		/*market_buttons_.resize(markets_cnt_);
		for (int i = 0; i < market_buttons_.size(); ++i) {

		}*/

	}

	void performDay() {
		stock_->sendDelivery();
		provider_->performDay();
		stock_->getDelivery();
		stock_->makePrices();
		stock_->getOrder();
		stock_->makeOrder();
		for (Market* market : markets_) {
			market->performDay();
		}
	}

	void play() {
		RenderWindow window(VideoMode(1400, 1000), "simulation", Style::Close | Style::Titlebar);
		for (int day = 0; day < days_; ++day) {
			while (window.isOpen()) {
				window.clear(Color::White);
				Event event;
				Vector2i mouse_position = Mouse::getPosition(window);
				while (window.pollEvent(event)) {
					if (event.type == Event::Closed) {
						window.close();
					}
				}
				for (auto& now : shelves_) {
					now.draw(window);
				}
				for (auto& now : edges_) {
					window.draw(now);
				}
				manager_choose_.draw(window);
				bar_.draw(window);
				types_choose_.draw(window);
				stats_.draw(window, mouse_position);
				for (auto& now : market_buttons_) {
					now.draw(window);
				}
				window.display();
			}
			// тут должно быть все исполнение кода 
		}
	}

	void makePackages() {
		packages_.push_back(Package(6, new Item("Молоко", 0, 90, 60, 40, 7, 0.76)));
		packages_.push_back(Package(20, new Item("Хлеб", 1, 70, 50, 30, 4, 0.82)));
		packages_.push_back(Package(12, new Item("Яблоки", 2, 120, 80, 50, 20, 0.32)));
		packages_.push_back(Package(110, new Item("Сырок", 3, 70, 50, 30, 40, 0.12)));
		packages_.push_back(Package(100, new Item("Ролтон", 4, 70, 50, 25, 100000, 0.12)));
		packages_.push_back(Package(25, new Item("Макароны", 5, 80, 55, 30, 100, 0.45)));
		packages_.push_back(Package(60, new Item("Чай", 6, 150, 80, 60, 100, 0.37)));
		packages_.push_back(Package(10, new Item("Помидоры", 7, 200, 140, 120, 7, 0.25)));
		packages_.push_back(Package(32, new Item("Зеленый горошек", 8, 130, 90, 70, 20, 0.7)));
		packages_.push_back(Package(20, new Item("Гречка", 9, 170, 120, 80, 10, 0.2)));
		packages_.push_back(Package(10, new Item("Фарш", 10, 200, 140, 100, 5, 0.18)));
		packages_.push_back(Package(30, new Item("Майонез", 11, 130, 90, 80, 12, 0.7)));
		packages_.push_back(Package(1, new Item("Тараканы", 12, 1000, 999, 998, 900, 1)));
		packages_.push_back(Package(40, new Item("Мюсли", 13, 140, 100, 70, 15, 0.15)));
	}

private:
	// все что нужно заранее (строго в фронте)
	Color back_color_, green_, red_, grey_;
	std::vector<RectangleShape> edges_;
	Button manager_choose_, types_choose_;
	Statistic stats_;
	std::vector<Button> shelves_;
	std::vector<Button> market_buttons_;
	ScrollBar bar_;

	int days_, types_, markets_cnt_;
	Provider* provider_;
	Stock* stock_;
	Manager* manager_;
	std::vector<Market*> markets_;
	std::vector <Package> packages_;
	std::vector <int> max_count_;
};
