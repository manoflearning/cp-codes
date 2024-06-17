#pragma gcc optimize("Ofast")
#pragma gcc optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int n, k;
ll a[202020], psum[202020];
double ans = 0;

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        psum[i] = a[i] + psum[i - 1];
    }
}

inline double AVG(int l, int r) { 
    if (l > r) swap(l, r);
    return (double)(psum[r] - psum[l - 1]) / (r - l + 1);
}

bool f(double x) {
    int st = 1, cnt = 0;
    {
        for (int en = 1; en <= n; en++) {
            // if (x > AVG(st, en)) continue;
            if (cnt + 1 == k && x <= AVG(st, n)) return 1;

            if (x <= AVG(st, en) && x <= AVG(en + 1, n)) st = en + 1, cnt++;
        }
    }
    if (cnt >= k) return 1;
    {
        st = n, cnt = 0;
        for (int en = n; en >= 1; en--) {
            // if (x > AVG(st, en)) continue;
            if (cnt + 1 == k && x <= AVG(1, st)) return 1;

            if (x <= AVG(st, en) && x <= AVG(en - 1, 1)) st = en - 1, cnt++;
        }
    }
    return cnt >= k;
}

void bs() {
    double l = 1e9, r = AVG(1, n);
    for (int i = 1; i <= n; i++) l = min<double>(l, a[i]);

    for (int tt = 0; tt < 50; tt++) {
        double mid = (l + r) / 2;

        if (f(mid)) l = mid;
        else r = mid;
    }

    ans = max(ans, l);
}

set<pair<int, int>> st;
void uflike() {
    priority_queue<pair<double, pair<int, int>>> pq;
    for (int i = 1; i <= n; i++) {
        st.insert({ i, i });
        pq.push({ -AVG(i, i), { i, i } });
    }

    while (sz(st) > k) {
        double l, r;
        do {
            l = pq.top().second.first, r = pq.top().second.second;
            pq.pop();
        } while (!st.count({ l, r }));
        
        double lavg = -1e9, ravg = -1e9;

        auto it = st.lower_bound({ l, r });
        if (it != st.begin()) {
            it--;
            auto [l2, r2] = *it;
            lavg = AVG(l2, r);
        }
        it = st.lower_bound({ l, r });
        it++;
        if (it != st.end()) {
            auto [l2, r2] = *it;
            ravg = AVG(l, r2);
        }

        it = st.lower_bound({ l, r });
        if (lavg >= ravg) {
            it--;
            auto [l2, r2] = *it;
            st.erase({ l, r });
            st.erase({ l2, r2 });
            st.insert({ l2, r });
            pq.push({ -AVG(l2, r), { l2, r }});
        }
        else {
            it++;
            auto [l2, r2] = *it;
            st.erase({ l, r });
            st.erase({ l2, r2 });
            st.insert({ l, r2 });
            pq.push({ -AVG(l, r2), { l, r2 }});
        }
    }

    double res = 1e9;
    for (auto& i : st) {
        res = min(res, AVG(i.first, i.second));
    }

    ans = max(ans, res);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    bs();

    uflike();

    cout << fixed;
    cout.precision(6);
    cout << ans;
}