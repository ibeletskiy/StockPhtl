#pragma once
#include "Column.h"

class Horizontal : public Column {
public:
	Horizontal() = default;
	Horizontal(Vector2f size, Vector2f pos, int value = 0) : Column(size, pos, value) {}
	virtual void setPosition(Vector2f pos) override {
		shape_.setPosition(pos);
	}

	virtual void setValue(float val) override {
		shape_.setSize(Vector2f(val, shape_.getSize().y));
	}

	virtual void setSize(float size) override {
		shape_.setSize(Vector2f(0, size));
	}
};

