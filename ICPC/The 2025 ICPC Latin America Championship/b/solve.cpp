#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int K = 1515;

typedef bitset<K> bs;

int solveLinear(vector<bs> &A, vi &b, bs& x, int m) {
	int n = sz(A), rank = 0, br;
	assert(m <= sz(x));
	vi col(m); iota(all(col), 0);
	rep(i,0,n) {
		for (br=i; br<n; ++br) if (A[br].any()) break;
		if (br == n) {
			rep(j,i,n) if(b[j]) return -1;
			break;
		}
		int bc = (int)A[br]._Find_next(i-1);
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) if (A[j][i] != A[j][bc]) {
			A[j].flip(i); A[j].flip(bc);
		}
		rep(j,i+1,n) if (A[j][i]) {
			b[j] ^= b[i];
			A[j] ^= A[i];
		}
		rank++;
	}

	x = bs();
    if (rank < m) {
        x[col[rank]] = 1;

        for (int i = rank - 1; i >= 0; i--) {
            int val = 0;
            if (A[i][rank]) val ^= 1;
            for (int j = i + 1; j < rank; j++) {
                if (A[i][j] && x[col[j]]) val ^= 1;
            }
            x[col[i]] = val;
        }
    } else {
        for (int i = rank; i--;) {
            if (!b[i]) continue;
            x[col[i]] = 1;
            rep(j,0,i) b[j] ^= A[j][i];
        }
    }
	return rank; // (multiple solutions if rank < m)
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    vector<string> fuck(n);
    for (auto &i : fuck) cin >> i;

    vector<bs> A(k + 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++) A[j][i] = fuck[i][j] == '1';
    for (int i = 0; i < n; i++) A[k][i] = 1;

    bs x{};
    vector<int> b(k + 1);

    const int rank = solveLinear(A, b, x, n);

    if (rank == -1 || rank == n) {
        cout << "*";
        return 0;
    }

    int cnt_all = 0, cnt_team1 = 0;
    for (int i = 0; i < n; i++) {
        if (x[i]) cnt_all++;
    }

    for (int i = 0; i < n; i++) {
        if (x[i]) {
            cnt_team1++;
            if (cnt_team1 <= cnt_all / 2) cout << 1;
            else cout << 2;
        } else {
            cout << 0;
        }
    }
}
