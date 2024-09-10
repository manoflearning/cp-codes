#include <bits/stdc++.h>
using namespace std;
#define ll long long

const char st = 'a';
const int MAXC = 'z' - 'a' + 1;
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
	void insert(const string& s, int key = 0) {
		if (s.size() == key) term = true;
		else {
			int next = s[key] - st;
			if (!child[next]) child[next] = new trie;
			child[next]->insert(s, key + 1);
		}
	}
	bool find(const string& s, int key = 0) {
		if (s.size() == key) return term;
		else {
			int next = s[key] - st;
			if (!child[next]) return false;
			else return child[next]->find(s, key + 1);
		}
	}
    bool can_win() {
        bool ret = 0;
        for (int nxt = 0; nxt < 26; nxt++) {
            if (!child[nxt]) continue;
            ret |= !child[nxt]->can_win();
        }
        return ret;
    }
    bool can_lose() {
        bool ret = 0, is_leaf = 1;
        for (int nxt = 0; nxt < 26; nxt++) {
            if (!child[nxt]) continue;
            is_leaf = 0;
            ret |= !child[nxt]->can_lose();
        }
        if (is_leaf) return 1;
        else return ret;
    }
};

int n;
ll k;
vector<string> a;
vector<int> gn;

void print_fr() { cout << "First"; exit(0); }
void print_sc() { cout << "Second"; exit(0); }

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    a.resize(n);
    for (auto& i : a) cin >> i;

    trie* root = new trie;

    for (auto& i : a) root->insert(i);
    
    bool can_win = root->can_win();
    bool can_lose = root->can_lose();

    if (can_win && can_lose) {
        // lose -> lose -> lose -> ... -> win
        print_fr();
    }
    else if (can_win) {
        // ... -> lose -> win -> lose -> win
        if (k & 1) print_fr();
        else print_sc();
    }
    else if (can_lose) {
        // lose -> lose -> lose -> ... -> lose
        print_sc();
    }
    else {
        // lose -> lose -> lose -> ... -> lose
        print_sc();
    }

    delete root;
}
