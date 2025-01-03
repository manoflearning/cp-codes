#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size() 

const ll INF = 1e18;

int n, m;
ll w, h;
struct Point { ll x, y, lx, dy, rx, uy; };
vector<Point> a, b;
vector<ll> cx, cy;

void input() {
    cin >> n >> m >> w >> h;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.x >> i.y;
        i.lx = i.x - w, i.rx = i.x;
        i.dy = i.y - h, i.uy = i.y;
    }
    b.resize(m);
    for (auto& i : b) {
        cin >> i.x >> i.y;
        i.lx = i.x - w, i.rx = i.x;
        i.dy = i.y - h, i.uy = i.y;
    }
}

void comp() {
    cx.push_back(-INF);
    cy.push_back(-INF);

    for (auto& i : a) {
        cx.push_back(i.lx);
        cx.push_back(i.rx);
        cy.push_back(i.dy);
        cy.push_back(i.uy);
    }
    for (auto& i : b) {
        cx.push_back(i.lx);
        cx.push_back(i.rx);
        cy.push_back(i.dy);
        cy.push_back(i.uy);
    }

    sort(cx.begin(), cx.end());
    cx.erase(unique(cx.begin(), cx.end()), cx.end());
    sort(cy.begin(), cy.end());
    cy.erase(unique(cy.begin(), cy.end()), cy.end());

    for (auto& i : a) {
        i.lx = lower_bound(cx.begin(), cx.end(), i.lx) - cx.begin();
        i.rx = lower_bound(cx.begin(), cx.end(), i.rx) - cx.begin();
        i.dy = lower_bound(cy.begin(), cy.end(), i.dy) - cy.begin();
        i.uy = lower_bound(cy.begin(), cy.end(), i.uy) - cy.begin();
    }
    for (auto& i : b) {
        i.lx = lower_bound(cx.begin(), cx.end(), i.lx) - cx.begin();
        i.rx = lower_bound(cx.begin(), cx.end(), i.rx) - cx.begin();
        i.dy = lower_bound(cy.begin(), cy.end(), i.dy) - cy.begin();
        i.uy = lower_bound(cy.begin(), cy.end(), i.uy) - cy.begin();
    }
}

vector<vector<ll>> psum;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    comp();

    psum.resize(sz(cx) + 1, vector<ll>(sz(cy) + 1));

    for (auto& i : a) {
        psum[i.rx + 1][i.uy + 1]++;
        psum[i.rx + 1][i.dy]--;
        psum[i.lx][i.uy + 1]--;
        psum[i.lx][i.dy]++;
    }

    for (auto& i : b) {
        psum[i.rx + 1][i.uy + 1]--;
        psum[i.rx + 1][i.dy]++;
        psum[i.lx][i.uy + 1]++;
        psum[i.lx][i.dy]--;
    }

    for (int i = 1; i < sz(cx) + 1; i++) {
        psum[i][0] += psum[i - 1][0];
    }
    for (int i = 1; i < sz(cy) + 1; i++) {
        psum[0][i] += psum[0][i - 1];
    }
    for (int i = 1; i < sz(cx) + 1; i++) {
        for (int j = 1; j < sz(cy) + 1; j++) {
            psum[i][j] += psum[i - 1][j];
            psum[i][j] += psum[i][j - 1];
            psum[i][j] -= psum[i - 1][j - 1];
        }
    }

    ll ans = -1;
    ll x, y;
    for (int i = 1; i < sz(cx) + 1; i++) {
        for (int j = 1; j < sz(cy) + 1; j++) {
            ll res = abs(psum[i][j]);
            if (ans < res) {
                ans = res;
                //x = i - 2000, y = j - 2000;
                x = cx[i], y = cy[j];
            }
        }
    }

    cout << ans << '\n' << x << ' ' << y << '\n';
}