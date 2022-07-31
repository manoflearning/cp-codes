#include <iostream>
#include <cmath>
#define ll long long
using namespace std;

struct xy {
	ll x; ll y;
};

int N;
double total;
xy dot[10000];

ll CCW(xy a, xy b, xy c);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	cout << fixed; cout.precision(1);

	cin >> N;

	for (int i = 0; i < N; i++)
		cin >> dot[i].x >> dot[i].y;

	for (int i = 1; i < N - 1; i++) {
		total += CCW(dot[i], dot[i + 1], dot[0]);
	}

	if (total < 0) total = -total;
	cout << total / 2;

	return 0;
}

ll CCW(xy a, xy b, xy c) {
	xy A = { b.x - a.x, b.y - a.y }, B = { c.x - a.x, c.y - a.y };
	ll flag = A.x * B.y - A.y * B.x;
	return flag;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: CCW. 한 점을 중심으로, 그 점을 포함하지 않은 모든 직선의 외적값의 절반을 전부 더해서 절댓값 연산을 취하면, 다각형의 크기를 알 수 있다. 
결정적 깨달음		: 
시간복잡도		: 
오답 원인		: 1.  
				  2.
*/////////////////////////////////////////////////////////////////////