#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>

int n;
vector<pii> a;
int dp[121][121];

int f(int l, int r) {
	auto& ret = dp[l][r];
	if (ret != -1) return ret;

	ret = 0;

	vector<pii> b;
	for (auto& i : a) {
		if (l <= i.first && i.second <= r) b.push_back(i);
	}

	priority_queue<pii, vector<pii>, greater<pii>> pq;
	int prv_cnt = 0;
	for (auto& i : b) {
		while (!pq.empty() && pq.top().first < i.first) {
			prv_cnt = max(prv_cnt, pq.top().second);
			pq.pop();
		}

		int res = prv_cnt + 1 + f(i.first + 1, i.second - 1);
		pq.push({ i.second, res });
		
		ret = max(ret, res);
	}

	return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

	memset(dp, -1, sizeof(dp));

    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.first >> i.second;
        if (i.first > i.second)
            swap(i.first, i.second);
    }

    sort(a.begin(), a.end());

	cout << f(1, 100);
}