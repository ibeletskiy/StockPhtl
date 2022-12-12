﻿#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <SFML/Graphics.hpp>

class Item {
public:
	Item(std::string name_, int number_, int price_, int discount_, int wholesale_, int duration_, double interest_):
		name_(name_), number_(number_), price_(price_), actual_(price_), discount_(discount_), wholesale_(wholesale_),
		duration_(duration_), interest_(interest_), is_discount_(0) {}

	Item(const Item& other) {
		*this = other;
	}

	int getActual() const {
		return actual_;
	}

	bool isDiscount() const {
		return (actual_ == discount_);
	}

	void setDiscount() {
		actual_ = discount_;
	}

	double getInterest() const {
		return interest_;
	}

	int getNumber() const {
		return number_;
	}

	int getDuration() const {
		return duration_;
	}
	
	int getPrice() const {
		return price_;
	}

protected:
	std::string name_;
	int number_;
	int actual_;
	int price_;
	int discount_;
	int wholesale_;
	int last_day_;
	int duration_;
	double interest_;
	bool is_discount_;
};

class Package : public Item {
public:
	Package(int count_, Item& item) : count_(count_), Item(item) {}

	int getCount() const {
		return count_;
	}

	void setCount(int val) {
		count_ = val;
	}

	void addCount(int val) {
		count_ += val;
	}

private:
	int count_;
};

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

	std::vector<int> getOrderList(std::vector<std::pair<Package, int>>& prices) {
		std::vector <int> order;
		for (auto& package : prices) {
			int number = package.first.getNumber();
			if (package.first.getPrice() == package.second) {
				order.push_back(std::max(0.0, max_count_[number] * 0.8 - shelf_[number].getCount()));
			}
			else {
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

private:
	int customer_count_;
	std::vector<Package> shelf_;
	std::vector<int> max_count_;
};

class Provider {
	Provider() {

	}

	~Provider() = default;

private:
	int day_;
};

int main() {

}