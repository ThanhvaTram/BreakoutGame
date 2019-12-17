#include "RunProgram.h"

















// Constructor mặc định
GAME::GAME()
{
	//Chỉnh thông số cửa sổ
	mode.height = 600;
	mode.width = 500;
	
	// đặt lại gamestate mặc định
	gamestate = GameState::MainMenu;

	// vẽ menu chính của game
	menu.inMenu(mode.width, mode.height, gamestate, 0);

	// mở cửa sổ
	window.create(mode, "PONG", Style::Close);

	// Thêm các âm thanh vào hệ thống quản lý âm thanh
	audiomanager.AddSound("Funny.ogg");
	audiomanager.AddSound("switchCollision.wav");
	audiomanager.AddSound("switch.wav");
	audiomanager.AddSound("diesound.wav");
	audiomanager.AddSound("loseSound.wav");
	audiomanager.AddSound("Bomb.wav");
	audiomanager.AddSound("winSound.wav");
	audiomanager.AddSound("ballhit.wav");
	audiomanager.AddSound("greedycoin.wav");
	audiomanager.AddSound("heartbeat.wav");
	
	//Thêm các texture vào hệ thống quản lý texture
	texturemanager.AddTexture("Ball.png");
	texturemanager.AddTexture("Heart.png");
	texturemanager.AddTexture("Brick.png");
	texturemanager.AddTexture("Bomb.png");
	texturemanager.AddTexture("Barrier.png");
	texturemanager.AddTexture("BlueBrick.png");
	texturemanager.AddTexture("Multiply.png");
	texturemanager.AddTexture("BrickLife.png");
	texturemanager.AddTexture("Heart3.png");
	texturemanager.AddTexture("Breakout.png");
	texturemanager.AddTexture("direction.png");
	texturemanager.AddTexture("Background_5.png");

	//Level lựa chọn đặt về level1
	LevelSelected = GameLevel::Level1;
	
	// Điểm chơi được đặt về 0
	Score = 0;

	// Điểm cao nhất được đặt về 0
	HighScore = 0;
	// Thời gian giữa 2 khung hình được đặt về 0
	DeltaTime = 0.0f;

	//Chế độ khung hình được về 0
	windowmode = 0;

	//Chế độ chơi mặc định
	playmode = PlayMode::Player1;
	
	//Biến tải level hoàn tất
	LoadLevel = false;

}

GAME::~GAME()
{
}


//Hàm đọc dữ liệu đã lưu
bool GAME::LoadGameData()
{
	// Mở file lưu dữ liệu
	ifstream fin;
	fin.open("HighScore.txt");
	if (fin.is_open() == true) // nếu mở thành công
	{
		// Giá trị âm lượng
		int volume;
		fin >> HighScore; // đọc giá trị điểm cao nhất
		fin.seekg(1, 1); // dời con trỏ sang 1 dấu phẩy
		fin >> volume; // đọc giá trị âm lượng
		audiomanager.SetVolume(volume * 10); // set giá trị âm lượng 
		fin.seekg(1, 1);// dời con trỏ sang 1 dấu phẩy
		fin >> windowmode; // đọc chế độ cửa sổ 
		
		// Đóng file và trả về true
		fin.close();
		return true;
	}
	else {

		// Nếu mở file không thành công
		// Set 
		HighScore = 0;
		windowmode = 0;
		audiomanager.SetVolume(100);
		cout << "Khong tai duoc highscore" << endl;
		//Trả về false
		return false;
	}




}


//Hàm lưu dữ liệu xuống file
bool GAME::SaveGameData()
{
	// Mở file để ghi 
	ofstream fout;
	fout.open("HighScore.txt");
	// nếu mở thành công
	if (fout.is_open() == true)
	{
		// Ghi điểm cao nhất , âm lượng hiện thời và chế độ cửa sổ
		fout << HighScore<<","<< audiomanager.GetVolume()<<"," << windowmode << endl;
		
		//Đóng file và trả về true
		fout.close();
		return true;
	}
	else
	{
		//Nếu không mở được file trả về false
		cout << "Khong luu duoc highscore" << endl;
		return false;
	}

}


//Hàm chạy Menu chính
void GAME::RunMainMenu()
{
	//Cài đặt các thuộc tính cho hình nền 
	RectangleShape background;
	background.setSize(Vector2f(500.0f, 600.0f));
	background.setTexture(&texturemanager.UseTexture("Breakout.png"),false);

	// Cài đặt các thành phần Text của Menu chính
	menu.inMenu(mode.width, mode.height, gamestate);

	// Phát âm thanh của Menu chính
	audiomanager.PlaySound("Funny.ogg", true);

	//Chạy Menu chính
	while (this->gamestate == GameState::MainMenu)
	{
		Event event;
		// Dòng While xử lý logic của game
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// xử lý khi cửa sổ bị tắt
			case Event::Closed:
			{
				// đặt lại trạng thái game về Exit
				gamestate = GameState::Exit;
				// tắt cửa sổ
				window.close();
				break;
			}
				// xử lý khi có nút bấm được bấm
			case Event::KeyPressed:
			{
				// khi bấm phím W hoặc phím mũi tên lên
				if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
				{
					//tăng lựa chọn lệnh menu lên 1
					menu.MoveUp(gamestate);
				}
				// khi bấm phim S hoặc phím mũi tên xuống

				else if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
				{
					//giảm lựa chọn lệnh menu xuống 1
					menu.MoveDown(gamestate);
				}

				//khi phím enter được bấm 
				else if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					// Lệnh điều khiển bằng 1
					if (menu.GetPressedItem() == 1)
					{
						//tải màn chơi và vô Menu chọn chế độ chơi
						gamestate = GameState::Loading;
						RunLoading(GameState::PlayModeSelect, GameState::MainMenu);
					}

					//Lệnh điều khiển bằng 2
					else if (menu.GetPressedItem() == 2)
					{
						//tải màn chơi và vô Menu cài đặt
						gamestate = GameState::Loading;
						RunLoading(GameState::Option,GameState::MainMenu);
					}
					//Lệnh điều khiển bằng 3
					else if (menu.GetPressedItem() == 3)
					{
						//tải màn chơi và vô Menu hiển thị điểm cao nhất 
						gamestate = GameState::Loading;
						RunLoading(GameState::HighScore, GameState::MainMenu);
					}

					//Lệnh điều khiển bằng 4
					else if (menu.GetPressedItem() == 4)
					{
						//tải màn chơi và vô Menu hướng dẫn chơi
						gamestate = GameState::Loading;
						RunLoading(GameState::Instruction, GameState::MainMenu);
					}

					//Lệnh điều khiển bằng 5
					else if (menu.GetPressedItem() == 5)
					{
						//thoát game
						gamestate = GameState::Exit;
						window.close();
					}
				}
				break;
			}
			default:
				break;
			}
		}

		// xử lý hiển thị 
		window.clear(Color(94, 183, 183, 250));

		//vẽ hình nền 
		window.draw(background);
		//vẽ các thành phần của Menu chính
		if (gamestate == GameState::MainMenu)
		{
			menu.draw(window, gamestate);
		}
		// hiển thị những thữ được vẽ ra cửa sổ
		window.display();

		//chạy Menu chọn chế độ chơi
		RunMenuPlayMode();

		//chạy Menu cài đặt
		RunMenuOption();

		//Chạy Menu hiển thị điểm cao nhất
		RunHighScoreBreakout();

		//Chạy Menu hương dẫn 
		RunMenuInstructionBreakout();
	
	}
}

