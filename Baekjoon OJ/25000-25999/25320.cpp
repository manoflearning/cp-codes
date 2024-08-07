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

struct block {
    int isA, num;
};

int n, m;
vt<int> cnt, nxt;
vt<block> bl;
priority_queue<int> unused, used;

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
    
    // input
	cin >> n >> m;

    cnt.resize(2 * n + 1);
    nxt.resize(2 * n + 1);
    bl.resize(m);

    int isValid = 1;
    EACH(i, bl) {
        string s1, s2;
        cin >> s1 >> s2 >> i.num;
        
        if (s1 == "A") i.isA = 1;
        if (1 <= i.num && i.num <= 2 * n) {
            cnt[i.num]++;
            if (cnt[i.num] >= 2) isValid = 0;
        }
        else isValid = 0;
    }

    // 예외 처리
    if (!isValid) {
        cout << "NO\n";
        return 0;
    }

    if (!bl.front().isA) {
        cout << "NO\n";
        return 0;
    }

    if (cnt[1] == 0) { //
        cout << "NO\n";
        return 0;
    }

    //
    FOR(i, 1, 2 * n + 1) {
        if (!cnt[i]) unused.push(i);
    }

    FOR(m) {
        if (i < m - 1 && bl[i].isA == bl[i + 1].isA) {
            used.push(bl[i].num);
        }
        else if (i == m - 1 && bl[i].isA) {
            used.push(bl[i].num);
        }
    }

    // 예외 처리 2
    if (sz(unused) < sz(used)) {
        cout << "NO\n";
        return 0;
    }
    
    while (sz(used)) {
        if (used.top() >= unused.top()) {
            cout << "NO\n";
            return 0;
        } 
        nxt[used.top()] = unused.top();
        used.pop(); unused.pop();
    }

    // 정답 출력
    cout << "YES\n";
    FOR(m) {
        cout << (bl[i].isA ? "A" : "B") << ' ' << "BLOCK" << ' ' << bl[i].num << '\n';
        if (bl[i].num == 1) {
            stack<int> st;
            while (sz(unused)) {
                st.push(unused.top());
                unused.pop();
            }

            int b = !bl[i].isA;
            while (sz(st)) {
                cout << (b ? "A" : "B") << ' ' << "CHAIN" << ' ' << st.top() << '\n';
                st.pop(); b = !b;
            }
        }

        if (i < m - 1 && bl[i].isA == bl[i + 1].isA) {
            cout << (bl[i].isA ? "B" : "A") << ' ' << "CHAIN" << ' ' << nxt[bl[i].num] << '\n';
        }
        else if (i == m - 1 && bl[i].isA) {
            cout << (bl[i].isA ? "B" : "A") << ' ' << "CHAIN" << ' ' << nxt[bl[i].num] << '\n';
        }
    }

	return 0;
}