

//Class cài đặt banh 
#ifndef _CBALL_H_
#define _CBALL_H_

#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include "Brick.h"
#include "Obstacle.h"
#include "cPaddle.h"
using namespace std;
#define PI 3.14159265 // định nghĩa số pi


class cBall
{
public:
	//vẽ đường định hướng banh
	vector<CircleShape> ballPath;

	// vị trí ban đầu của banh
	float originalX, originalY;

	// hình dạng banh
	CircleShape ballShape;

	//các vecto vận tốc theo chiều x và chiều y
	float xVelocity, yVelocity;
	
	//Số lượt chơi
	int Life;

	//Số lượt chơi mặc định
	int BasicLife = 3;

	//Constructor tùy biến
	//Input: giá trị tọa độ ban đầu của banh
	cBall(float startX, float startY);
	
	//hàm đặt giá trị banh về mặc định
	//Output: banh sẽ được đặt lại vị trí mặc định
	void reset();

	//hàm xử lý tương tác banh với hai cạnh biên trái, phải
	//Output: banh sẽ được xử lý tương tác
	void reboundSides();

	//hàm xử lý khi banh tương tác với người chơi
	//Ouptut: banh sẽ được xử lý tương tác
	void reboundPaddle();

	// hàm xử lý khi banh tương tác biên trên 
	//Output: banh sẽ được xử lý tương tác
	void reboundTop();

	//Hàm trả về tọa độ x
	//Output: trả về tọa độ x hiện thời của banh
	float getX();

	//Hàm trả về tọa độ y
	//Output: trả về tọa độ y hiện thời của banh
	float getY();

	//Hàm trả về hình dạng banh
	//Output: trả về hình dạng banh
	CircleShape getShape();

	//Hàm di chuyển banh
	//Input: thời gian giữa 2 khung hình, thông số cửa sổ hiện tại, người chơi, biến bool xác định đã bắt đầu trò chơi
	//Output: xử lý việc di chuyển của banh
	void Update(float DeltaTime,VideoMode mode, cPaddle& player1, bool& IsPlaying);



	//Hàm xác định vị trí rơi của banh (dùng cho người chơi máy tính)
	//Input:thông số cửa sổ hiện thời, hình dạng thông số người chơi
	//Output:giá trị điểm rơi được dự đoán
	float PredictCoordX(float modewidth, float modeheight, RectangleShape player);

	//Hàm kiểm tra va chạm với vật chắn
	//Input: vật chắn cần xác định, tốc độ giữa 2 khung hình
	//Output: biến bool xác định đã va chạm hoặc chưa va chạm
	bool ReboundBrick(Brick& brick, float deltaTime);

	//Hàm tương tác giữa banh và các vật cản
	//Input: Danh sách vật chắn, điểm số, hệ thống âm thanh, tốc độ giữa 2 khung hình
	//Output: biến bool xác định đã có tương tác với các loại vật cản
	bool BounceObstacle(Obstacle& obstacle, unsigned long int& Score, AudioManager& audiomanager, float DeltaTime);

	float IntersectionPoint(RectangleShape& paddle, float DeltaTime);

	bool ReboundPLayer(RectangleShape& shape, float deltatime);
	//Hàm vẽ đường di chuyển của banh
	//Input: Cửa sổ cần vẽ , biến kiểm tra có vẽ hay không
	//Output: hướng di chuyển của banh được vẽ
	void DrawPath(RenderWindow& window, bool checkHit);
};

#endif