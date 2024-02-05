#include <iostream>
using namespace std;

#pragma region 함수 템플릿
// 템플릿
// - 함수나 클래스를 찍어내는 틀로 2가지로 나뉜다.
// 1) 함수 템플릿
// 2) 클래스 템플릿
// 
// 
// 
// 함수 템플릿
// - 갖가지 타입의 변수를 출력하는 Print가 있다고 가정
// - 출력할 다른 타입이 생길 때마다 Print를 오버로딩해야하는가? - 함수 템플릿 등장
// - template<typename T>  or template<class T> : 템플릿 선언  (typename == class)
// - 컴파일 단계에서 컴파일러가 사용한 타입에 맞춰 생성
// 
// 
// 
// 템플릿 특수화
// class는 cout << 연산자를 지원하지 않기 때문에 cout으로 출력 시, 빌드 실패
// - 1. << 연산자 오버로딩 방법
// - 2. 템플릿 특수화  (어떤 특정 타입의 template만 예외 처리 할 때)
// 
#pragma endreigon


template<typename T>
void Print(T a)
{
    cout << a << endl;
}


template<typename T>
T Add(T a, T b)
{
    return a + b;
}


// 2개 이상 타입의 template
template<typename T1, typename T2>
void Print(T1 a, T2 b)
{
    cout << a << "," << b << endl;
}


class Knight
{
public:

public:
    int _hp = 100;
};

// 템플릿 특수화 (특정 타입의 예외처리)
//1. 특정 연산자 오버로딩 버전
ostream& operator<<(ostream& os, const Knight& k)
{
    os << k._hp;
    return os;
}

//2. 템플릿 특수화 버전
template<>
void Print(Knight a)
{
    cout << "Knight!!!!!!!!(템플릿 특수화)" << endl;
}


int main()
{
    Print(50);

    
    // 템플릿 특수화 예시
    Knight k1;
    Print(k1);

}
