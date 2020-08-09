#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct bb {
	int st;
	int en;
};

vector<bb> arr;

bool comp(bb a, bb b);

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int st, en;
		cin >> st >> en;

		arr.push_back({ st, en });
	}

	sort(arr.begin(), arr.end(), comp);

	int ans = 0;

	int end = 0;
	for (int i = 0; i < n; i++) {
		while (i < n && end > arr[i].st) i++;

		if (i < n) {
			end = arr[i].en;
			ans++;
		}
	}

	cout << ans;

	return 0;
}

bool comp(bb a, bb b) {
	if (a.en != b.en) return a.en < b.en;
	return a.st < b.st;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 그리디 알고리즘
접근 방식		: 회의가 언제 끝나냐가 중요. 가능한 회의 중 끝나는 시간이 가장 작은 회의를 고르면, 최적 부분 구조가 성립함.
결정적 깨달음		:
오답 원인		: 1. while문을 무한히 돌릴 수 있음
				  2.
*/////////////////////////////////////////////////////////////////////