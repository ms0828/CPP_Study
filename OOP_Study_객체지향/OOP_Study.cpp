using namespace std;

#include <iostream>

#pragma region 생성자와 소멸자
//클래스에 소속된 함수들을 멤버함수라고 함
// 이 중에서 특별함 함수 2가지, 시작과 끝을 알리는 함수들 (생성자, 소멸자)
// - 생성자(여러개 존재 가능)
// - 소멸자(오직 1개만)
// 
// 생성자를 명시적으로 만들지 않으면,
// 아무 인자도 받지 않는 [기본 생성자]가 컴파일러에 의해 자동으로 만들어짐
//      + 복사 생성자도 기본으로 만들어짐
// -> 그러나 명시적으로 어떤 생성자를 만들면,
//    자동으로 만들어지던 [기본 생성자]는 만들어지지 않음
// 
// 
// 
#pragma endregion




class Knight
{
public:
    //멤버 함수 선언
    // 멤버 함수는 멤버 변수에 접근 가능

    // [1]기본 생성자 (반환 값 없음)
    Knight()
    {
        cout << "Knight() 기본 생성자 호출" << endl;
    }

    // [2]복사 생성자
    // 자기 자신의 클래스 참조 타입을 인자로 받음
    // 왜 const? -> 인자로 들어오는 기존 knight의 값의 수정을 방지하기 위해서
    Knight(const Knight& knight)
    {
        cout << "Knight() 복사 생성자 호출" << endl;
        _hp = knight._hp;
        _attack = knight._attack;
        _posX = knight._posX;
        _posY = knight._posY;
    }


    // [3]기타 생성자 (인자(초기화할 멤버변수)를 받는 생성자)
    // - 이 중에서 인자를 1개만 받는 기타 생성자를 [타입 변환 생성자]라고 부르기도 함
    // ex) Knight k1;   
    //     k1 = 1; 
    // 이 때 k1 = 1에서 1을 만들 때 int hp가 1인 Knight가 생성되고, 이 Knight를 k1에 복사하는 과정이 일어난다.
    // 
    //  위와 같은 암시적 형변환을 방지하고, 명시적인 용도로만 사용하려면?  -> 생성자 앞에 explicit이란 키워드를 붙인다.
    explicit Knight(int hp)
    {
        cout << "Knight(int) 생성자 호출" << endl;
        _hp = 100;
    }

    //소멸자
    ~Knight()
    {
        cout << "Knight() 소멸자 호출" << endl;
    }

    void Move(int y, int x);
    void Attack();

    void Die()
    {
        _hp = 0;
        cout << "Die" << endl;
    }

public:
    //멤버 변수 선언
    int _hp;
    int _attack;
    int _posX;
    int _posY;
};

void Knight::Move(int y, int x)
{
    _posY = y;
    _posX = x;
}

void Knight::Attack()
{
    cout << "Attack" << endl;
}

int main()
{
    //Instantiate 객체를 만든다.
    // 생성 시, 메모리에는 객체의 멤버 변수 크기만큼 할당된다.

    // k1.Move(x,y); vs Move(&k1,x,y) 어셈블리어 로직 차이
    // Move(&k1,x,y)는 x,y push후에 k1의 주소를 push하여 함수 진입
    // k1.Move(x,y)는 x,y push후에 ecx레지스터에 k1의 주소를 그냥 들고 있음
    // 함수 진입하여 ptr[this] 라는 곳에 ecx를 옮기고 로직 실행
    //      -> 의미있는 차이는 없어보임
    Knight k1(100);
    k1._attack = 10;
    k1._posX = 0;
    k1._posY = 0;
    

    Knight k2(k1);  //복사 생성자 사용
 // Knight k2 = k1도 동일하게 복사 생성자 사용

#pragma region 형변환이란
    //암시적 형변환 -> 컴파일러가 알아서 바꿔치기 함
    int num = 1;
    float f = num;

    //명시적 형변환 -> 개발자가 명시적으로 형변환을 시킴
    int num2 = 1;
    float f2 = (float)num2;
#pragma endregion

    //인자 1개 ex)int _hp 하나를 받는 기타 생성자 (타입 변환 생성자)에 의해 가능한 타입 변환
    Knight k3;
    //k3 = 1;      //1을 할당할 때, _hp = 1인 Knight를 만들고 k5에 복사됨  //지금은 explicit을 붙여서 암시적 형변환 불가능!


}
