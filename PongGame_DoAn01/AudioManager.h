#ifndef __AudioManager_H__
#define __AudioManager_H__


// class hệ thống quản lý âm thanh
#include "SFML/Audio.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
using namespace sf;
// cấu trúc Sound gồm 3 thành phần chính
struct SOUND
{
	// Tên âm thanh cần phát
	string SoundName;

	// Bộ nhớ tạm chứa âm thanh cần phát
	SoundBuffer FileSound;
	
	//Biến Sound để cài đặt và phát âm thanh
	Sound Sound;

};
class AudioManager
{
private:
	// mảng chứa các âm thanh có trong âm thanh
	vector<SOUND>ListSound;
public:
	// Hàm dùng để phát âm thanh
	// Input: tên âm thanh, chế độ phát
	//Output: âm thanh có tên được phát
	void PlaySound(string Name,bool IsLoop);


	//Hàm thêm âm thanh vào hệ thống
	//Input: Địa chỉ chứa âm thanh
	//Output: âm thanh mới sẽ được thêm vào để sử dụng
	void AddSound(string FileLocation);
	
	//Hàm set âm lượng 
	//Input: giá trị âm lượng
	//Output: âm lượng tổng sẽ theo giá trị mới
	void SetVolume(int value);
	
	//Hàm lấy giá trị âm lượng hiện hành
	//Output:: giá trị âm thanh hiện hành
	int GetVolume();

	//Hàm dừng âm thanh
	//Input: tên âm thanh cần dừng
	//Output: âm thanh có tên nhập vào sẽ bị dừng 
	void StopSound(string Name);
	
	//Constructor
	AudioManager();

	//Destructor
	~AudioManager();
};
#endif

