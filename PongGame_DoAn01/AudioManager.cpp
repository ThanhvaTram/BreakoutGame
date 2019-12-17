#include "AudioManager.h"


//Hàm phát âm thanh
void AudioManager::PlaySound(string Name, bool IsLoop) // nhập vào tên âm và biến bool cho chế độ phát
{
	vector<SOUND>::iterator i;
	// Dòng for quét toàn bộ mảng âm thanh
	for (i = ListSound.begin(); i != ListSound.end(); i++)
	{
		if (Name == i->SoundName) // Kiểm tra tên âm thanh đang được quét có trùng tên âm nhập vào
		{
			i->Sound.setBuffer(i->FileSound);// nạp bộ nhớ đệm vào biến phát âm
			i->Sound.play();// phát âm
			i->Sound.setLoop(IsLoop);// chỉnh chế độ phát lặp hoặc không lặp
			break;
		}
	}
}

//Hàm thêm âm thanh vào hệ thống
void AudioManager::AddSound(string FileLocation) // tên âm cần thêm
{
	SOUND temp;// biến tạm chứa hiệu ứng sound 
	temp.SoundName = FileLocation;// tên của hiệu ứng sound
	FileLocation = "Sound/" + temp.SoundName;// địa chỉ chứa file sound
	if (!temp.FileSound.loadFromFile(FileLocation))// kiểm tra tính đúng sai của địa chỉ
	{
		cout << "error when load" << std::endl; // thông báo lỗi nếu sai địa chỉ
	}
	else
	{
		ListSound.push_back(temp); //nạp âm vào hệ thống
	}
}

//Hàm chỉnh âm lượng hiện hành
void AudioManager::SetVolume(int value) // giá trị âm lượng nhập vào
{
	vector<SOUND>::iterator i;
	// dòng for quét toàn bộ âm có trong hệ thống
	for (i = ListSound.begin(); i != ListSound.end(); i++)
	{
		i->Sound.setVolume(1.0f*value); // set giá trị âm lượng đang quét bằng giá trị nhập vào
	}
}

//Hàm trả về giá trị âm lượng hiện hành
int AudioManager::GetVolume() 
{
	// trả về giá trị âm lượng hiện hành
	return ((int)round(this->ListSound[1].Sound.getVolume() / 10));
}


//Hàm dừng âm thanh
void AudioManager::StopSound(string Name)// nhập vào tên âm cần dừng phát
{

	vector<SOUND>::iterator i;
	//dòng for quét toàn bộ âm trong hệ thống
	for (i = ListSound.begin(); i != ListSound.end(); i++)
	{
		if (i->SoundName == Name) // kiểm tra tên âm nhập và tên âm đang quét trùng nhau hay không
		{
			i->Sound.stop();// dừng âm đang quét nếu đúng
		}
	}
}
// constructor mặc định
AudioManager::AudioManager()
{
}

// destructor mặc định
AudioManager::~AudioManager()
{
}
