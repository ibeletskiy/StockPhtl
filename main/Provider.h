#pragma once
#include <vector>
#include "Package.h"
#include <map>
#include <utility>
#include <random>
#include <chrono>
#include <queue>

std::mt19937 rnd(std::chrono::steady_clock().now().time_since_epoch().count());

class Provider {
	Provider(std::vector<Package>& basic_shelf) {
		for (auto package : basic_shelf) {
			volume_.push_back(package.getCount());
		}
		day_ = 0;
	}

	void performDay() { // создать getLastDay()
		order_.clear();
		++day_;
		for (int i = 0; i < item_queue_.size(); ++i) {
			int date;
			if (!item_queue_[i].empty()) {
				date = day_ + item_queue_[i].front().getDuration();
			}
			while (!item_queue_[i].empty() && item_queue_[i].front().getLastDay() == day_) {
				order_.push_back(item_queue_[i].front());
				order_.back().setLastDay(date);
				item_queue_[i].pop();
			}
		}
	}

	std::vector<Package> getDelivery() {
		return order_;
	}

	void getOrder(std::vector<Package>& order) {
		for (int i = 0; i < order.size(); ++i) {
			if (order[i].getCount() == 0) continue;
			int date = day_;
			if (item_queue_[i].empty()) {
				date += 1;
			} else {
				date = item_queue_[i].back().getLastDay() + 1;
			}
			Package package = order[i];
			package.setCount(volume_[i]);
			package.setLastDay(date);
			for (int j = 0; j < order[i].getCount(); ++j) {
				item_queue_[i].push(package);
			}
		}
	}

	~Provider() = default;

private:
	int day_;
	std::vector<std::queue<Package>> item_queue_;
	std::vector<Package> order_;
	std::vector<int> volume_;
};

