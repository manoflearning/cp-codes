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

int ind[101010], w[101010], w2[101010], sum[101010], sum2[101010];
vt<int> adj[101010];

void init(int m) {
    FOR(i, 0, m + 1) {
        ind[i] = w[i] = w2[i] = sum[i] = sum2[i] = 0;
        adj[i].clear();
    }
}

/*int dfs1(int now) {
    int ret = w[now];
    EACH(i, adj[now]) {
        ret += dfs1(i);
    }
    return ret;
}
int dfs2(int now) {
    int ret = w2[now];
    EACH(i, adj[now]) {
        ret += dfs1(i);
    }
    return ret;
}*/

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

    while (tc--) {
        int n; cin >> n;
        string ss, ts;
        cin >> ss >> ts;
        vt<int> s, t;
        EACH(i, ss) s.push_back(i - 'a');
        EACH(i, ts) t.push_back(i - 'a');

        vt<int> cnts(3), cntt(3);
        FOR(n) {
            cnts[s[i]]++, cntt[t[i]]++;
        }

        //예외처리
        if (cnts[0] != cntt[0] || cnts[1] != cntt[1] || cnts[2] != cntt[2]) {
            cout << "NO\n";
            continue;
        }

        // 
        vt<int> a, b;
        FOR(n) {
            if (s[i] != 1) a.push_back(s[i]);
            if (t[i] != 1) b.push_back(t[i]);
        }

        if (a != b) cout << "NO\n";
        else {
            int cntb = 0, cntac = 0, m;
            FOR(n) {
                if (s[i] == 1) cntb++;
                if (s[i] == 2) {
                    adj[cntac].push_back(cntac + 1);
                    ind[cntac + 1]++;
                    //cout << cntac << ' ' << cntac + 1 << '\n';
                }
                if (s[i] == 0 || s[i] == 2) w[cntac] = cntb, cntac++, cntb = 0;
            }
            w[cntac] = cntb;
            cntb = 0;

            m = cntac;
            FOR(i, n - 1, -1, -1) {
                if (s[i] == 1) cntb++;
                if (s[i] == 0) {
                    adj[cntac].push_back(cntac - 1);
                    ind[cntac - 1]++;
                    //cout << cntac << ' ' << cntac - 1 << '\n';
                }
                if (s[i] == 0 || s[i] == 2) cntac--, cntb = 0;
            }
            
            cntb = 0;
            FOR(n) {
                if (t[i] == 1) cntb++;
                if (t[i] == 0 || t[i] == 2) w2[cntac] = cntb, cntac++, cntb = 0;
            }
            w2[cntac] = cntb;
            cntb = 0;
            
            int isP = 1;
            queue<int> q;
            FOR(i, 0, m + 1) {
                if (ind[i] == 0) {
                    q.push(i);
                    isP &= (w[i] >= w2[i]);
                    //isP &= (dfs1(i) == dfs2(i));
                }
                sum[i] = w[i]; sum2[i] = w2[i];
            }

            while (sz(q)) {
                int now = q.front();
                q.pop();
                //cout << now << ' ' << sum[now] << ' ' << w2[now] << '\n';
                isP &= (sum[now] >= sum2[now]);

                EACH(i, adj[now]) {
                    sum[i] += sum[now];
                    sum2[i] += sum2[now];
                    ind[i]--;
                    if (!ind[i]) q.push(i);
                }
            }

            if (isP) cout << "YES\n";
            else cout << "NO\n";

            init(m);
        }
    }

	return 0;
}