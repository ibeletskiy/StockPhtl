#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <SFML/Graphics.hpp>

class Item {
public:
	Item(std::string name_, int number_, int price_, int discount_, int wholesale_, int duration_, double interest_):
		name(name_), number(number_), price(price_), discount(discount_), wholesale(wholesale_),
		duration(duration_), interest(interest_) {}

	Item(Item& other) {
		*this = other;
	}

	std::string name;
	int number;
	int price;
	int discount;
	int wholesale;
	int last_day;
	int duration;
	double interest;
};

class Package : public Item {
public:
	Package(int count_, Item& item) : count(count), Item(item) {}

	int count;
};

class Market {
public:
	Market(std::vector<Package>& basic_shelf) {
		customer_count = 100;
		for (Package package : basic_shelf) {
			shelf.push_back(package);
			max_count.push_back(customer_count * package.interest * package.duration);
		}
	}

	void GetProducts(std::vector<Package>& input) {
		for (Package package : input) {
			shelf[package.number].count += package.number;
		}
	}

	std::vector<int> GetOrderList(std::vector<std::pair<Package, int>>& prices) {
		std::vector <int> order;
		for (auto& package : prices) {
			int number = package.first.number;
			if (package.first.price == package.second) {
				order.push_back(std::max(0.0, max_count[number] * 0.8 - shelf[number].count));
			}
			else {
				order.push_back(max_count[number] - shelf[number].count);
			}
		}
		return order;
	}

	void PerformDay() {
		for (Package& package : shelf) {
			package.count = std::max(0.0, package.count - customer_count * package.interest);
		}
	}

	int customer_count;
	std::vector<Package> shelf;
	std::vector<int> max_count;
};

class Provider {


	int day;
};

int main() {

}