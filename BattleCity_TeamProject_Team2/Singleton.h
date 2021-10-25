#pragma once


//template <typename T>
///*static*/ class Singleton
//{
//protected:
//	static T* instance;		// static ��� ����
//
//	// ������, �Ҹ��ڸ� ���� ȣ������ ���ϰ� �ҰŴ�.
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
	Singleton() {}		// ������, �Ҹ��ڸ� ���� ȣ������ ���ϰ� �ҰŴ�.
};



