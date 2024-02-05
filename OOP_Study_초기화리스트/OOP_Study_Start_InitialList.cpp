using namespace std;
#include <iostream>

#pragma region 초기화 리스트
// 멤버 변수 초기화? - 다양한 문법 존재
// 
// * 초기화를 왜 해야하는가?
// - 스택 메모리 구조 상, 이전에 다른 코드가 현재 사용할 메모리를 어지럽혔을 확률이 있다!
//  => 그래서 초기화가 필요하다!  (이전 쓰레기 값이 로직에 영향을 줄 수 있으니까!) (특히 포인터 등 주소 값이 연루되어 있을 경우 위험!)
// 
// Knight k를 선언후 _hp를 초기화하지 않고 k._hp를 출력했을 때, 기본 생성자가 없으면 에러가 난다?
// - 컴파일러가 초기화 (생성자)를 권고하는 것으로 이해하면 됨
// 
// 
// 초기화 방법
// - 생성자 내에서
// - 초기화 리스트
// - C++11 문법 (클래스 내 멤버변수에서 바로 int _hp = 100; 처럼 초기화 하는 방법)
// 
// 
// 1. 생성자 내에서
// Knight()     //생성자
// {
//      _hp = 100;
// }
// 
// 2. 초기화 리스트
// - 일단 상속 관계에서 원하는 부모 생성자 호출할 때 필요하다.
// Knight() : Player(1), _hp(100)    //생성자 이름 뒤에 붙이는 방법
// {
//      
// }
// 
// 
// - 1과 2는 int같은 기본 타입 같은 경우, 별 차이 없음
// - 멤버 타입이 클래스인 경우 차이가 난다. (클래스가 클래스를 멤버 변수로 갖고 있는 경우)
//  => 멤버 타입이 클래스인 경우, 초기화 리스트 문법으로 초기화를 하는 것이 좋다! <= 결론 
// 
// 이유 
// - 클래스가 멤버 변수로 다른 클래스를 갖고 있을 때, 멤버 변수 선언 자체로 인해 선처리 영역 때 Inventory() 기본 생성자가 호출 되고
// - 이어서 생성자에서 Inventory를 초기화 할 때, 또 다른 Inventory가 생성된다. (기존 선처리 영역에서 만들어진 Inventory는 소멸)
//  => 생성자 이름 뒤에 : 부모 클래스(기타 생성자) 처럼, 선처리 영역에서 1번만 처리하기 위해 초기화 리스트 문법을 사용한다!!!! 
// 
// 
// // Knight() : Player(1), _hp ,_inventory(20) 
// {
//      //이렇게 초기화 리스트를 사용하면, 선처리 영역 때 선언으로 인한 Inventory() 기본 생성자가 호출 되지 않고, 한 번만 생선된다.
// }
// 
// 초기화 리스트를 사용해야만 하는 또 다른 경우
// - 참조나 const 같이, 선처리 영역 때 꼭 초기화를 해줘야 하는 경우
// - 선언하고 생성자 안에서는 이미 선처리 영역 때 생성이 끝났기 때문에, 초기화 불가!!

#pragma endregion



#pragma region 초기화 리스트 코드
class Inventory
{
public:
    Inventory() { cout << "Inventory()" << endl; }
    Inventory(int size) { cout << "Inventory(int size)" << endl; _size = size; }

    ~Inventory() { cout << "Inventory 소멸자 호출" << endl; }
public:
    int _size = 10;
};


class Player
{
public:
    Player(){}
    Player(int id){}
};


class Knight : public Player
{
public:
    // : Player(int id) 기입하지 않으면, 선처리 영역 때 Player 기본생성자 호출
    Knight() : Player(1), _hp(100), _inventory(20)      //멤버 변수 이런 방법으로도 초기화 가능 (초기화 리스트)
    {
        _hp = 100;


        //생성자에서 inventory를 초기화할 때 다음과 같은 과정이 일어남!! 
        //_inventory = Inventory(20);      // <= 코드

        // 멤버변수 선언으로 인한 선처리 영역의 Inventory() 기본 생성자가 호출되고
        // 이어서 생성자 초기화에 의한 Inventory(int size) 생성자가 2번 호출!!!
        // 선처리 영역에서 생성된 Inventory는 필요없으니, 이 Inventory의 소멸자가 호출되고, 생성자 초기화에서 생성된 Inventory가 덮어씌어짐
        // => Knight는 1개인데 Inventory는 2번 생성되었다!! (물론 하나는 덮어씌어지면서 소멸)
        
    }

public:
    int _hp;

    // 클래스를 멤버 변수로 들고 있을 때
    Inventory _inventory;
    // - Knight가 만들어진 동시에, 선처리 영역에서 Inventory가 같이 만들어짐
    // - Inventory의 기본 생성자가 호출됨!!
    // - Knight가 소멸될 때, Inventory도 같이 소멸 (Inventory의 생명주기)

    // => 그러나 초기화 리스트로 초기화하는 방법을 사용하면, 위와 같은 방식이 일어나지 않음
};
#pragma endregion



int main()
{
    Knight k;

    cout << k._hp << endl;
}
