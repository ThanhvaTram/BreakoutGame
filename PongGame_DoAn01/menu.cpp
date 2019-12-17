#include "Menu.h"
#include<iostream>
using namespace sf;
using namespace std;

//Constructor mặc định
Menu::Menu()
{
	selectedItemIndex = 1; // đặt lệnh điều khiển về 1
}



//Hàm cài đặt các loại menu khác nhau
//Input: thông số cửa sổ, trạng thái game, Điểm HighScore
void Menu::inMenu(int width, int height, GameState gamestate, int highscore)

{
	if (!DisplayFont.loadFromFile("Font/SFPixelate-Bold.ttf")) // Load font hiển thị từ file
	{
		cout << "error open font" << endl;
	}
	
	//Kiểm tra gamestate truyền vào thuộc TH nào


	//cài đặt Menu chính
	if (gamestate == GameState::MainMenu) 
	{
		setMainMenu(1.0f*width,1.0f* height);
	}

	//cài đặt Menu hiển thị điểm cao nhất
	else if (gamestate == GameState::HighScore)
	{
		setMenuHighscore(1.0f * width, 1.0f * height, highscore);
	}

	//cài đặt Menu hiện thị cho Menu thắng game
	else if (gamestate == GameState::Win)
	{
		setMenuEndBreakout(1.0f * width, 1.0f * height, highscore, true);
	}

	//cài đặt Menu hiện thị cho Menu thua game
	else if (gamestate == GameState::Losing)
	{
		setMenuEndBreakout(1.0f * width, 1.0f * height, highscore, false);
	}

	//cài đặt Menu tạm dừng
	else if (gamestate == GameState::Pause)
	{
		SetMenuPause(1.0f * width, 1.0f * height);
	}

	//cài đặt Menu chọn level chơi
	else if (gamestate == GameState::LevelSelect)
	{
		SetMenuLevelSelect(1.0f * width, 1.0f * height);
	}

	//cài đặt Menu chọn chế độ chơi
	else if (gamestate == GameState::PlayModeSelect)
	{
		SetMenuPlayMode(1.0f * width, 1.0f * height);
	}

}

//Destructor mặc định
Menu::~Menu()
{
	
}




//Hàm vẽ các menu
//Input: cửa sổ game, trạng thái game cần vẽ
void Menu::draw(RenderWindow &window,GameState gamestate)
{
	//Lấy giá trị thành phần tối đa của menu cần vẽ
	int AmountOfMenuNeedToDraw = getAmountMaxNumber(gamestate);
	
	// kiểm tra vẽ TH tạm dừng
	if (gamestate == GameState::Pause) 
	{
		// Cài đặt các thông số cần thiết cho hình nền hiển thị
		RectangleShape Background;
		Background.setSize(Vector2f(window.getSize().x / 2.5f, window.getSize().y * 3.0f / 4.0f));
		Background.setOrigin(Background.getLocalBounds().width / 2.0f, Background.getLocalBounds().height / 2.0f);
		Background.setFillColor(Color(255, 175, 176, 250));
		Background.setOutlineColor(Color::White);
		Background.setOutlineThickness(1.0f);
		Background.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

		//Vẽ hình nền
		window.draw(Background);

		//Vẽ các thành phần trong Menu tạm dừng
		for (int i = 0; i < AmountOfMenuNeedToDraw; i++)
		{
			window.draw(mMenu[i]);
		}
	}


	// kiểm tra vẽ TH chọn level
	else if (gamestate == GameState::LevelSelect) // kiểm tra vẽ TH chọn level
	{

		//Cài đặt hiển thị các mũi tên trái phải 
		Texture Arrow;
		Arrow.loadFromFile("Texture/menuArrow.png");
		Arrow.setSmooth(true);
		Sprite rightarrow;
		rightarrow.setTexture(Arrow);
		rightarrow.setOrigin(rightarrow.getLocalBounds().width / 2.0f, rightarrow.getLocalBounds().height / 2.0f);
		Sprite leftarrow;
		leftarrow.setTexture(Arrow);
		leftarrow.rotate(180);
		leftarrow.setOrigin(Vector2f(leftarrow.getLocalBounds().width / 2.0f, leftarrow.getLocalBounds().height / 2.0f));
		leftarrow.setPosition(mMenu[LevelSelectionComponent - 1].getPosition().x-70.0f, mMenu[LevelSelectionComponent - 1].getPosition().y+10.0f);

		rightarrow.setPosition(mMenu[LevelSelectionComponent - 1].getPosition().x+70.0f, mMenu[LevelSelectionComponent - 1].getPosition().y+10.0f);


		//Vẽ mũi tên trái phải
		window.draw(rightarrow);
		window.draw(leftarrow);

		//Vẽ thành phần menu đầu tiên
		window.draw(mMenu[0]);

		//Vẽ thành phần menu có chỉ số bằng lệnh điều khiển
		window.draw(mMenu[selectedItemIndex]);
	}
	
	// Kiểm trả vẽ TH chọn chế độ chơi
	else if (gamestate == GameState::PlayModeSelect)  
	{
		//Cài đặt mũi tên trái phải
		Texture Arrow;
		Arrow.loadFromFile("Texture/menuArrow.png");
		Arrow.setSmooth(true);

		Sprite rightarrow;
		rightarrow.setTexture(Arrow);
		rightarrow.setOrigin(rightarrow.getLocalBounds().width / 2.0f, rightarrow.getLocalBounds().height / 2.0f);


		Sprite leftarrow;
		leftarrow.setTexture(Arrow);
		leftarrow.rotate(180);
		leftarrow.setOrigin(Vector2f(leftarrow.getLocalBounds().width / 2.0f, leftarrow.getLocalBounds().height / 2.0f));
		leftarrow.setPosition(mMenu[PlayModeSelectionComponent - 1].getPosition().x - 90.0f, mMenu[PlayModeSelectionComponent - 1].getPosition().y + 10.0f);

		rightarrow.setPosition(mMenu[PlayModeSelectionComponent - 1].getPosition().x + 90.0f, mMenu[PlayModeSelectionComponent - 1].getPosition().y + 10.0f);


		//Vẽ mũi tên trái phải
		window.draw(rightarrow);
		window.draw(leftarrow);

		//Vẽ thành phần menu đầu tiên
		window.draw(mMenu[0]);

		//Vẽ thành phần menu theo lệnh điều khiển
		window.draw(mMenu[selectedItemIndex]);
	}
	
	//Kiểm tra vẽ Các TH còn lại
	else
	{
		// Vẽ tất cả thành phần trong Menu
		for (int i = 0; i < AmountOfMenuNeedToDraw; i++)
		{
			window.draw(mMenu[i]);
		}
	}

}


