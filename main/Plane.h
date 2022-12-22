#pragma once
#include <SFML/Graphics.hpp>
#include "Provider.h"
#include "Market.h"
#include "Button.h"
#include "Stock.h"
#include "Statistic.h"
#include "Inputfield.h"
#include <vector>

class Plane {
public:
	
	Plane() {
		
	}
	
	void play();

private:
	// все что нужно заранее (строго в
	std::vector<RectangleShape> edges;
	



	int days_;
	int types_;
	Provider* provider_;
	Stock* stock_;
	Manager* manager_;
	std::vector<Market*> markets_;
	std::vector<Button> market_buttons_;
	std::vector<Button> shelves_;
	Statistic stats_;
};
