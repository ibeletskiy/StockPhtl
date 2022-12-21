#pragma once
#include "Column.h"

class Vertical : public Column {
public :
	Vertical() = default;
	Vertical(Vector2f size, Vector2f pos, int value = 0) : Column(size, pos, value) {}
	virtual void setPosition(Vector2f pos) override {
		shape_.setPosition({pos.x, pos.y - shape_.getSize().y});
	}

	virtual void setValue(float val) override {
		shape_.setPosition(Vector2f(shape_.getPosition().x, shape_.getPosition().y + shape_.getSize().y - val ));
		shape_.setSize({ shape_.getSize().x, val });
	}

	virtual void setSize(float size) override {
		shape_.setSize(Vector2f(size, 0));
	}
};

