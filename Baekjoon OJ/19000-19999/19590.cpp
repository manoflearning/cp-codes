#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int n;
vector<ll> a;

int main() {
    #ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    sort(a.rbegin(), a.rend());

    ll sum = -a[0];
    for (auto& i : a) sum += i;

    if (a[0] >= sum) cout << a[0] - sum;
    else cout << ((sum + a[0]) & 1 ? 1 : 0);

    return 0;
}