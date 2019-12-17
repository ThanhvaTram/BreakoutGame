#include "Obstacle.h"
#include <iterator>

//Hàm chuyển đổi vị trí từ mảng 2 chiều sang mảng 1 chiều
//Input: vị trị theo hàng, vị trí theo cột và tổng số cột
int Obstacle::CalPos(int RowPos, int ColPos, int TotalCol)
{
	return RowPos * TotalCol + ColPos; // trả về giá trị chuyển đồi từ mảng 2 chiều sang mảng 1 chiều
}

//Hàm tạo level chơi
//Input: số cột, số dòng, hệ thống quản lý texture, Level cần tạo
//Output: Level cần tạo được cài đặt
void Obstacle::CreateLevel(int xAmount, int yAmount, TextureManager& listtexture, GameLevel Lv)
{
	// Xóa các vật chắn còn trong màn chơi
	mWall.clear();
	//TH level cần cài đặt là lv1
	if (Lv == GameLevel::Level1)
	{
		//Cài đặt số cột số dòng
		mRow = 5;
		mColumn = 15;
		int modewidth = 500; // giá trị chiều dài của cửa sổ 
		float offset = 2.0f; // khoảng cách giữa các khối vật chắn

		//Cài đặt kích thước mỗi khối vật chắn
		float BrickWidth = static_cast<float> (modewidth - 2 * 15.0f - (mColumn - 1) * offset) / mColumn;
		TotalBrick = mRow * mColumn;

		// Tạo căn bản toàn bộ các vật chắn
		for (int i = 0; i < mRow; i++)
		{
			for (int j = 0; j < mColumn; j++)
			{
				// Cài đặt mặc định cho toàn bộ các vật chắn
				Brick brick(BrickWidth, BrickWidth / 2.0f);
				brick.mShape.setFillColor(Normal1);
				brick.mVisible = true;
				brick.ColPos = j;
				brick.RowPos = i;
				brick.mShape.setPosition(Vector2f(j * (brick.mShape.getGlobalBounds().width + offset) + 15.0f, i * (brick.mShape.getGlobalBounds().height + offset) + 50.0f));
				mWall.push_back(brick);
			}
		}

		//Tạo riêng các khối vật chắn nhân đôi điểm
		for (int i = 0; i < 3; i++)
		{
			for (int j=0; j <3-i; j++)
			{
				mWall[CalPos(i, j, 15)].mShape.setFillColor(GreedyColor);
				mWall[CalPos(i, j, 15)].mType = BrickType::Multiply;
				mWall[CalPos(i, 14-j, 15)].mShape.setFillColor(GreedyColor);
				mWall[CalPos(i, 14-j, 15)].mType = BrickType::Multiply;
			}
		}

		//Tạo riêng các khối vật chắn không thể bị phá hủy
		for (int i = 0; i < 5; i++)
		{
			mWall[CalPos(i, 7, 15)].mShape.setFillColor(Color::White);
			mWall[CalPos(i, 7, 15)].mType = BrickType::Barrier;
		}

		//Tạo riêng các khối vật chắn bomb
		for (int i = 0; i < 3; i++)
		{
			mWall[CalPos(4, i, 15)].mShape.setFillColor(Color::Red);
			mWall[CalPos(4, i, 15)].mType = BrickType::Bomb;
			mWall[CalPos(4, 14-i, 15)].mShape.setFillColor(Color::Red);
			mWall[CalPos(4, 14-i, 15)].mType = BrickType::Bomb;
		}
		
		
		//Tạo riêng các khối vật chắn tăng lượt chơi
		int minus = 3;
		for (int i = 0; i <4 ; i++)
		{
			{
				mWall[CalPos(i, minus, 15)].mShape.setFillColor(LifeColor);
				mWall[CalPos(i, minus, 15)].mType = BrickType::IncreaseLife;
				mWall[CalPos(i,14-minus, 15)].mShape.setFillColor(LifeColor);
				mWall[CalPos(i,14-minus, 15)].mType = BrickType::IncreaseLife;
				minus--;
			}
		}
		// Tạo riêng các khối vẽ đường đi
		mWall[CalPos(4, 3, 15)].mType = BrickType::DrawPath;
		mWall[CalPos(4, 3, 15)].mShape.setFillColor(Color::Green);
		mWall[CalPos(4, 11, 15)].mType = BrickType::DrawPath;
		mWall[CalPos(4, 11, 15)].mShape.setFillColor(Color::Green);
	}
	
	//TH level cần cài đặt là lv2
	else if (Lv == GameLevel::Level2)
	{
		mRow = 14; // cài đặt số dòng 
		mColumn = 30;// cài đặt số cột

		// Cài đặt kích thước khối vật chắn
		int modewidth = 500;
		float offset = 2.0f;
		float BrickWidth = static_cast<float> (modewidth - 2 * 15.0f - (mColumn - 1) * offset) / mColumn;

		//Cài đặt ban đầu cho toàn bộ vật chắn
		for (int i = 0; i < mRow; i++)
		{
			for (int j = 0; j < mColumn; j++)
			{
				Brick brick(BrickWidth, BrickWidth);
				brick.ColPos = j;
				brick.RowPos = i;
				brick.mShape.setFillColor(Normal1);
				brick.mType = BrickType::Normal;
				brick.mShape.setPosition(Vector2f(j * (brick.mShape.getGlobalBounds().width + offset) + 15.0f, i * (brick.mShape.getGlobalBounds().height + offset) + 50.0f));
				mWall.push_back(brick);
			}
		}
	

		//Cài đặt các khối nhân 2 điểm
		DrawUsingFor(CalPos(1, 9, 30), CalPos(1, 12, 30), false, GreedyColor, BrickType::Multiply);
		DrawUsingFor(CalPos(1, 16, 30), CalPos(1, 19, 30), false, GreedyColor, BrickType::Multiply);
		for (int i = 2; i <=6 ; i++)
		{
			mWall[CalPos(i, 8, 30)].mShape.setFillColor(GreedyColor);
			mWall[CalPos(i, 8, 30)].mType = BrickType::Multiply;
			mWall[CalPos(i, 20, 30)].mShape.setFillColor(GreedyColor);
			mWall[CalPos(i, 20, 30)].mType = BrickType::Multiply;
		}
		int minus = 0;
		for (int i = 7; i <= 12; i++)
		{
			mWall[CalPos(i, i+2, 30)].mShape.setFillColor(GreedyColor);
			mWall[CalPos(i, i + 2, 30)].mType=BrickType::Multiply;
			mWall[CalPos(i, 19-minus, 30)].mShape.setFillColor(GreedyColor);
			mWall[CalPos(i, 19 - minus, 30)].mType = BrickType::Multiply;
			minus++;
		}
		
		


		// Cài đặt các khối vật chắn không thể bị phá hủy
		{
			mWall[CalPos(4, 10, 30)].mType = BrickType::Barrier;
			mWall[CalPos(4, 10, 30)].mShape.setFillColor(BarrierColor);
			mWall[CalPos(4, 11, 30)].mType = BrickType::Barrier;
			mWall[CalPos(4, 11, 30)].mShape.setFillColor(BarrierColor);
			mWall[CalPos(5, 11, 30)].mType = BrickType::Barrier;
			mWall[CalPos(5, 11, 30)].mShape.setFillColor(BarrierColor);
			mWall[CalPos(5, 10, 30)].mType = BrickType::Barrier;

			mWall[CalPos(5, 10, 30)].mShape.setFillColor(BarrierColor);

			mWall[CalPos(4, 17, 30)].mType = BrickType::Barrier;
			mWall[CalPos(4, 17, 30)].mShape.setFillColor(BarrierColor);
			mWall[CalPos(4, 18, 30)].mType = BrickType::Barrier;
			mWall[CalPos(4, 18, 30)].mShape.setFillColor(BarrierColor);

			mWall[CalPos(5, 17, 30)].mType = BrickType::Barrier;
			mWall[CalPos(5, 17, 30)].mShape.setFillColor(BarrierColor);
			mWall[CalPos(5, 18, 30)].mType = BrickType::Barrier;
			mWall[CalPos(5, 18, 30)].mShape.setFillColor(BarrierColor);
		}



		//Cài đặt các khối vật chắn bomb
		for (int i = 13; i <= 15; i++)
		{
			mWall[CalPos(9, i, 30)].mType = BrickType::Bomb;
			mWall[CalPos(9, i, 30)].mShape.setFillColor(BombColor);
		}
		{
			mWall[CalPos(7, 14, 30)].mType = BrickType::Bomb;
			mWall[CalPos(7, 14, 30)].mShape.setFillColor(BombColor);
			mWall[CalPos(6, 14, 30)].mType = BrickType::Bomb;
			mWall[CalPos(6, 14, 30)].mShape.setFillColor(BombColor);
			mWall[CalPos(5, 10, 30)].mType = BrickType::Bomb;
			mWall[CalPos(5, 10, 30)].mShape.setFillColor(BombColor);
			mWall[CalPos(5, 17, 30)].mType = BrickType::Bomb;
			mWall[CalPos(5, 17, 30)].mShape.setFillColor(BombColor);

			mWall[CalPos(1, 8, 30)].mType = BrickType::Bomb;
			mWall[CalPos(1, 8, 30)].mShape.setFillColor(BombColor);
			mWall[CalPos(1, 13, 30)].mType = BrickType::Bomb;
			mWall[CalPos(1, 13, 30)].mShape.setFillColor(BombColor);

			mWall[CalPos(1, 20, 30)].mType = BrickType::Bomb;
			mWall[CalPos(1, 20, 30)].mShape.setFillColor(BombColor);
			mWall[CalPos(1, 15, 30)].mType = BrickType::Bomb;
			mWall[CalPos(1, 15, 30)].mShape.setFillColor(BombColor);
			mWall[CalPos(13, 14, 30)].mType = BrickType::Bomb;
			mWall[CalPos(13, 14, 30)].mShape.setFillColor(BombColor);
			mWall[CalPos(2, 14, 30)].mType = BrickType::Bomb;
			mWall[CalPos(2, 14, 30)].mShape.setFillColor(BombColor);
			mWall[CalPos(7, 8, 30)].mType = BrickType::Bomb;
			mWall[CalPos(7, 8, 30)].mShape.setFillColor(BombColor);
			mWall[CalPos(7, 20, 30)].mType = BrickType::Bomb;
			mWall[CalPos(7, 20, 30)].mShape.setFillColor(BombColor);
		}


		//Cài đặt ẩn đi các khối không cần thiết
		{
			mWall[CalPos(0, 13, 30)].mVisible = false;
			mWall[CalPos(0, 14, 30)].mVisible = false;
			mWall[CalPos(0, 15, 30)].mVisible = false;
			mWall[CalPos(1, 14, 30)].mVisible = false;
			DrawUsingFor(CalPos(0, 0, 3), CalPos(0, 8, 30), true, Normal2, BrickType::Multiply);
			DrawUsingFor(CalPos(0, 20, 30), CalPos(0, 29, 30), true, Normal2, BrickType::Multiply);
			DrawUsingFor(CalPos(1, 0, 30), CalPos(1, 7, 30), true, Normal2, BrickType::Multiply);
			DrawUsingFor(CalPos(1, 21, 30), CalPos(1, 29, 30), true, Normal2, BrickType::Multiply);
			for (int i = 2; i < 7; i++)
			{
				DrawUsingFor(CalPos(i, 0, 30), CalPos(i, 6, 30), true, Normal2, BrickType::Multiply);
				DrawUsingFor(CalPos(i, 22, 30), CalPos(i, 29, 30), true, Normal2, BrickType::Multiply);
			}
			for (int i = 2; i <= 6; i++)
			{
				mWall[CalPos(i, 7, 30)].mType = BrickType::Bomb;
				mWall[CalPos(i, 7, 30)].mShape.setFillColor(BombColor);
				mWall[CalPos(i, 21, 30)].mType = BrickType::Bomb;
				mWall[CalPos(i, 21, 30)].mShape.setFillColor(BombColor);
			}

			minus = 0;
			for (int i = 7; i < 14; i++)
			{
				DrawUsingFor(CalPos(i, 0, 30), CalPos(i, i, 30), true, Normal2, BrickType::Multiply);
				DrawUsingFor(CalPos(i, 21 - minus, 30), CalPos(i, 29, 30), true, Normal2, BrickType::Multiply);
				minus++;
			}
			minus = 0;
		}



		//Cài đặt các khối cho thêm mạng
		for (int i = 9; i <= 12; i++)
		{
			mWall[CalPos(0, i, 30)].mType = BrickType::IncreaseLife;
			mWall[CalPos(0, i, 30)].mShape.setFillColor(LifeColor);
			mWall[CalPos(0, 19-minus, 30)].mType = BrickType::IncreaseLife;
			mWall[CalPos(0, 19-minus, 30)].mShape.setFillColor(LifeColor);
			minus++;
		}
		{
			mWall[CalPos(2, 14, 30)].mType = BrickType::IncreaseLife;
			mWall[CalPos(2, 14, 30)].mShape.setFillColor(LifeColor);
		}
	}


	//TH level cần cài đặt là lv3
	else if (Lv == GameLevel::Level3)
	{
		//Cài đặt số dòng, số cột
		mRow = 8;
		mColumn = 15;

		//Cài đặt kích thước khối vật chắn
		int modewidth = 500;
		float offset = 2.0f;
		float BrickWidth = static_cast<float> (modewidth - 2 * 15.0f - (mColumn - 1) * offset) / mColumn;

		//Cài đặt ban đầu cho toàn bộ vặt chắn
		for (int i = 0; i < mRow; i++)
		{
			for (int j = 0; j < mColumn; j++)
			{
				Brick brick(BrickWidth, BrickWidth);
				brick.ColPos = j;
				brick.RowPos = i;
				brick.mShape.setFillColor(Normal2);
				brick.mType = BrickType::Normal;
				brick.mShape.setPosition(Vector2f(j * (brick.mShape.getGlobalBounds().width + offset) + 15.0f, i * (brick.mShape.getGlobalBounds().height + offset) + 50.0f));
				mWall.push_back(brick);
			}
		}
		// Cài đặt ẩn đi các khối không cần thiết 
		{
			DrawUsingFor(CalPos(2, 0, 15), CalPos(2, 3, 15), true, Color::White, BrickType::Normal);
			DrawUsingFor(CalPos(2, 11, 15), CalPos(2, 14, 15), true, Color::White, BrickType::Normal);

			DrawUsingFor(CalPos(3, 0, 15), CalPos(3, 2, 15), true, Color::White, BrickType::Normal);
			DrawUsingFor(CalPos(3, 12, 15), CalPos(3, 14, 15), true, Color::White, BrickType::Normal);

			DrawUsingFor(CalPos(4, 0, 15), CalPos(4, 1, 15), true, Color::White, BrickType::Normal);
			DrawUsingFor(CalPos(4, 13, 15), CalPos(4, 14, 15), true, Color::White, BrickType::Normal);
			for (int i = 0; i < 15; i++)
			{
				if (i == 0 || i == 1 || i == 3 || i == 11 || i == 13 || i == 14)
				{
					mWall[CalPos(5, i, 15)].mVisible = false;
				}
				if (i == 1 || i == 4 || i == 10 || i == 13)
				{
					mWall[CalPos(6, i, 15)].mVisible = true;
				}
				else
				{
					mWall[CalPos(6, i, 15)].mVisible = false;
				}
				if (i == 4 || i == 5 || i == 9 || i == 10)
				{
					mWall[CalPos(7, i, 15)].mVisible = true;
				}
				else
				{
					mWall[CalPos(7, i, 15)].mVisible = false;
				}
			}
		}

		//Cài đặt các khối nhân đôi điểm
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if ((i == 0 && j == 4) || (i == 0 && j == 10))
				{
					mWall[CalPos(i, j, 15)].mType = BrickType::Multiply;
					mWall[CalPos(i, j, 15)].mShape.setFillColor(GreedyColor);
				}
				else if ((i == 1 && j == 5) || (i == 1 && j == 9))
				{
					mWall[CalPos(i, j, 15)].mType = BrickType::Multiply;
					mWall[CalPos(i, j, 15)].mShape.setFillColor(GreedyColor);
				}
				else
				{
					mWall[CalPos(i, j, 15)].mVisible = false;
				}
			}
		}
		
		//Cài đặt các khối tăng lượt chơi
		{
			mWall[CalPos(6, 1, 15)].mType = BrickType::IncreaseLife;
			mWall[CalPos(6, 1, 15)].mShape.setFillColor(LifeColor);
			mWall[CalPos(6, 13, 15)].mType = BrickType::IncreaseLife;
			mWall[CalPos(6, 13, 15)].mShape.setFillColor(LifeColor);

			for (int i = 6; i <= 8; i++)
			{
				mWall[CalPos(5, i, 15)].mType = BrickType::IncreaseLife;
				mWall[CalPos(5, i, 15)].mShape.setFillColor(LifeColor);
			}
		}


		//Cài đặt các khối vật chắn bomb
		{
			mWall[CalPos(3, 5, 15)].mType = BrickType::Bomb;
			mWall[CalPos(3, 5, 15)].mShape.setFillColor(BombColor);

			mWall[CalPos(3, 9, 15)].mType = BrickType::Bomb;
			mWall[CalPos(3, 9, 15)].mShape.setFillColor(BombColor);

			mWall[CalPos(7, 4, 15)].mType = BrickType::Bomb;
			mWall[CalPos(7, 4, 15)].mShape.setFillColor(BombColor);

			mWall[CalPos(7, 5, 15)].mType = BrickType::Bomb;
			mWall[CalPos(7, 5, 15)].mShape.setFillColor(BombColor);

			mWall[CalPos(7, 9, 15)].mType = BrickType::Bomb;
			mWall[CalPos(7, 9, 15)].mShape.setFillColor(BombColor);

			mWall[CalPos(7, 10, 15)].mType = BrickType::Bomb;
			mWall[CalPos(7, 10, 15)].mShape.setFillColor(BombColor);
		}
	}
}


