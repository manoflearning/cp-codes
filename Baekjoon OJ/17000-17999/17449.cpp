#include <bits/stdc++.h>
using namespace std;

int r, n;
int a[202020];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> r >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    int rb = r, same = 0, rw = r;
    for (int i = 0; i < n; i++) {
        if (a[i] < rb) rb++;
        else if (a[i] == rb) {
            same++;
        }
        else if (a[i] > rb) {
            if (a[i] <= rb + same) {
                int diff = rb + same - a[i];
                rb = a[i];
                same -= diff;
            }
        }

        if (a[i] <= rw) rw++;

        // cout << i << ' ' << rb << ' ' << same << ' ' << rw << '\n';
    }

    cout << rb << ' ' << rw;
}