//Hàm di chuyển "Lên" trong các menu
//Input: trạng thái game hiện tại
void Menu::MoveUp(GameState gamestate)
{

	//Lấy giá trị cần vẽ tối đa
	int AmountOfMenuNeedToDraw = getAmountMaxNumber(gamestate);


	//Set thành phần menu thứ lệnh điều khiển về màu đen
	mMenu[selectedItemIndex].setFillColor(Color::Black);

	// Xét nếu lệnh điều khiển lớn hơn 1 thì sẽ giảm xuống 1
	if (selectedItemIndex - 1 >= 1) 
	{
		selectedItemIndex--;
	}
	//Xét TH lệnh điều khiển còn 0
	else
	{
		// lệnh điều khiển sẽ được đưa về giá trị tối đa
		selectedItemIndex = AmountOfMenuNeedToDraw - 1;
	}
	// set thành phần menu được chọn thành màu trắng
	mMenu[selectedItemIndex].setFillColor(Color::White);

}


//Hàm di chuyển "Xuống" trong các menu
//Input: trạng thái game hiện tại
void Menu::MoveDown(GameState gamestate)
{
	//Lấy giá trị cần vẽ tối đa
	int AmoutOfMenuNeedToDraw = getAmountMaxNumber(gamestate);

	//Set thành phần menu thứ lệnh điều khiển về màu đen
	mMenu[selectedItemIndex].setFillColor(Color::Black);

	//Xét TH nếu lệnh chưa lớn hơn số lượng tối đa của menu
	if (selectedItemIndex +1< AmoutOfMenuNeedToDraw)
	{
		//Tăng lệnh 1
		selectedItemIndex++;
	}
	//Xét TH nếu lệnh vượt quá số lượng tối đa
	else
	{
		// Đặt lệnh lại bằng giá trị 1
		selectedItemIndex = 1;
	}
	// set thành phần menu được chọn thành màu trắng
	mMenu[selectedItemIndex].setFillColor(Color::White);

}


//Hàm cài đặt các loại Text khác nhau
//Input: Text cần cài đặt, nội dung Text, kích cỡ chữ
void Menu::setTextMenu(Text &menu,String content,int Size)
{
	//Cài đặ các thuộc tính cần thiết để hiển thị Text
	menu.setFont(DisplayFont);// cài đặt font cho chữ
	menu.setFillColor(Color::Black);// cài đặt màu sắc cho chữ
	menu.setString(content); // cài đặt nội dung hiển thị
	menu.setCharacterSize(Size);// cài đặt kích cỡ chữ
	menu.setOrigin(menu.getLocalBounds().width/ 2.0f, menu.getLocalBounds().height/ 2.0f);// cài đặt trọng tâm cho chữ

}



