#pragma once
#include <iostream>
#include <io.h>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

struct Contents {
	string name;
	int cnt;
	bool operator<(Contents& rhs) {
		return cnt > rhs.cnt;
	}
};

vector<Contents> contents;

int searchingDir(string path, int dep);
int isFile(_finddata_t fd);
bool isExeFile(string s);

int main() {
	string path = "D:\\0JWK\\0programming\\PS-Codes\\Codes";
	searchingDir(path, 0);

	sort(contents.begin(), contents.end());

	cout<<"현재까지\n";
	for(int i = 1; i < contents.size(); i++) {
		cout<<contents[i].name<<"에서 "<<contents[i].cnt<<"문제, \n";
	}
	cout<<"총합 "<<contents[0].cnt<<"문제를 풀었습니다.";

    return 0;
}

int searchingDir(string path, int dep) {
	string dirPath = path + "\\*.*";
	struct _finddata_t fd;
	intptr_t handle;
	list<_finddata_t> fdlist;

	if ((handle = _findfirst(dirPath.c_str(), &fd)) == -1L) {
		cout << "No file in directory!" << endl;
		return 0;
	}

	int ret = 0;
	do {
		int isF = isFile(fd);
		if (fd.name[0] != '.') {
			if (isF == 0) {
				int sum = searchingDir(path + "\\" + fd.name, dep + 1);
				ret += sum;
				if(dep == 0) contents.push_back({fd.name, sum});
			}
			else {
				if (!isExeFile(fd.name)) ret++;
				fdlist.push_back(fd);
			}
		}
	} while (_findnext(handle, &fd) == 0);

	_findclose(handle);

	if(dep == 0) contents.push_back({"all", ret});

	return ret;
}

int isFile(_finddata_t fd) {
	if (fd.attrib & _A_SUBDIR) return 0;
	else return 1;
}

bool isExeFile(string s) {
	return s.back() == 'e';
}