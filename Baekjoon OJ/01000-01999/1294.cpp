#include <bits/stdc++.h>
using namespace std;

struct Node {
    string s;
    bool operator<(const Node& rhs) const {
        return s + rhs.s > rhs.s + s;
    }
};

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    int n; cin >> n;
	priority_queue<Node> pq;
    for (int i = 0; i < n; i++) {
        Node du; cin >> du.s;
        pq.push(du);
    }
    
    while (!pq.empty()) {
        Node du = pq.top();
        pq.pop();
        
        cout << du.s.front();
        du.s.erase(du.s.begin());
        if (!du.s.empty()) pq.push(du);
    }

	return 0;
}