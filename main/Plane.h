#pragma once
#include <SFML/Graphics.hpp>
#include "Provider.h"
#include "Market.h"
#include "Button.h"
#include "Stock.h"
#include "Statistic.h"
#include "Scrollbar.h"
#include "Inputfield.h"
#include "Smart.h"
#include "Simple.h"
#include <vector>
#include <random>
#include <chrono>

static std::mt19937 rnd(std::chrono::steady_clock().now().time_since_epoch().count());

class Plane {
public:
	void getStart() {
		RenderWindow window(VideoMode(600, 375), "get started", Style::Close | Style::Titlebar);
		InputField days_field({ 200, 40 }, { 200, 50 }, grey_, 1);
		days_field.setTitle(L"Количество дней", 17, Color::White);
		days_field.setTitlePosition({ 232, 100 });
		days_field.setOnlyNumbers(true);
		InputField types_field({ 200, 40 }, { 200, 150 }, grey_, 1);
		types_field.setTitle(L"Количество типов", 17, Color::White);
		types_field.setTitlePosition({ 228, 200 });
		types_field.setOnlyNumbers(true);
		InputField markets_field({ 200, 40 }, { 200, 250 }, grey_, 1);
		markets_field.setTitle(L"Количество магазинов", 17, Color::White);
		markets_field.setTitlePosition({ 210, 300 });
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
			types_ = std::min(14, std::stoi(types_field.getValue()));
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
	}

	bool insideArea(Vector2i mouse_position) {
		return (mouse_position.y >= edges_[0].getPosition().y + edges_[0].getSize().y &&
			mouse_position.y <= edges_[3].getPosition().y &&
			mouse_position.x >= edges_[1].getPosition().x + edges_[1].getSize().x &&
			mouse_position.x <= edges_[2].getPosition().x);
	}

	Plane() {
		makePackages();
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
		manager_choose_ = Button({ 300, 79 }, {950, 890}, grey_, 1);
		manager_choose_.setTitle(L"Smart", 40);
		manager_choose_.setTitlePosition({ 1040, 905 });
		smart_ = true;
		bar_ = ScrollBar(12, 565, { 30, 400 });
		bar_.setCircleColor(Color::White);
		bar_.setLineColor(grey_);
		days_ = 1;
		types_ = 1;
		markets_cnt_ = 1;
		getStart();
		stats_ = Statistic({ 1250, 165 }, { 85, 35 }, days_);
		stats_.setColor(green_, red_);
		stats_.setTextColor(Color::White);
		shuffle(packages_.begin(), packages_.end(), rnd);
		while (types_ < packages_.size()) packages_.pop_back();
		for (int i = 0; i < packages_.size(); ++i) {
			packages_[i].setNumber(i);
		}
		initialization();
		shelves_.resize(types_);
		for (int i = 0; i < shelves_.size(); ++i) {
			shelves_[i] = Button({ 738, 79 }, Vector2f(61, 402 + 81 * i), green_, 1);
			shelves_[i].setTitle(packages_[i].getName() + L" - " + std::to_wstring(stock_->getCaseCount(i)) +
				L" packages" + L" - " + std::to_wstring(stock_->getCost(i)) + L" $", 30, Color::White);
			shelves_[i].setTitlePosition(Vector2f(86, 422 + 81 * i));
		}
		market_buttons_.resize(markets_cnt_);
		for (int i = 0; i < market_buttons_.size(); ++i) {
			market_buttons_[i] = Button({ 120, 100 }, Vector2f(880 + (i % 3) * 160, 400 + (i / 3) * 160), grey_, 1);
			market_buttons_[i].setTitle(std::to_wstring(i + 1), 30);
			market_buttons_[i].setTitlePosition(Vector2f(930 + (i % 3) * 160, 430 + (i / 3) * 160));
		}

	}

