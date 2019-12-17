#include "cMultiPlayer.h"

cMultiPlayer::cMultiPlayer(int w, int h)
{
	width = w; height = h;
	score1 = score2 = 0;
	ball = new cBall(w / 2.0f - 5, h / 2.0f - 5);
	player1 = new cPaddle(w / 2.0f - 50, h - 20.0f,PlayMode::Player1);
	player2 = new cPaddle(w / 2.0f - 50, 20, PlayMode::Player2);
	quit = false;
}

cMultiPlayer::~cMultiPlayer()
{
	delete ball, player1, player2;
}

bool cMultiPlayer::getQuitState()
{
	return quit;
}

void cMultiPlayer::draw(RenderWindow& window)
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
	ss1 << "Score player 1: " << score1;
	hud.setPosition(20, height / 2.0f + 20);
	hud.setString(ss1.str());

	Text hud2;
	hud2.setFont(font);
	hud2.setFillColor(Color::Black);
	hud2.setCharacterSize(30);

	std::stringstream ss2;
	ss2 << "Score player 2: " << score2;

	hud2.setPosition(width - 20.0f, height / 2.0f - 20);
	hud2.setString(ss2.str());
	hud2.setOrigin(hud2.getGlobalBounds().width, hud2.getGlobalBounds().height / 2);



	window.draw(border);
	window.draw(hud);
	window.draw(hud2);
	window.draw(ball->getShape());
	window.draw(player1->paddleShape);
	window.draw(player2->paddleShape);
}

void cMultiPlayer::input(RenderWindow& window,float DeltaTime)
{
	
}



int cMultiPlayer::logic()
{
	int temp = 0; // kiem tra va cham de phat am thanh
					// 0 ko co gi, 1 sound hit, 2 sound lose
	// ball hit top
	if (ball->getY() <= 0) {
		ball->reset();
		score1++;
		temp = 2;
		//ballDirection = (eDir)((rand() % 4) + 1);
	}
	// ball hit bottom
	if (ball->getY() + 10 >= height) {
		ball->reset();
		score2++;
		temp = 2;
	}
	// ball hit sides
	if (ball->getX() <= 0 || ball->getX() >= width - 10) {
		ball->reboundSides();
		temp = 1;
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
		temp = 1;
	}
	// ball hit paddle 2
	if ((ball->getX() + 10 >= player2->getX()) && (ball->getX() <= player2->getX() + 100) &&
		(ball->getY() <= player2->getY() + 5)) {
		// ball hit right side or left side of paddle 2
		if ((ball->getX() + 10 >= player2->getX() || ball->getX() <= player2->getX() + 100) && ball->getY() < player2->getY() + 3) {
			ball->reboundSides();
			ball->reboundPaddle();
		}
		ball->reboundPaddle();
		temp = 1;
	}

	// paddle 1 hit left side then stop
	if (player1->getX() <= 0) {
		player1->hitLeftSide();
	}
	// paddle 1 hit right side then stop
	if (player1->getX() >= width - 100) {
		player1->hitRightSide();
	}
	// paddle 2 hit left side then stop
	if (player2->getX() <= 0) {
		player2->hitLeftSide();
	}
	// paddle 2 hit right side then stop
	if (player2->getX() >= width - 100) {
		player2->hitRightSide();
	}
	// win condition
	if (score1 >= 3|| score2 >= 3) {
		quit = true;
	}
	return temp;
}

void cMultiPlayer::update(float DeltaTime,VideoMode mode)
{
	//ball->Update(DeltaTime,mode,player1->paddleShape,player2->paddleShape);
	player1->Update(DeltaTime,0.0f,mode);
	player2->Update(DeltaTime,0.0f,mode);

}

void cMultiPlayer::reset()
{
	score1 = score2 = 0;
	ball->reset();
	player1->reset();
	player2->reset();
	quit = false;
}

int cMultiPlayer::getMaxScore()
{
	if (score1 > score2) {
		return score1;
	}
	else return score2;
}

int cMultiPlayer::GetScore1()
{
	return score1;
}

int cMultiPlayer::GetScore2()
{
	return score2;
}