//Constructor mặc định
Obstacle::Obstacle()
{
	mRow = 0;
	mColumn = 0;
	mLevel = GameLevel::Level1;
	TotalBrick = 0;
}


//Hàm vẽ các vật chắn
//Input: cửa sổ vẽ
void Obstacle::Draw(RenderWindow& window)
{
	vector<Brick>::iterator it;

	//Quét toàn bộ vector vật chắn
	for (it = mWall.begin(); it != mWall.end(); ++it)
	{
		if (it->mVisible == true) // xét biến hiển thị nếu true vật chắn mới được hiển thị ra ngoài màn hình
		{
			window.draw(it->mShape); // vẽ vật chắn thứ i
		}
	}
}




//Hàm hiển thị giới thiệu màn chơi ban đầu
//Input: cửa sổ vẽ, biến kiểm tra bắt đầu hiển thị, thời gian sẽ vẽ, Level cần vẽ
void Obstacle::Intro(RenderWindow& window, bool& LoadLevel, float TimeToDraw,GameLevel level)
{
	//TH level cần giới thiệu là 3
	if (LoadLevel == false && level==GameLevel::Level3)
	{
		// Xóa màn hình đen
		window.clear(Color(0, 0, 0, 255));

		// Các vật chắn sẽ được vẽ theo thời gian quy định 
		if (TimeToDraw > 1.0f)
		{
			window.draw(mWall[CalPos(0, 4, 15)].mShape);
			window.draw(mWall[CalPos(0, 10, 15)].mShape);
		}
		if (TimeToDraw > 1.5f)
		{
			for (int i = 1; i <=4; i++)
			{
					window.draw(mWall[CalPos(i, 8 + i, 15)].mShape);
					window.draw(mWall[CalPos(i + 1, 8 + i, 15)].mShape);
					window.draw(mWall[CalPos(i, 6 - i, 15)].mShape);
					window.draw(mWall[CalPos(i + 1, 6 - i, 15)].mShape);
			}
			window.draw(mWall[CalPos(6, 1, 15)].mShape);
			window.draw(mWall[CalPos(6 ,13, 15)].mShape);
		}
		if (TimeToDraw > 2.5f)
		{
			for (int i = 2; i <= 5; i++)
			{
				for (int j = 6; j <= 8;j++)
				{
					window.draw(mWall[CalPos(i, j, 15)].mShape);
				}
			}
		}
		if (TimeToDraw > 3.5f)
		{
			for (int i = 4; i <= 7; i++)
			{
				for (int j = 0; j <= 13; j++)
				{
					if (mWall[CalPos(i, j, 15)].mVisible == true)
					{
						window.draw(mWall[CalPos(i, j, 15)].mShape);
					}
				}
			}
		}
		if (TimeToDraw > 4.5f)
		{
			mWall[CalPos(3, 5, 15)].mShape.setScale(0.15f * TimeToDraw, 0.15f * TimeToDraw);
			mWall[CalPos(3, 9, 15)].mShape.setScale(0.15f * TimeToDraw, 0.15f * TimeToDraw);
			window.draw(mWall[CalPos(3, 5, 15)].mShape);
			window.draw(mWall[CalPos(3, 9, 15)].mShape);
		}
		if (TimeToDraw > 6.9f)
		{
			mWall[CalPos(3, 5, 15)].mShape.setScale(1,1);
			mWall[CalPos(3, 9, 15)].mShape.setScale(1,1);
			window.draw(mWall[CalPos(3, 5, 15)].mShape);
			// Sau khi vẽ hoàn tất các khối set biến Load về true để kết thúc
			LoadLevel = true;
		}
	}

	//TH level cần giới thiệu là 1
	else if (LoadLevel == false && level == GameLevel::Level1)
	{

		//Xóa màn hình đen
		window.clear(Color(0, 0, 0, 255));

		// Các vật chắn sẽ được vẽ theo thời gian quy định 
		if (TimeToDraw > 1.0f)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4-i; j++)
				{
					window.draw(mWall[CalPos(i, j, 15)].mShape);
					window.draw(mWall[CalPos(i,14-j, 15)].mShape);
				}
			}
		}
		if (TimeToDraw > 2.0f)
		{
			for (int i = 0; i <=2; i++)
			{
				window.draw(mWall[CalPos(4,i, 15)].mShape);
				window.draw(mWall[CalPos(4, 12+i, 15)].mShape);
			}
		}
		if (TimeToDraw > 3.0f)
		{
			for (int i = 0; i <= 4; i++)
			{
				window.draw(mWall[CalPos(i, 7, 15)].mShape);
			}
		}
		if (TimeToDraw > 4.0f)
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j <15 ; j++)
				{
					window.draw(mWall[CalPos(i, j, 15)].mShape);
				}
			}
		}
		if (TimeToDraw > 4.6f)
		{
			LoadLevel = true;	// Sau khi vẽ hoàn tất các khối set biến Load về true để kết thúc
		}
	}


	//TH level cần giới thiệu là 2
	else if (LoadLevel == false && level == GameLevel::Level2)
	{
		//Xóa màn hình đen
		window.clear(Color(0, 0, 0, 255));

		// Các vật chắn sẽ được vẽ theo thời gian quy định 
		if (TimeToDraw > 1.0f)
		{
			for (int i = 2; i <= 6; i++)
			{
				window.draw(mWall[CalPos(i, 7, 30)].mShape);
				window.draw(mWall[CalPos(i, 21, 30)].mShape);
			}
			for (int i = 9; i <= 12; i++)
			{
				window.draw(mWall[CalPos(0, i, 30)].mShape);
				window.draw(mWall[CalPos(0, 28-i, 30)].mShape);
			}
			int col = 8;
			for (int i = 7; i <= 13; i++)
			{
				window.draw(mWall[CalPos(i, col, 30)].mShape);
				window.draw(mWall[CalPos(i, 28-col, 30)].mShape);
				col++;
			}
			window.draw(mWall[CalPos(1, 8, 30)].mShape);
			window.draw(mWall[CalPos(1, 20, 30)].mShape);
			window.draw(mWall[CalPos(1, 13, 30)].mShape);
			window.draw(mWall[CalPos(1, 15, 30)].mShape);
			window.draw(mWall[CalPos(2, 14, 30)].mShape);
		}
		if (TimeToDraw > 1.5f)
		{
			for (int i = 9; i <= 12; i++)
			{
				window.draw(mWall[CalPos(1, i, 30)].mShape);
				window.draw(mWall[CalPos(1, i+7, 30)].mShape);
			}
			for (int i = 2; i <= 6; i++)
			{
				window.draw(mWall[CalPos(i, 8, 30)].mShape);
				window.draw(mWall[CalPos(i, 20, 30)].mShape);
			}
			int col = 9;
			for (int i = 7; i <= 12; i++)
			{
				window.draw(mWall[CalPos(i, col, 30)].mShape);
				window.draw(mWall[CalPos(i, 28-col, 30)].mShape);
				col++;
			}
		}
		if (TimeToDraw > 2.0f)
		{
			for (int i = 0; i < 14; i++)
			{
				for (int j = 0; j < 30; j++)
				{
					if ((i == 5 && j == 10) || (i==5 && j == 17))
					{

					}
					else if ((i == 4 && j == 11) || (i == 4 && j == 18))
					{

					}
					else if ((i == 4 && j == 10) || (i == 4 && j == 17))
					{

					}
					else if ((i == 5 && j == 11) || (i == 5 && j == 18))
					{

					}
					else if ((i == 6 && j == 14) || (i == 7 && j == 14))
					{

					}
					else if ((i ==9 && j>=12))
					{

					}
					else if ((i == 9 && j <= 16))
					{

					}
					else
					{
						if (mWall[CalPos(i, j, 30)].mVisible == true)
						{
							window.draw(mWall[CalPos(i, j, 30)].mShape);
						}
					}
					
				}
			}
		}
		if (TimeToDraw > 2.5f)
		{
			vector<Brick>::iterator it;

			for (it = mWall.begin(); it != mWall.end(); ++it)
			{
				if (it->mVisible == true)
				{
					window.draw(it->mShape);
				}
			}
		}
		if (TimeToDraw > 3.5f)
		{
			// Sau khi vẽ hoàn tất các khối set biến Load về true để kết thúc
			LoadLevel = true;
		}
	}
}
		


