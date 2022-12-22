#include <iostream>
#include <SFML/Graphics.hpp>
#include "Plane.h"

using namespace sf;

Font font;

int main() {
	font.loadFromFile("framd.ttf");
	Plane plane;
	plane.play();
}