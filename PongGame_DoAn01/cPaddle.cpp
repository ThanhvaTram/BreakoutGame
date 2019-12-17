#include "cPaddle.h"


//Constructor tùy biến
// nhận vào tọa độ ban đầu  X, tọa độ ban đâu Y, chế độ chơi
cPaddle::cPaddle(float startX, float startY, PlayMode type)
{
	//Cài đặt kích thước thanh trượt
	paddleShape.setSize(Vector2f(100.0f, 10.0f));

	//Cài đặt màu sắc cho thanh trượt
	paddleShape.setFillColor(Color::Black);

	//Cài đặt tọa độ mặc định theo giá trị đầu vào
	originalX = startX;
	originalY = startY;

	//Cài đặt trọng tâm cho thanh trượt
	paddleShape.setOrigin(paddleShape.getLocalBounds().width / 2.0f, paddleShape.getLocalBounds().height / 2.0f);

	//Cài đặt vị trí cho thanh trượt
	paddleShape.setPosition(originalX, originalY);

	//Cài đặt loại người chơi
	paddleType = type;
}




//Hàm trả về thông số,hình dạng người chơi
RectangleShape* cPaddle::getShape()
{
	return &paddleShape;
}


// Hàm di chuyển thanh trượt người chơi
void cPaddle::Update(float DeltaTime,float BallCoordX,VideoMode mode) // nhận vào tốc độ giữa 2 khung hình, tọa độ dự đoán, thông số cửa sổ
{
	// đặt tốc độ về 0
	paddleSpeed = 0.0f;
	if (paddleType == PlayMode::Computer) // kiểm tra chế độ chơi ( ở đây là TH người chơi máy tính)
	{

		//Kiểm tra tọa độ hiện hành của thanh trượt với điểm dự đoán
		if (abs(paddleShape.getPosition().x - BallCoordX) > 0.1f)
		{
			if (paddleShape.getPosition().x > BallCoordX) // nếu tọa độ hiện hành lớn hơn tọa độ X đự đoán
			{
				paddleSpeed = -150.0f; // set tốc độ về âm để cho thanh trượt di chuyển về phía bên trái
				// giới hạn trường hợp thanh trượt trượt ra khỏi màn chơi ( TH biên trái)
				if (paddleShape.getPosition().x + paddleSpeed * DeltaTime * 3 < paddleShape.getSize().x / 2.0f) 
				{
					//Đặt lại vị trí trước va chạm biên trái
					paddleShape.setPosition(paddleShape.getSize().x / 2.0f, paddleShape.getPosition().y); 

					//Đặt tốc độ lại về 0
					paddleSpeed = 0.0f;
				}
			}
			if (paddleShape.getPosition().x < BallCoordX) // nếu tọa độ hiện hành nhỏ hơn X dự đoán
			{
				paddleSpeed = 150.0f; // set tốc độ về dương để thanh trượt di chuyển về phía bên phải

				// giới hạn trường hợp thanh trượt trượt ra khỏi màn chơi (TH biên phải)
				if (paddleShape.getPosition().x + paddleShape.getSize().x / 2.0f + paddleSpeed * DeltaTime * 3 > mode.width)
				{
					// Đặt lại vị trí trước va cham biên trái
					paddleShape.setPosition(mode.width - paddleShape.getSize().x / 2.0f, paddleShape.getPosition().y);

					//Đặt lại tốc độ lại về 0
					paddleSpeed = 0.0f;
				}
			}
		}


	}


	else if (paddleType == PlayMode::Player1) // Kiểm tra chế độ chơi (TH người chơi con người)
	{
		if (Keyboard::isKeyPressed(Keyboard::A)) // Kiểm tra phím bấm nhận vào
		{
			paddleSpeed = -150.0f; // nếu phím bấm là A, thanh trượt sẽ di chuyển về phía bên trái

			// kiểm tra thanh trượt va chạm biên
			if (paddleShape.getPosition().x + paddleSpeed * DeltaTime * 3 < paddleShape.getSize().x / 2.0f)
			{

				// Đặt lại vị trí thanh trượt trước va  chạm
				paddleShape.setPosition(paddleShape.getSize().x / 2.0f, paddleShape.getPosition().y);

				//Đặt lại tốc độ về 0
				paddleSpeed = 0.0f;
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) // Kiểm tra phím bấm nhận vào
		{
			paddleSpeed = 150.0f; // nếu phím bấm là D, thanh trượt sẽ di chuyển về phía bên phải

			// kiểm tra thanh trượt va chạm biên
			if (paddleShape.getPosition().x + paddleShape.getSize().x / 2.0f + paddleSpeed * DeltaTime * 3 > mode.width)
			{
				//Đặt lại vị trí thanh trượt trước va chạm
				paddleShape.setPosition(mode.width - paddleShape.getSize().x / 2.0f, paddleShape.getPosition().y);

				// Đặt lại tốc độ về 0
				paddleSpeed = 0.0f;
			}
			
		}
	}
	// Di chuyển thanh trượt theo tốc độ và thời gian giữa 2 khung hình
	paddleShape.move(Vector2f(paddleSpeed * DeltaTime * 3, 0));
}
