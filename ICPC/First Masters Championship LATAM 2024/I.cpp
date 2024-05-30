#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAX = 1010101;
const int MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;

int n;
string s[1010], t;
ll h1[1010], h2[1010];
ll th1[1010], th2[1010];

ll d = 26, dexp1[MAX], dexp2[MAX];

int dp[1010];

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> s[i];
    cin >> t;
}

void rabin_karp(int j) {
    vector<int> a(sz(s[j]));
    for (int i = 0; i < sz(s[i]); i++) a[i] = s[j][i] - 'a';

    int len = sz(s[j]);
    ll p1 = 0, p2 = 0;
    for (int i = 0; i < len; i++) {
        p1 = (d * p1 + a[i]) % MOD1;
        p2 = (d * p2 + a[i]) % MOD2;
    }
    h1[j] = p1, h2[j] = p2;
}

void rabin_karp_t() {
    vector<int> a(sz(t));
    for (int i = 0; i < sz(t); i++) a[i] = t[i] - 'a';

    int len = sz(t);
    ll p1 = 0, p2 = 0;
    for (int i = 0; i < len; i++) {
        p1 = (d * p1 + a[i]) % MOD1;
        p2 = (d * p2 + a[i]) % MOD2;
        th1[i] = p1, th2[i] = p2;
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

    dexp1[0] = dexp2[0] = 1;
    for (int i = 1; i < MAX; i++) {
        dexp1[i] = d * dexp1[i - 1] % MOD1;
        dexp2[i] = d * dexp2[i - 1] % MOD2;
    }

    for (int i = 0; i < n; i++) rabin_karp(i);
    rabin_karp_t();


}