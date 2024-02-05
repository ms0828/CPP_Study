#include <iostream>
using namespace std;

// 함수 객체
// - 함수처럼 동작하는 객체
// 
// 왜사용하는가?
// - 함수 포인터의 단점 : 완전히 같은 시그니처(리턴,인자 타입)만 사용가능하다.
// 


void HelloWorld()
{
    cout << "HelloWorld" << endl;
}

// 함수 객체
class Functor
{
public:
    void operator()()
    {
        cout << "Functor Test" << endl;
        cout << _value << endl;
    }

    //이렇게 ()오버로딩으로 다양하게 응용
    bool operator()(int num)
    {
        cout << "Functor Test" << endl;
        _value += num;
        cout << _value << endl;

        return true;
    }
private:
    int _value = 0;
};

int main()
{

    //함수 포인터 선언과 사용 복습 (*,& 생략없이 원형으로)
    void (*pfunc)(void);
    pfunc = &HelloWorld;
    (*pfunc)();


    // 함수 포인터의 단점
    // - 시그니처가 안맞으면 사용 불가
    // - 상태를 가질 수 없다. (상태 : 함수에 저장되는 값 ex) int _hp;)
    


    // 함수 객체 (함수처럼 동작하는 객체)
    // - () 연산자 오버로딩이 필요
    // - 상태(멤버변수)를 유지하며 사용할 수 있다.
    // - () 연산자 오버로딩으로 다양하게 응용할 수 있다.

    Functor functor;
    functor();

    bool ret = functor(3);


    //MMO에서 함수 객체를 사용하는 예시
    // 클라 <-> 서버
    // 서버 : 클라가 보내준 네트워크 패킷을 받아서 처리
    //      ex) 클라 : 나 (5,0) 좌표로 이동시켜줘!
    // 이러한 요청을 객체로 만들 수 있음
    //      - 함수 실행 로직(요청)을 만든 시점과 실행할 시점의 분리 가능    (= 커맨드 패턴)
    // 

    
}

