#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 101010;
const int MAXV = 1010101;
const int MOD = 1e9 + 7;

// bool isPrime[MAXV + 1];
// vector<int> prime(1, 2);
// void getPrime() {
// 	fill(isPrime + 2, isPrime + MAXV + 1, 1);
// 	for (ll i = 4; i <= MAXV; i += 2)
// 		isPrime[i] = 0;
// 	for (ll i = 3; i <= MAXV; i += 2) {
// 		if (!isPrime[i]) continue;
// 		prime.push_back(i);
// 		for (ll j = i * i; j <= MAXV; j += i * 2)
// 			isPrime[j] = 0;
// 	}
// }

ll p2[MAXN];

int n, v[MAXN], rv[MAXV];
ll cnt[MAXV];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        rv[v[i]]++;
    }
}

vector<int> p;
int ans = n;
void solve(int idx, int x, int bit) {
    if (idx == sz(p)) {
        if (bit) ans -= cnt[x];
        else ans += cnt[x];
        return;
    }
    solve(idx + 1, x, bit);
    solve(idx + 1, x * p[idx], !bit);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    p2[0] = 1;
    for (int i = 1; i < MAXN; i++)
        p2[i] = 2 * p2[i - 1] % MOD;
    
    input();

    for (int i = 2; i < MAXV; i++) {
        for (int j = i; j < MAXV; j += i) {
            cnt[i] += rv[j];
        }
    }

    int q; cin >> q;
    while (q--) {
        int x; cin >> x;

        p.clear();
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) p.push_back(i);
            while (x % i == 0) x /= i;
        }
        if (x > 1) p.push_back(x);

        ans = n;
        solve(0, 1, 0);
        cout << p2[ans] << '\n';
    }
}
