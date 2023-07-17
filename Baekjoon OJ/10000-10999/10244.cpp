#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int n;
vector<int> a;

vector<int> isNotMul[101];

int ans = 0;
vector<int> vi(101);

void init() {
    a.clear();
    for (int i = 0; i < 101; i++) {
        isNotMul[i].clear();
    }
    ans = 0;
    for (int i = 0; i < 101; i++) vi[i] = 0;
}

void input() {
    cin >> n;
    if (!n) exit(0);
    a.resize(n);
    for (auto& i : a) cin >> i;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1) {
        init();

        input();

        a.erase(unique(a.begin(), a.end()), a.end());

        for (int x = 1; x <= 100; x++) {
            for (int i = 0; i < n; i++) {
                if (a[i] % x) isNotMul[x].push_back(i);
            }
            isNotMul[x].push_back(n);
        }
        
        for (int i = 0; i < n; i++) {
            int g = 0;
            for (int j = i; j < n; j = *upper_bound(isNotMul[g].begin(), isNotMul[g].end(), j)) {
                g = gcd(g, a[j]);
                if (!vi[g]) ans++, vi[g] = 1;
            }
        }

        cout << ans << '\n';
    }
}