//Hàm chạy Game Breakout
void GAME::RunGameBreakout()
{



	// dừng âm thanh 	
	audiomanager.StopSound("Funny.ogg");



	RectangleShape background;
	background.setSize(Vector2f(500.0f, 600.0f));
	background.setTexture(&texturemanager.UseTexture("Background_5.png"), false);

	//Bóng
	//Cài đặt các thông số cho bóng 

	cBall ball(mode.width/2.0f, mode.height*5.50f/6.0f);
	ball.ballShape.setTexture(&texturemanager.UseTexture("Ball.png"), false);

	//Cài đặt các thông số cho thanh trượt người chơi
	cPaddle player(mode.width/2.0f, mode.height * 5.65f / 6.0f, playmode);


	//Cài đặt thanh hướng căn lực 
	Sprite Aim;
	Texture direction;
	direction.loadFromFile("Texture/direction.png");
	direction.setSmooth(true);
	Aim.setTexture(direction);
	Aim.setScale(0.13f, 0.13f);
	Aim.setColor(Color::Black);
	Aim.setOrigin(Aim.getLocalBounds().width/2.0f, Aim.getLocalBounds().height);
	Aim.setPosition(ball.ballShape.getPosition().x, ball.ballShape.getPosition().y+0.95f);
	

	//Cài đặt thanh lực bắn
	RectangleShape Force[5];
	for (int i = 0; i < 5; i++)
	{
		Force[i].setSize(Vector2f(10, 10));
		Force[i].setOrigin(Force[i].getLocalBounds().width / 2.0f, Force[i].getLocalBounds().height / 2.0f);
		Force[i].setPosition(Aim.getPosition().x + 30.0f, -i*20+player.paddleShape.getPosition().y);
		Force[i].setFillColor(Color::Green);
	}

	//Cài đặt vật vản (màn chơi)
	Obstacle obstacle;
	obstacle.CreateLevel(15, 3, texturemanager, LevelSelected);


	//kiểm tra game đã bắt đầu chưa (nhấn enter để phát bóng)
	bool IsPlaying = false;

	//Đặt thời gian giữa 2 khung hình về 0
	DeltaTime = 0.0f;
	Clock clock;
	

	//Cài đặt Text hiển thị điểm số 
	Font font;
	font.loadFromFile("Font/SFPixelate-Bold.ttf");
	Text TextScore;
	TextScore.setFont(font);
	TextScore.setCharacterSize(20);
	TextScore.setFillColor(Color::White);
	TextScore.Bold;
	TextScore.setString("Score: " + to_string(Score));
	TextScore.setPosition(10.0f, 5.0f);

	// Cài đặt hiển thị cho số lượt chơi còn lại
	vector<Sprite> SpriteLife;
	for (int i = 0; i < 3; i++)
	{
		Sprite temp;
		temp.setTexture(texturemanager.UseTexture("Heart.png"));
		temp.setScale(0.15f, 0.15f);
		temp.setPosition(mode.width - (i * 25.0f + 30.0f), 10.0f);
		SpriteLife.push_back(temp);
		
	}
	SpriteLife.resize(100);
	
	// Khóa bóng và phát lực
	bool IsLocking = false;
	
	// Cài đặt cho hiển thị intro
	Clock ForIntro;

	//Cài đặt đồng hồ sử dụng cho các lượt phát lực
	Clock countForForce;
	float ForceTime = 0;
	int IndexToDrawForce = 0;


	//Set biến tải màn chơi hoàn thành về false
	LoadLevel = false;

	//Chạy vòng While chơi game
	while (gamestate == GameState::PlayingBreakOut)
	{
		

		// Vòng while xử lý logic game
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed: // xử lý khi ấn đóng cửa sổ 
			{
				gamestate = GameState::Exit; // chuyển trạng thái chơi về exit
				window.close();// đóng cửa sổ 
				break;
			}
			case Event::KeyPressed: // xử lý sự kiện khi có nút bàn phím được bấm 
			{
				if (Keyboard::isKeyPressed(Keyboard::BackSpace))
				{
					gamestate = GameState::Pause;
				}
				//Mới vào game, điều khiển hướng phát bóng
				if (IsLocking == false && IsPlaying==false && LoadLevel==true)//xử lý khi mới vào game
				{
					//di chuyển thanh canh hướng sang trái
					if (Keyboard::isKeyPressed(Keyboard::Left))
					{
						if (Aim.getRotation() == 270)
						{
						}
						else
						{
							Aim.rotate(-5);
						}
					

					}
					// di chuyển thanh canh hướng sang phải
					if (Keyboard::isKeyPressed(Keyboard::Right))
					{

						if (Aim.getRotation() == 90)
						{
						}
						else
						{
							Aim.rotate(5);
						}
					}
				
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						
						//Khóa hướng và tiến tơi căng lực để phát bóng
						IsLocking = true;
				
					}
					break;

				}
				// xử lý lực bắn dựa trên thanh lực hiển thị
				else if (IsLocking == true && IsPlaying==false && LoadLevel == true)
				{
					// Khi ấn space sẽ banh sẽ được bắn theo tốc độ đã được canh trước 
					if (Keyboard::isKeyPressed(Keyboard::Space))
					{
						// Biến đang chơi được set về true
						IsLocking = false;
						IsPlaying = true;
						// banh được khởi động dựa trên lực chọn và góc bắn
						ball.xVelocity =static_cast<float>((IndexToDrawForce+1) * sin(Aim.getRotation() * PI / 180));
						ball.yVelocity = static_cast<float>((IndexToDrawForce + 1) * cos(Aim.getRotation() * PI / 180));
					}
				}
				break;
				
			}
			default:
				break;
			}
		}

		// Xử lý hiển thị thanh lực
		if (IsLocking == false)
		{
			//Set giá trị thanh lực về 0
			IndexToDrawForce = 0;
			ForceTime = countForForce.getElapsedTime().asSeconds(); // lấy thời gian trôi qua của game
		}
		else
		{
			// Hiển thị thanh lực 
			if (countForForce.getElapsedTime().asSeconds() > ForceTime)
			{
				// Lực được lựa chọn sẽ tăng từ 0.8s 1 mức tối đa 5 mức tăng
				IndexToDrawForce++;
				ForceTime = ForceTime + 0.8f;
				if (IndexToDrawForce > 5) // nếu đã lên tới mức tối đa lực sẽ giảm xuống còn 0
				{
					IndexToDrawForce = 0;
				}
			
				
			}
		}
		// xử lý khi đang chơi và lượt chơi vẫn còn
		if (IsPlaying == true && ball.Life >=0)
		{
			//di chuyển player
			//di chuyển banh
			//kiểm tra nếu bóng chạm vật thể thì cập nhật text điểm
		
			float PredictBallCoordX = ball.PredictCoordX(1.0f*mode.width,1.0f* mode.height, player.paddleShape);
			player.Update(DeltaTime, PredictBallCoordX, this->mode);
			
			ball.Update(DeltaTime, mode, player, IsPlaying);
			
			// kiểm tra còn đang chơi hay không
			if (IsPlaying == false)
			{
				IsLocking = false; // đặt biến khóa hướng về lại false
			}
			//kiểm tra bóng chạm vật thể, chứa hàm quyết định behavior của vật thể sau khi chạm
			bool check = ball.BounceObstacle(obstacle, Score, audiomanager, DeltaTime);
			
			// Nếu tăng điểm sẽ cập nhật lại điểm hiển thị
			if (check == true)
			{
				TextScore.setString("Score: " + to_string(Score));
			}
			
		}
		//Xử lý thắng thua của game
		//kết thúc game: thua
		if (ball.Life == 0)
		{
			
			audiomanager.PlaySound("loseSound.wav", false);

			// Set lại gamestate và cài đặt Menu thua
			gamestate = GameState::Losing;
			menu.inMenu(mode.width, mode.height, gamestate, Score);
			
		}
		//kết thúc game: thắng
		if (obstacle.CheckWin() == true)
		{
			audiomanager.PlaySound("winSound.wav", false);
			// Set lại gamestate và cài đặt Menu thắng
			gamestate = GameState::Win;
			menu.inMenu(mode.width, mode.height, gamestate, Score);
			break;
		}
		// vẽ hình nền
		window.clear(Color::White);
		window.draw(background);

		// xử lý việc hiển thị thanh lực
		if (IsPlaying == false)
		{
			window.draw(Aim);
			if (IsLocking == true)
			{

				// xử lý khi thanh hướng xoay nằm bên phải 
				if (Aim.getRotation() >= 270)
				{
					for (int i = 0; i < 5; i++)
					{
						Force[i].setPosition(Aim.getPosition().x -90.0f, -i * 20 + (player.paddleShape.getPosition().y-10.0f));
					}
				}

				// xử lý khi thanh hướng xoay nằm bên trái 
				else if (Aim.getRotation()<=90)
				{
					for (int i = 0; i < 5; i++)
					{
						Force[i].setPosition(Aim.getPosition().x + 90.0f, -i * 20 + (player.paddleShape.getPosition().y-10.0f));
					}
				}
				// vẽ các mức lực khác nhau
				for ( int i= 0; i < IndexToDrawForce; i++)
				{
					window.draw(Force[i]);
				}
			}
		}

		// Xử lý hiển thị của số lượt chơi còn lại
		if (ball.Life > ball.BasicLife)
		{
			SpriteLife.clear();
			for (int i = 0; i < ball.Life; i++)
			{
				Sprite temp;
				temp.setTexture(texturemanager.UseTexture("Heart.png"));
				temp.setScale(0.15f, 0.15f);
				temp.setPosition(mode.width - (i * 25.0f + 30.0f), 10.0f);
				SpriteLife.push_back(temp);

			}
		}
		for (int i = 0; i < ball.Life; i++)
		{
			window.draw(SpriteLife[i]);
		}
		
		// xử lý hiển thị thanh điểm
		window.draw(TextScore);
		// xử lý hiển thị người chơi
		window.draw(player.paddleShape);
		// xử lý hiển thị quả banh
		window.draw(ball.getShape());
		// xử lý hiển thị đường dẫn quả banh
		ball.DrawPath(window, obstacle.IsDrawPath);

		// xử lý việc hiển thị màn chơi lúc đầu
		obstacle.Intro(window, LoadLevel, ForIntro.getElapsedTime().asSeconds(),LevelSelected);
		// xử lý việc hiển thị sau khi kết thúc intro
		if (LoadLevel == true)
		{
			obstacle.Draw(window);
		}
		window.display();

		//Lấy thời gian giữa 2 khung hình
		DeltaTime = clock.getElapsedTime().asSeconds();

		//Chạy menu tạm dừng
		RunPauseMenuBreakout();
		
		//Reset lại đồng hồ 
		clock.restart();
	}
}


