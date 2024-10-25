#include <bits/stdc++.h>
using namespace std;

int main() {
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif

    // cin.tie(NULL); cout.tie(NULL);
    // ios_base::sync_with_stdio(false);

    string s;
    getline(cin, s);

    int ph = 0, pg = 0;
    for (auto& c : s) {
        if (c == 'H' || c == 'A' || c == 'P' || c == 'Y') ph++;
        if (c == 'S' || c == 'A' || c == 'D') pg++;
    }

    if (ph + pg == 0) {
        cout << "50.00";
        return 0;
    }
 
    cout << fixed;
    cout.precision(2);
    cout << (double)ph / (ph + pg) * 100;
}
