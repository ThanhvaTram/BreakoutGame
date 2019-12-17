#include "Brick.h"

// Constructor mặc định
Brick::Brick() 
{
	
	mShape.setSize(Vector2f(30.0f, 30.0f)); // cài đặt kích thước cho vật chắn
	mShape.setOrigin(Vector2f(0.0f, 0.0f)); // cài đặt vị trí trọng tâm cho vật chắn

	mType = BrickType::Normal; // cài đặt loại vật chắn
	mVisible = true; // gán biến hiển thị về true
	
	// Gán vị trí mặc định về 0 0
	this->ColPos = 0; 
	this->RowPos = 0; 
}

// Constructor tùy biến nhận vào giá trị chiều dài chiều rộng
Brick::Brick(float width, float height) 
{

	mShape.setSize(Vector2f(width, height)); // cài đặt kích thước cho vật chắn dựa trên giá trị nhập vào
	mShape.setOrigin(Vector2f(0.0f, 0.0f)); // cài đặt trọng tâm cho vật chắn
	mType = BrickType::Normal; // cài đặt loại vật chắn
	
	// Gán vị trí mặc định về 0 0
	this->ColPos = 0;
	this->RowPos = 0;

	//Gán biến hiển thị về true
	mVisible = true;
}


// Hàm kiểm tra va chạm
void Brick::HitBrick()
{
	mVisible = false; // đưa biến <mVisible> về là false
}

// Hàm cài đặt vị trí cho vật chắn
void Brick::SetPosition(float x, float y) // nhận vào tọa độ x y
{
	mShape.setPosition(Vector2f(x, y)); // cài đặt vật chắn theo tọa độ nhận vào
}



