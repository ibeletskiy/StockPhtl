#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Vertical.h"
#include "Button.h"

class Statistic {
public:
	Statistic() = default;
	Statistic(Vector2f size, Vector2f position, int count = 0) : size_(size), position_(position) {
		stats_.resize(count);
		pointer_ = 0;
		for (int i = 0; i < count; ++i) {
			stats_[i].setSize((double)size_.y / stats_.size());
			stats_[i].setPosition(Vector2f(position_.x + ((double)size_.y / stats_.size()) * i, position_.y));
		}
		zero_.setString("0");
		zero_.setCharacterSize(20);
		zero_.setPosition(Vector2f(position.x - 20, position.y + size.y - 10 ));
		max_text_.setCharacterSize(20);
		max_text_.setPosition(Vector2f(position.x - 20, position.y + 10 ));
	}
	
	void addValue(int value) {
		if (value > max_) {
			max_ = value;
			max_text_.setString(std::to_string(max_));
			for (int i = 0; i < stats_.size(); ++i) {
				stats_[i].setValue(((double)stats_[i].getValue() / max_) * size_.y);
			}
		}
		if (pointer_ != stats_.size()) {
			stats_[pointer_++].setValue(((double)value / max_) * size_.y);
		} else {
			stats_.push_back(Vertical({ 0, 0 }, position_, value));
			for (int i = 0; i < stats_.size(); ++i) {
				stats_[i].setSize((double)size_.y / stats_.size());
				stats_[i].setPosition(Vector2f(position_.x + ((double)size_.y / stats_.size()) * i, position_.y));
			}
		}
	}

	void draw(RenderWindow& window, Vector2i mouse) {
		for (int i = 0; i < stats_.size(); ++i) {
			stats_[i].draw(window, mouse);
		}
		zero_.setFont(font);
		max_text_.setFont(font);
		window.draw(zero_);
		window.draw(max_text_);
	}

private:
	std::vector<Vertical> stats_;
	Vector2f size_, position_;
	Text zero_, max_text_;
	int max_;
	int pointer_;
};

// хранит и рисует статистику