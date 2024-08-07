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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAX = 202020;

int st, en;
int dist[MAX];

int bfs() {
    queue<int> q;
    dist[st] = 0;
    q.push(st);

    while (sz(q)) {
        int v = q.front();
        q.pop();

        if (v > 0 && dist[v - 1] == -1) {
            dist[v - 1] = dist[v] + 1;
            q.push(v - 1);
        }
        if (v + 1 < MAX && dist[v + 1] == -1) {
            dist[v + 1] = dist[v] + 1;
            q.push(v + 1);
        }
        if (v * 2 < MAX && dist[v * 2] == -1) {
            dist[v * 2] = dist[v] + 1;
            q.push(v * 2);
        }
    }

    return dist[en];
}

vector<int> ans;
void f(int x) {
    ans.push_back(x);
    if (x == st) return;
    
    if (x > 0 && dist[x - 1] + 1 == dist[x]) {
        f(x - 1); return;
    }
    if (x + 1 < MAX && dist[x + 1] + 1 == dist[x]) {
        f(x + 1); return;
    }
    if (!(x & 1) && dist[x / 2] + 1 == dist[x]) {
        f(x / 2); return;
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> st >> en;
    
    memset(dist, -1, sizeof(dist));
    cout << bfs() << '\n';

    f(en);
    for (int i = sz(ans) - 1; i >= 0; i--)
        cout << ans[i] << ' ';

	return 0;
}