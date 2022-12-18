#pragma once
#include "Market.h"
#include "Provider.h"
#include "Manager.h"
#include <deque>
#include <algorithm>

class Stock {
public:
	void writeOff() {
		
	}

	Stock(std::vector<Market*> markets, std::vector<Package>& basic_shelf, std::vector<int>& max_count, Provider* provider,
		Manager* manager):
		balance_(0), day_(0), markets_(markets), items_(basic_shelf), max_count_(max_count), provider_(provider), manager_(manager) {
		std::sort(markets_.begin(), markets_.end(), [](Market* a, Market* b) { return *b < *a; });
		orders_.resize(markets.size());
		for (auto& vec : orders_) {
			vec.resize(items_.size(), 0);
		}
	}

	void getDelivery() {
		std::vector <Package> order = provider_->sendDelivery();
		for (Package package : order) {
			case_[package.getNumber()].push_back(package);
		}
	}

	void makeOrder() {

	}

	void makePrices() {

	}

	void getOrder() {
		for (int i = 0; i < markets_.size(); ++i) {
			std::vector <int> order = markets_[i]->getOrderList(items_);
			for (int j = 0; j < order.size(); ++j) {
				orders_[i][j] += order[j];
			}
		}
	}


private:
	int balance_;
	int day_;
	std::vector <Market*> markets_;
	std::vector <std::vector<int>> orders_;
	std::vector <std::deque <Package>> case_;
	std::vector <Package> items_;
	std::vector <int> max_count_;
	Provider* provider_;
	Manager* manager_;
};

