#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct gsb {
	int g, s, b;
};

gsb arr[1005];

bool cmp(gsb a, gsb b) {
	if (a.g != b.g) return a.g > b.g;
	if (a.s != b.s) return a.s > b.s;
	if (a.b != b.b) return a.b > b.b;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int N, K;
	cin >> N >> K;

	gsb en;

	for (int i = 1; i <= N; i++) {
		int x; cin >> x;
		cin >> arr[i].g >> arr[i].s >> arr[i].b;
		if (x == K) en = arr[i];
	}

	sort(arr + 1, arr + N + 1, cmp);

	for (int i = 1; i <= N; i++) {
		if (arr[i].g == en.g && arr[i].s == en.s && arr[i].b == en.b) {
			cout << i;
			break;
		}
	}

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 정렬
결정적 깨달음		: 
시간복잡도		: O(nlgn)
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////