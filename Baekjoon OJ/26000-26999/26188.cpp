#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MAXN = 2020;

int n;
pll a[MAXN];

ll dist[MAXN << 1][MAXN << 1];
int siz[MAXN << 1];
int p;

vector<int> ans;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) 
        cin >> a[i].fr >> a[i].sc;
}

void preprocessing() {
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            ll res = (a[i].fr - a[j].fr) * (a[i].fr - a[j].fr) 
            + (a[i].sc - a[j].sc) * (a[i].sc - a[j].sc);

            dist[i][j] = dist[j][i] = res;
        }
        siz[i] = 1;
    }
    p = n + 1;
}

struct State {
    ll n; int d; // n / d
    int age1, age2;
    bool operator<(const State& rhs) const {
        if ((n * rhs.d) ^ (rhs.n * d)) return n * rhs.d > rhs.n * d;
        if (age1 ^ rhs.age1) return age1 > rhs.age1;
        else return age2 > rhs.age2;
    }
};

void solve() {
    priority_queue<State> pq;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            pq.push({ dist[i][j], siz[i] * siz[j], i, j });
        }
    }

    vector<int> vi(MAXN << 1);
    while (!pq.empty()) {
        State now = pq.top();
        pq.pop();
        if (vi[now.age1] || vi[now.age2]) continue;
        
        int idx = p++;
        vi[now.age1] = vi[now.age2] = 1;
        siz[idx] = siz[now.age1] + siz[now.age2];

        ans.push_back(siz[idx]);

        for (int i = 1; i < idx; i++) {
            if (vi[i]) continue;
            ll res = dist[i][now.age1] + dist[i][now.age2];
            dist[i][idx] = dist[idx][i] = res;
            pq.push({ dist[i][idx], siz[i] * siz[idx], i, idx });
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    preprocessing();

    solve();

    for (auto& i : ans)
        cout << i << '\n';
}