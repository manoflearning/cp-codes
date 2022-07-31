#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 102 * 101 / 2; // 102C2 (조합)

struct xy {
	double x; double y;
};

int N;
vector<xy> arr;
vector<pair<double, int>> graph[MAX];
vector<double> path(MAX, 1e9);
bool visited[MAX];

inline double cal_len(int a, int b);
double shortestpath();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	cout << fixed; cout.precision(6);

	double x, y;

	for (int i = 0; i < 2; i++) {
		cin >> x >> y;
		arr.push_back({ x, y });
	}

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		arr.push_back({ x, y });
	}

	//그래프 만들기

	//시작점에서 대포 혹은 도착점으로 가기 위해선 5m/s의 속도로 달려야 함.
	for (int i = 1; i < arr.size(); i++) {
		double len = cal_len(0, i);
		graph[0].push_back({ len / 5, i });
	}
	//한 대포에서 다른 대포로 가기 위해선, 1. 대포에 탄 후 남은 거리를 달리거나, 2. 대포에 타지 않고 달리는 경우 중 더 적은 시간이 걸리는 경우를 택한다.
	for (int i = 2; i < arr.size(); i++) {
		for (int l = i + 1; l < arr.size(); l++) {
			double len = cal_len(i, l);
			double v = min(len / 5, fabs(len - 50) / 5 + 2);
			graph[i].push_back({ v, l });
			graph[l].push_back({ v, i });
		}
	}
	//한 대포에서 도착점으로 가기
	for (int i = 2; i < arr.size(); i++) {
		double len = cal_len(i, 1);
		double v = min(len / 5, fabs(len - 50) / 5 + 2);
		graph[i].push_back({ v, 1 });
	}

	//다익스트라 알고리즘
	cout << shortestpath();

	return 0;
}

inline double cal_len(int a, int b) {
	return sqrt(pow(arr[a].x - arr[b].x, 2) + pow(arr[a].y - arr[b].y, 2));
}
double shortestpath() {
	priority_queue<pair<double, int>> pq;
	pq.push({ -0, 0 });
	
	while (!pq.empty()) {
		double v = -pq.top().first;
		int n = pq.top().second;
		pq.pop();
		
		if (path[n] < v) continue;

		if (n == 1) return v;

		path[n] = v;
		visited[n] = true;

		for (pair<double, int> next : graph[n]) {
			if (visited[next.second]) continue;
			pq.push({ -(v + next.first), next.second });
		}
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 대포와 달리기 규칙에 따라 가중치가 있는 그래프 만들기. 다익스트라 알고리즘을 통해 최단거리 찾기.
결정적 깨달음		: 
시간복잡도		: O(n^2lgn)
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////