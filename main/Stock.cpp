#include "Stock.h"

Stock::Stock(std::vector<Market*> markets, std::vector<Package>& basic_shelf, std::vector<int>& max_count, Provider* provider) :
	balance_(0), day_(0), markets_(markets), items_(basic_shelf), max_count_(max_count), provider_(provider) {
	std::sort(markets_.begin(), markets_.end(), [](Market* a, Market* b) { return *b < *a; });
	orders_.resize(markets.size());
	case_.resize(basic_shelf.size());
	for (auto& vec : orders_) {
		vec.resize(items_.size(), 0);
	}
	ordered_.resize(items_.size(), 0);
	manager_ = nullptr;
}

int Stock::getCaseSize() {
	return (int)case_.size();
}

void Stock::getDelivery() {
	std::vector <Package> order = provider_->sendDelivery();
	for (Package package : order) {
		case_[package.getNumber()].push_back(package);
		ordered_[package.getNumber()]--;
	}
	for (int i = 0; i < case_.size(); ++i) {
		while (case_[i].size() > max_count_[i]) case_[i].pop_front();
	}
}

void Stock::makeOrder() {
	std::vector <Package> order = items_;
	for (int i = 0; i < items_.size(); ++i) {
		order[i].setCount(max_count_[i] - case_[i].size());
	}
	manager_->makeOrder(order);
	provider_->getOrder(order);
	for (int i = 0; i < items_.size(); ++i) {
		ordered_[i] += order[i].getCount();
		balance_ -= order[i].getCount() * items_[i].getCount() * items_[i].getWholesale();
	}
}

int Stock::getCaseCount(int i) {
	return case_[i].size();
}

int Stock::getCost(int i) {
	return items_[i].getActual();
}

int Stock::getPrice(int i) {
	return items_[i].getPrice();
}

int Stock::getDiscount(int i) {
	return items_[i].getDiscount();
}

int Stock::getBalance() {
	return balance_;
}

void Stock::makePrices() {
	manager_->makePrices(items_);
}

void Stock::getOrder() {
	for (int i = 0; i < markets_.size(); ++i) {
		std::vector <int> order = markets_[i]->getOrderList(items_);
		for (int j = 0; j < order.size(); ++j) {
			orders_[i][j] += order[j];
		}
	}
}


void Stock::writeOff() {
	for (auto& v : case_) {
		while (!v.empty() && v[0].getLastDay() < day_) {
			// возможно положить посчитать количество мусора
			v.pop_front();
		}
	}
}

void Stock::sendDelivery() {
	++day_;
	for (int i = 0; i < markets_.size(); ++i) {
		std::vector<Package> to_send;
		for (int j = 0; j < orders_.size(); ++j) {
			while (!case_[j].empty() && case_[j][0].getCount() <= orders_[i][j]) {
				balance_ += items_[j].getActual() * case_[j][0].getCount();
				orders_[i][j] -= case_[j][0].getCount();
				to_send.push_back(case_[j][0]);
				case_[j].pop_front();
			}
		}
		markets_[i]->getProducts(to_send);
	}
}

void Stock::setManager(Manager* manager) {
	manager_ = manager;
}
