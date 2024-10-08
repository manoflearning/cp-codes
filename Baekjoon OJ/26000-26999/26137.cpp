#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int H0 = 1e7;
const int MAXN = 1010101;

int n;
vector<string> a;
int lb[MAXN], diff[MAXN];

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

    vector<int> ord1, ord2;

    for (int i = 0; i < n; i++) {
        int h = H0;
        int hmn = h;
        for (auto& c : a[i]) {
            h += (c == '(' ? 1 : -1);
            hmn = min(hmn, h);
        }

        lb[i] = H0 - hmn;
        diff[i] = h - H0;

        if (diff[i] >= 0) ord1.push_back(i);
        else ord2.push_back(i);
    }

    sort(all(ord1), [&](int p1, int p2) {
        return lb[p1] < lb[p2];
    });

    int now = 0;
    for (int i = 0; i < sz(ord1); i++) {
        int x = ord1[i];
        if (now < lb[x]) {
            cout << "impossible";
            exit(0);
        }
        now += diff[x];
    }

    for (int i = 0; i < sz(ord2); i++) {
        string& s = a[ord2[i]];
        reverse(all(s));
        for (auto& c : s)
            c = (c == '(' ? ')' : '(');

        int h = H0;
        int hmn = h;
        for (auto& c : s) {
            h += (c == '(' ? 1 : -1);
            hmn = min(hmn, h);
        }

        lb[ord2[i]] = H0 - hmn;
        diff[ord2[i]] = h - H0;
    }

    sort(all(ord2), [&](int p1, int p2) {
        return lb[p1] < lb[p2];
    });

    int now2 = 0;
    for (int i = 0; i < sz(ord2); i++) {
        int x = ord2[i];
        if (now2 < lb[x]) {
            cout << "impossible";
            exit(0);
        }
        now2 += diff[x];
    }

    if (now != now2) {
        cout << "impossible";
        exit(0);
    }

    for (auto& i : ord1) cout << i + 1 << '\n';
    reverse(all(ord2));
    for (auto& i : ord2) cout << i + 1 << '\n';
}
