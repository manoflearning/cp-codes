// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXN = 101;

int N, Q;
ll M;
vector<string> G[MAXN];
map<string, ll> P;
map<string, ll> stockCnt;

void input() {
    cin >> N >> M >> Q;
    for (int i = 1; i <= N; i++) {
        int x;
        string s;
        int y;
        cin >> x >> s >> y;
        G[x].push_back(s);
        P[s] = y;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    while (Q--) {
        int op;
        string s;
        ll p, q;
        cin >> op;

        if (op == 1) {
            cin >> s >> q;
            if (P[s] * q <= M) {
                M -= P[s] * q;
                stockCnt[s] += q;
            }
        }
        else if (op == 2) {
            cin >> s >> q;
            ll sellCnt = min(q, stockCnt[s]);
            M += P[s] * sellCnt;
            stockCnt[s] -= sellCnt;
        }
        else if (op == 3) {
            cin >> s >> q;
            P[s] += q;
        }
        else if (op == 4) {
            cin >> p >> q;
            for (auto& i : G[p]) P[i] += q;
        }
        else if (op == 5) {
            cin >> p >> q;
            for (auto& i : G[p]) {
                double price = P[i];
                price = price * (double)(100 + q) / 100;
                P[i] = (ll)price / 10 * 10;
            }
        }
        else if (op == 6) {
            cout << M << '\n';
        }
        else if (op == 7) {
            ll res = M;
            for (auto& i : stockCnt)
                res += P[i.first] * i.second;
            cout << res << '\n';
        }
    }
}