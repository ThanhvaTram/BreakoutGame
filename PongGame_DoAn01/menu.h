
//Class Menu
#ifndef __MENU_H__
#define __MENU_H__

#include "SFML/Graphics.hpp"
#include<string>
#include<sstream>
#include <vector>
#include "Obstacle.h"
using namespace std;
using namespace sf;


// Khai báo số lượng thành phần các menu khác nhau
#define MainMenuComponents 6 
#define PlayModeComponents 4
#define InstructionComponents 1
#define LosingPanelComponents 3
#define HighScoreComponents 3
#define EndBreakoutComponents 3
#define PauseMenuComponent 4
#define LevelSelectionComponent 5
#define PlayModeSelectionComponent 4

//Khai báo các trạng thái khác nhau game
enum class GameState
{
	MainMenu, Instruction,Losing, Exit, Pause,
	PlayingBreakOut, Win, HighScore,LevelSelect,Loading,LoadingOpen,Option,PlayModeSelect
};


class Menu
{
public:

	//Constructor mặc định
	Menu();


	//Hàm cài đặt các loại menu khác nhau
	//Input: thông số cửa sổ, trạng thái game, Điểm HighScore
	//Output: menu của gamestat nhập vào sẽ được cài đặt sẵn sàng để hiển thị
	void inMenu(int width, int height, GameState gamestate, int highscore= 0);

	//Destructor mặc định
	~Menu();


	//Hàm vẽ các menu
	//Input: cửa sổ game, trạng thái game cần vẽ
	//Output: vẽ các thành phần menu của trạng thái game nhập vào
	void draw(RenderWindow &window,GameState gamestate);

	//Hàm di chuyển "Lên" trong các menu
	//Input: trạng thái game hiện tại
	//Output: di chuyển lệnh điều khiển lên trên 1
	void MoveUp(GameState gamestate);


	//Hàm di chuyển "Xuống" trong các menu
	//Input: trạng thái game hiện tại
	//Output: di chuyển lệnh điều khiển xuống 1
	void MoveDown(GameState gamestate);

	//Hàm trả về giá trị lệnh điều khiển
	//Output: giá trị lệnh hiện hành
	int GetPressedItem() { return selectedItemIndex; }

	//Hàm cài đặt các loại Text khác nhau
	//Input: Text cần cài đặt, nội dung Text, kích cỡ chữ
	//Output: Text nhập vào được cài đặt để sử dụng
	void setTextMenu(Text &menu, String content,int Size);


	//Hàm cài đặt hiển thị Menu chính
	//Input: thông số cửa sổ
	//Output: Menu chính được cài đặt
	void setMainMenu(float width, float height);




	//Hàm cài đặt Menu hiển thị điểm cao nhất
	//Input: thông số cửa sổ, điểm cao nhất
	//Output: Menu hiển thị điểm cao nhất được cài đặt
	void setMenuHighscore(float width, float height, int highscore);


	//Hàm cài đặt Menu hiển thị kết thúc game
	//Input: thông số cửa sổ,điểm đạt được,biến thắng/thua
	//Output: Menu hiển thị kết thúc game được cài đặt
	void setMenuEndBreakout(float width, float height, int score, bool win);
	
	//Hàm cài đặt hiển thị Menu tạm dừng 
	//Input: thông số cửa sổ
	//Output: Menu tạm dừng được cài đặt
	void SetMenuPause(float width, float height);

	//Hàm cài đặt hiển thị Menu chọn level chơi
	//Input: thông số cửa sổ
	//Output: Menu chọn level chơi được cài đặt
	void SetMenuLevelSelect(float width, float height);
	
	//Hàm cài đặt hiển thị Menu chọn chế độ chơi
	//Input: thông số cửa sổ
	//Output: Menu chọn chế độ chơi được cài đặt
	void SetMenuPlayMode(float width, float height);

	//Vector chứa các thành phần của menu cần được cài đặt
	vector<Text>mMenu;
	
	// Lệnh điều khiển trong các màn chơi
	int selectedItemIndex;
private:
	//Font hiển thị 
	Font DisplayFont;
};

//Hàm trả về số lượng thành phần tối đa trong mỗi menu
//Input: trạng thái game
//Output: giá trị thành phần tối đa của menu gamstate truyền vào 
int getAmountMaxNumber(GameState gamestate);

#endif // !__MENU_H__
