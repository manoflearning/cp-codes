#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first 
#define sc second
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

#define EXPAND( x ) x // Use this if MS Visual Studio doesn't expand __VA_ARGS__ correctly
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) EXPAND( GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1) )
#define FOR(...) EXPAND( F_ORC(__VA_ARGS__ )(__VA_ARGS__) )
#define EACH(x, a) for (auto& x : a)

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct point {
    ll x, y;
    bool operator<(const point& rhs) const {
        if (x ^ rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
};

int n;
point p[3030];
pii ans[1010];

ll ccw(const point& a, const point& b, const point& c) {
	// res > 0 -> ccw, res < 0 -> cw, res = 0 -> colinear
	ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

point o = { 0, 0 };
bool cmp(const int& a, const int& b) { 
    return ccw(o, p[a], p[b]) > 0;
}

void input() {
    cin >> n;
    FOR(3 * n) {
        ll x, y;
        cin >> x >> y;
        p[i] = { x, y };
    }
}

int getBlue(vt<int>& a) {
    // (1. x값이 가장 작은, 2. x값이 가장 작은 점이 여러 개일 경우 y값이 가장 작은) 점 찾기
    FOR(i, 1, sz(a)) {
        if (p[a[i]] < p[a[0]]) swap(a[0], a[i]);
    }

    // p[a[0]]을 기준으로 해서 각도 정렬 (반시계 방향)
    o = p[a[0]];
    sort(a.begin() + 1, a.end(), cmp);

    // convex hull 찾기
    vt<int> st;
    st.push_back(a[0]);
	st.push_back(a[1]);
	for (int i = 2; i < sz(a); i++) {
        int next = a[i];
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

    //EACH(i, st) cout << i << ' ';
    //cout << '\n';

    // convex hull 상에서 파란 점이 있는지 확인
    int bit = 0, x = -1;
    EACH(i, st) if (i < n) { bit = 1; x = i; }

    // 만약 파란 점이 없다면 0을 반환
    if (!bit) return 0;

    // 만약 파란 점이 있다면 파란 점을 기준으로 각도 정렬
    FOR(i, sz(a)) if (a[i] == x) { swap(a[0], a[i]); break; }
    o = p[a[0]];
    sort(a.begin() + 1, a.end(), cmp);

    return 1; // 1을 반환
}

void dc(vt<int>& a) {
    if (a.empty()) return;

    int bit = getBlue(a);

    //EACH(i, a) cout << i << ' ';
    //cout << '\n';

    // 만약 파란 점이 있다면
    if (bit) {
        int res = 0, idx1 = -1, idx2 = -1;
        FOR(i, 1, sz(a)) {
            if (a[i] < n) res += 2;
            else res -= 1;

            if (res == -1 && idx1 == -1) idx1 = i;
            if (res == -2 && idx2 == -1) idx2 = i;
        }

        ans[a[0]] = { a[idx1], a[idx2] };

        vt<int> b, c, d;
        FOR(i, 1, idx1) b.push_back(a[i]); // [1, idx1 - 1] 구간
        FOR(i, idx1 + 1, idx2) c.push_back(a[i]); // [idx1 + 1, idx2 - 1] 구간
        FOR(i, idx2 + 1, sz(a)) d.push_back(a[i]); // [idx2 + 1, sz(a) - 1] 구간
        
        dc(b); dc(c); dc(d);
    }
    // 만약 파란 점이 없다면
    else {
        // 점들의 합이 0인 [1, j] 구간 찾기
        // convex hull 상의 어떤 점에서 시작하더라도, 그러한 구간을 찾을 수 있음
        for (int i = 0; i < 2; i++) {
            int res = 0;
            vt<int> b;
            for (int j = 1; j < sz(a); j++) {
                if (a[j] < n) res += 2;
                else res -= 1;
                b.push_back(a[j]);
                
                if (res == 0) {
                    dc(b);
                    b.clear();

                    b.push_back(a[0]);
                    FOR(k, j + 1, sz(a)) b.push_back(a[k]);
                    dc(b);
                    return;
                }
            }

            reverse(a.begin() + 1, a.end());
        }
        assert(0);
    }
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

	input();

    vt<int> a;
    FOR(3 * n) a.push_back(i);
    dc(a);

    FOR(n) {
        cout << ans[i].fr - n + 1 << ' ';
        cout << ans[i].sc - n + 1 << '\n';
    }

	return 0;
}