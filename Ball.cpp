#include "Ball.h"

using namespace std;
using namespace bangtal;

BallPtr Ball::create(
	const std::string& _image,
	const std::string& _color,
	bangtal::ScenePtr _locatedScene,
	int _x, int _y,
	bool _shown
)
{
	auto object = BallPtr(new Ball(_image, _color, _locatedScene, _x, _y, _shown));
	Object::add(object);

	return object;
}

Ball::Ball(
	const std::string& _image,
	const std::string& _color,
	bangtal::ScenePtr _locatedScene,
	int _x, int _y,
	bool _shown
) : Object(_image, _locatedScene, _x, _y, _shown), color(_color) 
{
	empty = false;
	top = false;
}

string Ball::getColor() {
	return color;
}

bool Ball::isEmpty() {
	return empty;
}

bool Ball::isTop() {
	return top;
}

void Ball::setColor(const std::string& _color) {
	color = _color;
}

void Ball::setEmpty(bool _empty) {
	empty = _empty;
}

void Ball::setTop(bool _top) {
	top = _top;
}

