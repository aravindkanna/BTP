#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

#include "omp.h"

using namespace std;

int main(){
	int n = 100;
	vector<int> vec(n, 0);
	for(int i = 0;i < n;i += 2) {
		vec[i] = vec[i + 1] = i;
	}

	for(int i = 0;i < n;i++) {
		cout << vec[i] << "   ";
	}
	cout << endl;

	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	for(int i = 0;i < vec.size();i++) {
		cout << vec[i] << "   ";
	}
	cout << endl;

	return 0;
}