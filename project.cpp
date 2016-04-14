#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "omp.h"

using namespace std;

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

int rootNlogN(int n){
	return sqrt(n)*log(n);
}

int rootN(int n){
	return sqrt(n);
}

vector<vector<int> > R2(vector<vector<int> > mat, int size, 
	vector<int> S, int d, int n, int e){
	vector<vector<int> > res(size, vector<int> (size));
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
	return 0;
}