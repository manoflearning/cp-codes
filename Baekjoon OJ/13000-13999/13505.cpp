#include <bits/stdc++.h>
using namespace std;
#define ll long long

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

	void insert(ll x, int key = 31) {
		if (key == -1) term = true;
		else {
			int next = -1;
            if (x & (1 << key)) next = 1;
            else next = 0;

			if (!child[next]) child[next] = new trie;
			child[next]->insert(x, key - 1);
		}
	}

	ll find(ll x, int key = 31) {
		if (key == -1) return 0;
		else {
			int next = -1;
            if (x & (1 << key)) next = 0;
            else next = 1;

			if (!child[next]) return child[!next]->find(x, key - 1);
			else return (1 << key) + child[next]->find(x, key - 1);
		}
	}
};

int n;
vector<ll> a;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    trie* root = new trie;

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    for (auto& i : a) root->insert(i);

    ll ans = 0;
    for (auto& i : a) {
        ans = max(ans, root->find(i));
    }

    cout << ans;

    delete root;

    return 0;
}