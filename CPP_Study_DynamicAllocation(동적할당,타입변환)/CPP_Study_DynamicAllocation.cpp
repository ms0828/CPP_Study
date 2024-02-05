using namespace std;
#include <iostream>

#pragma region 동적할당1
// 메모리 구조
// 낮은 주소 << [실행 코드] [ (전역, 정적변수)데이터 영역] [(동적 할당)힙] [(지역, 매개변수)스택] << 높은 주소
// 힙은 런 타임에 크기가 결정, 스택은 컴파일 타임에 크기가 결정
//
// 
// 지금까지는 데이터/ 스택 영역 이용해서 프로그램을 만들었는데,
//  새로운 영역(힙)이 언제 필요한가?
// 예시)
// - 대규모 게임에서 동접자 수에 따라 필요한 메모리 크기가 유동적으로 바뀜
// 
// 
// 
// *스택 영역
// - 함수가 끝나면 같이 정리되는 불안정한 메모리
// 
// *메모리(데이터) 영역
// - 프로그램이 실행되는 도중에는 무조건 사용 
// 
// * 힙 영역  (필요할 때만 사용하고, 필요없으면 반납할 수 있는!)
// - 우리가 생성/ 소멸 시점을 관리할 수 있는!
// - (malloc, free, new, delete, new[], delete[], ...)
// 
// 
// 
// * 프로그램이 실행되는 구조
// 유저 영역 (메모장, 게임, ...)  
// ----------
// 커널 영역 (Windows 등의 핵심 코드)
// 
// 
// 지식
//  - 유저 영역에서는 운영체제가 각기 다른 프로그램이 독립적으로 실행될 수 있게 도와줌)
//  - 유저 영역에서 메모리가 필요하면 커널에 요청 (운영체제에서 제공하는 API 호출) -> 커널에서 메모리 할당해서 건네줌
//  - 커널은 바쁘기 때문에, 한 번 요청할 때 크게 받아옴, 필요할 때 적당히 메모리 잘라서 사용
//  - malloc() 등으로 필요한 메모리를 요청하는 것은, 받아온 메모리에서 적당히 잘라 쓴다는 말
//  - c++에서는 기본적으로 CRT(C런타임 라이브러리)의 [힙 관리자]를 통해 힙 영역 사용
//  - 단, 정말 원한다면 우리가 직접 API를 통해 힙 생성하고 관리할 수 있음 (MMO 서버 메모리 풀링)
// 
// 
// malloc  ( void* malloc(size_t) )
// - 할당할 메모리 크기를 건네줌
// - 메모리 할당 후 시작 주소를 가리키는 포인터 반환 (메모리 부족하면 NULL)
// - malloc은 CRT의 힙 관리자를 통해 관리되고 있는 함수
//      - void* ??  (malloc의 반환 값)
//      - 타고 가면 void 뭐가 있는지 모르겠으니까 너가 적당히 변환해서 사용해라!
// 
// 
// free
// - malloc (혹은 기타 calloc, realloc)을 통해 할당된 영역을 해제
// - 힙 관리자가 할당/미할당 여부를 구분해서 관리
// - 어떻게 포인터만 인자로 받고, 할당된 크기만큼만 해제하나?
//      => 메모리 까보면 할당된 메모리 전에 크기를 나타내는 값도 할당되어있음
// 
// 
// 
// 동적할당 시, 조심해야할 버그
// 1. Heap Overflow
// - 유효한 힙 범위를 초과해서 사용하는 문제

// 2. 메모리 누수 (나중에 메모리가 부족해서 프로그램이 뻗음)
// - free는 반드시!!
// 
// 3. Use-After_Free
// - 반납 후에, 포인터로 메모리를 사용할 때 (포인터는 계속 남아있기 때문에 free 이후, 접근할 수 있음)
// - 반납 후, 포인터는 nullptr 해주기
#pragma endregion

#pragma region 동적할당2
//
// new / delete    (c++에 추가된 동적할당 방법) (malloc/free는 함수!,  new / delete는 연산자)
// 
// 사용예시)
// Monster* m2 = new Monster
// - Monster 크기 만큼 메모리 할당해서 포인터 반환
// - 사용 후에, delete m2;  꼭 해주기! 
// 
// 
// new가 malloc에 비해 좋긴한데~ 배열과 같이 N개 데이터를 같이 할당하려면? => new[]
// - Monster* m3 = new Monster[5];
// - 사용 후에, delete[] m3; 해주기!   ( [] 빼먹지 말 것! )
// 
// 
// 
// malloc/free VS new/delete
// - 편의성 : new/delte 승
// - but 타입 상관없이 특정한 크기의 메모리 영역을 할당 받으려면 malloc/free
// 
// 
// malloc과 new의 근본적인 차이는?    ********************
// - new/delete는 (생성타입이 클래스일 경우) 생성자(new) / 소멸자(delete)를 호출해준다!!!
// 
#pragma endregion


