#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second

const int sq = 257;

int n;
vector<pii> a;
vector<int> c;
vector<int> xx[101010];

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) 
        cin >> i.fr >> i.sc;
}

void cc() {
    for (auto& i : a)
        c.push_back(i.fr);

    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());

    for (auto& i : a)
        i.fr = lower_bound(c.begin(), c.end(), i.fr) - c.begin();
}

void descending() {
    vector<pii> xcnt;
    vector<int> Hash(101010);

    for (int i = 0; i < 101010; i++) {
        xcnt.push_back({ i, 0 });
    }
    for (auto& i : a) xcnt[i.fr].sc++;

    sort(xcnt.begin(), xcnt.end(), [&](const pii& a, const pii& b) {
        return a.sc > b.sc;
    });

    for (int i = 0; i < 101010; i++) {
        Hash[xcnt[i].fr] = i;
    }

    for (auto& i : a) i.fr = Hash[i.fr];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    cc();    

    descending();

    for (auto& i : a)
        xx[i.fr].push_back(i.sc);

    for (int i = 0; i < c.size(); i++) {
        sort(xx[i].begin(), xx[i].end());
    }

    ll ans = 0;
    for (int i = 0; i < c.size(); i++) {
        if (xx[i].size() < sq) break;

        auto& x1 = xx[i];
        ll cnt = 0;
        for (int j = i + 1; j < c.size(); j++) {
            auto& x2 = xx[j];

            for (auto& y : x2) {
                if (y == *lower_bound(x1.begin(), x1.end(), y)) cnt++;
            }
        }

        ans += cnt * (cnt - 1) / 2;
    }

    map<pii, ll> mp;
    for (int i = 0; i < c.size(); i++) {
        if (xx[i].size() >= sq) continue;

        auto& x1 = xx[i];
        for (int j = 0; j < x1.size(); j++) {
            for (int k = j + 1; k < x1.size(); k++) {
                mp[{ x1[j], x1[k] }]++;
            }
        }
    }

    for (auto& i : mp) 
        ans += i.sc * (i.sc - 1) / 2;

    cout << ans;

    return 0;
}