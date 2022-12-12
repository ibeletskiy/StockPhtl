#include <iostream>
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

	int getCost() {
		return actual_;
	}

	bool isDiscount() {
		return (actual_ == discount_);
	}

	void setDiscount() {

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

private:
	int count_;
};

class Market {
public:
	Market(std::vector<Package>& basic_shelf) {
		customer_count = 100;
		for (Package package : basic_shelf) {
			shelf.push_back(package);
			max_count.push_back(customer_count * package.interest_ * package.duration_);
		}
	}

	void GetProducts(std::vector<Package>& input) {
		for (Package package : input) {
			shelf[package.number_].count_ += package.number_;
		}
	}

	std::vector<int> GetOrderList(std::vector<std::pair<Package, int>>& prices) {
		std::vector <int> order;
		for (auto& package : prices) {
			int number = package.first.number_;
			if (package.first.price_ == package.second) {
				order.push_back(std::max(0.0, max_count[number] * 0.8 - shelf[number].count_));
			}
			else {
				order.push_back(max_count[number] - shelf[number].count_);
			}
		}
		return order;
	}

	void PerformDay() {
		for (Package& package : shelf) {
			package.count_ = std::max(0.0, package.count_ - customer_count * package.interest_);
		}
	}

private:
	int customer_count;
	std::vector<Package> shelf;
	std::vector<int> max_count;
};

class Provider {
	Provider() {

	}

	~Provider() = default;

private:
	int day;
};

int main() {

}