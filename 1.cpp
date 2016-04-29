#include <stdio.h>
#include <set>
#include <iostream>
#include <vector>

using namespace std;

int main(){
	set<int> s;
	s.insert(1);
	s.insert(1);
	s.insert(2);

	/*set<int>::iterator it = s.begin();
	for(it=s.begin();it!=s.end();it++){
		cout << *it << "     " ;
	}
	cout << endl;*/

	int m = 5;
	int n = 10;
	vector<vector<int> > vec(5, vector<int> (10));
	vector<int> v(10);

	for(int i=0;i<10;i++){
		cout << v[i] << "    ";
	}
	cout << endl;

	/*for(int i=0;i<vec.size();i++){
		for(int j=0;j<vec[i].size();j++){
			cout << vec[i][j] << "    ";
		}
		cout << endl;
	}*/

	return 0;
}