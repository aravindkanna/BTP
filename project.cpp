#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <set>
#include <ctime>

#include "omp.h"

using namespace std;

int rootNlogN(int n){
	return sqrt(n)*log(n);
}

int rootN(int n){
	return sqrt(n);
}

int logN(int n){
	return log(n);
}

vector<int> get_distinguished(int size, int s1){
	
	set<int> s;
	srand(time(NULL));
	while(1){
		//srand(time(NULL));
		int x = rand()%size;
		s.insert(x);
		if(s.size() == s1){
			break;
		}
	}
	vector<int> S1(s.begin(), s.end());
	return S1;
}

//follows sequential Floyd Marshal Algorithm
vector<vector<int> > B1(vector<vector<int> > mat, int size) {
	vector<vector<int> > res(size, vector<int> (size));

	#pragma omp parallel for private(i, j)
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			res[i][j] = mat[i][j];
		}
	}


	for(int k=0;k<size;k++){
		#pragma omp parallel for private(i, j)
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				res[i][j] = res[i][j] || (res[i][k] && res[k][j]);
			}
		}
	}

	return res;
}



vector<vector<int> > R2(vector<vector<int> > mat, int size, 
	vector<int> S, int d, int n, int e){
	vector<vector<int> > res(size, vector<int> (size));

	int s1 = rootNlogN(size);
	vector<int> S1 = get_distinguished(size, s1);
	return res;
}

void print_mat(vector<vector<int> > mat, int size){
	#pragma omp parallel for
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
				cout << mat[i][j] << "     ";
		}
		cout << endl;
	}
}

int main(){

	int N;
	cin >> N;
	
	vector<vector<int> > mat(N, vector<int> (N));

	cout << "Enter Elements Row-wise" << endl;
	for(int i=0;i<N;i++){
		cout << "Enter row: " << i << endl; 
		for(int j=0;j<N;j++){
			int x;
			cin >> x;
			mat[i][j] = x;
		}
	}

	vector<vector<int> > b1(N, vector<int> (N));
	b1 = B1(mat, N);

	print_mat(b1, N);
	//cout << rootNlogN(24) << endl;

	/*vector<int> v = get_distinguished(N, rootNlogN(N));
	cout << v.size() << endl;
	for(int i=0;i<v.size();i++){
		cout << v[i] << "   ";
	}
	cout << endl;*/
	return 0;
}