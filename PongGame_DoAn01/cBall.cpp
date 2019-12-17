#include "cBall.h"


//Constructor tùy biến
cBall::cBall(float startX, float startY) // tọa độ x y nhận vào
{


	Life = 3; // Số lược chơi mặc định
	ballShape.setRadius(7.0f); // cài đặt kích thước banh

	// cài đặt tọa độ ban đầu của banh
	originalX = startX; 
	originalY = startY;
	
	// cài đặt vận tốc ban đầu 
	xVelocity = 0;
	yVelocity = 0;

	// cài đặt các thông số tọa độ,trọng tâm và độ mịn của banh
	ballShape.setPosition(startX, startY);
	ballShape.setPointCount(360);
	ballShape.setOrigin(ballShape.getRadius(), ballShape.getRadius());
	
	
	for (int i = 0; i < 30; i++)
	{
		CircleShape path;
		path.setRadius(2.0f);
		path.setFillColor(Color::Green);
		path.setOrigin(Vector2f(path.getRadius(), path.getRadius()));
		path.setPosition(Vector2f(10.0f, 20.0f * i));
		ballPath.push_back(path);
	}
}


void cBall::reset()
{
	const float range = 0.9f - 0.5f;
	ballShape.setPosition(originalX, originalY);
	xVelocity = range * ((((float)rand()) / (float)RAND_MAX)) + 0.5f;
	//xVelocity = xVelocity * static_cast<float> (pow(-1, rand() % 2));
	cout << xVelocity << endl;
	yVelocity = sqrt(1.2f * 1.2f - xVelocity * xVelocity);
	
}

//hàm xử lý tương tác banh với hai cạnh biên trái, phải
void cBall::reboundSides()
{
	//xử lý khi bóng chạm 2 biên
	xVelocity = -xVelocity;
}


//hàm xử lý khi banh tương tác với người chơi
void cBall::reboundPaddle()
{
	//xử lý khi banh chạm người chơi
		xVelocity = 1.1f * xVelocity;
		yVelocity = -1.1f * yVelocity;
}
// hàm xử lý khi banh tương tác biên trên 
void cBall::reboundTop()
{
	//xử lý khi banh tương tác biên trên
	yVelocity = -yVelocity;
}



// Hàm lấy giá trị tọa độ x của banh
float cBall::getX()
{
	// lấy giá trị tọa độ x của banh
	return ballShape.getPosition().x;
}

// Hàm lấy giá trị tọa độ y của banh
float cBall::getY()
{
	// lấy giá trị tọa độ y của banh 
	return ballShape.getPosition().y;
}


// Hàm lấy hình dạng banh
CircleShape cBall::getShape()
{
	//lấy hình dạng banh
	return ballShape;
}

//Hàm di chuyển banh
void cBall::Update(float DeltaTime, VideoMode mode, cPaddle& player1, bool& IsPlaying)
{

	if (ballShape.getPosition().x + ballShape.getGlobalBounds().width / 2.0f > mode.width) // Kiểm tra banh có chạm biên phải hay không
	{
		reboundSides();// xử lý tương tác banh với hai biên
		ballShape.setPosition(mode.width - ballShape.getRadius() - 0.1f, ballShape.getPosition().y); // đặt lại vị trí banh trước va chạm
	}
	if (ballShape.getPosition().x - ballShape.getGlobalBounds().width / 2.0f < 0) // Kiểm tra banh có chạm biên trái hay không
	{
		reboundSides(); // xử lý tương tác banh với hai bên 
		ballShape.setPosition(ballShape.getRadius() + 0.1f, ballShape.getPosition().y); // đặt lại vị trí banh trước va chạm
	}
	if (ballShape.getPosition().y - ballShape.getRadius() < 32.0f) // kiểm tra banh có chạm biên trên hay không
	{
		reboundTop(); // xử lý tương tác banh với biên trên
		ballShape.setPosition(ballShape.getPosition().x, ballShape.getRadius() + 32.1f); // đặt lại vị trí trước va chạm
	}
	if (ReboundPLayer(*(player1.getShape()), DeltaTime))// kiểm tra banh va chạm với thanh trượt người chơi
	{
		//cout << IntersectionPoint(player1.paddleShape, DeltaTime) << endl;
		// đặt banh vị trí trước va chạm
		// xử lý tương tác giữa banh với người chơi 
		reboundPaddle();
		//xVelocity = 1.1 * xVelocity;
		//yVelocity = 1.1 * yVelocity;
	}

	if (ballShape.getPosition().y + ballShape.getRadius() > mode.height) // kiểm tra banh có rơi ra khỏi sân chơi không
	{
		//cout << ballShape.getPosition().y << endl;
		this->Life--; // giảm lượt chơi đi 1
		IsPlaying = false; // đặt biến đang chơi về false
		if (Life >= 0) // kiểm tra xem còn lượt chơi hay không 
		{
			// đặt banh về vị trí mặc định
			ballShape.setPosition(Vector2f(this->originalX, this->originalY));
			// đặt lại vận tốc của banh
			xVelocity = 0.0f;
			yVelocity = 0.0f;

			//đặt vị trí người chơi về vị trí mặc định
			player1.paddleShape.setPosition(player1.originalX, player1.originalY);
			
		}

	}

	//Di chuyển banh theo thời gian giữa 2 khung hình và vận tộc  x y
	ballShape.move(xVelocity * DeltaTime * 60.0f, yVelocity * DeltaTime * 60.0f);


}

