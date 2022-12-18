#pragma once
#include "Market.h"
#include "Provider.h"
#include <deque>
#include <algorithm>

class Stock {
public:
	void writeOff() {
		
	}

	

	Stock(std::vector<Market*> markets, std::vector<Package>& basic_shelf, std::vector<int>& max_count, Provider* provider):
		balance_(0), day_(0), markets_(markets), items_(basic_shelf), max_count_(max_count), provider_(provider) {
		std::sort(markets_.begin(), markets_.end(), [](Market* a, Market* b) { return *b < *a; });
	}

	void getDelivery() {
		std::vector <Package> order = provider_->sendDelivery();
		for (Package package : order) {
			case_[package.getNumber()].push_back(package);
		}
	}

	void makeOrder() {

	}

	void getOrder() {

	}


private:
	int balance_;
	int day_;
	std::vector <Market*> markets_;
	std::vector <std::vector<Package>> orders_;
	std::vector <std::deque <Package>> case_;
	std::vector <Package> items_;
	std::vector <int> max_count_;
	Provider* provider_;
};

