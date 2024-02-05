using namespace std;
#include <iostream>

// 객체지향 마무리

// 1. struct vs class (종이 한 장 차이)
// default 접근 지정자가 다름
// - struct : public
// - class : private
// 
// -> struct는 그냥 구조체(데이터 묶음)을 표현하는 용도
// -> class는 객체 지향 프로그래밍의 특징을 나타내는 용도
//
// 
// 2. static 변수, static 함수
// 공통된 값으로 유지되는 변수는 static으로 유지 (해당 클래스의 객체들이 공용으로 사용)
// - static은 객체와 함께 메모리가 스택에 올라가는 것이 아님
// - 초기화 하면 .data, 초기화 안하면 .bss  ==> 데이터 영역에 올라감
// - 생명주기 : 프로그램 시작, 종료 (메모리에 항상 올라가 있음)
// - 그러나 함수 안에 선언했다면, 함수 안에서만 접근 가능
// - 선언이나 초기화 한 번 하면, 그 static 변수를 선언하고 있는 함수를 다시 호출해도 초기화하지 않음
// 
//
struct TestStruct
{
    int _a;
    int _b;
};

class TestClass
{
    int _a;
    int _b;
};

class Marine
{
public:
    int _hp;
    static int s_attack;

public:
};

int Marine::s_attack = 0;           //외부 선언

int main()
{
    Marine m1;
    m1._hp = 40;
    Marine::s_attack = 6;
    //m1.s_attack = 3;
 
    Marine m2;
    m2._hp = 40;
    //m2.s_attack = 6;

    cout << Marine::s_attack << endl;

}
