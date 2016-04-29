#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <set>
#include <ctime>

#include "omp.h"

using namespace std;

void modify(vector<vector<int> > &mat, int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(mat[i][j]){
				mat[i][j] = 1;
			}
		}
	}
}

void search(vector<vector<int> > mat, int size, 
	int v0, int d, vector<int> &vec, vector<int> &reach){
	//base case
	d = d + 1;
	reach[v0] = 1;
	if(d == 1){
		for(int i=0;i<size;i++){
			if(mat[v0][i] && !reach[v0]){
				vec.push_back(i);
				reach[i] = 1;
			}
		}
		return;
	}

	for(int i=0;i<size;i++){
		if(mat[v0][i] && i!=v0 && !reach[i]){
			vec.push_back(i);
			reach[i] = 1;
			search(mat, size, i, d-1, vec, reach);
		}
	}
	vec.push_back(v0);
}

int rootNlogN(int n){
	return ceil(sqrt(n)*log(n));
}

int rootN(int n){
	return ceil(sqrt(n));
}

int logN(int n){
	return ceil(log(n));
}


/***
	This function gives you a vector of distinguished nodes of the size we want.
	num_nodes : representation for total number of nodes
	num_dist  : representation for number of distinguished nodes
	returns a vector of some integers which we can consider as distinguished nodes.
	As set stores in sorted order they come out to be sorted
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

	vector<vector<int> > res1(size, vector<int> (size));
	int search_dist = ceil(size/s1);
	for(int i=0;i<s1;i++){
		vector<int> vec;
		vector<int> reach(size);
		search(mat, size, S1[i], search_dist, vec, reach);

		
	}



	/*//Base case
	if(d==1){
		for(int i=0;i<s;i++){
			for(int j=0;j<size;j++){
				if(mat[S[i]][j]){
					res[S[i]][j] = 1;
				}
			}
		}
		return res;
	}
	else{
			//first step
		 	vector<vector<int> > res1(size, vector<int> (size));
		 	res1 = R2(mat, size, S1, ceil(size/s1), s1, e);

		 	//second step : Finding the transitive closure for res2
		 	vector<vector<int> > res2(size, vector<int> (size));
		 	res2 = B1(res1, size);

		 	//adding the edges found in second step to original graph
		 	for(int i=0;i<size;i++){
		 		for(int j=0;j<size;j++){
		 			if(mat[i][j] || res2[i][j]){
		 				mat[i][j] = 1;
		 			}
		 		}
		 	}

		 	//third step
		 	vector<vector<int> > res3(size, vector<int> (size));
		 	res3 = R2(mat, size, S, ceil(size/s1), s1, e);

		 	return res3;*/

		 	/*   R2(mat, size, S1, ceil(size/s1), n, e) + 
			   R2(mat, size, S1, ceil((d*s1)/size), s1, s1*s1) +
			   R2(mat, size, S, ceil(size/s1), n, e+s1*s1);*/



	
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

	vector<vector<int> > b1(N, vector<int> (N));
	b1 = B1(mat, N);

	//print_mat(b1, N);
	//cout << rootNlogN(24) << endl;

	/*vector<int> v = get_distinguished(N, rootNlogN(N));
	cout << v.size() << endl;
	for(int i=0;i<v.size();i++){
		cout << v[i] << "   ";
	}
	cout << endl;*/

	vector<int> S;
	for(int i=0;i<N;i++){
		S.push_back(i);
	}
	/*vector<vector<int> > r2(N, vector<int> (N));
	r2 = R2(mat, N, S, 2, N, N);
	print_mat(r2, N);*/

	vector<int> vec;
	vector<int> reach(N);
	search(mat, N, 2, 2, vec, reach);
	for(int i=0;i<vec.size();i++){
		cout << vec[i] << "   ";
	}

	return 0;
}