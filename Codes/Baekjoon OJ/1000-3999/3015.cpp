#include <iostream>
#include <stack>
using namespace std;

const int MAX = 500000;

int height[MAX];
int Count[MAX];

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", &height[i]);

	for (int i = 0; i < n; i++)
		Count[i] = 1;

	stack<int> people;
	long long ans = 0;

	for (int i = 0; i < n; i++) {
		int clone = 1;

		while (!people.empty() && height[i] >= height[people.top()]) {
			ans += Count[people.top()];
			if (height[i] == height[people.top()]) clone += Count[people.top()];
			people.pop();
		}

		if (!people.empty() && height[i] < height[people.top()]) ans++;

		people.push(i);
		Count[i] = clone;
	}

	printf("%lld", ans);

	return 0;
}
/*//////////////////////////////////////////////////////////////////////
문제 해법		: 스택의 활용. 기준 키보다 작은 키는 스택에서 빼고, 같거나 큰 키는 유지. 이때 같은 키 처리가 중요(일단 스택에서 뺀 후, 다시 넣음).
접근 방식		:
결정적 깨달음		:
오답 원인		: 1. 기준 키와 같은 키를 처리하지 못함.
				  2. 이중 for문의 변수명을 같게 함
				  3. 최악의 경우 O(n^2)의 시간복잡도(같은 키)
*///////////////////////////////////////////////////////////////////////