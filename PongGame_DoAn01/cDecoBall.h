#ifndef __CDECOBALL_H__
#define __CDECOBALL_H__
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace  sf;
using namespace  std;

class cDecoBall
{
private:
	Vector2f position;

	RectangleShape cDecoBallhape;

	float xVelocity = .8f;
	float yVelocity = .8f;

public:

	cDecoBall(float startX, float startY);

	FloatRect getPosition();

	RectangleShape getShape();

	float getXVelocity();

	void reboundSides();

	void reboundSides2();

	void reboundBatOrTop();

	void hitBottom();

	void update();

	bool DieuKien(float windowWidth, float windowHeight, Text HudPongGame);

	cDecoBall();
	~cDecoBall();
};
#endif // !__CDECOBALL_H__