#pragma region 타입 변환
// 타입 변환 1, 2 결론
// [값 타입 변환] : 진짜 비트열도 바꾸고 논리적으로 말이 되게 바꾸는 변환
// - 논리적으로 말이 된다? (ex BullDog -> Dog) OK
// - 논리적으로 말이 안된다 (ex Dog -> BullDog) 안 됨 (상관 없는 클래스 경우, 타입 변환 생성자, 연산자 필요!)
// [참조 타입 변환] : 비트열은 냅두고 '관점'만 바꾸는 변환
// - 안전하다 (BullDog -> Dog&) - 그냥 암시적으로 OK
// - 위험하다 (Dog -> BullDog&) - 명시적 변환 필요
// 
// 
// 
// --------포인터 타입 변환-------- (타입 변환3) ****
// 
// 
// 
// 
//
#pragma endregion


class Monster
{
public:
    int _hp;
    int _x;
    int _y;

public:

};


class Knight
{
public:
    int _hp = 10;
};

class Dog
{
public:
    Dog()
    {

    }

    //(말은 안되지만 공부 목적으로..) 타입 변환 생성자
    Dog(const Knight& knight)
    {
        _age = knight._hp;
    }

    //(말은 안되지만 공부 목적으로..) 타입 변환 연산자
    // - Dog를 대상으로 강제로 Knight로 변환할 때
    // - 특이하게 일반 함수 operator와 다르게 반환값 명시 필요없음
    operator Knight()
    {
        return (Knight)*this;
    }

public:
    int _age = 1;
    int _cuteness = 2;
};


class BullDog : public Dog
{
public:
    bool _french;
};


class Item
{
public:
    Item()
    {
        cout << "Item 기본 생성자" << endl;
    }

    Item(int itemType) : _type(itemType)
    {

    }

    Item(const Item& item)
    {
        cout << "Item(const Item&) 복사 생성자" << endl;
    }

   virtual ~Item()
    {
        cout << "Item 소멸자" << endl;
    }

public:
    int _type = 0;
    int _dbId = 0;

    char _dummy[4096] = {};     //이런 저런 정보들로 비대해진 아이템을 묘사하기 위해 만든 변수
};


void TestItem(Item item)
{
}

void TestItemPtr(Item* item)
{
}


class Mage
{
public:
    int _hp = 0;
};

enum ItemType
{
    IT_WEAPON = 0,
    IT_ARMOR = 1,
};

class Weapon : public Item
{
public:
    Weapon() : Item(IT_WEAPON)
    {
        cout << " Weapon 기본 생성자" << endl;
        _damage = rand() % 100;
    }

    ~Weapon()
    {
        cout << " Weapon 소멸자" << endl;
    }

public:
    int _damage = 0;
};

class Armor : public Item
{
public:
    Armor() : Item(IT_ARMOR)
    {
        cout << " Armor 기본 생성자" << endl;
    }

    ~Armor()
    {
        cout << " Armor 소멸자" << endl;
    }
public:
    int _defence = 0;
};


