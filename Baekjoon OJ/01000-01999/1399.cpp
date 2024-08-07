// M = 10^x(x은 0 이상의 정수)일 때 dig(골드 넘버)는 언제나 1이다.
// dig(x)는 x가 9의 배수일 때 9, x가 9의 배수가 아닐 때 x % 9.

#include <bits/stdc++.h>
using namespace std;
#define ll long long

void findPattern() {
    const int MAX = 101010;
    vector<int> dp(MAX);
    for (int i = 1; i <= 9; i++) dp[i] = i;
    for (int i = 10; i < MAX; i++) {
        int score = 0;
        string s = to_string(i);
        for (auto& j : s) score += j - '0';
        dp[i] = dp[score];
    }
    for (int i = 1; i < MAX; i++) 
        cout << i << ' ' << dp[i] << '\n';

    for (int i = 1; i < MAX; i++) {
        assert(dp[i] == (i % 9 ? i % 9 : 9));
    }
}

ll solve(int st, ll mul, int cnt) {
    ll ret = 0;
    
    map<pair<int, int>, int> mp;
    
    int now = st, op = 1;
    vector<int> arr;
    for (int i = 0, op = 1; i < cnt; i++) {
        mp[{ now, op }] = i;

        ret += op * (now ? now : 9);
        arr.push_back(op * (now ? now : 9));
        
        now = now * mul % 9;
        op *= -1;
        
        if (mp.find({ now, op }) != mp.end()) {
            int l = mp[{ now, op }], r = i;
            cnt -= i + 1;

            int len = (r - l + 1);
            ll sum = 0;
            for (int j = l; j <= r; j++) sum += arr[j];

            ret += cnt / len * sum;
            cnt %= len;
            for (int j = l; cnt; j++, cnt--) ret += arr[j];

            break;
        }
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

    //findPattern();

    int tc; cin >> tc;
    while (tc--) {
        int k, m;
        cin >> k >> m;

        cout << solve(m % 9, m * m, k / 2) << ' ';
        cout << solve(1, m * m, (k + 1) / 2) << '\n';
    }   
}