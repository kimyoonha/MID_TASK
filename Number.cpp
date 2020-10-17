#include "Number.h"

using namespace std;
using namespace bangtal;

NumberPtr Number::create(
	const std::string& _image,
	bangtal::ScenePtr _scene,
	int _x, int _y,
	bool shown,
	int _number
) 
{
	auto object = NumberPtr(new Number(_image, _scene, _x, _y, shown, _number));
	Object::add(object);

	return object;
}

Number::Number(
	const std::string& _image,
	bangtal::ScenePtr _scene,
	int _x, int _y,
	bool shown,
	int _number
): Object(_image, _scene, _x, _y, shown), number(_number) {}

const int Number::getNumber() { return number; }

void Number::setNumber(int _number) { number = _number; }