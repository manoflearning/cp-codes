#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vvi vector<vector<int>>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

const int MX = 99999;

int n, t, g;
int dist[MX + 5];

void init() {
    memset(dist, -1, sizeof(dist));
}

void input() {
    cin >> n >> t >> g;
}

int f(int x) {
    if (x == 0) return 0;
    for (int i = 5; i >= 0; i--) {
        if (2 * x / (int)pow(10, i)) {
            //cout << 2 * x - pow(10, i) << '\n';
            return 2 * x - pow(10, i);
        }
    }
}

int bfs() {
    queue<int> q;
    
    q.push(n);
    dist[n] = 0;
    
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        
        if (v == g) return dist[v];
        if (dist[v] == t) continue;
        
        int u = v + 1;
        if (u <= MX && dist[u] == -1) {
            q.push(u);
            dist[u] = dist[v] + 1;
        }
        
        u = f(v);
        if (2 * v <= MX && dist[u] == -1) {
            q.push(u);
            dist[u] = dist[v] + 1;
        }
    }
    
    return -1;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	init();
	
	input();
	
	int ans = bfs();
	
	if (ans == -1) cout << "ANG";
	else cout << ans;
}
