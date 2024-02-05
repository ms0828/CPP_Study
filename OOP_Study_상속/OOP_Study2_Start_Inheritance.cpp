using namespace std;
#include <iostream>

// 객체지향의 대표적인 3가지 속성
// - 상속성
// - 은닉성
// - 다형성


#pragma region 상속
// 상속 시, 생성자와 소멸자
// - 생성 시, 부모 생성자 -> 자식 생성자
// - 소멸 시, 자식 소멸자 -> 부모 소멸자
#pragma endregion


#pragma region 은닉(Data Hiding) = 캡슐화(Encapsulation)
// 왜 은닉하는가?
// - 위험하고 건드리면 안되는 경우
// - 다른 경로로 접근하길 원하는 경우
// 
// 접근 지정자
// - public : 모두 공개
// - protected : 자식들에게만 허락
// - private : class 내부에서만
// 
// 캡슐화
// - 연관된 데이터와 함수를 논리적으로 묶어놓은 것
// 
// 상속 접근 지정자  (상속 접근 지정자를 사용하지 않으면 자동으로 private임!) (주로 public을 사용)
// - 다음 세대한테 부모님의 유산을 어떻게 물려줄지?  (but 거의 public만 사용한다)
// - public : 부모님의 유산 설계 그대로 - 부모의 public은 public으로, protected는 protected로
// - protected : 내 자손들에게만 물려줌 - 부모의 public도 protected로 
// - private : 나만 쓰고 자손들에게는 안 물려줌 - 부모의 public도 private로

#pragma endregion


#pragma region 다형성(Polymorphism) **********
// 겉은 똑같은데, 기능이 다르게 동작한다.
// - 오버로딩 (함수 중복 정의 = 함수 이름의 재사용 (매개변수 개수, 타입 중복 정의)
// - 오버라이딩 (재정의 = 부모 클래스의 함수를 자식 클래스에서 재정의)
// 
// 
// 바인딩 (ex : 객체의 함수를 어떤 클래스의 함수에 매핑하나?) 
// - 정적 바인딩 : 컴파일 시점에 결정  (일반 함수는 정적 바인딩 사용)
// - 동적 바인딩 : 실행 시점에 결정    (상위 클래스를 인자로 설정해도, 자식 클래스를 매개변수에 넣고 자식 클래스의 함수를 호출할 수 있는 맥락)
//      * 동적 바인딩을 원한다면?(상위 클래스로 원본 객체의 함수를 실행하고 싶으면?) -> 가상 함수
//  
// 
// 동적 바인딩 분석 - 실체 객체가 어떤 타입인지 어떻게 알고 알아서 가상함수를 호출해준걸까?
//  가상함수 테이블
// - 클래스에 virtual 함수가 있으면, 객체가 메모리에 올라갈 때, 처음 부분에 가상 함수 테이블 (8바이트(64))이 올라간다.
//      -> MovePlayer(Player* p) 에 매개변수가 push 될 때, 가상 함수 테이블에 실제 전달된 특정 클래스의 가상 함수 주소 값이 올라감
//  - 따라서 MovePlayer()함수의 Player->VMove를 호출하면, (어셈블리어) 가상 함수 테이블(주소 값)에 가서, 특정 클래스의 함수를 call하게 된다. 
//  
// 
// - 그럼 특정 클래스의 가상 함수 주소값을 나타내는 vftable은 언제 채워지나?
//      -> 생성자 선처리 영역에 자신의 vftable 주소를 채워준다. 
//      -> 상속 시, vftable에 부모 클래스의 가상함수 주소값이 자식 클래스 가상함수 주소값으로 덮어 씌어진다.
//
// 
// 부모 클래스에서 순수 가상 함수 : 구현은 없고, 인터페이스만 넘기고 싶으면 (자식에서 재정의 강제)
// - virtual void VAttack() = 0  혹은 abstract void VAttack (인스턴스 불가)
//
#pragma endregion


#pragma region 상속 코드  (+다형성 동적 바인딩)
class Player
{
public:
    Player()
    {
        _hp = 100;
        _attack = 10;
        _defence = 5;
        cout << "Player 기본 생성자" << endl;
    }

    Player(int hp)
    {
        _hp = hp;
        _attack = 10;
        _defence = 5;
        cout << "Player hp 기타 생성자 (타입 변환 생성자)" << endl;
    }

    void Move() { cout << "Player Move 호출" << endl; };
    void Attack() { cout << "Player Attack 호출" << endl; };
    void Die() { cout << "Player Die 호출" << endl; };



