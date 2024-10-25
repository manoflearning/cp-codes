#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    // cin.tie(NULL); cout.tie(NULL);
    // ios_base::sync_with_stdio(false);

    int n; cin >> n;
    for (int i = 2; i <= n - 1; i++) {
        cout << "? " << i << endl;
        cout << flush;
        int x; cin >> x;
        if (x == 1) {
            cout << "! " << i - 1 << endl;
            cout << flush;
            string s; cin >> s;
            exit(0);
        }
    }

    cout << "! " << n - 1 << endl;
    cout << flush;
    string s; cin >> s;
}