void cBall::DrawPath(RenderWindow& window, bool checkHit)
{
	//kiểm tra bóng đã đụng brick vẽ đường đi chưa
	if (checkHit == true)
	{
		
		
		// Lưu dấu của vận tộc theo chiều X
	

		//trường hợp bóng đi lên
		if (yVelocity < 0)
		{
			// Quét 30 điểm Path đường đi
			for (int i = ballPath.size()-1; i >= 0; i--)
			{
				// Không vẽ lại những điểm đã qua trên thanh dự đoán đường đi
				if (ballPath[i].getPosition().y < ballShape.getPosition().y)
				{
					// Cài đặt tọa độ hiển thị về 0
					float xStep = 0.0f;
					//Cài đặt cho điểm hiển thị đầu tiên
					// Sử dụng công thức hình học để tính tính vị trí x hiển thị dựa trên cotan góc x y và tọa độ x của banh
					xStep = ballShape.getPosition().x - (ballShape.getPosition().y - ballPath[i].getPosition().y) * xVelocity / yVelocity;
					
					// Xét trường tọa độ tính được đụng vô biên trái
					if (xStep > (500.0f - ballShape.getRadius()))
					{
						// đặt lại vị trí trước va chạm
						xStep = 2.0f * (500.0f - ballShape.getRadius()) - xStep;
					
					}
					// Xét trường hợp tọa độ tính được đụng vô biên phải
					if (xStep < ballShape.getRadius())
					{

						// đặt lại vị trí trước va chạm 
						xStep = 2.0f * ballShape.getRadius() - xStep;
						
					}
					// đặt vị trí lại tọa độ từng điểm đường đi
					ballPath[i].setPosition(xStep, ballPath[i].getPosition().y);
					// vẽ đường đi
					window.draw(ballPath[i]);
				}
			}
		}
		
		// trường hợp bóng đi xuống
		else if (yVelocity>0)
		{
			for (int i = 0; i < ballPath.size(); i++)
			{
				// Không vẽ lại những điểm đã qua trên thanh dự đoán đường đi
				if (ballPath[i].getPosition().y > ballShape.getPosition().y)
				{
					// cài đặt tọa độ ban đầu
					float xStep = 0.0f;

					// tính toán dựa trên hình học
					xStep = ballShape.getPosition().x - (ballShape.getPosition().y - ballPath[i].getPosition().y) * (xVelocity / yVelocity);

					// Xét các trường hợp đụng biên hai bên
					if (xStep > (500.0f - ballShape.getRadius()))
					{
						xStep = 2.0f * (500.0f - ballShape.getRadius()) - xStep;
					}
					if (xStep < ballShape.getRadius())
					{
						xStep = 2.0f * ballShape.getRadius() - xStep;
					}
					// Đặt vị trí của các điểm dự đoán dựa trên x
					ballPath[i].setPosition(xStep, ballPath[i].getPosition().y);

					//Vẽ đường dự đoán
					window.draw(ballPath[i]);

				}
			}
		}

	}
}


