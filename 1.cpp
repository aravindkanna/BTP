#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <ctime>

#include "omp.h"

using namespace std;

int main(){
	int a = 0;
	int n = omp_get_num_threads();
	clock_t start = clock();
	#pragma omp parallel for
	for(int i=0;i<10000000;i++){
		for(int j=0;j<100;j++){
			a++;
		}		
	}
	clock_t end = clock();
	cout << "Start Time: " << start << endl;
	cout << "End Time: " << end << endl;
	cout << "Difference: " << end-start << endl;
	return 0;
}