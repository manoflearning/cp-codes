#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a, ans;
int mnx = 0, mxx = 1, mny = 0, mxy = 0;
int dir = 1;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        int x; cin >> x >> i;
    }
    a.pop_back();

    ans.push_back(1);
    int nowx = 1, nowy = 0;
    for (auto& i : a) {
        dir = (dir - i + 4) % 4;
        int diff = -1;
        if (dir == 0) {
            diff = mxy - nowy + 1;
            nowy += diff;
        }
        if (dir == 1) {
            diff = mxx - nowx + 1;
            nowx += diff;
        }
        if (dir == 2) {
            diff = nowy - mny + 1;
            nowy -= diff;
        }
        if (dir == 3) {
            diff = nowx - mnx + 1;
            nowx -= diff;
        }
        ans.push_back(diff);
        mnx = min(mnx, nowx);
        mxx = max(mxx, nowx);
        mny = min(mny, nowy);
        mxy = max(mxy, nowy);
    }

    for (auto& i : ans)
        cout << i << ' ';
}