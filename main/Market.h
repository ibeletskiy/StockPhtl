#pragma once
#include <vector>
#include "Package.h"

class Market {
public:
	Market(std::vector<Package>& basic_shelf) {
		customer_count_ = 100;
		for (Package package : basic_shelf) {
			shelf_.push_back(package);
			max_count_.push_back(customer_count_ * package.getInterest() * package.getDuration());
		}
	}

	void getProducts(std::vector<Package>& input) {
		for (Package package : input) {
			shelf_[package.getNumber()].addCount(package.getCount());
		}
	}

	std::vector<int> getOrderList(const std::vector<Package>& prices) {
		std::vector <int> order;
		for (auto& package : prices) {
			int number = package.getNumber();
			if (!package.isDiscount()) {
				order.push_back(std::max(0.0, max_count_[number] * 0.8 - shelf_[number].getCount()));
			} else {
				order.push_back(max_count_[number] - shelf_[number].getCount());
			}
		}
		return order;
	}

	void performDay() {
		for (Package& package : shelf_) {
			package.setCount(std::max(0.0, package.getCount() - customer_count_ * package.getInterest()));
		}
	}

	bool operator<(Market other) {
		return this->customer_count_ < other.customer_count_;
	}

private:
	int customer_count_;
	std::vector<Package> shelf_;
	std::vector<int> max_count_;
};
