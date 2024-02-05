#include <iostream>
using namespace std;

#pragma region 정수
//0이 아닌 초기화 값이 있으면 .data 영역
//초기값이 0이거나 없으면 .bss영역

//콘솔/모바일 게임은 메모리가 늘 부족! -> 작은 자료형 고려
//온라인 게임 -> 네트워크 통신할 때, 큰 자료형은 부담!, 최대한 작은 자료형

//레벨 같이 양수만 가능한 값은 무조건 unsigned? -> 의견이 갈림
//  -차라리 에러를 나게 해서 버그를 빨리 찾는게 나을 수도

//자료형의 범위를 초과해도 에러를 발생하지 않음
//  -최대값이어도 비트를 무조건 올리기 때문에 최상위 비트가 켜지는 등, 에러 발생할 수 있음
//  -(양수 오버플로우)

char a; //1byte (-128~127)
unsigned int ua;    //0~255 (최상위 비트를 부호가 아닌 숫자로 사용)
short b;    //2byte (-32768~32767)
int c;  //4byte
__int64 d;  // == 8byte (=long long)
#pragma endregion

#pragma region 불리언과 실수
//bool은 1byte 정수에 불과
// 왜 1bit만 사용하지 않나? -> 컴퓨터 최소 연산이 주로 1byte이기 때문

//실수(부동소수점)(float, double)
float attackSpeed = 0.639f; //4byte, 부호(1) 지수(8) 유효숫자(23) = 32bit
double attackSpeed2 = 123.4123; //8byte, 부호(1) 지수(11) 유효숫자(52) = 64bit
//ex) -3.375라는 값을 저장한다고 할 때
// 1) 2진수 변환 = 3 + 0.375 = 0b11 + 0b0.011 = 0b11.011
// 2) 정규화 0b1.1011 * 2^1 
//      1(부호) 1(지수) 1011(유효숫자)
//      단 지수는 unsigned byte라고 가정하고 숫자+127을 만들어줌
// 3) ...

//부동소수점 표현 원리를 몰라도 상관없으나, 부동소수점 표현은 근사값이라는 것은 기억하자
//  따라서 실수 2개를 ==로 비교하는 것도 지양
#pragma endregion

#pragma region 문자와 문자열
//char(1byte)도 그냥 정수지만, '문자'의미를 나타내기 위해 사용

//전 세계 모든 문자에 대해 유일 코드를 부여한 것이 유니코드
//유니코드는 표기 방식이 여러가지 있는데 대표적으로 UTF8 UTF16
//wchar_t wch = L'가';
//UTF8
//- 알파벳, 숫자1바이트
//- 유럽 지역 문자는 2바이트
//- 한글, 한자 등 3바이트
//UTF16
//- 알파벳, 숫자, 한글, 한자 등 거의 대부분 문자 2바이트

//문자열
//끝은 NULL(0)이 들어가야 한다.
//main함수 내에서 char str[] = {'a','b','c'} 저장 후 출력하면 이상한 값이 뒤에 붙는 이유
//  -char str2[] = "Hello" 처럼 ""안에 문자열을 써서 저장하면 자동으로 끝에 NULL이 붙는다.

char ch = 'a'+ 1;       //'a'가 의미하는 97에 1더하여 98, 즉 'b'로 출력됨
#pragma endregion

#pragma region 비교 연산과 논리 연산
//비교연산이나 논리연산 (==, <=, &&, ..)은 참이면 1, 다르면 0을 반환
//강의에서 어셈블리어로 설명하는 부분 있는데, 필요하면 찾아서 정리하기
//&&경우 앞 조건이 false면 뒤 조건은 확인하지 않고 false 처리 (어셈블리어로 확인할 수 있음)
#pragma endregion

#pragma region 비트 연산과 비트 플래그 (비트 활용 예제)
//언제 필요한가?
//  비트 단위의 조작이 필요할 때 ex) 게임 서버에서 ID를 발급한다거나, 비트 플래그

