#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#define ll long long
using namespace std;

struct point {
	ll x, y, px, py;
	point() : point(0, 0, 1, 0) {}
	point(int sx, int sy): point(sx, sy, 1, 0) {}
	point(int sx, int sy, int spx, int spy): x(sx), y(sy), px(spx), py(spy) {}
	bool operator <(point& O) {
		if (py * O.px != px * O.py) 
			return py * O.px < px * O.py;
		if (y != O.y) return y < O.y;
		return x < O.x;
	}
};

vector<point> p;

ll ccw(point& a, point& b, point& c);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N; cin >> N;

	p.resize(N);
	for (int i = 0; i < N; i++) {
		int x, y;
		cin >> x >> y;
		p[i] = point(x, y);
	}

	sort(p.begin(), p.end());

	for (int i = 1; i < N; i++) {
		p[i].px = p[i].x - p[0].x;
		p[i].py = p[i].y - p[0].y;
	}

	sort(p.begin() + 1, p.end());

	stack<int> s;
	s.push(0);
	s.push(1);
	for (int next = 2; next < N; next++) {
		while (s.size() >= 2) {
			int first, second;
			first = s.top();
			s.pop();
			second = s.top();
			if (ccw(p[second], p[first], p[next]) > 0) {
				s.push(first);
				break;
			}
		}
		s.push(next);
	}

	cout << s.size() << '\n';

	return 0;
}

ll ccw(point& a, point& b, point& c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}