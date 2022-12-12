#pragma once
#include <string>

class Item {
public:
	Item(std::string name_, int number_, int price_, int discount_, int wholesale_, int duration_, double interest_) :
		name_(name_), number_(number_), price_(price_), actual_(price_), discount_(discount_), wholesale_(wholesale_),
		duration_(duration_), interest_(interest_), is_discount_(0) {}

	Item(const Item& other) {
		*this = other;
	}

	int getActual() const {
		return actual_;
	}

	bool isDiscount() const {
		return (actual_ == discount_);
	}

	void setDiscount() {
		actual_ = discount_;
	}

	void setLastDay(int value) {
		last_day_ = value;
	}

	double getInterest() const {
		return interest_;
	}

	int getNumber() const {
		return number_;
	}

	int getDuration() const {
		return duration_;
	}

	int getPrice() const {
		return price_;
	}

	int getLastDay() const {
		return last_day_;
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
