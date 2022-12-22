#include "Provider.h"
#include <random>
#include <chrono>

static std::mt19937 rnd(std::chrono::steady_clock().now().time_since_epoch().count());

Provider::Provider(std::vector<Package>& basic_shelf) {
	for (auto package : basic_shelf) {
		volume_.push_back(package.getCount());
	}
	day_ = 0;
}

void Provider::performDay() {
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

std::vector<Package> Provider::sendDelivery() {
	return order_;
}

void Provider::getOrder(std::vector<Package>& order) {
	for (int i = 0; i < order.size(); ++i) {
		if (order[i].getCount() == 0) continue;
		int date = day_;
		if (item_queue_[i].empty()) {
			date += 1 + rnd() % 4;
		}
		else {
			date = item_queue_[i].back().getLastDay() + rnd() % 3;
		}
		Package package = order[i];
		package.setCount(volume_[i]);
		package.setLastDay(date);
		for (int j = 0; j < order[i].getCount(); ++j) {
			item_queue_[i].push(package);
		}
	}
}

