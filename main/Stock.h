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

	Stock(std::vector<Market*> markets, std::vector<Package>& basic_shelf, std::vector<int>& max_count, Provider* provider, Manager* manager);

	void getDelivery();

	void makeOrder();

	void makePrices();

	void getOrder();

	void writeOff();

	void sendDelivery();

	void setManager(Manager* manager);

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