//~ (bitwise not) : 모든 비트를 역전환
//& (bitwise and) : 두 비트 쌍에 대해 and연산 (둘 다 1이면 1)
//| (bitwise or) : 두 비트 쌍에 대해 or연산 (하나라도 1이면 1)
//^ (bitwise xor) : 두 비트 쌍에 대해 xor연산 (두 비트가 같으면 0, 다르면 1)

//<< (left shift) : 비트를 왼쪽 이동, 왼쪽의 넘치는 비트는 버림, 새로 생성되는 오른쪽 비트는 0으로 채움
//  -값은 2의 n승 만큼 곱해짐
//>> (right shift) : 비트를 오른쪽 이동, 오른쪽 넘치는 비트는 버림,
//  but 왼쪽 생성되는 비트는 부호 비트가 존재할 경우 부호 비트를 따라감, 부호 비트가 없으면 0으로 채움

// tip : 비트 플래그에 사용할 변수는 unsigned를 쓰자 (부호가 없어야 왼쪽으로 생성되는 부호 비트가 딸려오지 않음)

//사용 예제) 상태이상을 나타낼 때, 만약 상태이상이 32개면? bool을 32개를 선언해야하나?
//0b0000 [무적][변이][스턴][공중부양]
//char flag;
//flag = (1 << 3);  //0b1000 (무적상태) (3을 상수로 만든다면 개발,유지 편함)
//flag = flag | (1<<2); //0b1100 (변이 상태 추가)

//bitmask (무적인지 확인하고 싶다?)(다른 상태는 관심 없음)
//bool invincible = ((flag & (1<<3)) != 0);
#pragma endregion

#pragma region const와 메모리 구조

//상수 설정 법
const int INVINCIBLE = 0;

//전역 변수
//  - 데이터 영역 (종류는 알 필요 없음)
//      .data (초기값 있는 경우)
//      .bss (초기값 없는 경우)
//      .rodate(읽기 전용 데이터) (const는 무조건 rodata? -> X : 컴파일러 나름이다.)

// 지역 변수
//  - 스택 (함수 내에서 쓰는 지역 변수) (Stack Pointer(레지스토리), Base Pointer(레지스토리) 등 구글 이미지 참고)
//  

#pragma endregion

#pragma region 유의사항
//1. 유효범위
// - 스택 : {} 중괄호의 범위가 생존 범위
// 
//2. 타입 변환
// - 메모리 크기에 따른 데이터 소실 문제
// 
//3. 곱셈(오버플로우), 나눗셈(변수로 나누었을 때, 변수가 0이 되면 에러 발생)
// - 나눗셈 경우 float ratio = int / int 경우, 형 변환이 안되어 결과가 정수로만 떨어짐 
//      -> 해결법 : 중간 연산에 하나의 int를 (float)로 강제 형변환하기
#pragma endregion

#pragma region 열거형
//ENUM
//  -컴파일 단계에서 ENUM을 값으로 바꿔버리기 때문에, 따로 메모리가 할당되지 않는다. (메모리 효율성이 좋음)
//  -const는 전역에 선언하면 메모리가 할당되지 않지만, stack에 선언하거나 const의 포인터를 사용하는 코드가 있으면 메모리가 잡힌다.
//  -숫자를 지정 안하면 값은 0부터 시작해서 차례로 +1 값
enum ENUM_SRP
{
    ENUM_SCISSORS = 1,
    ENUM_ROCK,  //첫 값에 차례로 +1
    ENUM_PAPER
};

//전처리 지시문 (#)
//  -define은 정의한 코드를 그대로 전처리 단계에 바꿔치기한다.
//  -상수 목적으로 쓸 때, define 보단 const나 enum을 사용하는 것이 좋음 (define은 최대한 지양)
//  -개발 단계에서도 마우스를 위에 올리면 enum은 정보가 뜨는 방면, define은 안뜸
#define DEFINE_SCISSORS 1
#define DEFINE_TEST cout << "Hello World" << endl;

