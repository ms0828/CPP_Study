#include <iostream>
using namespace std;

#pragma region 콜백함수
// 콜백 : 다시 호출하다, 역으로 호출하다
// - 어떤 상황이 일어나면 -> 이 기능을 호출해줘
// ex) 이 스킬 버튼을 누르면 -> 스킬을 쓰는 함수를 호출
// 
// 
// 특정 아이템을 찾는 함수의 인자를 일반적으로 사용하고 싶을 때
// 1)함수 포인터 (같은 시그니처)를 인자로 지정
//  - 단점
//      - 가장 간단한 형태로 콜백 함수를 만들 수 있지만, 상태를 저장할 수 없다! (대안으로 함수 객체)
// 
// 2) 함수 객체
//  - 단점
//      - 특정 함수 객체가 아닌 다른 함수 객체를 인자로 사용 못함(상태는 저장하나 일반적으로 사용X) (대안으로 부모 클래스)
// 
// 3) 템플릿을 이용하여 2의 단점을 해결
//  - FindItem() 함수 선언 위에 template 사용
// 
#pragma endregion


class Item
{
public:
public:
    int _itemId = 0;
    int _rarity = 0;
    int _ownerId = 0;
};

class FindByOwnerId
{
public:
    bool operator()(const Item* item)
    {
        return(item->_ownerId == _ownerId);
    }
public:
    int _ownerId;
};

class FindByRarity
{
public:
    bool operator()(const Item* item)
    {
        return(item->_rarity == _rarity);
    }
public:
    int _rarity;
};

template<typename T>
Item* FindItem(Item items[], int itemCnt, /*bool(*func)(const Item*)*/ /*FindByOwnerId*/ T selector)
{
    for (int i = 0; i < itemCnt; i++)
    {
        Item* item = &items[i];

        // 조건 체크
        if (selector(item))
            return item;

    }

    return nullptr;
}

int main()
{
    Item item[10];
    item[3]._ownerId = 100;
    item[8]._rarity = 1;

    FindByOwnerId functor1;
    functor1._ownerId = 100;

    FindByRarity functor2;
    functor2._rarity = 1;

    Item* item1 = FindItem(item, 10, functor1);
    Item* item2 = FindItem(item, 10, functor2);

}

