#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int k, n; 
    cin >> k >> n;
    
    vector<string> a(k);
    for (auto& i : a) cin >> i;

    sort(a.begin(), a.end(), [&](const string& p1, const string& p2) {
        return (sz(p1) ^ sz(p2) ? sz(p1) > sz(p2) : p1 > p2);
    });

    vector<string> b;
    for (int i = 0; i < n - k; i++) b.push_back(a[0]);
    for (int i = 0; i < k; i++) b.push_back(a[i]);

    sort(b.begin(), b.end(), [&](const string& p1, const string& p2) {
        /*for (int i = 0; i < 2 * max(sz(p1), sz(p2)); i++) {
            if (p1[i % sz(p1)] != p2[i % sz(p2)]) return p1[i % sz(p1)] > p2[i % sz(p2)];
        }
        return sz(p1) > sz(p2);*/
        return p1 + p2 > p2 + p1;
    });

    for (auto& i : b) cout << i;
}