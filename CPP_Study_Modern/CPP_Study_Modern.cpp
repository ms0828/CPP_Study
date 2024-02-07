#include<vector>
#include <iostream>
using namespace std;

#pragma region auto
// auto ( 형식 연역 (type deduction) )
// 컴파일 단계에서 자료형을 찾아줌
// - auto a = 3;
// 
// 
// 그럼 무조건 auto로 사용???
// - 비추천 : 코드의 가독성이 떨어진다.
// - Pair<int, Knight> 같은 타이핑이 긴 자료형이나 for문의 삼항문에서 적절히 사용
// 
// 
// &(참조)나 const를 auto로 받을 때 주의!
// - 그냥 auto는 const나 참조를 무시하고 일반 타입으로 받는다
// => auto& or const auto로 명시적으로 받아야한다.
// 
#pragma endregion

#pragma region 중괄호 초기화{}
// 
// 자료형 선언에 { } 로 값을 초기화하는 문법
// 
// 장점
// - vector와 같은 컨테이너에 효과적
// - 축소 변환 방지
// 
// 컨테이너나 클래스에 어떤 원리로 { } 안에 값들을 넣을 수 있는건가?
// - initializer_list<>을 인자로 받는 생성자가 만들어짐
// 
// 
// 기타 생성자와 initializer_list 생성자 중 initializer_list 생성자가 우선순위가 더 높다.
// - 단점 : 혼란을 줄 가능성이 있다.
// 
// 
// 중괄호 초기화는 아직도 호불호가 갈리는 문법!!  - 무조건 좋은게 아님
// 

class Knight
{
public:
    Knight()
    {

    }

    // 다음과 같은 생성자가 있으면 중괄호 초기화가 먼저? 아님 기타 생성자가 먼저?
    // => Knight(initializer_list li)가 우선순위가 높다!!
    Knight(int a, int b)
    {

    }

    Knight(initializer_list<int> li)
    {
        cout << "Knight(initializer_list li) " << endl;
    }
};


#pragma endregion

#pragma region nullptr
// (NULL은 0과 같음)
// 왜 0이나 NULL을 안쓰고  nullptr을 쓸까?
// - 가독성을 위해
// - int와 * 타입을 인자로 받는 함수오버로딩 문제 
//      Test(void* ptr) or Test(int a) 두 함수중 Test(NULL)을 호출하면 Test(int a)가 호출된다!
// 
// 
// nullptr 구현 부분
// operator T* () 은 형변환 연산자 재정의로 특수한 문법이 있다.
// (operator 앞에 반환값이 없는 이유)
// 강의 코드 해석 - T*으로 반환될 상황이 있을 때, 형변환 연산자를 구현한 Nullptr이 사용될 수 있음.
// 
#pragma endregion

#pragma region using
// typedef에서 개선된 문법
// - 가독성과 직관성
// typedef __int64 id;      ->      using id = int;
// typedef void (*MyFunc)();    ->      using MyFunc = void(*)();
// 
// - template 사용 가능
//  template<typename T>
//  using List = std::list<T>;
// 
#pragma endregion

#pragma region enum class
// (scoped enum)
// 기존의 enum이랑 enumclass(scoped enum)은 장단점이 갈림
// 
// enum class 장점
// - 이름공간 관리
//      기존의 enum앞에 PT_ 같은 별칭을 붙이는 이유
//      기존의 enum은 전역으로 사용되서, enum에서 사용한 이름은 밖에서 쓸 수 없다!
//      
// 
// - 암묵적인 변환 금지
//      밑에와 같이 암묵적인 변환 금지됨  (같은 int형도 마찬가지로 금지) (따라서 불편한 점도 있음)
//      double value = ObjectType::Player;
// 


// 기존의 enum (unscoped enum)
// - PlayerType같은 enum의 이름은 사실상 필요없음 (관리상일 뿐)
// double or int    value = PT_Knight;가 통과
enum PlayerType
{
    PT_Knight = 5,
    PT_Archer,
    PT_Mage
};

// enum 클래스
// - 스코프 안에서만 유효
// =, << 같은 연산자를 사용할 때 static_cast를 사용해야하는 번거로움
enum class ObjectType
{
    Player,
    Monster,
    Projectile,
};


#pragma endregion

#pragma region delete (삭제된 함수)
// 특정 함수 호출을 막으려면
// ex) NullPtr 구현 중, operator& 같은 주소 연산자를 막을 때
// 
// 
// 설명 예시 - Mage의 복사 연산자를 막아보자

class Mage
{
public:
    void operator=(const Mage& m) = delete;

// 기존은 정의되지 않은 함수 선언을 private에 넣어서 막음
private:
    //void operator=(const Mage& m);4

public:
    int _hp = 100;
};
#pragma endregion

#pragma region override, final
// 
// main 함수 code로 설명
// 
class Player
{
public:
    virtual void Attack()
    {
        cout << "Player Attack!" << endl;
    }
};

class Archer : public Player
{
public:
    //재정의 (override)
    virtual void Attack() override
    {
        cout << "Archer Attack!" << endl;
    }

};

#pragma endregion

#pragma region 오른값 참조와 std::move
// *** 코어 라이브러리를 만들 때 자주 활용
// modern cpp로 넘어오는 가장 핵심적인 변화
// 
// 왼값(l-value) vs 오른값(rvalue)
// l-value : 단일식을 넘어서 계속 지속되는 개체
// r-value : l-value가 아닌 나머지 (임시 값, 열거형, 람다, i++ 등)

int a = 3;     // a는 왼 값  3은 오른 값

class Fighter
{
public:

public:
    int _hp = 100;
};

