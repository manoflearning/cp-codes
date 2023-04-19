// - 주어진 수열에 (A_i < 0 and 0 < A_j and |A_i| != |A_j|)를 만족하는 두 인덱스 i, j가 있다고 하자.
// - 
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
vector<ll> a;

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

    sort(a.begin(), a.end());

    ll ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans = max(ans, min(a[n - 1] - a[i], a[i]));
    }

    cout << ans;
}