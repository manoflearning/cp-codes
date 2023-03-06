#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;
const int MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;
const int MAX = 90 * 10000 * 2 + 100;

int n;
vector<int> a[MAX], b[MAX];
ll d = 180 * 10000 * 2, dexp1[404040], dexp2[404040];

int rabinKarp(vector<int>& aa, vector<int>& bb) {
	ll a1 = 0, a2 = 0, b1 = 0, b2 = 0;
	for (int i = 0; i < aa.size(); i++) {
		a1 = (d * a1 + aa[i]) % MOD1;
		a2 = (d * a2 + aa[i]) % MOD2;
		b1 = (d * b1 + bb[i]) % MOD1;
		b2 = (d * b2 + bb[i]) % MOD2;
	}
	if (a1 == b1 && a2 == b2) return 0;
    cout << a1 << ' ' << a2 << '\n' << b1 << ' ' << b2 << "\n\n";
	for (int i = 1; i < bb.size(); i++) {
		b1 = (d * (b1 - dexp1[bb.size() - 1] * bb[i - 1]) + bb[i - 1]) % MOD1;
		b1 = (b1 + MOD1) % MOD1;
		b2 = (d * (b2 - dexp2[bb.size() - 1] * bb[i - 1]) + bb[i - 1]) % MOD2;
		b2 = (b2 + MOD2) % MOD2;
        cout << a1 << ' ' << a2 << '\n' << b1 << ' ' << b2 << "\n\n";
		if (a1 == b1 && a2 == b2) return i;
	}
    return -1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    dexp1[0] = dexp2[0] = 1;
    for (int i = 1; i < 404040; i++) {
        dexp1[i] = d * dexp1[i - 1] % MOD1;
        dexp2[i] = d * dexp2[i - 1] % MOD2;
    }

    cin >> n;
    for (int i = 0; i < 2 * n; i++) {
        double x, y;
        cin >> x >> y;
        x *= 10000, y *= 10000;
        x += 90 * 10000, y += 180 * 10000;
        if (i < n) a[(int)x].push_back(y);
        else b[(int)x].push_back(y);
    }

    int ans = 1;
    int diff = INF;
    for (int i = 0; i < MAX; i++) {
        if (a[i].size() != b[i].size()) { ans = 0; break; }
        if (a[i].empty() && b[i].empty()) continue;

        if (diff != INF) {
            for (auto& j : a[i]) j += diff, j = (j + d) % d;
            for (auto& j : b[i]) j = (j + d) % d;
            sort(a[i].begin(), a[i].end());
            sort(b[i].begin(), b[i].end());
            if (a[i] != b[i]) { ans = 0; break; }
        }
        else {
            sort(a[i].begin(), a[i].end());
            sort(b[i].begin(), b[i].end());

            vector<int> aa(1, a[i][0] - a[i].back());
            vector<int> bb(1, b[i][0] - b[i].back());
            for (int j = 1; j < a[i].size(); j++) {
                aa.push_back(a[i][j] - a[i][j - 1]);
                bb.push_back(b[i][j] - b[i][j - 1]);
            }

            for (auto& j : aa) j = (j + d) % d;
            for (auto& j : bb) j = (j + d) % d;

            for (auto& j : aa) cout << j << ' ';
            cout << '\n';
            for (auto& j : bb) cout << j << ' ';
            cout << '\n';
            cout << '\n';

            int idx = rabinKarp(aa, bb);
            if (idx == -1) { ans = 0; break; }
            diff = b[i][idx] - a[i][0];
            cout << diff << '\n';
        }
    }

    if (ans) cout << "Same";
    else cout << "Different";
}