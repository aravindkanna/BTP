#include <stdio.h>
#include <set>
#include <iostream>

using namespace std;

int main(){
	set<int> s;
	s.insert(1);
	s.insert(1);
	s.insert(2);

	set<int>::iterator it = s.begin();
	for(it=s.begin();it!=s.end();it++){
		cout << *it << "     " ;
	}
	cout << endl;
	return 0;
}