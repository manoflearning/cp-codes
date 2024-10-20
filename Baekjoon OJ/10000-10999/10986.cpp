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

const int MAXN = 1e6 + 5;

int n, m, a[MAXN];
ll cnt[1005];

void input() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
}

ll f() {
    ll ret = 0, sum = 0;
    
    cnt[0]++;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        
        cnt[sum % m]++;
    }
    
    for (int i = 0; i < m; i++) {
        ret += cnt[i] * (cnt[i] - 1) / 2;
    }
        
    return ret;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	input();
	
	cout << f();
	
	return 0;
}
