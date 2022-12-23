#include "Smart.h"
#include "Stock.h"
#include "Market.h"

void Smart::makeOrder(std::vector <Package>& order) {
	for (Package& item : order) {
		if (!stock_->case_[item.getNumber()].empty() && stock_->case_[item.getNumber()].front().getLastDay() - stock_->day_ <= 2) {
			item.setCount(0);
		}
		else 
		{
			int cnt = 0;
			for (Market* market : stock_->markets_) {
				cnt += std::max(0.0, market->max_count_[item.getNumber()] * 0.8 - market->shelf_[item.getNumber()].getCount());
			}
			cnt /= stock_->items_[item.getNumber()].getCount();
			cnt = std::min(cnt, stock_->max_count_[item.getNumber()]);
			item.setCount(std::max(0, int(cnt - stock_->case_[item.getNumber()].size() - stock_->ordered_[item.getNumber()])));
		}
	}
}

void Smart::makePrices(std::vector <Package>& items) {
	for (Package& item : items) {
		int cnt = 0;
		for (Package package : stock_->case_[item.getNumber()]) {
			if (double(package.getLastDay() - stock_->day_) <= 0.3 * package.getDuration()) {
				++cnt;
			}
		}
		if (cnt * 3 > stock_->case_[item.getNumber()].size()) {
			item.setDiscount();
		}
		else {
			item.deleteDiscount();
		}
	}
}