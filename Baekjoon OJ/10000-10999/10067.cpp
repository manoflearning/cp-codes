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

struct lf {
    ll p, q;
    double s;
    lf() : lf(1, 0) {}
    lf(ll sp, ll sq) : p(sp), q(sq) {}
};

double cross(const lf& u, const lf& v) {
    return (double)(v.q - u.q) / (u.p - v.p);
}

int n, cnt;
ll a[101010], psum[101010];
ll dp[101010][2];
vt<int> dp2[101010][2];
ll ans;
vt<int> ans2;

/*void naiveDP() {
    FOR(i, 1, n) {
        dp[i][1] = psum[i] * (psum[n] - psum[i]);
    }
    FOR(k, 2, cnt + 1) {
        FOR(i, 1, n) {
            FOR(j, 1, i) {
                dp[i][k] = max(dp[i][k], (psum[i] - psum[j]) * (psum[n] - psum[i]) + dp[j][k - 1]);
                // (psum[n] + psum[j]) * psum[i] - psum[j] * psum[n] + dp[j][k - 1] - (psum[i] * psum[i])
            }
        }
    }
}*/

void convexHullTrick() {
    FOR(i, 1, n) {
        dp[i][1] = psum[i] * (psum[n] - psum[i]);
        dp2[i][1].push_back(i);
    }

    FOR(k, 2, cnt + 1) {
        int bit = (k & 1);

        vt<lf> ch;
        vt<int> num;
        FOR(i, 2, n) {
            if (a[i - 1] && dp[i - 1][k - 1]) {
                lf g(psum[n] + psum[i - 1], -psum[i - 1] * psum[n] + dp[i - 1][!bit]);
                while (sz(ch)) {
                    g.s = cross(g, ch.back());
                    if (ch.back().s < g.s) break;
                    ch.pop_back();
                    num.pop_back();
                }
                ch.push_back(g);
                num.push_back(i - 1);
            }

            if (ch.empty()) continue;

            int l = 0, r = sz(ch) - 1;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (psum[i] < ch[mid].s) r = mid - 1;
                else l = mid;
            }

            int fpos = l;
            dp[i][bit] = ch[l].p * psum[i] + ch[l].q - psum[i] * psum[i];
            dp2[i][bit] = dp2[num[l]][!bit];
            dp2[i][bit].push_back(i);
        }
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

    // input & build prefix sum
	cin >> n >> cnt;
    FOR(n) cin >> a[i + 1];
    
    FOR(i, 1, n + 1)
        psum[i] = a[i] + psum[i - 1];
    
    //naiveDP();

    // Edge Case
    int pCnt = 0;
    FOR(i, 1, n + 1) {
        if (a[i]) pCnt++;
    }
    if (pCnt <= cnt) {
        FOR(i, 1, n) {
            if (a[i]) ans2.push_back(i);
        }
        FOR(i, 1, n) {
            if (sz(ans2) == cnt) break;
            if (!a[i]) ans2.push_back(i);
        }

        sort(all(ans2));
        
        ans += psum[ans2[0]] * (psum[n] - psum[ans2[0]]);
        FOR(i, 1, sz(ans2)) {
            int u = ans2[i - 1], v = ans2[i];
            ans += (psum[v] - psum[u]) * (psum[n] - psum[v]);
        }

        cout << ans << '\n';
        EACH(i, ans2) cout << i << ' ';
        
        return 0;
    }

    // Convex Hull Trick
    convexHullTrick();

    FOR(i, 1, n) {
        if (ans < dp[i][cnt]) {
            ans = dp[i][cnt];
            ans2 = dp2[i][cnt];
            /*ans2.clear();
            int now = i;
            ans2.push_back(now);
            FOR(i, cnt, 1, -1) {
                ans2.push_back(dp2[now][i]);
                now = dp2[now][i];
            }*/
        }
    }

    cout << ans << '\n';
    EACH(i, ans2) 
        cout << i << ' ';

	return 0;
}