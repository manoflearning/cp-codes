#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}
__int128_t lcm(ll x, ll y) {
    return (__int128_t)x * y / gcd(x, y);
}

const int MAX3 = 36;
const int MAX5 = 25;
const int MAX7 = 20;
const int MAXA = 17;

ll pow3[MAX3 + 1], pow5[MAX5 + 1], pow7[MAX7 + 1];
tuple<ll, ll, ll> dp[MAXA + 1][MAXA + 1][MAXA + 1];

void preprocessing() {
    {
        pow3[0] = 1;
        for (int i = 1; i <= MAX3; i++) {
            pow3[i] = 3 * pow3[i - 1];
        }
    }
    {
        pow5[0] = 1;
        for (int i = 1; i <= MAX5; i++) {
            pow5[i] = 5 * pow5[i - 1];
        }
    }
    {
        pow7[0] = 1;
        for (int i = 1; i <= MAX7; i++) {
            pow7[i] = 7 * pow7[i - 1];
        }
    }

    for (int i7 = 0; i7 <= MAX7; i7++) {
        for (int i5 = 0; i5 <= MAX5; i5++) {
            if ((__int128_t)pow7[i7] * pow5[i5] >= (ll)1e17) continue;
            for (int i3 = 0; i3 <= MAX3; i3++) {
                if ((__int128_t)pow7[i7] * pow5[i5] * pow3[i3] >= (ll)1e17) continue;

                ll x1 = pow7[i7] * pow5[i5] * pow3[i3];

                for (int j7 = 0; j7 <= MAX7; j7++) {
                    for (int j5 = 0; j5 <= MAX5; j5++) {
                        if ((__int128_t)pow7[max(i7, j7)] * pow5[max(i5, j5)] >= (ll)1e17) continue;
                        for (int j3 = 0; j3 <= MAX3; j3++) {
                            if ((__int128_t)pow7[max(i7, j7)] * pow5[max(i5, j5)] * pow3[max(i3, j3)] >= (ll)1e17) continue;

                            ll x2 = pow7[j7] * pow5[j5] * pow3[j3];

                            ll x3 = pow7[max(i7, j7)] * pow5[max(i5, j5)] * pow3[max(i3, j3)];

                            int a1 = sz(to_string(x1));
                            int a2 = sz(to_string(x2));
                            int a3 = sz(to_string(x3));
                            dp[a1][a2][a3] = {x1, x2, x3};
                        }
                    }
                }
            }
        }
    }
}

void is_valid_sol() {
    for (int a1 = 1; a1 <= 17; a1++) {
        for (int a2 = 1; a2 <= 17; a2++) {
            for (int a3 = 1; a3 <= 17; a3++) {
                auto [x1, x2, x3] = dp[a1][a2][a3];
                if (x1 != 0) {
                    assert(a1 == sz(to_string(x1)));
                    assert(a2 == sz(to_string(x2)));
                    assert(a3 == sz(to_string(x3)));
                    assert(x3 == lcm(x1, x2));
                } else {
                    assert(a3 < max(a1, a2) || a1 + a2 < a3);
                }
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    preprocessing();

    is_valid_sol();

    int tc; cin >> tc;
    while (tc--) {
        int a1, a2, a3;
        cin >> a1 >> a2 >> a3;

        auto [x1, x2, x3] = dp[a1][a2][a3];

        if (x1 == 0) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
            cout << x1 << ' ' << x2 << '\n';
        }
    }
}
