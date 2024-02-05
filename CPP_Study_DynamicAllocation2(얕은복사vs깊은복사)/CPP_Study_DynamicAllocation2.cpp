#include <iostream>
using namespace std;

// 얕은 복사 vs 깊은 복사  ** 매우 중요 **

class Pet
{
public:
    Pet()
    {
        cout << "Pet()" << endl;
    }

    ~Pet()
    {
        cout << "~Pet()" << endl;
    }

    Pet(const Pet& pet)
    {
        cout << "Pet(const Pet& pet)" << endl;
    }

    Pet& operator=(const Pet& pet)
    {
        cout << "operator=(const Pet&)" << endl;
        return *this;
    }

public:
};

class Player
{
public:
    Player()
    {
        cout << "Player()" << endl;
    }

    Player(const Player& player)
    {
        cout << "Player(const Player&)" << endl;
        _level = player._level;
    }

    Player& operator=(const Player& player)
    {
        cout << "operator=(const Player&)" << endl;
        _level = player._level;
        return *this;
    }

public:
    int _level = 0;

};

class Knight : public Player
{
public:
    
    Knight()
    {

    }

    Knight(const Knight& knight)
    {
        _hp = knight._hp;
        //pet의 깊은 복사 구현
        //_pet = new Pet(*knight._pet);

    }

    Knight& operator=(const Knight& knight)
    {
        cout << "Knight의 명시적 복사 대입 연산자 호출! (부모나 멤버 클래스 복사 대입 연산자는 자동으로 호출되지 않는다.)" << endl;
        _hp = knight._hp;
        //pet의 깊은 복사 구현
        //_pet = new Pet(*knight._pet);

        return *this;
    }

    ~Knight()
    {
        //delete _pet;
    }

public:
    int _hp = 100;
    Pet _pet;       //이렇게 Pet자체를 가지도록 하면, Pet의 생명주기가 Knight와 완전히 동일하게 되어서 관리하기 어려움
    //Pet* _pet;
};


int main()
{
    Pet* pet = new Pet();

    Knight knight1;      //기본 생성자 호출
    knight1._hp = 200;
    //knight1._pet = pet;
    
    

    // 같은 Knight를 복사하고 싶으면?-
    cout << "----------복사 생성자----------" << endl;
    Knight knight2 = knight1;    //복사생성자 호출     // == Knight knight3(knight)


    
    cout << "----------복사 대입 연산자----------" << endl;
    Knight knight3;
    knight3 = knight1; // 복사 대입 연산자


    // 복사 생성자, 복사 대입 연산자는 따로 안만들어 주면 컴파일러가 암시적으로 만들어준다.
    
    // 얕은 복사 - 멤버 데이터를 비트열 단위로 "똑같이"복사 (메모리 영역 값을 그대로 복사)


    // Knight가 pet을 포인터로 갖고 있을 때, 복사된 Knight2,3,4는 Knight1의 똑같은 pet을 가리키게 된다.
    // => 얕은 복사 (포인터는 주소값 바구니 -> 주소값을 똑같이 복사 -> 동일한 객체를 가리키게 됨)
    // Stack : Knight1 [ hp, 0x1000 ]  --> Heap 0x1000 Pet[  ]
    // Stack : Knight2 [ hp, 0x1000 ]  --> Heap 0x1000 Pet[  ]
    // - 어떤 문제점이 있을까?
    // - Knight1,2,3이 소멸될 때 소멸자에 delete pet이 있으면 첫번째 소멸된 Knight 이후로는 없는 객체 포인터를 delete하게 되는 문제 발생
    // 
    // 
    // 객체 복사의 의도라면, Knight1의 펫의 포인터를 복사하면 안되고 펫의 정보가 같은 다른 동일한 펫을 만들어 복사받아야한다. 
    // => 깊은 복사 (포인터는 주소값 바구니 -> 새로운 객체를 생성 -> 상이한 객체를 가리키는 상태가 됨)
    // - 멤버 데이터가 참조(주소) 값이라면, 데이터를 새로 만들어준다. (원본 객체가 참조하는 대상까지 새로 만들어서 복사)
    // Stack : Knight1 [ hp, 0x1000 ]   -> Heap 0x1000 Pet[ ]
    // Stack : Knight2 [ hp, 0x2000 ]   -> Heap 0x2000 Pet[ ]
    // Stack : Knight3 [ hp, 0x3000 ]   -> Heap 0x3000 Pet[ ]

    // 따라서 클래스 안에 참조나 포인터가 있으면, 컴파일러가 암시적으로 만들어주는 복사 생성자, 복사 대입 연산자를 커스터마이징 해야하는 경우가 생김       
  


    //실험 (어떤 과정으로 복사가 일어날까?)
    // - 암시적 복사 생성자 Steps
    // 1) 부모 클래스가 있는 경우, 부모 클래스의 복사 생성자 호출
    // 2) 멤버 클래스가 있는 경우, 멤버 클래스의 복사 생성자 호출 (멤버 클래스 : 멤버 변수로 포인터가 아닌 클래스를 들고 있는 경우)
    // 3) 부모, 멤버 클래스가 없고, 멤버가 기본 타입인 경우 메모리 복사 (앝은 복사)
    // 
    // - 명시적 복사 생성자 Steps
    // 1) 부모 클래스가 있는 경우, 부모 클래스의 기본 생성자 호출
    // 2) 멤버 클래스가 있는 경우, 멤버 클래스의 기본 생성자 호출
    // 
    // 복사 생성자가 언제 호출되고, 호출되지 않는 경우는 언제인지 항상 인지하고 작업하기**
    // => 해당 클래스에 명시적 복사 생성자가 있을 때, Knight(const Knight& knight) : Player(knight) 처럼 부모나 멤버 클래스의 복사 생성자를 따로 호출하지 않으면, 호출되지 않음!!!!!
    // 
    // 
    // - 암시적 복사 대입 연산자 Steps
    // 1) 부모 클래스가 있는 경우, 부모 클래스의 복사 대입 연산자 호출
    // 2) 멤버 클래스가 있는 경우, 멤버 클래스의 복사 대입 연산자 호출 (멤버 클래스 : 멤버 변수로 포인터가 아닌 클래스를 들고 있는 경우)
    // 3) 부모, 멤버 클래스가 없고, 멤버가 기본 타입인 경우 메모리 복사 (앝은 복사)
    // 
    // - 명시적 복사 대입 연산자 Steps
    // 1) 알아서 해주는거 없음 (모두 다 알아서)
    // 

    //결론
    // 객체를 복사한다는 것은 두 객체의 값들을 일치시키려는 것
    //      따라서 기본적으로 얕은 복사 방식으로 동작하게 됨
    // -그러나 깊은 복사가 필요한 경우, 명시적 복사를 사용해야함 (모든 책임을 프로그래머가 위임)

}