void TestFighter_Copy(Fighter fighter) { }
void TestFighter_LValueRef(Fighter& fighter) { }
void TestFighter_ConstLValueRef(const Fighter& fighter) { }
void TestFighter_RValueRef(Fighter&& fighter) { }       //매개 변수 타입에 &을 붙이면 오른값 참조가 됨
// 이동 대상! - 원본을 넘겨주되 더 이상 사용하지 않을 것이라는 힌트가 내제 (받은 원본을 맘대로 사용할 수 있다는 hint)
// Fighter&& fighter처럼 오른 값 참조를 받을 때, Fighter 클래스에서 이동 생성자 또는 이동 대입 연산자가 만들어지고 실행된다!  (복사 생성자, 복사 대입 연산자가 아님!!)
// <어떤 장점?>
// - 얕은 복사(원본으로 받아온 객체의 멤버함수를 그대로 나의 멤버 변수에 복사하는 얕은 복사)와 깊은 복사(복사 대상으로 받아온 원본(Player)의 펫을 내 *pet으로 할당할 때 생기는 문제점, 이에 대한 해결 방안으로 Pet* pet = new pet(원본._pet) 으로 할당하는 깊은 복사 <동작이 무겁다!>)
// => 결국, 복사가 아닌 *이동(이전)*에 많이 사용된다.
// 
// 
// std::move()    (오른값 참조 캐스팅)     static_cast<오른값 참조>를 쉽게 타이핑 할 수 있도록 지원하는 문법
// f2 = static_cast<Fighter&&>(f1);     ->      f2 = std::move(f1);
// 
// 
// 결국 원본을 유지하지 않아도 될 때, 복사를 빨리 할 수 있는 방법이다!
//      => 얕은 복사로 모두 꺼내쓴다!
// (코어 라이브러리 제작에 많이 사용되어 modern cpp 부터 속도가 좀 빨라졌음)
// (클라이언트 만들 때 많이 사용되진 않음)

#pragma endregion

int main()
{
#pragma region auto
    /*
    auto a = 123;


    // 주의
    // - 기본 auto는 const, &(참조) 무시!!!!
    int& ref = a;
    const int cst = a;

    auto test1 = ref;
    auto test2 = cst;
    // -> test1과 test2는 일반 int이다.
    
    // 만약 auto로 &나 const로 받고 싶으면
    auto& test3 = a;
    const auto test4 = a;
    */
#pragma endregion

#pragma region 중괄호 초기화{}
    /*
    // 기존의 초기화 문법
    int a = 0;
    int b(0);
    
    // 중괄호 초기화
    int c{ 0 };     

    Knight k1;
    Knight k2 = k1; //복사 생성자 (대입 연산자x)
    Knight k3{ k2 };

    // 장점
    // 
    // 1. 컨테이너와 같은 자료형을 초기화할 때 효과적
    vector<int> v1{ 1, 2, 3 };      // 1, 2, 3을 push한 것과 똑같음

    // 2. 축소 변환 방지  (ex: double 자료형에 int타입 정수로 초기화 할 때) 
    int x = 0;
    // double y(x); // 일반 괄호 초기화 - 축소 변환 방지 X
    double y{ x };  // 중괄호 초기화는 축소 변환을 방지해준다.
    
    */
#pragma endregion

#pragma region override

    Archer* ac = new Archer();
    Player* p = ac;
    ac->Attack();       //archer의 attack 호출
    p->Attack();        //player의 attack 호출 (player의 포인터로 archer를 받아 관리하기 때문)

    //만약 p->Attack을 했을 때, 원본 클래스(자식)의 함수가 호출되게 하려면?
    // 기존 : Player의 Attack()에 virtual 키워드 붙이기
    //      자식의 오버라이딩한 Attack()에 암묵적으로 모두 virtual이 붙게됨
    // 
    // 최초로 virtual을 사용한 클래스를 찾을 때 불편한 문제
    //      대체 이 함수는 누구부터 선언한 함수인가?? (어디서 부터 업캐스팅을 해야하냐!!)
    //      - virtual 만으로는 누가 최초로 선언하고, 어디서부터 물려받은 함수인지 파악하기 어려움
    //      => 대안으로 override 문법 탄생
    // 
    // override
    // 재정의 함수 뒤에 override 키워드를 붙인다.
    // virtual void Attack() override
    // {
    //      cout<< "Archer Attack()" << endl;
    // }
    // 
    // final  : 내 밑 자식으로 더 이상 해당 함수에 오버라이딩을 허용하지 않음
    // virtual void Attack() final
    // {
    //      cout<< "Archer Attack()" << endl;
    // }

#pragma endregion

#pragma region 오른값 참조

    Fighter f;

    TestFighter_Copy(f);
    TestFighter_LValueRef(f);

    // 밑에 코드는 왼 값이 아니기에 오류가 뜸
    // TestFighter_LValueRef(Fighter());
    // 오른 값은 임시로 사용되고 버려질 애라 함수 내부에서 값을 수정하는게 헛지거리로 판단하고 막아놓음


    // 위와같은 이유로 인자에 const가 붙으면 가능 (읽기 위한 용도로 생각하고 문법적으로 허용해줌)
    TestFighter_ConstLValueRef(Fighter());
    // 그러나 const가 아닌 멤버함수를 사용하는 로직이 있으면 안된다는 불편함


    // 오른 값 참조 사용 예시
    TestFighter_RValueRef(Fighter());
    // 왼 값은 인자로 불가능!


    // 오른 값이라고 무조건 다 임시 객체라는건 아니다!
    // 경우에 따라 왼 값이 "이동(이전)" 되며 복사가 필요할 때 사용됨!
    //TestFighter_RValueRef(static_cast<Fighter&&>(f));

#pragma endregion


}