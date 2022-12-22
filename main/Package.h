#pragma once
#include "Item.h"

class Package : public Item {
public:
	Package(int count_, Item* item) : count_(count_), Item(*item) {}

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

