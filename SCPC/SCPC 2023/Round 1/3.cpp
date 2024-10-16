#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

int n;
vector<ll> a;

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

int getGroup2Ans() { // O(nsqrt(n))
    vector<int> di;
    for (int i = 1; i <= sqrt(n) + 0.5; i++) {
        if (n % i) continue;
        di.push_back(i);
        if (i != n / i) di.push_back(n / i);
    }

    sort(all(di));

    for (auto& d : di) {
        int isValid = 1;
        for (int i = 0; i < n; i++) {
            if (a[i] != a[(i + d) % n]) {
                isValid = 0; break;
            }
        }
        if (isValid) return d;
    }
    return n;
}

ll sumOfAll() {
    ll ret = 0;
    for (auto& i : a) ret += i;
    return ret;
}

void a_few_moment_later() {
    for (int i = 2 * n; i >= 0; i--) {
        if (a[i % n] <= 1) continue;

        a[(i + n - 1) % n] += a[i % n] - 1;
        a[i % n] = 1;
    }
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';
        
        input();

        if (n <= sumOfAll()) cout << 1 << '\n';
        else {
            a_few_moment_later();

            cout << getGroup2Ans() << '\n';
        }

        cout << flush;
    }
}