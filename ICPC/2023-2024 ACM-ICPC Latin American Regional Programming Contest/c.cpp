#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pli pair<ll, int>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 404040;
const int MAXK = 404040;
const int SQ = 814;
const int INF = 1e9 + 7;

const int D = 2 * MAXN;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int MOD3 = 1e9 + 11;

int n, k;
int a[MAXN];


void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

ll cnt[MAXK], diff[MAXK];
ll dexp1[MAXK], dexp2[MAXK], dexp3[MAXK];
ll val1 = 0, val2 = 0, val3 = 0;

map<tuple<ll, ll, ll, int>, vector<int>> mp;

void rabin_karp() {
    dexp1[0] = dexp2[0] = dexp3[0] = 1;
    for (int i = 1; i < MAXK; i++) {
        dexp1[i] = D * dexp1[i - 1] % MOD1;
        dexp2[i] = D * dexp2[i - 1] % MOD2;
        dexp3[i] = D * dexp3[i - 1] % MOD3;
    }

    for (int i = 1; i <= k - 1; i++) {
        val1 = (val1 + dexp1[i] * diff[i]) % MOD1;
        val2 = (val2 + dexp2[i] * diff[i]) % MOD2;
        val3 = (val3 + dexp3[i] * diff[i]) % MOD3;
    }
}

void add(int idx) {
    val1 = (val1 + dexp1[idx] * diff[idx]) % MOD1;
    val2 = (val2 + dexp2[idx] * diff[idx]) % MOD2;
    val3 = (val3 + dexp3[idx] * diff[idx]) % MOD3;
}
void del(int idx) {
    val1 = (val1 - dexp1[idx] * diff[idx]) % MOD1;
    val1 = (val1 + MOD1) % MOD1;
    val2 = (val2 - dexp2[idx] * diff[idx]) % MOD2;
    val2 = (val2 + MOD2) % MOD2;
    val3 = (val3 - dexp3[idx] * diff[idx]) % MOD3;
    val3 = (val3 + MOD3) % MOD3;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (int i = 0; i < MAXK; i++) {
        diff[i] = MAXN;
    }

    rabin_karp();

    mp[{ val1, val2, val3, 0 }].push_back(0);
    for (int i = 1; i <= n; i++) {
        if (1 < a[i]) del(a[i] - 1);
        if (a[i] < k) del(a[i]);
        diff[a[i] - 1]++;
        diff[a[i]]--;
        if (1 < a[i]) add(a[i] - 1);
        if (a[i] < k) add(a[i]);

        mp[{ val1, val2, val3, i % k }].push_back(i);
    }

    int ans = 0;
    for (auto& it : mp) {
        auto arr = it.second;
        if (arr.empty()) continue;
        ans = max(ans, arr.back() - arr.front());
    }

    cout << ans;
}