//Hàm chạy Menu điểm số cao nhất
void GAME::RunHighScoreBreakout()
{
	//Cài đặt hiển thị cho background
	RectangleShape background;
	background.setSize(Vector2f(500.0f, 600.0f));
	background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);

	// Vòng while xử lý Menu hiển thị điểm cao nhất 
	while (gamestate == GameState::HighScore)
	{
		Event event;
		//Vòng While xử lý logic game
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// TH đóng cửa sổ 
			case Event::Closed:
			{
				//Đặt lại trạng thái chơi về Exit
				gamestate = GameState::Exit;
				window.close(); // đóng cửa sổ
				break;
			}
			// TH khi có nút được bấm
			case Event::KeyPressed:
			{
				// Xử lý khi có phím W hoặc phím Up được bấm
				if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
				{
					//Giảm lệnh điều khiển đi 1
					menu.MoveUp(gamestate);
				}
				// Xử lý khi có phím S hoặc phím Up được Down
				else if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
				{
					//Tăng lệnh điều khiển lên 1
					menu.MoveDown(gamestate);
				}
				// Xử lý khi có nút enter được bấm 
				else if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					// TH lệnh điều khiển bằng 1
					if (menu.GetPressedItem() == 1)
					{
						//Reset lại HighScore người về lại 0
						HighScore = 0;
						// Lưu giá trị HighScore mới 
						SaveGameData();
						
					}
					else if (menu.GetPressedItem() == 2)
					{
						// Tải lại và chuẩn bị cho Menu chính 
						gamestate = GameState::Loading;
						RunLoading(GameState::MainMenu, GameState::HighScore);
						
					}
				}
				break;
			}
			}

		}
		// Vẽ hình nền
		window.draw(background);

		// Vẽ các thành phần của Menu hiển thị điểm cao nhất 
		if (gamestate == GameState::HighScore)
		{
			menu.draw(window, gamestate);
		}
		window.display();

	}
}


//Hàm chạy Menu tạm dừng
void GAME::RunPauseMenuBreakout()
{
	if (gamestate == GameState::Pause)
	{
		// Đặt lệnh điều khiển về 1
		menu.selectedItemIndex = 1;
		// Cài đặt Menu tạm dừng 
		menu.inMenu(mode.width, mode.height, gamestate);

		// Xử lý Menu tạm dừng 
		while (gamestate == GameState::Pause)
		{
			Event event;
			//Vòng While xử lý logic game
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					//TH  đóng cửa sổ 
				case Event::Closed:
				{
					// Đặt lại gamestate và đóng cửa sổ
					gamestate = GameState::Exit;
					window.close();
					break;
				}
				//TH có phím được bấm
				case Event::KeyPressed:
				{
					// Xử lý khi có nút W hoặc nút Up được bấm
					if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
					{
						//Giảm điều khiển lệnh đi 1
						menu.MoveUp(gamestate);
					}
					// Xử lý khi có nút S hoặc nút Down được bấm
					else if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
					{
						//Tăng điều khiển lên 1
						menu.MoveDown(gamestate);
					}
					// Xử lý khi bấm phím Enter
					else if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						// Khi lệnh điều khiển bằng 1
						if (menu.GetPressedItem() == 1)
						{
							// Resume game hiện tại
							gamestate = GameState::PlayingBreakOut;
						}
						// Khi lệnh điều khiển bằng 2
						else if (menu.GetPressedItem() == 2)
						{
							//Thoát ra ngoài Menu chính
							gamestate = GameState::Loading;
							RunLoading(GameState::MainMenu, GameState::PlayingBreakOut);

						}

						// Khi lệnh điều khiển bằng 3
						else if (menu.GetPressedItem() == 3)
						{
							//Thoát game, đóng cửa sổ
							gamestate = GameState::Exit;
							window.close();
						}
					}
				}
				break;
				}
			}
			// Hiển thị các thành phần của Menu tạm dừng 
			menu.draw(window, gamestate);
			window.display();
		}
	}
}


//Hàm chạy Menu thắng/thua
void GAME::RunLosingPanelBreakout()
{
	// Kiểm tra Score hiện thời có lớn hơn HighScore hay không 
	if (Score > HighScore)
	{
		// Nếu lớn hơn, cập nhật lại HighScore và lưu xuống file 
		HighScore = Score;
		SaveGameData();
	}

	//Cài đặt Menu thắng thua 
	menu.inMenu(mode.width, mode.height, gamestate, Score);
	// Đặt lại lệnh điều khiển bằng 1 
	menu.selectedItemIndex = 1;

	// Xử lý Menu thắng/thua
	while (gamestate == GameState::Losing || gamestate == GameState::Win)
	{
		Event event;
		//Vòng While xử lý logic game 
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				//TH Đóng cửa sổ 
			case Event::Closed:
			{
				//Đặt lại gamestate và đóng cửa sổ 
				gamestate = GameState::Exit;
				window.close();
				break;
			}
			//TH có phím được bấm 
			case Event::KeyPressed:
			{
				//Khi phím W hoặc UP được bấm 
				if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
				{
					//Giảm lệnh điều khiển đi 1 
					menu.MoveUp(gamestate);
				}
				//Khi phím S hoặc Down được bấm 
				else if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
				{
					//Tăng lệnh điều khiển đi 1 
					menu.MoveDown(gamestate);
				}
				//Khi phím enter được bấm 
				else if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					// Đặt lại Score =0
					Score = 0;

					//nếu lệnh điều khiển là 1, sẽ restart game 
					if (menu.GetPressedItem() == 1)
					{
						gamestate = GameState::Loading;
						RunLoading(GameState::PlayingBreakOut,GameState::Losing);
					}
					// nếu lệnh điều khiển là 2, sẽ thoát ra Menu chính 
					else if (menu.GetPressedItem() == 2)
					{
						gamestate = GameState::Loading;
						RunLoading(GameState::MainMenu, GameState::PlayingBreakOut);
					}
				}
				break;
			}
			default:
				break;
			}
		}

		// Xóa màn hình 
		window.clear(Color(255, 175, 176, 250));

		//Vẽ các thành phần hiển thị của Menu thắng/thua 
		if (gamestate == GameState::Losing|| gamestate == GameState::Win)
		{
			menu.draw(window, gamestate);
		}

		window.display();
	}
}


//Hàm chạy Menu chọn Level
void GAME::RunMenuSelectLevel()
{
	//Cài đặt hình nền hiển thị 
	RectangleShape background;
	if (gamestate == GameState::LevelSelect)
	{
		background.setSize(Vector2f(500.0f, 600.0f));
		background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);
		menu.SetMenuLevelSelect(1.0f * mode.width, 1.0f * mode.height);
	}

	// Xử lý Menu lựa chọn Level
	while (gamestate == GameState::LevelSelect)
	{
		Event event;
		//Vòng While xử lý logic game 
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				//TH Đóng cửa sổ 
			case Event::Closed:
			{
				//Đặt lại trạng thái game và đóng cửa sổ 
				gamestate = GameState::Exit;
				window.close();
				break;
			}
			//TH có phím được bấm
			case Event::KeyPressed:
			{
				//Khi phím A hoặc phím Left được bấm 
				if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
				{
					//Giảm lệnh điều khiển đi 1 
					menu.MoveUp(gamestate);
				}
				//Khi phím D hoặc phím Right được bấm 
				else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
				{
					//Tăng lệnh điều khiển lên 1 
					menu.MoveDown(gamestate);
				}
				//Khi phím Enter được bấm 
				else if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					//TH lệnh điều khiển là 1
					if (menu.GetPressedItem() == 1)
					{
						//Load màn chơi 1 
						LevelSelected = GameLevel::Level1;
						gamestate = GameState::Loading;
						
					}
					//TH lệnh điều khiển là 2
					else if (menu.GetPressedItem() == 2)
					{
						//Load màn chơi 2 
						LevelSelected = GameLevel::Level2;
						gamestate = GameState::Loading;

					}
					//TH lệnh điều khiển là 3
					else if (menu.GetPressedItem() == 3)
					{
						//Load màn chơi 3
						LevelSelected = GameLevel::Level3;
						gamestate = GameState::Loading;

					}
					//TH lệnh điều khiển là 4
					else if (menu.GetPressedItem() == 4)
					{
						//Thoát về Menu chính 
						gamestate = GameState::Loading;
						RunLoading(GameState::PlayModeSelect, GameState::LevelSelect);
					}
				}
			}
			}
			break;
		}
		//Load các màn chơi
		if (gamestate == GameState::Loading)
		{
			RunLoading(GameState::PlayingBreakOut, GameState::LevelSelect);
		}
		else
		{
			//Hiển thị Menu chọn Level
			window.clear(Color(94, 183, 183, 250));
			window.draw(background);
			menu.draw(window, gamestate);
			window.display();
		}
		
	}
}


