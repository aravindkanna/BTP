#ifdef __APPLE__
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <map>
#else
#include<bits/stdc++.h>
#endif
using namespace std;

typedef vector<int> VI; 
typedef pair<int,int> PII;
typedef long long int LL;
typedef pair<LL, LL> PLL;

#define si [] () { int x; scanf("%d", &x); return x; }
#define sl [] () { LL x; scanf("%lld", &x); return x; }
#define oi [] (int x) { printf("%d", x); }
#define os [] () { printf(" "); }
#define onl [] () { printf("\n"); }

#define pb                           push_back 
#define mp                           make_pair
#define F                            first
#define S                            second
#define INF                          INT_MAX
#define mod 1000000007
#define __sync__		     std::ios::sync_with_stdio(false);
#define all(a)			     a.begin(),a.end()

#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) {
	cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
	const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

set<int> S;

int main()
{
	srand(time(NULL));
	int n, m;
	cin>>n>>m;
	int sq = sqrt(n);
	int s = sq; //n/(rand()%sq + 1);
	int d = sq; //n/(rand()%sq + 1);
	int t = sq; //n/(rand()%sq + 1);
	cout<<n<<" "<<m<<" "<<s<<" "<<d<<" "<<t<<"\n";
	for(int i=0;i<m;i++)
	{
		int u, v, w;
		cin>>u>>v>>w;
		cout<<u<<" "<<v<<"\n";
	}
	while(S.size() < s) S.insert((rand()%n)+1);
	for(auto &x : S) cout<<x<<" ";
	cout<<"\n";
	return 0;
}      