//Hàm trả về số lượng thành phần tối đa trong mỗi menu
//Input: trạng thái game
int getAmountMaxNumber(GameState gamestate)
{
	//Xét các TH khác nhau truyền vào của trạng thái chơi mà trả về giá trị tối đa có trong Menu trạng thái chơi đó
	if (gamestate == GameState::MainMenu)
	{
		return MainMenuComponents;
	}
	else if (gamestate == GameState::Instruction)
	{
		return InstructionComponents;
	}
	else if (gamestate == GameState::Losing || gamestate == GameState::Win)
	{
		return LosingPanelComponents;
	}
	else if (gamestate == GameState::HighScore)
	{
		return HighScoreComponents;
	}
	else if (gamestate == GameState::Pause)
	{
		return PauseMenuComponent;
	}
	else if (gamestate == GameState::LevelSelect)
	{
		return LevelSelectionComponent;
	}
	else if (gamestate == GameState::PlayModeSelect)
	{
		return PlayModeSelectionComponent;
	}
	return 4;
}



// Dưới đây là phần Code chung cho việc cài đặt các menu riêng rẻ khác nhau

/*Code set tuân theo mẫu chung sau
// if (mMenu.empty()!= true) 
{
	--Xóa các giá trị có trong mảng--


	mMenu.clear();
	mMenu.shrink_to_fit();

}
--Cài đặt lại số lượng thành phần tối đa--

mMenu.resize(Số lượng thành phần tối đa của Menu đã được định nghĩa);

--Cài đặt các thành phần có trong Menu--

setTextMenu(mMenu[giá trị thành phần], " ", kích cỡ chữ);
mMenu[giá trị thành phần].setFillColor(màu của Text);
mMenu[giá trị thành phần].setPosition(tọa độ của Text));
*/
//-----------------------------------


//Hàm cài đặt hiển thị Menu chính
//Input: thông số cửa sổ
void Menu::setMainMenu(float width,float height)
{
	
	if (mMenu.empty()!= true)
	{
		mMenu.clear();
		mMenu.shrink_to_fit();

	}
	mMenu.resize(MainMenuComponents);

	setTextMenu(mMenu[0], " ", 60);
	mMenu[0].setFillColor(Color(0,0,0,255));
	mMenu[0].setPosition(Vector2f(width / 2.0f, height / 2.0f * 0.5f));

	setTextMenu(mMenu[1], "Play",40);
	mMenu[1].setFillColor(Color::White);
	mMenu[1].setPosition(Vector2f(width / 2.0f, height / 2.0f * 0.85f));


	setTextMenu(mMenu[2], "Option", 40);
	mMenu[2].setFillColor(Color::Black);
	mMenu[2].setPosition(Vector2f(width / 2.0f, height / 2.0f));

	setTextMenu(mMenu[3], "Highscore",40);
	mMenu[3].setFillColor(Color::Black);
	mMenu[3].setPosition(Vector2f(width / 2.0f, height/2.0f * 1.15f));


	setTextMenu(mMenu[4], "Instruction", 40);
	mMenu[4].setFillColor(Color::Black);
	mMenu[4].setPosition(Vector2f(width / 2.0f, height / 2.0f * 1.30f));

	setTextMenu(mMenu[5], "Exit",40);
	mMenu[5].setFillColor(Color::Black);
	mMenu[5].setPosition(Vector2f(width / 2.0f, height/2.0f *1.45f));

}

//Hàm cài đặt Menu hiển thị điểm cao nhất
//Input: thông số cửa sổ, điểm cao nhất
void Menu::setMenuHighscore(float width, float height, int highscore)
{
	if (mMenu.empty() != true)
	{
		mMenu.clear();
		mMenu.shrink_to_fit();

	}
	mMenu.resize(HighScoreComponents);

	setTextMenu(mMenu[0], "HIGHSCORE: " + to_string(highscore), 30);
	mMenu[0].setFillColor(Normal1);
	mMenu[0].setPosition(Vector2f(width / 2, height / 2.0f));

	setTextMenu(mMenu[1], "Reset highscore", 30);
	mMenu[1].setFillColor(Color::White);
	mMenu[1].setPosition(Vector2f(width / 2, height / 2.0f * 1.25f));

	setTextMenu(mMenu[2], "Back", 30);
	mMenu[2].setPosition(Vector2f(width / 2, height / 2.0f * 1.5f));

}

