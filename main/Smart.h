#pragma once
#include "Manager.h"
#include <vector>

class Smart : public Manager {
public:
	virtual void makePrices(std::vector <Package>& items) override;
	virtual void makeOrder(std::vector <Package>& order) override;
};
