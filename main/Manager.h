#pragma once
#include "Package.h"
#include <vector>

class Stock;

class Manager {
public:
	virtual void makePrices(std::vector <Package>& items) = 0;
	virtual void makeOrder(std::vector <Package>& order) = 0;
protected:
	Stock* stock_;
};