//Hàm cài đặt Menu hiển thị kết thúc game
//Input: thông số cửa sổ,điểm đạt được,biến thắng/thua
void Menu::setMenuEndBreakout(float width, float height, int score, bool win)
{
	if (mMenu.empty() != true)
	{
		mMenu.clear();
		mMenu.shrink_to_fit();

	}
	mMenu.resize(EndBreakoutComponents);

	if (win == true)
	{
		setTextMenu(mMenu[0], "YOU WON!\nYour score: " + to_string(score), 35);
		cout << "Thang roi nha, sao hong hien won" << endl;
	}
	else {
		setTextMenu(mMenu[0], "YOU LOST!\nYour score: " + to_string(score), 35);
	}
	mMenu[0].setFillColor(Color::Black);
	mMenu[0].setPosition(Vector2f(width / 2, height / 2.0f * 0.5f));

	setTextMenu(mMenu[1], "Restart", 30);
	mMenu[1].setFillColor(Color::White);
	mMenu[1].setPosition(Vector2f(width / 2, height / 2.0f));

	setTextMenu(mMenu[2], "Main menu", 30);
	mMenu[2].setFillColor(Color::Black);
	mMenu[2].setPosition(Vector2f(width / 2, height / 2.0f * 1.25f));


}

//Hàm cài đặt hiển thị Menu tạm dừng 
//Input: thông số cửa sổ
void Menu::SetMenuPause(float width, float height)
{
	if (mMenu.empty() != true)
	{
		mMenu.clear();
		mMenu.shrink_to_fit();

	}
	mMenu.resize(PauseMenuComponent);
	setTextMenu(mMenu[0], "PAUSE", 40);
	mMenu[0].setFillColor(Color::Black);
	mMenu[0].setPosition(width / 2.0f, height * 0.5f / 2.0f);

	setTextMenu(mMenu[1], "Resume", 30);
	mMenu[1].setFillColor(Color::White);
	mMenu[1].setPosition(width / 2.0f, height * 0.75f / 2.0f);

	setTextMenu(mMenu[2], "Main Menu", 30);
	mMenu[2].setFillColor(Color::Black);
	mMenu[2].setPosition(width / 2.0f, height * 1.0f / 2.0f);

	setTextMenu(mMenu[3], "Quit", 30);
	mMenu[3].setFillColor(Color::Black);
	mMenu[3].setPosition(width / 2.0f, height * 1.25f / 2.0f);





}

//Hàm cài đặt hiển thị Menu chọn level chơi
//Input: thông số cửa sổ
void Menu::SetMenuLevelSelect(float width, float height)
{
	if (mMenu.empty() != true)
	{
		mMenu.clear();
		mMenu.shrink_to_fit();

	}
	mMenu.resize(LevelSelectionComponent);
	setTextMenu(mMenu[0], "Level", 50);
	mMenu[0].setFillColor(Normal1);
	mMenu[0].setPosition(width / 2.0f, height * 0.75f / 2.0f);


	setTextMenu(mMenu[1], "1", 40);
	mMenu[1].setFillColor(Color::White);
	mMenu[1].setPosition(width / 2.0f, height * 1.0f / 2.0f);

	setTextMenu(mMenu[2], "2", 40);
	mMenu[2].setFillColor(Color::Black);
	mMenu[2].setPosition(width / 2.0f, height * 1.0f / 2.0f);

	setTextMenu(mMenu[3], "3", 40);
	mMenu[3].setFillColor(Color::Black);
	mMenu[3].setPosition(width / 2.0f, height * 1.0f / 2.0f);

	setTextMenu(mMenu[4], "Back", 40);
	mMenu[4].setFillColor(Color::Black);
	mMenu[4].setPosition(width / 2.0f, height * 1.0f / 2.0f);

}


//Hàm cài đặt hiển thị Menu chọn chế độ chơi
//Input: thông số cửa sổ
void Menu::SetMenuPlayMode(float width, float height)
{
	if (mMenu.empty() != true)
	{
		mMenu.clear();
		mMenu.shrink_to_fit();

	}
	mMenu.resize(PlayModeComponents);
	setTextMenu(mMenu[0], "Play mode", 50);
	mMenu[0].setFillColor(Normal1);
	mMenu[0].setPosition(width / 2.0f, height * 0.75f / 2.0f);


	setTextMenu(mMenu[1], "Player", 40);
	mMenu[1].setFillColor(Color::White);
	mMenu[1].setPosition(width / 2.0f, height * 1.0f / 2.0f);

	setTextMenu(mMenu[2], "Com", 40);
	mMenu[2].setFillColor(Color::White);
	mMenu[2].setPosition(width / 2.0f, height * 1.0f / 2.0f);

	setTextMenu(mMenu[3], "Back", 40);
	mMenu[3].setFillColor(Color::White);
	mMenu[3].setPosition(width / 2.0f, height * 1.0f / 2.0f);


}




