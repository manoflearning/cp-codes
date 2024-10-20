#include <bits/stdc++.h>
using namespace std;
#define ll long long

bool vi[2020][2020];

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    int d1, d2;
    cin >> d1 >> d2;

    int ans = 0;
    for (int i = d1; i <= d2; i++) {
        for (int j = 0; j < i; j++) {
            int n = i, d = j;
            n /= gcd(i, j);
            d /= gcd(i, j);
            if (!vi[n][d]) {
                vi[n][d] = 1;
                ans++;
            }
        }
    }

    cout << ans;
}