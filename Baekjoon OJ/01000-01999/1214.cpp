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

    ll D, P, Q;
    cin >> D >> P >> Q;
    if (P > Q) swap(P, Q); // P <= Q
    
    // D <= xP + yQ
    // D <= zPQ + x'P + y'Q (x' < Q, y' < P)
    // x'P + y'Q < 2PQ
    ll cnt = max(0ll, D - 2 * P * Q) / (P * Q);
    D -= cnt * P * Q;
    
    ll res = 1e18;
    for (int i = 0; i * Q <= D + Q; i++) {
        ll leftD = max(0ll, D - i * Q);
        res = min(res, (leftD + P - 1) / P * P + i * Q);
    }
    cout << cnt * P * Q + res;
}