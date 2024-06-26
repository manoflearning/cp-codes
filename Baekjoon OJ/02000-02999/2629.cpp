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

int n, m;
int a[35], b[8], dp[35][120001];

void init() {
    for (int i = 0; i < 35; i++)
        memset(dp[i], -1, sizeof(dp[i]));
}

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; i++) cin >> b[i];
}

//구간 [idx, n)에서 무게 sz를 확인할 수 있는가?
int f(int idx, int sz) {
    int& ret = dp[idx][sz];
    
    if (ret != -1) return ret;
    if (sz == 40000) return ret = 1;
    if (idx == n) return ret = 0;
    
    ret = 0;
    ret |= f(idx + 1, sz);
    ret |= f(idx + 1, sz + a[idx]);
    ret |= f(idx + 1, sz - a[idx]);
    
    return ret;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	init();
	
	input();
    
	for (int i = 0; i < m; i++) {
	    if (f(0, b[i] + 40000)) cout << "Y ";
	    else cout << "N ";
	}
	
	return 0;
}
