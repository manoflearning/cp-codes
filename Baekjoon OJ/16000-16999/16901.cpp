#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 202020;
const ll INF = 1e18;

const int MAXC = 2;
struct trie {
	trie* child[MAXC];
	bool term;
	trie() {
		fill(child, child + MAXC, nullptr);
		term = false;
	}
	~trie() {
		for (int i = 0; i < MAXC; i++)
			if (child[i]) delete child[i];
	}
	void insert(int val, int key = 29) {
		if (key == -1) term = true;
		else {
			int next = (val & (1 << key) ? 1 : 0);
			if (!child[next]) child[next] = new trie;
			child[next]->insert(val, key - 1);
		}
	}
	ll find(int val, int key = 29) {
		if (key == -1) return 0;
		else {
			int next = (val & (1 << key) ? 1 : 0);
			if (child[next]) return child[next]->find(val, key - 1);
            else return (1 << key) + child[!next]->find(val, key - 1);
		}
	}
};

int n;
vector<int> a(MAXN);

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

ll dnc(int s, int e, int d) {
    if (s >= e) return 0;
    if (d == -1) return 0;
    
    int mid = -1;
    for (int i = s; i + 1 <= e; i++) {
        if (!(a[i] & (1 << d)) && (a[i + 1] & (1 << d))) {
            mid = i;
            break;
        }
    }

    if (mid == -1) return dnc(s, e, d - 1);

    ll ret = 0;

    trie* root = new trie;
    for (int i = s; i <= mid; i++) root->insert(a[i]);

    ll res = INF;
    for (int i = mid + 1; i <= e; i++) {
        res = min(res, root->find(a[i]));
    }
    delete root;

    ret += res;
    ret += dnc(s, mid, d - 1);
    ret += dnc(mid + 1, e, d - 1);
    
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    sort(a.begin() + 1, a.begin() + 1 + n);

    cout << dnc(1, n, 29);
}