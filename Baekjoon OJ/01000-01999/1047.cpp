#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n;
struct Node {
    int x, y, len;
};
vector<Node> a;
vector<int> cx, cy;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) 
        cin >> i.x >> i.y >> i.len;

    for (auto& i : a) {
        cx.push_back(i.x);
        cy.push_back(i.y);
    }
    sort(all(cx));
    cx.erase(unique(all(cx)), cx.end());
    sort(all(cy));
    cy.erase(unique(all(cy)), cy.end());


    sort(all(a), [&](const Node& p1, const Node& p2) {
        return p1.len > p2.len;
    });

    int ans = n;
    for (int i = 0; i < sz(cx); i++) {
        for (int j = i; j < sz(cx); j++) {
            for (int p = 0; p < sz(cy); p++) {
                for (int q = p; q < sz(cy); q++) {
                    int sx = cx[i], ex = cx[j];
                    int sy = cy[p], ey = cy[q];

                    int sum = 0, cnt = 0;
                    vector<int> arr;
                    for (auto& v : a) {
                        if (v.x < sx || ex < v.x || v.y < sy || ey < v.y) sum += v.len, cnt++;
                        else arr.push_back(v.len);
                    }
                    for (auto& i : arr) {
                        if (2 * (ex - sx + ey - sy) <= sum) break;
                        sum += i, cnt++;
                    }

                    if (2 * (ex - sx + ey - sy) <= sum) {
                        ans = min(ans, cnt);
                    }
                }
            }
        }
    }

    cout << ans;
}