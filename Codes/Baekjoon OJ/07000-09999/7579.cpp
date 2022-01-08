#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

const int MAXN = 100;

int n, m;
ll a[MAXN + 5], b[MAXN + 5], dp[MAXN + 5][10005];
//dp[i][j]는 구간 [0, i]에서 i번째 메모리를 포함하고,
//총 j 이하의 비용을 소모해서 얻을 수 있는 메모리의 최댓값

void init() {
    for (int i = 0; i < MAXN; i++) {
        fill(dp[i], dp[i] + 10001, -1);
    }
}

void input() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
}

ll f(int idx, int c) {
    ll& ret = dp[idx][c];
    
    if (ret != -1) return ret;
    if (b[idx] > c) return ret = 0;
    
    ret = a[idx];
    
    for (int i = 0; i < idx; i++) {
        ret = max(ret, a[idx] + f(i, c - b[idx]));
    }
    
    return ret;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	init();
	
	input();
	
	int ans = INF;
	for (int i = 0; i <= 10000; i++) {
	    for (int j = 0; j < n; j++) {
	        if (f(j, i) >= m) {
	            ans = i;
	            i = 10001, j = n;
	            break;
	        }
	    }
	}
	
	cout << ans;
	
	return 0;
}
