#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n,k; cin >> n >> k;
    vector<string> arr(n);
    for(auto &s:arr) {
        cin >> s;
        s+="1";
    }
    k++;

    typedef bitset<2000> T;

    vector<T> bits(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            bits[i] <<= 1;
            bits[i] |= (arr[i][j]-'0');
        }
    }

    T a; for(int i=0; i<2000; i++) a[i]=1;
    vector<pair<T,T>> last(k, {a,a});
    string ans = "*";

    for(int i = 0; i < n; i++) {
        T now = bits[i];
        string nans(n, '0');

        // T nxt(1ll << (n - i - 1));
        T nxt(T(1) << i);

        for(int j=k-1; j>=0; j--) {
            if((((now >> j) & T(1)).to_ullong())) {
                if(last[j].first == a) break;
                else {
                    now = now ^ last[j].first;
                    nxt ^= last[j].second;
                }
            }
        }

        if(now == 0) {
            int m = nxt.count();
            int cnt = 0;

            for(int j = 0; j < n; j++) {
                if(((nxt >> j) & T(1)).to_ullong()) nans[j] = ((cnt++) < (m / 2)) + '1';
            }
            ans = nans;

            break;
        }

        for(int j = k-1; j >= 0; j--) {
            if((((now >> j) & T(1)).to_ullong())) {
                last[j].first = now;
                last[j].second = nxt;

                break;
            } 
        }
    }
    cout << ans << '\n';
}
