#pragma once
#include "Market.h"
#include <deque>

class Stock {
public:

	Stock(std::vector<Market*> markets, std::vector<Package>& basic_shelf, std::vector<int>& max_count):
		balance_(0), day_(0), markets_(markets), items_(basic_shelf), max_count_(max_count) {}

	void writeOff() {
		for (auto& v : case_) {
			while (!v.empty() && v[0].getLastDay() < day_) {
				// возможно положить посчитать количество мусора
				v.pop_front();
			}
		}
	}

private:
	int balance_;
	int day_;
	std::vector <Market*> markets_;
	std::vector <std::vector<Package>> orders_;
	std::vector <std::deque <Package>> case_;
	std::vector <Package> items_;
	std::vector <int> max_count_;
};

