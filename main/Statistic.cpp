#include "Statistic.h"

Statistic::Statistic(Vector2f size, Vector2f position, int count) : size_(size), position_(position) {
	stats_.resize(count, Column({ 0, 0 }, { 0, 0 }, 0));
	pointer_ = 0;
	for (int i = 0; i < count; ++i) {
		stats_[i].setPosition(Vector2f(position_.x + ((double)size_.x / stats_.size() + 1) * i, position_.y + size_.y));
		stats_[i].setSize((double)size_.x / stats_.size());
	}
	max_ = 0;
	zero_.setFillColor(Color::Black);
	zero_.setString("0");
	zero_.setCharacterSize(20);
	zero_.setPosition(Vector2f(position.x - 30, position.y + size.y - 20));
	max_text_.setFillColor(Color::Black);
	max_text_.setCharacterSize(20);
	max_text_.setPosition(Vector2f(position.x - 30, position.y));
}

void Statistic::addValue(int value) {
	if (std::abs(value) > max_) {
		max_ = std::abs(value);
		max_text_.setString(std::to_string(max_));
		max_text_.setFont(font);
		int value = max_text_.getLocalBounds().width;
		max_text_.setPosition(Vector2f(position_.x - max_text_.getGlobalBounds().width - 10, position_.y));
		for (int i = 0; i < stats_.size(); ++i) {
			stats_[i].setValue(((double)stats_[i].getValue() / max_) * size_.y, stats_[i].getValue());
		}
	}
	if (pointer_ != stats_.size()) {
		stats_[pointer_++].setValue(((double)value / max_) * size_.y, value);
	} else {
		stats_.push_back(Column(Vector2f(0, ((double)value / max_) * size_.y), position_, value));
		for (int i = 0; i < stats_.size(); ++i) {
			stats_[i].setPosition(Vector2f(position_.x + ((double)size_.x / stats_.size() + 1) * i, position_.y + size_.y));
			stats_[i].setSize((double)size_.x / stats_.size());
		}
		++pointer_;
	}
}

void Statistic::draw(RenderWindow& window, Vector2i mouse) {
	for (int i = 0; i < stats_.size(); ++i) {
		stats_[i].draw(window, mouse);
	}
	zero_.setFont(font);
	max_text_.setFont(font);
	window.draw(zero_);
	window.draw(max_text_);
}
