#include <iostream>
#include <cmath>
#include <algorithm>
#define ld long double
using namespace std;

struct xy {
	ld x; ld y;
};

xy N[2000][2], M[2000][2];

ld find_min(xy a, xy b, xy c, xy d);
ld find_len(xy a, xy b, xy c);
bool DotProduct(xy a, xy b, xy c);
bool isMeet(xy a, xy b, xy c, xy d);
ld CCW(xy a, xy b, xy c);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	cout << fixed; cout.precision(11);
	
	int n, m; cin >> n >> m;

	for (int i = 0; i < n; i++)
		cin >> N[i][0].x >> N[i][0].y >> N[i][1].x >> N[i][1].y;
	for(int i = 0; i < m; i++)
		cin >> M[i][0].x >> M[i][0].y >> M[i][1].x >> M[i][1].y;

	ld ans = 1e9;

	for (int i = 0; i < n; i++) {
		for (int l = 0; l < m; l++) {
			ans = min(ans, find_min(N[i][0], N[i][1], M[l][0], M[l][1]));
		}
	}

	cout << ans;

	return 0;
}

ld find_min(xy a, xy b, xy c, xy d) {
	//if (isMeet(a, b, c, d)) return 0;

	ld ret = 1e9;
	//선분의 끝 간의 거리 구하기
	ret = min(ret, sqrt(pow(c.x - a.x, 2) + pow(c.y - a.y, 2)));
	ret = min(ret, sqrt(pow(c.x - b.x, 2) + pow(c.y - b.y, 2)));
	ret = min(ret, sqrt(pow(d.x - a.x, 2) + pow(d.y - a.y, 2)));
	ret = min(ret, sqrt(pow(d.x - b.x, 2) + pow(d.y - b.y, 2)));
	//한 점에서 내린 수선의 길이 구하기
	if (DotProduct(a, b, c))
		ret = min(ret, find_len(a, b, c));
	if (DotProduct(a, b, d))
		ret = min(ret, find_len(a, b, d));
	if (DotProduct(c, d, a))
		ret = min(ret, find_len(c, d, a));
	if (DotProduct(c, d, b))
		ret = min(ret, find_len(c, d, b));

	return ret;
}
bool DotProduct(xy a, xy b, xy c) {
	xy A = { b.x - a.x, b.y - a.y }, B = { c.x - a.x, c.y - a.y };
	double flag1 = A.x * B.x + A.y * B.y;
	flag1 /= sqrt(pow(A.x, 2) + pow(A.y, 2)) + sqrt(pow(B.x, 2) + pow(B.y, 2));

	A = { a.x - b.x, a.y - b.y }, B = { c.x - b.x, c.y - b.y };
	double flag2 = A.x * B.x + A.y * B.y;
	flag2 /= sqrt(pow(A.x, 2) + pow(A.y, 2)) + sqrt(pow(B.x, 2) + pow(B.y, 2));

	return flag1 >= 0 && flag2 >= 0;
}
ld find_len(xy a, xy b, xy c) {
	ld ret = CCW(a, b, c) / sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
	return fabs(ret);
}
bool isMeet(xy a, xy b, xy c, xy d) {
	int ab = CCW(a, b, c) * CCW(a, b, d);
	int cd = CCW(c, d, a) * CCW(c, d, b);

	if (ab == 0 && cd == 0) {
		pair<int, int> A = { a.x, a.y }, B = { b.x,b.y }, C = { c.x,c.y }, D = { d.x,d.y };
		if (A > B) swap(A, B);
		if (C > D) swap(C, D);
		return A <= D && C <= B;
	}
	else return ab <= 0 && cd <= 0;
}
ld CCW(xy a, xy b, xy c) {
	xy A = { b.x - a.x, b.y - a.y }, B = { c.x - a.x, c.y - a.y };
	ld flag = A.x * B.y - A.y * B.x;

	return flag;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: CCW. 벡터의 외적을 통해 두 선분의 교차 여부를 알 수 있다. 벡터의 외적과 내적을 통해 두 선분 간의 최단거리를 알 수 있다.
결정적 깨달음		: 벡터의 내적을 통해 어떤 한 점에서 한 선분으로 수선을 내리는 것이 가능한지 판단 가능.
시간복잡도		: O(nm)
오답 원인		: 1. CCW의 절댓값은 두 벡터로 인해 생기는 평행사변형의 크기와 같지만, CCW의 값이 음일수도 있음을 고려하지 못함.
				  2.
*/////////////////////////////////////////////////////////////////////