#pragma once
#include <Object.h>

class Number;
typedef std::shared_ptr<Number> NumberPtr;

class Number : public bangtal::Object
{
public:
	static NumberPtr create(
		const std::string& _image,
		bangtal::ScenePtr _scene = nullptr,
		int _x = 0, int _y = 0,
		bool shown = true,
		int _number = 0
	);
	virtual const int getNumber();
	virtual void setNumber(int _number);
protected:
	Number(
		const std::string& _image,
		bangtal::ScenePtr _scene,
		int _x, int _y,
		bool shown,
		int _number
	);
	int number;
};