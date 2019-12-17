
#ifndef  __TextureManager_H__
#define __TextureManager_H__

//class quản lý các texture 
#include "SFML/Graphics.hpp"
#include "Brick.h"
#include <string>
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;

// cấu trúc 1 Texture
struct TEXTURE
{
	//Tên texture 
	string textureName;

	//Texure tải lên
	Texture texture;

};
class TextureManager
{
protected:
	//vector các Texture có trong hệ thống
	vector<TEXTURE> mListTexture;
public:
	//Hàm thêm Texture vào hệ thống
	//Input: Vị trí file 
	void AddTexture(string fileLocation);

	//Hàm trả về Texture theo tên cần dùng
	//Input: tên texture cần sử dụng 
	//Output: texture có tên trùng tên truyền vào
	Texture& UseTexture(string textureName);

	//Constructor mặc định
	TextureManager();
	//Destructor mặc định
	~TextureManager();
};
#endif //  __TextureManager_H__

