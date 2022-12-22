#pragma once
#include <vector>
#include "Package.h"
#include <utility>
#include <random>
#include <chrono>
#include <queue>

class Provider {
public:
	Provider(std::vector<Package>& basic_shelf);

	void performDay();

	std::vector<Package> sendDelivery();

	void getOrder(std::vector<Package>& order);

	~Provider() = default;

private:
	int day_;
	std::vector<std::queue<Package>> item_queue_;
	std::vector<Package> order_;
	std::vector<int> volume_;
};

