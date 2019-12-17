
//Class DS vật chắn
#ifndef OBSTACLE_H_
#define OBSTACLE_H_
#include"Brick.h"
#include"TextureManager.h"

//Khái báo các level khác nhau
enum class GameLevel
{
	Level1, Level2, Level3
};

//Khái báo các màu cho các loại vật chắn khác nhau
const Color Normal1(Color(31, 171, 137, 250));
const Color Normal2((Color(255, 128, 128, 250)));
const Color Normal3(Color(255, 186, 146, 250));
const Color GreedyColor(Color(255, 223, 0, 250));
const Color BombColor(Color(255,0,0,250));
const Color BarrierColor(Color(255,255,255,250));
const Color LifeColor(Color(138, 43, 226,250));
const Color DrawPathColor(Color::Green);



class Obstacle
{
public:
	bool IsDrawPath = false;
	//vector chứa các vật chắn
	vector<Brick> mWall;

	//Tổng số dòng
	int mRow;

	//Tổng số cột 
	int mColumn;

	//Level chơi 
	GameLevel mLevel;

	//Tổng số vật chắn trong màn chơi
	int TotalBrick;

	//Hàm chuyển đổi vị trí từ mảng 2 chiều sang mảng 1 chiều
	//Input: vị trị theo hàng, vị trí theo cột và tổng số cột
	//Output: vị trí trong vector 1 chiều mWall
	int CalPos(int RowPos, int ColPos, int TotalCol);

	//Hàm tạo level chơi
	//Input: số cột, số dòng, hệ thống quản lý texture, Level cần tạo
	//Output: Level cần tạo được cài đặt
	void CreateLevel(int xAmount, int yAmount, TextureManager& listtexture, GameLevel Lv);

	//Construc mặc định
	Obstacle();

	//Hàm vẽ các vật chắn
	//Input: cửa sổ vẽ
	//Output: các vật chắn được vẽ
	void Draw(RenderWindow& window);

	//Hàm hiển thị giới thiệu màn chơi ban đầu
	//Input: cửa sổ vẽ, biến kiểm tra bắt đầu hiển thị, thời gian sẽ vẽ, Level cần vẽ
	//Output: hiệu ứng giới thiệu khi load level lần đầu
	void Intro(RenderWindow& window, bool& LoadLevel, float TimeToDraw,GameLevel level);

	//Hàm vẽ các khối khác nhau sử dùng vòng for
	//Input: vị trí bắt đầu, vị trí kết thúc, biến kiểm tra vẽ tắt hay vẽ mở, Loại vật chắn 
	//Output: vẽ các vật chắn theo ý muốn
	void DrawUsingFor(int start, int end, bool IsEqual,Color color,BrickType type);

	// Hàm kiểm tra thắng thua
	// Output: kiểm tra xem người chơi đã thắng hay chưa
	bool CheckWin();

	// Hàm tương tác với khối vật chắn gây nổ
	//Input: vị trí vặt chắn, điểm, hệ thống quản lý âm thanh, số lượt chơi còn lại
	//Output: tương tác với khối vật gây nổ
	void HitBombBrick(int location,unsigned long int& Score, AudioManager& audiomanager,int &Life);

	//Hàm tương tác với các khối vật chắn
	//Input: vị trí tương tác, điểm số, hệ thống quản lý âm thanh, số lượt chơi còn lại
	//Output: tương tác với vật chắn
	void BrickBehaviour(int location,unsigned long int& Score, AudioManager& audiomanager,int &Life);
};


#endif // !Obstacle
