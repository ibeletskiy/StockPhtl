#pragma once
#include "Column.h"

class Vertical : public Column {
public :
	Vertical(Vector2f size, Vector2f pos, int value = 0) : Column(size, pos, value) {}
	virtual void setPosition(Vector2f pos) override {
		shape_.setPosition({pos.x, pos.y - shape_.getSize().y});
	}

	virtual void setValue(double val) override {
		shape_.setPosition({ shape_.getPosition().x, shape_.getPosition().y + shape_.getSize().y - val });
		shape_.setSize({ shape_.getSize().x, val });
	}

	virtual void setSize(double size) override {
		shape_.setSize({ size, 0 });
	}
};

