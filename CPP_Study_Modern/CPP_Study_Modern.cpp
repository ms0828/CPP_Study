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


#pragma region 전달 참조 (forwarding reference)
// 모던 CPP 이전 기존 이름은 보편 참조(universal reference)
// 
// &&를 두 번 -> 오른값 참조
// 
// &가 두번 등장하면 무조건 오른값? X
// 
// -----아래 코드 예시 확인-----
// 
// 왼값, 오른값을 따로 받는 버전을 만들면 되는데, 왜 이런 문법을 지원하는가??
// - ex) template 함수 인자의 개수가 하나만 늘어나도 2x2 = 4개의 버전을 만들어야함
// 
// 
// 
// => 전달 참조는 forward를 사용하면 된다!
// 
// 

class Knight2
{
public:
    Knight2() { cout << "기본 생성자" << endl; }
    Knight2(const Knight2&) { cout << "복사 생성자" << endl; }
    Knight2(Knight2&&) noexcept { cout << "이동 생성자" << endl; }

};

void Test_RValueRef(Knight2&& k)    //오른값 참조 변수를 받는 함수
{
    
}

void Test_Copy(Knight2 k)
{

}

// 형식 연역이 일어나는 template나 auto에서 전달 참조가 일어나는 예시
template<typename T>
void Test_ForwardingRef(T&& param)      // T&&에 const나 부가적인 것을 붙이면 전달 참조로 동작되지 않음
{
    // TODO


    // 헷갈리기 쉬운 부분
    Test_Copy(param);       //main 함수 코드대로, Test Copy 함수가 받는 T&& param이 오른값으로 전달될지라도, param 자체는 왼값(재사용가능)이기 때문에
    //                         Test_Copy()에 들어가는 param은 왼값으로 동작한다. Knight2의 이동 생성자가 아닌, 복사 생성자가 실행됨!!
    // => 오른값 참조로 Tset_ForwardingRef를 전달했지만, T&& param 자체는 왼값이기 때문에 Test_Copy에 param을 전달할 때는 std::move를 해줘야 의도한 오른값 참조 전달이 된다.



    // 사용 예시)
    // Test_ForwardingRef 함수에서 param이 왼값으로 전달되었다면, Test_Copy(param) 처럼 복사하는 형태로 사용할 것임
    // param이 오른값으로 전달되었다면, Test_Copy(std::move(param)) 처럼 오른값 참조로 유지하며 사용할 것임
   
    // -> 위 두 케이스를 하나로 통일하는 문법!!!
    Test_Copy(std::forward<T>(param));     //전달 참조를 받아 사용할 때는 std::forward사용
    //위 결과로 왼값 전달 -> 복사 생성자 실행 , 오른값 전달 -> 이동 생성자 실행됨
}

#pragma endregion

#pragma region 람다
// 함수 객체를 빠르게 만드는 문법
// 코드 참조
// [ 캡처 ] ( 인자값 ) { 구현부 }

enum class ItemType
{
    None,
    Armor,
    Weapon
};

enum class Rarity
{
    Common,
    Rare,
    Unique
};

class Item
{
public:
    Item() {}
    Item(int itemId, Rarity rarity, ItemType type) : _itemId(itemId), _rarity(rarity), _type(type)
    {

    }

public:
    int _itemId = 0;
    Rarity _rarity = Rarity::Common;
    ItemType _type = ItemType::None;
};


#pragma endregion

#pragma region 스마트포인터
// 포인터를 알맞는 정책에 따라 관리하는 객체 (포인터를 래핑해서 사용)
// 
// 왜 필요한가?
// - 메모리 오염을 막고, 코드 안전성을 높이기 위해
// 
// 
// *shared_ptr*, weak_ptr, unique_ptr 3가지 종류
// 
// 
// shared_ptr만 사용하면 사이클 문제 발생
// - k1 k2이 서로 target으로 지정했을 때, 하나가 delete되어도 메모리가 끝까지 남아있음 (계속 주시하는 target은 남아있기 때문에, 결국 따로 nullptr을 해줘야하는 문제 발생)
// 
// => 위와 같은 순환구조가 발생할 여지가 있으면, wear_ptr을 사용\
// shared_ptr와는 다르게 객체의 생명주기(refCount)에 관여하지 않지만, 간접적으로 객체가 삭제되었는지 확인하며 작업할 수 있음)
//      확인 후, 다시 사용할 때는 shared_ptr로 변환해서 사용
// weak_ptr 내부 구조 잘 모르겠음, 다시 공부하기
// 
// 
class Knight3
{
public:
    Knight3() { cout << "Knight3()" << endl; }
    ~Knight3() { cout << "Knight3 소멸" << endl; }

    void Attack()
    {
        if (_target)
        {
            _target->_hp -= _damage;
            cout << "HP : " << _target->_hp << endl;
        }
    }
public:
    int _hp = 100;
    int _damage = 10;
    Knight3* _target = nullptr;
};

class RefCountBlock
{
public:
    int _refCount = 1;
};


// shared_ptr 구현
// 레퍼런스 카운터를 관리!
template<typename T>
class SharedPtr
{
public:
    SharedPtr(){}
    SharedPtr(T* ptr) : _ptr(ptr)
    {
        if (_ptr != nullptr)
        {
            _block = new RefCountBlock();
            cout << "RefCount : " << _block->_refCount << endl;
        }
    }

    //복사 생성자
    SharedPtr(const SharedPtr& sptr) : _ptr(sptr._ptr), _block(sptr._block)
    {
        if (_ptr != nullptr)
        {
            _block->_refCount++;
        }

    }

    //복사 대입 연산자
    void operator=(const SharedPtr& sptr)
    {
        _ptr = sptr._ptr;
        _block = sptr._block;

        if (_ptr != nullptr)
        {
            _block->_refCount++;
        }

    }

