#include <iostream>
#include <algorithm>
using namespace std;

#pragma region 알고리즘 라이브러리
// 
// 가장 많이 사용되는 알고리즘 라이브러리 기능들
// find
// find_if
// count
// count_if
// all_of
// any_of
// none_of
// for_each
// remove
// remove_if	(* 주의점)
// - remove_if는 predicate에 해당하는 요소를 삭제하는 기능
// - 원리는 predicate에 해당하지 않는 요소를 앞으로 순서대로 배치하고,
//		탐색이 끝나면 나머지 요소들은 뒤에 그대로 배치한다. 반환 값은 나머지 요소의 첫번째 iterator
// => 그래서 auto it = remove_if(v.begin(),v.end(), IsOdd());
//			 v.erase(it, v.end());
//   처럼 erase와 세트로 사용된다.
// 
// 
// 

#pragma endregion

int main()
{

}

