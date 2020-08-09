#include <iostream>
#include <map>
using namespace std;

long long n, p, q;
map<long long, long long> bst;

long long eterArr(long long x);

int main() {
	cin >> n >> p >> q;

	cout << eterArr(n);

	return 0;
}

long long eterArr(long long x) {
	map<long long, long long>::iterator ret = bst.find(x);
	//memoization
	if (ret != bst.end()) return ret->second;
	//base case
	if (x == 0) return 1;

	long long ans1 = eterArr(x / p), ans2 = eterArr(x / q);

	bst.insert({ x / p, ans1 });
	bst.insert({ x / q, ans2 });

	return ans1 + ans2;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 동적계획법, 이진 탐색 트리
접근 방식		: n == 10^12일 때 메모이제이션을 배열로 구현하기 위해서는 배열의 크기를 10^12로 잡아야 한다. 그러나 이진 탐색 트리를 활용한다면 비록 탐색에는 O(lgn)이 걸리긴 하나, 메모리 효율을 크게 높일 수 있다.
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////