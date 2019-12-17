
// class Vật chắn
#ifndef BRICK_H_
#define BRICK_H_
#include <SFML/Graphics.hpp>
#include <math.h>
#include <SFML/Audio.hpp>
#include "AudioManager.h"
#include <iostream>
using namespace std;

// Khai báo các loại vật chắn khác nhau 
enum class BrickType 
{
	Normal, // vật chắn bình thường 
	Multiply, // vật chắn nhân đôi điểm
	Barrier, // vật chắn không thể bị phá hủy
	Bomb,// vật chắn gây nổ
	IncreaseLife, // vật chắn tăng lượt chơi
	DrawPath //vật chắn vẽ đường đi 
};

class Brick
{
public:
	// Hình dạng vật chắn
	RectangleShape mShape;

	// Loại vật chắn
	BrickType mType;

	//Biến bool xác định vật chắn có thể được hiện ra hay không
	bool mVisible;
	
	//Vị trí của vật chắn trên màn chơi
	int ColPos;
	int RowPos;

	//Constructor mặc định
	Brick();

	//Constructor tùy biến
	//Input: chiều dài, chiều rộng 
	Brick(float width, float height);



	// Hàm kiểm tra vật chắn đã bị va chạm
	//Output: biến hiện thị <mVisible> gán về false
	void HitBrick();

	// Hàm cài đặt vị trí hiển thị cho vật chắn
	//Input: vị trí theo trục x,vị trí theo trục y
	//Output: vị trí vật chắn sẽ được đặt theo tọa độ xy nhập vào
	void SetPosition(float x, float y);
	

};

#endif // !BRICK_H_

