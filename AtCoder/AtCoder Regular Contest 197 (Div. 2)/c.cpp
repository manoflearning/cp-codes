#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAX = 4040404;

struct Fenwick { // 0-indexed
    int flag, cnt; // array size
    vector<ll> arr, t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1, cnt++);
        arr.resize(flag);
        t.resize(flag);
    }
    void add(int p, ll value) { // add value at position p
        arr[p] += value;
        while (p < flag) {
            t[p] += value;
            p |= p + 1;
        }
    }
    void modify(int p, ll value) { // set value at position p
        add(p, value - arr[p]);
    };
    // ll query(int x) {
    //     ll ret = 0;
    //     while (x >= 0) ret += t[x], x = (x & (x + 1)) - 1;
    //     return ret;
    // }
    // ll query(int l, int r) {
    //     return query(r) - (l ? query(l - 1) : 0);
    // }
    int kth(int k) { // find the kth smallest number (1-indexed)
        assert(t.back() >= k);
        int l = 0, r = arr.size();
        for (int i = 0; i <= cnt; i++) {
            int mid = (l + r) >> 1;
            ll val = mid ? t[mid - 1] : t.back();
            if (val >= k) r = mid;
            else l = mid, k -= val;
        }
        return l;
    }
} fw;

// bool isPrime[MAX + 1];
// vector<int> prime(1, 2);
// void getPrime() {
//     fill(isPrime + 2, isPrime + MAX + 1, 1);
//     for (ll i = 4; i <= MAX; i += 2)
//         isPrime[i] = 0;
//     for (ll i = 3; i <= MAX; i += 2) {
//         if (!isPrime[i]) continue;
//         prime.push_back(i);
//         for (ll j = i * i; j <= MAX; j += i * 2)
//             isPrime[j] = 0;
//     }
// }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // getPrime();

    // cout << sz(prime) << '\n';

    fw.build(MAX);
    for (int i = 1; i < MAX; i++) {
        fw.modify(i, 1);
    }

    int q; cin >> q;

    vector<bool> vis(MAX);
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;

        if (a < MAX && !vis[a]) {
            vis[a] = 1;
            for (int j = 1; j * a < MAX; j++) {
                fw.modify(j * a, 0);
            }
        }

        cout << fw.kth(b) << '\n';
    }
}
