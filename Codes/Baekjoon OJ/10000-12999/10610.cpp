#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(char a, char b);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	string N; cin >> N;

	sort(N.begin(), N.end(), cmp);

	if (N.back() != '0') {
		cout << -1;
		return 0;
	}

	int sum = 0;
	for (char x : N)
		sum += x - '0';

	if (sum % 3 != 0) {
		cout << -1;
		return 0;
	}

	cout << N;

	return 0;
}

bool cmp(char a, char b) {
	return a > b;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 정렬
결정적 깨달음		: 1의 자리가 0이고, 각 자리수의 합이 3의 배수라면, 3의 배수이다. 그렇지 않다면 3의 배수가 아니다.
시간복잡도		: O(nlgn)
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////