#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    int res = 0, ans = 1;
    vector<int> cnt(11);
    queue<int> q;
    for (int i = 0; i < n; i++) {
        cnt[a[i]]++;
        if (cnt[a[i]] == 1) res++;

        q.push(i);

        while (!q.empty() && res > 2) {
            cnt[a[q.front()]]--;
            if (cnt[a[q.front()]] == 0) res--;
            q.pop();
        }

        ans = max(ans, (int)q.size());
    }

    cout << ans;
}
