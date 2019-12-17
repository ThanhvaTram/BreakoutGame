#include"cDecoBall.h"

//ham khoi tao vi tri x,y va khoi tao qua cau co dang hinh vung 10 10 va gan vi tri hinh chu nhat cho x va y
cDecoBall::cDecoBall(float startX, float startY)
{
	position.x = startX;
	position.y = startY;

	cDecoBallhape.setSize(sf::Vector2f(10, 10));
	cDecoBallhape.setFillColor(Color::Red);
	cDecoBallhape.setPosition(position);
}

//ham tra ve vi tri cua mot hinh vuong
FloatRect cDecoBall::getPosition()
{
	return cDecoBallhape.getGlobalBounds();
}
// hamtra ve hinh dang cau mot qua bong
RectangleShape cDecoBall::getShape()
{
	return cDecoBallhape;
}

// ham lay toc do
float cDecoBall::getXVelocity()
{
	return xVelocity;
}

void cDecoBall::reboundSides()
{
	xVelocity = -xVelocity;
}
void cDecoBall::reboundSides2()
{
	yVelocity = -yVelocity;
}

void cDecoBall::reboundBatOrTop()
{

	position.y -= (yVelocity * 30);
	yVelocity = -yVelocity;
}

void cDecoBall::hitBottom()
{
	position.y = 500;
	position.x = 500;
}

void cDecoBall::update()
{
	// Update the ball position variables
	position.y += yVelocity;
	position.x += xVelocity;

	// Move the ball and the bat
	cDecoBallhape.setPosition(position);
}

bool cDecoBall::DieuKien(float windowWidth, float windowHeight, Text hudPongGame)
{
	bool temp = 0;
	if (this->getPosition().left < 0 || this->getPosition().left + 10 > windowWidth)
	{
		this->reboundSides();
		temp = 1;
	}
	if (this->getPosition().top < 0 || this->getPosition().top + 10 > windowHeight)
	{
		this->reboundSides2();
		temp = 1;

	}
	if (this->getPosition().intersects(hudPongGame.getGlobalBounds())) {
		this->reboundBatOrTop();
		temp = 1;
	}
	return temp;
}

cDecoBall::cDecoBall()
{
}


cDecoBall::~cDecoBall()
{
}