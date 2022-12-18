#pragma once
#include "Market.h"

class Stock {
public:

private:
	int balance_;
	std::vector <Market*> markets_;
	std::vector <std::vector<Package>> orders_;
	std::vector <std::vector<Package>> case_;

};

