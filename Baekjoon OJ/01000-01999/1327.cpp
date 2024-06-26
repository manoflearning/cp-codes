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

int n, k, st, en;
map<int, int> mp;

void init() {
    for (int i = 0; i < n; i++) {
        en += i * (1 << 3 * i);
    }
}

void input() {
    cin >> n >> k;
    
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        //'*'가 '<<'보다 연산자 우선순위 높음
        st += (x - 1) * (1 << 3 * i);
    }
}

int f2(int x, int idx) {
    int ret = 0;
    if (x & (1 << 3 * idx)) ret |= (1 << 0);
    if (x & (1 << 3 * idx + 1)) ret |= (1 << 1);
    if (x & (1 << 3 * idx + 2)) ret |= (1 << 2);
    
    return ret;
}

int f(int v, int idx) {
    int a = v, b = 0;
    
    for (int i = idx; i < idx + k; i++) {
        a &= ~(f2(v, i) * (1 << 3 * i));
        b |= f2(v, i) * (1 << 3 * (2 * idx + k - i - 1));
    }
    
    return a | b;
}

int bfs() {
    queue<int> q;
    
    q.push(st);
    mp.insert({ st, 0 });
    
    while (!q.empty()) {
        int v = q.front(), d = mp.find(v)->second;
        q.pop();
        
        if (v == en) return d;
        
        for (int i = 0; i < n - k + 1; i++) {
            int u = f(v, i);
            if (mp.find(u) != mp.end()) continue;
            
            q.push(u);
            mp.insert({ u, d + 1 });
        }
    }
    return -1;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	input();
	
	init();
	
	cout << bfs();
	
	return 0;
}
