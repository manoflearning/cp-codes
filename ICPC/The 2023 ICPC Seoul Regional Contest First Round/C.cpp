#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int h = 0, s = 0;

    while (1) {
        string S; cin >> S;
        if (cin.eof()) break;
        for (auto& i : S) {
            if (i == 'H') h++;
            else if (i == 'A') h++, s++;
            else if (i == 'P') h++;
            else if (i == 'Y') h++;
            else if (i == 'S') s++;
            else if (i == 'D') s++;
        }
    }

    cout << fixed;
    cout.precision(2);

    const double eps = 1e-8;

    if (h == 0 && s == 0) cout << "50.00";
    else cout << ((double)h / (h + s) + eps) * 100;
}