	void performDay() {
		if (!smart_) manager_ = new Simple();
		else manager_ = new Smart();
		manager_->setStock(stock_);
		stock_->setManager(manager_);
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

	void changePackage(int ind) {
		RenderWindow window(VideoMode(600, 400), "change item", Style::Close | Style::Titlebar);
		InputField cost({ 200, 40 }, { 200, 50 }, grey_, 1);
		cost.setTitle(L"Цена", 17, Color::White);
		cost.setTitlePosition({ 279, 100 });
		cost.setOnlyNumbers(true);
		InputField discount({ 200, 40 }, { 200, 150 }, grey_, 1);
		discount.setTitle(L"Скидка", 17, Color::White);
		discount.setTitlePosition({ 269, 200 });
		discount.setOnlyNumbers(true);
		while (window.isOpen()) {
			window.clear(back_color_);
			Event event;
			Vector2i mouse_position = Mouse::getPosition(window);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
				}
				cost.change(event, mouse_position);
				discount.change(event, mouse_position);
			}

			discount.draw(window);
			cost.draw(window);

			window.display();
		}
		int value = stock_->getPrice(ind), discount_value = stock_->getDiscount(ind);
		if (cost.getValue() != L"") {
			value = std::min(50, std::stoi(cost.getValue()));
		}
		if (discount.getValue() != L"") {
			discount_value = std::min(40, std::stoi(discount.getValue()));
		}
		stock_->setPrice(ind, value, discount_value);
	}

	void changeMarket(int ind) {
		RenderWindow window(VideoMode(600, 400), "change item", Style::Close | Style::Titlebar);
		InputField customers({ 200, 40 }, { 200, 50 }, grey_, 1);
		customers.setTitle(L"Количество покупателей", 17, Color::White);
		customers.setTitlePosition({ 205, 100 });
		customers.setOnlyNumbers(true);
		while (window.isOpen()) {
			window.clear(back_color_);
			Event event;
			Vector2i mouse_position = Mouse::getPosition(window);
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
				}
				customers.change(event, mouse_position);
			}
			customers.draw(window);
			window.display();
		}
		int value = markets_[ind]->getCount();
		if (customers.getValue() != L"") {
			value = std::min(75, std::stoi(customers.getValue()));
		}
		markets_[ind]->setCount(value);
	}

	void play() {
		RenderWindow window(VideoMode(1400, 1000), "simulation", Style::Close | Style::Titlebar);
		for (int day = 0; day <= days_; ++day) {
			bool end = false, check = true;
			while (window.isOpen() && check) {
				window.clear(back_color_);
				Event event;
				Vector2i mouse_position = Mouse::getPosition(window);
				while (window.pollEvent(event)) {
					if (event.type == Event::Closed) {
						window.close();
						end = true;
					}
					if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
						check = false;
						break;
					}
					bar_.changeCircle(mouse_position, event);
					if (bar_.isChosen() && !shelves_.empty()) {
						double value = bar_.getValue() * (shelves_.back().getPosition().y - shelves_[0].getPosition().y);
						for (int i = 0; i < shelves_.size(); ++i) {
							shelves_[i].setButtonPosition(Vector2f(61, 402 + 81 * i - value));
							shelves_[i].setTitlePosition(Vector2f(86, 422 + 81 * i - value));
						}
					}
					for (int i = 0; i < shelves_.size(); ++i) {
						if (shelves_[i].pressed(mouse_position, event) && insideArea(mouse_position)) {
							changePackage(i);
							for (int i = 0; i < shelves_.size(); ++i) {
								shelves_[i].setTitle(packages_[i].getName() + L" - " + std::to_wstring(stock_->getCaseCount(i)) +
									L" packages" + L" - " + std::to_wstring(stock_->getCost(i)) + L" $", 30, Color::White);
							}
						}
					}
					for (int i = 0; i < market_buttons_.size(); ++i) {
						if (market_buttons_[i].pressed(mouse_position, event)) {
							changeMarket(i);
						}
					}

					if (manager_choose_.pressed(mouse_position, event)) {
						if (smart_) {
							manager_ = new Simple();
							manager_choose_.setTitle(L"Simple", 40);
						} else {
							manager_ = new Smart();
							manager_choose_.setTitle(L"Smart", 40);
						}
						smart_ = !smart_;
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
			if (end) break;
			performDay();
			for (int i = 0; i < shelves_.size(); ++i) {
				if (packages_[i].isDiscount()) {
					shelves_[i].setButtonColor(red_);
				} else {
					shelves_[i].setButtonColor(green_);
				}
				shelves_[i].setTitle(packages_[i].getName() + L" - " + std::to_wstring(stock_->getCaseCount(i)) +
					L" packages" + L" - " + std::to_wstring(stock_->getCost(i)) + L" $", 30, Color::White);
			}
			stats_.addValue(stock_->getBalance());
		}
	}

	void makePackages() {
		packages_.push_back(Package(6, new Item(L"Молоко", 0, 9, 6, 4, 7, 0.76)));
		packages_.push_back(Package(20, new Item(L"Хлеб", 1, 7, 5, 3, 4, 0.82)));
		packages_.push_back(Package(12, new Item(L"Яблоки", 2, 12, 8, 5, 20, 0.32)));
		packages_.push_back(Package(110, new Item(L"Сырок", 3, 7, 5, 3, 40, 0.12)));
		packages_.push_back(Package(100, new Item(L"Ролтон", 4, 7, 5, 3, 100000, 0.12)));
		packages_.push_back(Package(25, new Item(L"Макароны", 5, 8, 5, 3, 100, 0.45)));
		packages_.push_back(Package(60, new Item(L"Чай", 6, 15, 10, 8, 100, 0.37)));
		packages_.push_back(Package(10, new Item(L"Помидоры", 7, 20, 14, 12, 7, 0.25)));
		packages_.push_back(Package(32, new Item(L"Зеленый горошек", 8, 13, 9, 7, 20, 0.7)));
		packages_.push_back(Package(20, new Item(L"Гречка", 9, 17, 12, 8, 10, 0.2)));
		packages_.push_back(Package(10, new Item(L"Фарш", 10, 20, 14, 10, 5, 0.18)));
		packages_.push_back(Package(30, new Item(L"Майонез", 11, 13, 9, 8, 12, 0.7)));
		packages_.push_back(Package(1, new Item(L"Тараканы", 12, 100, 99, 99, 900, 1)));
		packages_.push_back(Package(40, new Item(L"Мюсли", 13, 14, 10, 7, 15, 0.15)));
	}

private:
	Color back_color_, green_, red_, grey_;
	std::vector<RectangleShape> edges_;
	Button manager_choose_, types_choose_;
	Statistic stats_;
	std::vector<Button> shelves_;
	std::vector<Button> market_buttons_;
	ScrollBar bar_;

	bool smart_;
	int days_, types_, markets_cnt_;
	Provider* provider_;
	Stock* stock_;
	Manager* manager_;
	std::vector<Market*> markets_;
	std::vector <Package> packages_;
	std::vector <int> max_count_;
};
