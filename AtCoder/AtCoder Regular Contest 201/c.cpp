#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998'244'353;
const int N = 202020;

const char st = 'A';
const int MAXC = 'B' - 'A' + 1;

ll pow2[N];

struct trie {
    trie *child[MAXC];
    ll dp, cnt;
    bool base = 0;
    trie() {
        fill(child, child + MAXC, nullptr);
        dp = cnt = 0;
        base = 0;
    }
    ~trie() {
        for (int i = 0; i < MAXC; i++)
            if (child[i]) delete child[i];
    }
    void insert(const string &s, int key = 0) {
        if (s.size() == key) {
            base = 1;
        } else {
            int next = s[key] - st;
            if (!child[next]) child[next] = new trie;
            child[next]->insert(s, key + 1);
        }

        cnt = 0;
        cnt += (child[0] ? child[0]->cnt : 0) + (child[1] ? child[1]->cnt : 0);
        cnt += base;

        dp = 0;
        dp += (base ? pow2[cnt - base] : 0);
        dp %= MOD;
        dp += (child[0] ? child[0]->dp : 0) * (child[1] ? child[1]->dp : 0) % MOD;
        dp %= MOD;

        // DEBUG
        // cout << s << ' ' << key << '\n';
        // cout << dp << ' ' << cnt << ' ' << base << '\n';
        // cout << '\n';
    }
    // bool find(const string &s, int key = 0) {
    //     if (s.size() == key) return term;
    //     else {
    //         int next = s[key] - st;
    //         if (!child[next]) return false;
    //         else return child[next]->find(s, key + 1);
    //     }
    // }
};

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    pow2[0] = 1;
    for (int i = 1; i < N; i++) {
        pow2[i] = 2 * pow2[i - 1] % MOD;
    }

    trie *root = new trie;

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        root->insert(s);
        cout << root->dp << '\n';
    }

    delete root;
}
