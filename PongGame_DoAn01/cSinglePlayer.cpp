#include "cSinglePlayer.h"

cSinglePlayer::cSinglePlayer(int w, int h)
{
	width = w; height = h;
	score1 = 0;
	ifstream infileHighScore;
	infileHighScore.open("highScore.txt");
	infileHighScore >> highScore;
	infileHighScore.close();
	ball = new cBall(static_cast<float>(w - 5),static_cast<float>( h - 5));
	player1 = new cPaddle(static_cast<float> (w) , static_cast<float> (h), PlayMode::Player1);
	quit = false;
}

cSinglePlayer::~cSinglePlayer()
{
	delete ball, player1;
}

bool cSinglePlayer::getQuitState()
{
	return quit;
}

void cSinglePlayer::draw(RenderWindow& window)
{
	RectangleShape border(Vector2f(800 - 6, 500 - 6));
	border.setFillColor(Color::White);
	border.setOutlineThickness(3);
	border.setOutlineColor(Color::Black);
	border.setPosition(3, 3);

	Font font;
	font.loadFromFile("Font/Font2.ttf");

	Text hud;
	hud.setFont(font);
	hud.setFillColor(Color::Black);
	hud.setCharacterSize(30);

	std::stringstream ss1;
	ss1 << "High Score: " << highScore << endl;
	ss1 << "Score: " << score1;
	hud.setPosition(20, 20);
	hud.setString(ss1.str());

	window.draw(border);
	window.draw(hud);
	window.draw(ball->getShape());
	window.draw(player1->paddleShape);
}



bool cSinglePlayer::logic()
{
	// ball hit top
	bool Check = 0;
	if (ball->getY() <= 0) {
		ball->reboundTop();
		score1++;
		Check = 1;
	
	}
	// ball hit bottom
	if (ball->getY() + 10 >= height) {
		quit = true;
	}
	// ball hit sides
	if ((ball->getX() <= 0) || ball->getX() >= width - 10) 
	{
		ball->reboundSides();
		Check = 1;
	}
	// ball hit paddle 1
	if ((ball->getX() + 10 >= player1->getX()) && (ball->getX() <= player1->getX() + 100) &&
		(ball->getY() + 10 >= player1->getY())) {
		// ball hit right side or left side of paddle 1
		if ((ball->getX() + 10 >= player1->getX() || ball->getX() <= player1->getX() + 100) && ball->getY() + 10 > player1->getY() + 1) {
			ball->reboundSides();
			ball->reboundPaddle();
		}
		ball->reboundPaddle();
		Check = 1;

	}
	// paddle 1 hit left side
	if (player1->getX() <= 0) {
		player1->hitLeftSide();
	}
	// paddle 1 hit right side
	if (player1->getX() >= width - 100) {
		player1->hitRightSide();
	}
	return Check;
}

void cSinglePlayer::update(float DeltaTime, VideoMode mode)
{
	RectangleShape player2;
	//ball->Update(DeltaTime,mode,player1->paddleShape,player2);
	player1->Update(DeltaTime, 0.0f, mode);
}

int cSinglePlayer::getMaxScore()
{
	if (score1 > highScore) {
		highScore = score1;
	}
	return highScore;
}

void cSinglePlayer::reset()
{
	if (highScore < score1) {
		highScore = score1;
	}
	ofstream outputHighScore;
	outputHighScore.open("highScore.txt",ios::trunc);
	outputHighScore << highScore;
	outputHighScore.close();

	score1 = 0;
	ball->reset();
	player1->reset();
	quit = false;
}

int cSinglePlayer::GetScore()
{
	return score1;
}
