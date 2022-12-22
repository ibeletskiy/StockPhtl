#pragma once
#include "Manager.h"
#include <vector>

class Simple : public Manager {
public:
	virtual void makePrices(std::vector <Package>& items) override {
		for (auto& package : items) {
			package.deleteDiscount();
		}
	}
	virtual void makeOrder(std::vector <Package>& order) override;
};
