#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Item {
public:
	std::string name;
	int article;
	int price;
	int discount;
	int last_day;
	int duration;
	double interest;
};

class Package : public Item {
public:
	int count;
};

class PackageList {
public:
	std::vector <Package> list;
};

class Case {
public:
	std::vector <PackageList> shelves;
	std::vector <int> max_count;
};

class Market {
public:
	Market(int item_count, PackageList& basic_shelf) {
		customer_count = 100;
	}

	int customer_count;
	PackageList shelf;
};

int main() {

}