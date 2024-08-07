#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

int n;
vector<pii> a;

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) {
        cin >> i.fr >> i.sc;
        i.sc--;
    }
}

int solve1() {
    int ret = 0;

    vector<int> ps1(101010), ps2(101010);
    for (auto& i : a) {
        ps1[i.fr]++, ps2[i.sc]++;
    }
    for (int i = 1; i < 101010; i++) {
        ps1[i] += ps1[i - 1];
        ps2[i] += ps2[i - 1];
    }

    for (auto& i : a) {
        ret = max(ret, ps1[i.sc] - ps2[i.fr - 1]);
    }
    return ret;
}

int solve2() {
    vector<int> ps(101010);
    for (auto& i : a) {
        ps[i.fr]++, ps[i.sc + 1]--;
    }
    int ret = 0;
    for (int i = 1; i < 101010; i++) {
        ps[i] += ps[i - 1];
        ret = max(ret, ps[i]);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    cout << solve1() << ' ' << solve2();
}