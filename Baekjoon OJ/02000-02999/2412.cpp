//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

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
const int dx[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dz[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, t;
vector<pii> a;
map<pii, int> Hash;
int dist[50505];

int bfs() {
    memset(dist, -1, sizeof(dist));

    queue<pii> q;
    q.push({ 0, 0 });
    dist[Hash[{ 0, 0 }]] = 0;

    while (sz(q)) {
        auto [x, z] = q.front();
        q.pop();
        
        if (z == t) return dist[Hash[{ x, z }]];

        for (int i = 0; i < 8; i++) {
            for (int j = 1; j <= 2; j++) {
                for (int k = 1; k <= 2; k++) {
                    int nx = x + j * dx[i], nz = z + k * dz[i];
                    //cout << nx << ' ' << nz << ' ' << Hash.count({ nx, nz }) << '\n';
                    if (Hash.count({ nx, nz }) && dist[Hash[{ nx, nz }]] == -1) {
                        dist[Hash[{ nx, nz }]] = dist[Hash[{ x, z }]] + 1;
                        q.push({ nx, nz });
                    }
                }
                
            }
        }
    }

    return -1;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> t;
    a.resize(n);
    for (auto& i : a) cin >> i.fr >> i.sc;
    a.push_back({ 0, 0 });

    for (int i = 0; i < n + 1; i++) Hash[a[i]] = i;

    int ans = bfs();
    cout << ans;

	return 0;
}