//Hàm tải màn chơi
void GAME::RunLoading(GameState nextGameState,GameState CurrentGameState)
{
	if (gamestate == GameState::Loading)
	{

		// Cài đặt các thông số cho hai "cánh cửa"
		RectangleShape leftdoor;
		RectangleShape rightdoor;
		leftdoor.setSize(Vector2f(1.0f*mode.width,1.0f* mode.height));
		leftdoor.setFillColor(Color(255, 127, 80, 255));
		rightdoor.setFillColor(Color(255, 127, 80, 255));
		rightdoor.setSize(Vector2f(mode.width*1.0f, mode.height*1.0f));
		leftdoor.setOrigin(leftdoor.getLocalBounds().width, leftdoor.getLocalBounds().height / 2.0f);
		rightdoor.setOrigin(rightdoor.getLocalBounds().left, rightdoor.getLocalBounds().height / 2.0f);

		leftdoor.setPosition(0.0f, mode.height / 2.0f);
		rightdoor.setPosition(1.0f*mode.width, mode.height / 2.0f);
		float deltatime = 0;
		Clock Time;

		//xử lý việc tải màn chơi 
		while (gamestate == GameState::Loading)
		{

			Event event;
			//Vòng While xử lý logic game 
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::Closed:
				{
					//Đặt lại trạng thái game và đóng cửa sổ 
					gamestate = GameState::Exit;
					window.close();
				}
				case Event::KeyPressed:
				{

				}
				}
				break;
			}

			//Di chuyển hai "cánh cửa" mô phỏng việc đóng cửa 
			rightdoor.move(-350.0f * deltatime, 0);
			leftdoor.move(350.0f * deltatime, 0);

			// Hiển thị cái cảnh cửa 
			window.draw(leftdoor);
			window.draw(rightdoor);
			window.display();

			//Lấy thời gian giữa 2 khung hình 
			deltatime = Time.getElapsedTime().asSeconds();

			//Đặt lại đồng hồ 
			Time.restart();

			//Kiểm tra việc cửa đã đóng hoàn tất 
			if (rightdoor.getPosition().x < mode.width/2.0f-150.0f)
			{
				//Đặt gamestate vào trạng thái chuẩn bị mở cửa 
				gamestate = GameState::LoadingOpen;
				RunOpenLoading(nextGameState,CurrentGameState);
			}
		}
	}
}


//Hàm kết thúc tải màn chơi
void GAME::RunOpenLoading(GameState nextGameState,GameState CurrentGameState)
{
	if (gamestate == GameState::LoadingOpen)
	{
		//Cài đặt thông số cho hai "cánh cửa"
		RectangleShape leftdoor;
		RectangleShape rightdoor;
		leftdoor.setSize(Vector2f(1.0f*mode.width,1.0f* mode.height));
		leftdoor.setFillColor(Color(255, 127, 80, 255));
		rightdoor.setFillColor(Color(255, 127, 80, 255));
		rightdoor.setSize(Vector2f(mode.width*1.0f, mode.height*1.0f));
		leftdoor.setOrigin(leftdoor.getLocalBounds().width, leftdoor.getLocalBounds().height / 2.0f);
		rightdoor.setOrigin(rightdoor.getLocalBounds().left, rightdoor.getLocalBounds().height / 2.0f);

		leftdoor.setPosition(mode.width / 2.0f, mode.height / 2.0f);
		rightdoor.setPosition(mode.width / 2.0f, mode.height / 2.0f);
		float deltatime = 0;
		Clock Time;

		//Xử lý việc mở cửa 
		while (gamestate == GameState::LoadingOpen)
		{

			Event event;
			//Vòng While xử lý logic game 
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					//TH Đóng cửa sổ 
				case Event::Closed:
				{
					//Đặt lại gamestate và đóng cửa sổ 
					gamestate = GameState::Exit;
					window.close();
				}
				case Event::KeyPressed:
				{

				}
				}
				break;
			}
			
			//Tùy chế độ tải tiếp theo để hiển thị chính xác 
			if (nextGameState==GameState::PlayingBreakOut)
			{
				window.clear();
			}
			else
			{
				DrawIntroMenu(nextGameState, CurrentGameState);
			}

			//Xử lý việc mở cửa 
			rightdoor.move(350.0f * deltatime, 0);
			leftdoor.move(-350.0f * deltatime, 0);

			//hiển thị 2 cánh cửa 
			window.draw(leftdoor);
			window.draw(rightdoor);
			window.display();

			//Lấy thời gian giữa 2 khung hình 
			deltatime = Time.getElapsedTime().asSeconds();

			//Đặt lại đồng hồ 
			Time.restart();
			
			//Xử lý việc cửa đã hoàn tất mở 
			if (rightdoor.getPosition().x >=mode.width)
			{
				//Đặt gamestate tiếp theo
				gamestate = nextGameState;
			}
		}
	}
}


