#pragma once
#include "Market.h"
#include "Provider.h"
#include "Manager.h"
#include <deque>
#include <algorithm>
#include "Smart.h"
#include "Simple.h"

class Stock {
public:
	Stock() = default;
	Stock(std::vector<Market*> markets, std::vector<Package>& basic_shelf, std::vector<int>& max_count, Provider* provider);

	int getCaseSize();

	int getCaseCount(int i);

	int getCost(int i);

	int getDiscount(int i);

	int getPrice(int i);

	int getBalance();

	void getDelivery();

	void makeOrder();

	void makePrices();

	void getOrder();

	void writeOff();

	void sendDelivery();

	void setManager(Manager* manager);

	void setPrice(int it, int price, int discount) {
		bool disc = items_[it].isDiscount();
		items_[it].setNewPrice(price);
		items_[it].setNewDiscount(discount);
		if (disc) {
			items_[it].setDiscount();
		}
		else {
			items_[it].deleteDiscount();
		}
	}

	void sortMarkets() {
		std::sort(markets_.begin(), markets_.end(), [](Market* a, Market* b) { return *b < *a; });
	}

	friend void Smart::makeOrder(std::vector <Package>& items);
	friend void Simple::makeOrder(std::vector <Package>& items);
	friend void Smart::makePrices(std::vector <Package>& items);

private:
	int balance_;
	int day_;
	std::vector <Market*> markets_;
	std::vector <std::vector<int>> orders_;
	std::vector <std::deque<Package>> case_;
	std::vector <Package> items_;
	std::vector <int> ordered_;
	std::vector <int> max_count_;
	Provider* provider_;
	Manager* manager_;
};

