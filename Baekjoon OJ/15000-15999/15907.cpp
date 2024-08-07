#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
vector<int> a;

int MAX = 2e6;
vector<bool> isPrime;
vector<int> prime(1, 2);
void getPrime() {
    MAX = 2e6 / (n >= 3 ? n / 3 : 1);
    isPrime.resize(MAX + 1, true);
    isPrime[0] = isPrime[1] = 0;
    for (ll i = 4; i <= MAX; i += 2)
        isPrime[i] = 0;
    for (ll i = 3; i <= MAX; i += 2) {
        if (!isPrime[i]) continue;
        prime.push_back(i);
        for (ll j = i * i; j <= MAX; j += i * 2)
            isPrime[j] = 0;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    getPrime();

    int ans = 0;
    for (auto& i : prime) {
        unordered_map<int, int> mp;
        for (auto& j : a)
            ans = max(ans, ++mp[j % i]);
    }

    cout << ans;
}