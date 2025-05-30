#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX = 1e6;

bool isPrime[MAX + 1];
vector<int> prime(1, 2);

void getPrime() {
	fill(isPrime + 2, isPrime + MAX + 1, 1);
	for (ll i = 4; i <= MAX; i += 2)
		isPrime[i] = 0;
	for (ll i = 3; i <= MAX; i++) {
		if (isPrime[i]) prime.push_back(i);
		for (ll j = i * i; j <= MAX; j += i * 2)
			isPrime[j] = 0;
	}
}

bool isPow2[MAX + 1];
ll psum1[MAX + 1], psum2[MAX + 1];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    getPrime();

    for (ll i = 1; i * i <= MAX; i++) {
        isPow2[i * i] = 1;
    }

    for (ll i = 1; i <= MAX; i++) {
        psum1[i] = psum1[i - 1];
        psum2[i] = psum2[i - 1];

        if (!isPrime[i]) continue;

        psum1[i]++;

        for (ll x = 1; x * x <= i; x++) {
            if (isPow2[i - x * x]) {
                psum2[i]++; break;
            }
        }
    }

	while (1) {
        int lb, ub;
        cin >> lb >> ub;

        if (lb == -1 && ub == -1) break;

        cout << lb << ' ' << ub << ' ';
        if (lb < 1) lb = 1;
        if (ub < 1) ub = 1;
        cout << psum1[ub] - psum1[lb - 1] << ' ' << psum2[ub] - psum2[lb - 1] << '\n';
    }

	return 0;
}