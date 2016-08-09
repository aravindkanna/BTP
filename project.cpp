#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <set>
#include <ctime>
#include <algorithm>

#include "omp.h"

using namespace std;

void rem_dup(vector<int> &v){
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
}

void modify(vector<vector<int> > &mat, int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(mat[i][j]){
				mat[i][j] = 1;
			}
		}
	}
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

//tested..!!!
void search(vector<vector<int> > mat, int size, 
	int v0, int d, vector<int> &vec, vector<int> &reach){
	
	reach[v0] = 1;
	vec.push_back(v0);
	if(d == 1){
		for(int i = 0;i < size;i++){
			if(mat[v0][i] == 1 && reach[i] == 0){
				vec.push_back(i);
				reach[i] = 1;
			}
		}
		return;
	}

	for(int i = 0;i < size;i++){
		if(mat[v0][i] && i != v0 && !reach[i]){
			vec.push_back(i);
			reach[i] = 1;
			search(mat, size, i, d - 1, vec, reach);
		}
	}
	rem_dup(vec);
}

int rootN(int n){
	return ceil(sqrt(n));
}

int logN(int n){
	return ceil(log(n));
}

int rootNlogN(int n){
	return ceil(sqrt(n)*log(n));
}



/***
	This function gives you a vector of distinguished nodes of the size we want.
	num_nodes : representation for total number of nodes
	num_dist  : representation for number of distinguished nodes
	returns a vector of some integers which we can consider as distinguished nodes.
	As set stores in sorted order they come out to be sorted
	It is tested and working fine
***/
vector<int> get_distinguished(int num_nodes, int num_dist){
	
	set<int> s;
	srand(time(NULL));
	while(1){
		//srand(time(NULL));
		int x = rand()%num_nodes;
		s.insert(x);
		if(s.size() == num_dist){
			break;
		}
	}
	vector<int> S1(s.begin(), s.end());
	return S1;
}

//follows sequential Floyd Warshall Algorithm
vector<vector<int> > B1(vector<vector<int> > mat, int size) {
	vector<vector<int> > res(size, vector<int> (size));

	#pragma omp parallel for private(i, j)
	for(int i = 0;i < size;i++){
		for(int j = 0;j < size;j++){
			res[i][j] = mat[i][j];
		}
	}


	for(int k = 0;k < size;k++){
		#pragma omp parallel for private(i, j)
		for(int i = 0;i < size;i++){
			for(int j = 0;j < size;j++){
				res[i][j] = res[i][j] || (res[i][k] && res[k][j]);
			}
		}
	}

	return res;
}


/***
	This function returns a matrix 
	Can call that transitive closure of s nodes specified in S, searched through
	a distance of d, with n nodes and e edges.
	The matrix returned gives you an idea of what nodes are reachable from S to 
	a distance of d.
***/
vector<vector<int> > R2(vector<vector<int> > mat, int size, 
	vector<int> S, int d, int n, int e){

	int s = S.size();
	vector<vector<int> > res(size, vector<int> (size));

	int s1 = rootNlogN(size);
	vector<int> S1 = get_distinguished(size, s1);
	//S1 is the set of rootNlogN distinguished nodes

	//Step-1 is to select s1 distinguished nodes and to search for n/s1 distance
	//for other nodes.
	vector<vector<int> > res1(size, vector<int> (size));
	int search_dist = ceil(size/s1);
	for(int i = 0;i < s1;i++){
		vector<int> vec;
		vector<int> reach(size);
		search(mat, size, S1[i], search_dist + 1, vec, reach);
		rem_dup(vec);

		int x = vec.size();
		for(int j=0;j<x;j++){
			res1[S1[i]][vec[j]] = 1;
		}
	}
	print_mat(res1, size);
	cout << endl << endl;
	//Step 1 is completed. Next step is to find transitive closure for the 
	//graph obtained by res1.

	vector<vector<int> > res2(size, vector<int> (size));
	res2 = B1(res2, size);
	print_mat(res2, size);
	cout << endl << endl;

	//Now the next step is to add these edges to the original graph.
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(!mat[i][j] && res2[i][j]){
				mat[i][j] = 1;
			}
		}
	}

	//Next step is to search from original S nodes to a distance of n/s1 
	//in the resulting mat graph. Also search_dist is same as before.
	for(int i=0;i<s;i++){
		vector<int> vec;
		vector<int> reach(size);
		search(mat, size, S[i], search_dist+1, vec, reach);
		rem_dup(vec);

		int x = vec.size();
		for(int j=0;j<x;j++){
			res[S[i]][vec[j]] = 1;
		}
	}
	
	return res;
}

int main(){

	/***
		Hexagon Input
		0 1 0 0 0 1
		1 0 1 0 0 0
		0 1 0 1 0 0
		0 0 1 0 1 0
		0 0 0 1 0 1
		1 0 0 0 1 0
	***/

	int N;
	cout << "Enter size of matrix:" << endl;
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

	modify(mat, N);
	print_mat(mat, N);

	vector<int> vec;
	vector<int> reach(N, 0);
	search(mat, N, 3, 2, vec, reach);

	cout << endl << endl;
	for(int i = 0;i < vec.size();i++) {
		cout << vec[i] << "    ";
	}
	cout <<endl;
	return 0;
}