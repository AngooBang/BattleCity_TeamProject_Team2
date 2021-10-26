#include "ImageManager.h"
#include "Image.h"
#include "TileMap.h"

void ImageManager::Init()
{

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Boom_Effect.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Bullet/Missile_Up.bmp", 9, 12, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Bullet/Missile_Left.bmp", 12, 9, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Bullet/Missile_Down.bmp", 9, 12, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Bullet/Missile_Right.bmp", 12, 9, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Spawn_Effect2.bmp",	256, 64, 4, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Boom_Effect2_Tank.bmp", 160, 32, 5, 1, true, RGB(255, 0, 255));


	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item1.bmp", 64, 64, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item2.bmp", 64, 64, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item3.bmp", 64, 64, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item4.bmp", 64, 64, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item5.bmp", 64, 64, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item6.bmp", 64, 64, true, RGB(255, 0, 255));


	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/GameOver.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Game_Over.bmp", 96, 45, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);


	ImageManager::GetSingleton()->AddImage("Image/backGround2.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/HISocre.bmp", 470, 50, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Player1.bmp", 230, 40, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/PTS.bmp", 90, 40, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/TotalScore.bmp", 360, 40, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Stage_w.bmp", 111, 21, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Number_w.bmp", 120, 42, 5, 2, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage("Image/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));


	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Title.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	//ImageManager::GetSingleton()->AddImage("Image/backGround2.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	//ImageManager::GetSingleton()->AddImage("Image/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));


	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Player/Player.bmp", 512, 256, 8, 4, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Spawn_Effect2.bmp", 256, 64, 4, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Shield.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));


	ImageManager::GetSingleton()->AddImage("Image/TileBackGround.bmp", TILE_MAP_SIZE_X, TILE_MAP_SIZE_Y);
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/SamlpTile1.bmp", 320, 320, 10, 10, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/SmallSamlpTile.bmp", 96, 64, 6, 4, true, RGB(255, 0, 255));


	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/Icon_Enemy.bmp", 30, 30);
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/player1Life.bmp", 60, 60, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/StageFlag.bmp", 60, 60, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Icon/Point.bmp", 80, 16, 5, 1, true, RGB(255, 0, 255));

	//ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Spawn_Effect2.bmp",
	//	256, 64, 4, 1, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage("Image/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Boom_Effect2_Tank.bmp", 160, 32, 5, 1, true, RGB(255, 0, 255));

	//ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Spawn_Effect2.bmp",
	//	256, 64, 4, 1, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage("Image/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Boom_Effect2_Tank.bmp", 160, 32, 5, 1, true, RGB(255, 0, 255));

	//ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Spawn_Effect2.bmp",
	//	256, 64, 4, 1, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage("Image/Enemy.bmp", 512, 384, 8, 6, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddImage("Image/BattleCity/Effect/Boom_Effect2_Tank.bmp", 160, 32, 5, 1, true, RGB(255, 0, 255));

}

void ImageManager::Release()
{
	map<string, Image*>::iterator it;
	for (it = mapImages.begin(); it != mapImages.end();)
	{
		SAFE_RELEASE(it->second);
		// erase에서 리턴값으로 it의 다음 iterator를 돌려주게됨. 계속 대입해서 반복시킴
		it = mapImages.erase(it);

	}

}

Image* ImageManager::AddImage(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	// 이미지를 찾아보고 만약 있으면 추가안함.
	if (FindImage(fileName))
	{
		return nullptr;
	}
	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(fileName, img));

	return img;


}

//void ImageManager::AddImage(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
//{
//	if (FindImage(fileName))
//	{
//		return;
//	}
//	Image* img = new Image;
//	if (FAILED(img->Init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
//	{
//		SAFE_RELEASE(img);
//		return;
//	}
//
//	mapImages.insert(make_pair(fileName, img));
//}

Image* ImageManager::AddImage(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
	if (FindImage(fileName))
	{
		return nullptr;
	}
	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(fileName, img));
	return img;
}

Image* ImageManager::FindImage(const char* fileName)
{
	
	map<string, Image*>::iterator it = mapImages.find(fileName);
	if (it == mapImages.end())
	{
		return nullptr;
	}

	return it->second;
}

void ImageManager::DeleteImage(const char* fileName)
{
	map<string, Image*>::iterator it = mapImages.find(fileName);
	if (it == mapImages.end())
	{
		return;
	}

	SAFE_RELEASE(it->second);		// Image* // Image 동적할당 해제
	mapImages.erase(it);			// 맵에서 노드 삭제



}
