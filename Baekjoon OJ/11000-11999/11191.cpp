#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXB = 62;

int n;
vector<ll> a;
vector<ll> b[66];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    for (auto& x : a) {
        for (int i = MAXB; i >= 0; i--) {
            if (x & (1ll << i)) {
                b[i].push_back(x);
                break;
            }
        }
    }

    return 0;
}