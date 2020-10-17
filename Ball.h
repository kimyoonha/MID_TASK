#pragma once
#include <Object.h>
#include <iostream>

class Ball;
typedef std::shared_ptr<Ball> BallPtr;


class Ball : public bangtal::Object
{
	public:
		static BallPtr create(
			const std::string& _image, 
			const std::string& _color,
			bangtal::ScenePtr _locatedScene = nullptr, 
			int _x = 0, int _y = 0, 
			bool _shown = true
			);
	protected:
		Ball(
			const std::string& _image,
			const std::string& _color,
			bangtal::ScenePtr _locatedScene,
			int _x, int _y,
			bool _shown
		);

	public:
		virtual std::string getColor();
		virtual bool isEmpty();
		virtual bool isTop();
		virtual void setColor(const std::string& _color);
		virtual void setEmpty(bool _empty);
		virtual void setTop(bool _top);
	protected:
		std::string color;
		bool empty;
		bool top;
};
