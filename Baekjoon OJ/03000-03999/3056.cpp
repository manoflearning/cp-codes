#include <bits/stdc++.h>
using namespace std;
#define ll long long

int N;
ll a[22][22];
double dp[1 << 20];
vector<int> bits[22];

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> a[i][j];
        }
    }
}

void preprocessing() {
    bits[0].push_back(0);
    for (int bit = 1; bit < (1 << N); bit++) {
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            if (bit & (1 << i)) cnt++;
        }
        bits[cnt].push_back(bit);
    }
}

void bottomup() {
    dp[0] = 100;
    
    for (int i = 0; i < N; i++) {
        for (auto& bit : bits[i]) {
            for (int j = 0; j < N; j++) {
                if (bit & (1 << j)) continue;
                int nbit = bit | (1 << j);
                dp[nbit] = max(dp[nbit], dp[bit] * a[i][j] / 100);
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    preprocessing();

    bottomup();

    cout << fixed;
    cout.precision(8);
    cout << dp[(1 << N) - 1];
}