// Hàm dự đoán điểm rơi của banh 
float cBall::PredictCoordX(float modewidth, float modeheight, RectangleShape player)  // nhận vào kích thước cửa sổ màn chơi, thông số thanh trượt người chơi
{
	//Tọa độ banh rơi cần dự đoán ( đặt ban đầu là 0)
	float distance = 0.0f;

	
	float d = 0.0f;

	//Bán kính của banh
	float radius = ballShape.getRadius();

	//Cài đặt thông số modewidth
	modewidth = modewidth - radius;
	d = player.getPosition().y - player.getSize().y / 2.0f - ballShape.getPosition().y - radius;

	//Tính khoảng cách dựa trên tan 
	distance = ballShape.getPosition().x + d * xVelocity / abs(yVelocity); // tính được tan góc giữa vector x và vector y

	//xét TH tọa độ nhỏ hơn biên trái
	if (distance < radius)
	{
		// lấy trị tuyệt đối tọa độ
		distance = abs(distance);


		int phanNguyen = static_cast<int> (distance / modewidth); // số lần đụng tường của banh
		//Tính lại tọa độ
		distance = distance - modewidth * phanNguyen;
		// Tính số lần đụng tường chẵn hay lẻ
		if (phanNguyen % 2 != 0) {
			distance = modewidth - distance;
		}
	}
	//Xét TH tọa độ lớn hơn biên phải
	if (distance > modewidth + radius)
	{
		//Tính lại tọa độ
		distance = distance - modewidth - ballShape.getRadius();
		int phanNguyen = static_cast<int> (distance / modewidth);
		distance = distance - modewidth * phanNguyen;

		// Tính số lần đụng tường chẵn hay lẻ
		if (phanNguyen % 2 == 0) {
			distance = modewidth - distance;
		}

	}
	return distance;

}
//Hàm xác định xem có va chạm vật chắn hay không 
bool cBall::ReboundBrick(Brick& brick, float deltaTime)
{
	bool check = false;
	if (brick.mVisible == true) // kiểm tra vật chắn có được hiển thị hay không
	{
		if (xVelocity > 0) // kiểm tra va ch
		{
			//Kiểm tra va chạm 
			if ((ballShape.getPosition().x + ballShape.getRadius() + xVelocity*deltaTime*60.0f > brick.mShape.getPosition().x
				&& ballShape.getPosition().x + ballShape.getRadius() + xVelocity*deltaTime*60.0f < brick.mShape.getPosition().x + brick.mShape.getGlobalBounds().width)
				&& ((ballShape.getPosition().y - ballShape.getRadius() > brick.mShape.getPosition().y
					&& ballShape.getPosition().y - ballShape.getRadius() < brick.mShape.getPosition().y + brick.mShape.getGlobalBounds().height)
					|| (ballShape.getPosition().y + ballShape.getRadius() > brick.mShape.getPosition().y
						&& ballShape.getPosition().y + ballShape.getRadius() < brick.mShape.getPosition().y + brick.mShape.getGlobalBounds().height)))
			{
				xVelocity = -xVelocity; // đổi chiều vận tộc x
				check = true; // đặt biến đã va chạm về true
			}
		}
		// kiểm tra bóng bay theo chiều x âm
		else {
			// Kiểm tra va chạm
			if ((ballShape.getPosition().x - ballShape.getRadius() + xVelocity*deltaTime*60.0f > brick.mShape.getPosition().x
				&& ballShape.getPosition().x - ballShape.getRadius() + xVelocity * deltaTime * 60.0f < brick.mShape.getPosition().x + brick.mShape.getGlobalBounds().width)
				&& ((ballShape.getPosition().y - ballShape.getRadius() > brick.mShape.getPosition().y
					&& ballShape.getPosition().y - ballShape.getRadius() < brick.mShape.getPosition().y + brick.mShape.getGlobalBounds().height)
					|| (ballShape.getPosition().y + ballShape.getRadius() > brick.mShape.getPosition().y
						&& ballShape.getPosition().y + ballShape.getRadius() < brick.mShape.getPosition().y + brick.mShape.getGlobalBounds().height)))
			{
				xVelocity = -xVelocity; // đổi chiều vận tốc x
				check = true; // đặt biến đã va chạm về true
			}
		}


		if (yVelocity > 0) // Kiểm tra bóng bay theo chiều y dương
		{
			//Kiểm tra va chạm
			if ((ballShape.getPosition().y + ballShape.getRadius() + yVelocity*deltaTime*60.0f > brick.mShape.getPosition().y
				&& ballShape.getPosition().y + ballShape.getRadius() + yVelocity*deltaTime*60.0f < brick.mShape.getPosition().y + brick.mShape.getGlobalBounds().height)
				&& ((ballShape.getPosition().x - ballShape.getRadius() > brick.mShape.getPosition().x
					&& ballShape.getPosition().x - ballShape.getRadius() < brick.mShape.getPosition().x + brick.mShape.getGlobalBounds().width)
					|| (ballShape.getPosition().x + ballShape.getRadius() > brick.mShape.getPosition().x
						&& ballShape.getPosition().x + ballShape.getRadius() < brick.mShape.getPosition().x + brick.mShape.getGlobalBounds().width)))
			{
				yVelocity = -yVelocity;
				check = true; // đặt biến đã va chạm về true
			}
		}
		else {  
			// Kiểm tra bóng bay theo chiều y âm
			if ((ballShape.getPosition().y - ballShape.getRadius() + yVelocity*deltaTime*60.0f > brick.mShape.getPosition().y
				&& ballShape.getPosition().y - ballShape.getRadius() + yVelocity*deltaTime*60.0f < brick.mShape.getPosition().y + brick.mShape.getGlobalBounds().height)
				&& ((ballShape.getPosition().x - ballShape.getRadius() > brick.mShape.getPosition().x
					&& ballShape.getPosition().x - ballShape.getRadius() < brick.mShape.getPosition().x + brick.mShape.getGlobalBounds().width)
					|| (ballShape.getPosition().x + ballShape.getRadius() > brick.mShape.getPosition().x
						&& ballShape.getPosition().x + ballShape.getRadius() < brick.mShape.getPosition().x + brick.mShape.getGlobalBounds().width)))
			{
			
				yVelocity = -yVelocity; // đổi chiều vận tốc y
				check = true; // đặt biến đã va chạm về true
			}
		}
	}
	return check; // trả về biến kiểm tra đã va chạm
}


