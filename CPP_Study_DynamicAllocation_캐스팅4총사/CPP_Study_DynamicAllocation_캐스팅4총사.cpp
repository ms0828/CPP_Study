#include <iostream>
using namespace std;

#pragma region 캐스팅 4총사
// 
// 1) static_cast
// 2) dynamic_cast
// 3) const_cast
// 4) reinterpret_cast
// 
// (int*) (Knight*) 같은 타입변환은 옛날 c스타일
// - c++에서는 좀 더 구체적임을 나타낼 수 있는 4가지 표현 사용
// 


#pragma endregion




class Player
{
public:
    virtual ~Player() {}
};

class Knight : public Player
{
public:

};

class Archer : public Player
{
public:

};


void PrintName(char* str)
{
    cout << str << endl;
}


int main()
{
    // static cast : 타입 원칙에 비춰볼 때 상식적인 캐스팅만 허용해준다 (사용 빈도 가장 높음)
    // - 1) int <-> float
    // - 2) 부모와 자식 관계, Player* -> Knight * (다운캐스팅) (부모에서 자식으로 캐스팅) << 단 안전성 보장 못함

    int hp = 100;
    int maxHp = 200;
    float ratio = static_cast<float>(hp) / maxHp;

    //부모-> 자식이지만 new Knight로 할당받았기에, 상식적으로 말이 돼서 static cast 통과!
    //자식 -> 부모는 당연히 상식적이기에 static cast 가능
    Player* p = new Knight();
    Knight* k1 = static_cast<Knight*>(p);



    // dynamic_cast : 상속 관계에서의 안전 형변환
    // RTTI(RunTime Type Information)일 때 사용 가능  (virtual이 있을 때), (ex. 가상함수테이블) 
    // - virtual 함수를 하나라도 만들면, 객체의 메모리에 가상함수테이블(vftable) 주소가 기입,
    //      (다형성을 활용하는 방식)
    // - 만약 잘못된 타입으로 캐스팅을 했으면, nullptr 반환***** (안전성 Up!)
    //      이를 이용해서 맞는 타입으로 캐스팅을 했는지 확인하기 유용함
    Knight* k2 = dynamic_cast<Knight*>(p);



    

    // const_cast : const를 붙이거나 뗄 때 사용  (실전에서 사용할 일 거의 없음)
    // ex) PrintName은 인자로 str*를 받는데, "Rookiss"는 const 문자열--> const를 떼야한다.
    //  이럴때 const_cast 사용 
    PrintName(const_cast<char*>("Rookiss"));


    // reinterpret_cast (사용 빈도 낮음)
    // 가장 위험하고 강력한 형태의 캐스팅
    // - 포인터랑 전혀 관계없는 다른 타입 변환 등
    __int64 address = reinterpret_cast<__int64>(k2);

    
}

