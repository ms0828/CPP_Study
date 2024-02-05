#include <iostream>
using namespace std;

#pragma region 포인터 기초~연산까지
//포인터 변수는 32bit(x86) 프로그램으로 실행하면 4byte, 64bit로 실행하면 8byte 고정 크기

//Type은 왜 붙여줄까?
// -> 나중에 포인터를 사용할 때, 해당 주소에 있는 값을 어떻게 해석할지 알기 위해서

//포인터 연산
// 1)주소 연산자(&)
// -주소를 나타내는 연산자
// 2)산술 연산자 (+, -)
// -포인터도 +, - 연산 가능하다.
// -각 포인터 자료형의 타입에 따라 주소값 계산이 바뀜, ex) int포인터는 주소값이 4(4byte)증가함
// 3)간접 연산자 (*)
// -해당 포인터가 가리키는 주소로 접근
// 4)간접 멤버 연산자(->)
// -ex) 구조체(or 클래스)의 특정 멤버를 다룰 때 사용 - '->' + '.'를 한 번에 처리!
// -Player* playerPtr = &ptr;
// -playerPtr->hp = 100;  == (*playerPtr).hp = 100;
//
#pragma endregion

#pragma region 포인터 실습 (rpg 스탯 초기화 예시) & 참조 방식
//스탯 정보를 반환 값으로 하는 함수에서 리턴 값을 받아 초기화하는 방법은 중간에 지역변수(temp)가 복사 되는 과정이 여러번 일어나 비효율적
//매개변수로 주소값을 넣어 초기화하는 방법이 훨씬 효율적

//StatInfo 구조체가 1000바이트짜리 대형 구조체라면?
//-(값 전달) StatInfo로 넘기면 1000바이트가 복사해서 사용
//-(주소 전달) StatInfo*로 넘기면 4바이트 or 8바이트만 사용
//-(참조 전달) StactInfo&로 넘기면 4바이트 or 8바이트만 사용
//      - 참조 방식 사용하면 주소 전달 방식의 메모리 측면 장점을 얻고, 일반 변수처럼 사용할 수 있는 장점까지

#pragma endregion

#pragma region 포인터 vs 참조
//성능 : 똑같음
//편의성 : 참조 승!
// but 참조는 나중에 유지보수 할 때, 실수의 여지가 있음
// -함수 안에서 값을 참조인지 모르고 바꿔버릴수도! -> 해결법 : 매개변수에 (const StatInfo& info) 처럼 'const'를 붙인다.
//
// -위 해결법 맥락에서 포인터도 const 사용 가능!
//  - * 기준으로 앞에 붙이느냐, 뒤에 붙이느냐에 따라 다름
//  - 위 예시에서 매개변수 info의 주소 값을 고정하느냐 vs 주소가 가리키는 데이터를 고정하느냐
// - 뒤 : (StatInfo* const info) info라는 바구니의 내용물(주소)를 바꿀 수 없음
// - 앞 : (const StatInfo* info) info가 가리키는 메모리의 내용(값)을 바꿀 수 없음, info 바구니의 주소 값은 바꿀 수 있음 
//
//초기화 여부
// -참조 타입은 생성과 동시에 초기화 필수 (참조하는 대상이 없으면 안됨)
// -참조 타입은 nullptr 개념이 없음. (nullptr가 될 수 있으면 포인터를 사용해야함)
// 
//포인터에서 Null은 nullptr 사용
//
// Rookiss 선호 스타일
// -없는 경우도 고려해야 한다면 포인터 (null 체크는 필수)
// -바뀌지 않고 읽는 용도만 사용하면, const를 붙여서 사용 (const ref&)
//  
//
#pragma endregion 

#pragma region 배열
//배열 선언의 크기는 상수여야 함
//ex)StatInfo monster[10];
// 
//배열의 이름은 시작 위치를 가리키는 포인터로 동작
//ex) auto WhoAml = monsters 로 확인 가능 - WhoAml 자료형은 StatInfo *
//ex) StatInfo *monster_0 = monsters
//ex) StatInfo& monster_1 = *(monsters+1)   /아래 방식과 다르게, 이 부분은 특정 배열 값의 주소를 받은 것!
// -    StatInfo monster_1 = *(monsters+1) /위 방식과 차이점 생각하기, 이 부분은 구조체 메모리에 특정 배열 값을 복사한 것!
//
//배열의 메모리 접근법
//- 1.monsters + 1  /포인터 연산으로 접근 -> 주소
//- 2.monsters[1]   /-> 특정 배열의 값(내용)
//      - *(monsters+1) = monster[1]
// 
//배열 초기화 문법
//int num[5] = {0} : 전부다 0으로 초기화
//int num[10] = {1,2,3,4,5} : 5 이후 나머지는 값은 0으로 초기화
//int num[] = {1,2,3,4,5}   : 배열 요소 개수에 맞는 크기의 배열로 만들어줌
// 
//
#pragma endregion

