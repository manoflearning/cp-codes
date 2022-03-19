#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

struct line {
	int x, y1, y2;
	bool isStart;
	line() : line(0, 0, 0, false) {}
	line(int sx, int sy1, int sy2, bool sIsSt) :
		x(sx), y1(sy1), y2(sy2), isStart(sIsSt) {}
	bool operator <(line& O) {
		return x < O.x;
	}
};

vector<line> arr;
int flag;
vector<int> sgtr, cnt;

void update(int L, int R, int n, int nL, int nR, int v);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	//input
	int N; cin >> N;

	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		arr.push_back(line(x1, y1, y2, true));
		arr.push_back(line(x2, y1, y2, false));
	}
	
	sort(arr.begin(), arr.end());

	//세그먼트 트리 형성
	for (flag = 1; flag < 30000; flag *= 2);
	sgtr.resize(2 * flag);
	cnt.resize(2 * flag);

	//line 순회
	ll ans = 0;
	for (int i = 0; i < arr.size(); i++) {
		auto& l = arr[i];

		if (i != 0) ans += sgtr[1] * (l.x - arr[i - 1].x);

		if (l.isStart) update(l.y1 + 1, l.y2, 1, 1, flag, 1);
		else update(l.y1 + 1, l.y2, 1, 1, flag, -1);
	}

	cout << ans << '\n';

	return 0;
}

void update(int L, int R, int n, int nL, int nR, int v) {
	if (R < nL || nR < L) return;
	
	if (L <= nL && nR <= R) cnt[n] += v;
	else {
		int mid = (nL + nR) / 2;
		update(L, R, 2 * n, nL, mid, v);
		update(L, R, 2 * n + 1, mid + 1, nR, v);
	}
	
	if (cnt[n] > 0) sgtr[n] = (nR - nL + 1);
	else {
		if (nL == nR) sgtr[n] = 0;
		else sgtr[n] = sgtr[2 * n] + sgtr[2 * n + 1];
	}
}