#pragma once
#include <Windows.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

#pragma comment(lib, "winmm.lib")


#define WIN_START_POS_X	10
#define WIN_START_POS_Y	10
#define WIN_SIZE_X	1000
#define WIN_SIZE_Y	900
#define PI 3.14159265357989
#define PI2 (3.14159265357989 * 2)

#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } } 
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }

enum MoveDir { Up, Left, Down, Right, End };

enum class BulletSpeed {Slow = 10, Normal = 15, Fast = 20, End};
enum class EnemyType { Basic, Speed, Power, ArmorGray, ArmorGreen, ArmorYellow, End };
enum class TankType { Player, Enemy };

typedef struct ArgumentFuncPtr
{
	string sceneName;
	string loadingSceneName;
} ARGUMENT_PTR, * LPARGUMENT_PTR;

#include "TimerManager.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;