#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int N, K;
string s[15];
int rem[15], p10[1010];

ll dp[1 << 15][101];

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> s[i];
    cin >> K;
}

void preprocessing() {
    p10[0] = 1 % K;
    for (int i = 1; i < 1010; i++) {
        p10[i] = 10 * p10[i - 1] % K;
    }
}

void getRemainder() {
    for (int i = 0; i < N; i++) {
        int now = 0;
        for (auto& c : s[i]) {
            now = 10 * now + c - '0';
            now %= K;
        }
        rem[i] = now;
    }
}

void bottomup() {
    // base case
    dp[0][0] = 1;

    // inductive step
    for (int bit = 1; bit < (1 << N); bit++) {
        int len = 0;
        for (int b = 0; b < N; b++) {
            if (bit & (1 << b)) len += sz(s[b]);
        }

        for (int b = 0; b < N; b++) {
            if ((bit & (1 << b)) == 0) continue;
            for (int prv = 0; prv < K; prv++) {
                int now = (prv + rem[b] * p10[len - sz(s[b])] % K) % K;
                dp[bit][now] += dp[bit - (1 << b)][prv];
            }
        }
    }
}

void output() {
    ll p = dp[(1 << N) - 1][0];
    ll q = 1;
    for (int i = 1; i <= N; i++) q *= i;

    for (int i = 2; i <= N; i++) {
        while (p % i == 0 && q % i == 0) {
            p /= i, q /= i;
        }
    }

    cout << p << '/' << q;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    preprocessing();

    getRemainder();

    bottomup();

    output();
}