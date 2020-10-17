#pragma once
#include <Object.h>


class Button : public bangtal::Object
{
	public:
		static bangtal::ObjectPtr create(
			const std::string& _image,
			bangtal::ScenePtr _scene = nullptr,
			int _x = 0, int _y = 0,
			bool shown = true
		);
	protected:
		Button(
			const std::string& _image,
			bangtal::ScenePtr _scene,
			int _x, int _y,
			bool shown
		);
};