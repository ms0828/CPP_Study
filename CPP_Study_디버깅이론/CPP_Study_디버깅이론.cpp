// CPP_Study_디버깅이론.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
using namespace std;

#pragma region 디버깅

// 조사식, 호출스택
// 중단점에 우클릭하여 조건부를 걸 수 있다. (특정 객체를 보고 싶을 때)
// 
// 실행 중간에 로그를 남기고 싶으면? 
// - 중단점에 우클릭하여 작업 -> 출력 창에 메세지 표시
// 
// 코드 흐름 강제 조작하는 법
// - 중단점 왼쪽으로 끌고 다른 곳에 둘 수 있음
// 
// 
// 
// 
#pragma endregion


void Test2()
{
    int b = 1;
}

void Test1()
{
    int a = 0;
    
    Test2();
}


int main()
{
    int num = 5;

    Test1();
}