    ~SharedPtr() 
    {
        if (_ptr != nullptr)
        {
            _block->_refCount--;

            if (_block->_refCount == 0)
            {
                delete _ptr;
                delete _block;
                cout << "Delete Data" << endl;
            }
        }
    }

public:
    T* _ptr = nullptr;
    RefCountBlock* _block;
};
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

#pragma region 전달 참조 (forwarding reference)

    Knight2 k2_1;

    //일반 함수에 왼값을 넣었을 때
    Test_RValueRef(std::move(k2_1));        //rvalue_cast
    //Test_RValueRef(k2_1);


    //template 함수에 왼값을 넣었을 때
    //오른값 참조를 인자로 지정했는데, 왼값이 통과가 된다??? 
    Test_ForwardingRef(k2_1);       //왼값으로 받아진다.
    Test_ForwardingRef(std::move(k2_1));    //오른값으로 받아진다.


    //auto&&(오른값)에 왼값을 넣었을 때
    auto&& k2_2 = k2_1; // 이 경우에도 왼값으로 받아짐
    //auto&& k2_2 = std::move(k2_1);  //당연히 원래 타입 선언대로 오른값으로 해도 받아진다.

    // template나 auto를 이용해 오른값으로 선언한 변수에 왼값을 대입하면, 왼값으로 자동 캐스팅이 된다.
    // 형식 연역(type deduction)이 일어날 때, 오른값 -> 왼값으로 자동으로 대입해줌
    // 이를 전달 참조라고 한다.
    // (왼값을 넣으면 왼값 참조, 오른값을 넣으면 오른값 참조)




    //전달 참조를 구별하는 방법
    Knight2& k2_3 = k2_1;   //왼값 참조
    Knight2&& k2_4 = std::move(k2_1);   //오른값 참조
    // 오른값: 왼값이 아니다 = 단일식에서 벗어나면 사용x
    // 오른값 참조 : 오른값만 참조할 수 있는 참조 타입


    //Test_RValueRef(k2_4);   //오른값 타입 매개변수에 오른값을넣었는데 안된다>>>?
    Test_RValueRef(std::move(k2_4));
    // k2_4는 오른값 참조이지, 오른값이 아니다! 단일식에서 벗어나도 사용 가능! 
    // 따라서 오른값을 매개변수로 받는 위 함수에서 k2_4(오른값 참조)는 못들어감!
    // => 그래서 k2_4에 std::move를 다시 붙혀준다.

    // std::move 기능은 오른값 참조로 변경해주는 함수
    // 그러나 Knight2&& k2_4 = std::move(k2_1)으로 받는 순간 k2_4는 왼값이라고 보게 되어 위 함수가 통과 안되는 것임

#pragma endregion


#pragma region 람다
    
    vector<Item> v;

    v.push_back(Item(1, Rarity::Common, ItemType::Weapon));
    v.push_back(Item(2, Rarity::Common, ItemType::Armor));
    v.push_back(Item(3, Rarity::Rare, ItemType::None));
    v.push_back(Item(4, Rarity::Unique, ItemType::Weapon));

    // 람다 = 함수 객체를 손쉽게 만드는 문법
    {
        struct IsUniqueItem
        {
            bool operator()(Item& item)
            {
                return item._rarity == Rarity::Unique;
            }
        };

        // (개인)헷갈리는 부분 보충 설명
        // IsUniqueItem() --> 구조체의 생성자임!  Pr _pr을 인자로 받아 안에서 (&Item)로 실행하는 부분이 operator()(Item &item)이 실행되는 부분임



        // 람다 표현식
        // 클로저 : 람다에 의해 만들어진 실행지점 객체
        auto isUniqueLamda = [](Item& item) { return item._rarity == Rarity::Unique; };

        // 람다 첫 부분 "[ ]" {캡처(capture)} : 함수 객체 내부에 변수를 저장하는 개념과 유사
        // - 람다식 외부에 있는 변수를 { } 부분에 사용가능하게함
        // - 기본 캡처 모드 : 값 (복사) 방식(=) , 참조 방식(&) 
        //          ex) [=] or [&]
        // 아무 것도 안쓰면, 람다식 외부에 있는 변수 사용 불가, (람다식이 함수 객체(클래스)로 어떻게 변형되는지 알아보기)
        // 변수마다 캡처 모드를 지정해서 사용가능,  ex) [&ItemId, &rarity, type](..){..};
        auto findIt = find_if(v.begin(), v.end(), isUniqueLamda);
        if (findIt != v.end())
            cout << "Item id " << findIt->_itemId << endl;



        /*int itemId = 4;

        auto f = [=](Item& item) {return item._itemId == itemId; };*/
    }

#pragma endregion

#pragma region 스마트포인터
    {
        Knight3* k3_1 = new Knight3();
        Knight3* k3_2 = new Knight3();

        k3_1->_target = k3_2;

        k3_1->Attack();

        delete k3_2;
        //k3_1->Attack();     //메모리 오염
        // - k3_1의 target이 nullptr이 아니면, delete k3_2이 호출이 되면 안된다!!
    }
    
    cout << "---------------------------" << endl;


    {
        SharedPtr<Knight3> k3_1(new Knight3());
        SharedPtr<Knight3> k3_2 = k3_1;
        // k3_2가 new Knight3()의 ref를 가지고 있기 때문에, delete k3_1해도 new Knight3()이 삭제되지 않을 것임
    
        // delete를 개발자가 일일히 작성하지 않아도, SharedPtr이 소멸될 때, ref Count가 0이면 delete를 해주게끔 구현함
    
        // cpp에서 지원하는 문법 이름 : shared_ptr<T> sptr = make_shared<T>();
    }
    



#pragma endregion

}