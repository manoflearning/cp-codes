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

struct yx {
    ll y, x;
};

int n;
vt<yx> chd, sw;
vt<int> p;
ll d[11][12];
int vi[11], vi2[11];
vt<int> adj[11];
vt<pii> ans;

void init() {
    chd.clear();
    sw.clear();
    p.clear();
    memset(vi, 0, sizeof(vi));
    memset(vi2, 0, sizeof(vi2));
    FOR(11) adj[i].clear();
    ans.clear();
}

ll dist(yx a, yx b) {
    return (a.y - b.y) * (a.y - b.y) + (a.x - b.x) * (a.x - b.x);
}

int psum[11][12];

int simul(int idx) {
    if (idx == n) return 1;

    ll mn = 1e18;
    EACH(i, adj[p[idx]]) {
        if (!vi2[i]) {
            mn = min(mn, d[p[idx]][i]);
        }
    }
    
    if (mn == 1e18) return 0;
    
    int x = -1, mn2 = INF;
    EACH(i, adj[p[idx]]) {
        if (!(!vi2[i] && mn == d[p[idx]][i])) continue;

        if (mn2 > psum[n - 1][i] - psum[idx][i]) {
            mn2 = psum[n - 1][i] - psum[idx][i];
            x = i;
        }
    }

    if (vi2[x]) return 0;

    vi2[x] = 1;
    if (simul(idx + 1)) {
        ans.push_back({ p[idx], x });
        return 1;
    }
    vi2[x] = 0;

    return 0;
}

void permu(int idx) {
    if (idx == n) {
        if (ans.empty()) {
            FOR(i, n) {
                memset(psum[i], 0, sizeof(psum[i]));
                EACH(j, adj[p[i]]) {
                    psum[i][j]++;
                }
                if (i > 0) {
                    FOR(j, 12) {
                        if (i > 0) psum[i][j] += psum[i - 1][j];
                    }
                }
            }
            
            simul(0);
        }
        return;
    }

    FOR(i, n) {
        if (vi[i]) continue;
        vi[i] = 1;
        p.push_back(i);
        permu(idx + 1);
        vi[i] = 0;
        p.pop_back();
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
	
	int tc; cin >> tc;

    FOR(t, 1, tc + 1) {
        cout << "Case #" << t << ": ";

        cin >> n;

        chd.resize(n);
        sw.resize(n + 1);

        EACH(i, chd) cin >> i.y >> i.x;
        EACH(i, sw) cin >> i.y >> i.x;

        FOR(n) {
            FOR(j, n + 1) {
                d[i][j] = dist(chd[i], sw[j]);
            }
            FOR(j, 1, n + 1) {
                if (d[i][j] <= d[i][0]) {
                    adj[i].push_back(j);
                }
            }
        }

        permu(0);

        if (sz(ans)) {
            cout << "POSSIBLE\n";
            FOR(i, sz(ans) - 1, -1, -1) {
                cout << ans[i].fr + 1 << ' ' << ans[i].sc + 1 << '\n';
            }
        }
        else cout << "IMPOSSIBLE\n";

        init();
    }

	return 0;
}