//Hàm chạy Menu cài đặt
void GAME::RunMenuOption()
{
	if (gamestate == GameState::Option)
	{
		//Cài đặt các Text cần thiết cho Menu cài đặt 
		Text OptionTitle;
		Text Volume;
		Text WindowMode[2];
		Text MainMenuButton;
		Text ApplyButton;
		RectangleShape Background;
		RectangleShape VolumeSlider[10];


		// cài đặt các icon mũi tên trái và phải
		Texture arrow;
		arrow.loadFromFile("Texture/menuArrow.png");
		arrow.setSmooth(true);
		Sprite rightarrow;
		Sprite leftarrow;

		rightarrow.setTexture(arrow);
		rightarrow.setOrigin(Vector2f(rightarrow.getLocalBounds().width / 2.0f, rightarrow.getLocalBounds().height / 2.0f));



		leftarrow.setTexture(arrow);
		leftarrow.rotate(180);
		leftarrow.setOrigin(Vector2f(leftarrow.getLocalBounds().width / 2.0f, leftarrow.getLocalBounds().height / 2.0f));




		//Load font hiển thị từ file 
		DisplayFont.loadFromFile("Font/SFPixelate-Bold.ttf");


		// cài đặt cho tên menu Option
		OptionTitle.setFont(DisplayFont);
		OptionTitle.setFillColor(Normal1);
		OptionTitle.setString("OPTION");
		OptionTitle.setCharacterSize(40);
		OptionTitle.setOrigin(OptionTitle.getLocalBounds().width / 2.0f, OptionTitle.getLocalBounds().height / 2.0f);
		OptionTitle.setPosition(mode.width / 2.0f, mode.height * 0.7f / 2.0f);


		// cài đặt nút chỉnh âm lượng
		Volume.setFont(DisplayFont);
		Volume.setFillColor(Color::Black);
		Volume.setString("Volume:");
		Volume.setCharacterSize((40));
		Volume.setOrigin(Volume.getLocalBounds().width, Volume.getLocalBounds().height);
		Volume.setPosition(mode.width / 2.0f, mode.height * 1.0f / 2.0f);






		// cài đặt cho nút xác nhận chuyển cài đặt
		ApplyButton.setFont(DisplayFont);
		ApplyButton.setFillColor(Color::White);
		ApplyButton.setString("Apply");
		ApplyButton.setCharacterSize(static_cast<int>(40));
		ApplyButton.setOrigin(ApplyButton.getLocalBounds().width / 2.0f, ApplyButton.getLocalBounds().height / 2.0f);
		ApplyButton.setPosition(mode.width / 2.0f, mode.height * 1.4f / 2.0f);


		// cài đặt cho phần hình ảnh hiện thị thanh tăng giảm âm lượng
		for (int i = 0; i < 10; i++)
		{

			VolumeSlider[i].setFillColor(Color::White);
			VolumeSlider[i].setSize(Vector2f(5.0f, 20.0f));
			VolumeSlider[i].setOrigin(VolumeSlider[i].getLocalBounds().left / 2.0f, VolumeSlider[i].getLocalBounds().height / 2.0f);
			VolumeSlider[i].setPosition((mode.width / 2.0f) + i * 10.0f + 30.0f, mode.height * 1.0f / 2.0f);
			VolumeSlider[i].rotate(180.0f);
		}


		// cài đặt cho nút trở về menu chính
		MainMenuButton.setFont(DisplayFont);
		MainMenuButton.setFillColor(Color::White);
		MainMenuButton.setString("Back");
		MainMenuButton.setCharacterSize(static_cast<int>(30));
		MainMenuButton.setOrigin(MainMenuButton.getLocalBounds().width / 2.0f, MainMenuButton.getLocalBounds().height / 2.0f);
		MainMenuButton.setPosition(mode.width / 2.0f, mode.height * 1.7f / 2.0f);



		// cài đặt cho phông nền
		Background.setSize(Vector2f(500.0f, 600.0f));
		Background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);


		// cài đặt thanh hiển thị âm lượng option đồng bộ với âm lượng hiện tại
		int ChangeVolume = 0;
		ChangeVolume = audiomanager.GetVolume();



		// set lựa chọn lệnh trong menu về lại 1
		int CommandOrder = 1;

		// Cài đặt bộ text cho hiển thị chế độ cửa sổ 
		string YesNo[2]{
			" No"," Yes"
		};
		for (int i = 0; i < 2; i++)
		{
			WindowMode[i].setFont(DisplayFont);
			WindowMode[i].setFillColor(Color::White);
			WindowMode[i].setCharacterSize(40);
			WindowMode[i].setLetterSpacing(0.4f);
			WindowMode[i].setString("Borderless:");
			WindowMode[i].setOrigin(WindowMode[i].getLocalBounds().width, WindowMode[i].getLocalBounds().height);
			WindowMode[i].setPosition(mode.width / 2.0f, mode.height * 1.2f / 2.0f);


			WindowMode[i].setString("Borderless:" + YesNo[i]);

		}
		int TempVolume = ChangeVolume;
		// cài đặt cho biến xác nhận đã chuyển tùy chỉnh
		bool IsApplyChange = false;

		// Xử lý Menu option 
		while (gamestate == GameState::Option)
		{
		


			// xử lý việc hiển thị của 2 icon mũi tên trái và phải
			if (CommandOrder == 1)
			{

				rightarrow.setPosition(mode.width * 1.55f / 2.0f, mode.height * 1.0f / 2.0f);
				leftarrow.setPosition(mode.width * 1.05f / 2.0f, mode.height * 1.0f / 2.0f);
			}
			else if (CommandOrder == 2)
			{

				rightarrow.setPosition(mode.width * 1.55f / 2.0f, mode.height * 1.2f / 2.0f);
				leftarrow.setPosition(mode.width * 1.05f / 2.0f, mode.height * 1.2f / 2.0f);
			}


			// vòng while xử lý logic game
			Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::Closed: // xử lý khi ấn đóng cửa sổ
				{
					gamestate = GameState::Exit; // set trạng thái game về lại exit
					window.close();// đóng cửa sổ 
					break;
				}
				case Event::KeyPressed: // xử lý sự kiện khi nút bàn phím được bấm
				{

					// xử lý khi nút mũi tên lên được bấm
					if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						if (CommandOrder > 1)
						{
							audiomanager.PlaySound("transitionbutton.wav", false);
							CommandOrder--;// giảm lựa chọn trong menu đi 1 khi bấm 1 lần nút mũi tên lên
			

						}
					}
					// xử lý khi mũi tên xuống được bấm
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						if (IsApplyChange == false) // xử lý khi người chơi không đổi setting( dùng cho việc hiển thị)
						{
							if (CommandOrder < 3)
							{
								audiomanager.PlaySound("transitionbutton.wav", false);
								CommandOrder++;// tăng lựa chọn lệnh lên 1 khi bấm 1 lần nút mũi tên xuống 
						
							}
						}
						else // xử lý khi người chơi đã đổi setting 
						{
							if (CommandOrder < 4)
							{
								audiomanager.PlaySound("transitionbutton.wav", false);
								CommandOrder++;//tăng lựa chọn lệnh lên 1 khi bấm 1 lần nút mũi tên xuống
					
							}
						}

					}

					//xử lý khi phím BackSpace được nhấn 
					if (Keyboard::isKeyPressed(Keyboard::BackSpace))
					{
						audiomanager.PlaySound("enterbutton.wav", false);
						// trạng thái game trở về menu chính ( hoạt động giống phím back)
						gamestate = GameState::MainMenu;
					}

					//xử lý khi lựa chọn lệnh menu là 1 và có phím nhấn 
					if (CommandOrder == 1)
					{
						// xử lý khi phím bấm mũi tên phải được nhấn 
						if (Keyboard::isKeyPressed(Keyboard::Right))
						{
							if (ChangeVolume < 10)
							{
								IsApplyChange = true;
								ChangeVolume++; // tăng giá trị lựa chọn lệnh ngang ở phần volume lên 1 khi bấm 1 lần nút mũi tên phải 
								audiomanager.SetVolume(ChangeVolume*10);// set giá trị âm lượng dựa trên lựa chọn lệnh ngang
							}

						}

						// xử lý khi phím bấm mũi tên trái được nhấn 
						else if (Keyboard::isKeyPressed(Keyboard::Left))
						{
							if (ChangeVolume > 0)
							{
								IsApplyChange = true;
								ChangeVolume--; // giảm giá trị lựa chọn lệnh ngang ở phần volume lên 1 khi bấm 1 lần nút mũi tên trái 
								audiomanager.SetVolume(ChangeVolume*10);// set giá trị âm lượng dựa trên lựa chọn lệnh ngang
							}
						}

					}
					//xử lý khi lựa chọn lệnh menu là 1 và có phím nhấn 
					else if (CommandOrder == 2)
					{
						// xử lý khi phím bấm mũi tên phải được nhấn 
						if (Keyboard::isKeyPressed(Keyboard::Right))
						{
							if (windowmode < 1)
							{
								IsApplyChange = true;
								windowmode++; // thay đổi chế độ cửa sổ 
							}

						}
						// xử lý khi phím bấm mũi tên trái được nhấn 
						else if (Keyboard::isKeyPressed(Keyboard::Left))
						{
							if (windowmode > 0)
							{
								IsApplyChange = true;
								windowmode--;// thay đổi chế độ cửa sổ 
							}
						}
					}



					// xử lý khi nút bấm enter được nhấn
					if (Keyboard::isKeyPressed(Keyboard::Enter))
					{
						audiomanager.PlaySound("enterbutton.wav", false);
						// nếu nút apply có hiển thị do người dùng thay đổi cài đặt
						if (IsApplyChange == true && CommandOrder == 4)
						{
							// Đặt lại âm lượng mới 
							audiomanager.SetVolume(TempVolume*10);
							gamestate = GameState::Loading;
							RunLoading(GameState::MainMenu,GameState::Option);
						
						}
						else if (IsApplyChange == false && CommandOrder == 3)
						{
							//Thoát về Main menu
							gamestate = GameState::MainMenu;
							gamestate = GameState::Loading;
							RunLoading(GameState::MainMenu,GameState::Option);
						}
						else if (IsApplyChange == true && CommandOrder == 3)
						{
							//Đặt lại chế độ cửa sổ 
							CommandOrder = 1;
							IsApplyChange = false;
							if (windowmode == 1)
							{
								window.create(mode, "PONG", Style::None);
							}
							else
							{
								window.create(mode, "PONG", Style::Close);
							}
							//Lưu giá trị 
							SaveGameData();
						}
					}
					break;
				}
				default:
					break;
				}
			}


			/*PHẦN CODE DƯỚI ĐÂY XỬ LÝ PHẦN HIỂN THỊ KHUNG HÌNH*/
			window.draw(Background);
			window.draw(OptionTitle);
			window.draw(Volume);
			window.draw(MainMenuButton);
			window.draw(WindowMode[windowmode]);



			// xử lý việc vẽ icon mũi tên trái và phải dựa trên lựa chọn lệnh là nút Volume hay là nút Resolution
			if (CommandOrder == 1 || CommandOrder == 2)
			{
				window.draw(rightarrow);
				window.draw(leftarrow);
			}

			// xử lý khi biến thay đổi chưa xác nhận là true để hiển thị nút apply, nút apply không mặc định hiển thị nếu người chơi không thay đổi độ phân giải
			if (IsApplyChange == true)
			{
				window.draw(ApplyButton);
			}

			// xử lý việc vẽ các nút khác nhau dựa trên các lệnh điều khiển khác nhau 
			if (CommandOrder == 1)
			{
				MainMenuButton.setFillColor(Color::Black);
				Volume.setFillColor(Color::White);
				ApplyButton.setFillColor(Color::Black);
				WindowMode[windowmode].setFillColor(Color::Black);

			}

			else if (CommandOrder == 2)
			{
				MainMenuButton.setFillColor(Color::Black);
				Volume.setFillColor(Color::Black);
				ApplyButton.setFillColor(Color::Black);
				WindowMode[windowmode].setFillColor(Color::White);
			}

			else if (CommandOrder == 3 && IsApplyChange == false)
			{
				MainMenuButton.setFillColor(Color::White);
				Volume.setFillColor(Color::Black);
				ApplyButton.setFillColor(Color::Black);
				WindowMode[windowmode].setFillColor(Color::Black);
			}
			else if (CommandOrder == 3 && IsApplyChange == true)
			{
				MainMenuButton.setFillColor(Color::Black);
				Volume.setFillColor(Color::Black);
				ApplyButton.setFillColor(Color::White);
				WindowMode[windowmode].setFillColor(Color::Black);
			}

		
			else if (CommandOrder == 4 && IsApplyChange == true)
			{
				MainMenuButton.setFillColor(Color::White);
				Volume.setFillColor(Color::Black);
				ApplyButton.setFillColor(Color::Black);
				WindowMode[windowmode].setFillColor(Color::Black);

			}
			// xử lý việc hiển thị của thanh trượt âm lượng
			for (int i = 0; i < 10; i++)
			{
				if (i < ChangeVolume)// các thanh trượt sẽ nhận giá trị hiện thời của biến lựa chọn lệnh ngang để hiển thị đúng mức âm lượng
				{
					VolumeSlider[i].setFillColor(Color::Green);
				}
				else
				{
					VolumeSlider[i].setFillColor(Color::White);
				}
				// Vẽ các thanh trượt âm lượng 
				window.draw(VolumeSlider[i]);


			}
			window.display();
		}
	}
}


