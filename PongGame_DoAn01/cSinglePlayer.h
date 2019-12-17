#ifndef _CSINGLEPLAYER_H_
#define _CSINGLEPLAYER_H_

#include "cBall.h"
#include "cPaddle.h"
#include <sstream>
#include <cstdlib>
#include <fstream>

class cSinglePlayer
{
private:
	bool quit;
	int width, height;
	int score1;
	int highScore;
	cBall *ball;
	cPaddle *player1;
public:
	cSinglePlayer(int w, int h);
	~cSinglePlayer();
	bool getQuitState();
	void draw(RenderWindow& window);
	bool logic();
	void update(float DeltaTime, VideoMode mode);
	int getMaxScore();
	void reset();
	int GetScore();
};

#endif // !__CSINGLEPLAYER_H__
