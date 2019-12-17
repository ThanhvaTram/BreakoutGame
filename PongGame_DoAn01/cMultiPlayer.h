#ifndef _CMULTIPLAYER_H_
#define _CMULTIPLAYER_H_

#include "cBall.h"
#include "cPaddle.h"
#include <sstream>
#include <cstdlib>

class cMultiPlayer
{
private:
	bool quit;
	int width, height;
	int score1, score2;
	cBall* ball;
	cPaddle* player1;
	cPaddle* player2;
public:
	cMultiPlayer(int w, int h);
	~cMultiPlayer();
	bool getQuitState();
	void draw(RenderWindow& window);
	void input(RenderWindow& window,float DeltaTime);
	int logic();
	void update(float DeltaTime,VideoMode mode);
	void reset();
	int getMaxScore();
	int GetScore1();
	int GetScore2();
};

#endif // !__CMULTIPLAYER_H__