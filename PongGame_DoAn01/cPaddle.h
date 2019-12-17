

//Class người chơi
#ifndef _CPADDLE_H_
#define _CPADDLE_H_

#include <SFML/Graphics.hpp>
using namespace sf;
enum class PlayMode 
{
	Player1,Computer
};
class cPaddle
{
public:
	//Tọa độ ban đầu của người chơi
	float originalX, originalY;
	
	//Tốc độ di chuyển của người chơi
	float paddleSpeed = 1.5f;

	//Thông số, hình dạng người chơi
	RectangleShape paddleShape;

	//Chế độ chơi 
	PlayMode paddleType;

	//Constructor tùy biến
	//Input: tọa độ X Y mặc định, chế độ chơi
	cPaddle(float startX, float startY, PlayMode type);

	


	//Hàm lấy thông số và hình dạng thanh trượt
	//Output: thông số và hình dạng thanh trượt
	RectangleShape* getShape();

	//Hàm di chuyển thanh trượt người chơi
	//Input: thời gian giữa 2 khung hình, tọa độ banh dự đoán( dùng cho TH người chơi máy tính), thông số cửa sổ đang mở
	//Output: thanh trượt di chuyển theo hướng xác định
	void Update(float DeltaTime, float BallCoordX, VideoMode mode);
};

#endif // !__CPADDLE_H__