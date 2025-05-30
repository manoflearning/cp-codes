//#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX = 202020;

int n;
vector<int> p1(MAX), p2(MAX);
vector<vector<int>> t1(MAX), t2(MAX);

int cnt;
vector<int> in1(MAX), in2(MAX), out1(MAX), out2(MAX);

void input() {
    cin >> n;
    for (int v = 2; v <= n; v++) {
        cin >> p1[v];
        t1[p1[v]].push_back(v);
    }
    for (int v = 2; v <= n; v++) {
        cin >> p2[v];
        t2[p2[v]].push_back(v);
    }
}

void dfs(int v, const vector<vector<int>>& t, vector<int>& in, vector<int>& out) {
    in[v] = ++cnt;
    for (auto& i : t[v]) {
        dfs(i, t, in, out);
    }
    out[v] = cnt;
}

// fenwick tree
struct Fenwick { // 0-indexed
	int flag, cnt; // array size
	vector<ll> arr, t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1, cnt++);
		arr.resize(flag);
		t.resize(flag);
	}
	void add(int p, ll value) { // add value at position p
		arr[p] += value;
		while (p < flag) {
			t[p] += value;
			p |= p + 1;
		}
	}
	ll query(int x) {
		ll ret = 0;
		while (x >= 0) ret += t[x], x = (x & (x + 1)) - 1;
		return ret;
	}
	ll query(int l, int r) {
		return query(r) - (l ? query(l - 1) : 0);
	}
}fw;

struct Query {
    ll x1, x2, y1, y2;
    int idx;
};
vector<Query> q;
vector<int> ans(MAX);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs(1, t2, in1, out1);
    cnt = 0;
    dfs(1, t1, in2, out2);

    for (int v = 1; v <= n; v++) {
        q.push_back({ in1[v], out1[v], in2[v], out2[v], v });
    }

    sort(q.begin(), q.end(), [&](const Query& lhs, const Query& rhs) {
        return lhs.x1 > rhs.x1;
    });

    fw.build(cnt + 1);
    queue<pair<int, int>> qu;
    for (auto& i : q) {
        /*while (!qu.empty() && qu.front().first > i.x2) {
            fw.add(qu.front().second, -1);
            qu.pop();
        }*/
        cout << i.x1 << ' ' << i.x2 << ' ' << i.y1 << ' ' << i.y2 << ' ' << i.idx << '\n';
        ans[i.idx] = fw.query(i.y1 + 1, i.y2);
        fw.add(i.y1, 1);
        qu.push({ i.x1, i.y1 });
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
}