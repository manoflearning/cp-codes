#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int n, m;
	cin >> n >> m;

	deque<int> arr;

	for (int i = 1; i <= n; i++)
		arr.push_back(i);

	int count = 0;

	for (int test = 0; test < m; test++) {
		int x;
		cin >> x;

		int count1 = 0, count2 = 0;
		while (arr.front() != x) {
			arr.push_back(arr.front());
			arr.pop_front();

			count1++;
		}
		count2 -= count1;
		do {
			arr.push_front(arr.back());
			arr.pop_back();

			count2++;
		} while (arr.front() != x);

		count += min(count1, count2);

		arr.pop_front();
	}

	cout << count;

	return 0;
}
/*//////////////////////////////////////////////////////////////////////
문제 해법		: 덱이 시작과 끝에서 모두 삽입과 삭제가 가능하다는 점을 활용
접근 방식		:
결정적 깨달음		:
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////