#pragma once
#include "Market.h"
#include "Provider.h"
#include "Manager.h"
#include <deque>
#include <algorithm>
#include "Smart.h"

class Stock {
public:

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
		std::vector <Package> order;
		for (int i = 0; i < items_.size(); ++i) {
			order[i].setCount(max_count_[i] - case_[i].size());
		}
		manager_->makeOrder(order);
		provider_->getOrder(order);
	}

	void makePrices() {
		manager_->makePrices(items_);
	}

	void getOrder() {
		for (int i = 0; i < markets_.size(); ++i) {
			std::vector <int> order = markets_[i]->getOrderList(items_);
			for (int j = 0; j < order.size(); ++j) {
				orders_[i][j] += order[j]; 
			}
		}
	}

	void writeOff() {
		for (auto& v : case_) {
			while (!v.empty() && v[0].getLastDay() < day_) {
				// возможно положить посчитать количество мусора
				v.pop_front();
			}
		}
	}

	void sendDelivery() {
		for (int i = 0; i < markets_.size(); ++i) {
			std::vector<Package> to_send;
			for (int j = 0; j < orders_.size(); ++j) {
				while (!case_[j].empty() && case_[j][0].getCount() <= orders_[i][j]) {
					balance_ += case_[j][0].getActual();
					to_send.push_back(case_[j][0]);
					case_[j].pop_front();
				}
			}
			markets_[i]->getProducts(to_send);
		}
	}

	void setManager(Manager* manager) {
		manager_ = manager;
	}

	friend void Smart::makeOrder(std::vector <Package>& items);
	friend void Smart::makePrices(std::vector <Package>& items);

private:
	int balance_;
	int day_;
	std::vector <Market*> markets_;
	std::vector <std::vector<int>> orders_;
	std::vector <std::deque<Package>> case_;
	std::vector <Package> items_;
	std::vector <int> max_count_;
	Provider* provider_;
	Manager* manager_;
};

