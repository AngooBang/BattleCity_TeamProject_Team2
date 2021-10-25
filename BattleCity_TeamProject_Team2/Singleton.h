#pragma once


//template <typename T>
///*static*/ class Singleton
//{
//protected:
//	static T* instance;		// static 멤버 변수
//
//	// 생성자, 소멸자를 직접 호출하지 못하게 할거다.
//	virtual ~Singleton() {};
//
//public:
//	static T* GetSingleton();
//	void ReleaseSingleton();
//};
template <typename T>
/*static*/ class Singleton
{
public:
	virtual ~Singleton() = default;
	static T* GetSingleton()
	{
		static T instance;
		return &instance;
	}
protected:
	Singleton() {}		// 생성자, 소멸자를 직접 호출하지 못하게 할거다.
};



