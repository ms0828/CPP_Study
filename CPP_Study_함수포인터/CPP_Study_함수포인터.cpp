#include <iostream>
using namespace std;

#pragma region 함수 포인터
// "포인터를 타고가면 함수가 있다!"를 어떻게 표현?
// - 
// 

#pragma endregion


int Add(int a, int b)
{
    return a + b;
}

int Sub(int a, int b)
{
    return a - b;
}


class Item
{
public:

public:
    int _itemId;
    int _rarity;
    int _ownerId;
};


// 함수 포인터 타입 예제
// - 특정 조건으로 Item을 찾는 함수는 각 검색 조건에 따라 방대해지고 여러개일 수도 있음
// - 검색 조건 함수를 인자로 받을 수 있게 설계!!

typedef bool(ITEM_SELECTOR)(Item* item);

Item* FindItem(Item items[], int itemCnt, ITEM_SELECTOR* selector)
{
    for (int i = 0; i < itemCnt; i++)
    {
        Item* item = &items[i];
        
        if (selector(item))
            return item;
    }

    return nullptr;
}

bool isRareItem(Item* item)
{
    return item->_rarity >= 2;
}




// ------------함수포인터2

class Knight
{
public:
    int GetHp()
    {
        cout << "GetHp()" << endl;
        return 0;
    }

public:
    int _hp = 100;
};

// typedef 정의들
typedef int INTEGER;
typedef int* POINTER;
typedef int ARRAY[20];
typedef int(*PFUNC)(int, int);//   //함수 포인터
typedef int(Knight::*PMEMFUNC)();  //멤버 함수 포인터

int main()
{
#pragma region 함수 포인터1

    int a = 10;
    typedef int DATA;



    // 1) 포인터       *
    // 2) 변수 이름     ptr
    // 3) 데이터 타입    int
    DATA* ptr = &a;


    // 함수 타입 지정
    // -int 2개를 받아 int를 반환한다 == FUNC_TYPE 으로 설정
    typedef int(FUNC_TYPE)(int a, int b);
    // FUNC_TYPE fn;         == int (*fn)(int, int)       (FUNC_TYPE은 함수 타입 지정, 밑에는 타입 지정과 함께 특정 함수 포인터 선언)
                                        // int (*fn)(int, int)  방법이 더 많이 사용됨



    // 1) 포인터       *
    // 2) 변수 이름     fn
    // 3) 데이터 타입    함수int(int, int) (== FUNC_TYPE)
    FUNC_TYPE* fn;




    // 어셈블리어로 분석하면 함수 이름도 (어떤 명령어 시작의)주소이다!
    // ex) ~ call (0x012cb1)
    int result1 = Add(1, 2);


    //따라서 함수의 타입이 같다면 함수 타입 포인터로 함수를 담을 수 있다.
    fn = Add;       // & 생략가능 (함수의 주소를 넣는다는 동일)
    int result2 = fn(1, 2);


    // 함수 포인터는 *(접근 연산자) 붙어도 똑같은 함수 주소!  (result2에 fn은 사실 *을 생략했다고 보면 됨)
    int result3 = (*fn)(1, 2);


    // 장점
    // - 함수 타입(리턴,인자)이 같다면, 함수를 일관적으로 한번에 교체가능
    fn = Sub;
    int result4 = fn(1, 2);


    cout << result1 << endl;
    cout << result2 << endl;
    cout << result3 << endl;
    cout << result4 << endl;
    
#pragma endregion


#pragma region 함수 포인터2
    // 함수 포인터1로 만든 함수 포인터는 [전역, 정적 함수]만 담을 수 있다.
    // - 객체에서 실행되는 멤버 함수는 일반함수와 호출규약이 다르다!
    // - 멤버 함수를 담으려면?
    // => 멤버 함수 포인터를 사용한다.
    //  (멤버 함수 포인터는 *, &생략 불가)

    Knight k1;
    k1.GetHp();

    PMEMFUNC mfn;
    mfn = &Knight::GetHp;


    (k1.*mfn)();
    //fn(1,2) == (*fn)(1,2) 와 다르게 멤버 함수 포인터는 접근 연산자 *을 생략하면 안됨



#pragma endregion

}

