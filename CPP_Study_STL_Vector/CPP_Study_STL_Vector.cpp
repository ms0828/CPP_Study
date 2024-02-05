#include <iostream>
using namespace std;
#include <vector>

#pragma region vector
// STL (Standard Template Library)
// - 프로그래밍 할 때 필요한 자료구조/ 알고리즘을 템플릿으로 제공하는 라이브러리
// 
// 
// 컨테이너 : 데이터를 저장하는 객체 (= 자료구조)
// 
// 
// Vector (동적 배열)  (컨테이너 중 하나) 학습 목표
// - vector의 동작 원리(size/capacity)
// - 중간 삽입, 삭제
// - 처음, 끝 삽입 삭제
// - 임의 접근
// 
// 
// -----------------vector1------------------
// 
// 동적 배열 (배열의 크기를 유동적으로 사용하는 원리)
// - 여유분을 두고 메모리를 할당한다. 
// - 여유분까지 꽉 찼으면, 메모리를 증설한다.
//      새로운 큰 배열을 만들고, 기존 배열의 요소를 복사, 기존 배열 메모리는 delete
// 
// 
// 생각해야할 점들  (아래에 답이  있음)
// (1) 여유분은 얼만큼? 
// (2) 증설을 얼만큼? 
// (3) 기존 데이터는 어떻게 처리?
// 
// 
// vector의 size와 capacity
// - size : 실제 사용 데이터 개수
// - capacity : 여유분을 포함한 용량 개수
//      capacity 증가량 : 이전 capacity의 약 1.5배 씩 여유분을 할당
// 
// 
// 왜 새로운 메모리를 할당받아 옮기는가?
// - 배열은 연속된 메모리이기 때문에, 기존 메모리 이후 메모리가 사용되고 있을 수도 있기 때문이다. 
//      따라서 완전히 새로운 공간에 할당받아 기존 배열을 옮긴다.
// 
// 
// capacity는 왜 1.5배 씩 증가?
//  - 하나 push할 때 마다, 새로운 메모리를 만들고 기존 것을 옮기는 작업의 비용을 줄이기 위해
// 
// 
// 처음부터 capacity의 용량을 설정할 수 있음
// v.reserve(1000);
// 
// 
// 처음부터 size를 조절할 수 있음
// - v.resize(100);       100크기의 메모리에 0으로 초기화
//      or 선언할 때 사이즈와 초기값 설정 가능   veotor<int> v(100,0);
// 
// 
// size가 줄어들어도, capacity는 줄어들지 않는다!!
//      v.clear()해도, capacity는 그대로
// 
// 
// 
// -----------------vector2------------------
// 반복자(Iterator) : 포인터와 유사한 개념, 컨테이너의 원소를 가리키고, 다음/이전 원소로 이동 가능
// 
// 포인터 vs iterator
// - 데이터를 접근하는 것은 동일 (내부적으로 포인터를 들고 있음) (+ Iterator클래스에 포인터 관련 연산자 오버로딩)
// - iterator는 소속(주인)의 정보가 담겨있다.
// * 인덱스 접근은 내부적으로 배열을 들고 있는 컨테이너만 가능! 
// 
// 
// 
// -----------------vector3-------------------
// -중간 삽입/삭제
// -처음/끝 삽입/삭제
// -임의 접근(인덱스 접근) 
// 
// vector는 원소가 하나의 메모리 블록에 연속하게 저장된다!!
// 
// 
// vector의 특징
// - 벡터는 처음/중간 삽입, 삭제가 비효율적이다! (이후/이전 값들을 복사해서 밀어내야함)
//      v.push_back(), v.pop_back()은 있는 반면에 v.push_front 함수가 없는 이유!
// - 대신, 메모리 블록이 연속해서 저장되기 때문에 찾기가 쉽다. 인덱스 접근 용이
//      v[i]가 제공되는 이유!
// 
// 벡터의 중간삽입, 삭제
// v.insert(v.begin() + 2, 5);    //2번째 원소에 5를 삽입
// v.erase(v.begin() + 2);      //2번째 원소를 삭제
// (insert와 erase는 vector<int>::iterator(삽입,삭제한 위치)를 반환한다.)
// 
// 
// 
// 
// 
// 
#pragma endregion

int main()
{
#pragma region vector1
    /*
    vector<int> v;
    v.resize(1000);

    for (int i = 0; i < 1000; i++)
    {
        v.push_back(100);
        cout << v.size() << " " << v.capacity() << endl;
    }*/

#pragma endregion


#pragma region vector2

    /*
    
    vector<int> v(10);
    for (int i = 0; i < v.size(); i++)
    {
        v[i] = i;
    }

    vector<int>::iterator it;
    int* ptr;
    it = v.begin();
    ptr = &v[0];

    // 포인터와 마찬가지로 +a 만큼 증가시키는 것은 (특정 타입에 맞춰서  int : (+-)4byte )주소 연산을 한다는 것
    it++;
    ptr++;
    it += 1;
    ptr += 1;


    vector<int>::iterator itEnd = v.end();
    // itEnd는 쓰레기 값을 갖고 있다?
    // - iterator는 현재 연산 끝나면 다음 메모리를 가리키기 때문에

    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        cout << (*it) << endl;
    }
    // Tip!
    // it++ 보다 ++it이 성능이 좀 더 좋다.
    // it++은 이전 값을 복사해두고 복사된 이전 버전을 반환하기 때문

    */
#pragma endregion


#pragma region vector3
    
    // if 쭉 스캔하면서 3이라는 데이터가 있으면 일괄 삭제하고 싶다
    vector<int> v;
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        int data = *it;
        if (data == 3)
        {
            //v.erase(it);
            // 위 코드가 에러가 나는 이유! - 어셈블리어로 분석
            // v.erase(it)실행 후, it의 proxy를 보면 null로 되어있음 - 소속 컨테이너 정보가 날라감
            // => iterator는 erase(it)하는 순간 iterator가 유효하지 않게 된다.
        
            it = v.erase(it);
            //위 코드는 에러가 나지 않는다. - erase가 삭제된 위치의 iterator를 반환하기 때문
            // but for 증감문에서 ++it이 될 때, 해당 위치는 건너뛰기 때문에, else문에 ++it을 해야한다. 
         
            // 위와같은 이유로 for 문 안에서 v.clear()는 사용X
        }
    }
    



#pragma endregion
}

