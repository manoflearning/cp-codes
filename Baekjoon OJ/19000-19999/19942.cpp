#include <bits/stdc++.h>
using namespace std;

int n;
int mna, mnb, mnc, mnd;
int a[22], b[22], c[22], d[22], e[22];
int ans = 1e9 + 7;
vector<int> ans2;

vector<int> res;

void bt(int idx, int aa, int bb, int cc, int dd, int ee) {
    if (idx == n + 1) {
        if (aa >= mna && bb >= mnb && cc >= mnc && dd >= mnd) {
            if (ee < ans || (ee == ans && ans2 > res)) {
                ans = ee;
                ans2 = res;
            }
        }
        return;
    }

    bt(idx + 1, aa, bb, cc, dd, ee);
    res.push_back(idx);
    bt(idx + 1, aa + a[idx], bb + b[idx], cc + c[idx], dd + d[idx], ee + e[idx]);
    res.pop_back();
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;
    cin >> mna >> mnb >> mnc >> mnd;
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i] >> c[i] >> d[i] >> e[i];

    bt(1, 0, 0, 0, 0, 0);

    if (ans == 1e9 + 7) {
        cout << -1;
        return 0;
    }

    cout << ans << '\n';
    for (auto& i : ans2) 
        cout << i << ' ';

	return 0;
}