int main()
{

#pragma region 동적할당 기본

    //Monster monster[500 * 10000]; // 스택 오버 플로우 발생 가능


    //          size_t   (malloc이 요구하는 인자)
     /*#ifdef _WIN64  (64bit)
    typedef unsigned __int64 size_t;
    #else (32bit)
    typedef unsigned int     size_t;*/


    // malloc
    void* pointer = malloc(sizeof(Monster));
    Monster* m1 = (Monster*)pointer;

    free(pointer);


    // new
    Monster* m2 = new Monster;
    delete m2;

    //new[]
    Monster* m3 = new Monster[5];
    delete[] m3;
 
#pragma endregion

#pragma region 타입 변환

    // -------타입 변환 유형 (비트열 재구성 여부)
    // 1. 값 타입 변환
    // - 의미(ex: 최대한 똑같은 숫자)를 유지하기 위해서, 원본 객체와 다른 비트열 재구성
    int a = 123456789;  //2의 보수
    float b = (float)a; //부동소수점
    cout << "값 타입 변환 b : " << b << "   (최대한 비슷한 숫자나 비트열 재구성으로 인해 조금 다르다)" << endl;
    // a -> b 어떻게 저장될까? 
    // - 메모리 구조를 살펴보면 다른 값
    // => 최대한 똑같은 숫자를 유지하되, 실제 메모리 값은 다를 수 있다.
    //
    // 2. 참조 타입 변환
    // - 비트열을 재구성하지 않고, '관점'만 바꾸는 것
    //      (포인터 타입 변환도 '참조 타입 변환' 동일한 룰을 따른다.)
    int a2 = 123456789;  //2의 보수
    float b2 = (float&)a2; //부동소수점
    cout << "참조 타입 변환 b2 : " << b2 << "   완전한 다른 값" << endl;
    // = > 메모리 값은 유지하나, 관점이 달라 다른 값이 나올 수 있다.
    // => 123456789를 float 관점으로 해석하여 다른 값이 나옴


    // ------안전도 분류-------
    // 1. 안전한 변환
    // - 의미가 항상 100% 완전히 일치하는 경우
    // ex) 같은 타입이면서 크기만 더 큰 바구니로 이동 (업 캐스팅)
    // ex) char-> short, short -> int, int -> _int64
    // 
    // 2. 불안전한 변환
    // - 의미가 항상 100% 일치한다고 보장하지 못하는 경우
    // - ex) 타입이 다를 때
    // ex) 같은 타입이지만 큰 바구니 -> 작은 바구니로 이동 (다운 캐스팅) 


    // ------프로그래머 의도에 따라 분류------
    // 1. 암시적 변환
    // ex) 이미 알려진 타입 변환 규칙에 따라 컴파일러가 '자동'으로 타입 변환
    int a3 = 12345678;
    float b3 = a3;   //암시적으로 컴파일러가 변환
    //
    // 2. 명시적 변환
    int a4 = 12345678;
    int* b4 = (int *)a4;     //컴파일러가 위험해서 암시적 변환을 막아놓음 - 명시적 변환 필요



    // ------둘 사이 연관 관계가 없는 클래스 타입 변환------
    //1. 연관 없는 클래스 사이의 '값 타입' 변환
    // - 일반적으로 안됨 (but 타입 변환 생성자, 타입 변환 연산자 사용하면 가능)
    {
        //      (1). 타입 변환 생성자
        Knight knight;
        Dog dog = (Dog)knight;  //원래 안되지만, Dog의 타입 변환 생성자를 만듬 {  Dog(const Knight& knight){};  }
        //      (2). 타입 변환 연산자
        //Knight knight2 = dog;   //Dog에 타입 변환 연산자를 정의해서 가능
    }
    //
    // 2. 연관 없는 클래스 사이의 '참조 타입' 변환
    {
        Knight knight;
        Dog& dog = (Dog&)knight;
    }
    
    // 윗 줄 해석 = 만약 dog2를 타면 Dog인 메모리가 있을 것이다! 라고 주장하는 것과 같음 
    //dog2._cuteness = 12;  -> dog2는 8byte인 반면에 knight는 4byte이므로 이 코드는 엉뚱한 메모리를 가리키게 된다! 위험한 상황
    // (어셈블리어 관점에서 참조 = 포인터)
    // => 값 타입 변환이 아닌, 참조 타입 변환은 [명시적]으로는 컴파일 통과!! - 하지만 사용할 때 조심!
    // 
    // 
    // -----상속 관계에 있는 클래스 사이의 변환-----
    // 1. 상속 관계 클래스의 값 타입 변환
    // 자식 -> 부모 OK
    {
        BullDog bullDog;
        Dog dog = bullDog;     //업 캐스팅
    }
    //
    // 2. 상속 관계 클래스의 참조 타입 변환
    {
        Dog dog;
        BullDog bullDog = (BullDog&)dog;      //다운 캐스팅
    }
    //부모 -> 자식은 명시적 형변환 필요! but 조심
    {
        BullDog bullDog;
        Dog dog = bullDog;
    }
    //자식->부모는 OK


    cout << endl << endl << endl << endl;
#pragma endregion


#pragma region 타입 변환(포인터) ***
    // 복습
    {
        // Stack [ type(4) dbid(4) dummy(4096) ]
        Item item;

        // Stack [ 주소(8) ]
        //Heap[type(4) dbid(4) dummy(4096)]
        Item* item2 = new Item();


        //-----함수 인자로 클래스를 어떻게 넘길까?------
        //Item을 인자로 하는 TestItem 실행 결과
        TestItem(item);
        TestItem(*item2);
        //item이 인자로 들어갈 때, Item 복사 생성자가 호출! = 인자로 인한 Item이 생성된다!
        // => 메모리 낭비가 된다!


        //Item의 포인터를 인자로 하는 TestItemPtr 실행 결과
        TestItemPtr(&item);
        TestItemPtr(item2);
        //Item이 만들어지지 않아 주소를 위한 8byte 메모리만 소모!

        delete item2;       //delete 안하면 소멸자 실행X, 메모리 누수 발생(힙 어딘가에 계속 메모리 사용하고 있음)
    }

    ////복습2 - 배열버전
    //{
    //    cout << "---------------------------------------" << endl;
    //    // 진짜 아이템 100개 있는 것 [스택 메모리에 올라와 있는]
    //    Item item[100] = {};
    //    // 아이템을 가리키는 주소 바구니가 100개
    //    Item* item2[100] = {};
    //}


    //연관성이 없는 클래스 사이의 포인터 변환 (중요)
    {
        //암시적으로는 No, 명시적으로는 OK한 경우
        // Stack [ Mage*(주소) ] -> Heap [ Mage ]
        Mage* mage = new Mage();
        // Stack [ Item *(주소) ] -> Heap [ Mage ]
        Item* item = (Item*) mage;

        item->_type = 2;
        //윗 줄의 결과로 mage의 hp가 바뀌게 된다! = 엉뚱한 값이 바뀌게 된다! = item*을 조작했지만 결국 가리키고 있는 mage의 첫번째 4byte 메모리를 조작함
        item->_dbId = 1;
        //윗 줄의 결과로는 Knight 메모리 오프셋을 벗어난 잘못된 메모리를 조작하는 결과!
        //delete가 될 때, Knight의 메모리 오프셋 중 잘못된 메모리를 조작했다고 오류가 남 (오히려 좋은 상황, 안터지면 난감해짐)
       
        cout << endl << endl << endl << endl;
    }


    // 부모 -> 자식 변환 테스트  (명시적 변환 필요! but 조심)
    {
        /*Item* item = new Item();
        Weapon* weapon = (Weapon*)item;
        weapon->_damage = 10;
        delete item;*/
    }


    // 자식 -> 부모 변환 테스트 (OK)
    {
        Weapon* weapon = new Weapon();

        Item* item = weapon;

        delete weapon;
    }

    //그럼 안전하게 항상 자식 -> 부모로만 사용하면 되지 않나?
    // => 명시적 변환을 써야하는 경우 예시
    {
        Item* inventory[20] = {};
        srand((unsigned int)time(nullptr));

        for (int i = 0; i < 20; i++)
        {
            int randValue = rand() % 2;
            switch (randValue)
            {
            case 0:
                inventory[i] = new Weapon();

                break;
            case 1:
                inventory[i] = new Armor();
                break;
            }
        }

        for (int i = 0; i < 20; i++)
        {
            Item* item = inventory[i];
            if (item == nullptr)
                continue;


            if (item->_type == IT_WEAPON)
            {
                Weapon* weapon = (Weapon*)item;
                //cout << "Weapon Damage : " << weapon->_damage << endl;
            }
        }

        //**********매우 매우 중요***********
        // inventory를 Item*로 관리하고 있을 때, 
        //  delelte inventory[i]를 호출하면 Item의 소멸자만 호출된다!
        // => Weapon과 Armor의 소멸자는 호출되지 않는다. 

        //해결법
        // ***부모 클래스 소멸자에 가상함수 키워드 virtual를 붙여준다.***
        //  => 자식의 클래스를 찾아 자식의 소멸자가 호출됨, 부모 클래스의 소멸자도 같이 호출됨 (자식의 소멸자에선 원래 부모 소멸자가 호출되기 때문)
        for (int i = 0; i < 20; i++)
        {
            Item* item = inventory[i];
            if (item == nullptr)
                continue;


            delete item;

            //아니면 아래와 같은 방식으로 할당 받은 정확한 타입으로 해제!
            /*if (item->_type == IT_WEAPON)
            {
                Weapon* weapon = (Weapon*)item;
                delete weapon;
            }
            else
            {
                Armor* armor = (Armor*)item;
                delete armor;
            }*/

        }

        //결론
        // 포인터 vs 일반 타입 차이를 이해하자
        // 포인터 사이의 타입 변환(캐스팅)을 할 때는 매우매우 조심하자
        // 부모- 자식 관게에서 부모 클래스의 소멸자에는 virtual를 붙이자!!


    }


#pragma endregion



    return 0;
}

