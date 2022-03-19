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

int n, ans;
vvi a(20, vi(20));

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            ans = max(ans, a[i][j]);
        }
    }
}

/*int pruning(int l) {
    vi cnt(21);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!a[i][j]) continue;
            
            for (int k = 1; k <= 20; k++) {
                if ((1 << k) == a[i][j]) {
                    cnt[k]++;
                    break;
                }
            }
        }
    }
    
    for (int i = 1; i <= 20; i++) {
        if (!cnt[i]) continue;
        
        //if ((1 << (mx - i + 1)) <= min(1 << l, cnt[i])) return 0;
        
        int mx = 0;
        for (int j = 1; j <= 9; j++) {
            if ((1 << j) & cnt[i]) mx = max(mx, j);
        }
        
        if (ans < ((1 << i) << min(l, mx))) return 0;
    }
    
    return 1;
}*/

//1 = 왼, 2 = 오, 3 = 상, 4 = 하
void f3(const vvi& b, int num) {
    if (num == 1) {
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                a[y][x] = b[y][x];
            }
        }
    }
    else if (num == 2) {
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                a[y][n - x - 1] = b[y][x];
            }
        }
    }
    else if (num == 3) {
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                a[x][y] = b[y][x];
            }
        }
    }
    else if (num == 4) {
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                a[x][n - y - 1] = b[y][x];
            }
        }
    }
}

int f2(int l) {
    int ret = 0, mx = 0;
    
    //블록 합치기
    for (int y = 0; y < n; y++) {
        int prv = 0, idx;
        for (int x = 0; x < n; x++) {
            mx = max(mx, a[y][x]);
            if (a[y][x] && !prv) {
                prv = a[y][x], idx = x;
            }
            else if (a[y][x] && prv) {
                if (prv == a[y][x]) {
                    a[y][idx] <<= 1;
                    a[y][x] = prv = 0;
                    
                    ret = 1;
                    ans = max(ans, a[y][idx]);
                    //assert(ans <= (1024 << 10));
                }
                if (prv != a[y][x]) {
                    prv = a[y][x], idx = x;
                }
            }
        }
    }
    
    if ((mx << l) <= ans) return 0;
    
    //블록 이동시키기
    for (int y = 0; y < n; y++) {
        vi c;
        for (int x = 0; x < n; x++) {
            if (x < n - 1 && !a[y][x] && a[y][x + 1]) ret = 1;
            if (a[y][x]) {
                c.push_back(a[y][x]);
                a[y][x] = 0;
            }
        }
        for (int x = 0; x < (int)c.size(); x++) {
            a[y][x] = c[x];
        }
    }
    
    return ret;
}

void f(int cnt) {
    if (cnt == 11/* || pruning(10 - cnt + 1)*/) return;
    
    vvi b = a;
    for (int i = 1; i <= 4; i++) {
        f3(b, i);
        if (f2(10 - cnt)) f(cnt + 1);
    }
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
    
	input();

	f(1);

	cout << ans;
	
	return 0;
}
