#include <iostream>
#include <queue>
using namespace std;

const int MAX = 100;
const pair<int, int> dir[4] = { {-1,0},{0,1},{1,0},{0,-1} }; //��, ��, ��, ��

int n;
bool visited[MAX + 1][MAX + 1];
bool apple[MAX + 1][MAX + 1];
queue<pair<int, int>> snk;
queue<pair<int, char>> chng;

int simul(int Y, int X, int time, int dr);

int main() {
	cin >> n;
	//��� ��ġ ���� �Է�
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int y, x;
		cin >> y >> x;

		apple[y][x] = true;
	}
	//���� ��ȯ ���� �Է�
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		int time;
		char dir;
		cin >> time >> dir;

		chng.push({ time, dir });
	}
	//
	snk.push({ 0, 0 });
	cout << simul(1, 1, 0, 1);

	return 0;
}

int simul(int Y, int X, int time, int dr) {
	//base case : ���� �Ӹ��� �� �Ǵ� ���� �浹���� ��
	if (visited[Y][X]) return time;
	if (Y < 1 || n < Y || X < 1 || n < X) return time;
	//�� ���� �ø���, �� ���� ����
	visited[Y][X] = true;
	snk.push({ Y,X });
	//����� �Դ��� �� ���̸� �پ����
	if (apple[Y][X]) apple[Y][X] = false;
	else {
		visited[snk.front().first][snk.front().second] = false;
		snk.pop();
	}
	//���� ��ȯ
	if (!chng.empty() && time == chng.front().first) {
		if (chng.front().second == 'D') {
			if (dr == 3) dr = 0;
			else dr++;
		}
		else {
			if (dr == 0) dr = 3;
			else dr--;
		}
		chng.pop();
	}
	//�̵�
	return simul(Y + dir[dr].first, X + dir[dr].second, time + 1, dr);
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: 
���� ���		: 
������ ������		:
���� ����		: 1. ���ϰ� �Ųٷ� ���ǵ�. �迭���� ���� {-1, 0}, �ϴ� {1, 0}���� ����.
				  2.
*/////////////////////////////////////////////////////////////////////