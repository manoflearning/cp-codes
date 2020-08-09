#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 102 * 101 / 2; // 102C2 (����)

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

	//�׷��� �����

	//���������� ���� Ȥ�� ���������� ���� ���ؼ� 5m/s�� �ӵ��� �޷��� ��.
	for (int i = 1; i < arr.size(); i++) {
		double len = cal_len(0, i);
		graph[0].push_back({ len / 5, i });
	}
	//�� �������� �ٸ� ������ ���� ���ؼ�, 1. ������ ź �� ���� �Ÿ��� �޸��ų�, 2. ������ Ÿ�� �ʰ� �޸��� ��� �� �� ���� �ð��� �ɸ��� ��츦 ���Ѵ�.
	for (int i = 2; i < arr.size(); i++) {
		for (int l = i + 1; l < arr.size(); l++) {
			double len = cal_len(i, l);
			double v = min(len / 5, fabs(len - 50) / 5 + 2);
			graph[i].push_back({ v, l });
			graph[l].push_back({ v, i });
		}
	}
	//�� �������� ���������� ����
	for (int i = 2; i < arr.size(); i++) {
		double len = cal_len(i, 1);
		double v = min(len / 5, fabs(len - 50) / 5 + 2);
		graph[i].push_back({ v, 1 });
	}

	//���ͽ�Ʈ�� �˰�����
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
���� �ع�		: ������ �޸��� ��Ģ�� ���� ����ġ�� �ִ� �׷��� �����. ���ͽ�Ʈ�� �˰������� ���� �ִܰŸ� ã��.
������ ������		: 
�ð����⵵		: O(n^2lgn)
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////