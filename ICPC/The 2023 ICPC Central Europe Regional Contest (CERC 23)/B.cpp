#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

ll ccw(const pii& a, const pii& b, const pii& c) {
    ll res = (b.fr - a.fr) * (c.sc - a.sc) - (c.fr - a.fr) * (b.sc - a.sc);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

double dist(const pii& a, const pii& b) {
    return sqrt((a.fr - b.fr) * (a.fr - b.fr) + (a.sc - b.sc) * (a.sc - b.sc));
}

int n;
string s;
vector<pii> a1, a2;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if (s[i] == 'B') a1.push_back({ x, y });
        if (s[i] == 'G') a2.push_back({ x, y });
    }

    sort(all(a1), [&](const pii& p1, const pii& p2) {
        return (p1.sc ^ p2.sc ? p1.sc < p2.sc : p1.fr < p2.fr);
    });

    if (!a1.empty()) {
        sort(a1.begin() + 1, a1.end(), [&](const pii& p1, const pii& p2) {
            return ccw(a1[0], p1, p2) > 0;
        });
    }

    sort(all(a2), [&](const pii& p1, const pii& p2) {
        return (p1.sc ^ p2.sc ? p1.sc < p2.sc : p1.fr < p2.fr);
    });

    if (!a2.empty()) {
        sort(a2.begin() + 1, a2.end(), [&](const pii& p1, const pii& p2) {
            return ccw(a2[0], p1, p2) > 0;
        });
    }

    double ans = 0;
    for (int i = 0; i + sz(a1) / 2 < sz(a1); i++) {
        ans += dist(a1[i], a1[i + sz(a1) / 2]);
    }
    for (int i = 0; i + sz(a2) / 2 < sz(a2); i++) {
        ans += dist(a2[i], a2[i + sz(a2) / 2]);
    }

    cout << fixed;
    cout.precision(8);
    cout << ans;
}