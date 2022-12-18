#pragma once
#include "Package.h"

class Stock;

class Manager {
public:
	virtual void makePrices(std::vector <Package>& items) = 0;
	virtual void makeOrder() = 0;

private:
	Stock* stock;
};