//Hàm vẽ các khối khác nhau sử dùng vòng for
//Input: vị trí bắt đầu, vị trí kết thúc, biến kiểm tra vẽ tắt hay vẽ mở, Loại vật chắn 
void Obstacle::DrawUsingFor(int start, int end, bool IsEqual,Color color, BrickType type)
{
	// Check biến kiểu vẽ
	if (IsEqual == true)
	{
		// Quét toàn bộ từ điểm đầu đến điểm cuối
		for (int i = start; i <= end; i++)
		{
			//Set giá trị hiển thị về false
			mWall[i].mVisible = false;
		}
	}
	else
	{
		// Quét toàn bộ từ điểm đầu đến điểm cuối
		for (int i = start; i <= end; i++)
		{
			//Set giá trị hiển thị về true
			mWall[i].mVisible = true;

			//Set màu của khối về đúng màu cần hiển thị
			mWall[i].mShape.setFillColor(color);

			//Set loại của vật chắn theo loại truyền vào
			mWall[i].mType = type;
		}
	}
}


// Hàm kiểm tra thắng/thua
bool Obstacle::CheckWin()
{

	vector<Brick>::iterator it;
	//Quét toàn bộ vector vật cahwns
	for (it = mWall.begin(); it != mWall.end(); ++it)
	{
		// nếu ngoài trừ vật chắn không thể phá hủy thì nếu còn tồn tại vật chắn còn khả năng hiển thị 
		if (it->mType!=BrickType::Barrier && it->mVisible == true)
		{
			return false; // trả về false 
		}
	}

	//nếu tất cả brick (trừ vật cản không có khả năng biến mất) đều đã chạm
	return true; // trả về true
}



