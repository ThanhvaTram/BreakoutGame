#include "TextureManager.h"

//Hàm thêm Texture vào hệ thống
void TextureManager::AddTexture(string fileLocation)
{
	TEXTURE temp;// biến tạm chứa Texture
	temp.textureName = fileLocation;// tên của Texture 
	fileLocation = "Texture/" + temp.textureName;// địa chỉ chứa file sound
	;
	if (!temp.texture.loadFromFile(fileLocation))// nếu không tìm thấy báo lỗi 
	{
		cout << "error when load" << std::endl;
	}
	else
	{
		//Nạp Texture cần thêm vào hệ thống 
		mListTexture.push_back(temp);
	}
}


//Hàm trả về Texture theo tên cần dùng
Texture& TextureManager::UseTexture(string textureName)
{
	vector<TEXTURE>::iterator it;
	Texture temp;
	//Quét toàn bộ vector Texture
	for (it = mListTexture.begin(); it != mListTexture.end(); ++it)
	{
		if (it->textureName == textureName) // tìm thấy Texture có tên trùng với tên nhập vào 
		{
			// Trả về texture có tên cần dùng 
			it->texture.setSmooth(true);
			return it->texture;
		}
	}
	return temp;
}

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}
