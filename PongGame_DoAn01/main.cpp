#include"RunProgram.h"
using namespace std;

int main()
{

	// Tạo object Game
	GAME game;
	// Tải dữ liệu đã lưu
	game.LoadGameData();

	// Cài đặt chế độ cửa sổ
	if (game.windowmode == 1)
	{
		// Chế độ cửa sổ không viền
		game.window.create(game.mode, "PONG", Style::None);
	}
	else
	{
		// Chế độ cửa sổ có viền 
		game.window.create(game.mode, "PONG", Style::Close);
	}

	//Chạy game
	while (game.gamestate != GameState::Exit)
	{
		// Chạy Menu chính
		game.RunMainMenu();

		// Chạy phần game chính
		game.RunGameBreakout();

		// Chạy màn kết thúc game
		game.RunLosingPanelBreakout();
	}
	
	


}