//Hàm tương tác với khối vật chắn gây nổ
//Input: vị trí vặt chắn, điểm, hệ thống quản lý âm thanh, số lượt chơi còn lại
void Obstacle::HitBombBrick(int location, unsigned long int& Score, AudioManager& audiomanager, int& Life)
{

	// Đặt khối vật chắn gây nổ hiển thị về false
	mWall[location].HitBrick();

	//Tăng điểm
	Score++;


	//Chuyển đổi từ vị trí mảng 1 chiều sang vị trí mảng 2 chiều 
	int locX = location % mColumn;
	int locY = location / mColumn;
	
	//Khối vật nổ sẽ gây nổ xung quanh 8 ô khác nhau
	int arrLoc[8] =
	{ (locX - 1) + (locY - 1) * mColumn ,(locX)+(locY - 1) * mColumn ,(locX + 1) + (locY - 1) * mColumn,
		(locX - 1) + (locY)*mColumn, (locX + 1) + (locY)*mColumn,
		(locX - 1) + (locY + 1) * mColumn,(locX)+(locY + 1) * mColumn, (locX + 1) + (locY + 1) * mColumn
	};

	// Xét TH giá trị cột 0
	if (locX == 0)
	{
		// Tắt đi 3 TH 
		arrLoc[0] = -1; arrLoc[3] = -1; arrLoc[5] = -1;
	}
	// Xét TH giá trị cột bằng tối đa
	else if (locX == mColumn - 1)
	{
		//Tắt đi 3 TH
		arrLoc[2] = -1; arrLoc[4] = -1; arrLoc[7] = -1;
	}
	// Xét TH vị trí hàng 0
	if (locY == 0)
	{
		//Tắt đi 3 TH
		arrLoc[0] = -1; arrLoc[1] = -1; arrLoc[2] = -1;
	}
	// Xét TH vị trí hàng tối đa
	else if (locY == mRow - 1)
	{
		//Tắt đi 3 TH
		arrLoc[5] = -1; arrLoc[6] = -1; arrLoc[7] = -1;
	}
	// Xử lý tương tác với 8 vị trí xung quanh
	for (int i = 0; i < 8; i++)
	{
		// Xét đk để tương tác 
		if (arrLoc[i] >= 0 && arrLoc[i] < mColumn * mRow)
		{
			// Xử lý tương tác ở vị trí các khối bị nổ
			BrickBehaviour(arrLoc[i], Score, audiomanager, Life);
		}
	}
}



