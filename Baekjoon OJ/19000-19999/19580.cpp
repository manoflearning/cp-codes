#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

struct Citizen { ll L, R; };
struct Store { ll P; int X; };

int n, m;
vector<Citizen> a;
vector<Store> b;

void input() {
    cin >> n >> m;
    a.resize(n);
    for (auto& i : a)
        cin >> i.L >> i.R;
    b.resize(m);
    for (auto& i : b)
        cin >> i.P >> i.X;
}

vector<ll> c;

void valueCompress() {
    c.push_back(-1);
    for (auto& i : a) {
        c.push_back(i.L);
        c.push_back(i.R);
    }
    for (auto& i : b)
        c.push_back(i.P);

    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());

    for (auto& i : a) {
        i.L = lower_bound(c.begin(), c.end(), i.L) - c.begin();
        i.R = lower_bound(c.begin(), c.end(), i.R) - c.begin();
    }
    for (auto& i : b)
        i.P = lower_bound(c.begin(), c.end(), i.P) - c.begin();
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    valueCompress();

    vector<vector<int>> L(sz(c));
    for (auto& i : a)
        L[i.L].push_back(i.R);
    
    vector<ll> mask(sz(c));
    for (auto& i : b)
        mask[i.P] += i.X;

    int ans = 0;

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i < sz(c); i++) {
        for (auto& j : L[i]) pq.push(j);

        while (sz(pq) && pq.top() < i) pq.pop();
        while (sz(pq) && mask[i] > 0) {
            mask[i]--; pq.pop();
            ans++;
        }
    }

    cout << ans;
}