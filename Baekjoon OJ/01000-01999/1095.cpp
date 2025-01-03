//#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX = 1e5;
bool isPrime[MAX + 1];
vector<int> prime(1, 2);
void getPrime() {
	fill(isPrime + 2, isPrime + MAX + 1, 1);
	for (ll i = 4; i <= MAX; i += 2)
		isPrime[i] = 0;
	for (ll i = 3; i <= MAX; i += 2) {
		if (!isPrime[i]) continue;
		prime.push_back(i);
		for (ll j = i * i; j <= MAX; j += i * 2)
			isPrime[j] = 0;
	}
}

ll S, F, M;
vector<ll> p;
vector<pair<ll, ll>> arr;

int f(ll x, ll y) {
    int ret = 0;
    ll z = y;
    while (x >= z) {
        ret += x / z;
        z *= y;
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

    getPrime();

    cin >> S >> F >> M;

    for (auto& i : prime) {
        if (M < i) break;
        int res = f(S + F, i) - f(S, i) - f(F, i);
        arr.push_back({ i, res });
    }
    
    vector<int> dp(M + 1);
    dp[1] = 1;
    for (int i = 0; i < arr.size(); i++) {
        vector<int> tmp(M + 1);
        ll x = arr[i].first;
        for (int j = 0; j < arr[i].second; j++) {
            for (ll k = 1; k <= M; k++) {
                if (M < k * x || !dp[k]) continue;
                tmp[k * x] = 1;
            }
            x *= arr[i].first;
        }
        for (int k = 1; k <= M; k++)
            if (tmp[k]) dp[k] = 1;
    }

    int ans = 1;
    for (int i = 1; i <= M; i++)
        if (dp[i]) ans = i;

    cout << ans;
}