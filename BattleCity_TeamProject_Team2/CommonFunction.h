// CommonFunction.h

#pragma once
#include <Windows.h>
#include <math.h>

inline float GetDistance(const POINTFLOAT& pos1, const POINTFLOAT& pos2)
{
	return sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
		+ (pos1.y - pos2.y) * (pos1.y - pos2.y));
}
inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// 원하는 윈도우 작업영역 설정
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX;	rc.bottom = sizeY;

	// 스타일이 포함된 실제 윈도우 크기 계산
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 계산된 값으로 윈도우를 이동시키면서 크기도 함께 변환
	MoveWindow(g_hWnd, startX, startY,
		rc.right - rc.left, rc.bottom - rc.top, true);
}
inline bool CheckInRect(RECT a, RECT b)
{
	if (a.top <= b.top || a.left <= b.left || a.bottom >= b.bottom || a.right >= b.right)
		return true;
	else
		return false;
}


inline bool CheckCollision(RECT a, RECT b)
{
	if (a.left < b.right && a.top < b.bottom && a.right > b.left && a.bottom > b.top)
		return true;
	else
		return false;
}

