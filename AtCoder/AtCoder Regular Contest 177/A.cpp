// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int N, A[6], X[15];
int W[6] = { 1, 5, 10, 50, 100, 500 };
int mul[6] = { 0, 5, 2, 5, 2, 5 };
int B[6];
bool ans = true;

void input() {
    for (int i = 0; i < 6; i++) cin >> A[i];
    cin >> N;
    for (int i = 0; i < N; i++) cin >> X[i];
}

void solve() {
    for (int i = 0; i < N; i++) {
        int x = X[i];
        for (int j = 5; j >= 0; j--) {
            B[j] += x / W[j];
            x %= W[j];
        }
    }

    for (int i = 5; i >= 0; i--) {
        B[i] -= min(B[i], A[i]);
        if (B[i] > 0) {
            if (i == 0) ans = false;
            else B[i - 1] += mul[i] * B[i];
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

    solve();

    cout << (ans ? "Yes" : "No");
}