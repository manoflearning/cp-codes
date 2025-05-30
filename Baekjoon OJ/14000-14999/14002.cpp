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

int n, a[1005];
int dp[1005];

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
}

//a[idx]를 마지막 수로 포함하는 가장 긴 증가하는 부분 수열
int f(int idx) {
    int& ret = dp[idx];
    if (ret != -1) return ret;
    
    ret = 1;
    for (int i = 0; i < idx; i++) {
        if (a[i] < a[idx]) ret = max(ret, f(i) + 1);
    }
    
    return ret;
}

void rf(int idx) {
    for (int i = 0; i < idx; i++) {
        if (a[i] < a[idx] && (f(i) + 1 == f(idx))) {
            rf(i);
            break;
        }
    }
    
    cout << a[idx] << ' ';
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	memset(dp, -1, sizeof(dp));
	
	input();
	
	int ans = 0, b = 0;
	for (int i = 0; i < n; i++) {
	    if (f(i) > ans) {
	        ans = f(i);
	        b = i;
	    }
	}
	
	cout << ans << '\n';
	rf(b);
	
	return 0;
}