//Hàm tương tác với các khối vật chắn
//Input: vị trí tương tác, điểm số, hệ thống quản lý âm thanh, số lượt chơi còn lại
void Obstacle::BrickBehaviour(int location,unsigned long int& Score, AudioManager& audiomanager,int& Life)
{
	//Xét TH các vật chắn cần xét tương tác khác loại không thể bị phá hủy
	if (mWall[location].mVisible == true && mWall[location].mType != BrickType::Barrier)
	{
		// TH vật chắn cần xét tương tác là loại bình thường 
		if (mWall[location].mType == BrickType::Normal)
		{
			// Phát âm thanh 
			audiomanager.PlaySound("ballhit.wav", false);
			// Tắt biến hiển thị
			mWall[location].mVisible = false;

			//Tổng sổ vật chắn giảm
			TotalBrick--;

			//Tăng điểm lên 1
			Score++;
		}

		//TH vật chắn cần xét tương tác là loại nhân đôi
		else if (mWall[location].mType == BrickType::Multiply)
		{
			// Phát âm thanh
			audiomanager.PlaySound("greedycoin.wav", false);

			//Tắt biến hiển thị
			mWall[location].mVisible = false;

			//Giảm tổng số gạch
			TotalBrick--;

			//Xét TH điểm còn là 0 không thể nhân đôi
			if (Score == 0)
			{
				Score++;
			}
			else
			{
				//Nhân đổi điểm
				int Multiplier = 0;
				Multiplier = rand() % 3;
				if (Multiplier == 0)
				{
					Score = Score * 2;
				}
				else if (Multiplier == 1)
				{
					Score = static_cast<int>(Score * 1.5);
				}
				else if (Multiplier == 2)
				{
					Score = static_cast<int>(Score * 0.5);
				}
			}
		}


		//TH vật chắn cần xét là loại bomb
		else if (mWall[location].mType == BrickType::Bomb)
		{
			// Gọi hàm tương tác bomb
			HitBombBrick(location, Score, audiomanager,Life);
			// Tắt biến hiển thị 
			mWall[location].mVisible = false;

			//trừ tổng số gạch đi
			TotalBrick--;

			//Phát âm thanh
			audiomanager.PlaySound("Bomb.wav", false);

		}

		//TH vật chắn cần xét là loại tăng lượt chơi
		else if (mWall[location].mType == BrickType::IncreaseLife)
		{
			mWall[location].mVisible = false;
			TotalBrick--;
			audiomanager.PlaySound("heartbeat.wav", false);
			Life++;
		}
		else if (mWall[location].mType == BrickType::DrawPath)
		{
			mWall[location].mVisible = false;
			TotalBrick--;
			audiomanager.PlaySound("ballhit.wav", false);
			this->IsDrawPath = true;
		}
	}
	else if (mWall[location].mType == BrickType::Barrier && mWall[location].mVisible == true)
	{
		audiomanager.PlaySound("ballhit.wav", false);
	}
	
}