//Hàm chạy Menu hướng dẫn chơi
void GAME::RunMenuInstructionBreakout()
{
	//Load font từ file 
	DisplayFont.loadFromFile("Font/SFPixelate-Bold.ttf");

	//Cài đặt hình nền hiển thị
	RectangleShape bg;
	bg.setSize(Vector2f(500.0f, 600.0f));
	bg.setTexture(&texturemanager.UseTexture("Breakout.png"), false);


	//Cài đặt các khối hiển thị 
	RectangleShape normalrec[7];
	int mColumn = 15;
	int modewidth = 500;
	float offset = 2.0f;
	float BrickWidth = static_cast<float> (modewidth - 2 * 15.0f - (mColumn - 1) * offset) / mColumn;
	for (int i = 0; i < 7; i++)
	{
		normalrec[i].setSize(Vector2f(BrickWidth, BrickWidth / 2.0f));
		normalrec[i].setOrigin(normalrec[i].getLocalBounds().width / 2.0f, normalrec[i].getLocalBounds().height / 2.0f);
		normalrec[i].setPosition(mode.width / 2.0f * 0.25f, 50.0f*i+mode.height / 2.0f*0.75f);
	}


	normalrec[0].setFillColor(Normal1);
	normalrec[1].setFillColor(Normal2);
	normalrec[2].setFillColor(Color::Green);
	normalrec[3].setFillColor(BombColor);
	normalrec[4].setFillColor(BarrierColor);
	normalrec[5].setFillColor(LifeColor);
	normalrec[6].setFillColor(GreedyColor);


	//cài đặt các miêu tả cho các khối vật chắn 
	Text Describe[7];
	for (int i = 0; i < 7; i++)
	{
		Describe[i].setFont(DisplayFont);
	}
	for (int i = 0; i < 2; i++)
	{
		Describe[i].setString("Normal Brick");
		Describe[i].setCharacterSize(25);
		Describe[i].setOrigin(Describe[i].getLocalBounds().width / 2.0f, Describe[i].getLocalBounds().height / 2.0f);
		Describe[i].setPosition(mode.width / 2.0f, normalrec[i].getPosition().y - 10.0f);
	}


	Describe[2].setString("Draw path");
	Describe[2].setCharacterSize(25);
	Describe[2].setFillColor(Color::Green);
	Describe[2].setOrigin(Describe[2].getLocalBounds().width / 2.0f, Describe[2].getLocalBounds().height / 2.0f);
	Describe[2].setPosition(mode.width / 2.0f, normalrec[2].getPosition().y - 10.0f);

	Describe[0].setFillColor(Normal1);
	Describe[1].setFillColor(Normal2);
	Describe[2].setFillColor(Color::Green);



	Describe[3].setString("TNT Brick");
	Describe[3].setCharacterSize(25);
	Describe[3].setFillColor(BombColor);
	Describe[3].setOrigin(Describe[3].getLocalBounds().width / 2.0f, Describe[3].getLocalBounds().height / 2.0f);
	Describe[3].setPosition(mode.width / 2.0f, normalrec[3].getPosition().y - 10.0f);

	Describe[4].setString("Barrier Brick");
	Describe[4].setCharacterSize(25);
	Describe[4].setFillColor(BarrierColor);
	Describe[4].setOrigin(Describe[4].getLocalBounds().width / 2.0f, Describe[4].getLocalBounds().height / 2.0f);
	Describe[4].setPosition(mode.width / 2.0f, normalrec[4].getPosition().y - 10.0f);

	Describe[5].setString("Life Brick");
	Describe[5].setCharacterSize(25);
	Describe[5].setFillColor(LifeColor);
	Describe[5].setOrigin(Describe[5].getLocalBounds().width / 2.0f, Describe[5].getLocalBounds().height / 2.0f);
	Describe[5].setPosition(mode.width / 2.0f, normalrec[5].getPosition().y - 10.0f);

	Describe[6].setString("Multiply point");
	Describe[6].setCharacterSize(25);
	Describe[6].setFillColor(GreedyColor);
	Describe[6].setOrigin(Describe[6].getLocalBounds().width / 2.0f, Describe[6].getLocalBounds().height / 2.0f);
	Describe[6].setPosition(mode.width / 2.0f, normalrec[6].getPosition().y - 10.0f);


	//Cài đặt cho nút Back
	Text Back;
	Back.setFont(DisplayFont);
	Back.setString("Back");
	Back.setCharacterSize(25);
	Back.setFillColor(Color::White);
	Back.setOrigin(Back.getLocalBounds().width / 2.0f, Back.getLocalBounds().height / 2.0f);
	Back.setPosition(mode.width / 2.0f, normalrec[6].getPosition().y + 25.0f);


	// Xử lý Menu hướng dẫn chơi 
	while (gamestate == GameState::Instruction)
	{
		Event event;
		//Vòng While xử lý logic game 
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				//TH Đóng cửa sổ 
			case Event::Closed:
			{
				//Đặt lại trạng thái game và đóng cửa sổ 
				window.close();
				gamestate = GameState::Exit;
				
			}
			//TH Có phím được bấm 
			case Event::KeyPressed:
			{
				//Nếu là phím enter hoặc backspace được nhấn
				if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::BackSpace))
				{
					//Quay về Menu chính 
					gamestate = GameState::Loading;
					RunLoading(GameState::MainMenu, GameState::Instruction);
				}
			}
			}
		}
		//Vẽ Hình nền
		window.draw(bg);

		//Vẽ nút Back
		window.draw(Back);

		//Vẽ các khối hiển thị và miêu tả của từng khối 
		for (int i = 0; i < 7; i++)
		{
			window.draw(Describe[i]);
		}
		for (int i = 0; i < 7; i++)
		{
			window.draw(normalrec[i]);
		}
	
		window.display();
	}
}


//Hàm chạy Menu chọn chế độ chơi
void GAME::RunMenuPlayMode()
{
	//Cài đặt hiển thị hình nền
	RectangleShape Background;
	Background.setSize(Vector2f(500.0f, 600.0f));
	Background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);

	//xử lý Menu chọn chế độ chơi 
	while (gamestate == GameState::PlayModeSelect)
	{
		Event event;
		//Vòng While xử lý logic game 
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				//TH Đóng cửa sổ 
			case Event::Closed:
			{
				//Đặt lại trạng thái game và đóng cửa sổ 
				window.close();
				gamestate = GameState::Exit;
			}
			//TH có phím được bấm 
			case Event::KeyPressed:
			{
				//Nếu phím A hoặc phím Left được bấm
				if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
				{
					//Giảm lệnh điều khiển đi 1
					menu.MoveUp(gamestate);
				}
				//Nếu phím D hoặc phím Right được bấm
				else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
				{
					//Tăng lệnh điều khiển lên 1 
					menu.MoveDown(gamestate);
				}
				//Xử lý khi nút enter được bấm 
				else if (Keyboard::isKeyPressed(Keyboard::Enter))
				{
					//TH lệnh điều khiển là 1
					if (menu.GetPressedItem() == 1)
					{
						//Chế độ người chơi con người và tải Menu chọn màn chơi 
						playmode = PlayMode::Player1;
						gamestate = GameState::Loading;
						RunLoading(GameState::LevelSelect, GameState::PlayModeSelect);
					}
					//TH lệnh điều khiển là 2
					else if (menu.GetPressedItem() == 2)
					{
						//Chế độ người chơi máy tính và tải Menu chọn màn chơi 
						playmode = PlayMode::Computer;
						gamestate = GameState::Loading;
						RunLoading(GameState::LevelSelect, GameState::PlayModeSelect);
					}
					//TH lệnh điều khiển là 3
					else if (menu.GetPressedItem() == 3)
					{
						//Quay về Menu chính 
						gamestate = GameState::Loading;
						RunLoading(GameState::MainMenu, GameState::PlayModeSelect);
					}
				}
			default:
				break;
			}
			}
		}
		//Vẽ Hình nền và các thành phần trong Menu chọn chế độ chơi 
		window.clear(Color(94, 183, 183, 250));
		window.draw(Background);
		menu.draw(window, gamestate);
		window.display();
		RunMenuSelectLevel();
	}
}


