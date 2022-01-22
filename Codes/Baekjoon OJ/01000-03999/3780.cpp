//union find(path compression)
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
const int MOD = 1000;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

int n;
vi p, dist;

void init() {
    p.clear();
    dist.clear();
}

int find(int x) {
	if (p[x] < 0) return x;
	
	int pp = p[x];
	p[x] = find(p[x]);
	
	dist[x] += dist[pp];
	
	return p[x];
}

void merge(int a, int b) {
	p[a] = b;
	dist[a] += (int)fabs(a - b) % MOD;
}

void f() {
    cin >> n;
    p.resize(n + 1, -1);
    dist.resize(n + 1, 0);
    
    while (1) {
        char c; cin >> c;
        
        if (c == 'O') break;
        
        if (c == 'E') {
            int a; cin >> a;
            
            find(a);
            
            cout << dist[a] << '\n';
        }
        
        if (c == 'I') {
            int a, b;
            cin >> a >> b;
            
            merge(a, b);
        }
    }
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int tc; cin >> tc;
	
	while (tc--) {
	    init();
	    
	    f();
	}
	
	return 0;
}

//naive 2(union find)
/*#define _USE_MATH_DEFINES
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
const int MOD = 1000;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

int n;
vi p;

void init() {
    p.clear();
}

int find(int x) {
	if (p[x] < 0) return x;
	return find(p[x]);
}

void merge(int a, int b) {
	p[a] = b;
}

void f() {
    cin >> n;
    p.resize(n + 1, -1);
    
    while (1) {
        char c; cin >> c;
        
        if (c == 'O') break;
        
        if (c == 'E') {
            int a; cin >> a;
            
            int ans = 0;
            while (p[a] > 0) {
                ans += (int)fabs(p[a] - a) % MOD;
                a = p[a];
            }
            cout << ans << '\n';
        }
        
        if (c == 'I') {
            int a, b;
            cin >> a >> b;
            
            merge(a, b);
        }
    }
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int tc; cin >> tc;
	
	while (tc--) {
	    init();
	    
	    f();
	}
	
	return 0;
}*/

//naive
/*#define _USE_MATH_DEFINES
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

int n;
vi adj[20005];

void init() {
    for (auto& i : adj) i.clear();
}

void f() {
    cin >> n;

    while (1) {
        char c; cin >> c;
        
        if (c == 'O') break;
        
        if (c == 'E') {
            int a; cin >> a;
            
            int sum = 0;
            while (!adj[a].empty()) {
                sum += (int)fabs(a - adj[a][0]) % MOD;
                a = adj[a][0];
            }
            
            cout << sum << '\n';
        }
        
        if (c == 'I') {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
        }
    }
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int tc; cin >> tc;
	
	while (tc--) {
	    init();
	    
	    f();
	}
	
	return 0;
}*/
