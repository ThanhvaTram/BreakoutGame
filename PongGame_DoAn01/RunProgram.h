#pragma once

#include"cBall.h"
#include"cPaddle.h"
#include"menu.h"
#include"cMultiPlayer.h"
#include"cSinglePlayer.h"
#include"cDecoBall.h"
#include"Obstacle.h"

#include "AudioManager.h"
#include "TextureManager.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
using namespace sf;
class GAME
{
private:
	Menu menu;

	

	AudioManager audiomanager;
	TextureManager texturemanager;
	unsigned long int HighScore;
	unsigned long int Score;
	float DeltaTime;
	Font DisplayFont;
	GameLevel LevelSelected;
	bool LoadLevel;
	PlayMode playmode;


public:
	VideoMode mode;
	RenderWindow window;
	GameState gamestate;
	GAME();
	~GAME();
	int windowmode;

	//Hàm đọc dữ liệu đã lưu
	//Output: true nếu đọc thành công, false nếu đọc bị lỗi
	bool LoadGameData();

	//Hàm lưu dữ liệu xuống file
	//Output: true nếu lưu thành công, false nếu thất bại
	bool SaveGameData();

	//Hàm chạy Menu chính
	//Output: chạy Menu chính
	void RunMainMenu();

	//Hàm chạy game Breakout
	//Output: chạy game Breakout
	void RunGameBreakout();

	//Hàm chạy Menu điểm số cao nhất
	//Output: chạy Menu điểm số cao nhất 
	void RunHighScoreBreakout();

	//Hàm chạy Menu tạm dừng
	//Output: chạy Menu Tạm dừng
	void RunPauseMenuBreakout();

	//Hàm chạy Menu thắng/thua
	//Output: chạy Menu thắng thua
	void RunLosingPanelBreakout();

	//Hàm chạy Menu chọn Level
	//Output: chạy Menu chọn Level
	void RunMenuSelectLevel();

	//Hàm tải màn chơi
	//Input: trạng thái game kế tiếp, trạng thái game hiện tại
	//Output: tải màn chơi
	void RunLoading(GameState nextGameState,GameState CurrentGameState);

	//Hàm kết thúc tải màn chơi
	//Input: trạng thái game kết tiếp, trạng thái game hiện tại
	//Output: kết thúc tải màn chơi
	void RunOpenLoading(GameState nextGameState,GameState CurrentGameState);
	
	//Hàm chạy Menu cài đặt
	//Output: chạy Menu cài đặt
	void RunMenuOption();

	//Hàm chạy Menu hướng dẫn chơi
	//Output: chạy Menu hướng dẫn chơi
	void RunMenuInstructionBreakout();
	
	//Hàm chạy Menu chọn chế độ chơi
	//Output: chạy Menu chọn chế độ chơi
	void RunMenuPlayMode();

	//Hàm vẽ tải màn chơi
	//Input: trạng thái game tiếp theo, trạng thái game hiện tải
	//Output: vẽ trạng thái game cần thiết 
	void DrawIntroMenu(GameState toDraw,GameState CurrentGameState);


};
