#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int L, K, C;
vector<int> a;

void input() {
    cin >> L >> K >> C;
    a.resize(K);
    for (auto& i : a) cin >> i;
}

int solve1() {
    int l = 1, r = L;
    while (l < r) {
        int mid = (l + r) >> 1;
        int len = 0, cnt = C;
        while (cnt-- && len + mid < L) {
            int cut = *(upper_bound(all(a), len + mid) - 1);
            if (cut == len) break;
            len = cut;
        }
        if (len + mid >= L) r = mid;
        else l = mid + 1;
    }
    return l;
}

int solve2(int x) {
    int l = 0, r = upper_bound(all(a), x) - a.begin() - 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        int len = a[mid], cnt = C - 1;
        while (cnt-- && len + x < L) {
            int cut = *(upper_bound(all(a), len + x) - 1);
            if (cut == len) break;
            len = cut;
        }
        if (len + x >= L) r = mid;
        else l = mid + 1;
    }
    return a[l];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    a.push_back(INF);
    sort(all(a));
    a.erase(unique(all(a)), a.end());

    int ans1 = solve1();
    int ans2 = solve2(ans1);
    cout << ans1 << ' ' << ans2 << '\n';
}