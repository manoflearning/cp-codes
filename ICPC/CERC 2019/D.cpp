#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

const string s[] = { "top", "bottom", "left", "right", "pass" };

int R, C, K;
int mny = INF, mxy = -INF, mnx = INF, mxx = -INF;
int t_cnt, b_cnt, l_cnt, r_cnt;

void input() {
    cin >> R >> C >> K;
    for (int i = 0; i < K; i++) {
        int y, x;
        cin >> y >> x;
        mny = min(mny, y);
        mxy = max(mxy, y);
        mnx = min(mnx, x);
        mxx = max(mxx, x);
    }
}

vector<int> arr;

void get() {
    string t; int val;
    cin >> t >> val;
    if (t == s[0]) arr[0] -= val;
    if (t == s[1]) arr[1] -= val;
    if (t == s[2]) arr[2] -= val;
    if (t == s[3]) arr[3] -= val;
}

void print(int idx, int val = 0) {
    if (idx != 4) cout << s[idx] << ' ' << val << endl;
    else cout << s[idx] << endl;
    arr[idx] -= val;
}

int num_rows() {
    int cnt = 0;
    cnt += (1 <= arr[0]);
    cnt += (1 <= arr[1]);
    cnt += (1 <= arr[2]);
    cnt += (1 <= arr[3]);
    return cnt;
}
int num_rows_bg_1() {
    int cnt = 0;
    cnt += (2 <= arr[0]);
    cnt += (2 <= arr[1]);
    cnt += (2 <= arr[2]);
    cnt += (2 <= arr[3]);
    return cnt;
}

void solve() {
    arr.push_back(t_cnt);
    arr.push_back(b_cnt);
    arr.push_back(l_cnt);
    arr.push_back(r_cnt);
    arr.push_back(0);

    // initial choice
    if (num_rows() == 0) print(4);
    else if (num_rows() == 1) {
        if (num_rows_bg_1() == 0) print(4);
        else {
            int res = 0;
            for (int i = 0; i < 4; i++) {
                if (arr[i] > 1) print(i, arr[i] - 1);
            }
        }
    }
    else if (num_rows() == 2) {
        if (num_rows_bg_1() == 0) print(4);
        else if (num_rows_bg_1() == 1) {
            int res = 0;
            for (int i = 0; i < 4; i++) {
                if (arr[i] > 1) print(i, arr[i] - 1);
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    input();

    t_cnt = mny - 1;
    b_cnt = R - mxy;
    l_cnt = mnx - 1;
    r_cnt = C - mxx;

    
}