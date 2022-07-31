#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <stack>
#define ll long long
using namespace std;

const int MAX = 1e3;

struct xy {
	int x, y;
};

xy st[MAX + 5], en[MAX + 5];
int enToSt[MAX + 5];

int dfsn[2 * MAX + 5], dCnt, sNum[2 * MAX + 5], sCnt;
vector<int> adj[2 * MAX + 5];
bool finished[2 * MAX + 5];
stack<int> stk;

bool isCross(xy a1, xy a2, xy b1, xy b2);
int ccw(xy a, xy b, xy c);
inline int trans(int x);
int dfs(int now);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int W, P;
	cin >> W >> P;

	for (int i = 1; i <= W; i++)
		cin >> st[i].x >> st[i].y;

	for (int i = 1; i <= P; i++)
		cin >> enToSt[i] >> en[i].x >> en[i].y;

	//임의의 파이프 쌍의 교차 여부를 기준으로 그래프 형성
	for (int i = 1; i <= P; i++) {
		for (int l = i + 1; l <= P; l++) {
			//수원지가 같을 경우 
			if (enToSt[i] == enToSt[l]) continue;

			//두 파이프가 교차할 경우
			if (isCross(st[enToSt[i]], en[i], st[enToSt[l]], en[l])) {
				//두 파이프 중 하나의 파이프에만 로봇이 삽입되어야 함.
				//(￢i ⇒ l) ∧ (￢l ⇒ i) ∧ (i ⇒ ￢l) ∧ (l ⇒ ￢i) 
				adj[trans(-i)].push_back(trans(l));
				adj[trans(-l)].push_back(trans(i)); 
				adj[trans(i)].push_back(trans(-l));
				adj[trans(l)].push_back(trans(-i));
			}
		}
	}

	//scc
	memset(dfsn, -1, sizeof(dfsn));

	for (int i = 0; i < 2 * P; i++)
		if (dfsn[i] == -1) dfs(i);

	//충족 가능성 판별
	bool yes = true;
	for (int i = 0; i < 2 * P; i += 2) {
		if (sNum[i] == sNum[i + 1]) {
			yes = false;
			break;
		}
	}

	if (yes) cout << "possible";
	else cout << "impossible";

	return 0;
}

bool isCross(xy a1, xy a2, xy b1, xy b2) {
	int aCcw = ccw(a1, a2, b1) * ccw(a1, a2, b2);
	int bCcw = ccw(b1, b2, a1) * ccw(b1, b2, a2);

	if (aCcw == 0 && bCcw == 0) {
		return a2.x == b2.x && a2.y == b2.y;
		/*pair<int, int> p1 = { a1.x, a1.y };
		pair<int, int> p2 = { a2.x, a2.y };
		pair<int, int> p3 = { b1.x, b1.y };
		pair<int, int> p4 = { b2.x, b2.y };

		if (p1 > p2) swap(p1, p2);
		if (p3 > p4) swap(p3, p4);

		return p1 <= p4 && p2 <= p3;*/
	}
	else return aCcw <= 0 && bCcw <= 0;
}

int ccw(xy a, xy b, xy c) {
	xy A = { b.x - a.x, b.y - a.y }, B = { c.x - a.x, c.y - a.y };

	ll ret = (ll)A.x * B.y - (ll)A.y * B.x;

	if (ret > 0) return 1;
	else if (ret == 0) return 0;
	else return -1;
}

inline int trans(int x) {
	return (x > 0) ? 2 * (x - 1) : 2 * (-x - 1) + 1;
}

int dfs(int now) {
	int ret = dfsn[now] = ++dCnt;

	stk.push(now);

	for (int next : adj[now]) {
		if (dfsn[next] == -1) ret = min(ret, dfs(next));
		else if (!finished[next]) ret = min(ret, dfsn[next]);
	}

	if (ret >= dfsn[now]) {
		while (true) {
			int t = stk.top();
			stk.pop();

			sNum[t] = sCnt;
			finished[t] = true;

			if (t == now) break;
		}
		sCnt++;
	}

	return ret;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 2-SAT, ccw
결정적 깨달음		: 
시간복잡도		: O(P^2)
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////