#pragma endregion

#pragma region 함수_스택 프레임
//게임 업계에서는 대부분 함수 이름 대문자로 시작(카멜표기)
//스택 영역은 데이터 영역(전역, 정적 변수)와 다르게 컴파일 타임에 크기가 결정됨

//함수가 스택 영역에 올라갈 때, 지역변수, 반환 주소값(다시 돌아올 주소 값), 매개변수 등이 스택에 올라감

//Mul함수가 실행될 때 어셈블리어로 확인하면, 매개변수 a, b를 담은 레지스토리를 전부 push 하는 것을 볼 수 있다. -> 매개변수를 스택에 먼저 올림
// sp 레지스토리를 살펴보면 스택 메모리 상황 볼 수 있다.
// 어셈블리어 함수 호출 명령어 call 이후에는 스택에 함수 끝나고 돌아올 명령어 주소를 push (basePointer)
// 함수로 들어가면, basePointer에 다시 stack Pointer를 mov (현재 함수 스코프에서 어디까지 스택 메모리를 사용할지)
// 함수가 끝나면, 함수에서 사용한 스택 메모리를 pop으로 정리  

#pragma endregion

#pragma region 지역 변수와 값 전달 & 호출 스택 & 함수 마무리
// 함수 값 전달 디버깅으로 확인하는 내용

// 함수가 어디서 호출되는지 알려면? -> 디버거 창 우측 하단 호출 스택을 이용! 나중에 매우 중요 (함수 호출 시, 스택에 push하는 반환 주소값과 밀접한 관련)

// 오버로딩 (중복 정의 : 함수 이름의 재사용) (매개 변수가 다를 때) (반환 형식은 상관X)
// - 매개 변수 개수가 다르거나, 타입이 다르거나(순서가 다른걸 포함)

// 기본 인자 값
// 매개변수에 기본 값 설정 가능 ex) void SetPlayer(int hp , int mp = 50)
// -기본 값 설정은 오른쪽 마지막 매개 변수부터 가능하다.

// 스택 오버플로우
// 함수를 계속 호출하여 스택 메모리 공간 이상으로 스택에 메모리를 올릴 때

#pragma endregion



int Mul(int a, int b)
{
    int c = a * b;
    return c;
}

void IncreaseValue(int value)
{
    value = value + 1;
}


//함수 선언
void Func1();
void Func2(int a, int b);
void Func3(float a);

//함수 구현
void Func1()
{
    cout << "Func1" << endl;
    Func2(1, 2);

    Func3(1);
}

void Func2(int a, int b)
{
    cout << "Func2" << endl;
    Func3(10);
}

void Func3(float a)
{
    cout << "Func3" << endl;
}

//구조체
struct ObjectInfo
{
    int type;
    int hp;
    int attack;
    int defense;
};
ObjectInfo playerInfo;
ObjectInfo monsterInfo;

//Ctrl+K+C , Ctrl+K+U   주석 처리, 해제 단축키
int main()
{
    //int flag;
    //flag = (1 << 3);  //0b1000 (무적상태) (3을 상수로 만든다면 개발,유지 편함)
    //flag = flag | (1<<2); //0b1100 (변이 상태 추가)
    //bool invincible = ((flag & (1 << 3))!=0);


    /*cout << ENUM_SCISSORS << endl;
    DEFINE_TEST;
    cout << DEFINE_SCISSORS << endl;*/

    //-----스택 프레임-----
    /*int a = 3;
    int b = 5;
    int result = Mul(a, b);
    cout << result << endl;*/


    //지역 변수와 값 전달
    /*int value = 1;
    cout << "increase 호출 전" << value << endl;
    IncreaseValue(value);
    cout << "increase 호출 후" << value << endl;*/

    //호출스택
    //Func1();




}
