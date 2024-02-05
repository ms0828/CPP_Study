#include<set>
#include<map>
#include <iostream>
using namespace std;

#pragma region set,multimap,multiset
// ---------set---------
// 데이터 자체가 키일 때 --> Set
// 나머지 특성은 map이랑 똑같다.
// 
// map은 [key]접근 연산자로 값을 할당하거나 바꿔칠 수 있지만,
//  set은 []이 지원되지 않음 - 키와 value가 같기 때문에
// 
// 
// ---------동일한 key의 중복을 허용하는 multimap,multiset----------
//                  (사용할 일 많이 없음)
// 
// map에서 조금 달라지는 점 : [key] 접근 연산자 지원X 
// 
// mulmap.erase(key)은 해당 key의 pair를 모두 삭제
// 
// 하나만 삭제하고 싶으면, find로 첫번째 데이터 찾고, 삭제하기 
// 
// 같은 key에 대한 pair의 범위를 얻는 함수 (iterator 쌍 반환)
// pair<multimap<int,int>::iterator, multimap<int,int>::iterator> itPair = mulmap.equal_range(key)   
// 
// lower_bound(key), upper_bound(key) 로 특정 key의 첫번째 iterator와 마지막 iterator 반환받을 수 있음
// 
#pragma endregion

int main()
{
    set<int> s;
    
    s.insert(10);
    s.insert(20);
    s.insert(30);
    s.insert(40);
    s.insert(50);

    s.erase(40);

    set<int>::iterator findIt = s.find(50);

    cout << (*findIt) << endl;

    for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
    {
        cout << (*it) << endl;
    }
    cout << "---------------------" << endl;



    // 멀티 map   (set도 똑같음)

    multimap<int, int> mm;
    mm.insert(make_pair(1, 100));
    mm.insert(make_pair(1, 200));
    mm.insert(make_pair(1, 300));
    mm.insert(make_pair(2, 400));
    mm.insert(make_pair(2, 500));
    mm.insert(make_pair(2, 500));




}
