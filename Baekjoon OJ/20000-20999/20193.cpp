// 관찰 1
// 변의 길이를 최소로 하는 화려한 정사각형에는, 2개 이상의 변 위에 점이 놓여 있다.

// 관찰 2
// 변의 길이를 최소로 하는 화려한 정사각형 중 적어도 하나 이상에는, 3개 이상의 변 위에 점이 놓여 있다.
// 2개의 변 위에만 점이 놓여 있는 화려한 정사각형도 존재할 수 있지만, 
// 이 경우 화려한 정사각형을 적당히 평행이동하여 3개 이상의 변 위에 점이 놓여 있도록 만들 수 있다.



// subtask 2
/*#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;

int n, k;
unordered_set<int> s[55];
int dp[55][2525][2525];

int f(int co, int x, int y) {
    int& ret = dp[co][x][y];
    if (ret != -1) return ret;
    if (s[co].count(x * 2525 + y)) return ret = 0;

    ret = INF;
    if (x < 2500) ret = min(ret, f(co, x + 1, y) + 1);
    if (y < 2500) ret = min(ret, f(co, x, y + 1) + 1);
    if (x < 2500 && y < 2500) ret = min(ret, f(co, x + 1, y + 1) + 1);

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // initialize
    for (int i = 0; i < 55; i++) {
        for (int j = 0; j < 2525; j++) {
            for (int k = 0; k < 2525; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
    
    // input
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int x, y, co;
        cin >> x >> y >> co;
        s[co].insert(x * 2525 + y);
    }

    // solve
    int ans = INF;
    for (int sx = 2500; sx >= 1; sx--) {
        for (int sy = 2500; sy >= 1; sy--) {
            int res = 0;
            for (int co = 1; co <= k; co++) {
                res = max(res, f(co, sx, sy));
            }
            ans = min(ans, res);
        }
    }

    cout << ans;
}*/

// subtask 1
// 모든 정사각형에 대해 완전탐색
/*#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Point {
    ll x, y, co;
};

int n, k;
vector<Point> a;

ll cntColor(ll sx, ll sy, ll ex, ll ey) {
    int ret = 0;
    vector<int> vi(k + 1);
    for (auto& p : a) {
        if (p.x < sx || ex < p.x) continue;
        if (p.y < sy || ey < p.y) continue;
        if (!vi[p.co]) ret++, vi[p.co] = 1;
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    a.resize(n);
    for (auto& i : a)
        cin >> i.x >> i.y >> i.co;

    for (int len = 0; len <= 50; len++) {
        for (int sx = 1; sx + len <= 50; sx++) {
            for (int sy = 1; sy + len <= 50; sy++) {
                int ex = sx + len, ey = sy + len;
                if (cntColor(sx, sy, ex, ey) == k) {
                    cout << len;
                    return 0;
                }
            }
        }
    }
}*/