#pragma region 포인터 vs 배열 
//포인터와 배열은 같을까? (문자열 예시)
// const char *test1 = "Hello World"        / test1 [ 주소 ]  <= 8byte
// 'H'로 시작하는 메모리 주소를 test1 바구니에다가 복사 (어셈블리어로 확인)
//
// char test2[] = "Hello World;
// .data 주소[H][e][l][l][o][][W][o][r][l][d][W0]     <= "Hello World"
// [H][e][l][l][][][][].. <= test2[][][][].. /  어셈블리어로 보면 위 메모리를 test2라는 순차적인 4byte씩 배열 바구니에 복사
// 
//  결론 배열은 주소를 담는 바구니(포인터)가 아니라, 같은 데이터끼리 붙어있는 바구니 모음
//   - 다만 배열 이름은 바구니 모음의 시작주소
//
// 
// 배열(이름)을 함수의 인자로 넘기면?
// - 컴파일러가 알아서 포인터로 치환한다. (char[] -> char *)
//
#pragma endregion


#pragma region 다중 포인터
//
// 아래 코드로 정리
#pragma endregion



void SetMessage(const char* a)
{
    //*a = "Bye";  /const 없으면 이렇게 할 수 있고, 이렇게 하면 변경됨
    a = "Bye";  // <-- 결과는 안바뀐다.
}
//const인 char를 포인터를 사용하여 원격으로 바꿈 (이중 포인터 사용)
void SetMessage(const char** a)
{
    *a = "Bye";
}

void SetMessage2(const char*& a)
{
    a = "Bye";
}


int main()
{
#pragma region 이론
    //int num = 1;
    //int* ptr = &num;


    //타입이 불일치할 때 문제 예시
    //- int64(8byte)크기 포인터에 8byte 크기의 값을 넣음
    //- 그러나 ptr2는 num을 가리키고 있고, num은 4byte 크기의 메모리만 할당되어있음. -> 문제 발생
   // __int64* ptr2 = (__int64*)&num;
    //*ptr2 = 0xAABBCCDDEEFF;  
    
    
    //포인터 연산
    // 2)산술 연산자(+,-)
    // -메모리 주소 1차이는 1바이트를 의미한다. (컴퓨터가 메모리 주소를 표현하는 방법임 그냥)
    //ptr += 1;  //ptr주소가 4증가함 -> 왜? : int형 포인터이기 때문에, 다음 주소는 다음 int형 메모리 주소를 예측한 값, 따라서 포인터 자료형의 타입에 따라 다르다.
    // 3)간접 연산자(*)
    //int value = *ptr;   //ptr이 가리키는 주소로 가서 값을 가져옴

#pragma endregion 
    
#pragma region 참조
    //참조 타입
    //로우레벨(어셈블리) 관점에서 실제 작동 방식은 int*와 100% 똑같음
    //사용은 일반 변수처럼 사용
    // = number라는 바구니에 reference라는 다른 이름을 지어준 것과 같음
    int number = 1;
    int& reference = number;
    reference = 3;
    cout << number << endl;
#pragma endregion

#pragma region 다중 포인터


    // .rdata [H][e][l][l][o][\0]
    //msg [ Hello의 시작 주소 ] << 8byte 
    const char* msg = "Hello";
    // 스택 구조
    //[매개변수][RET][지역변수(msg[ Hello 시작 주소 ])] [매개변수(a(Hello 시작 주소) --> Bye 시작 주소)][RET][지역변수]
    //위 스택 구조로는 매개변수 a(Hello -> Bye)는 복사된 것이기에 함수 끝나면 사라짐  (msg와 a가 같은 것이 아니다!) (함수 내부에서는 a가 "Bye"를 가리키게 된다 쳐도 함수 밖 msg는 그대로인 이유)

    SetMessage(msg);
    //cout << msg << endl;

    // .rdata [H][e][l][l][o][\0]
    //msg [ Hello 주소 ] << 8byte
    //pp [ &msg ] << 8byte
    const char** pp = &msg;
    //[매개변수] [RET] [지역변수(msg[ "Hello" ]의 주소)] [매개변수(a(&msg))][RET][지역변수]
    SetMessage(pp);

    cout << msg << endl;


    //          나의 정리
    const char* ptr = "Hello";
    //ptr = "Bye";
    //위 결과는 바뀐다. but 함수에서 매개변수로 넘겨 바꾸는 것은 안바뀐다.
    // [매개변수][RET][지역변수(ptr[ Hello 시작 주소 ])] [매개변수(a [ Hello 시작 주소 ] --> a [ Bye 시작 주소] ][RET][지역변수]    /주소를 넘겨도 주소 값이 복사되는 것은 일반 변수와 동일!! (ptr과 a는 같은 것이 아니다!!)
    //   따라서 함수에서 바꾸려면 *ptr을 사용해서 ptr이 가리키는 메모리를 접근해야한다. but *로 접근했을 때, const인 "Hello"를 바꾸는 것이 되기 때문에 불가능하다.
    
    const char** ptr2 = &ptr;
    *ptr2 = "Bye";
    //위 케이스도 당연히 바뀐다. 이것을 함수에서 바꾸려면?
    // [매개변수][RET][지역변수(ptr2[ ptr[ "Hello" 주소 ] ])] [매개변수(a[ptr 주소] --> (*a = ptr) *a = "Bye"))][RET][지역변수]
    // 위 결과로는 ptr이 "Bye"로 바뀌게 된다. -> 그냥 포인터를 매개변수로 넘겼을 때, *ptr로 const인 "Hello"를 바꾸는 것이 아닌, 이중 포인터를 사용해서 ptr이 가리키는 곳을 "Bye"로 바꿀 수 있게 됨.
    // SetMessage(const char** a)
    // {
    //      *a = "Bye";
    // }
    //
#pragma endregion

    
}   

