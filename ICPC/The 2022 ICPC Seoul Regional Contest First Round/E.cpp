#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif
    
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    ll n, b, a;
    cin >> n >> b >> a;

    vector<ll> arr(1, -1);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        arr.push_back(x);
    }

    sort(arr.begin(), arr.end());

    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        ll sum = 0;
        for (int i = 1; i <= mid; i++) {
            if (i > mid - a) sum += arr[i] / 2;
            else sum += arr[i];
        }
        if (sum > b) r = mid - 1;
        else l = mid;
    }

    cout << l;

    return 0;
}