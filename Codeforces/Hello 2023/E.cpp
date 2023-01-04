// 토너먼트 그래프를 생각해보자. 플레이어 u가 v를 이긴다면 방향 간선 (u, v)가 존재한다.

// Lemma 1: 모든 플레이어 중 outdegree가 가장 높은 플레이어 i에 대해서, i는 candidate master다.
// Proof: 우리는 Lemma 1보다 강한 주장을 할 것이다. 즉, i는 최대 두 개의 간선을 거쳐 모든 플레이어에 도달할 수 있다.
// i에서 한 개의 간선을 거쳐 도달하는 플레이어의 집합을 S1, S2 := { 1, 2, ..., n } - S1 - { i }라고 하자.
// S2의 어떤 플레이어 j에 대해서, i에서 j까지 두 개의 간선을 거쳐 도달할 수 없다고 가정하자. (proof by contradiction)
// 그렇다면 간선 (j, i)가 존재하고, S1의 모든 노드 k에 대해 간선 (j, k)가 존재한다.
// 따라서 플레이어 j의 outdegree는 최소 |S1| + 1 이상이다.
// 플레이어 i의 outdegree가 최대라는 가정에 모순되므로, i는 최대 두 개의 간선을 거쳐 모든 플레이어에 도달할 수 있다.

// Lemma 2: outdegree가 w 이상인 모든 플레이어는 candidate master이고, 
// outdegree가 w 미만인 모든 플레이어는 candidate master가 아닌 정수 w가 존재한다.
// Proof: 토너먼트 그래프를 scc들로 분할해보자.
// 하나의 scc를 노드로 하고, scc들간의 연결관계를 간선으로 하는 dag를 생각할 수 있다. (scc dag)
// scc dag 상에서 indegree가 0인 노드 v를 생각해보자.
// 노드 v에 포함되는 플레이어들의 집합을 A, 포함되지 않는 플레이어들의 집합을 B라고 하자.
// 노드 v에 포함되는 플레이어들은 모두 candidate master이고, 포함되지 않는 플레이어들은 모두 candidate master가 아니다.
// 노드 v에 포함되는 플레이어들의 outdegree는 |B| 이상이고, 노드 포함되지 않는 플레이어들의 outdegree는 |B| 미만이다.
// 따라서 w := |B|로 생각하면 w의 존재성을 증명할 수 있다.

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
int query(int idx) {
	string s;
	for (int i = 0; i < n; i++) {
		s.push_back(i == idx ? '0' : '1');
	}
	cout << "? " << idx + 1 << ' ' << s << endl;

	int ret; cin >> ret;
	return ret;
}

void answer(vector<int> arr) {
	string s;
	for (int i = 0; i < n; i++) s.push_back('0');
	for (auto& i : arr) s[i] = '1';
	cout << "! " << s << endl;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n;

	vector<pii> arr;
	for (int i = 0; i < n; i++) {
		int res = query(i);
		arr.push_back({ res, i });
	}

	sort(arr.rbegin(), arr.rend());

	ll sum = 0;
	vector<int> done;
	for (int i = 0; i < n; i++) {
		done.push_back(arr[i].sc);
		sum += arr[i].fr;

		if (sum == (n - sz(done)) * sz(done) + sz(done) * (sz(done) - 1) / 2) {
			answer(done);
			return 0;
		}
	}

	answer(done);

	return 0;
}