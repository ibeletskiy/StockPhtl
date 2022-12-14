#pragma once
#include <string>

class Item {
public:
	Item(std::wstring name_, int number_, int price_, int discount_, int wholesale_, int duration_, double interest_) :
		name_(name_), number_(number_), price_(price_), actual_(price_), discount_(discount_), wholesale_(wholesale_),
		duration_(duration_), interest_(interest_), is_discount_(0) {}

	int getActual() const {
		return actual_;
	}

	std::wstring getName() const {
		return name_;
	}

	bool isDiscount() const {
		return (actual_ == discount_);
	}

	void setDiscount() {
		actual_ = discount_;
	}

	void deleteDiscount() {
		actual_ = price_;
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

	int getDiscount() const {
		return discount_;
	}

	int getLastDay() const {
		return last_day_;
	}

	int getWholesale() const {
		return wholesale_;
	}

	void setNumber(int n) {
		number_ = n;
	}

	void setNewPrice(int price) {
		price_ = price;
	}

	void setNewDiscount(int discount) {
		discount_ = discount;
	}

protected:
	std::wstring name_;
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
