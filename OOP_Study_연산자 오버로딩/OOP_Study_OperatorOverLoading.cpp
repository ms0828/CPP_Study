using namespace std;
#include <iostream>

#pragma region 연산자 오버로딩
// 
// 일단 [연산자 함수]를 정의해야 함
// 멤버함수 vs 전역함수가 존재하는 것처럼, 연산자 함수도 두 가지 방식으로 만들 수 있음
// 
// 멤버 연산자 함수 ver
// - a operator b 형태에서 왼쪽 기준으로 실행됨, (a가 클래스여야 가능!, a를 기준 피연산자 라고 함)
// 한계 > a가 클래스가 아니면 사용 불가
// 
// 전역 연산자 함수 ver
// - a operator b 형태라면, a, b 모두를 연산자 함수의 피연산자로 만들어준다.
// 
// 멤버 연산자 함수만 지원하는 형태는?
// - 대표적으로 대입 연산자 (a = b)
// 
// 
// 복사 대입 연산자
// - 대입 연산자 중, 자기 자신의 참조 타입을 인자로 받는 연산자
// - [복사 생성자]와 다른점 - 커스터 마이징 가능  (참고로 복사 생성자는 따로 안만들면 컴파일러가 알아서 만들어준다)
// 
// 증감 연산자 ++ --
// - 전위형(++a)  operator++()
// - 후위형(a++)  operator++(int)   (매개변수 int는 따로 사용안해도 됨, 이름도 안지어도 됨)
// 
// 
// - 모든 연산자를 다 오버로딩 할 수 있는 것은 아니다. (::, ., * 이런건 안됨)
// 
// 
// 
#pragma endregion


class Position
{
public:
    Position operator+(const Position& arg) //인자 타입을 꼭 참조로 해야하는 것은 아니지만, 메모리 효율을 위해 8byte(64)만 사용하려고
    {
        Position pos;
        pos._x = _x + arg._x;
        pos._y = _x + arg._y;

        return pos;
    }

     
    Position operator+(int arg)
    {
        Position pos;
        pos._x = _x + arg;
        pos._y = _x + arg;

        return pos;
    }

    void operator=(int arg)
    {
        _x = arg;
        _y = arg;
    }

    Position& operator=(const Position& arg)
    {
        _x = arg._x;
        _y = arg._y;

        return *this;
    }


public:
    int _x;
    int _y;

};


// 전역 연산자 함수
// - 왼쪽이 일반 변수여도 사용가능!!
Position operator+(int a, const Position& b)
{
    Position ret;
    ret._x = b._x + a;
    ret._y = b._y + a;

    return ret;
}


int main()
{
    Position pos1;
    pos1._x = 0;
    pos1._y = 0;

    Position pos2;
    pos2._x = 0;
    pos2._y = 0;


    //두 pos의 좌표를 더하고 싶으면??
    // 연산자 오버로딩으로 연산자를 커스터 마이징!!
    Position pos3 = pos1 + pos2;
    // => pos3 = pos1.operator+(pos2) 와 동일
    
    Position pos4 = pos3 + 1;
    // => pos4 = pos3.operator+(1) 와 동일
    // 멤버 연산자 함수의 한계점으로 인해, 1 + pos3 은 안됨! (왼쪽이 클래스여야만 가능)
    // - 전역 연산자 함수로는 가능

}

