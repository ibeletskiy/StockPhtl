#include "Simple.h"
#include "Stock.h"

void Simple::makeOrder(std::vector <Package>& order) {
	for (Package& item : order) {
		if (!stock_->case_[item.getNumber()].empty() && stock_->case_[item.getNumber()].front().getLastDay() - stock_->day_ <= 2) {
			item.setCount(0);
		}
		else {
			item.setCount(std::max(item.getCount() - stock_->ordered_[item.getNumber()], 0));
		}
	}
}

