#pragma once
#include "Column.h"

class Horizontal : public Column {
public:
	Horizontal(Vector2f size, Vector2f pos, int value = 0) : Column(size, pos, value) {}
	virtual void setPosition(Vector2f pos) override {
		shape_.setPosition(pos);
	}

	virtual void setValue(double val) override {
		shape_.setSize({ val, shape_.getSize().y });
	}

	virtual void setSize(double size) override {
		shape_.setSize({ 0, size });
	}
};

