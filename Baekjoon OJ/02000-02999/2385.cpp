#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    vector<string> a(n);
    for (auto& i : a) cin >> i;

    vector<string> b = a;
    sort(b.begin(), b.end(), [&](const string& p1, const string& p2) {
        return p1 + p2 < p2 + p1;
    });

    string du;
    if (b[0][0] == '0') du = b[0];

    sort(a.begin(), a.end(), [&](const string& p1, const string& p2) {
        if (p1[0] == '0' && p2[0] == '0') return p1 < p2;
        else if (p1[0] == '0' || p2[0] == '0') return p1 > p2;
        else return p1 + du + p2 < p2 + du + p1;
    });

    if (a[0][0] == '0') {
        cout << "INVALID";
        return 0;
    }

    sort(a.begin() + 1, a.end(), [&](const string& p1, const string& p2) {
        return p1 + p2 < p2 + p1;
    });

    for (auto& i : a) cout << i;
}