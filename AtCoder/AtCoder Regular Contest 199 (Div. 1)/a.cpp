#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; if (!(cin >> T)) return 0;
    while (T--) {
        int N; cin >> N;
        vector<string> A(N);
        for (auto& s : A) cin >> s;
        vector<int> R(N), C(N);
        for (int& x : R) cin >> x;
        for (int& x : C) cin >> x;

        vector<int> Y(N, -1);
        for (int j = 0; j < N; ++j) {
            int bj = 0;
            for (int i = 0; i < N; ++i) bj += A[i][j] - '0';
            if (bj == C[j]) Y[j] = 0;
            else if (N - bj == C[j]) Y[j] = 1;
            else { cout << "No\n"; goto next; }
        }

        for (int i = 0; i < N; ++i) {
            int s = 0;
            for (int j = 0; j < N; ++j) s += (A[i][j] - '0') ^ Y[j];
            if (s != R[i]) { cout << "No\n"; goto next; }
        }

        cout << "Yes\n";
        cout << string(N, '0') << '\n';
        for (int y : Y) cout << y;
        cout << '\n';

    next:;
    }
}