//Hàm tương tác với các vật thể 
bool cBall::BounceObstacle(Obstacle& obstacle,unsigned long int& Score, AudioManager& audiomanager, float DeltaTime) // nhận vao danh sách các vật chắn, điểm số, hệ thống âm thanh và thời gian giữa 2 khung hình
{
	vector<Brick>::iterator it;
	bool Check = false; // Biến kiểm trả va chạm

	//Quét từ cuối danh sách về cuối danh sách để hạn chế tình trạng xuyên bóng
	for (int i = obstacle.mRow * obstacle.mColumn - 1; i >= 0; --i)
	{
		if (ReboundBrick(obstacle.mWall[i], DeltaTime) == true) // kiểm tra va chạm với vật chắn tại vị trí thứ i
		{
			
			obstacle.BrickBehaviour(i, Score, audiomanager,Life); // xử lý tương tác ở vật chắn i
			Check = true; // biến va chạm đặt về true

		}
	}
	return Check; // trả về biến Check

}

float cBall::IntersectionPoint(RectangleShape& paddle, float DeltaTime)
{
	//cout << ballShape.getPosition().x << " " << ballShape.getPosition().y << endl;
	Vector2f FirstPoint(ballShape.getPosition().x,ballShape.getPosition().y+ballShape.getGlobalBounds().height/2.0f);
	Vector2f SecondPoint(ballShape.getPosition().x * (1.0f + DeltaTime * 60.0f), (ballShape.getPosition().y + ballShape.getGlobalBounds().height / 2.0f) * (1 + DeltaTime * 60.0f));
	float X = ((FirstPoint.x - SecondPoint.x) / (FirstPoint.y - SecondPoint.y)) * ((paddle.getPosition().y - paddle.getGlobalBounds().height / 2.0f) - FirstPoint.y) + FirstPoint.x;
	return X;
}

