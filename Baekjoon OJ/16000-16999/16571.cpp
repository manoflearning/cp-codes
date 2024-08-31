#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> a(3, vector<int>(3));
int dp[59049], p3[11];

int to_bit(const vector<vector<int>>& arr) {
    int ret = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ret += p3[i * 3 + j] * arr[i][j];
        }
    }
    return ret;
}

vector<vector<int>> to_arr(int bit) {
    vector<vector<int>> ret(3, vector<int>(3));
    for (int i = 2; i >= 0; i--) {
        for (int j = 2; j >= 0; j--) {
            int k = (i * 3 + j), cnt = 0;
            while (bit >= p3[k]) {
                cnt++;
                bit -= p3[k];
            }
            ret[i][j] = cnt;
        }
    }
    return ret;
}

bool row_check(const vector<vector<int>>& arr) {
    if (arr[0][0] > 0 && arr[0][0] == arr[0][1] && arr[0][1] == arr[0][2]) return 1;
    if (arr[1][0] > 0 && arr[1][0] == arr[1][1] && arr[1][1] == arr[1][2]) return 1;
    if (arr[2][0] > 0 && arr[2][0] == arr[2][1] && arr[2][1] == arr[2][2]) return 1;
    return 0;
}
bool col_check(const vector<vector<int>>& arr) {
    if (arr[0][0] > 0 && arr[0][0] == arr[1][0] && arr[1][0] == arr[2][0]) return 1;
    if (arr[0][1] > 0 && arr[0][1] == arr[1][1] && arr[1][1] == arr[2][1]) return 1;
    if (arr[0][2] > 0 && arr[0][2] == arr[1][2] && arr[1][2] == arr[2][2]) return 1;
    return 0;
}
bool dia_check(const vector<vector<int>>& arr) {
    if (arr[0][0] > 0 && arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2]) return 1;
    if (arr[2][0] > 0 && arr[2][0] == arr[1][1] && arr[1][1] == arr[0][2]) return 1;
    return 0;
}

int f(int bit) {
    int& ret = dp[bit];
    if (ret != -1) return ret;

    vector<vector<int>> arr = to_arr(bit);
    if (row_check(arr)) return ret = 2;
    if (col_check(arr)) return ret = 2;
    if (dia_check(arr)) return ret = 2;
    
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] == 1) cnt1++;
            if (arr[i][j] == 2) cnt2++;
        }
    }

    int now = -1;
    if (cnt1 == cnt2 + 1) now = 2;
    else now = 1;

    if (cnt1 + cnt2 == 9) return ret = 1;

    ret = 2;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] > 0) continue;
            arr[i][j] = now;
            
            int res = f(to_bit(arr));
            if (res == 2) return ret = 0;
            else if (res == 1) ret = 1;
            else if (res == 0) {}

            arr[i][j] = 0;
        }
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    p3[0] = 1;
    for (int i = 1; i <= 10; i++)
        p3[i] = 3 * p3[i - 1];
    memset(dp, -1, sizeof(dp));

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> a[i][j];
        }
    }
    
    int res = f(to_bit(a));
    cout << (res == 0 ? "W" : (res == 1 ? "D" : "L"));
}
