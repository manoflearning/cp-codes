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

int n, m, en;
pii a[505 * 505 + 505];
int dist[505 * 505 + 505];

vector<int> cal(int v) {
    vector<int> ret;

    int rem = v % m;
    if (!(rem == 0 || rem == n - 1 || rem == n || rem == m - 1)) {
        if (v - 1 >= 0 && a[v - 1].sc == a[v].fr) ret.push_back(v - 1);
        if (a[v].sc == a[v + 1].fr) ret.push_back(v + 1);
    }
    else if (rem == 0 || rem == n) {
        if (a[v].sc == a[v + 1].fr) ret.push_back(v + 1);
    }
    else if (rem == n - 1 || rem == m - 1) {
        if (v - 1 >= 0 && a[v - 1].sc == a[v].fr) ret.push_back(v - 1);
    }

    if (!(rem == 0 || rem == n - 1)) {
        if (v - n >= 0 && a[v - n].sc == a[v].fr) ret.push_back(v - n);
        if (v - (n - 1) >= 0 && a[v - (n - 1)].fr == a[v].sc) ret.push_back(v - (n - 1));
        if (a[v + (n - 1)].sc == a[v].fr) ret.push_back(v + (n - 1));
        if (a[v + n].fr == a[v].sc) ret.push_back(v + n);
    }
    else if (rem == 0) {
        if (v - (n - 1) >= 0 && a[v - (n - 1)].fr == a[v].sc) ret.push_back(v - (n - 1));
        if (a[v + n].fr == a[v].sc) ret.push_back(v + n);
    }
    else if (rem == n - 1) {
        if (v - n >= 0 && a[v - n].sc == a[v].fr) ret.push_back(v - n);
        if (a[v + (n - 1)].sc == a[v].fr) ret.push_back(v + (n - 1));
    }

    return ret;
}

void bfs() {
    memset(dist, -1, sizeof(dist));
    queue<int> q;
    q.push(0);
    dist[0] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        
        en = max(en, v);
        
        vector<int> u = cal(v);
        for (auto& i : u) {
            if (dist[i] != -1) continue;
            
            dist[i] = dist[v] + 1;
            q.push(i);
        }
    }
}

void track(int v) {
    vector<int> u = cal(v);
    for (auto& i : u) {
        if (dist[i] == dist[v] - 1) {
            track(i);
            break;
        }
    }
    cout << v + 1 << ' ';
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    for (int i = 0; i < n * n - n / 2; i++) {
        cin >> a[i].fr >> a[i].sc;
    }

    /*if (n == 1) {
        cout << 1 << '\n' << 1;
        return 0;
    }*/

    m = 2 * n - 1;
    bfs();

    cout << dist[en] + 1 << '\n';
    track(en);

	return 0;
}