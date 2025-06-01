#include <bits/stdc++.h>
using namespace std;
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;
    while (T--) {
        int N;
        unsigned long long K;
        cin >> N >> K;

        vector<unsigned long long> A(N + 1);
        for (int i = 1; i <= N; i++) {
            cin >> A[i];
        }

        if (N == 3 && K == 0) {
            cout << "Yes\n3\n1 1 1\n";
            continue;
        }

        if (K == 0) {
            cout << "Yes\n2\n1 1\n";
            continue;
        }

        if (N == 3) {
            unsigned long long a1 = A[1], a2 = A[2], a3 = A[3];
            if (K == a2) {
                cout << "No\n";
            } else if (K == a1) {
                cout << "Yes\n0\n\n";
            } else if (K == (a1 ^ a2)) {
                cout << "Yes\n1\n1\n";
            } else if (K == (a2 ^ a3)) {
                cout << "Yes\n3\n1 1 1\n";
            } else if (K == (a1 ^ a2 ^ a3)) {
                cout << "Yes\n2\n2 1\n";
            } else if (K == (a1 ^ a3)) {
                cout << "Yes\n3\n1 1 1\n";
            } else {
                cout << "No\n";
            }
            continue;
        }

        static unsigned long long basisVal[60], basisMask[60];
        for (int b = 0; b < 60; b++) {
            basisVal[b] = basisMask[b] = 0ULL;
        }

        for (int i = 1; i <= N; i++) {
            unsigned long long x = A[i], m = 1ULL << (i - 1);
            for (int b = 59; b >= 0; b--) {
                if (!((x >> b) & 1ULL)) continue;
                if (!basisVal[b]) {
                    basisVal[b] = x;
                    basisMask[b] = m;
                    break;
                }
                x ^= basisVal[b];
                m ^= basisMask[b];
            }
        }

        unsigned long long cur = K, maskK = 0ULL;
        bool bad = false;
        for (int b = 59; b >= 0; b--) {
            if (!((cur >> b) & 1ULL)) continue;
            if (!basisVal[b]) {
                cout << "No\n";
                bad = true;
                break;
            }
            cur ^= basisVal[b];
            maskK ^= basisMask[b];
        }
        if (bad) continue;
        if (cur != 0ULL) {
            cout << "No\n";
            continue;
        }

        auto is_unreachable = [&](unsigned long long M) {
            if (N == 3) {
                if (M == (1ULL << 1) || M == ((1ULL << 0) | (1ULL << 2))) return true;
                return false;
            } else {
                unsigned long long odd = 0ULL, even = 0ULL;
                for (int i = 1; i <= N; i += 2) odd |= (1ULL << (i - 1));
                for (int i = 2; i <= N; i += 2) even |= (1ULL << (i - 1));
                return (M == odd || M == even);
            }
        };

        if (is_unreachable(maskK)) {
            cout << "No\n";
            continue;
        }

        vector<int> S;
        for (int i = 1; i <= N; i++) {
            if ((maskK >> (i - 1)) & 1ULL) {
                S.push_back(i);
            }
        }
        sort(S.begin(), S.end());

        if (S.size() == 2 && S[0] == 1) {
            int j = S[1];
            cout << "Yes\n4\n" << (j - 2) << " " << (j - 1) << " " << (j - 2) << " 1\n";
            continue;
        }

        vector<int> ops;
        auto bringA1 = [&](int j) {
            for (int k = j - 1; k >= 2; k--) {
                ops.push_back(k);
                ops.push_back(k);
            }
            for (int t = j - 1; t >= 1; t--) {
                ops.push_back(t);
            }
        };
        auto bringA2 = [&](int j) {
            for (int u = j - 1; u >= 3; u--) {
                int p = u - 1;
                ops.push_back(p);
                ops.push_back(p);
            }
            for (int t = j - 1; t >= 2; t--) {
                ops.push_back(t);
            }
            ops.push_back(1);
        };

        int i1 = S[0];
        if (i1 != 1) bringA1(i1);
        for (size_t idx = 1; idx < S.size(); idx++) {
            bringA2(S[idx]);
        }

        if ((int)ops.size() > 10000) {
            cout << "No\n";
        } else {
            cout << "Yes\n" << ops.size() << "\n";
            for (int x : ops) cout << x << " ";
            cout << "\n";
        }
    }
    return 0;
}