bool cBall::ReboundPLayer(RectangleShape& brick, float deltaTime)
{
	bool check = false;
	float Intersect = IntersectionPoint(brick, deltaTime);
	if (ballShape.getGlobalBounds().width / 2.0f + ballShape.getPosition().y + yVelocity * 60.0f * deltaTime >
		brick.getPosition().y - brick.getGlobalBounds().height / 2.0f)
	{
		if (Intersect >= brick.getPosition().x - brick.getGlobalBounds().width / 2.0f &&
			Intersect <= brick.getPosition().x + brick.getGlobalBounds().width / 2.0f)
		{
			return true;
		}
	}
	return check;
	 // kiểm tra vật chắn có được hiển thị hay không
	/*
		if (xVelocity > 0) // kiểm tra va ch
		{
			//Kiểm tra va chạm 
			if ((ballShape.getPosition().x + ballShape.getRadius() + xVelocity * deltaTime * 60.0f > brick.getPosition().x- brick.getGlobalBounds().width / 2.0f
				&& ballShape.getPosition().x + ballShape.getRadius() + xVelocity * deltaTime * 60.0f < brick.getPosition().x + brick.getGlobalBounds().width/2.0f)
				&& ((ballShape.getPosition().y - ballShape.getRadius() > brick.getPosition().y- brick.getGlobalBounds().height / 2.0f
					&& ballShape.getPosition().y - ballShape.getRadius() < brick.getPosition().y + brick.getGlobalBounds().height/2.0f)
					|| (ballShape.getPosition().y + ballShape.getRadius() > brick.getPosition().y- brick.getGlobalBounds().height / 2.0f
						&& ballShape.getPosition().y + ballShape.getRadius() < brick.getPosition().y + brick.getGlobalBounds().height/2.0f)))
			{
				xVelocity = -xVelocity; // đổi chiều vận tộc x
				check = true; // đặt biến đã va chạm về true
				return check;
			}
		}
		// kiểm tra bóng bay theo chiều x âm
		else if (xVelocity<0)
		{
			// Kiểm tra va chạm
			if ((ballShape.getPosition().x - ballShape.getRadius() + xVelocity * deltaTime * 60.0f > brick.getPosition().x - brick.getGlobalBounds().width / 2.0f
				&& ballShape.getPosition().x - ballShape.getRadius() + xVelocity * deltaTime * 60.0f < brick.getPosition().x + brick.getGlobalBounds().width / 2.0f)
				&& ((ballShape.getPosition().y - ballShape.getRadius() > brick.getPosition().y - brick.getGlobalBounds().height / 2.0f
					&& ballShape.getPosition().y - ballShape.getRadius() < brick.getPosition().y + brick.getGlobalBounds().height / 2.0f)
					|| (ballShape.getPosition().y + ballShape.getRadius() > brick.getPosition().y - brick.getGlobalBounds().height / 2.0f
						&& ballShape.getPosition().y + ballShape.getRadius() < brick.getPosition().y + brick.getGlobalBounds().height / 2.0f)))
			{
				xVelocity = -xVelocity; // đổi chiều vận tốc x
				check = true; // đặt biến đã va chạm về true
				return check;
			}
		}


		if (yVelocity > 0) // Kiểm tra bóng bay theo chiều y dương
		{
			//Kiểm tra va chạm
			if ((ballShape.getPosition().y + ballShape.getRadius() + yVelocity * deltaTime * 60.0f > brick.getPosition().y - brick.getGlobalBounds().height / 2.0f
				&& ballShape.getPosition().y + ballShape.getRadius() + yVelocity * deltaTime * 60.0f < brick.getPosition().y + brick.getGlobalBounds().height / 2.0f)
				&& ((ballShape.getPosition().x - ballShape.getRadius() > brick.getPosition().x- brick.getGlobalBounds().width / 2.0f
					&& ballShape.getPosition().x - ballShape.getRadius() < brick.getPosition().x + brick.getGlobalBounds().width / 2.0f)
					|| (ballShape.getPosition().x + ballShape.getRadius() > brick.getPosition().x - brick.getGlobalBounds().width / 2.0f
						&& ballShape.getPosition().x + ballShape.getRadius() < brick.getPosition().x + brick.getGlobalBounds().width / 2.0f)))
			{
				yVelocity = -yVelocity;
				check = true; // đặt biến đã va chạm về true
				return check;
			}
		}
		else {
			// Kiểm tra bóng bay theo chiều y âm
			if ((ballShape.getPosition().y - ballShape.getRadius() + yVelocity * deltaTime * 60.0f > brick.getPosition().y - brick.getGlobalBounds().height / 2.0f
				&& ballShape.getPosition().y - ballShape.getRadius() + yVelocity * deltaTime * 60.0f < brick.getPosition().y + brick.getGlobalBounds().height / 2.0f)
				&& ((ballShape.getPosition().x - ballShape.getRadius() > brick.getPosition().x - brick.getGlobalBounds().width / 2.0f
					&& ballShape.getPosition().x - ballShape.getRadius() < brick.getPosition().x + brick.getGlobalBounds().width / 2.0f)
					|| (ballShape.getPosition().x + ballShape.getRadius() > brick.getPosition().x - brick.getGlobalBounds().width / 2.0f
						&& ballShape.getPosition().x + ballShape.getRadius() < brick.getPosition().x + brick.getGlobalBounds().width / 2.0f)))
			{

				yVelocity = -yVelocity; // đổi chiều vận tốc y
				check = true; // đặt biến đã va chạm về true
				return check;
			}
		}
	return check;*/
}