    //다형성 - 동적 바인딩 !! -> 가상함수 선언 ************
    //vftable (가상함수테이블)에 [VMove] [VDie]가 올라감 (순차적으로) 
    //      + 하지만 자식 클래스에 가상 함수가 있으면, vftable에 자식 클래스의 가상함수 주소가 덮어씌어짐
    virtual void VMove() { cout << "Player VMove 호출" << endl; } ;
    virtual void VDie() { cout << "Player VDie 호출" << endl; };


    ~Player()
    {
        cout << "~Player 소멸자 호출" << endl;
    }


public:
    int _hp;
    int _attack;
    int _defence;
};


class Knight : public Player
{
public:
    //생성자
    Knight()        //어셈블리어 분석하면 {} 전에(선처리 영역) 부모의 기본 생성자를 호출
    {
        _stamina = 50;
        cout << "Knight 기본 생성자" << endl;
    }

    // 객체 생성 시, 부모의 특정 생성자를 지목해서 호출하고 싶다면?
    Knight(int stamina) : Player(100)
    {
        _stamina = stamina;
        cout << "Knight stamina 기타 생성자(타입 변환 생성자) 호출" << endl;
    }

    
    //재정의 
    void Move() { cout << "Kngiht Move 호출" << endl; };


    //소멸자
    ~Knight()   //어셈블리어 분석하면 {} 후에(후처리 영역) 부모의 소멸자를 호출
    {
        cout << "~Knight 소멸자 호출" << endl;
    }

public:
    int _stamina;

};

#pragma endregion


#pragma region 은닉(캡슐화) 코드
//위험해서 건드리면 안되는 경우 - 은닉(캡슐화)
class Car
{
public:
    void MoveHandle() {};
    void PushPedal() {};
    void OpenDoor() {};

    void TurnKey()
    {
        RunEngine();
    }

protected:
    void RunEngine() {};    //엔진 구동

private:
    void DisassembleCar() {};   //차 분해
    void ConnectCircuit() {};   //전기선 연결

};

class SuperCar : public Car  //상속 접근 지정자
{
public:
    void PushRemoteController()
    {
        RunEngine();
    }
};

//다른 경로로 접근하길 원하는 경우 - 은닉(캡슐화)
class Berserker
{
public:
    //Getter, Setter
    int GetHp() { return _hp; }

    void SetHp(int hp)      //캡슐화 예시 (연관된 데이터와 함수를 논리적으로 묶어놓은 것)
    {
        _hp = hp;
        if (_hp <= 50)
            SetBerserkerMode();
    }

private:
    //사양 : 체력이 50이하로 떨어지면 버서커 모드 발동
    void SetBerserkerMode()
    {
        cout << "버서커 모드 발동" << endl;
    }

private:
    int _hp = 100;

};

#pragma endregion


#pragma region 다형성 코드
class Mage : public Player
{
public:
    void Move() { cout << "Mage Move - Player Move를 오버 라이딩" << endl; }

    //가상 함수는 재정의를 하더라도 가상 함수다!! (자식에서 virtual 안써도 가상함수로 판별)
    virtual void VMove() { cout << "Mage VMove - from : Player의 virtual VMove" << endl; }

public:
    int _mp;

};

//정적 바인딩 (컴파일 단계에서 결정) (일반 함수) (Player는 Player로 해석)
void MovePlayer(Player* p)
{
    p->Move();
}

//동적 바인딩 (가상함수)
void VMovePlayer(Player* p)
{
    p->VMove();
}

#pragma endregion



int main()
{
#pragma region 상속
    //(상속)instantiate 시 메모리 (아래 Kngiht k 생성 시)
    // [ Player(12byte) ] + [ Knight(4byte) ]   => 16byte
    // 
    // 상속 시, 생성자와 소멸자
    // - 생성 시, 부모 생성자 -> 자식 생성자
    // - 소멸 시, 자식 소멸자 -> 부모 소멸자
    // 

    Knight k(50);

    /*k.Move();
    k.Attack();
    k.Die();*/

#pragma endregion

#pragma region 은닉(캡슐화)
    Car car;

    Berserker b;
    b.SetHp(20);

#pragma endregion

#pragma region 다형성
    Mage m;
    m.Move();   //Mage의 Move 호출 - 오버 라이딩

    //정적 바인딩
    //MovePlayer(&m);  //player.Move가 호출 (매개변수 타입이 Player이기 때문)

    //동적 바인딩
    VMovePlayer(&m);  //Mage.VMove가 호출 

#pragma endregion

}
