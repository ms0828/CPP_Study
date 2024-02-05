#include <iostream>
using namespace std;

#pragma region 클래스 템플릿
// typename T를 붙이면 어떤 타입도 다 넣을 수 있음
// 그런데 무조건 typename을 붙여야 하는 것은 아니다.
//		- 변수를 선언하고 (기본 값 초기화도 가능) 아래서 사용할 수도 있다.
// template<> 안에 들어가는건 [골라줘야할 목록]이라고 할 수 있음
// 
// 
// 템플릿 특수화(클래스 버전)
// - 특정 클래스만 예외
// 
#pragma endregion


template<typename T, int SIZE>
// RandomBox<int, 10> vs RandomBox<int, 20>  두 클래스는 완전히 다른 클래스임
class RandomBox
{
public:
	T GetRandomData()
	{
		int idx = rand() % SIZE;
		return _data[idx];
	}
public:
	T _data[SIZE];
};



// 템플릿 특수화(클래스 버전)
// - 특정 클래스만 예외
// 예시) double 타입만 다르게 예외처리 하려면

template<int SIZE>
class RandomBox<double, SIZE>
{
public:
	double GetRandomData()
	{
		cout << "double버전의 RandomBox 특수화" << endl;
		int idx = rand() % SIZE;
		return _data[idx];
	}
public:
	double _data[SIZE];
};

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));


	RandomBox<int, 10> rb1;
	for (int i = 0; i < 10; i++)
	{
		rb1._data[i] = i;
	}
	int value1 = rb1.GetRandomData();
	cout << value1 << endl;



	RandomBox<double, 100> rb2;
	for (int i = 0; i < 100; i++)
	{
		rb2._data[i] = i + 0.5f;
	}
	float value2 = rb2.GetRandomData();
	cout << value2 << endl;


}
