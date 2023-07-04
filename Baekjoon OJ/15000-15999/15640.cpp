#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n = 100, m = 50;
    vector<pair<int, int>> a;

    int en = 1;
    for (int st = 35; st <= 99; st += 2) {
        a.push_back({ st, en++ });
    }

    cout << n << ' ' << m << ' ' << a.size() << '\n';
    for (auto& i : a)
        cout << i.first << ' ' << i.second << '\n';
}

// c := f(33)
// f(98) = 1/2 * (1 + 1 + c) = 1 + 1/2 * c
// f(96) = 1/2 * (1 + f(98) + 1 + c) = 1 + 1/2 * f(98) + 1/2 * c = 2 + c
// f()