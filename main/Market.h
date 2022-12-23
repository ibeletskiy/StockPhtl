#pragma once
#include <vector>
#include "Package.h"
#include "Smart.h"

class Market {
public:
	Market(std::vector<Package>& basic_shelf);

	void getProducts(std::vector<Package>& input);

	std::vector<int> getOrderList(const std::vector<Package>& prices);

	void performDay();

	bool operator<(Market other);

	void setCount(int count);

	friend void Smart::makeOrder(std::vector <Package>& items);

private:
	int customer_count_;
	std::vector<Package> shelf_;
	std::vector<int> max_count_;
};
