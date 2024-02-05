#include <iostream>
#include<map>
#include<vector>
using namespace std;

#pragma region map
// 
// 연관 컨테이너
// 
// 특정 데이터를 찾아야할 때 유리한 자료구조
// 
// 
// map : 균형 이진트리(AVL)를 사용
// - 노드 기반
// - key와 value로 구성
// - 삽입 시, key 중복X, 두 번째 삽입은 *무시*
//
// 
// 
// 
// 
#pragma endreigon


class Player
{
public:
    Player() : _playerId(0){}
    Player(int playerId) : _playerId(playerId) {}

public:
    int _playerId;
};



int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

#pragma region map(연관 컨테이너)의 필요성 

    /*
    
    vector<Player*> v;

    //10만명 입장

    for (int i = 0; i < 100000; i++)
    {
        Player* p = new Player();
        v.push_back(p);
    }


    // 5만명 퇴장
    for (int i = 0; i < 50000; i++)
    {
        int randIndex = rand() % v.size();
        Player* p = v[randIndex];
        delete p;

        v.erase(v.begin() + randIndex);

    }

    // 위처럼 서버에서 player를 vector로 관리한다고 가정 
    // ID == 10000인 Player를 찾으려면?
    // - 중간에 나간 Player가 있기 때문에, 특정 ID인 Player를 한 번에 인덱스로 찾을 수 없다!
    //      차례로 탐색을 해야한다.
    // 
    // 
    // 벡터나 리스트 같은 선형 자료구조는 특정 데이터를 빨리 찾을 수 없다.
    // 원하는 조건에 해당하는 데이터를 찾는 것에 불리

    */
#pragma endregion


    map<int, int> m;


    // 삽입은 기존에 key가 있으면 두번째 삽입은 무시된다.
    pair<map<int, int>::iterator, bool> ok;
    ok = m.insert(make_pair(1, 100));
    ok = m.insert(make_pair(1, 200));        // 이 삽입은 무시됨  pair ok 중 bool 부분에 false 
    
    

    // 없으면 추가, 있으면 수정하려면
    // v1
    map<int, int>::iterator findIt = m.find(100);
    if (findIt != m.end())
    {
        findIt->second = 200;
    }
    else
    {
        m.insert(make_pair(100, 200));
    }
    
    // v2
    m[100] = 500;
    // [] 연산자 사용할 때 주의, 대입을 하지 않더라고 Key/Value 형태의 데이터가 추가된다!
    // ex) cout<<m[i]<<endl; 사용할 때, 데이터가 없으면 기본 값으로 강제로 추가함




    // 다시 시나리오로 돌아와서
    // 10만명 접속
    for (int i = 0; i < 100000; i++)
    {
        m.insert(pair<int, int>(i, i * 100));
    }

    for (int i = 0; i < 50000; i++)
    {
        int randValue = rand() % 50000;

        //Erase By Key
        m.erase(randValue);
    }

    // ID == 1인 Player를 찾고 싶다!
    // - 빠르게 찾을 수 있음

    //Find By Key
    // 못찾으면 m.end() 반환
    map<int, int>::iterator findIt2 = m.find(10000);
    if (findIt2 != m.end())
    {
        cout << "찾음" << endl;
    }
    else
    {
        cout << "못찾음" << endl;
    }

    

    // map 순회
    // map의 iterator는 *iterator로 접근하면 pair<key,value>가 나온다.
    // 
    for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
    {
        pair<const int, int>& p = (*it);
        int key = p.first;
        int value = p.second;

        
    }

}
