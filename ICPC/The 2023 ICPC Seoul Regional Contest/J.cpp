#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MOD = 1e9 + 7;
const double EPS = 1e-4;

ll k;
string L, R;

const ll p[] = { 2, 3, 5, 7 };

const vector<int> d[10] = {
    { 100, 100, 100, 100 }, // 0
    { 0, 0, 0, 0 }, // 1
    { 1, 0, 0, 0 }, // 2
    { 0, 1, 0, 0 }, // 3
    { 2, 0, 0, 0 }, // 4
    { 0, 0, 1, 0 }, // 5
    { 1, 1, 0, 0 }, // 6
    { 0, 0, 0, 1 }, // 7
    { 3, 0, 0, 0 }, // 8
    { 0, 2, 0, 0 }, // 9
};

int cnt[4];
ll digit[5];

void div(int x) {
    while (k % p[x] == 0) { k /= p[x]; cnt[x]++; }
}

ll dp0[24][2][2][2];
ll f0(int idx, bool has_0, bool is_ub, bool all_0, const string& num) {
    auto& ret = dp0[idx][has_0][is_ub][all_0];
    if (ret != -1) return ret;
    
    // base case
    if (idx == sz(num)) {
        if (has_0) return ret = 1;
        else return ret = 0;
    }

    // inductive step
    ret = 0;
    if (is_ub) {
        for (char c = '0'; c <= num[idx]; c++) {
            bool n_has_0 = has_0 || (c == '0' && !all_0);
            bool n_is_ub = (c == num[idx]);
            bool n_all_0 = all_0 && (c == '0');
            ret = (ret + f0(idx + 1, n_has_0, n_is_ub, n_all_0, num)) % MOD;
        }
    } else {
        for (char c = '0'; c <= '9'; c++) {
            bool n_has_0 = has_0 || (c == '0' && !all_0);
            bool n_all_0 = all_0 && (c == '0');
            ret = (ret + f0(idx + 1, n_has_0, 0, n_all_0, num)) % MOD;
        }
    }
    return ret;
}

ll dp[24][1102941 + 10][2];
ll f(int idx, int state, bool is_ub, const string& num) {
    auto& ret = dp[idx][state][is_ub];
    if (ret != -1) return ret;

    vector<int> arr(4);
    for (int i = 0; i < 4; i++)
        arr[i] = state % digit[i + 1] / digit[i];
    
    // base case
    if (idx == sz(num)) {
        bool is_valid = 1;
        for (int i = 0; i < 4; i++) {
            is_valid &= (cnt[i] <= arr[i]);
        }
        return ret = (is_valid ? 1 : 0);
    }

    // inductive step
    ret = 0;
    if (is_ub) {
        for (int i = 1; i <= num[idx] - '0'; i++) {            
            int n_state = 0;
            for (int j = 0; j < 4; j++)
                n_state += digit[j] * (arr[j] + d[i][j]);

            bool n_is_ub = (i == num[idx] - '0');

            ret = (ret + f(idx + 1, n_state, n_is_ub, num)) % MOD;
        }
    } else {
        for (int i = 1; i <= 9; i++) {
            int n_state = 0;
            for (int j = 0; j < 4; j++)
                n_state += digit[j] * (arr[j] + d[i][j]);

            ret = (ret + f(idx + 1, n_state, 0, num)) % MOD;
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

    digit[0] = 1;
    digit[1] = digit[0] * (20 * 3 + 1);
    digit[2] = digit[1] * (20 * 2 + 1);
    digit[3] = digit[2] * (20 + 1);
    digit[4] = digit[3] * (20 + 1);
    
    cin >> k >> L >> R;
    
    div(0); div(1);
    div(2); div(3);

    ll ans = 0;

    // case 1: 0 exists
    {
        memset(dp0, -1, sizeof(dp0));
        ans += f0(0, 0, 1, 1, R);
        
        memset(dp0, -1, sizeof(dp0));
        ans -= f0(0, 0, 1, 1, L);
    }

    // case 2: 0 does not exist
    if (k == 1) {
        memset(dp, -1, sizeof(dp));
        ans += f(0, 0, 1, R);
        for (int i = 1; i < sz(R); i++)
            ans += f(i, 0, 0, R);

        memset(dp, -1, sizeof(dp));
        ans -= f(0, 0, 1, L);
        for (int i = 1; i < sz(L); i++)
            ans -= f(i, 0, 0, L);
    }

    // case 3: L
    {
        bool has_0 = 0;
        vector<int> arr(4);
        for (auto& c : L) {
            if (c == '0') has_0 = 1;
            else 
                for (int i = 0; i < 4; i++)
                    arr[i] += d[c - '0'][i];
        }
        bool is_valid = 1;
        for (int i = 0; i < 4; i++) {
            is_valid &= (cnt[i] <= arr[i]);
        }
        is_valid &= (k == 1);
        if (is_valid || has_0) ans++;
    }
    
    ans = (ans % MOD + MOD) % MOD;

    cout << ans;
}
