#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

struct xy {
	int x; int y;
};

xy arr[3000][2];
int p[3000];
bool visited[3000];

bool isMeet(xy a, xy b, xy c, xy d);
int CCW(xy a, xy b, xy c);
int find(int x);
void merge(int a, int b);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(p, -1, sizeof(p));

	int N; cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> arr[i][0].x >> arr[i][0].y >> arr[i][1].x >> arr[i][1].y;
	}

	for (int i = 0; i < N; i++) {
		for (int l = i + 1; l < N; l++) {
			if (isMeet(arr[i][0], arr[i][1], arr[l][0], arr[l][1])) merge(i, l);
		}
	}

	int cnt = 0, mx = -1;
	for (int i = 0; i < N; i++) {
		int root = find(i);
		if (visited[root]) continue;
		visited[root] = true;
		cnt++;
		mx = max(mx, -p[root]);
	}

	cout << cnt << '\n' << mx;

	return 0;
}

bool isMeet(xy a, xy b, xy c, xy d) {
	int ab = CCW(a, b, c) * CCW(a, b, d);
	int cd = CCW(c, d, a) * CCW(c, d, b);
	
	if (ab == 0 && cd == 0) {
		pair<int, int> A = { a.x, a.y }, B = { b.x, b.y }, C = { c.x, c.y }, D = { d.x, d.y };
		if (A > B) swap(A, B);
		if (C > D) swap(C, D);
		return (A <= D && C <= B);
	}
	else return (ab <= 0 && cd <= 0);
}
int CCW(xy a, xy b, xy c) {
	xy A = { b.x - a.x, b.y - a.y };
	xy B = { c.x - a.x, c.y - a.y };
	int flag = A.x * B.y - A.y * B.x;
	
	if (flag > 0) return 1;
	if (flag < 0) return -1;
	return 0;
}
int find(int x) {
	if (p[x] < 0) return x;
	p[x] = find(p[x]);
	return p[x];
}
void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	p[B] += p[A];
	p[A] = B;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: CCW, 유니온 파인드. 각 선분에 번호를 붙인다. CCW로 선분이 만나는지 여부를 판단. 두 선분이 만날 경우 선분의 번호를 기준으로 union 연산을 한다. 모든 2개의 선분의 조합을 대상으로 연산 수행. 만들어진 그룹의 개수와 선분의 개수 세기
결정적 깨달음		:
시간복잡도		: O(n^2) (union, find 연산은 상수시간 취급)
오답 원인		: 1. 외적값이 모두 0일 경우 예외처리가 필요함
				  2.
*/////////////////////////////////////////////////////////////////////