#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>

const int MAXN = 606060;
const int MOD1 = 1e9 + 9;
const int MOD2 = 1e9 + 13;

const int D = 1e5 + 7;

ll power2[66];
ll dexp1[MAXN], dexp2[MAXN];

int H, N;
ll K, P[MAXN];

ll Hash1[MAXN], Hash2[MAXN];

void rabinKarp() {
  Hash1[0] = Hash2[0] = P[0];
  for (int i = 1; i < 3 * N; i++) {
    Hash1[i] = (D * Hash1[i - 1] + P[i]) % MOD1;
    Hash2[i] = (D * Hash2[i - 1] + P[i]) % MOD2;
  }
}
ll get_key(int s, int e) {
    ll ret1 = 0, ret2 = 0, ret3 = 0;
    ret1 += Hash1[e];
    ret2 += Hash2[e];
    if (s > 0) {
        ret1 += MOD1 - Hash1[s - 1] * dexp1[e - s + 1] % MOD1;
        ret2 += MOD2 - Hash2[s - 1] * dexp2[e - s + 1] % MOD2;
    }
    ret1 %= MOD1, ret2 %= MOD2;
    return ret2 * MOD2 + ret1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    power2[0] = 1;
    for (int i = 1; i <= 62; i++) power2[i] = 2 * power2[i - 1];

    dexp1[0] = dexp2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        dexp1[i] = D * dexp1[i - 1] % MOD1;
        dexp2[i] = D * dexp2[i - 1] % MOD2;
    }

    cin >> H >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> P[i];
        P[i + N] = P[i + 2 * N] = P[i];
    }

    rabinKarp();

    for (int d = 1; d <= H; d++) {
        unordered_map<ll, ll> cnt;
        ll l = power2[H - d];
        for (int i = 0, j = 0; j < min<ll>(power2[d - 1], N); i = (i + l) % N, j++) {
            ll s = i, e = i + l - 1;
            if (e >= 3 * N) e = 2 * N + e % N;
            auto key = get_key(s, e);
            cnt[key] += (power2[d - 1] - (j + 1)) / N + 1;
            if (cnt[key] >= K) { cout << d; exit(0); } 
        }
    }

    cout << -1;
}