//Hàm vẽ tải màn chơi
void GAME::DrawIntroMenu(GameState toDraw, GameState CurrentGameState)
{
	//Xét TH trạng thái game tiếp theo là Cài đặt
	if (toDraw == GameState::Option)
	{
		//Set up toàn bộ các text tương tự như trên Menu cài đặt
		Text OptionTitle;
		Text Volume;
		Text WindowMode[2];
		Text MainMenuButton;
		Text ApplyButton;
		RectangleShape Background;
		RectangleShape VolumeSlider[10];


		// cài đặt các icon mũi tên trái và phải
		Texture arrow;
		arrow.loadFromFile("Texture/menuArrow.png");
		arrow.setSmooth(true);
		Sprite rightarrow;
		Sprite leftarrow;

		rightarrow.setTexture(arrow);
		rightarrow.setOrigin(Vector2f(rightarrow.getLocalBounds().width / 2.0f, rightarrow.getLocalBounds().height / 2.0f));



		leftarrow.setTexture(arrow);
		leftarrow.rotate(180);
		leftarrow.setOrigin(Vector2f(leftarrow.getLocalBounds().width / 2.0f, leftarrow.getLocalBounds().height / 2.0f));





		DisplayFont.loadFromFile("Font/SFPixelate-Bold.ttf");


		// cài đặt cho tên menu Option
		OptionTitle.setFont(DisplayFont);
		OptionTitle.setFillColor(Normal1);
		OptionTitle.setString("OPTION");
		OptionTitle.setCharacterSize(40);
		OptionTitle.setOrigin(OptionTitle.getLocalBounds().width / 2.0f, OptionTitle.getLocalBounds().height / 2.0f);
		OptionTitle.setPosition(mode.width / 2.0f, mode.height * 0.7f / 2.0f);


		// cài đặt nút chỉnh âm lượng
		Volume.setFont(DisplayFont);
		Volume.setFillColor(Color::Black);
		Volume.setString("Volume:");
		Volume.setCharacterSize((40));
		Volume.setOrigin(Volume.getLocalBounds().width, Volume.getLocalBounds().height);
		Volume.setPosition(mode.width / 2.0f, mode.height * 1.0f / 2.0f);






		// cài đặt cho nút xác nhận chuyển cài đặt
		ApplyButton.setFont(DisplayFont);
		ApplyButton.setFillColor(Color::White);
		ApplyButton.setString("Apply");
		ApplyButton.setCharacterSize(static_cast<int>(40));
		ApplyButton.setOrigin(ApplyButton.getLocalBounds().width / 2.0f, ApplyButton.getLocalBounds().height / 2.0f);
		ApplyButton.setPosition(mode.width / 2.0f, mode.height * 1.4f / 2.0f);


		// cài đặt cho phần hình ảnh hiện thị thanh tăng giảm âm lượng

		for (int i = 0; i < 10; i++)
		{

			VolumeSlider[i].setFillColor(Color::White);
			VolumeSlider[i].setSize(Vector2f(5.0f, 20.0f));
			VolumeSlider[i].setOrigin(VolumeSlider[i].getLocalBounds().left / 2.0f, VolumeSlider[i].getLocalBounds().height / 2.0f);
			VolumeSlider[i].setPosition((mode.width / 2.0f) + i * 10.0f + 30.0f, mode.height * 1.0f / 2.0f);
			VolumeSlider[i].rotate(180.0f);
		}


		// cài đặt cho nút trở về menu chính
		MainMenuButton.setFont(DisplayFont);
		MainMenuButton.setFillColor(Color::White);
		MainMenuButton.setString("Back");
		MainMenuButton.setCharacterSize(static_cast<int>(30));
		MainMenuButton.setOrigin(MainMenuButton.getLocalBounds().width / 2.0f, MainMenuButton.getLocalBounds().height / 2.0f);
		MainMenuButton.setPosition(mode.width / 2.0f, mode.height * 1.7f / 2.0f);



		// cài đặt cho phông nền
		Background.setSize(Vector2f(500.0f, 600.0f));
		Background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);


		// cài đặt thanh hiển thị âm lượng option đồng bộ với âm lượng hiện tại
		int ChangeVolume = 0;
		ChangeVolume = audiomanager.GetVolume();


		// set lựa chọn lệnh trong menu về lại 1
		int CommandOrder = 1;

		//Cài đặt các bộ Text cho việc hiển thị chế độ cửa sổ 

		string YesNo[2]{
			" No"," Yes"
		};
		for (int i = 0; i < 2; i++)
		{
			WindowMode[i].setFont(DisplayFont);
			WindowMode[i].setFillColor(Color::White);
			WindowMode[i].setCharacterSize(40);
			WindowMode[i].setLetterSpacing(0.4f);
			WindowMode[i].setString("Borderless:");
			WindowMode[i].setOrigin(WindowMode[i].getLocalBounds().width, WindowMode[i].getLocalBounds().height);
			WindowMode[i].setPosition(mode.width / 2.0f, mode.height * 1.2f / 2.0f);


			WindowMode[i].setString("Borderless:" + YesNo[i]);

		}
		if (CommandOrder == 1)
		{
			MainMenuButton.setFillColor(Color::Black);
			Volume.setFillColor(Color::White);
			ApplyButton.setFillColor(Color::Black);
			WindowMode[windowmode].setFillColor(Color::Black);

		}
		// Vẽ các thành phần Text trong Menu cài đặt 
		int TempVolume = ChangeVolume;
		window.draw(Background);
		window.draw(OptionTitle);
		window.draw(Volume);
		window.draw(MainMenuButton);
		window.draw(WindowMode[windowmode]);

		if (CommandOrder == 1 || CommandOrder == 2)
		{
			window.draw(rightarrow);
			window.draw(leftarrow);
		}

		for (int i = 0; i < 10; i++)
		{
			if (i < ChangeVolume)
			{
				VolumeSlider[i].setFillColor(Color::Green);
			}
			else
			{
				VolumeSlider[i].setFillColor(Color::White);
			}

			window.draw(VolumeSlider[i]);
		}
	}

	//Xét TH trạng thái game tiếp theo là Hiển thị điểm số cao nhất
	else if (toDraw == GameState::HighScore)
	{
		// Cài đặt hình nền hiển thị
		RectangleShape Background;
		Background.setSize(Vector2f(500.0f, 600.0f));
		Background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);

		//Cài đặt lại Menu cần hiển thị
		menu.inMenu(mode.width, mode.height, toDraw, HighScore);
		//Đặt lại lệnh điều khiển bằng 1
		menu.selectedItemIndex = 1;

		//Vẽ hình nền và các thành phần có trong Menu hiển thị điểm cao nhất 
		window.draw(Background);
		for (int i = 0; i < HighScoreComponents; i++)
		{
			window.draw(menu.mMenu[i]);
		}
	}

	//Xét TH trạng thái game tiếp theo là chọn màn chơi 
	else if (toDraw == GameState::LevelSelect)
	{
		//Cài đặt hình nền hiển thị
		RectangleShape Background;
		Background.setSize(Vector2f(500.0f, 600.0f));
		Background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);

		//Cài đặt Menu chọn màn chơi
		menu.inMenu(mode.width, mode.height, toDraw, HighScore);

		//Đặt lại lệnh điều khiển là 1
		menu.selectedItemIndex = 1;
		//Vẽ các thành phân Menu chọn màn chơi và hình nền
		window.draw(Background);
		window.draw(menu.mMenu[0]);
		window.draw(menu.mMenu[1]);
	}

	// Xét TH trạng thái game tiếp theo là Menu Hướng dẫn 
	else if (toDraw == GameState::Instruction)
	{

		// Các cài đặt tương tự như hiển thị Menu Hướng dẫn chơi 

		DisplayFont.loadFromFile("Font/SFPixelate-Bold.ttf");
		RectangleShape bg;
		bg.setSize(Vector2f(500.0f, 600.0f));
		bg.setTexture(&texturemanager.UseTexture("Breakout.png"), false);
		RectangleShape normalrec[7];
		int mColumn = 15;
		int modewidth = 500;
		float offset = 2.0f;
		float BrickWidth = static_cast<float> (modewidth - 2 * 15.0f - (mColumn - 1) * offset) / mColumn;
		for (int i = 0; i < 7; i++)
		{
			normalrec[i].setSize(Vector2f(BrickWidth, BrickWidth / 2.0f));
			normalrec[i].setOrigin(normalrec[i].getLocalBounds().width / 2.0f, normalrec[i].getLocalBounds().height / 2.0f);
			normalrec[i].setPosition(mode.width / 2.0f * 0.25f, 50.0f * i + mode.height / 2.0f * 0.75f);
		}


		normalrec[0].setFillColor(Normal1);
		normalrec[1].setFillColor(Normal2);
		normalrec[2].setFillColor(Normal3);
		normalrec[3].setFillColor(BombColor);
		normalrec[4].setFillColor(BarrierColor);
		normalrec[5].setFillColor(LifeColor);
		normalrec[6].setFillColor(GreedyColor);

		Text Describe[7];
		for (int i = 0; i < 7; i++)
		{
			Describe[i].setFont(DisplayFont);
		}
		for (int i = 0; i < 2; i++)
		{
			Describe[i].setString("Normal Brick");
			Describe[i].setCharacterSize(25);
			Describe[i].setOrigin(Describe[i].getLocalBounds().width / 2.0f, Describe[i].getLocalBounds().height / 2.0f);
			Describe[i].setPosition(mode.width / 2.0f, normalrec[i].getPosition().y - 10.0f);
		}
		Describe[0].setFillColor(Normal1);
		Describe[1].setFillColor(Normal2);
		
		
		Describe[2].setFillColor(Color::Green);
		Describe[2].setString("Draw path");
		Describe[2].setCharacterSize(25);
		Describe[2].setFillColor(Color::Green);
		Describe[2].setOrigin(Describe[2].getLocalBounds().width / 2.0f, Describe[2].getLocalBounds().height / 2.0f);
		Describe[2].setPosition(mode.width / 2.0f, normalrec[2].getPosition().y - 10.0f);



		Describe[3].setString("TNT Brick");
		Describe[3].setCharacterSize(25);
		Describe[3].setFillColor(BombColor);
		Describe[3].setOrigin(Describe[3].getLocalBounds().width / 2.0f, Describe[3].getLocalBounds().height / 2.0f);
		Describe[3].setPosition(mode.width / 2.0f, normalrec[3].getPosition().y - 10.0f);

		Describe[4].setString("Barrier Brick");
		Describe[4].setCharacterSize(25);
		Describe[4].setFillColor(BarrierColor);
		Describe[4].setOrigin(Describe[4].getLocalBounds().width / 2.0f, Describe[4].getLocalBounds().height / 2.0f);
		Describe[4].setPosition(mode.width / 2.0f, normalrec[4].getPosition().y - 10.0f);

		Describe[5].setString("Life Brick");
		Describe[5].setCharacterSize(25);
		Describe[5].setFillColor(LifeColor);
		Describe[5].setOrigin(Describe[5].getLocalBounds().width / 2.0f, Describe[5].getLocalBounds().height / 2.0f);
		Describe[5].setPosition(mode.width / 2.0f, normalrec[5].getPosition().y - 10.0f);

		Describe[6].setString("Multiply point");
		Describe[6].setCharacterSize(25);
		Describe[6].setFillColor(GreedyColor);
		Describe[6].setOrigin(Describe[6].getLocalBounds().width / 2.0f, Describe[6].getLocalBounds().height / 2.0f);
		Describe[6].setPosition(mode.width / 2.0f, normalrec[6].getPosition().y - 10.0f);

		Text Back;
		Back.setFont(DisplayFont);
		Back.setString("Back");
		Back.setCharacterSize(25);
		Back.setFillColor(Color::White);
		Back.setOrigin(Back.getLocalBounds().width / 2.0f, Back.getLocalBounds().height / 2.0f);
		Back.setPosition(mode.width / 2.0f, normalrec[6].getPosition().y + 25.0f);

		window.draw(bg);
		window.draw(Back);
		for (int i = 0; i < 7; i++)
		{
			window.draw(Describe[i]);
		}
		for (int i = 0; i < 7; i++)
		{
			window.draw(normalrec[i]);
		}

	}

	//Xét TH trạng thái game tiếp theo là chọn chế độ chơi và trạng thái hiện hành là Menu chính
	else if (toDraw == GameState::PlayModeSelect && CurrentGameState==GameState::MainMenu)
	{
		//Cài đặt hình nền 
		RectangleShape Background;
		Background.setSize(Vector2f(500.0f, 600.0f));
		Background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);
		//Cài đặt Menu chọn chế độ chơi
		menu.inMenu(mode.width, mode.height, toDraw, HighScore);
		menu.selectedItemIndex = 1;

		//Vẽ hình nền và các thành phàn Menu chọn chế độ chơi 
		window.draw(Background);
		window.draw(menu.mMenu[0]);
		window.draw(menu.mMenu[1]);
	}


	//Xét TH trạng thái game tiếp theo là Menu chính và trạng thái hiện hành là Menu cài đặt
	else if (toDraw == GameState::MainMenu && CurrentGameState == GameState::Option)
	{
		//Cài đặt hình nền
		RectangleShape Background;
		Background.setSize(Vector2f(500.0f, 600.0f));
		Background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);

		//cài đặt lại Menu chính 
		window.draw(Background);
		menu.inMenu(mode.width, mode.height, toDraw, HighScore);
		menu.selectedItemIndex = 2;

		//Hiển thị Menu chính 
		for (int i = 0; i < MainMenuComponents; i++)
		{
			if (i == menu.selectedItemIndex)
			{
				menu.mMenu[i].setFillColor(Color::White);
			}
			else
			{
				menu.mMenu[i].setFillColor(Color::Black);
			}
			window.draw(menu.mMenu[i]);
		}


	}

	//Xét TH trạng thái game tiếp theo là Menu chính và trạng thái hiện hành là Menu hiển thị điểm cao nhất 
	else if (toDraw == GameState::MainMenu && CurrentGameState == GameState::HighScore)
	{
		//Cài đặt hình nền
		RectangleShape Background;
		Background.setSize(Vector2f(500.0f, 600.0f));
		Background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);

		//Cài đặt Menu Chính
		window.draw(Background);
		menu.inMenu(mode.width, mode.height, toDraw, HighScore);
		menu.selectedItemIndex = 3;

		//Hiển thị Menu chính 
		for (int i = 0; i < MainMenuComponents; i++)
		{
			if (i == menu.selectedItemIndex)
			{
				menu.mMenu[i].setFillColor(Color::White);
			}
			else
			{
				menu.mMenu[i].setFillColor(Color::Black);
			}
			window.draw(menu.mMenu[i]);
		}
	}

	//Xét TH trạng thái game tiếp theo là Menu chính và trạng thái hiện hành là đang chơi game 
	else if (toDraw == GameState::MainMenu && CurrentGameState == GameState::PlayingBreakOut)
	{
		//Cài đặt hình nền 
		RectangleShape Background;
		Background.setSize(Vector2f(500.0f, 600.0f));
		Background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);
		window.draw(Background);

		//Cài đặt Menu chính 
		menu.inMenu(mode.width, mode.height, toDraw, HighScore);
		menu.selectedItemIndex = 1;

		//Hiển thị Menu chính 
		for (int i = 0; i < MainMenuComponents; i++)
		{
			if (i == menu.selectedItemIndex)
			{
				menu.mMenu[i].setFillColor(Color::White);
			}
			else
			{
				menu.mMenu[i].setFillColor(Color::Black);
			}
			window.draw(menu.mMenu[i]);
		}
	}

	//Xét TH trạng thái game tiếp theo là Menu chính và trạng thái hiện hành là Menu hướng dẫn 
	else if (toDraw == GameState::MainMenu && CurrentGameState == GameState::Instruction)
	{
		//Cài đặt hình nền 
		RectangleShape Background;
		Background.setSize(Vector2f(500.0f, 600.0f));
		Background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);
		window.draw(Background);
		
		//Cài đặt Menu chính 
		menu.inMenu(mode.width, mode.height, toDraw, HighScore);
		menu.selectedItemIndex = 4;

		//Cài đặt hiển thị Menu chính 
		for (int i = 0; i < MainMenuComponents; i++)
		{
			if (i == menu.selectedItemIndex)
			{
				menu.mMenu[i].setFillColor(Color::White);
			}
			else
			{
				menu.mMenu[i].setFillColor(Color::Black);
			}
			window.draw(menu.mMenu[i]);
		}
	}

	//Xét TH trạng thái game tiếp theo là Menu chính và trạng thái hiện hành là Menu chọn chế độ chơi 
	else if (toDraw == GameState::MainMenu && CurrentGameState == GameState::PlayModeSelect)
	{
		//Cài đặt hình nền 
		RectangleShape Background;
		Background.setSize(Vector2f(500.0f, 600.0f));
		Background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);
		window.draw(Background);

		//Cài đặt Menu chính 
		menu.inMenu(mode.width, mode.height, toDraw, HighScore);
		menu.selectedItemIndex = 1;

		//Hiển thị Menu chính 
		for (int i = 0; i < MainMenuComponents; i++)
		{
			if (i == menu.selectedItemIndex)
			{
				menu.mMenu[i].setFillColor(Color::White);
			}
			else
			{
				menu.mMenu[i].setFillColor(Color::Black);
			}
			window.draw(menu.mMenu[i]);
		}
	}


	//Xét TH trạng thái game tiếp theo là Menu Chọn chế độ chơi  và trạng thái hiện hành là Menu chọn màn chơi
	else if (toDraw == GameState::PlayModeSelect && CurrentGameState == GameState::LevelSelect)
	{
		//Cài đặt hình nền 
		RectangleShape Background;
		Background.setSize(Vector2f(500.0f, 600.0f));
		Background.setTexture(&texturemanager.UseTexture("Breakout.png"), false);
		window.draw(Background);
		
		//Cài đặt Menu hiển thị Chọn Chế độ chơi
		menu.inMenu(mode.width, mode.height, toDraw, HighScore);
		if (playmode == PlayMode::Computer)
		{
			menu.selectedItemIndex = 2;
			window.draw(menu.mMenu[0]);
			window.draw(menu.mMenu[2]);
		}
		else if(playmode == PlayMode::Player1)
		{
			menu.selectedItemIndex = 1;
			window.draw(menu.mMenu[0]);
			window.draw(menu.mMenu[1]);
		}
	}

	//Xét TH trạng thái game tiếp theo là Menu Thua  và trạng thái hiện hành là Menu chọn màn chơi
	else if (toDraw == GameState::Losing && CurrentGameState == GameState::LevelSelect)
	{
		window.clear();
	}

	//Xét TH trạng thái game tiếp theo là Menu Thua  và trạng thái hiện hành là Menu chọn màn chơi
	else if (toDraw == GameState::Win && CurrentGameState == GameState::LevelSelect)
	{
		window.clear();
	}
}

		

	




	


