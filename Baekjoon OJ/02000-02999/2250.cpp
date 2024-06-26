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

const int MAXN = 1e4 + 5;

int n, par[MAXN], chd[MAXN][2], cnt, num[MAXN], rt;
vi lev[MAXN];

void init() {
    memset(par, -1, sizeof(par));
}

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        chd[a][0] = b;
        chd[a][1] = c;
        if (b != -1) par[b] = a;
        if (c != -1) par[c] = a;
    }
}

int findRt() {
    for (int i = 1; i <= n; i++)
        if (par[i] == -1) return i;
}

//inorder traversal
void dfs(int v, int l) {
    lev[l].push_back(v);
    
    if (chd[v][0] != -1)
        dfs(chd[v][0], l + 1);
    
    num[v] = cnt++;
    
    if (chd[v][1] != -1)
        dfs(chd[v][1], l + 1);
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	init();
	
	input();
	
	rt = findRt();
	
	dfs(rt, 1);
	
	int ans = 0, ansLv;
	for (int i = 1; lev[i].size(); i++) {
	    int mn = INF, mx = -INF;
	    for (int j : lev[i]) {
	        mn = min(mn, num[j]);
	        mx = max(mx, num[j]);
	    }
	    if (ans < mx - mn + 1) {
	        ans = mx - mn + 1;
	        ansLv = i;
	    }
	}
	
	cout << ansLv << ' ' << ans;
	
	return 0;
}
