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
ll k, dp[15][225][225];

void init() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 225; j++) {
            for (int k = 0; k < 225; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
}

void input() {
    cin >> n >> m >> k;
}

ll f(int len, int prv, ll sum) {
    ll& ret = dp[len][prv][sum];
    if (ret != -1) return ret;
    if (len == 0) return ret = (sum == m);
    
    ret = 0;
    for (int i = prv; i <= m - sum; i++) {
        ret += f(len - 1, i, sum + i);
    }
    return ret;
}

void f2(int len, int prv, ll sum, int cnt) {
    if (len == 0) return;
    
    for (int i = prv; i <= m; i++) {
        if (cnt <= f(len - 1, i, sum + i)) {
            cout << i << ' ';
            f2(len - 1, i, sum + i, cnt);
            break;
        }
        
        cnt -= f(len - 1, i, sum + i);
    }
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	init();
	
	input();
	
	f2(n, 1, 0, k);
	
	/*for (int i = 1; i <= 6; i++) {
	    f2(n, 1, 0, i);
	    cout << '\n';
	}*/
	
	return 0;
}
