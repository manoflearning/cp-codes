#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vl vector<ll>
#define vvl vector<vector<ll>>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

int n, m;
vi p, d;

void init() {
    p.clear();
    d.clear();
}

void input() {
    cin >> n >> m;
}

int find(int x) {
    if (p[x] < 0) return x;
    int pp = p[x];
    p[x] = find(p[x]);
    d[x] += d[pp];
    return p[x];
}

int dist(int x) {
    find(x);
    return d[x];
}

void merge(int a, int b, int w) {
    int A = find(a), B = find(b);
    if (A == B) return;
    p[A] = B;
    d[A] = (d[b] + w) - d[a];
}

void f() {
    for (int i = 0; i < m; i++) {
	    char c; cin >> c;
	    if (c == '!') {
	        int a, b, w;
	        cin >> a >> b >> w;
	        merge(a, b, w);
	    }
	    if (c == '?') {
	        int a, b;
	        cin >> a >> b;
	        
	        if (find(a) == find(b)) {
	            cout << dist(a) - dist(b) << '\n';
	        }
	        else {
	            cout << "UNKNOWN\n";
	        }
	    }
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	while (1) {
	    init();
	    
	    input();
	    
	    if (n == 0 && m == 0) break;
	    
	    p.resize(n + 1, -1);
        d.resize(n + 1);
	    
	    f();
	}
	
	return 0;
}
