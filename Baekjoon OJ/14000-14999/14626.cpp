#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    string s; cin >> s;

    int sum = 0, idx = -1;
    for (int i = 0; i < 13; i++) {
        if (s[i] == '*') {
            idx = i;
        } else {
            sum += (i & 1 ? 3 : 1) * (s[i] - '0');
        }
    }

    if (idx & 1) {
        map<int, int> mp;
        for (int i = 0; i < 10; i++) {
            mp[i * 3 % 10] = i;
        }
        cout << mp[(10 - sum % 10) % 10];
    } else {
        cout << (10 - sum % 10) % 10;
    }
}