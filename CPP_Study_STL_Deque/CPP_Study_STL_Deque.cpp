#include<deque>
#include<vector>
#include <iostream>
using namespace std;

#pragma region deque
// 
// 시퀀스 컨테이너
// - 데이터가 삽입 순서대로 나열되는 형태
// - vector list deque
// 
// 
// (양방향으로 사용하는 queue)
// deque (배열 기반, vector와 메모리 할당 정책이 조금 다름)
// - vector와 다르게 배열인 기존 메모리를 없애고 새로운 메모리를 할당받는게 아니라
//      기존 메모리를 두고, 이어서 새로운 메모리를 다른 공간에 할당받는다.
// 
// - push_front() 지원하고, 임의 접근 가능
// 
// 
// 
// 처음/끝 삽입/삭제 
// - 빠르다.
// 
// 중간 삽입/삭제
// - vector와 마찬가지로 중간 값을 삭제하면, 빈 공간을 당겨와서 채운다.
// - vector와 마찬가지로 느리다.
//      중간에 새로운 배열 메모리를 만들고 삽입하면 되지않나? -- 불가 : 임의접근이 불가능해짐
// 
// 
// iterator의 * 연산자를 살펴보면 block을 먼저 찾고, 인덱스를 찾아 접근함
// 
// 
// 
// 

#pragma endregion

int main()
{
    vector<int> v(3, 1);
    deque<int> dq(3, 1);



    // vector
    // [1 1 1]  ---- 삭제
    // [1 1 1 2 2]
    // 
    // deque
    // [    3 3]
    // [1 1 1 2] ---- 유지
    // [2      ]
    // 

    v.push_back(2);
    v.push_back(2);

    dq.push_back(2);
    dq.push_back(2);

    dq.push_front(3);
    dq.push_front(3);
    
}

