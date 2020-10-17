#include "Button.h"
#include <iostream>

using namespace std;
using namespace bangtal;

ObjectPtr Button::create(
	const std::string& _image,
	bangtal::ScenePtr _scene,
	int _x, int _y,
	bool shown
)
{
	auto obj = ObjectPtr(new Button(_image, _scene, _x, _y, shown));
	Object::add(obj);

	return obj;
}

Button::Button(
	const std::string& _image,
	bangtal::ScenePtr _scene,
	int _x, int _y,
	bool shown
): Object(_image, _scene, _x, _y, shown) {}
