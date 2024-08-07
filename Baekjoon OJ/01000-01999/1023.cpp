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

int n;
ll k, dp[55][105], p2[105];

void init() {
    for (int i = 0; i < 55; i++) {
        for (int j = 0; j < 105; j++) {
            dp[i][j] = -1;
        }
    }
    
    p2[0] = 1;
    for (int i = 1; i < 55; i++)
        p2[i] = (p2[i - 1] << 1);
}

void input() {
    cin >> n >> k;
}

//f(len, op)는 남은 길이가 len이고 아직 열려 있는 괄호가 op개인 문자열에서
//완성될 수 있는 괄호 ㄴㄴ 문자열의 개수
ll f(int len, int op) {
    ll& ret = dp[len][op + 50];
    if (ret != -1) return ret;
    if (len == 0) return ret = (op != 0);
    
    if (op < 0) return ret = p2[len];
    
    return ret = f(len - 1, op + 1) + f(len - 1, op - 1);
}

void f2(int len, int op, ll sum) {
    if (len == 0) return;
    
    if (op < 0) {
        if (sum <= p2[len - 1]) {
            cout << '(';
            f2(len - 1, op, sum);
        }
        else {
            cout << ')';
            f2(len - 1, op, sum - p2[len - 1]);
        }
    }
    else {
        if (sum <= f(len - 1, op + 1)) {
            cout << '(';
            f2(len - 1, op + 1, sum);
        }
        else {
            cout << ')';
            f2(len - 1, op - 1, sum - f(len - 1, op + 1));
        }
    }
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	init();
	
	input();
	
	k++;
	if (k <= f(n, 0)) f2(n, 0, k);
	else cout << -1;
	
	return 0;
}
