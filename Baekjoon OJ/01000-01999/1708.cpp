// BOJ 1708 AC Code
// https://www.acmicpc.net/problem/1708
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

struct point {
	ll x, y;
    bool operator<(const point& rhs) const {
        if (x != rhs.x) return x < rhs.x;
		else return y < rhs.y;
    }
};

int N;
vector<point> p;
vector<int> st, en;

ll ccw(point& a, point& b, point& c) {
	// res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int i = 0; i < N; i++) {
		int x, y;
		cin >> x >> y;
		p.push_back({ x, y });
	}

	sort(p.begin(), p.end());

	st.push_back(0);
	st.push_back(1);
	for (int next = 2; next < N; next++) {
		while (st.size() >= 2) {
			int first = st.back();
			st.pop_back();
			int second = st.back();
			if (ccw(p[second], p[first], p[next]) > 0) {
				st.push_back(first);
				break;
			}
		}
		st.push_back(next);
	}

    en.push_back(N - 1);
    en.push_back(N - 2);
    for (int next = N - 3; next >= 0; next--) {
		while (en.size() >= 2) {
			int first = en.back();
			en.pop_back();
			int second = en.back();
			if (ccw(p[second], p[first], p[next]) > 0) {
				en.push_back(first);
				break;
			}
		}
		en.push_back(next);
	}

	cout << (int)st.size() + (int)en.size() - 2;

	return 0;
}