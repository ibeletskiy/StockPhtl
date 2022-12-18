#pragma once
#include "Market.h"
#include <deque>

class Stock {
public:
	

private:
	int balance_;
	std::vector <Market*> markets_;
	std::vector <std::vector<Package>> orders_;
	std::vector <std::deque<Package>> case_;

};
