#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int MAXN = 1010101 * 2;
const int MOD = 1e6 + 3;

int n, k;
vector<int> a(MAXN / 2);

int dfsn[MAXN], dCnt, sNum[MAXN], sCnt;
int finished[MAXN];
vector<int> adj[MAXN];
int sind[MAXN];
stack<int> stk;
pii p[MAXN];

inline int inv(int x) {
	// negative number -a indicates ¬a.
	return (x > 0) ? 2 * (x - 1) : 2 * (-x - 1) + 1;
}

void twoCnf(int a, int b) {
	// (a ∨ b) iff (¬a → b) iff (¬b → a)
	adj[inv(-a)].push_back(inv(b));
	adj[inv(-b)].push_back(inv(a));
}

void implies(int a, int b) {
    adj[inv(a)].push_back(inv(b));
}

int dfs(int now) {
	int ret = dfsn[now] = ++dCnt;
	stk.push(now);
	for (int next : adj[now]) {
		if (dfsn[next] == -1) ret = min(ret, dfs(next));
		else if (!finished[next]) ret = min(ret, dfsn[next]);
	}
	if (ret >= dfsn[now]) {
		while (1) {
			int t = stk.top();
			stk.pop();
			sNum[t] = sCnt;
			finished[t] = 1;
			if (t == now) break;
		}
		sCnt++;
	}
	return ret;
}

int isSatisfiable() {
	// determining satisfiability 
	int isS = 1;
	for (int v = 0; v < 2 * n; v += 2) {
		// if x and ¬x is in same scc, then the proposition is not satisfiable
		if (sNum[v] == sNum[v + 1]) {
			isS = 0;
			break;
		}
	}
	return isS;
}

ll fac[MAXN], _inv[MAXN], facInv[MAXN];
ll binom(int n, int r) {
	return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // Preprocessing in O(N)
	fac[0] = fac[1] = _inv[1] = 1;
	facInv[0] = facInv[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		fac[i] = i * fac[i - 1] % MOD;
		_inv[i] = -(MOD / i) * _inv[MOD % i] % MOD;
		if (_inv[i] < 0) _inv[i] += MOD;
		facInv[i] = facInv[i - 1] * _inv[i] % MOD;
	}

    memset(dfsn, -1, sizeof(dfsn));

    cin >> n >> k;
    for (int i = 0; i < n - k + 1; i++) cin >> a[i];

    ll ans = 1;
    for (int i = 0; i + 1 < n - k + 1; i++) {
        if (a[i] == a[i + 1] + 1) {
            twoCnf(i, i);
            twoCnf(-(i + k), -(i + k));
        } else if (a[i] + 1 == a[i + 1]) {
            twoCnf(-i, -i);
            twoCnf(i + k, i + k);
        } else if (a[i] == a[i + 1]) {
            implies(i, i + k);
            implies(i + k, i);
        } else {
            cout << 0;
            exit(0);
        }
    }

    for (int v = 0; v < 2 * n; v++)
		if (dfsn[v] == -1) dfs(v);

    if (isSatisfiable()) {
        int cnt1 = 0, cnt0 = 0;
        for (int i = 0; i + 1 < n - k + 1 && i < k; i++) {
            for (int j = i; j + 1 < n - k + 1; j += k) {
                if (a[j] == a[j + 1] + 1) { cnt1++; break; }
                if (a[j] + 1 == a[j + 1]) { cnt0++; break; }
            }
        }

        cout << binom(k - cnt1 - cnt0, a[0] - cnt1);
    } else {
        cout << 0;
    }
}
