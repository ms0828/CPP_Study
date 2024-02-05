#include <iostream>
#include"Player.h"
using namespace std;

#pragma region 전방선언
// 
// 전방선언
// 만약 Player.h가 Monster를 멤버 클래스로 들고있다고 가정
// - Player는 몇 바이트??
// - Monster 메모리를 할당받기 위해 Monster의 크기를 알아야함
// - 그러기 위해 Monster 클래스(설계도)를 include해야 알 수 있다.
// => Player 클래스(설계도)를 작성하기 위해 Monster를 알아야한다!
// 
// 
// 만약 Player.h가 Monster*를 멤버 변수로 들고있다고 가정
// - Player는 몇 바이트?
// - Monster의 크기에 상관없이 Monster* (8byte, 64bit)의 크기만큼 메모리를 할당받으면 됨
// => Player 클래스를 작성하기 위해 Monster 클래스를 알필요가 없다!
// => 이럴 때, 전방선언이 가능하다!  (include까지 할 필요가 없음)
// => 전역에 class Monster; 혹은 멤버 변수에 class Monster* _target;
// 
// 
// 그러나 위처럼 전방선언 후에, Player.cpp에 가서 KillMonster()함수를 구현한다고 가정
//      KillMonster에는 Monster* _target에 접근하여 피를 깎는 로직
// - 실제로 해보면, _target에 접근할 수 없다고 한다?!
// => Player는 현재 Monster의 설계도를 갖고 있는게 아니라, Monster* 타입의 포인터 바구니만 들고있기에,
//          Monster의 클래스(설계도)를 알아야한다!
// => 따라서 실질적으로 Monster를 접근할 때, Player.cpp에 include"Monster.h"를 해야한다.
// 
// 
// 
// + .h 파일에서 include문을 피해야하는 이유
// - 만약 Player.h에 Monster를 include하고, Player가 멤버 클래스로 Monster를 갖고있거나, 함수 로직에 Monster를 사용한다고 가정
// - Monster가 include되어서 빌드될 때, Monster도 Player를 역참조 하고 있다면??(Player를 include하고 있다면?)
// => 서로 반복해서 순환되기 때문에 문제가 발생한다!!
// 
// 
// 
// 만약 Player.h가 Player 멤버 클래스를 들고 있으면?
// - Player는 몇 바이트인가?
// - Player의 크기를 알기 위해 Player를 알아야하는데, Player를 알기위해 Player를 알아야한다.
// => 이 때는 Player*를 사용한다.
// 

#pragma endregion


int main()
{

    // Player는 몇 바이트??


    Player p1;

    Player* p2 = new Player();
}
