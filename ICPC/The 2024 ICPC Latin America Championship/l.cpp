#include <bits/stdc++.h>
using namespace std;

int R, C, K;
vector<string> a, b;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> R >> C >> K;
    a.resize(R);
    b.resize(R);
    for (int i = 0; i < R; i++) {
        cin >> a[i] >> b[i];
    }

    for (int i = 0; i < R; i++) {
        bool vis = 0;
        for (int j = 0; j < K; j++) {
            if (b[i][j] == '*') vis = 1;
        }

        if (vis) {
            for (int j = 0; j < C; j++) {
                if (a[i][j] == '-') {
                    cout << 'N';
                    return 0;
                }
            }
        }
    }

    cout << 'Y';
}