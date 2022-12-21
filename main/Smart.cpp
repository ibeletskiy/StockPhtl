#include "Smart.h"
#include "Stock.h"

void Smart::makeOrder(std::vector <Package>& order) {
	for (Package& item : order) {
		if (!stock_->case_[item.getNumber()].empty() && stock_->case_[item.getNumber()].front().getLastDay() - stock_->day_ <= 2) {
			item.setCount(0);
		}
		else {
			item.setCount(item.getCount() - stock_->ordered_[item.getNumber()]);
		}
	}
}

void Smart::makePrices(std::vector <Package>& items) {
	for (Package& item : items) {
		if (item.isDiscount()) {
			item.deleteDiscount();
			continue;
		}
		int cnt = 0;
		for (Package package : stock_->case_[item.getNumber()]) {
			if (package.getLastDay() - stock_->day_ <= 0.2 * package.getDuration()) {
				++cnt;
			}
		}
		if (cnt * 3 >= stock_->case_[item.getNumber()].size()) {
			item.setDiscount();
		}
		else {
			item.deleteDiscount();
		}
	}
}